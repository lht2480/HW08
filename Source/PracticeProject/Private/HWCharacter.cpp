#include "HWCharacter.h"
#include "HWPlayerController.h"
#include "HWGameState.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"


AHWCharacter::AHWCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(RootComponent);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;

	OverheadWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("OverheadWidget"));
	OverheadWidget->SetupAttachment(GetMesh());
	OverheadWidget->SetWidgetSpace(EWidgetSpace::Screen);//위젯스페이스를 결정하는 코드


	BaseNormalSpeed = 600.0f;
	SprintSpeedMultiplier = 1.5f;
	BaseSprintSpeed = BaseNormalSpeed * SprintSpeedMultiplier;

	CurrentNormalSpeed = BaseNormalSpeed;
	CurrentSprintSpeed = BaseSprintSpeed;

	GetCharacterMovement()->MaxWalkSpeed = CurrentNormalSpeed;
	bIsSprinting = false;

	MaxHealth = 100.0f;
	Health = MaxHealth;

}

void AHWCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdateOverheadHP();
}

void AHWCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (AHWPlayerController* PlayerController = Cast<AHWPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Triggered, this, &AHWCharacter::Move);
			}
			if (PlayerController->JumpAction)
			{
				EnhancedInput->BindAction(PlayerController->JumpAction, ETriggerEvent::Triggered, this, &AHWCharacter::StartJump);
				EnhancedInput->BindAction(PlayerController->MoveAction, ETriggerEvent::Completed, this, &AHWCharacter::StopJump);
			}
			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(PlayerController->LookAction, ETriggerEvent::Triggered, this, &AHWCharacter::Look);
			}
			if (PlayerController->SprintAction)
			{
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Triggered, this, &AHWCharacter::StartSprint);
				EnhancedInput->BindAction(PlayerController->SprintAction, ETriggerEvent::Completed, this, &AHWCharacter::StopSprint);
			}
		}
	}
}

void AHWCharacter::Move(const FInputActionValue& value)
{
	if (!Controller) return;

	const FVector2D MoveInput = value.Get<FVector2D>();

	if (!FMath::IsNearlyZero(MoveInput.X))
	{
		AddMovementInput(GetActorForwardVector(), MoveInput.X);
	}

	if (!FMath::IsNearlyZero(MoveInput.Y))
	{
		AddMovementInput(GetActorRightVector(), MoveInput.Y);
	}

}

void AHWCharacter::StartJump(const FInputActionValue& value)
{
	if (value.Get<bool>())
	{
		Jump();
	}
}

void AHWCharacter::StopJump(const FInputActionValue& value)
{
	if (!value.Get<bool>())
	{
		StopJumping();
	}
}

void AHWCharacter::Look(const FInputActionValue& value)
{
	FVector2D LookInput = value.Get<FVector2D>();

	AddControllerYawInput(LookInput.X);
	AddControllerPitchInput(LookInput.Y);
}

void AHWCharacter::StartSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		bIsSprinting = true;
		GetCharacterMovement()->MaxWalkSpeed = CurrentSprintSpeed;
	}
}

void AHWCharacter::StopSprint(const FInputActionValue& value)
{
	if (GetCharacterMovement())
	{
		bIsSprinting = false;
		GetCharacterMovement()->MaxWalkSpeed = CurrentNormalSpeed;
	}
}

float AHWCharacter::GetHealth() const
{
	return Health;
}

void AHWCharacter::AddHealth(float Amount)
{
	Health = FMath::Clamp(Health + Amount, 0.0f, MaxHealth);
	UpdateOverheadHP();
}

float AHWCharacter::TakeDamage(
	float DamageAmount,
	struct FDamageEvent const& DamageEvent,
	AController* EventInstigator,
	AActor* DamageCauser)
{
	float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health = FMath::Clamp(Health - DamageAmount, 0.0f, MaxHealth);
	UpdateOverheadHP();

	if (Health <= 0.0f)
	{
		OnDeath();
	}
	return ActualDamage;
}

void AHWCharacter::OnDeath()
{
	AHWGameState* HWGameState = GetWorld() ? GetWorld()->GetGameState<AHWGameState>() : nullptr;
	if (HWGameState)
	{
		HWGameState->OnGameOver();
	}
}

void AHWCharacter::UpdateOverheadHP()
{
	if (!OverheadWidget) return;

	UUserWidget* OverheadWidgetInstance = OverheadWidget->GetUserWidgetObject();
	if (!OverheadWidgetInstance) return;

	if (UTextBlock* HPText = Cast<UTextBlock>(OverheadWidgetInstance->GetWidgetFromName(TEXT("OverHeadHP"))))
	{
		HPText->SetText(FText::FromString(FString::Printf(TEXT(" %.0f / %.0f"), Health, MaxHealth)));
	}
}

void AHWCharacter::ApplySlowEffect(float SpeedMultiplier, float Duration)
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		CurrentNormalSpeed = BaseNormalSpeed * SpeedMultiplier;
		CurrentSprintSpeed = BaseSprintSpeed * SpeedMultiplier;

		if (bIsSprinting)
		{
			MovementComponent->MaxWalkSpeed = CurrentSprintSpeed;
		}
		else 
		{
			MovementComponent->MaxWalkSpeed = CurrentNormalSpeed;
		}

		GetWorldTimerManager().ClearTimer(SlowEffectTimerHandle);
		GetWorldTimerManager().SetTimer(
			SlowEffectTimerHandle,
			this,
			&AHWCharacter::ResetMovementSpeed,
			Duration,
			false
		);
	}
}

void AHWCharacter::ResetMovementSpeed()
{
	UCharacterMovementComponent* MovementComponent = GetCharacterMovement();
	if (MovementComponent)
	{
		CurrentNormalSpeed = BaseNormalSpeed;
		CurrentSprintSpeed = BaseSprintSpeed;

		if (bIsSprinting)
		{
			MovementComponent->MaxWalkSpeed = CurrentSprintSpeed;
		}
		else
		{
			MovementComponent->MaxWalkSpeed = CurrentNormalSpeed;
		}
	}
	GetWorldTimerManager().ClearTimer(SlowEffectTimerHandle);
}

float AHWCharacter::GetSlowEffectRemainingTime() const
{
	if (GetWorld())
	{
		return GetWorldTimerManager().GetTimerRemaining(SlowEffectTimerHandle);
	}
	return 0.0f;
}