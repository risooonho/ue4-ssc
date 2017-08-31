// Fill out your copyright notice in the Description page of Project Settings.

#include "SSCOverlapComponent.h"
#include "SideScrollerPrivatePCH.h"

#include "SideScrollerCamera.h"

// Sets default values for this component's properties
USSCOverlapComponent::USSCOverlapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USSCOverlapComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void USSCOverlapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USSCOverlapComponent::BeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(SSCLog, Log, TEXT("Component Begins Overlapping"));

	// Notify listeners
	OnOverlapWithOverlapComponent.Broadcast(TargetLocation, ArmLength, FollowCharZ);
}

