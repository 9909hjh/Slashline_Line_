// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "MyBTTask_RunAawy.generated.h"

/**
 * 
 */
UCLASS()
class SLASHLINE_API UMyBTTask_RunAawy : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

public:
	UMyBTTask_RunAawy(FObjectInitializer const& object_inItializer);
	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_Comp, uint8* NodeMemory)override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float RunAway_range = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float RunAway_Amound = 500.0f;
};
