// Fill out your copyright notice in the Description page of Project Settings.

#include "SideScrollerFollowComponent.h"
#include "SideScrollerPrivatePCH.h"

#include "SSCOverlapComponent.h"


// Sets default values for this component's properties
USideScrollerFollowComponent::USideScrollerFollowComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/* Spawn CollisionBox for SSCOverlapComponentCheck and attach to root*/
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if (BoxComponent->GetOwner() != nullptr)
	{
		BoxComponent->SetupAttachment(GetOwner()->GetRootComponent());
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &USideScrollerFollowComponent::BeginOverlap);
	}
}


// Called when the game starts
void USideScrollerFollowComponent::BeginPlay()
{
	Super::BeginPlay();
	
	// ...
	
}


// Called every frame
void USideScrollerFollowComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USideScrollerFollowComponent::GetSSCOverlapComponents()
{
//	this->GetOwner()
}

void USideScrollerFollowComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, 
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	UE_LOG(SSCLog, Log, TEXT("TESTYTEST"));
}
