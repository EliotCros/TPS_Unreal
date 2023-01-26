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
				start();
			}
		}

		//RUNNING

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
	return false if at least a target is alive
*/
bool ATargetManager::testTarget(){
	for (size_t i = 0; i < targetList.Num(); i++) {

		if (!targetList[i]->isDead) return true;
	}
	return false;
}

bool ATargetManager::isFinished()
{
	return finished;
}

int ATargetManager::targetCount(){
	if (parentManager == nullptr) {
		return targetList.Num();
	}
	else {
		return parentManager->targetCount() + targetList.Num();
	}
}

void ATargetManager::reset() {
	for (size_t i = 0; i < targetList.Num(); i++) {
		targetList[i]->reset();
	}
	if (parentManager != nullptr) {
		parentManager->reset();
	}
}

