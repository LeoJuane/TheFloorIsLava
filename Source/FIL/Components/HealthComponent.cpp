// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	CurrentHealth = Health;
	MaxHealth = Health;

	HealthState = (CurrentHealth > 0.0f) ? EHealthState::Alive : EHealthState::Dead;
}

float UHealthComponent::ApplyDamage(float InDamage)
{
	if (InDamage <= 0.0f || HealthState == EHealthState::Dead)
	{
		return 0.0f;
	}
	return ModifyHealth_Internal(-1.0f * InDamage) * -1.0f;
}

float UHealthComponent::GiveHealth(float InHealth)
{
	if (InHealth <= 0.0f || (HealthState == EHealthState::Dead))
	{
		return 0.0f;
	}
	return ModifyHealth_Internal(InHealth);
}

void UHealthComponent::BP_GetHealth(float& OutHealth, float& OutMaxHealth) const
{
	OutHealth = CurrentHealth;
	OutMaxHealth = OutMaxHealth;
}

float UHealthComponent::ModifyHealth_Internal(float InHealthDelta)
{
	float ActualDelta = 0.0f;
	if (InHealthDelta < 0.0f)
	{
		ActualDelta = FMath::Max(InHealthDelta, CurrentHealth * -1.0f);
	}
	else if (InHealthDelta > 0.0f)
	{
		//
		ActualDelta = FMath::Min(InHealthDelta, MaxHealth - CurrentHealth);
	}

	if (ActualDelta == 0.0f)
	{
		return 0.0f;
	}

	CurrentHealth += ActualDelta;
	OnHealthChanged.Broadcast(CurrentHealth, ActualDelta);

	EHealthState PreviousState = HealthState;
	if (HealthState == EHealthState::Alive && CurrentHealth <= 0.0f)
	{
		//We died
		HealthState = EHealthState::Dead;
	}
	else if (HealthState == EHealthState::Dead && CurrentHealth >= 0.0f)
	{
		//We've been revived
		HealthState = EHealthState::Alive;
	}

	if (PreviousState != HealthState)
	{
		OnHealthStateChanged.Broadcast(HealthState);
	}
	return ActualDelta;
}
