// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthPickUp.h"
#include "../FILCharacter.h"
#include "../Components/HealthComponent.h"

void AHealthPickUp::OnPickedUp(AFILCharacter& InCharacter)
{
	if (UHealthComponent* const HealthComponent = InCharacter.GetHealthComponent())
	{
		HealthComponent->GiveHealth(Health);
	}
	Super::OnPickedUp(InCharacter);
}
