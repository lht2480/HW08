#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "SlowingItem.generated.h"

UCLASS()
class PRACTICEPROJECT_API ASlowingItem : public ABaseActor
{
	GENERATED_BODY()
	
public:
	ASlowingItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float SlowMultiplier;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	float SlowDuration;

	virtual void ActivateItem(AActor* Activor) override;
};
