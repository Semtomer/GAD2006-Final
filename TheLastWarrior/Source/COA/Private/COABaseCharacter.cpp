// Fill out your copyright notice in the Description page of Project Settings.


#include "COABaseCharacter.h"

// Sets default values
ACOABaseCharacter::ACOABaseCharacter():

bDead(false),
Health(100.f),
MaxHealth(100.f),
AttackStartupTime(0.5f),
shieldHealth(50.f),
bIsShieldActive(false)

{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);

}

// Called when the game starts or when spawned
void ACOABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACOABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float ACOABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (bDead) return 0.0f;

	//Blueprint event call
	DamageAmount = ModifyDamage(DamageAmount);

	if (bIsShieldActive)
		shieldHealth -= DamageAmount;
	else 
		Health -= DamageAmount;

	if (Health <= 0.f) {

		bDead = true;

		APlayerController* PlayerController = Cast<APlayerController>(GetController());

		if (PlayerController != nullptr)
		{
			DisableInput(PlayerController);
		}
		CharacterDied();
	}

	return 0.0f;
}

void ACOABaseCharacter::ChangeAnimState_Implementation(ECharAnimState NewState)
{
	AnimState = NewState;

	if (NewState == ECharAnimState::CAS_ATTACK)
	{ //Start timer
		GWorld->GetTimerManager().SetTimer(AttackTimer, this, &ACOABaseCharacter::OnAttack, AttackStartupTime, false);
	}
	else if (NewState == ECharAnimState::CAS_STRONGATTACK)
	{
		GWorld->GetTimerManager().SetTimer(AttackTimer, this, &ACOABaseCharacter::OnAttack, AttackStartupTime, false);
	}
	else
	{ //Clear timer
		GWorld->GetTimerManager().ClearTimer(AttackTimer);
	}
}

