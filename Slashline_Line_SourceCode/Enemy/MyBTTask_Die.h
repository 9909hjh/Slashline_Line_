// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "MyBTTask_Die.generated.h"

/**
 * 
 */
UCLASS()
class SLASHLINE_API UMyBTTask_Die : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTTask_Die(FObjectInitializer const& object_Initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* Node_Memory)override;
};
