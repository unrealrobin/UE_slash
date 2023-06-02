// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "SlashAnimInstance.generated.h"


class ASlashCharacter;
class UCharacterMovementComponent;
/**
 * 
 */
UCLASS()
class SLASH_API USlashAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	//Anim BP BeginPlay
	virtual void NativeInitializeAnimation() override;
	//Anim BP Tick
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	
	UPROPERTY(BlueprintReadOnly)
	ASlashCharacter* SlashCharacter;
	
	UPROPERTY(BlueprintReadOnly, Category = Movement)
	UCharacterMovementComponent* SlashCharacterMovementComponent;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	float GroundSpeed;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	bool IsFalling;
};
