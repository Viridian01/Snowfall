// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowfallCharacter.h"

#include "DrawDebugHelpers.h"
#include "Interactable.h"
#include "SnowfallMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ASnowfallCharacter::ASnowfallCharacter() // : ACharacter(ObjectInitializer.SetDefaultSubobjectClass<USnowfallMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	InteractRange = 1000.0f;
	BaseTurnRate = 45.0f;
	BaseLookUpRate = 45.0f;

	//MovementPtr = Cast<USnowfallMovementComponent>(ACharacter::GetMovementComponent());
}

// Called when the game starts or when spawned
void ASnowfallCharacter::BeginPlay()
{
	Super::BeginPlay();

	World = GetWorld();

	CharacterCamera = Cast<UCameraComponent>(GetDefaultSubobjectByName("PlayerCamera"));
	WorldWeapon = Cast<UStaticMeshComponent>(GetDefaultSubobjectByName(TEXT("Weapon_W")));
}

// Called every frame
void ASnowfallCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASnowfallCharacter::Move(FVector Direction, float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		AddMovementInput(Direction, Value);
	}
}

void ASnowfallCharacter::Turn(float Rate)
{
	Rate = Rate * BaseTurnRate * World->GetDeltaSeconds();
	AddControllerYawInput(Rate);
}

void ASnowfallCharacter::LookUp(float Rate)
{
	Rate = Rate * BaseLookUpRate * World->GetDeltaSeconds();
	AddControllerPitchInput(Rate);
}

void ASnowfallCharacter::MoveForward(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		AddMovementInput(GetActorForwardVector(), Value);
	}
}

void ASnowfallCharacter::MoveRight(float Value)
{
	if (!FMath::IsNearlyZero(Value))
	{
		AddMovementInput(GetActorRightVector(), Value);
	}
}

void ASnowfallCharacter::Fire1()
{
	if (!ActiveWeapon || !WorldWeapon)
	{
		return;
	}

	float CurrTime = World->GetTimeSeconds();
	float WeaponAttackTimer = ActiveWeapon->GetNextAttackTime();
	if (WeaponAttackTimer <= CurrTime)
	{
		ActiveWeapon->UpdateAttackTime(CurrTime);
		if (ActiveWeapon->Fire())
		{
			UGameplayStatics::PlaySoundAtLocation(WorldWeapon, ActiveWeapon->GetFireSound(), WorldWeapon->GetComponentTransform().GetLocation());
		}
	}
	else
	{
		ActiveWeapon->DryFire();
	}
}

void ASnowfallCharacter::Reload()
{
	if (!ActiveWeapon)
	{
		return;
	}

	ActiveWeapon->LoadMagazine();
}

void ASnowfallCharacter::Interact()
{
	// UE_LOG(LogTemp, Display, TEXT("Attempting interaction."));
	FHitResult HitResult;
	if(World->LineTraceSingleByChannel(HitResult, CharacterCamera->GetComponentLocation(), (CharacterCamera->GetComponentLocation() + (CharacterCamera->GetForwardVector() * InteractRange)), ECC_Visibility))
	{
		// DrawDebugLine(World, CharacterCamera->GetComponentLocation(), HitResult.ImpactPoint, FColor::Green, false, 5.f, ECC_WorldStatic, 1.f);
		IInteractable* InteractActor = Cast<IInteractable>(HitResult.GetActor());
		if (InteractActor)
		{
			// UE_LOG(LogTemp, Display, TEXT("Interactable Detected."));
			InteractActor->Interact();
		}
	}
}

void ASnowfallCharacter::UpdateHeadRot()
{
	HeadRot.Roll = -GetControlRotation().Pitch;
}
