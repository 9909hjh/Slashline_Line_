// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "Runtime/Core/Public/UObject/NameTypes.h"
#include "Runtime/Core/Public/Containers/UnrealString.h"

/**
 * 20181289 한주형
 * 블랙보드에 사용되는 변수들을 선언.
 */

namespace bb_keys
{
	TCHAR const* const target_location = TEXT("TargetLocation");
	TCHAR const* const can_see_player = TEXT("CanSeePlayer");
	TCHAR const* const player_is_in_AttackRange = TEXT("IsPlayerInAttackRange");
	TCHAR const* const enemy_die = TEXT("IsEnemyDie");
}
