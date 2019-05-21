// Adam's Copyright 2019

#include "PositionReporter.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReporter::UPositionReporter()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReporter::BeginPlay()
{
	Super::BeginPlay();

	// ...runs once
	//Log, Warning, Error
	FString ObjectName = GetOwner()->GetName();
	FString ObjectPos = GetOwner()->GetTransform().GetLocation().ToString();//  "X=something, Y=something, Z=something";
	///UE_LOG(LogTemp, Warning, TEXT("%s is at %s!"), *ObjectName, *ObjectPos);
	
}


// Called every frame
void UPositionReporter::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...runs every frame
}

