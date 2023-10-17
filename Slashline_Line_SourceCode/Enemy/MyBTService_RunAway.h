// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_RunAway.generated.h"

/**
 * 
 */
UCLASS()
class SLASHLINE_API UMyBTService_RunAway : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UMyBTService_RunAway();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		float RunAway_range = 300.0f;
};
