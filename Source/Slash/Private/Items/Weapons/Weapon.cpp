// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/Weapons/Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Slash/Public/Interface/IHitInterface.h"



AWeapon::AWeapon()
{
	//Creating the Collision Box for the Weapon.
	WeaponBox = CreateDefaultSubobject<UBoxComponent>(FName("Weapon Box"));
	WeaponBox->SetupAttachment(RootComponent);
	WeaponBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//Setting Collision Channels for The Weapon Box
	WeaponBox->SetCollisionResponseToAllChannels(ECR_Overlap);
	WeaponBox->SetCollisionResponseToChannel(ECC_Pawn,ECR_Ignore);
	//Start and End of Weapon Box Trace
	BoxStart = CreateDefaultSubobject<USceneComponent>("Box Start");
	BoxStart->SetupAttachment(RootComponent);
	BoxEnd = CreateDefaultSubobject<USceneComponent>("Box End");
	BoxEnd -> SetupAttachment(RootComponent);
}

void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	WeaponBox->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::OnWeaponBoxOverlap);
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

	if(EquipSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), EquipSound, GetActorLocation(),GetActorRotation());
	}
	
	AttachWeaponToSocket(InParent, InSocketName);
}

void AWeapon::OnWeaponBoxOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	FVector StartLocation = BoxStart->GetComponentLocation();
	FVector EndLocation = BoxEnd->GetComponentLocation();

	//will store the OutHit information
	FHitResult OutHit;

	//Will be populated to ignore double hits
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);
	
	UKismetSystemLibrary::BoxTraceSingle(this,
		StartLocation,
		EndLocation,
		FVector(8.0f, 4.4f, 30.0f),
		GetActorRotation(),
		TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHit,
		true);

	if(OutHit.GetActor())
	{
		//checking if the hit actor inherits from the HitInterface
		IIHitInterface* HitInterface = Cast<IIHitInterface>(OutHit.GetActor());
		if(HitInterface)
		{
			HitInterface->GetHit(OutHit.ImpactPoint);
		}
	}
	
	
}



