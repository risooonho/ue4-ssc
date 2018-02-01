// Fill out your copyright notice in the Description page of Project Settings.

#include "SSCCameraComponent.h"

#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"

#include "SSCBlueprintFunctionLibrary.h"

#include "SideScrollerFollowComponent.h"
#include "SSCActorOverlapComponent.h"
#include "SSCGameMode.h"


// Sets default values for this component's properties
USSCCameraComponent::USSCCameraComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void USSCCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set Camera Angle
	GetOwner()->SetActorRotation(DefaultCameraAngle);

	// Update protectedVariables to Default Camera Settings
	ProtectedCameraParametersInstance.TargetLocation = DefaultTargetLocation;
	ProtectedCameraParametersInstance.Armlength = DefaultCameraArm;
	ProtectedCameraParametersInstance.FollowCharZ = bDefaultFollowCharZ;

	UWorld* TheWorld = GetWorld();
	if (TheWorld != nullptr)
	{
		AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
		ASSCGameMode* SSCGameMode = Cast<ASSCGameMode>(GameMode);
		if (SSCGameMode != nullptr)
		{
			SSCGameMode->UpdateCameraDelegate.AddDynamic(this, &USSCCameraComponent::UpdateCameraParameters);
		}
		
	}
	
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
			//SSCOverlapComponent->OnOverlapWithOverlapComponent.AddDynamic(this, &USSCCameraComponent::UpdateCameraParameters);
		}
	}
	
}


// Called every frame
void USSCCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetCameraLocation(GetActorsLocation());
}

void USSCCameraComponent::SetCameraLocation(FVector ActorsLocation)
{
	/*if (ActorsLocation.IsZero())
	{
	UE_LOG(SSCLog, Log, TEXT("No Actor To Follow and DefaultCameraType set to Follow"));
	return;
	}*/

	FVector NewLocation;

	switch (DefaultCameraType)
	{
		
		case ESSCTypes::Static:
			// Set camera to DefaultTargetLocation and apply z-axis camera-offset
			NewLocation = ProtectedCameraParametersInstance.TargetLocation + GetOwner()->GetActorUpVector() * DefaultCameraOffsetZ;
			GetOwner()->SetActorLocation(NewLocation);
			break;
		case ESSCTypes::Follow:
			// Set camera distance in relation to rotation
			NewLocation = ActorsLocation + GetOwner()->GetActorForwardVector() * ProtectedCameraParametersInstance.Armlength + GetOwner()->GetActorUpVector() * DefaultCameraOffsetZ;

			// Calculate camera location with InterpolationSpeed
			if (bInterpolationSpeed)
			{
				NewLocation = FMath::VInterpTo(GetOwner()->GetActorLocation(), NewLocation, GetWorld()->GetDeltaSeconds(), InterpolationSpeed);
			}

			GetOwner()->SetActorLocation(NewLocation);
			break;

		case ESSCTypes::Cylindrical:


			break;
		case ESSCTypes::Spline:

			break;

	};	
}

// Update Camera Parameters
void USSCCameraComponent::UpdateCameraParameters(FUpdateCameraParametersStruct newCameraParameters)
{
	ProtectedCameraParametersInstance = newCameraParameters;

	UE_LOG(SSCLog, Log, TEXT("SSCCamera Updated"));
}

FVector USSCCameraComponent::GetActorsLocation()
{
	if (ActorsToFollow.Num() == 0) {
		return{};
	}

	FVector ActorsLocation = FVector(0.0f, 0.0f, 0.0f);

	for (AActor* Actors : ActorsToFollow)
	{
		ActorsLocation += Actors->GetActorLocation();
		//UE_LOG(SSCLog, Log, TEXT("Following Actor %s"), *Actors->GetName());

	}

	ActorsLocation = ActorsLocation / ActorsToFollow.Num();

	ActorsToFollowLocation = ActorsLocation;

	return ActorsToFollowLocation;
}