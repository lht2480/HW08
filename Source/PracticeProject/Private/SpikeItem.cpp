#include "SpikeItem.h"
#include "Engine/World.h"
#include "HWGameState.h"
#include "HWCharacter.h"
#include "Kismet/GamePlayStatics.h"

ASpikeItem::ASpikeItem()
{
	SpikeDamage = 15;

	HitCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("HitCapsule"));
	HitCollision->SetupAttachment(RootComponent);

	HitCollision->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void ASpikeItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	if (Activator && Activator->ActorHasTag("Player"))
	{
		UGameplayStatics::ApplyDamage(
			Activator,
			SpikeDamage,
			nullptr,
			this,
			UDamageType::StaticClass()
		);

		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Player Damaged by Spike! Damage: %d"), SpikeDamage));

		AHWCharacter* Character = Cast<AHWCharacter>(Activator);
		if (Character)
		{
			Character->UpdateOverheadHP();
		}
	}
}
