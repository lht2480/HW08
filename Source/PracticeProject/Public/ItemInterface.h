#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

UINTERFACE(MinimalAPI)
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};


class PRACTICEPROJECT_API IItemInterface
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp, //�ڱ� �ڽ��� �ǹ�
		AActor* OtherActor, //���⿡ �ε��� ������ ����
		UPrimitiveComponent* OtherComp, //���Ϳ� �پ��ִ� �浹�� ����Ű�� ������Ʈ
		int32 OtherBodyIndex,
		bool bFrameSweep,
		const FHitResult& SweepResult) = 0;

	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;

	virtual void ActivateItem(AActor* Activor) = 0;
	virtual FName GetItemType() const = 0; //FName Ÿ������ �˾Ƴ��� ����
};
