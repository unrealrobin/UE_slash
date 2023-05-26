// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters\SlashCharacter.h"


ASlashEcho::ASlashEcho()
{

	PrimaryActorTick.bCanEverTick = true;

}


void ASlashEcho::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASlashEcho::Move(FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();
	if(DirectionValue && (DirectionValue != 0.f))
	{
		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, DirectionValue);
		
	}
}


void ASlashEcho::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASlashEcho::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
}

