// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowfallMovementComponent.h"

#include "SnowfallCharacter.h"
#include "GameFramework/Character.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

USnowfallMovementComponent::USnowfallMovementComponent()
{
	SnowfallCharacter = Cast<ASnowfallCharacter>(GetOwner());

	// HL2 cl_(forward & side)speed = 450Hu
	MaxAcceleration = 857.25f;
	// Set the default walk speed
	MaxWalkSpeed = 361.9f;
	WalkSpeed = 285.75f;
	RunSpeed = 361.9f;
	SprintSpeed = 609.6f;

	// Start out braking
	bBrakingFrameTolerated = true;
}

void USnowfallMovementComponent::CalcVelocity(float DeltaTime, float Friction, bool bFluid, float BrakingDeceleration)
{
	if (!HasValidData() || HasAnimRootMotion() || DeltaTime < MIN_TICK_TIME || (CharacterOwner && CharacterOwner->GetLocalRole() == ROLE_SimulatedProxy && !bWasSimulatingRootMotion))
	{
		return;
	}

	Friction = FMath::Max(0.0f, Friction);
	const float MaxAccel = GetMaxAcceleration();
	float MaxSpeed = GetMaxSpeed();

	bool bZeroRequestedAcceleration = true;
	FVector RequestedAcceleration = FVector::ZeroVector;
	float RequestedSpeed = 0.0f;
	if (ApplyRequestedMove(DeltaTime, MaxAccel, MaxSpeed, Friction, BrakingDeceleration, RequestedAcceleration, RequestedSpeed))
	{
		RequestedAcceleration = RequestedAcceleration.GetClampedToMaxSize(MaxAccel);
		bZeroRequestedAcceleration = false;
	}

	if (bForceMaxAccel)
	{
		// If at full speed, force acceleration
		if (Acceleration.SizeSquared() > SMALL_NUMBER)
		{
			Acceleration = Acceleration.GetSafeNormal() * MaxAccel;
		}
		else
		{
			Acceleration = MaxAccel * (Velocity.SizeSquared() < SMALL_NUMBER ? UpdatedComponent->GetForwardVector() : Velocity.GetSafeNormal());
		}

		AnalogInputModifier = 1.0f;
	}

	// Path following above didn't care about the analog modifier, but we do for everything else below, so get the fully modified value.
	// Use max of requested speed and max speed if we modified the speed in ApplyRequestedMove above.
	const float MaxInputSpeed = FMath::Max(MaxSpeed * AnalogInputModifier, GetMinAnalogSpeed());
	MaxSpeed = FMath::Max(RequestedSpeed, MaxInputSpeed);

	// Apply braking or deceleration
	const bool bZeroAcceleration = Acceleration.IsNearlyZero();
	const bool bIsGroundMove = IsMovingOnGround() && bBrakingFrameTolerated;

	float SurfaceFriction = 1.0f;
	UPhysicalMaterial* PhysMat = CurrentFloor.HitResult.PhysMaterial.Get();
	if (PhysMat)
	{
		SurfaceFriction = FMath::Min(1.0f, PhysMat->Friction * 1.25f);
	}

	// Apply friction
	if (bIsGroundMove && !bAppliedFriction)
	{
		const float ActualBrakingFriction = (bUseSeparateBrakingFriction ? BrakingFriction : Friction) * SurfaceFriction;
		ApplyVelocityBraking(DeltaTime, ActualBrakingFriction, BrakingDeceleration);
		bAppliedFriction = true;
	}

	if (!bZeroAcceleration)
	{
		Acceleration = Acceleration.GetClampedToMaxSize2D(MaxSpeed);
		// Find veer
		const FVector AccelDir = Acceleration.GetSafeNormal();
		const float Veer = Velocity.X * AccelDir.X + Velocity.Y * AccelDir.Y;
		//  Get add speed
		const float AddSpeed = Acceleration.Size2D() - Veer;
		if (AddSpeed > 0.0f)
		{
			float AccelerationMultiplier = bIsGroundMove ? GroundAccelMultiplier : AirAccelMultiplier;
			Acceleration *= AccelerationMultiplier * SurfaceFriction * DeltaTime;
			Acceleration = Acceleration.GetClampedToMaxSize2D(AddSpeed);
			Velocity += Acceleration;
		}
	}

	if (!bZeroRequestedAcceleration)
	{
		Velocity += RequestedAcceleration * DeltaTime;
	}
}

void USnowfallMovementComponent::ApplyVelocityBraking(float DeltaTime, float Friction, float BrakingDeceleration)
{
	float Speed = Velocity.Size2D();
	if (Speed <= 0.1f || !HasValidData() || HasAnimRootMotion() || DeltaTime < MIN_TICK_TIME)
	{
		return;
	}

	const float FrictionFactor = FMath::Max(0.0f, BrakingFrictionFactor);
	Friction = FMath::Max(0.0f, Friction * FrictionFactor);
	BrakingDeceleration = FMath::Max(BrakingDeceleration, Speed);
	BrakingDeceleration = FMath::Max(0.0f, BrakingDeceleration);
	const bool bZeroFriction = FMath::IsNearlyZero(Friction);
	const bool bZeroBraking = BrakingDeceleration == 0.0f;

	if (bZeroFriction || bZeroBraking)
	{
		return;
	}

	const FVector OldVel = Velocity;

	// Decelerate to brake to a stop
	const FVector RevAccel = Friction * BrakingDeceleration * Velocity.GetSafeNormal();
	Velocity -= RevAccel * DeltaTime;

	// Don't reverse direction
	if ((Velocity | OldVel) <= 0.0f)
	{
		Velocity = FVector::ZeroVector;
		return;
	}

	// Clamp to zero if nearly zero, or if below minimum threshold and braking
	const float VSizeSq = Velocity.SizeSquared();
	if (VSizeSq <= KINDA_SMALL_NUMBER)
	{
		Velocity = FVector::ZeroVector;
	}
}

float USnowfallMovementComponent::GetMaxSpeed() const
{
	if (IsWalking() || IsFalling())
	{
		return WalkSpeed;
	}
	return Super::GetMaxSpeed();
}

void USnowfallMovementComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	bAppliedFriction = false;

	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	bBrakingFrameTolerated = IsMovingOnGround();
}
