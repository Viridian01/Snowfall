// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SnowfallCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class SNOWFALL_API USnowfallCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FRotator controlRot;
	
};
