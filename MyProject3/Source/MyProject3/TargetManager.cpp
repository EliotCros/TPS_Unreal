// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetManager.h"

// Sets default values
ATargetManager::ATargetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATargetManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATargetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!finished) {

		if (!active) {
			//START
			if (parentManager == nullptr) {

				start();
			}else if (parentManager->isFinished()) {
				bool t = parentManager->isFinished();
				//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (t)?FString::Printf(TEXT("true")): FString::Printf(TEXT("false")));
				start();
			}
		}

		//RUNNING
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (targetList[i]->isDead) ? FString::Printf(TEXT("true")) : FString::Printf(TEXT("false")));

		if (!testTarget()) {

			finished = true;
			active = false;
		}
	}
}

void ATargetManager::start(){

	for (size_t i = 0; i < targetList.Num(); i++){
		targetList[i]->raise();
	}
	active = true;
}

/*
	return true if at least a target is alive
*/
bool ATargetManager::testTarget(){
	for (size_t i = 0; i < targetList.Num(); i++) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, (targetList[i]->isDead) ? FString::Printf(TEXT("true")) : FString::Printf(TEXT("false")));

		if (targetList[i]->isDead) return true;
	}
	return false;
}

bool ATargetManager::isFinished()
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Blocking Hit =: %s"), finished));
	return finished;
}

