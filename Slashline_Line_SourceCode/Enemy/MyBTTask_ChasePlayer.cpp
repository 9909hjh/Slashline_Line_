// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_ChasePlayer.h"
#include "ApproachEnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "BlackBoardKeys.h"

UMyBTTask_ChasePlayer::UMyBTTask_ChasePlayer(FObjectInitializer const& object_Initializer)
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UMyBTTask_ChasePlayer::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* Node_Memory)
{
	AApproachEnemyAIController* const cont = Cast<AApproachEnemyAIController>(ownerComp.GetAIOwner());
	FVector const player_location = cont->get_blackboard()->GetValueAsVector(bb_keys::target_location);

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(cont, player_location);

	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
