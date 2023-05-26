// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashEcho.h"

// Sets default values
ASlashEcho::ASlashEcho()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASlashEcho::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASlashEcho::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASlashEcho::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

