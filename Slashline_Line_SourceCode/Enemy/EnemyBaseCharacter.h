// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyBaseCharacter.generated.h"

/**
 * 20181289 한주형
 * 몬스터 베이스 클래스 입니다. 이 클래스가 EnemyBot의 부모 클래스가 되며 기본적인 채력, 데미지 받기, 이팩트, 죽는 애니메이션의 기능이 들어있습니다.
 * 이팩트 같은 경우 기획자가 추가할 수 있도록 BP에서 수정할 수 있도록 기능을 빼놓았습니다.
 * 또한 EnemyDieAnim()가 실행되면 애니메이션이 작동할 수 있도록 했습니다.
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

	//펑션으로 이벤트 블프로 만들어서 이펙트 적용시키자.
	UFUNCTION(BlueprintImplementableEvent)
		void BloodEffect();

	UFUNCTION(BlueprintImplementableEvent)
		void DieBloodEffect();

	//몬스터 사망시.
	void EnemyDie();

	//BP에서 이벤트로 연결
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
