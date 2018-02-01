// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "SSCBlueprintFunctionLibrary.generated.h"

/* If Multiplayer-Option is enabled at any SideScrollerFollowComponents, only Actors with proper ID's will be followed - not yet implemented */
UENUM(BlueprintType)
namespace ESSCCameraID {
	enum SSCCameraID {
		Camera0,
		Camera1,
		Camera2,
		Camera3,
		Camera4,
		Camera5,
		Camera6,
		Camera7
	};
}

UENUM(BlueprintType)
namespace ESSCTypes {
	enum SSCCameraType {
		Follow,
		Static,
		Cylindrical,
		Spline
	};
}

USTRUCT()
struct FUpdateCameraParametersStruct
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	TEnumAsByte<ESSCTypes::SSCCameraType> SSCType;

	UPROPERTY(EditAnywhere)
	FVector TargetLocation;

	UPROPERTY(EditAnywhere)
	float Armlength;

	UPROPERTY(EditAnywhere)
	bool FollowCharX = true;

	UPROPERTY(EditAnywhere)
	bool FollowCharY = true;
	
	UPROPERTY(EditAnywhere)
	bool FollowCharZ = true;

	UPROPERTY(EditAnywhere)
	bool bMinX;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bMinX"))
	float MinX;

	UPROPERTY(EditAnywhere)
	bool bMaxX;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bMaxX"))
	float MaxX;

	UPROPERTY(EditAnywhere)
	bool bMinY;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bMinY"))
	float MinY;

	UPROPERTY(EditAnywhere)
	bool bMaxY;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bMaxY"))
	float MaxY;

	UPROPERTY(EditAnywhere)
	bool bMinZ;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bMinZ"))
	float MinZ;

	UPROPERTY(EditAnywhere)
	bool bMaxZ;

	UPROPERTY(EditAnywhere, meta = (EditCondition = "bMaxZ"))
	float MaxZ;
};

UCLASS()
class USSCBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
	
	
	
};
