// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"

#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"

// Sets default values
ABird::ABird()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	UCapsuleComponent* BirdCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	BirdCapsule->SetCapsuleRadius(15.f);
	BirdCapsule->SetCapsuleHalfHeight(20.f);
	SetRootComponent(BirdCapsule);
	USkeletalMeshComponent* BirdMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdSkeletalMeshComponent"));
	BirdMesh -> SetupAttachment(GetRootComponent());
}


void ABird::BeginPlay()
{
	Super::BeginPlay();
	
}


void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

