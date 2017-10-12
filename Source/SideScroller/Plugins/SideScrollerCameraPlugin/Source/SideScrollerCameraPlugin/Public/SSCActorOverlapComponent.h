// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SideScrollerPrivatePCH.h"

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"

#include "SSCActorOverlapComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FSSCActorOverlapComponentBeginOverlapSignature, AActor*, SSCOverlapActor, AActor*, SideScrollerFollowActor);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIDESCROLLERCAMERAPLUGIN_API USSCActorOverlapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USSCActorOverlapComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/* Create BoxComponent to check for SSCOverlapComponents*/
	UPROPERTY(BlueprintAssignable, Category = "SideScroller")
	UBoxComponent *BoxComponent;

	/* Event when OverlapComponent begins Overlap with SideScrollerFollowComponent */
	UPROPERTY(BlueprintAssignable, Category = "SideScroller")
	FSSCActorOverlapComponentBeginOverlapSignature OnActorOverlapWithSSCOverlapComponent;

	UFUNCTION()
		void BeginOverlap(UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult &SweepResult);
};
