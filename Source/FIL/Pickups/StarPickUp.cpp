// Fill out your copyright notice in the Description page of Project Settings.


#include "StarPickUp.h"
#include "../FILGameMode.h"
#include "Engine/World.h"

void AStarPickUp::OnPickedUp(AFILCharacter& InCharacter)
{
	AFILGameMode* const GameMode = GetWorld()->GetAuthGameMode<AFILGameMode>();
	GameMode->OnStarPickedUp(*this);
}
