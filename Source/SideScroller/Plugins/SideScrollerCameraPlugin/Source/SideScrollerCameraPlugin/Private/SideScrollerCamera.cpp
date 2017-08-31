// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerCamera.h"


#include "EngineUtils.h"

#include "SideScrollerFollowComponent.h"

ASideScrollerCamera::ASideScrollerCamera(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts
void ASideScrollerCamera::BeginPlay()
{
	Super::BeginPlay();

	// Set Camera Angle
	this->SetActorRotation(DefaultCameraAngle);

	// Update protectedVariables to Default Camera Settings
	ProtectedTargetLocation = DefaultTargetLocation;
	ProtectedCameraArm = DefaultCameraArm;
	ProtectedFollowCharZ = bDefaultFollowCharZ;

	// Get all actors to follow
	for (TActorIterator<AActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		TArray<USideScrollerFollowComponent*> SideScrollerFollowComponents;
		ActorItr->GetComponents(SideScrollerFollowComponents);

		if (SideScrollerFollowComponents.Num() > 0)
		{
			ActorsToFollow.Add(*ActorItr);
			UE_LOG(SSCLog, Log, TEXT("Following Actor: %s"), *ActorItr->GetName());
			SetCameraLocation(GetActorsLocation());
		}

		TArray<USSCOverlapComponent*> SSCOverlapComponents;
		ActorItr->GetComponents(SSCOverlapComponents);

		if (SSCOverlapComponents.Num() > 0)
		{
			auto SSCOverlapComponent = Cast<USSCOverlapComponent>(SSCOverlapComponents[0]);
			SSCOverlapComponent->OnOverlapWithOverlapComponent.AddDynamic(this, &ASideScrollerCamera::UpdateCameraParameters);
		}
	}
}

void ASideScrollerCamera::Tick(float DeltaTime)
{
	SetCameraLocation(GetActorsLocation());
}

FVector ASideScrollerCamera::GetActorsLocation()
{
	if (ActorsToFollow.Num() == 0) {
		return{};
	}

	FVector ActorsLocation = FVector(0.0f,0.0f,0.0f);

	for (AActor* Actors : ActorsToFollow)
	{
		ActorsLocation += Actors->GetActorLocation();
		//UE_LOG(SSCLog, Log, TEXT("Following Actor %s"), *Actors->GetName());

	}

	ActorsLocation = ActorsLocation / ActorsToFollow.Num();

	ActorsToFollowLocation = ActorsLocation;
	
	return ActorsToFollowLocation;
}

void ASideScrollerCamera::SetCameraLocation(FVector ActorsLocation)
{
	/*if (ActorsLocation.IsZero())
	{
		UE_LOG(SSCLog, Log, TEXT("No Actor To Follow and DefaultCameraType set to Follow"));
		return;
	}*/


	if (DefaultCameraType == EDefaultCameraType::Static)
	{
		// Set camera to DefaultTargetLocation and apply z-axis camera-offset
		FVector NewLocation = ProtectedTargetLocation + this->GetActorUpVector() * DefaultCameraOffsetZ;
		this->SetActorLocation(NewLocation);
	}
	else if (DefaultCameraType == EDefaultCameraType::Follow)
	{
		// Set camera distance in relation to rotation
		FVector NewLocation = ActorsLocation + this->GetActorForwardVector() * ProtectedCameraArm + this->GetActorUpVector() * DefaultCameraOffsetZ;

		// Calculate camera location with InterpolationSpeed
		if (bInterpolationSpeed)
		{
			NewLocation = FMath::VInterpTo(this->GetActorLocation(), NewLocation, GetWorld()->GetDeltaSeconds(), InterpolationSpeed);
		}
		
		this->SetActorLocation(NewLocation);
	}
}

void ASideScrollerCamera::UpdateCameraParameters(FVector TargetLocation, float Armlength, bool FollowCharZ)
{
	ProtectedTargetLocation = TargetLocation;
	ProtectedCameraArm = Armlength;
	ProtectedFollowCharZ = FollowCharZ;
}
