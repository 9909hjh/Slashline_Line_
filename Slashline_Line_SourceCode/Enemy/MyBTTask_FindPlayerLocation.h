// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "UObject/UObjectGlobals.h"
#include "MyBTTask_FindPlayerLocation.generated.h"


/**
 * 20181289 한주형 BT부분 코드 플레이어를 찾는 역할을 담당합니다.
 */
UCLASS()
class SLASHLINE_API UMyBTTask_FindPlayerLocation : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UMyBTTask_FindPlayerLocation(FObjectInitializer const& object_Initializer);

	EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* Node_Memory)override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess = "true"))
		bool search_random = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Search", meta = (AllowProtectedAccess = "true"))
		float search_radius = 150.0f;

};
