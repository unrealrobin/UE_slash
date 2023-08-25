// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterTypes.h"
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
class UAnimMontage;
class AWeapon;

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
	void PlayAttackMontage() const;
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

	//Montages
	UFUNCTION(BlueprintCallable)
	void AttackEnd();
	
	bool CanAttack() const;
	bool CanArm();
	bool CanDisarm();

	UFUNCTION(BlueprintCallable)
	void Disarm();

	UFUNCTION(BlueprintCallable)
	void Arm();

	UFUNCTION(BlueprintCallable)
	void FinishedEquipping();

	//Attack Collisions
	UFUNCTION(BlueprintCallable)
	void SetWeaponEnableCollision(ECollisionEnabled::Type CollisionType);


private:
	//Items
	UPROPERTY(VisibleInstanceOnly)
	AItem* OverlappedItem;

	UPROPERTY(VisibleInstanceOnly)
	AWeapon* OverlappingWeapon;

	UPROPERTY(VisibleInstanceOnly)
	AWeapon* EquippedWeapon;

	UPROPERTY(VisibleInstanceOnly, Category = "Character States" )
	ECharacterState CharacterState = ECharacterState::ECS_Unequipped;

	//The only reason this is BlueprintReadWrite is because we are using a Notify and the ABP to control when to change the Action state back to UnOccupied
	UPROPERTY(BlueprintReadWrite,  meta=(AllowPrivateAccess = "true"), Category = "Character States" )
	EActionState ActionState = EActionState::EAS_UnOccupied;

	//Animation Montages
	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditDefaultsOnly, Category = Montages)
	UAnimMontage* SheathSword;

	void PlaySheathSwordMontage(FName SectionName);

	
public:
	//Getters
	FORCEINLINE AItem* GetOverlappingItem() const {return OverlappedItem;}
	FORCEINLINE ECharacterState GetCharacterState() const {return CharacterState;}

	//Setters
	FORCEINLINE void SetOverlappingItem(AItem* Item) {OverlappedItem = Item;}
	
};
