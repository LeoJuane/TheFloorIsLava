// Copyright Epic Games, Inc. All Rights Reserved.

//FIL
#include "FILGameMode.h"
#include "FILCharacter.h"
#include "FILGameState.h"
#include "Components/HealthComponent.h"
#include "Pickups/StarPickUp.h"

//Engine
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFILGameMode::AFILGameMode()
{
	GameStateClass = AFILGameState::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AFILGameMode::OnStarPickedUp(AStarPickUp& InPickedUpStar)
{
	int32 PickedUpStars = GetGameState<AFILGameState>()->AddCollectedStar();
	InPickedUpStar.DestroyPickup();

	if (PickedUpStars >= RequiredStars)
	{
		static constexpr bool bPlayerWon = true;
		SetGameOverTimer(bPlayerWon);
	}
}

void AFILGameMode::SetPlayerDefaults(APawn* InPlayerPawn)
{
	AFILCharacter* const FILCharacter = CastChecked<AFILCharacter>(InPlayerPawn);
	UHealthComponent* const HealthComponent = FILCharacter->GetHealthComponent();

	HealthComponent->OnHealthStateChanged.AddDynamic(this, &AFILGameMode::OnPlayerHealthStateChanged);

	GetWorld()->GetTimerManager().SetTimer(GameDuration_TimerHandle, this, &AFILGameMode::OnGameDurationEnded, GameDuration);
}

void AFILGameMode::OnPlayerHealthStateChanged(EHealthState InHealthState)
{
	if (InHealthState == EHealthState::Dead)
	{
		static constexpr bool bPlayerWon = false;
		SetGameOverTimer(bPlayerWon);
	}
}

void AFILGameMode::OnGameDurationEnded()
{
	SetGameOverTimer(/*bPlayerWon =*/ false);
}

void AFILGameMode::SetGameOverTimer(bool bPlayerWon)
{
	if (GameOver_TimerHandle.IsValid())
	{
		return;
	}

	if (GameDuration_TimerHandle.IsValid())
	{
		GameDuration_TimerHandle.Invalidate();
	}

	GetGameState<AFILGameState>()->NotifyGameOver(bPlayerWon);
	GetWorld()->GetTimerManager().SetTimer(GameOver_TimerHandle, this, &AFILGameMode::ReloadLevel, GameOverRestartDuration);
}

void AFILGameMode::ReloadLevel()
{
	GameOver_TimerHandle.Invalidate();

	const FName LevelName = *UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, LevelName);
}
