// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBaseCharacter.generated.h"

/**
 * 20181289 ������
 * ���� ���̽� Ŭ���� �Դϴ�. �� Ŭ������ EnemyBot�� �θ� Ŭ������ �Ǹ� �⺻���� ä��, ������ �ޱ�, ����Ʈ, �״� �ִϸ��̼��� ����� ����ֽ��ϴ�.
 * ����Ʈ ���� ��� ��ȹ�ڰ� �߰��� �� �ֵ��� BP���� ������ �� �ֵ��� ����� �����ҽ��ϴ�.
 * ���� EnemyDieAnim()�� ����Ǹ� �ִϸ��̼��� �۵��� �� �ֵ��� �߽��ϴ�.
 */
UCLASS()
class SLASHLINE_API AEnemyBaseCharacter : public ACharacter
{
	GENERATED_BODY()
public:
	AEnemyBaseCharacter();

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, Category = "AI | Status")
		float EnemyHealth;

	UPROPERTY(EditAnywhere, Category = "AI | Status")
		float EnemyMaxHealth;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage_FX")
		UParticleSystem* GetHitFx;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Damage_FX")
		UParticleSystem* GetDieFx;

	//������� �̺�Ʈ ������ ���� ����Ʈ �����Ű��.
	UFUNCTION(BlueprintImplementableEvent)
		void BloodEffect();

	UFUNCTION(BlueprintImplementableEvent)
		void DieBloodEffect();

	//���� �����.
	void EnemyDie();

	//BP���� �̺�Ʈ�� ����
	UFUNCTION(BlueprintImplementableEvent)
		void EnemyDieAnim();

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI | Die", meta = (AllowPrivateAccess = "true"))
		UAnimMontage* Diemontage;

protected:

	/** Called for forwards/backward input */
	void MoveForward(float Value);

	/** Called for side to side input */
	void MoveRight(float Value);

	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)override;
};
