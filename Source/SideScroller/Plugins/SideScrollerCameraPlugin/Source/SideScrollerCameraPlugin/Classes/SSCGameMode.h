// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerPrivatePCH.h"

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "SSCBlueprintFunctionLibrary.h"

#include "SSCGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUpdateCameraFromSSCOverlapSignature, FUpdateCameraParametersStruct, cameraParametersInstance);

UCLASS()
class SIDESCROLLERCAMERAPLUGIN_API ASSCGameMode : public AGameModeBase
{

	GENERATED_BODY()
	
public:

	FUpdateCameraFromSSCOverlapSignature UpdateCameraDelegate;

	ASSCGameMode();
};
