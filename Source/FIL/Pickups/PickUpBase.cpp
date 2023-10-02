// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUpBase.h"
#include "../FILCharacter.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
APickUpBase::APickUpBase()
{
	PrimaryActorTick.bCanEverTick = false;

	RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = RootScene;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootScene);

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere Collision"));
	SphereCollision->SetupAttachment(RootScene);

	//Collision Setup
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	SphereCollision->SetGenerateOverlapEvents(true);
}

void APickUpBase::DestroyPickup()
{
	SetActorHiddenInGame(true);
	SetLifeSpan(0.1f);
}

void APickUpBase::BeginPlay()
{
	Super::BeginPlay();
	OnActorBeginOverlap.AddDynamic(this, &APickUpBase::OnOtherActorBeginOverlap);
}

void APickUpBase::OnPickedUp(AFILCharacter& InCharacter)
{
	DestroyPickup();
}

void APickUpBase::OnOtherActorBeginOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (AFILCharacter* const Character = Cast<AFILCharacter>(OtherActor))
	{
		NativeOnPickedUp(*Character);
	}
}

void APickUpBase::NativeOnPickedUp(AFILCharacter& InCharacter)
{
	OnPickedUp(InCharacter);
	BP_OnPickedUp(&InCharacter);
}
