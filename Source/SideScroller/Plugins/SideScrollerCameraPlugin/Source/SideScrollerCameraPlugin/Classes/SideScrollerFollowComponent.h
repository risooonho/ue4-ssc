// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerPrivatePCH.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"

#include "SideScrollerFollowComponent.generated.h"


UENUM()
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

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

	virtual void GetSSCOverlapComponents();

	/* Create BoxComponent to check for SSCOverlapComponents*/
	UBoxComponent *BoxComponent;

	/* Enable/Disables Multiplayer-Options of Component */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	bool bMultipleCameras;

	/* If Multiplayer-Option is enabled, only Actors with proper ID's will be followed */
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SideScroller")
	TEnumAsByte<ESSCCameraID::SSCCameraID> CameraID;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
};


