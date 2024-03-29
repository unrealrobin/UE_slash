// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

class USphereComponent;

UENUM(BlueprintType)
enum class EItemState: uint8
{
	EIS_Equipped UMETA(DisplayName = "Equipped"),
	EIS_Hovering UMETA(DisplayName = "Hovering"),
	
};
UCLASS()
class SLASH_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	AItem();
	virtual void Tick(float DeltaTime) override;
	
protected:

	EItemState ItemState = EItemState::EIS_Hovering;
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	UStaticMeshComponent* ItemMesh;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float Amplitude{0.25f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float TimeConstant{5.f};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sine Parameters")
	float RotationPerTick{5.f};

	UFUNCTION(BlueprintPure)
	float TransformSin();

	UFUNCTION(BlueprintPure)
	float TransformCos();

	template<typename T>
	T Avg(T First, T Second);

	UPROPERTY(VisibleAnywhere)
	USphereComponent* Sphere;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult);

	UFUNCTION()
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float RunningTime;
};

//Template function for Avg (Types dont matter, as long as math operations work with them)
template <typename T>
inline T AItem::Avg(T First, T Second)
{
	return (First + Second) / 2;
}
