// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Character.h"
#include "SlashCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UEnhancedInputComponent;
class UInputMappingContext;
class UInputAction;
class UGroomComponent;

UCLASS()
class SLASH_API ASlashCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASlashCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;


	//Input Action Setup
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* SlashMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* Moving;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* JumpAction;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* LookingAction;

	//IA Callback
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);

	//Camera
	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;

	//Hair
	UPROPERTY(EditAnywhere, Category = Hair)
	UGroomComponent* Hair;
	UPROPERTY(EditAnywhere, Category = Hair)
	UGroomComponent* Eyebrows;
};
