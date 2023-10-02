// Fill out your copyright notice in the Description page of Project Settings.


#include "FILGameState.h"

int32 AFILGameState::AddCollectedStar()
{
	++CollectedStars;
	OnStarCollected.Broadcast(CollectedStars);
	return CollectedStars;
}

void AFILGameState::NotifyGameOver(bool bInPlayerWon)
{
	OnGameOver.Broadcast(bInPlayerWon);
}