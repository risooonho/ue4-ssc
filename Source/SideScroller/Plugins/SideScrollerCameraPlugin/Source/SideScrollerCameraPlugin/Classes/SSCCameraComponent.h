// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerPrivatePCH.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SSCOverlapComponent.h"
#include "SSCBlueprintFunctionLibrary.h"

#include "SSCCameraComponent.generated.h"


UCLASS( ClassGroup=(SideScrollerCamera), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLERCAMERAPLUGIN_API USSCCameraComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USSCCameraComponent();

private:
	// Array for all Actors to follow with camera
	TArray<AActor*> ActorsToFollow;

	FInputAxisBinding ManualCameraX;

	FInputAxisBinding ManualCameraY;

	float ManualCameraXValue;

	float ManualCameraYValue;

	APlayerController* PlayerController;

	float ManualCameraBackwardsRotationTimeElapsed;

	bool bAreActorsToFollowMoving;

	FVector ActorsToFollowLocation;

	FVector ActorsToFollowLocationLastFrame;

	float SplineOverTimeTimeElapsed = 0;

	float Splinepoint = 0;

	float SplineLength;

	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	float ProtectedCameraArm;

	FRotator ProtectedCameraAngle;

	bool ProtectedFollowCharZ;

	TEnumAsByte<ESSCTypes::SSCCameraType> ProtectedCameraType;

	FUpdateCameraParametersStruct ProtectedCameraParametersInstance;

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

	UPROPERTY(EditAnywhere)
		FUpdateCameraParametersStruct DefaultCameraParameters;

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Get location of followed actors
	FVector GetActorsLocation();

	// Calculate camera location
	void SetCameraLocation(FVector ActorsLocation);

	/* Angle in which the camera will follow the target */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		FRotator DefaultCameraAngle;

	/* Default camera z-axis ofset, in cm */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		float DefaultCameraOffsetZ;

	/* If Multiplayer-Option is enabled at any SideScrollerFollowComponents, only Actors with proper ID's will be followed - not yet implemented */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		TEnumAsByte<ESSCCameraID::SSCCameraID> CameraID;

	/* Enable / Disable Delay for camera movement */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		bool bInterpolationSpeed;

	/* Default Interpolation Speed as camera delay with dynamic movement, higher values = less delay */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller", meta = (EditCondition = "bInterpolationSpeed"))
		float InterpolationSpeed;

	UFUNCTION()
		void UpdateCameraParameters(FUpdateCameraParametersStruct newCameraParameters);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		bool bManualCameraRotation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller", meta = (EditCondition = "bManualCameraRotation"))
		FName RotateCameraXAxisMappingName;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller" , meta = (EditCondition = "bManualCameraRotation"))
		FName RotateCameraYAxisMappingName;

	UFUNCTION()
		void ManuallyRotateCamera(float deltaTime);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller", meta = (EditCondition = "bManualCameraRotation"))
		float ManualCameraRotationSpeed = 50;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller", meta = (EditCondition = "bManualCameraRotation"))
		bool bLimitManualCameraRotation = true;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller", meta = (EditCondition = "bLimitManualCameraRotation"))
		float ManualCameraMaxPitchValue = 90;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller", meta = (EditCondition = "bLimitManualCameraRotation"))
		float ManualCameraMaxYawValue = 90;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		bool bManualCameraBackwardsRotationWhenMoving;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller", meta = (EditCondition = "!bManualCameraBackwardsRotationWhenMoving"))
		float ManualCameraBackwardsRotationTime = 1.0f;

	UFUNCTION()
		bool AreActorsMoving(FVector ActorsToFollowLocation);

	void AvoidObstacles();

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller", meta = (EditCondition = "bManualCameraRotation"))
		float ManualCameraBackwardsRotatingSpeed = 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
		bool bAvoidObstacles;

	FDelegateHandle MyDelegateHandle;
};
