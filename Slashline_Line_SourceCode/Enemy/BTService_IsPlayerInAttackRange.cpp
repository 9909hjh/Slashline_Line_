// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_IsPlayerInAttackRange.h"
#include "EnemyBotCharacter.h"
#include "ApproachEnemyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardKeys.h"
#include "../Player/KatanaCharacter.h"
#include "Kismet/GameplayStatics.h"

UBTService_IsPlayerInAttackRange::UBTService_IsPlayerInAttackRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Is Player in Attack Range");
}

void UBTService_IsPlayerInAttackRange::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	AApproachEnemyAIController* cont = Cast<AApproachEnemyAIController>(owner_comp.GetAIOwner());
	AEnemyBotCharacter* npcBot = Cast<AEnemyBotCharacter>(cont->GetPawn());

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	cont->get_blackboard()->SetValueAsBool(bb_keys::player_is_in_AttackRange, npcBot->GetDistanceTo(player) <= Attack_range); //range보다 작거나 같을때
	if (npcBot->GetDistanceTo(player) <= Attack_range) // Attack_range의 거리가 되면 공격하게 설정.
	{
		npcBot->IsAAttack = true;
	}
	else
	{
		npcBot->IsAAttack = false;
	}

}
