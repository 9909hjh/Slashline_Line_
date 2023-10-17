// Fill out your copyright notice in the Description page of Project Settings.


#include "EnemyBotCharacter.h"

#include "ApproachEnemyAIController.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "../Player/KatanaCharacter.h"
#include "MyProjectile.h"
#include "Engine/World.h"
#include "GameFramework/CharacterMovementComponent.h" 

AEnemyBotCharacter::AEnemyBotCharacter(const FObjectInitializer& ObjectInitializer) : EnemyAttack(0), currentRate(0), FireRate(0)
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void AEnemyBotCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AKatanaCharacter* player = Cast<AKatanaCharacter>(OtherActor);
	if (player != nullptr)
	{
		
		if (OtherActor->IsA(AKatanaCharacter::StaticClass()))
		{
			//카타나 캐릭터가에 부딛히면 데미지를 주게함.
			UGameplayStatics::ApplyDamage(OtherActor, EnemyAttack, nullptr, this, nullptr);
		}
	}
}

void AEnemyBotCharacter::Tick(float second)
{
	currentRate -= second;
}

int AEnemyBotCharacter::Enemy_Attack_Implementation()
{
	if (currentRate <= 0.0f)
	{
		currentRate = FireRate;
		if (montage && IsAAttack == true)
		{
			PlayAnimMontage(montage);

			if (BotName == "NinZa" && MyBullet)
			{
				FVector start = GetActorLocation();
				FVector end = UGameplayStatics::GetPlayerCharacter(this, 0)->GetActorLocation();

				const FRotator SpawnRotaion = UKismetMathLibrary::FindLookAtRotation(start, end);
				const FVector SpawnLocation = GetActorLocation() + SpawnRotaion.RotateVector(FVector::ZeroVector);

				UWorld* const World = GetWorld();
				if (World != NULL)
				{
					World->SpawnActor<AMyProjectile>(MyBullet, SpawnLocation, SpawnRotaion); // 스폰 위치!
				}
			}
		}
	}
	

	return 0;
}

UAnimMontage* AEnemyBotCharacter::get_montage() const
{
	return montage;
}