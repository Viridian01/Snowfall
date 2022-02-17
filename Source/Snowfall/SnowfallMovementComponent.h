// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SnowfallMovementComponent.generated.h"

/**
 * Base Movement Component for Snowfall. Based on the Project Borealis Movement Component, PBMovementComponent.
 */
UCLASS()
class SNOWFALL_API USnowfallMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()
	
protected:

	// Is stepping left, otherwise, right
	bool StepSide;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float GroundAccelMultiplier;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Movement")
	float AirAccelMultiplier;

	bool bBrakingFrameTolerated;

	class ASnowfallCharacter* SnowfallCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	float RunSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	float SprintSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (ClampMin = "0", UIMin = "0"))
	float WalkSpeed;

	bool bAppliedFriction;

public:

	USnowfallMovementComponent();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	virtual void CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration) override;
	virtual void ApplyVelocityBraking(float DeltaTime, float Friction, float BrakingDeceleration) override;

	virtual float GetMaxSpeed() const override;

	// Acceleration
	FORCEINLINE FVector GetAcceleration() const
	{
		return Acceleration;
	}
};
