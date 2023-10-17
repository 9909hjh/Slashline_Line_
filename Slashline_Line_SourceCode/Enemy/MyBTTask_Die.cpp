// Fill out your copyright notice in the Description page of Project Settings.

//�Ⱦ��� ��ũ��Ʈ
#include "MyBTTask_Die.h"
#include "ApproachEnemyAIController.h"
#include "BlackBoardKeys.h"

#include "EnemyBotCharacter.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Runtime/NavigationSystem/Public/NavigationSystem.h"
#include "NavigationSystem.h"
#include "Engine.h"
#include "Engine/World.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"

UMyBTTask_Die::UMyBTTask_Die(FObjectInitializer const& object_Initializer)
{
	NodeName = TEXT("IsDie");
}

EBTNodeResult::Type UMyBTTask_Die::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* Node_Memory)
{
	auto const cont = Cast<AApproachEnemyAIController>(ownerComp.GetAIOwner());
	AEnemyBotCharacter* const npcBot = Cast<AEnemyBotCharacter>(cont->GetPawn());

	cont->get_blackboard()->SetValueAsBool(bb_keys::enemy_die, npcBot->EnemyHealth <= 0.0f);
	//UAIBlueprintHelperLibrary::
	//cont->get_blackboard()->SetValueAsBool(bb_keys::player_is_in_AttackRange, npcBot->GetDistanceTo(player) <= Attack_range); //range���� �۰ų� ������

	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
