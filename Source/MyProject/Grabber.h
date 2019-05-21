// Adam's Copyright 2019

#pragma once
#include "Runtime/Engine/Classes/Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYPROJECT_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	//how far ahead of the player can we reach in CM
	float Reach = 100.0f;

	UPhysicsHandleComponent* PhysicsHandle = nullptr;

	UInputComponent* InputComponent = nullptr;

	//ray-cast and grab what is in reach
	void Grab();

	//called when grab is released
	void Release();

	void FindPhysicsHandleComponent();

	void SetupInputComponent();

	//return hit for first physics body in reach
	const FHitResult GetFirstPhysicsBodyInReach();

	//Returns current start of reach line
	FVector GetReachLineStart();

	//Returns current end of reach line
	FVector GetReachLineEnd();


};
