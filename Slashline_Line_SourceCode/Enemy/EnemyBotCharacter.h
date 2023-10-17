// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnemyBaseCharacter.h"
#include "Animation/AnimMontage.h"
#include "CombatInterface.h"
#include "EnemyBotCharacter.generated.h"

/**
 * 20181289 ������ �� ���̽� Ŭ������ �Ļ� Ŭ���� �Դϴ�.
 * �ش� ��ũ��Ʈ���� ���ݷ�, ���� �ӵ�, ���� ���� ����, ���� �ִϸ��̼��� ����ϴ� Ŭ���� �Դϴ�. Enemy_Attack_Implementation()�� BT�� ���� �������̽��� Ȱ���ؼ� ����մϴ�.
 * ���� ��Ƽ������ �̿��� ���� ���� �κ��� BP���� ������ �Ͽ����� ������� �ִ� �κ��� NotifyActorBeginOverlap()�� �̿��� CPP���� ó���Ͽ����ϴ�.
 * ���� �̿��� ������ ������� ĳ���Ͱ� �ƴ� ������ ������ �� �ֵ��� �߽��ϴ�.
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

	// AI���� �κ�
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
