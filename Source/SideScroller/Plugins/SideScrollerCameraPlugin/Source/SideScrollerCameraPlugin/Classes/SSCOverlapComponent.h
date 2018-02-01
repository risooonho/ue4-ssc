// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerPrivatePCH.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"

#include "SSCBlueprintFunctionLibrary.h"

#include "SSCOverlapComponent.generated.h"



//DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FSSCOverlapComponentBeginOverlapSignature, FVector, TargetLocation, float, ArmLength, bool, FollowCharZ);

UCLASS( ClassGroup=(SideScrollerCamera), meta=(BlueprintSpawnableComponent) )
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
	void BeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult &SweepResult);

	UBoxComponent *BoxComponent;

	UPROPERTY(EditAnywhere)
	FUpdateCameraParametersStruct cameraParametersInstance;

	/* Distance in which the camera will follow the target, in cm */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	TEnumAsByte<ESSCTypes::SSCCameraType> SSCType; 
	

	/* Event when OverlapComponent begins Overlap with SideScrollerFollowComponent */
	/*UPROPERTY(BlueprintAssignable, Category = "SideScroller")
	FSSCOverlapComponentBeginOverlapSignature OnOverlapWithOverlapComponent;*/

	//FDelegateHandle MyDelegateHandle;
};
