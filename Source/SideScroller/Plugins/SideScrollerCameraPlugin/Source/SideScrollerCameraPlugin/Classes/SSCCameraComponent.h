// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerPrivatePCH.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SSCOverlapComponent.h"
#include "SideScrollerFollowComponent.h" // Just for enum, can be deletet when enum has its own class

#include "SSCCameraComponent.generated.h"

UENUM()
namespace EDefaultCameraTypeTwo {
	enum Type {
		Follow,
		Static
	};
}

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLERCAMERAPLUGIN_API USSCCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USSCCameraComponent();

private:
	// Array for all Actors to follow with camera
	TArray<AActor*> ActorsToFollow;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float ProtectedCameraArm;

	FRotator ProtectedCameraAngle;

	bool ProtectedFollowCharZ;

	TEnumAsByte<EDefaultCameraTypeTwo::Type> ProtectedCameraType;

	/* Default camera z-axis ofset, in cm */
	float ProtectedCameraOffsetZ;

	/* Default target location for static camera */
	FVector ProtectedTargetLocation;

	/* If Multiplayer-Option is enabled at any SideScrollerFollowComponents, only Actors with proper ID's will be followed - not yet implemented */
	TEnumAsByte<ESSCCameraID::SSCCameraID> ProtectedCameraID;

	/* Default Interpolation Speed as camera delay with dynamic movement, higher values = less delay */
	float ProtectedInterpolationSpeed;

	/* Enable / Disable Delay for camera movement */
	bool bProtectedInterpolationSpeed;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get location of followed actors
	FVector GetActorsLocation();

	// Calculate camera location
	void SetCameraLocation(FVector ActorsLocation);

	FVector ActorsToFollowLocation;

	/* Distance in which the camera will follow the target, in cm */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		float DefaultCameraArm;

	/* Angle in which the camera will follow the target */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		FRotator DefaultCameraAngle;

	/*Set Default camera Type for situations, where camera-targets are in no overlapping SSCOverlapComponent */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		TEnumAsByte<EDefaultCameraTypeTwo::Type> DefaultCameraType;

	/* Default camera z-axis ofset, in cm */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		float DefaultCameraOffsetZ;

	/* Default target location for static camera */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		FVector DefaultTargetLocation;

	/* If Multiplayer-Option is enabled at any SideScrollerFollowComponents, only Actors with proper ID's will be followed - not yet implemented */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		TEnumAsByte<ESSCCameraID::SSCCameraID> CameraID;

	/* Default Interpolation Speed as camera delay with dynamic movement, higher values = less delay */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		float InterpolationSpeed;

	/* Enable / Disable Delay for camera movement */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		bool bInterpolationSpeed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		bool bDefaultFollowCharZ;

	UFUNCTION()
		void UpdateCameraParameters(FVector TargetLocation, float Armlength, bool FollowCharZ);
};
