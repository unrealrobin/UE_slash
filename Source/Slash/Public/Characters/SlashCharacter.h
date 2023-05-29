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


	//Input Setup
	UPROPERTY(EditAnywhere, Category = Input)
	UInputMappingContext* SlashMappingContext;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* Moving;


	//IA Callback
	void Move(const FInputActionValue& Value);

	//Camera
	UPROPERTY(EditAnywhere, Category = Camera)
	UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, Category = Camera)
	USpringArmComponent* SpringArm;
};
