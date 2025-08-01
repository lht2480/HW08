#include "SlowingItem.h"
#include "HWCharacter.h"

ASlowingItem::ASlowingItem()
{
	ItemType = FName(TEXT("SlowingItem"));

	SlowMultiplier = 0.3f;
	SlowDuration = 3.0f;
}

void ASlowingItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	AHWCharacter* Character = Cast<AHWCharacter>(Activator);
	if (Activator && Activator->ActorHasTag("Player"))
	{
		if (AHWCharacter* PlayerCharacter = Cast<AHWCharacter>(Activator))
		{
			PlayerCharacter->ApplySlowEffect(SlowMultiplier, SlowDuration);
		}
	}
	DestroyItem();
}
