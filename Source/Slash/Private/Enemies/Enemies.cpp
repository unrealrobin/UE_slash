// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemies/Enemies.h"
#include "Components/CapsuleComponent.h"
#include "Slash/DebugMacros.h"

// Sets default values
AEnemies::AEnemies()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Setting Collisions for Enemy Mesh
	GetMesh()->SetCollisionObjectType(ECC_WorldDynamic);
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);
	GetMesh()->SetGenerateOverlapEvents(true);

	//Ignoring the Camera for Collisions for the capsule
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

}

// Called when the game starts or when spawned
void AEnemies::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemies::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemies::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemies::GetHit(const FVector& ImpactPoint)
{
	DRAW_DEBUG(ImpactPoint);
	UE_LOG(LogTemp, Warning, TEXT("Get Hit Fired"));
	PlayHitReactMontage(FName("ReactRight"));
}

void AEnemies::PlayHitReactMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(HitReactMontage);
	AnimInstance->Montage_JumpToSection(SectionName, HitReactMontage);
}


