// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBTTask_Attack.h"
#include "ApproachEnemyAIController.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Engine/World.h"
#include "Engine/LatentActionManager.h"
#include "Components/SkeletalMeshComponent.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "AIController.h"
#include "EnemyBaseCharacter.h"
#include "EnemyBotCharacter.h"

UMyBTTask_Attack::UMyBTTask_Attack(FObjectInitializer const& object_Initializer)
{
	NodeName = TEXT("Short Dist Attack");
}

EBTNodeResult::Type UMyBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& ownerComp, uint8* Node_Memory)
{
	AAIController* const cont = ownerComp.GetAIOwner();
	AEnemyBotCharacter* const npcBot = Cast<AEnemyBotCharacter>(cont->GetPawn());
	if (ICombatInterface* const icombat = Cast<ICombatInterface>(npcBot))
	{
		if (MontageHasFinished(npcBot))
		{
			icombat->Execute_Enemy_Attack(npcBot);
		}
	}
	FinishLatentTask(ownerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

bool UMyBTTask_Attack::MontageHasFinished(AEnemyBotCharacter* const npcBot)
{
	return npcBot->GetMesh()->GetAnimInstance()->Montage_GetIsStopped(npcBot->get_montage());
}

