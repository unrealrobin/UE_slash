// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputActionValue.h"
#include "GameFramework/Pawn.h"
#include "Bird.generated.h"

//Forward Declared Classes, so .h Files can be included in .cpp
class UCapsuleComponent;
class USkeletalMeshComponent;
class UInputAction;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class SLASH_API ABird : public APawn
{
	GENERATED_BODY()

public:
	
	ABird();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
protected:
	
	virtual void BeginPlay() override;

	//Define a Single Context for our Input Map
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	class UInputMappingContext* BirdMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
	UInputAction* LookAction;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	
private:
	
	UPROPERTY(VisibleAnywhere)
	UCapsuleComponent* TheCapsule;
	
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USpringArmComponent* SpringArm;
};
