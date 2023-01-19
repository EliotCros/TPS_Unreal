// Fill out your copyright notice in the Description page of Project Settings.


#include "shoot.h"

// Sets default values
Ashoot::Ashoot()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	//Camera = World->GetFirstPlayerController()->PlayerCameraManager

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
	shoot();
}

void Ashoot::shoot() {
	
	FHitResult OutHit;
	FVector Start = GetActorLocation() + FVector(0, 0, 50);

	FVector ForwardVector = GetActorForwardVector();
	FVector End = ((ForwardVector * 500.f) + Start);
	FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 5);

	if (ActorLineTraceSingle(OutHit, Start, End, ECC_WorldStatic, CollisionParams))
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("The Component Being Hit is: %s"), *OutHit.GetComponent()->GetName()));
	}

}

