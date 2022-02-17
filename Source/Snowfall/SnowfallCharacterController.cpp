// Fill out your copyright notice in the Description page of Project Settings.


#include "SnowfallCharacterController.h"

void ASnowfallCharacterController::BeginPlay()
{
	Super::BeginPlay();

	ControlledCharacter = Cast<ASnowfallCharacter>(GetPawn());
}

void ASnowfallCharacterController::BeginPlayingState()
{
	Super::BeginPlayingState();
	/*
		ControlledCharacter = Cast<ASnowfallCharacter>(GetCharacter());
		ActiveWeapon = ControlledCharacter->ActiveWeapon;
	*/
}

void ASnowfallCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*if (ActiveWeapon)
	{
		GEngine->AddOnScreenDebugMessage(1, 1.0f, FColor::Green, ActiveWeapon->Name.ToString());
		GEngine->AddOnScreenDebugMessage(2, 1.0f, FColor::Green, FString::FromInt(ActiveWeapon->GetCurrentMagazine()).Append(ActiveWeapon->IsRoundInChamber() ? "+1" : ""));
	}*/
}

void ASnowfallCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ASnowfallCharacterController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ASnowfallCharacterController::MoveRight);
	InputComponent->BindAxis("LookUp", this, &ASnowfallCharacterController::LookUp);
	InputComponent->BindAxis("Turn", this, &ASnowfallCharacterController::Turn);
	InputComponent->BindAction("Jump", IE_Pressed, this, &ASnowfallCharacterController::Jump);
	InputComponent->BindAction("Fire1", IE_Pressed, this, &ASnowfallCharacterController::Fire1);
	InputComponent->BindAction("Reload", IE_Pressed, this, &ASnowfallCharacterController::Reload);
	InputComponent->BindAction("Interact", IE_Pressed, this, &ASnowfallCharacterController::Interact);
}

void ASnowfallCharacterController::Turn(float Rate)
{
	ControlledCharacter->Turn(Rate);
}

void ASnowfallCharacterController::LookUp(float Rate)
{
	ControlledCharacter->LookUp(Rate);
}

void ASnowfallCharacterController::MoveForward(float Value)
{
	ControlledCharacter->MoveForward(Value);
}

void ASnowfallCharacterController::MoveRight(float Value)
{
	ControlledCharacter->MoveRight(Value);
}

void ASnowfallCharacterController::Jump()
{
	ControlledCharacter->Jump();
}

void ASnowfallCharacterController::Fire1()
{
	ControlledCharacter->Fire1();
}

void ASnowfallCharacterController::Reload()
{
	ControlledCharacter->Reload();
}

void ASnowfallCharacterController::Interact()
{
	ControlledCharacter->Interact();
}