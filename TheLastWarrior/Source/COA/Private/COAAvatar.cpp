// Fill out your copyright notice in the Description page of Project Settings.


#include "COAAvatar.h"

ACOAAvatar::ACOAAvatar() :
	bRunning(false),
	bStaminaDrained(false),
	WalkSpeed(200.f),
	RunSpeed(500.f),
	MovementScale(1.0f),
	Stamina(100.0f),
	StaminaDrainRate(0.4f),
	StaminaGainRate(0.2f),
	MaxStamina(100.0f),
	bIsPressed(false),
	bHasVelocity(false),
	walkingSoundTimer(0.6f)
{
	mSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	mSpringArm->TargetArmLength = 300.0f;
	mSpringArm->SetupAttachment(RootComponent);

	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mCamera->SetupAttachment(mSpringArm, USpringArmComponent::SocketName);

	mCamera->bUsePawnControlRotation = false;
	mSpringArm->bUsePawnControlRotation = true;
	bUseControllerRotationYaw = false;

	GetCharacterMovement()->JumpZVelocity = 450.0f;
}
// Called to bind functionality to input
void ACOAAvatar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &ACharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &ACharacter::AddControllerPitchInput);


	PlayerInputComponent->BindAxis("MoveForward", this, &ACOAAvatar::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ACOAAvatar::MoveRight);

	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ACOAAvatar::RunPressed);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ACOAAvatar::RunReleased);

}

// Called when the game starts or when spawned
void ACOAAvatar::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ACOAAvatar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->MovementMode == EMovementMode::MOVE_Walking)
	{
		if (!bDead && bRunning && !bStaminaDrained && bIsPressed && AnimState == ECharAnimState::CAS_IDLE)
		{
			Stamina = FMath::Max(0.f, Stamina - StaminaDrainRate);

			if (Stamina == 0.0f)
			{
				bStaminaDrained = true;
				UpdateMovementParams();				
			}		
		}
		else
		{
			if (!bDead)
			{
				Stamina = FMath::Min(MaxStamina, Stamina + StaminaGainRate);

				if (Stamina >= MaxStamina)
				{
					bStaminaDrained = false;
					UpdateMovementParams();
				}
			}	
		}
	}
}

void ACOAAvatar::MoveForward(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, value * MovementScale);
}

void ACOAAvatar::MoveRight(float value)
{
	FRotator Rotation = GetController()->GetControlRotation();
	FRotator YawRotation(0.0f, Rotation.Yaw, 0.0f);
	FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, value * MovementScale);
}

void ACOAAvatar::RunPressed()
{
	bRunning = true;
	UpdateMovementParams();
	walkingSoundTimer = 0.35;
}

void ACOAAvatar::RunReleased()
{
	bRunning = false;
	UpdateMovementParams();
	walkingSoundTimer = 0.6;
	
}

void ACOAAvatar::UpdateMovementParams()
{
	MaxWalkSpeed = bRunning && !bStaminaDrained ? RunSpeed : WalkSpeed;
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
}

