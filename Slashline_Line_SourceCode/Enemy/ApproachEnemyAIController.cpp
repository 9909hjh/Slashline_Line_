// Fill out your copyright notice in the Description page of Project Settings.


#include "ApproachEnemyAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"

#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"

#include "UObject/ConstructorHelpers.h"
#include "EngineGlobals.h"
#include "../Player/KatanaCharacter.h" // 다른 폴더의 헤더 경로 찾는 방법
#include "EnemyBotCharacter.h"
#include "Kismet/KismetMathLibrary.h"

#include "BlackBoardKeys.h"

AApproachEnemyAIController::AApproachEnemyAIController(FObjectInitializer const& object_intializer) : Super(object_intializer), AISightRadius(1000), AISightAge(5), AILoseSightRadius(100)
{
	PrimaryActorTick.bCanEverTick = true;

	behavior_tree_Comp = object_intializer.CreateDefaultSubobject<UBehaviorTreeComponent>(this, TEXT("BehaviorComp"));
	BlackboardComp = object_intializer.CreateDefaultSubobject<UBlackboardComponent>(this, TEXT("BlackboardComp"));

	setup_perception_system();
}

void AApproachEnemyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AApproachEnemyAIController::OnPossess(APawn* pawn)
{
	Super::OnPossess(pawn);

	AEnemyBotCharacter* Bot = Cast<AEnemyBotCharacter>(pawn);
	if (Bot && Bot->BotBehavior)
	{
		if (Bot->BotBehavior->BlackboardAsset)
		{
			Blackboard->InitializeBlackboard(*Bot->BotBehavior->BlackboardAsset);
		}

		behavior_tree_Comp->StartTree(*(Bot->BotBehavior));
	}
}

void AApproachEnemyAIController::Tick(float DeltSeconds)
{
	Super::Tick(DeltSeconds);
}

UBlackboardComponent* AApproachEnemyAIController::get_blackboard() const
{
	return BlackboardComp;
}

void AApproachEnemyAIController::on_target_detected(AActor* actor, FAIStimulus const stimulus)
{
	
	if (auto const player = Cast<AKatanaCharacter>(actor)) // 죽지 않았다면을 추가.
	{
		//성공적으로 감지하면 블랙보드에 true값을 넣어준다.
		//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, "Find Player!!");
		//IsPlayerDetected = true;
		get_blackboard()->SetValueAsBool(bb_keys::can_see_player, stimulus.WasSuccessfullySensed());
	}
}

FRotator AApproachEnemyAIController::GetControlRotation() const
{
	if (GetPawn() == nullptr)
	{
		return FRotator(0.f, 0.f, 0.f);
	}

	return FRotator(0.f, GetPawn()->GetActorRotation().Yaw, 0.0f);
}

void AApproachEnemyAIController::setup_perception_system()
{
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius + SightConfig->SightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AApproachEnemyAIController::on_target_detected);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
}
