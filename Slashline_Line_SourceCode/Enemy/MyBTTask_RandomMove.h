// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "GameFramework/Pawn.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "MyBTTask_RandomMove.generated.h"

/**
 * 
 */
UCLASS()
class SLASHLINE_API UMyBTTask_RandomMove : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTTask_RandomMove(FObjectInitializer const& object_inItializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_Comp, uint8* NodeMemory)override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowPrivateAccess = "true"));
	float search_radius = 1500.0f;
};
