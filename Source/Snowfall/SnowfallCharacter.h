// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "WeaponBase.h"
#include "SnowfallCharacter.generated.h"

UCLASS(config = Game)
class SNOWFALL_API ASnowfallCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	AWeaponBase* ActiveWeapon;
	UStaticMeshComponent* WorldWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator HeadRot;

private:
	//class ASnowfallController* SnowfallController;
	class UCameraComponent* CharacterCamera;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Snowfall Player")
	float InteractRange;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Snowfall Player")
	float BaseTurnRate;

	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"), Category = "Snowfall Player")
	float BaseLookUpRate;

	//USnowfallMovementComponent* MovementPtr;

	bool bIsSprinting;
	bool bWantsToWalk;
	UWorld* World;

public:

	// Sets default values for this character's properties
	ASnowfallCharacter();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category="Snowfall Character")
	void UpdateHeadRot();

	// Handles strafing movement, left and right
	void Move(FVector Direction, float Value);
	void Turn(float Rate);
	void LookUp(float Rate);
	void MoveForward(float Value);
	void MoveRight(float Value);

	void Fire1();
	void Reload();

	void Interact();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	
};
