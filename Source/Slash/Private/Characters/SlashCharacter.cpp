// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/SlashCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GroomComponent.h"
#include "Items/Weapons/Weapon.h"
#include "Animation/AnimMontage.h"
#include "Components/BoxComponent.h"

ASlashCharacter::ASlashCharacter()
{

	PrimaryActorTick.bCanEverTick = true;

	//Camera Components
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 300.f;
	Camera = CreateDefaultSubobject<UCameraComponent>(FName("Camera"));
	Camera->SetupAttachment(SpringArm);

	//Hair Components
	Hair = CreateDefaultSubobject<UGroomComponent>(FName("Hair"));
	Hair->SetupAttachment(GetMesh());
	Hair->AttachmentName = FString("head");
	Eyebrows = CreateDefaultSubobject<UGroomComponent>(FName("Eyebrows"));
	Eyebrows->SetupAttachment(GetMesh());
	Eyebrows->AttachmentName = FString("head");
	
}

void ASlashCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Creation of Enhanced Input Mapping Subsystem
	if(const APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem =
			ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(
				PlayerController->GetLocalPlayer()))
		{
			//Applying our specific SlashInputMappingContext to this Subsystem
			Subsystem->AddMappingContext(SlashMappingContext, 0);
		}
	}
	
}

void ASlashCharacter::Move(const FInputActionValue& Value)
{
	//if character is Attacking or Equipping Weapon
	if(ActionState != EActionState::EAS_UnOccupied)
	{
		return;
	}
	const FVector2d MovementVector = Value.Get<FVector2d>();
	const FRotator ControlRotation = GetControlRotation();
	const FRotator YawRotation(0.f, ControlRotation.Yaw, 0.f);
	
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(ForwardDirection, MovementVector.X);
	
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(RightDirection, MovementVector.Y);
	
}

void ASlashCharacter::Look(const FInputActionValue& Value)
{
	const FVector2d LookAxisVector = Value.Get<FVector2d>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ASlashCharacter::PlayAttackMontage() const
{
	//Plays the Montage at some Section
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if(AnimInstance && AttackMontage)
	{
		AnimInstance->Montage_Play(AttackMontage);
		int Selection = FMath::RandRange(0,0);
		FName SectionName = FName();
		switch (Selection)
		{
		case 0:
			SectionName = FName("Attack3");
			break;
		case 1:
			SectionName = FName("Attack2");
			break;
		default :
			SectionName = FName("Attack1");
		}
		AnimInstance->Montage_JumpToSection(SectionName, AttackMontage);
	}
}

void ASlashCharacter::DoAttack()
{
	//Attack Callback
	if(CanAttack())
	{
		ActionState = EActionState::EAS_Attacking;
		PlayAttackMontage();
		
	}
	
}

void ASlashCharacter::DoDodge()
{
}

void ASlashCharacter::DoEquip()
{
	
	//Picks up and Equips a weapon if there is no equipped weapon.
	if(EquippedWeapon == nullptr)
	{
		OverlappingWeapon = Cast<AWeapon>(OverlappedItem);
		if(OverlappingWeapon && CharacterState == ECharacterState::ECS_Unequipped)
		{
			CharacterState = ECharacterState::ECS_Equipped1H;
			OverlappingWeapon->Equip(GetMesh(), FName("RightHandSocket"));
			EquippedWeapon = OverlappingWeapon;
		};
	}
	else //if there is a weapon equipped, Arm or Disarm
	{
		if(CanDisarm())
		{
			ActionState = EActionState::EAS_EquippingWeapon;
			CharacterState = ECharacterState::ECS_Unequipped;
			PlaySheathSwordMontage(FName("Disarm"));
			
		}else if(CanArm())
		{
			ActionState = EActionState::EAS_EquippingWeapon;
			CharacterState = ECharacterState::ECS_Equipped1H;
			PlaySheathSwordMontage(FName("Arm"));
			
		}
	};
}

void ASlashCharacter::AttackEnd()
{
	ActionState = EActionState::EAS_UnOccupied;
}

bool ASlashCharacter::CanAttack() const
{
	if(CharacterState != ECharacterState::ECS_Unequipped && ActionState == EActionState::EAS_UnOccupied)
	{
		return true;
	}

	return false;
}

bool ASlashCharacter::CanArm()
{
	if(EquippedWeapon && CharacterState == ECharacterState::ECS_Unequipped)
	{
		return true;
	}
	return false;
}

bool ASlashCharacter::CanDisarm()
{
	if(EquippedWeapon && CharacterState != ECharacterState::ECS_Unequipped)
	{
		return true;
	}
	return false;
}

//gets called from Echo Animation Blue Print Nodes that are fired from Anim Notifys
void ASlashCharacter::Disarm()
{
	if(EquippedWeapon)
	{
		ActionState = EActionState::EAS_EquippingWeapon;
		EquippedWeapon->AttachWeaponToSocket(GetMesh(), FName("SpineSocket1"));
	}
}

//gets called from Echo Animation Blue Print Nodes that are fired from Anim Notifys
void ASlashCharacter::Arm()
{
	if(EquippedWeapon)
	{
		ActionState = EActionState::EAS_EquippingWeapon;
		EquippedWeapon->AttachWeaponToSocket(GetMesh(), FName("RightHandSocket"));
	}
}

//gets called from Echo Animation Blue Print Nodes that are fired from Anim Notifys
void ASlashCharacter::FinishedEquipping()
{
	ActionState = EActionState::EAS_UnOccupied;
}

void ASlashCharacter::SetWeaponEnableCollision(ECollisionEnabled::Type CollisionType)
{
	if(EquippedWeapon && EquippedWeapon->GetWeaponBox())
	{
		EquippedWeapon->GetWeaponBox()->SetCollisionEnabled(CollisionType);
	}
	
	
}

void ASlashCharacter::PlaySheathSwordMontage(FName SectionName)
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	AnimInstance->Montage_Play(SheathSword);
	AnimInstance->Montage_JumpToSection(SectionName, SheathSword);
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
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(LookingAction, ETriggerEvent::Triggered, this, &ASlashCharacter::Look);
		EnhancedInputComponent->BindAction(Attack, ETriggerEvent::Triggered, this, &ASlashCharacter::DoAttack);
		EnhancedInputComponent->BindAction(Equip, ETriggerEvent::Triggered, this, &ASlashCharacter::DoEquip);
		EnhancedInputComponent->BindAction(Dodge, ETriggerEvent::Triggered, this, &ASlashCharacter::DoDodge);
	}
}



