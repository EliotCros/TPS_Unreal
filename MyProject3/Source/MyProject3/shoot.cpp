// Fill out your copyright notice in the Description page of Project Settings.


#include "shoot.h"

// Sets default values
Ashoot::Ashoot()
{
	UWorld* World = GetWorld();
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Ashoot::BeginPlay()
{
	Super::BeginPlay();


	
	
}

// Called every frame
void Ashoot::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT(alacon));

	if (CameraRay == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("le seum"));
	}
	shoot();
}

void Ashoot::shoot() {
	/*FCollisionQueryParams CollisionParams;

	FHitResult camhit;
	FVector Startcam = camLocation;
	FVector ForwardVectorCam = camForward;
	FVector EndCam = ((ForwardVectorCam * 5000.f) + Startcam);

	DrawDebugLine(GetWorld(), Startcam, EndCam, FColor::Red, false, 1, 0, 1);
	if (ActorLineTraceSingle(camhit, Startcam, EndCam, ECC_WorldStatic, CollisionParams))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("The Component Being Hit is: %s"), *camhit.GetComponent()->GetName()));
	}
	FHitResult Playerhit;
	FVector Startplayer = GetActorLocation() + FVector(0, 0, 50);
	FVector ForwardVectorPlayer = GetActorForwardVector();
	FVector EndPlayer = camhit.Location;

	DrawDebugLine(GetWorld(), Startplayer, EndPlayer, FColor::Green, false, 1, 0, 1);

	if (ActorLineTraceSingle(Playerhit, Startplayer, EndPlayer, ECC_WorldStatic, CollisionParams))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("The Component Being Hit is: %s"), *Playerhit.GetComponent()->GetName()));
	}*/
}

void Ashoot::setcam(UCameraComponent* camera) {
	alacon = 1;
	CameraRay = camera;
}

