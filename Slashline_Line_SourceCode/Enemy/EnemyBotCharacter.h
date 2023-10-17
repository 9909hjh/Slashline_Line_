// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseCharacter.h"
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
#include "EnemyBotCharacter.generated.h"

/**
 * 20181289 한주형 적 베이스 클래스의 파생 클래스 입니다.
 * 해당 스크립트에서 공격력, 공격 속도, 블랫의 생성 여부, 공격 애니메이션을 담당하는 클래스 입니다. Enemy_Attack_Implementation()는 BT를 위해 인터페이스를 활용해서 사용합니다.
 * 또한 노티파이을 이용한 공격 로직 부분은 BP에서 구현을 하였으며 대미지를 주는 부분은 NotifyActorBeginOverlap()을 이용해 CPP에서 처리하였습니다.
 * 블랫을 이용한 공격의 대미지는 캐릭터가 아닌 블랫에서 설정할 수 있도록 했습니다.
 */
UCLASS()
class SLASHLINE_API AEnemyBotCharacter : public AEnemyBaseCharacter, public ICombatInterface
{
	GENERATED_BODY()

public:
	AEnemyBotCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	virtual void Tick(float second) override;

	UPROPERTY(EditAnywhere, Category = "AI | Begavior")
		class UBehaviorTree* BotBehavior;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "AI | Attack")
		bool IsAAttack;

	/*ApproachEnemy Damage*/
	UPROPERTY(EditAnywhere, Category = "AI | Status") 
		float EnemyAttack;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI | Name&Bullet")
		TSubclassOf<class AMyProjectile> MyBullet;

	// AI공격 부분
	int Enemy_Attack_Implementation() override;

	UAnimMontage* get_montage() const;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | AttackMontage", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* montage;

	// projectile BotName == NinZa
	UPROPERTY(EditAnywhere, Category = "AI | Name&Bullet", meta = (AllowPrivateAccess = "true"))
		FName BotName;

	UPROPERTY(EditAnywhere, Category = "AI | Status", meta = (AllowPrivateAccess = "true"))
		float currentRate;

	UPROPERTY(EditAnywhere, Category = "AI | Status", meta = (AllowPrivateAccess = "true"))
		float FireRate;
};
