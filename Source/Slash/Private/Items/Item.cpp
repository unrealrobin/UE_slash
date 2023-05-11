#include "Items/Item.h"
#include "DrawDebugHelpers.h"
#include "Slash/DebugMacros.h"



AItem::AItem()
{
	PrimaryActorTick.bCanEverTick = true;
}


void AItem::BeginPlay()
{
	Super::BeginPlay();
		
	
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Movement Rate in Units of CM/Sec
	float MovementRate = 50.f;
	float RotationRate = 45.f;
	//MovementRate * DeltaTime (cm/s * s/frame) = cm/frame
	AddActorWorldOffset(FVector(MovementRate * DeltaTime, 0.f, 0.f));
	AddActorWorldRotation(FRotator(0.f, RotationRate * DeltaTime, 0.f));
	DRAW_SPHERE_SINGLE_FRAME(GetActorLocation());
	DRAW_VECTOR_SINGLE_FRAME(GetActorLocation(), GetActorLocation() + GetActorForwardVector() * 100.f);
	
}
