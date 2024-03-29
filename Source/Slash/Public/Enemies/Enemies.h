// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Interface/IHitInterface.h"
#include "Enemies.generated.h"

class UAnimMontage;

UCLASS()
class SLASH_API AEnemies : public ACharacter, public IIHitInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemies();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GetHit(const FVector& ImpactPoint) override;

	void PlayHitReactMontage(FName SectionName);

private:
	UPROPERTY(EditAnywhere, Category = "Enemy Montages")
	UAnimMontage* HitReactMontage;

};
