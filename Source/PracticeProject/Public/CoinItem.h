#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "CoinItem.generated.h"

UCLASS()
class PRACTICEPROJECT_API ACoinItem : public ABaseActor
{
	GENERATED_BODY()
	
public:
	ACoinItem();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 PointValue;

	virtual void ActivateItem(AActor* Activator) override;
};