// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundBase.h"
#include "UObject/NoExportTypes.h"
#include "WeaponBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, BlueprintType, Blueprintable, EditInlineNew, DefaultToInstanced)
class SNOWFALL_API UWeaponBase : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FText name;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	USoundBase* fireSound;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	UStaticMesh* model;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int magazineCapacity;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	int currentMagazine;

	bool roundInChamber;

public:

	UWeaponBase();
	USoundBase* GetFireSound();
	int GetCurrentMagazine();
	void FireRound();
	void LoadMagazine();
	bool isRoundInChamber();
	
};
