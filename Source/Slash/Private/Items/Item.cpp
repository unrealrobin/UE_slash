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

	UWorld* World = GetWorld();
	FVector Location = GetActorLocation();
	FVector Forward = GetActorForwardVector();
	FString HexColor = TEXT("#e3f542");
	//DRAW_SPHERE(Location);
	//DrawDebugSphere(World, Location, 30.f, 24, FColor::FromHex(FString(HexColor)), true );
	//DRAW_SPHERE_COLOR(Location, HexColor);
	/*DRAW_LINE(Location, Location + Forward * 100);
	DRAW_POINT(Location + Forward * 100);*/
	DRAW_VECTOR(Location, Location + Forward * 100);
	//DrawDebugBox(World, Location, FVector(10,10,10), FColor::FromHex(FString(HexColor)), true, -1.f, 0, 4.f );
	//DRAW_BOX(Location);
		
	
}


void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
