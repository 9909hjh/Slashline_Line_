// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "ApproachEnemyAIController.generated.h"

/**
 * 20181289 한주형
 * 몬스터 AI컨트롤러입니다. 비헤비어트리를 사용하여 몬스터의 움직임을 제어합니다. 
 * 따라서 이 함수는 BT, BTS와 연결되어 작동하는 클래스입니다.
 */
class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS(config = Game)
class SLASHLINE_API AApproachEnemyAIController : public AAIController
{
	GENERATED_BODY()

public:
	AApproachEnemyAIController(FObjectInitializer const& object_intializer = FObjectInitializer::Get());

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* pawn) override;
	virtual void Tick(float DeltSeconds) override;

	virtual FRotator GetControlRotation() const override;

	class UBlackboardComponent* get_blackboard() const;


	UFUNCTION(BlueprintCallable, Category = "Behavior")
		void on_target_detected(AActor* actor, FAIStimulus const stimulus);

	//===
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AImember")
		float AISightRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AImember")
		float AISightAge;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AImember")
		float AILoseSightRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AImember")
		float AIFieldOfView = 90.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AImember")
		class UAISenseConfig_Sight* SightConfig;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AImember")
		bool IsPlayerDetected;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AImember")
		float DistanceToPlayer;

private:
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AImember", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent* behavior_tree_Comp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AImember", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree* btree;

	class UBlackboardComponent* BlackboardComp;
	class UAISenseConfig_Sight* sight_config;

	void setup_perception_system();
	
};
