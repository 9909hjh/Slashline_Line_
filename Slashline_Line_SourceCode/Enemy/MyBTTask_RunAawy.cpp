// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_RunAawy.h"

#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "NavigationSystem.h"
#include "ApproachEnemyAIController.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBotCharacter.h"
#include "BlackBoardKeys.h"

UMyBTTask_RunAawy::UMyBTTask_RunAawy(FObjectInitializer const& object_inItializer)
{
	NodeName = TEXT("Find RunAway");
}

EBTNodeResult::Type UMyBTTask_RunAawy::ExecuteTask(UBehaviorTreeComponent& owner_Comp, uint8* NodeMemory)
{
	AApproachEnemyAIController* cont = Cast<AApproachEnemyAIController>(owner_Comp.GetAIOwner());
	AEnemyBotCharacter* npcBot = Cast<AEnemyBotCharacter>(cont->GetPawn());

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (npcBot->GetDistanceTo(player) <= RunAway_range)
	{
		FVector away = npcBot->GetActorForwardVector() * (-RunAway_Amound) + npcBot->GetActorLocation();

		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, away);
	}

	FinishLatentTask(owner_Comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
