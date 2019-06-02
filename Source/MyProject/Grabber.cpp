// Adam's Copyright 2019

#include "Grabber.h"
#include "Engine/World.h"
#include <Runtime\Engine\Public\DrawDebugHelpers.h>
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsHandleComponent.h"
#include "Classes/Components/PrimitiveComponent.h"
#include "Windows/MinWindows.h"

#define OUT

/// Sets default values for this component's properties
UGrabber::UGrabber()
{
	/// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	/// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	/// ...
}


/// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandleComponent();
	SetupInputComponent();

}

void UGrabber::SetupInputComponent()
{
	///look for attached input component
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();//finds type Uphysicshandlecomponent
	if (InputComponent)
	{
		///UE_LOG(LogTemp, Warning, TEXT("Input component found"))
			///bind the input axis
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing input component"), *GetOwner()->GetName())
	}
}

///look for attached physics handle
void UGrabber::FindPhysicsHandleComponent()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();//finds type Uphysicshandlecomponent
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("%s missing physics handle component"), *GetOwner()->GetName())
	}
	
}

void UGrabber::Grab()
{

	//UE_LOG(LogTemp, Warning, TEXT("Grab pressed"))

	///LINE TRACE and see if we can reach any actors with physics body collision channel set
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();//gets the mesh
	auto ActorHit = HitResult.GetActor();

	///if we hit something, then attach a physics handle
	if (ActorHit)
	{
		//attach physics handle
		if (!PhysicsHandle) { return; }//if its not assigned to anything, dont go to next line (woudld crash)
		PhysicsHandle->GrabComponentAtLocationWithRotation(
		ComponentToGrab,
		NAME_None, //no bones needed
		ComponentToGrab->GetOwner()->GetActorLocation(),
		ComponentToGrab->GetOwner()->GetActorRotation()
		);
	}
}


void UGrabber::Release()
{
	//UE_LOG(LogTemp, Warning, TEXT("Grab released"))
	//release physics handle
	PhysicsHandle-> ReleaseComponent();
}

/// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//if the physics handle is attached
	if (!PhysicsHandle) { return; }//if its not assigned to anything, dont go to next line (woudld crash)
	if(PhysicsHandle->GrabbedComponent)
	{
		//move the object that we're holding
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
		
	
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	///setup query parameters 
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());
	///line trace akaRay-casting out to reach distance
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		GetReachLineStart(),
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	///see what we hit
	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		//UE_LOG(LogTemp, Warning, TEXT("Line Trace hit: %s"), *(ActorHit->GetName()))

	}

	return HitResult;
}

FVector UGrabber::GetReachLineEnd()
{
	///get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);
	
	return PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;
}

FVector UGrabber::GetReachLineStart()
{
	///get player viewpoint this tick
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewPointLocation, OUT PlayerViewPointRotation);

	return PlayerViewPointLocation;
}