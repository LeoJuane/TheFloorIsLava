// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "PickUpBase.generated.h"

class AFILCharacter;
class USceneComponent;
class USphereComponent;
class UStaticMeshComponent;

UCLASS()
class FIL_API APickUpBase : public AActor
{
	GENERATED_BODY()
	
public:	
	
	APickUpBase();

	void DestroyPickup();

protected:

	virtual void BeginPlay() override;

	virtual void OnPickedUp(AFILCharacter& InCharacter);

	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Picked Up"))
	void BP_OnPickedUp(AFILCharacter* InCharacter);

private:

	//Called when other actor overlaps this one
	UFUNCTION()
	void OnOtherActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor);

	void NativeOnPickedUp(AFILCharacter& InCharacter);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USceneComponent* RootScene;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	USphereComponent* SphereCollision;
};
