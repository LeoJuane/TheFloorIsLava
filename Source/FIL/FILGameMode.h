// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

//Engine
#include "GameFramework/GameModeBase.h"

//FIL
//#include "Components/HealthComponent.h"
#include "FILGameMode.generated.h"

enum class EHealthState : uint8;
class AStarPickUp;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameOver, bool, bPlayerWon);

UCLASS(minimalapi)
class AFILGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:

	AFILGameMode();

	UPROPERTY(BlueprintAssignable)
	FOnGameOver OnGameOver;

	void OnStarPickedUp(AStarPickUp& InPickedUpStar);

	UFUNCTION(BlueprintCallable)
	float GetGameDuration() const { return GameDuration; }

	UFUNCTION(BlueprintCallable)
	float GetGameOverRestartDuration() const { return GameOverRestartDuration; }

	UFUNCTION(BlueprintCallable)
	int32 GetRequiredStars() const { return RequiredStars; }

protected:

	virtual void SetPlayerDefaults(APawn* InPlayerPawn) override;

	UPROPERTY(EditDefaultsOnly)
	float GameDuration{90.0f};

	UPROPERTY(EditDefaultsOnly)
	float GameOverRestartDuration = 3.0f;

	//Stars the player needs to collect to win the game
	UPROPERTY(EditDefaultsOnly)
	int32 RequiredStars = 5;

private:

	UFUNCTION()
	void OnPlayerHealthStateChanged(EHealthState InHealthState);

	UFUNCTION()
	void OnGameDurationEnded();

	virtual void SetGameOverTimer(bool bPlayerWon);

	UFUNCTION()
	void ReloadLevel();

	FTimerHandle GameDuration_TimerHandle;
	FTimerHandle GameOver_TimerHandle;
};



