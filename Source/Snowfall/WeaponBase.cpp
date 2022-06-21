// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

void AWeaponBase::UpdateAmmoDisplay()
{
	AmmoDisplay = FText::FromString(FString::FromInt(GetCurrentMagazine()).Append(IsRoundInChamber() ? "+1" : ""));
	UE_LOG(LogTemp, Display, TEXT("Updated ammo display."));
}

void AWeaponBase::DryFire()
{

}

AWeaponBase::AWeaponBase()
{
	V_ModelStaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WorldModel"));
	if (V_ModelStaticMeshComponent->SetStaticMesh(V_Model))
	{
		V_ModelStaticMeshComponent->ToggleVisibility();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Unable to assign associated W_Model to Static Mesh Component."));
	}
	bIsRoundInChamber = false;
	NextPossibleAttackTime = 0.0f;
	UpdateAmmoDisplay();
}

USoundBase* AWeaponBase::GetFireSound()
{
	return FireSound;
}

int AWeaponBase::GetCurrentMagazine()
{
	return CurrentMagazine;
}

bool AWeaponBase::Fire()
{
	if (!bIsRoundInChamber)
	{
		return false;
	}
	
	// If weapon is ready to fire
	if (CurrentMagazine > 0)
	{
		CurrentMagazine -= 1;
	}
	else
	{
		bIsRoundInChamber = false;
	}
	UpdateAmmoDisplay();
	return true;
}

void AWeaponBase::LoadMagazine()
{
	if(bIsRoundInChamber)
	{
		CurrentMagazine = MagazineCapacity;
	}
	else
	{
		CurrentMagazine = MagazineCapacity - 1;
		bIsRoundInChamber = true;
	}
	UpdateAmmoDisplay();
}

bool AWeaponBase::IsRoundInChamber()
{
	return bIsRoundInChamber;
}

float AWeaponBase::GetNextAttackTime()
{
	return NextPossibleAttackTime;
}

void AWeaponBase::UpdateAttackTime(float Time)
{
	NextPossibleAttackTime = Time + FireRate;
}

void AWeaponBase::Interact(AActor* InteractingActor)
{
	Super::Interact(InteractingActor);

	OnPickup(InteractingActor);
}

void AWeaponBase::OnPickup(AActor* InteractingActor)
{
	bIsOwned = true;
	W_ModelStaticMeshComponent->ToggleVisibility();
	V_ModelStaticMeshComponent->ToggleVisibility();

	AttachToActor(InteractingActor, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
}
