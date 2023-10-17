// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class SLASHLINE_API AMyProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyProjectile();

	UPROPERTY(EditDefaultsOnly, Category = "State")
		float myInitialSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "State")
		float myMaxSpeed;

	UPROPERTY(EditDefaultsOnly, Category = "State")
		float Damage;

	UPROPERTY(EditDefaultsOnly, Category = "State")
		FName ProjectileName;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		class USphereComponent* CollisionComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "State")
		class UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnHit(AActor* UClothingSimulationInteractor, UPrimitiveComponent* OtherComp, FVector NomalImpulse, const FHitResult& Hit);

	FORCEINLINE class USphereComponent* GetProjectileCollision()const { return CollisionComp; }
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement()const { return ProjectileMovement; }

};
