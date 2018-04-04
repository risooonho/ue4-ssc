// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SSCEventHandler.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTestDelegateSignature, FUpdateCameraParametersStruct, cameraParametersInstance);

UCLASS()
class SIDESCROLLERCAMERAPLUGIN_API USSCEventHandler : public UActorComponent
{
		GENERATED_BODY()
	
public:

	//ASSCEventHandler();

	FTestDelegateSignature TestDelegate;
	
	//USSCEventHandler();
};
