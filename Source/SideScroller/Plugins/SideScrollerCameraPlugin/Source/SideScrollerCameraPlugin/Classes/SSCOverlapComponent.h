// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerPrivatePCH.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "SSCOverlapComponent.generated.h"

// Will ich noch in seperate Datei verpacken
UENUM()
namespace ESSCTypes {
	enum Type {
		Follow,
		Static
	};
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSSCOverlapComponentBeginOverlapSignature, FVector, TargetLocation, float, ArmLength, bool, FollowCharZ);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLERCAMERAPLUGIN_API USSCOverlapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USSCOverlapComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

	/* Distance in which the camera will follow the target, in cm */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	TEnumAsByte<ESSCTypes::Type> SSCType; 
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	FVector TargetLocation;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	float ArmLength;

	/* Event when OverlapComponent begins Overlap with SideScrollerFollowComponent */
	UPROPERTY(BlueprintAssignable, Category = "SideScroller")
	FSSCOverlapComponentBeginOverlapSignature OnOverlapWithOverlapComponent;

	/* All Following not yet implemented */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	bool FollowCharZ;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	float MinZ;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	float MaxZ;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	float MinX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	float MaxX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	float MinY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	float MaxY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	bool bMinX;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	bool bMinY;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	bool bMinZ;
};
