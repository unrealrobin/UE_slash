// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"

#include "Characters/SlashCharacter.h"

AWeapon::AWeapon()
{
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if(ItemState == EItemState::EIS_Hovering)
	{
		AddActorWorldOffset(FVector(0.f, 0.f, TransformSin()));
		AddActorWorldRotation(FRotator(0.0,RotationPerTick * DeltaTime, 0.0 ));
	}
}

void AWeapon::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnSphereOverlap(OverlappedComponent, OtherActor, OtherComp,
	                       OtherBodyIndex,
	                       bFromSweep, SweepResult);
	
	
}

void AWeapon::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnSphereEndOverlap(OverlappedComponent, OtherActor, OtherComp,
	                          OtherBodyIndex);
}

void AWeapon::AttachWeaponToSocket(USceneComponent* InParent, FName InSocketName)
{
	FAttachmentTransformRules TransformRules(EAttachmentRule::SnapToTarget, true);
	ItemMesh->AttachToComponent(InParent, TransformRules, InSocketName);
}


void AWeapon::Equip(USceneComponent* InParent, FName InSocketName)
{
	ItemState = EItemState::EIS_Equipped;
	
	AttachWeaponToSocket(InParent, InSocketName);
}



