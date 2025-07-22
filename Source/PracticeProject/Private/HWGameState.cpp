#include "HWGameState.h"
#include "HWGameInstance.h"
#include "HWPlayerController.h"
#include "SpawnVolume.h"
#include "CoinItem.h"
#include "HWCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/TextBlock.h"
#include "Blueprint/UserWidget.h"

AHWGameState::AHWGameState()
{
	Score = 0;
	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;
	LevelDuration = 30.0f;
	CurrentLevelIndex = 0;
	MaxLevels = 3;
}

void AHWGameState::BeginPlay()
{
	Super::BeginPlay();
	StartLevel();

	GetWorldTimerManager().SetTimer(
		HUDUpdateTimerHandle,
		this,
		&AHWGameState::UpdateHUD,
		0.1f,
		true
	);
}

int32 AHWGameState::GetScore() const
{
	return Score;
}
void AHWGameState::AddScore(int32 Amount)
{
	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UHWGameInstance* HWGameInstance = Cast<UHWGameInstance>(GameInstance);
		if (HWGameInstance)
		{
			HWGameInstance->AddToScore(Amount);
		}
	}
}

void AHWGameState::StartLevel()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AHWPlayerController* HWPlayerController = Cast<AHWPlayerController>(PlayerController))
		{
			HWPlayerController->ShowGameHUD();
		}
	}

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UHWGameInstance* HWGameInstance = Cast<UHWGameInstance>(GameInstance);
		if (HWGameInstance)
		{
			CurrentLevelIndex = HWGameInstance->CurrentLevelIndex;
		}
	}

	SpawnedCoinCount = 0;
	CollectedCoinCount = 0;

	TArray<AActor*> FoundVolumes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundVolumes);

	const int32 ItemToSpawn = 40;

	for (int32 i = 0; i < ItemToSpawn; i++)
	{
		if (FoundVolumes.Num() > 0)
		{
			ASpawnVolume* SpawnVolume = Cast<ASpawnVolume>(FoundVolumes[0]);
			if (SpawnVolume)
			{
				AActor* SpawnedActor = SpawnVolume->SpawnRandomItem();
				if (SpawnedActor && SpawnedActor->IsA(ACoinItem::StaticClass()))
				{
					SpawnedCoinCount++;
				}
			}
		}
	}

	UpdateHUD();

	GetWorldTimerManager().SetTimer(
		LevelTimerHandle,
		this,
		&AHWGameState::OnLevelTimeUp,
		LevelDuration,
		false
	);

	UE_LOG(LogTemp, Warning, TEXT("레벨 %d단계 시작!!! 코인 %d개 스폰!!"),
		CurrentLevelIndex + 1,
		SpawnedCoinCount);
}

void AHWGameState::OnLevelTimeUp()
{
	EndLevel();
}

void AHWGameState::OnCoinCollected()
{
	CollectedCoinCount++;
	UE_LOG(LogTemp, Warning, TEXT("Coin Collected: %d / %d"), CollectedCoinCount, SpawnedCoinCount);

	if (SpawnedCoinCount > 0 && CollectedCoinCount >= SpawnedCoinCount)
	{
		EndLevel();
	}
}

void AHWGameState::EndLevel()
{
	GetWorldTimerManager().ClearTimer(LevelTimerHandle);

	if (UGameInstance* GameInstance = GetGameInstance())
	{
		UHWGameInstance* HWGameInstance = Cast<UHWGameInstance>(GameInstance);
		if (HWGameInstance)
		{
			AddScore(Score);
			CurrentLevelIndex++;
			HWGameInstance->CurrentLevelIndex = CurrentLevelIndex;
		}
	}

	if (CurrentLevelIndex >= MaxLevels)
	{
		OnGameOver();
		return;
	}
	
	if (LevelMapNames.IsValidIndex(CurrentLevelIndex))
	{
		UGameplayStatics::OpenLevel(GetWorld(), LevelMapNames[CurrentLevelIndex]);
	}
	else
	{
		OnGameOver();
	}
}

void AHWGameState::OnGameOver()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AHWPlayerController* HWPlayerController = Cast<AHWPlayerController>(PlayerController))
		{
			HWPlayerController->SetPause(true);
			HWPlayerController->ShowMainMenu(true);
		}
	}
}

void AHWGameState::UpdateHUD()
{
	if (APlayerController* PlayerController = GetWorld()->GetFirstPlayerController())
	{
		if (AHWPlayerController* HWPlayerController = Cast<AHWPlayerController>(PlayerController))
		{
			if (UUserWidget* HUDWidget = HWPlayerController->GetHUDWidget())
			{
				if (UTextBlock* TimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Time"))))
				{
					float RemainingTime = GetWorldTimerManager().GetTimerRemaining(LevelTimerHandle);
					TimeText->SetText(FText::FromString(FString::Printf(TEXT("Time : %.1f"), RemainingTime)));
				}

				if (UTextBlock* ScoreText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Score"))))
				{
					if(UGameInstance* GameInstance = GetGameInstance())
					{
						UHWGameInstance* HWGameInstance = Cast<UHWGameInstance>(GameInstance);
						if (HWGameInstance)
						{
							ScoreText->SetText(FText::FromString(FString::Printf(TEXT("Score : %d"), HWGameInstance->TotalScore)));
						}
					}
				}

				if (UTextBlock* LevelText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("Level"))))
				{
					LevelText->SetText(FText::FromString(FString::Printf(TEXT("Level : %d"), CurrentLevelIndex + 1)));
				}

				if (UTextBlock* SlowTimeText = Cast<UTextBlock>(HUDWidget->GetWidgetFromName(TEXT("SlowTime"))))
				{
					AHWCharacter* Character = Cast<AHWCharacter>(PlayerController->GetPawn());

					if (Character)
					{
						float RemainingSlowTime = Character->GetSlowEffectRemainingTime();
						if (RemainingSlowTime > 0.0f)
						{
							SlowTimeText->SetText(FText::FromString(FString::Printf(TEXT("Slow Time : %.1f"), RemainingSlowTime)));
							SlowTimeText->SetVisibility(ESlateVisibility::Visible);
						}
						else
						{
							SlowTimeText->SetText(FText::GetEmpty());
							SlowTimeText->SetVisibility(ESlateVisibility::Hidden);
						}
					}
				}
			}
		}
	}
}