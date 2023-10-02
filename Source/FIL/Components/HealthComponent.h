// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

//Engine
#include "Components/ActorComponent.h"

//FIL
#include "HealthComponent.generated.h"

UENUM(BlueprintType)
enum class EHealthState : uint8
{
	Alive,
	Dead
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnHealthChanged, float, NewHealth, float, DeltaValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnHealthStateChanged, EHealthState, NewState);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FIL_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();
	
public:

	UFUNCTION(BlueprintCallable)
	float ApplyDamage(float InDamage);

	UFUNCTION(BlueprintCallable)
	float GiveHealth(float InHealth);

	EHealthState GetHealthState() const { return HealthState; }

	UFUNCTION(BlueprintCallable, meta = (DisplayName = "Get Health"))
	void BP_GetHealth(float& OutHealth, float& OutMaxHealth) const;

	UPROPERTY(BlueprintAssignable)
	FOnHealthChanged OnHealthChanged;

	UPROPERTY(BlueprintAssignable)
	FOnHealthStateChanged OnHealthStateChanged;

protected:

	UPROPERTY(EditAnywhere)
	float Health = 3.0f;

private:

	float ModifyHealth_Internal(float InHealthDelta);

	EHealthState HealthState;
	float CurrentHealth;
	float MaxHealth;
};
