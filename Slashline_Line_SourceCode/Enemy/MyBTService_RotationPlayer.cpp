// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTService_RotationPlayer.h"
#include "EnemyBotCharacter.h"
#include "ApproachEnemyAIController.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BlackBoardKeys.h"
#include "../Player/KatanaCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"

UMyBTService_RotationPlayer::UMyBTService_RotationPlayer()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("RotationPlayer");
}

void UMyBTService_RotationPlayer::OnBecomeRelevant(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	Super::OnBecomeRelevant(owner_comp, node_memory);

	AApproachEnemyAIController* cont = Cast<AApproachEnemyAIController>(owner_comp.GetAIOwner());
	AEnemyBotCharacter* npcBot = Cast<AEnemyBotCharacter>(cont->GetPawn());

	ACharacter* player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);

	FVector start = npcBot->GetActorLocation();
	FVector end = player->GetActorLocation();

	const FRotator RotationToPlayer = UKismetMathLibrary::FindLookAtRotation(start, end);

	npcBot->SetActorRotation(FRotator(0, RotationToPlayer.Yaw, 0));
}
