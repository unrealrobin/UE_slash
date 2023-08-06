#pragma once

//States for whether the Character has an Equipped Weapon and Type or not.
UENUM(BlueprintType)
enum class ECharacterState: uint8
{
	ECS_Unequipped UMETA(DisplayName = "Unequipped"),
	ECS_Equipped1H UMETA(DisplayName = "Equipped 1 Hand Weapon"),
	ECS_Equipped2H UMETA(DisplayName = "Equipped 2 Hand Weapon"),
};

//States for defining whether the Character is in an Attacking State or not.
UENUM(BlueprintType)
enum class EActionState: uint8
{
	EAS_Attacking UMETA(DisplayName = "Attacking"),
	EAS_UnOccupied UMETA(DisplayName = "UnOccupied"),
	EAS_EquippingWeapon UMETA(DisplayName = "EquippingWeapon"),
};
