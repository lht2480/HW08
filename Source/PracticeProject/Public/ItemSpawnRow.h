#pragma once

#include "CoreMinimal.h"
#include "ItemSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;//하드 레퍼런스 : 클래스가 항상 로드된 상태에서 바로 접근
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
};
