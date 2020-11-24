// Fill out your copyright notice in the Description page of Project Settings.


#include "WeaponBase.h"

UWeaponBase::UWeaponBase()
{
	roundInChamber = false;
}

USoundBase* UWeaponBase::GetFireSound()
{
	return fireSound;
}

int UWeaponBase::GetCurrentMagazine()
{
	return currentMagazine;
}

void UWeaponBase::FireRound()
{
	if (!roundInChamber)
	{
		return;
	}
	
	if (currentMagazine > 0)
	{
		currentMagazine -= 1;
	}
	else
	{
		roundInChamber = false;
	}
}

void UWeaponBase::LoadMagazine()
{
	if(roundInChamber)
	{
		currentMagazine = magazineCapacity;
	}
	else
	{
		currentMagazine = magazineCapacity - 1;
		roundInChamber = true;
	}
}

bool UWeaponBase::isRoundInChamber()
{
	return roundInChamber;
}
