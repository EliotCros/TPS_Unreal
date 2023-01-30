// Fill out your copyright notice in the Description page of Project Settings.


#include "HGameManager.h"

// Sets default values
AHGameManager::AHGameManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHGameManager::BeginPlay()
{
	Super::BeginPlay();
	Tags.Add(FName("GameManager"));
	start();
}

// Called every frame
void AHGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (runTimer) {
		elapsedTime += DeltaTime;
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(elapsedTime));
	}
	if (lastManager != nullptr) {
		if (lastManager->finished) {
			displayScore();
		}
	}
}

void AHGameManager::start(){
	elapsedTime = 0;
	runTimer = true;
}

void AHGameManager::reset(){
	pointCount = 0;
	if (lastManager != nullptr)
		lastManager->reset();
}

void AHGameManager::displayScore() {
	runTimer = false;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%lld"), pointCount));
}

void AHGameManager::getPoint(int point){
	pointCount += point;
}

