#pragma once
#include "DrawDebugHelpers.h"
#include "GraphColor/Private/appconst.h"

//Macros
#define DRAW_SPHERE(Location) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::Blue, true);
#define DRAW_LINE(StartLocation, EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Cyan, true, -1.f, 0, 1);
#define DRAW_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(), Location, 15.f, FColor::Cyan, true);
#define DRAW_VECTOR(StartLocation, EndLocation) if(GetWorld()) \
	{ \
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Cyan, true, -1.f, 0, 1); \
		DrawDebugPoint(GetWorld(), EndLocation, 15.f, FColor::Cyan, true); \
	}
#define DRAW_SPHERE_COLOR(Location, HexColor) if(GetWorld()) DrawDebugSphere(GetWorld(), Location, 25.f, 12, FColor::FromHex(FString(HexColor)), true);
#define DRAW_BOX(Location) if(GetWorld()) \
	{ \
		DrawDebugBox(GetWorld(), Location, FVector(10,10,10), FColor::Red, true , -1.f, 0, 4.f); \
	}