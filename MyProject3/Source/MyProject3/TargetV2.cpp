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

// Called every frame
void ATargetV2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATargetV2::ProcessEvent_Implementation(FName Name, float Float)
{
	UE_LOG(LogTemp, Warning, TEXT("Parameter (FName) : %s \nParameter (float) : %f"), *Name.ToString(), Float);

	//SetActorScale3D(FVector(GetActorScale.X * 1.05f));
}

