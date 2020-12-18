// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowfallCharacter.h"


// Sets default values
ASnowfallCharacter::ASnowfallCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	sprinting = false;
}

// Called when the game starts or when spawned
void ASnowfallCharacter::BeginPlay()
{
	Super::BeginPlay();

	worldWeapon = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Weapon_W")));
}

// Called every frame
void ASnowfallCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnowfallCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASnowfallCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ASnowfallCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	//PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &ACharacter::Crouch);
	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ASnowfallCharacter::Shoot);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ASnowfallCharacter::Reload);
}

void ASnowfallCharacter::MoveForward(float value)
{
	if (!FMath::IsNearlyZero(value))
	{
		float modifier = sprinting ? SPRINT_MODIFIER : 1.0f;
		AddMovementInput(GetActorForwardVector(), value * modifier);
	}
}

void ASnowfallCharacter::MoveRight(float value)
{
	if (!FMath::IsNearlyZero(value))
	{
		AddMovementInput(GetActorRightVector(), value);
	}
}

void ASnowfallCharacter::Shoot()
{
	if (activeWeapon->isRoundInChamber())
	{
		activeWeapon->FireRound();
		if (!activeWeapon)
		{
			return;
		}

		if (worldWeapon)
		{
			UGameplayStatics::PlaySoundAtLocation(worldWeapon, activeWeapon->GetFireSound(), worldWeapon->GetComponentTransform().GetLocation());
		}
	}
}

void ASnowfallCharacter::Reload()
{
	if (!activeWeapon)
	{
		return;
	}

	activeWeapon->LoadMagazine();
}

void ASnowfallCharacter::Crouch()
{
	
}

void ASnowfallCharacter::Sprint()
{
	sprinting = true;
}

void ASnowfallCharacter::UpdateHeadRot()
{
	headRot.Roll = -GetControlRotation().Pitch;
}

