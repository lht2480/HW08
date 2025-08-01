#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "HWGameInstance.generated.h"

UCLASS()
class PRACTICEPROJECT_API UHWGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UHWGameInstance();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 TotalScore;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "GameData")
	int32 CurrentLevelIndex;

	UFUNCTION(BlueprintCallable, Category = "GameData")
	void AddToScore(int32 Amount);
};
