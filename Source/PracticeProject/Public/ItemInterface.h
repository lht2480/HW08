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
		UPrimitiveComponent* OverlappedComp, //자기 자신을 의미
		AActor* OtherActor, //여기에 부딪힌 상대방의 액터
		UPrimitiveComponent* OtherComp, //액터에 붙어있던 충돌을 일으키는 컴포넌트
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
	virtual FName GetItemType() const = 0; //FName 타입형을 알아낼때 유용
};
