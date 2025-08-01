#include "HWGameInstance.h"

UHWGameInstance::UHWGameInstance()
{
	TotalScore = 0;
	CurrentLevelIndex = 0;
}

void UHWGameInstance::AddToScore(int32 Amount)
{
	TotalScore += Amount;
	UE_LOG(LogTemp, Warning, TEXT("Total Score Updated : %d"), TotalScore);
}