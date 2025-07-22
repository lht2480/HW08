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
	TSubclassOf<AActor> ItemClass;//�ϵ� ���۷��� : Ŭ������ �׻� �ε�� ���¿��� �ٷ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
};
