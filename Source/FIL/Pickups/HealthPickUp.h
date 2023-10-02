// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUpBase.h"
#include "HealthPickUp.generated.h"

class AFILCharacter;

UCLASS()
class FIL_API AHealthPickUp : public APickUpBase
{
	GENERATED_BODY()
	
protected:

	virtual void OnPickedUp(AFILCharacter& InCharacter) override;

	UPROPERTY(EditAnywhere)
	float Health = 1;
};
