// Fill out your copyright notice in the Description page of Project Settings.
#include "TargetV2.h"


#include "TargetV2.h"
#include "HGameManager.h"

// Sets default values
ATargetV2::ATargetV2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	trajectory = CreateDefaultSubobject<USplineComponent>(TEXT("Spline Component"));
	trajectory->SetupAttachment(GetRootComponent());

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetupAttachment(trajectory);
}

// Called when the game starts or when spawned
void ATargetV2::BeginPlay()
{
	Super::BeginPlay();
	FRotator rot = GetActorRotation();

	startHeight = MeshComponent->GetRelativeTransform().GetLocation().Z;

	startRot= MeshComponent->GetRelativeTransform().Rotator().Roll;



	FOnTimelineFloat ProgressFunction;
	ProgressFunction.BindUFunction(this, TEXT("ProcessMovementTimeline"));
	MovementTimeline.AddInterpFloat(MovementCurve, ProgressFunction);

	FOnTimelineEvent OnTimelineFinishedFunction;
	OnTimelineFinishedFunction.BindUFunction(this, TEXT("OnEndMovementTimeline"));
	MovementTimeline.SetTimelineFinishedFunc(OnTimelineFinishedFunction);

	MovementTimeline.SetTimelineLengthMode(TL_LastKeyFrame);
	
	
}



void ATargetV2::ProcessEvent_Implementation(FName Name, float Float)
{
	killTarget();
}

// Called every frame
void ATargetV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (raising) {

		FVector Location = MeshComponent->GetRelativeTransform().GetLocation();

		Location.Z += RaisingSpeed * DeltaTime;
		if (Location.Z > startHeight + targetHeight) {

			raising = false;
			Location.Z = startHeight + targetHeight;
			if (onRail) {
				MovementTimeline.PlayFromStart();
			}
			

		}
		MeshComponent->SetRelativeLocation(Location);
	}
	if (lowering) {
		FVector Location = MeshComponent->GetRelativeTransform().GetLocation();
		Location.Z -= RaisingSpeed * DeltaTime;
		if (Location.Z < startHeight) {
			lowering = false;
			Location.Z = startHeight;

		}
		MeshComponent->SetRelativeLocation(Location);

	}

	if (isRotating) {
		FRotator rot = MeshComponent->GetRelativeTransform().Rotator();
		rot.Roll += RotatingSpeed * DeltaTime;

		if (rot.Roll < targetRotation) {
			rot.Roll = targetRotation;
		}
		MeshComponent->SetWorldRotation(rot);
	}


	//Curving
	if (!isDead && raised) {
		if (MovementCurve != nullptr && onRail) {
			if (MovementTimeline.IsPlaying()) {
				MovementTimeline.TickTimeline(DeltaTime);
			}
		}
	}
	

}



void ATargetV2::killTarget() {
	if (raised && !isDead) {
		Fallen();
		isDead = true;
		emitPoint();
	}
}


void ATargetV2::raise() {
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


//SPLINE

void ATargetV2::ProcessMovementTimeline(float Value){

	
	
	const float SplineLength = trajectory->GetSplineLength();

	const FVector CurrentSplineLocation = trajectory->GetLocationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);
	FRotator CurrentSplineRotation = trajectory->GetRotationAtDistanceAlongSpline(Value * SplineLength, ESplineCoordinateSpace::World);

	CurrentSplineRotation.Pitch = 0.f;
	//SetActorLocation(CurrentSplineLocation);
	//SetActorRotation(CurrentSplineRotation);
	MeshComponent->SetWorldLocationAndRotation(CurrentSplineLocation, CurrentSplineRotation);

	
}

void ATargetV2::OnEndMovementTimeline(){

	if (!playOnce){
		MovementTimeline.PlayFromStart();
	}
}