#include "HWPlayerController.h"
#include "HWGameState.h"
#include "HWGameInstance.h"
#include "EnhancedInputSubsystems.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"

AHWPlayerController::AHWPlayerController()
	:InputMappingContext(nullptr),
	MoveAction(nullptr),
	JumpAction(nullptr),
	LookAction(nullptr),
	SprintAction(nullptr),
	HUDWidgetClass(nullptr),
	HUDWidgetInstance(nullptr),
	MainMenuWidgetClass(nullptr),
	MainMenuWidgetInstance(nullptr)
{
}

void AHWPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (InputMappingContext)
			{
				Subsystem->AddMappingContext(InputMappingContext, 0);
			}
		}
	}

	FString CurrentMapName = GetWorld()->GetMapName();
	if (CurrentMapName.Contains("MenuLevel"))
	{
		ShowMainMenu(false);
	}

	AHWGameState* HWGameState = GetWorld() ? GetWorld()->GetGameState<AHWGameState>() : nullptr;
	if (HWGameState)
	{
		HWGameState->UpdateHUD();
	}
}

UUserWidget* AHWPlayerController::GetHUDWidget() const
{
	return HUDWidgetInstance;
}

void AHWPlayerController::ShowMainMenu(bool bIsRestart)
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (MainMenuWidgetClass)
	{
		MainMenuWidgetInstance = CreateWidget<UUserWidget>(this, MainMenuWidgetClass);
		if (MainMenuWidgetInstance)
		{
			MainMenuWidgetInstance->AddToViewport();

			bShowMouseCursor = true;
			SetInputMode(FInputModeUIOnly());
		}

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))//��ŸƮ���� ����ŸƮ����
		{
			if (bIsRestart)
			{
				ButtonText->SetText(FText::FromString(TEXT("Restart")));
			}
			else
			{
				ButtonText->SetText(FText::FromString(TEXT("Start")));
			}
		}

		UTextBlock* GameTitleText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("GameStartText")));
		UTextBlock* GameOverText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("GameOverText")));

		if (bIsRestart) // ���ӿ�����
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc)
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}

			//�� ���� ǥ��
			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
			{
				if (UHWGameInstance* HWGameInstance = Cast<UHWGameInstance>(UGameplayStatics::GetGameInstance(this)))
				{
					TotalScoreText->SetText(FText::FromString(FString::Printf(TEXT("Total Score: %d"), HWGameInstance->TotalScore)));
					TotalScoreText->SetVisibility(ESlateVisibility::Visible);
				}
			}

			if (GameTitleText)
			{
				GameTitleText->SetVisibility(ESlateVisibility::Hidden); // �Ǵ� Hidden
			}
			// "Game over!"
			if (GameOverText)
			{
				GameOverText->SetVisibility(ESlateVisibility::Visible);
			}
		}
		else
		{
			if (UTextBlock* TotalScoreText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName("TotalScoreText")))
			{
				TotalScoreText->SetVisibility(ESlateVisibility::Hidden); // �Ǵ� Hidden
			}
			// "Game over!" �ؽ�Ʈ �����
			if (GameOverText)
			{
				GameOverText->SetVisibility(ESlateVisibility::Hidden); // �Ǵ� Hidden
			}
			// "���θԱ� ����" �ؽ�Ʈ ���̱�
			if (GameTitleText)
			{
				GameTitleText->SetText(FText::FromString(TEXT("CoinGame")));
				GameTitleText->SetVisibility(ESlateVisibility::Visible);
			}
		}
	}
}

void AHWPlayerController::ShowGameHUD()
{
	if (HUDWidgetInstance)
	{
		HUDWidgetInstance->RemoveFromParent();
		HUDWidgetInstance = nullptr;
	}

	if (MainMenuWidgetInstance)
	{
		MainMenuWidgetInstance->RemoveFromParent();
		MainMenuWidgetInstance = nullptr;
	}

	if (HUDWidgetClass)
	{
		HUDWidgetInstance = CreateWidget<UUserWidget>(this, HUDWidgetClass);
		if (HUDWidgetInstance)
		{
			HUDWidgetInstance->AddToViewport();

			bShowMouseCursor = false;
			SetInputMode(FInputModeGameOnly());
		}

		AHWGameState* HWGameState = GetWorld() ? GetWorld()->GetGameState<AHWGameState>() : nullptr;
		if (HWGameState)
		{
			HWGameState->UpdateHUD();
		}
	}
}

void AHWPlayerController::StartGame()
{
	if (UHWGameInstance* HWGameInstnce = Cast<UHWGameInstance>(UGameplayStatics::GetGameInstance(this)))
	{
		HWGameInstnce->CurrentLevelIndex = 0;
		HWGameInstnce->TotalScore = 0;
	}
	
	UGameplayStatics::OpenLevel(GetWorld(), FName("BasicLevel"));
	SetPause(false);
}