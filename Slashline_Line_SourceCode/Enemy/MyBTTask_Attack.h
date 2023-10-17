// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "EnemyBotCharacter.h"
#include "MyBTTask_Attack.generated.h"

/**
 * 
 */
UCLASS()
class SLASHLINE_API UMyBTTask_Attack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_Attack(FObjectInitializer const& object_Initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* Node_Memory)override;

private:
	bool MontageHasFinished(AEnemyBotCharacter* const npcBot);
	
};
