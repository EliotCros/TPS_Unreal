// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetV2.h"

// Sets default values
ATargetV2::ATargetV2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetV2::BeginPlay()
{
	Super::BeginPlay();
	
}



void ATargetV2::ProcessEvent_Implementation(FName Name, float Float)
{
	UE_LOG(LogTemp, Warning, TEXT("Parameter (FName) : %s \nParameter (float) : %f"), *Name.ToString(), Float);
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("target"));
	killTarget();
	//SetActorScale3D(FVector(GetActorScale.X * 1.05f));
}

// Called every frame
void ATargetV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (raising) {
		FVector Location = GetActorLocation();
		Location.Z += RaisingSpeed * DeltaTime;
		if (Location.Z > startHeight + targetHeight) {
			raising = false;
			Location.Z = startHeight + targetHeight;
		}
		SetActorLocation(Location);
	}
	if (lowering) {
		FVector Location = GetActorLocation();
		Location.Z -= RaisingSpeed * DeltaTime;
		if (Location.Z < startHeight) {
			lowering = false;
			Location.Z = startHeight;

		}
		SetActorLocation(Location);


	}

	if (isRotating) {
		FRotator rot = GetActorRotation();
		rot.Roll += RotatingSpeed * DeltaTime;

		if (rot.Roll > targetRotation) {
			rot.Roll = targetRotation;
		}

		SetActorRotation(rot);

	}

}


void ATargetV2::killTarget() {
	Fallen();
	isDead = true;
}

void ATargetV2::raise() {
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("raise"));

	raising = true;
	targetHeight = raisedHeight;
}

void ATargetV2::lower() {
	lowering = true;
	targetHeight = 0;

}

void ATargetV2::Fallen() {
	isRotating = true;
	targetRotation = FallingAngle;
}