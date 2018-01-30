// Fill out your copyright notice in the Description page of Project Settings.

#include "SSCCameraComponent.h"

#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

#include "SideScrollerFollowComponent.h"
#include "SSCActorOverlapComponent.h"
#include "SSCGameMode.h"


// Sets default values for this component's properties
USSCCameraComponent::USSCCameraComponent()
{
// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
// off to improve performance if you don't need them.
PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void USSCCameraComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set Camera Angle
	GetOwner()->SetActorRotation(DefaultCameraAngle);

	// Update protectedVariables to Default Camera Settings
	ProtectedTargetLocation = DefaultTargetLocation;
	ProtectedCameraArm = DefaultCameraArm;
	ProtectedFollowCharZ = bDefaultFollowCharZ;

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

	// Check for manual camera rotation settings
	if (bManualCameraRotation)
	{
		UE_LOG(SSCLog, Log, TEXT("ManualCameraRotation activated"));
		if (RotateCameraXAxisMappingName != TEXT("None"))
		{
			if (GetOwner() != nullptr)
			{
				PlayerController = Cast<APlayerController>(GetWorld()->GetFirstPlayerController());

				if (PlayerController != nullptr) //&& PlayerController->InputEnabled == false)
				{
					GetOwner()->EnableInput(PlayerController);

					GetOwner()->InputComponent->BindAxis(RotateCameraXAxisMappingName); // <- hier nochmal schauen, ob das so okay oder der beste Weg ist
					GetOwner()->InputComponent->BindAxis(RotateCameraYAxisMappingName); // <- hier nochmal schauen, ob das so okay oder der beste Weg ist
				}
			}
		}
		else
		{
			UE_LOG(SSCLog, Warning, TEXT("ManualCameraRotation is activated, but no RotateCameraXAxisMapping is set"));
		}
	}

}


// Called every frame
void USSCCameraComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	SetCameraLocation(GetActorsLocation());

	if (bManualCameraRotation && PlayerController != nullptr)
	{
		ManuallyRotateCamera(DeltaTime);
	}
	else
	{
		if (PlayerController == nullptr)
		{
			UE_LOG(SSCLog, Warning, TEXT("MaualCameraRotation is set to true, but PlayerController is null"))
		}
	}
}

void USSCCameraComponent::SetCameraLocation(FVector ActorsLocation)
{
	/*if (ActorsLocation.IsZero())
	{
	UE_LOG(SSCLog, Log, TEXT("No Actor To Follow and DefaultCameraType set to Follow"));
	return;
	}*/


	if (DefaultCameraType == EDefaultCameraTypeTwo::Static)
	{
		// Set camera to DefaultTargetLocation and apply z-axis camera-offset
		FVector NewLocation = ProtectedTargetLocation + GetOwner()->GetActorUpVector() * DefaultCameraOffsetZ;
		GetOwner()->SetActorLocation(NewLocation);
	}
	else if (DefaultCameraType == EDefaultCameraTypeTwo::Follow)
	{
		// Set camera distance in relation to rotation
		FVector NewLocation = ActorsLocation + GetOwner()->GetActorForwardVector() * ProtectedCameraArm + GetOwner()->GetActorUpVector() * DefaultCameraOffsetZ;

		// Calculate camera location with InterpolationSpeed
		if (bInterpolationSpeed)
		{
			NewLocation = FMath::VInterpTo(GetOwner()->GetActorLocation(), NewLocation, GetWorld()->GetDeltaSeconds(), InterpolationSpeed);
		}

		GetOwner()->SetActorLocation(NewLocation);
	}
}

// Updates Camera Parameters, e.g. when an Actor with SideScrollerFollowComponent start overlapping with Actor with SSCActorOverlapComponent
void USSCCameraComponent::UpdateCameraParameters(FVector TargetLocation, float Armlength, bool FollowCharZ)
{
	ProtectedTargetLocation = TargetLocation;
	ProtectedCameraArm = Armlength;
	ProtectedFollowCharZ = FollowCharZ;

	UE_LOG(SSCLog, Log, TEXT("SSCCamera Updated"));
}

// Returns center of all followed Actors
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

	// If manual camera backwards movement is dependent on movement of followed actors, call AreActorsMoving function
	if (bManualCameraBackwardsRotationWhenMoving == true)
	{
		AreActorsMoving(ActorsToFollowLocation);
	}

	return ActorsToFollowLocation;
}

// returns if one of the actors to follow is moving
bool USSCCameraComponent::AreActorsMoving(FVector ActorsToFollowLocation)
{
	if (ActorsToFollowLocationLastFrame == FVector(0, 0, 0)) //auch mal schauen, obs da nichts besseres gibt
	{
		ActorsToFollowLocationLastFrame = ActorsToFollowLocation;
		bAreActorsToFollowMoving = false;
	}
	else if (ActorsToFollowLocation == ActorsToFollowLocationLastFrame)
	{
		bAreActorsToFollowMoving = false;
	}
	else
	{
		bAreActorsToFollowMoving = true;
	}

	ActorsToFollowLocationLastFrame = ActorsToFollowLocation;
	
	return bAreActorsToFollowMoving;
}

// Manual Camera Movement
void USSCCameraComponent::ManuallyRotateCamera(float DeltaTime)
{
	if (GetOwner()->GetInputAxisValue(RotateCameraXAxisMappingName) != 0 || GetOwner()->GetInputAxisValue(RotateCameraYAxisMappingName) != 0)
	{
		ManualCameraXValue = ManualCameraXValue + GetOwner()->GetInputAxisValue(RotateCameraXAxisMappingName) * DeltaTime * ManualCameraRotationSpeed;
		ManualCameraYValue = ManualCameraYValue + GetOwner()->GetInputAxisValue(RotateCameraYAxisMappingName) * DeltaTime * ManualCameraRotationSpeed;


		GetOwner()->AddActorLocalRotation(FRotator((GetOwner()->GetInputAxisValue(RotateCameraXAxisMappingName)) * DeltaTime * ManualCameraRotationSpeed, (GetOwner()->GetInputAxisValue(RotateCameraYAxisMappingName)) * DeltaTime * ManualCameraRotationSpeed, 0));
		GetOwner()->SetActorRotation(FRotator(GetOwner()->GetActorRotation().Pitch, GetOwner()->GetActorRotation().Yaw, 0)); // <-- verursacht einen kurzen "offset" in der Kamera beim Drehen

		if (ManualCameraBackwardsRotationTimeElapsed != 0 && bManualCameraBackwardsRotationWhenMoving == false)
		{
			ManualCameraBackwardsRotationTimeElapsed = 0;
		}
	}
	else if ((ManualCameraBackwardsRotationTimeElapsed >= ManualCameraBackwardsRotationTime && bManualCameraBackwardsRotationWhenMoving == false) || (bManualCameraBackwardsRotationWhenMoving == true && bAreActorsToFollowMoving == true))
	{
		if (ManualCameraXValue < 0)
		{
			ManualCameraXValue = ManualCameraXValue + 0.1f;
			GetOwner()->AddActorLocalRotation(FRotator(0.1f, 0, 0));
			GetOwner()->SetActorRotation(FRotator(GetOwner()->GetActorRotation().Pitch, GetOwner()->GetActorRotation().Yaw, 0)); // <-- verursacht einen kurzen "offset" in der Kamera beim Drehen

			if (ManualCameraXValue < -180)
			{
				ManualCameraXValue += 360;
			}
		}
		else if (ManualCameraXValue > 0)
		{
			ManualCameraXValue = ManualCameraXValue - 0.1f;
			GetOwner()->AddActorLocalRotation(FRotator(-0.1f, 0, 0));
			GetOwner()->SetActorRotation(FRotator(GetOwner()->GetActorRotation().Pitch, GetOwner()->GetActorRotation().Yaw, 0)); // <-- verursacht einen kurzen "offset" in der Kamera beim Drehen

			if (ManualCameraXValue > 180)
			{
				ManualCameraXValue -= 360;
			}
		}

		if (ManualCameraYValue < 0)
		{
			ManualCameraYValue = ManualCameraYValue + 0.1f;
			GetOwner()->AddActorLocalRotation(FRotator(0, 0.1f, 0));
			GetOwner()->SetActorRotation(FRotator(GetOwner()->GetActorRotation().Pitch, GetOwner()->GetActorRotation().Yaw, 0)); // <-- verursacht einen kurzen "offset" in der Kamera beim Drehen

			if (ManualCameraYValue < -180)
			{
				ManualCameraYValue += 360;
			}
		}
		else if (ManualCameraYValue > 0)
		{
			ManualCameraYValue = ManualCameraYValue - 0.1f;
			GetOwner()->AddActorLocalRotation(FRotator(0, - 0.1f, 0));
			GetOwner()->SetActorRotation(FRotator(GetOwner()->GetActorRotation().Pitch, GetOwner()->GetActorRotation().Yaw, 0)); // <-- verursacht einen kurzen "offset" in der Kamera beim Drehen

			if (ManualCameraYValue > 180)
			{
				ManualCameraYValue -= 360;
			}
		}

		if (FMath::IsNearlyZero(ManualCameraXValue, 0.1f))
		{
			ManualCameraXValue = 0.0f;
		}

		if (FMath::IsNearlyZero(ManualCameraYValue, 0.1f))
		{
			ManualCameraYValue = 0.0f;
		}
	}
	else if (bManualCameraBackwardsRotationWhenMoving == false)
	{
		ManualCameraBackwardsRotationTimeElapsed += DeltaTime;
	}
	
	
	//UE_LOG(SSCLog, Log, TEXT("Value %f"), GetOwner()->GetInputAxisValue(RotateCameraXAxisMappingName));

	/*if (InputComponentz != nullptr)
	{
		//UE_LOG(SSCLog, Log, TEXT("Value %s"), (GetOwner()->InputComponent->bIsActive ? TEXT("True") : TEXT("False")));
	}
	else
	{
		UE_LOG(SSCLog, Error, TEXT("ManuallyRotateCamera() is called, but InputComponentn is null"));
	}*/
}