// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "WeaponBase.h"
#include "SnowfallCharacterAnimInstance.h"
#include "SnowfallCharacter.generated.h"

UCLASS()
class SNOWFALL_API ASnowfallCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Instanced)
	UWeaponBase* activeWeapon;
	UStaticMeshComponent* worldWeapon;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator headRot;
	
public:
	// Sets default values for this character's properties
	ASnowfallCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category="Snowfall Character")
	void UpdateHeadRot();

private:

	void MoveForward(float value);
	void MoveRight(float value);
	void Shoot();
	void Reload();
};
