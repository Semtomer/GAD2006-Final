// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"
#include "COACharAnimInstance.h"
#include "COABaseCharacter.generated.h"

UCLASS()
class COA_API ACOABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACOABaseCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
		bool bDead;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "COA")
		float Health;

	UPROPERTY(EditAnywhere, Category = "COA")
		float HealingRate;

	UPROPERTY(EditAnywhere, Category = "COA")
		float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float AttackStartupTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "COA")
		ECharAnimState AnimState;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "COA")
		float shieldHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "COA")
		bool bIsShieldActive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintImplementableEvent, Category = "COA")
	float ModifyDamage(float damage);

	UFUNCTION(BlueprintImplementableEvent, Category = "COA")
	void CharacterDied();

	UFUNCTION(BlueprintImplementableEvent, Category = "COA")
	void OnAttack();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "COA")
	void ChangeAnimState(ECharAnimState NewState);

	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "COA")
	ECharAnimState GetAnimState() { return AnimState; }

private:
	FTimerHandle AttackTimer;

};
