// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "EnemyBotCharacter.h"
#include "MyBTTask_ChasePlayer.generated.h"

/**
 * 
 */
UCLASS()
class SLASHLINE_API UMyBTTask_ChasePlayer : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_ChasePlayer(FObjectInitializer const& object_Initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* Node_Memory)override;
};
