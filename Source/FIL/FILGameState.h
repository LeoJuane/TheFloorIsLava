// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/GameStateBase.h"
#include "FILGameState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStarCollected, int32, CollectedStars);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnFILGameOver, bool, bPlayerWon);

UCLASS()
class FIL_API AFILGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	
	int32 AddCollectedStar();

	UFUNCTION(BlueprintCallable)
	int32 GetCollectedStars() const { return CollectedStars; }

	void NotifyGameOver(bool bInPlayerWon);

protected:

	UPROPERTY(BlueprintAssignable)
	FOnStarCollected OnStarCollected;

	UPROPERTY(BlueprintAssignable)
	FOnFILGameOver OnGameOver;

private:

	int32 CollectedStars = 0;

};
