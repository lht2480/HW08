#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "itemInterface.h"
#include "BaseActor.generated.h"

class USphereComponent;

UCLASS()
class PRACTICEPROJECT_API ABaseActor : public AActor, public IItemInterface
{
	GENERATED_BODY()

public:
	ABaseActor();

protected:
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp, //�ڱ� �ڽ��� �ǹ�
		AActor* OtherActor, //���⿡ �ε��� ������ ����
		UPrimitiveComponent* OtherComp, //���Ϳ� �پ��ִ� �浹�� ����Ű�� ������Ʈ
		int32 OtherBodyIndex,
		bool bFrameSweep,
		const FHitResult& SweepResult) override;

	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) override;
	virtual void ActivateItem(AActor* Activor) override;
	virtual FName GetItemType() const override;

	virtual void DestroyItem();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item")
	FName ItemType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USceneComponent* Scene;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	USphereComponent* Collision;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Item|Component")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	UParticleSystem* PickupParticle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Item|Effects")
	USoundBase* PickupSound;
};
