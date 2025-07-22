#pragma once

#include "CoreMinimal.h"
#include "BaseActor.h"
#include "MineItem.generated.h"

UCLASS()
class PRACTICEPROJECT_API AMineItem : public ABaseActor
{
	GENERATED_BODY()
	
public:
	AMineItem();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* ExplosionCollision;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* ExplosionParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* ExplosionSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDelay;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionRadius;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	int32 ExplosionDamage;

	FTimerHandle ExplosionTimerHandle;
	bool bHasExplded;

	virtual void ActivateItem(AActor* Activator) override;

	void Explode();

};
