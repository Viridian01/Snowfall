// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnowfallItem.h"
#include "Sound/SoundBase.h"
#include "UObject/NoExportTypes.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, DefaultToInstanced)
class SNOWFALL_API AWeaponBase : public ASnowfallItem
{
	GENERATED_BODY()

private:

	bool bIsRoundInChamber;
	float NextPossibleAttackTime;
	bool bIsOwned;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* FireSound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* V_Model;

	UStaticMeshComponent* V_ModelStaticMeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int MagazineCapacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int CurrentMagazine;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float FireRate;

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText AmmoDisplay;

private:

	void UpdateAmmoDisplay();
	void OnPickup(AActor* InteractingActor);

public:

	AWeaponBase();
	USoundBase* GetFireSound();
	int GetCurrentMagazine();
	bool Fire();
	void DryFire();
	void LoadMagazine();
	bool IsRoundInChamber();
	float GetNextAttackTime();
	void UpdateAttackTime(float Time);

	virtual void Interact(AActor* InteractingActor) override;
};
