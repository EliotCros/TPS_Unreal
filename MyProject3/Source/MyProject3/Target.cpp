// Fill out your copyright notice in the Description page of Project Settings.


#include "Target.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	startHeight = GetActorLocation().Z;

	
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (isMoving) {
		FVector Location = GetActorLocation();
		Location.Z += RaisingSpeed * DeltaTime * ((lowering)?-1:1);
		
		if (Location.Z < startHeight) {
			lowering = false;
			isMoving = false;
			Location.Z = startHeight;
		}
		if (Location.Z > startHeight + targetHeight) {
			raising = false;
			isMoving = false;
			Location.Z = startHeight + targetHeight;
		}
		SetActorLocation(Location);
	}

	if (isRotating) {
		FRotator rot = GetActorRotation();
		rot.Roll += RotatingSpeed * DeltaTime ;

		if (rot.Roll > targetRotation) {
			rot.Roll = targetRotation;
		}

		SetActorRotation(rot);

	}

}

// Called to bind functionality to input
void ATarget::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ATarget::killTarget() {
	Fallen();
	isDead = true;
}

void ATarget::raise() {
	isMoving = true;
	raising = true;
	targetHeight = raisedHeight;
}

void ATarget::lower() {
	isMoving = true;
	lowering = true;
	targetHeight = 0;

}

void ATarget::Fallen() {
	isRotating = true;
	targetRotation = FallingAngle;
}


