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

		if (UTextBlock* ButtonText = Cast<UTextBlock>(MainMenuWidgetInstance->GetWidgetFromName(TEXT("StartButtonText"))))//스타트일지 리스타트일지
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

		if (bIsRestart) // 게임오버시
		{
			UFunction* PlayAnimFunc = MainMenuWidgetInstance->FindFunction(FName("PlayGameOverAnim"));
			if (PlayAnimFunc)
			{
				MainMenuWidgetInstance->ProcessEvent(PlayAnimFunc, nullptr);
			}

			//총 점수 표시
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
				GameTitleText->SetVisibility(ESlateVisibility::Hidden); // 또는 Hidden
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
				TotalScoreText->SetVisibility(ESlateVisibility::Hidden); // 또는 Hidden
			}
			// "Game over!" 텍스트 숨기기
			if (GameOverText)
			{
				GameOverText->SetVisibility(ESlateVisibility::Hidden); // 또는 Hidden
			}
			// "코인먹기 게임" 텍스트 보이기
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