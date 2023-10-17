// Fill out your copyright notice in the Description page of Project Settings.


#include "MyProjectile.h"
#include "Components/SphereComponent.h"
#include "EnemyBaseCharacter.h"
#include "../Player/KatanaCharacter.h"
#include "Engine.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AMyProjectile::AMyProjectile() : Damage(10)
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f); //지름
	CollisionComp->SetCollisionProfileName("Bot_Projectile");
	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyProjectile::OnOverlapBegin);
	RootComponent = CollisionComp;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 200.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	InitialLifeSpan = 3.0f; // 스폰 시간.

}

void AMyProjectile::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && (OtherActor != this) && OtherComp)
	{
		if (OtherActor->IsA(AKatanaCharacter::StaticClass()))
		{
			//카타나 캐릭터가에 부딛히면 삭제하고 데미지를 주게 사용.
			UGameplayStatics::ApplyDamage(OtherActor, Damage, nullptr, this, nullptr);
			Destroy();
		}
	}
}

void AMyProjectile::OnHit(AActor* UClothingSimulationInteractor, UPrimitiveComponent* OtherComp, FVector NomalImpulse, const FHitResult& Hit)
{

}