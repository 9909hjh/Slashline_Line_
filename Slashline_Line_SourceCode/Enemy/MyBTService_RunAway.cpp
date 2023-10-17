// Fill out your copyright notice in the Description page of Project Settings.

//안쓰는 스크립트
#include "MyBTService_RunAway.h"
#include "EnemyBotCharacter.h"
#include "ApproachEnemyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardKeys.h"
#include "../Player/KatanaCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

UMyBTService_RunAway::UMyBTService_RunAway()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("RunAwayRange");
}

void UMyBTService_RunAway::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	AApproachEnemyAIController* cont = Cast<AApproachEnemyAIController>(owner_comp.GetAIOwner());
	AEnemyBotCharacter* npcBot = Cast<AEnemyBotCharacter>(cont->GetPawn());

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	if (npcBot->GetDistanceTo(player) <= RunAway_range)
	{
		FVector away = npcBot->GetActorForwardVector() * (-500.0f) + npcBot->GetActorLocation();
		float Bot_X = npcBot->SetActorLocation(FVector(away.X, 0.0f, 0.0f));
		float Bot_Y = npcBot->SetActorLocation(FVector(0, away.Y, 0.0f));
		float Bot_Z = npcBot->SetActorLocation(FVector(0.0f, 0.0f, npcBot->GetActorLocation().Z));

		FVector FinAway = UKismetMathLibrary::MakeVector(Bot_X, Bot_Y, Bot_Z);

		cont->get_blackboard()->SetValueAsVector(bb_keys::target_location, FinAway);
	}
}
