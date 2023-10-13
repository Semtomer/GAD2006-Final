// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "COABaseCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "COAAvatar.generated.h"

/**
 * 
 */
UCLASS()
class COA_API ACOAAvatar : public ACOABaseCharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	ACOAAvatar();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
		UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
		USpringArmComponent* mSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float Stamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float MaxStamina;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float StaminaGainRate;

	UPROPERTY(EditAnywhere, Category = "COA")
		float StaminaDrainRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float WalkSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "COA")
		float MaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float MovementScale;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "COA")
		bool bStaminaDrained;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "COA")
		bool bIsPressed;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "COA")
		bool bHasVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "COA")
		float walkingSoundTimer;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

private: 
	
	bool bRunning;

	void MoveForward(float value);
	void MoveRight(float value);
	void RunPressed();
	void RunReleased();
	void UpdateMovementParams();
};
	