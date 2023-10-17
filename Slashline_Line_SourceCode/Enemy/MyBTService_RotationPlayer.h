// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "MyBTService_RotationPlayer.generated.h"

/**
 * 2018129 ÇÑÁÖÇü : Look at player Node
 */
UCLASS()
class SLASHLINE_API UMyBTService_RotationPlayer : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:
	UMyBTService_RotationPlayer();
	void OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)override;

};
