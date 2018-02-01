// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerPrivatePCH.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SSCBlueprintFunctionLibrary.h"

#include "SideScrollerFollowComponent.generated.h"

UCLASS( ClassGroup=(SideScrollerCamera), meta=(BlueprintSpawnableComponent) )
class USideScrollerFollowComponent : public UActorComponent
{
	GENERATED_BODY()


public:	
	// Sets default values for this component's properties
	USideScrollerFollowComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Enable/Disables Multiplayer-Options of Component */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	bool bMultipleCameras;

	/* If Multiplayer-Option is enabled, only Actors with proper ID's will be followed */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	TEnumAsByte<ESSCCameraID::SSCCameraID> CameraID;
};


