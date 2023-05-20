// Fill out your copyright notice in the Description page of Project Settings.


#include "Bird.h"

#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ABird::ABird()
{
 	
	PrimaryActorTick.bCanEverTick = true;
	
	TheCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	TheCapsule->SetCapsuleRadius(15.f);
	TheCapsule->SetCapsuleHalfHeight(20.f);
	SetRootComponent(TheCapsule);
	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("BirdSkeletalMeshComponent"));
	Mesh->SetupAttachment(GetRootComponent());
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 50.f;
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	
}


void ABird::BeginPlay()
{
	Super::BeginPlay();

	
	if(const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
		if(Subsystem)
		{
			//Applying our specific BirdMappingContext to this Subsystem
			Subsystem->AddMappingContext(BirdMappingContext, 0);
		}
	}
}

void ABird::Move(const FInputActionValue& Value)
{
	const float DirectionValue = Value.Get<float>();
	if(DirectionValue && (DirectionValue != 0.f))
	{
		const FVector Forward = GetActorForwardVector();
		AddMovementInput(Forward, DirectionValue);
		
	}
}

void ABird::Look(const FInputActionValue& Value)
{
	const FVector2d CurrentValue = Value.Get<FVector2d>();
	if(CurrentValue.X && CurrentValue.Y)
	{
		AddControllerPitchInput(CurrentValue.Y);
		AddControllerYawInput(CurrentValue.X);
	}
}


void ABird::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABird::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//Binding Enhanced Input Action
	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ABird::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ABird::Look);
	};

}

