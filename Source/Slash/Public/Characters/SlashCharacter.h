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
class AItem;

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
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* Equip;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* Attack;
	UPROPERTY(EditAnywhere, Category = Input)
	UInputAction* Dodge;

	//IA Callback
	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void DoAttack();
	void DoDodge();
	void DoEquip();

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

private:
	//Items
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappedItem;

public:
	//Getters
	FORCEINLINE AItem* GetOverlappingItem() const {return OverlappedItem;}

	//Setters
	FORCEINLINE void SetOverlappingItem(AItem* Item) {OverlappedItem = Item;}
	
};
