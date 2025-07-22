#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GamePlayStatics.h"
#include "SpikeItem.generated.h"

UCLASS()
class PRACTICEPROJECT_API ASpikeItem : public ABaseActor
{
	GENERATED_BODY()
	
public:
	ASpikeItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 SpikeDamage;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UCapsuleComponent* HitCollision;

	virtual void ActivateItem(AActor* Activator) override;
};
