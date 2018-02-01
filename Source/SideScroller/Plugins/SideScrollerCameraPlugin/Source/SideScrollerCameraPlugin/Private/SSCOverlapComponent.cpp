// Fill out your copyright notice in the Description page of Project Settings.

#include "SSCOverlapComponent.h"
#include "SideScrollerPrivatePCH.h"

#include "GameFramework/GameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

#include "SSCActorOverlapComponent.h"
#include "SSCGameMode.h"

// Sets default values for this component's properties
USSCOverlapComponent::USSCOverlapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	/* Spawn CollisionBox for SSCOverlapComponentCheck and attach to root*/
	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
	if (BoxComponent->GetOwner() != nullptr)
	{
		BoxComponent->SetupAttachment(GetOwner()->GetRootComponent());
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &USSCOverlapComponent::BeginOverlap);
	}
}


// Called when the game starts
void USSCOverlapComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
}


// Called every frame
void USSCOverlapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void USSCOverlapComponent::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult &SweepResult)
{
	
	TArray<USSCActorOverlapComponent*> SSCActorOverlapComponents;
	OtherActor->GetComponents(SSCActorOverlapComponents);
	if (SSCActorOverlapComponents.Num() > 0)
	{
		UE_LOG(SSCLog, Log, TEXT("Actor begins overlapping with %s"), *GetOwner()->GetName() );

		// Notify listeners
		UWorld* TheWorld = GetWorld();
		if (TheWorld != nullptr)
		{
			AGameModeBase* GameMode = UGameplayStatics::GetGameMode(TheWorld);
			ASSCGameMode* MyGameMode = Cast<ASSCGameMode>(GameMode);
			if (MyGameMode != nullptr)
			{
				MyGameMode->UpdateCameraDelegate.Broadcast(cameraParametersInstance);
			}
			else
			{
				UE_LOG(SSCLog, Error, TEXT("Game Mode is not SSCGameMode - Cant Broadcast Events"));
			}
		}
	}
}

