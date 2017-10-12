// Fill out your copyright notice in the Description page of Project Settings.

#include "SSCActorOverlapComponent.h"
#include "SideScrollerPrivatePCH.h"

#include "SSCCameraComponent.h"

#include "SSCOverlapComponent.h"


// Sets default values for this component's properties
USSCActorOverlapComponent::USSCActorOverlapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/* Spawn CollisionBox for SSCOverlapComponentCheck and attach to root*/
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if (BoxComponent->GetOwner() != nullptr)
	{
		BoxComponent->SetupAttachment(GetOwner()->GetRootComponent());
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &USSCActorOverlapComponent::BeginOverlap);
	}
}


// Called when the game starts
void USSCActorOverlapComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USSCActorOverlapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USSCActorOverlapComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	TArray<USSCOverlapComponent*> SSCOverlapComponents;
	OtherActor->GetComponents(SSCOverlapComponents);

	if (SSCOverlapComponents.Num() > 0)
	{
		UE_LOG(SSCLog, Log, TEXT("Actor begins overlapping with %s"), *OtherActor->GetName() );

		// Notify listeners
		OnActorOverlapWithSSCOverlapComponent.Broadcast(OtherActor, this->GetOwner());
	}
}