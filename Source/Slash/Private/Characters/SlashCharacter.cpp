// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters\SlashCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ASlashCharacter::ASlashCharacter()
{

	PrimaryActorTick.bCanEverTick = true;


	

	//Camera Components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);
}


void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Creation of Enhanced Input Mapping Subsystem
	if(const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		
		if(UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			//Applying our specific SlashInputMappingContext to this Subsystem
			Subsystem->AddMappingContext(SlashMappingContext, 0);
		}
	}
	
}


void ASlashCharacter::Move(const FInputActionValue& Value)
{
	const FVector2d MovementVector = Value.Get<FVector2D>();
	
	const FVector Forward = GetActorForwardVector();
	AddMovementInput(Forward, MovementVector.X);

	const FVector Right = GetActorRightVector();
	AddMovementInput(Right, MovementVector.Y);
	
		
	
}


void ASlashCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ASlashCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Casting the Default PlayerInputComponent to the New Enhanced Input Component
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		//Binding our New Input Actions to their Callback Functions
		EnhancedInputComponent->BindAction(Moving, ETriggerEvent::Triggered, this, &ASlashCharacter::Move);
		
	}
}

