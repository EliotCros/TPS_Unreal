// Fill out your copyright notice in the Description page of Project Settings.
#include "TargetV2.h"

#include "HGameManager.h"


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
	FVector Location = GetActorLocation();
	FRotator rot = GetActorRotation();

	startHeight = Location.Z;
	startRot= rot.Roll;
	
}



void ATargetV2::ProcessEvent_Implementation(FName Name, float Float)
{
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
	if (raised) {
		Fallen();
		isDead = true;
		emitPoint();
	}
}


void ATargetV2::raise() {
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("raise"));
	raised = true;
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

void ATargetV2::emitPoint(){
	TSubclassOf<AHGameManager> classToFind;
	classToFind = AHGameManager::StaticClass();
	TArray<AActor*> GM;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, GM);

	if (GM[0] != nullptr) {
		AHGameManager* g = Cast<AHGameManager>(GM[0]);
		g->getPoint(pointVal);
	}


}


void ATargetV2::reset(){
	FVector Location = GetActorLocation();
	Location.Z = startHeight;
	SetActorLocation(Location);
	FRotator rot = GetActorRotation();
	rot.Roll = startRot;
	SetActorRotation(rot);
}