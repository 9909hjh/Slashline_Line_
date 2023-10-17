// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBaseCharacter.h"

// Sets default values
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"

#include "ApproachEnemyAIController.h"
#include "GameFramework/DefaultPawn.h"

// ���� ���� �ڵ�
#include "../LevelScript/KatanaGameLevelScriptActor.h" // �����κ�

AEnemyBaseCharacter::AEnemyBaseCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input...	
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // ...at this rotation rate
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;
}

void AEnemyBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	//���� �ڵ�
	AKatanaGameLevelScriptActor* KatanaLevel2 = Cast<AKatanaGameLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (KatanaLevel2 != nullptr)
	{
		KatanaLevel2->OnEnemySpawned();
	}
}

void AEnemyBaseCharacter::EnemyDie()
{
	//���� �ڵ�
	AKatanaGameLevelScriptActor* KatanaLevel = Cast<AKatanaGameLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (KatanaLevel != nullptr)
	{
		KatanaLevel->OnEnemyDied();
	}

	//��Ʈ�ѷ� ����κ�
	if (Controller != NULL)
	{
		Controller->UnPossess();
	}

}

float AEnemyBaseCharacter::TakeDamage(float Damage, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (EnemyHealth <= 0.0f)
	{
		return 0.0f;
	}

	const float myGetDamage = Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);

	if (myGetDamage > 0.f)
	{
		BloodEffect(); // ����Ʈ
		EnemyHealth -= myGetDamage;
	}


	if (EnemyHealth <= 0.0f)
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("HP is : Die"));
		DieBloodEffect(); // ����Ʈ
		EnemyDieAnim(); // BP���� ����
		EnemyDie();
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("HP is : %f"), EnemyHealth));
	}

	return myGetDamage;
}


void AEnemyBaseCharacter::MoveForward(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void AEnemyBaseCharacter::MoveRight(float Value)
{
	if ((Controller != nullptr) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get right vector 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		// add movement in that direction
		AddMovementInput(Direction, Value);
	}
}