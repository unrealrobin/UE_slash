// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/Item.h"
#include "Weapon.generated.h"

//For Weapon Box collisions
class UBoxComponent;
class USceneComponent;
/**
 * 
 */
UCLASS()
class SLASH_API AWeapon : public AItem
{
	GENERATED_BODY()

public:
	AWeapon();
	virtual void Tick(float DeltaTime) override;
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	void AttachWeaponToSocket(USceneComponent* InParent, FName InSocketName);
	void Equip(USceneComponent* InParent, FName InSocketName);
	
	UFUNCTION()
	void OnWeaponBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);
	
protected:
	virtual void BeginPlay() override;

	

private:
	UPROPERTY(EditAnywhere, Category = "Weapon Properties")
	class USoundBase* EquipSound;

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* WeaponBox;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxStart;
	
	UPROPERTY(VisibleAnywhere)
	USceneComponent* BoxEnd;

public:
	//Getters and Setters
	FORCEINLINE UBoxComponent* GetWeaponBox(){return WeaponBox;};
	
};
