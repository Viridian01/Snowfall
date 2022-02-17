// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "SnowfallCharacter.h"
#include "GameFramework/PlayerController.h"
#include "SnowfallCharacterController.generated.h"

class USnowfallMovementComponent;

/**
 * 
 */
UCLASS()
class SNOWFALL_API ASnowfallCharacterController : public APlayerController
{
	GENERATED_BODY()

private:

	ASnowfallCharacter* ControlledCharacter;
	AWeaponBase* ActiveWeapon;

public:

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupInputComponent() override;

	void Turn(float Rate);
	void LookUp(float Rate);
	void Jump();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Fire1();
	void Reload();
	void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void BeginPlayingState() override;

};
