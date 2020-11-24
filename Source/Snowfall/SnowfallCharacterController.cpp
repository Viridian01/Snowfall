// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowfallCharacterController.h"

void ASnowfallCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASnowfallCharacterController::BeginPlayingState()
{
	Super::BeginPlayingState();
	controlledCharacter = Cast<ASnowfallCharacter>(GetCharacter());
	activeWeapon = controlledCharacter->activeWeapon;
}

void ASnowfallCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (activeWeapon)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, activeWeapon->name.ToString());
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Green, FString::FromInt(activeWeapon->GetCurrentMagazine()).Append(activeWeapon->isRoundInChamber() ? "+1" : ""));
	}
}
