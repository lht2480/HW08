#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "HealingItem.generated.h"

UCLASS()
class PRACTICEPROJECT_API AHealingItem : public ABaseActor
{
	GENERATED_BODY()
	
public:
	AHealingItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 HealAmount;

	virtual void ActivateItem(AActor* Activator) override;
};
