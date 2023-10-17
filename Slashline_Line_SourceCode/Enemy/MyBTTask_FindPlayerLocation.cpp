// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_FindPlayerLocation.h"
//#include "Slashline.h"
#include "ApproachEnemyAIController.h"
#include "BlackBoardKeys.h"

#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UMyBTTask_FindPlayerLocation::UMyBTTask_FindPlayerLocation(FObjectInitializer const& object_Initializer)
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UMyBTTask_FindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* Node_Memory)
{
	ACharacter* const player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	auto const cont = Cast<AApproachEnemyAIController>(ownerComp.GetAIOwner());
	FVector const player_location = player->GetActorLocation();

	if (search_random)
	{
		FNavLocation loc;

		UNavigationSystemV1* const nav_sys = UNavigationSystemV1::GetCurrent(GetWorld());
		if (nav_sys->GetRandomPointInNavigableRadius(player_location, search_radius, loc, nullptr))
		{
			cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, loc.Location);
		}
	}
	else
	{
		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, player_location);
	}

	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}