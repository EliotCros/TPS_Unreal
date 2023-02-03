// Fill out your copyright notice in the Description page of Project Settings.


#include "TargetManager.h"

// Sets default values
ATargetManager::ATargetManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));

}

// Called when the game starts or when spawned
void ATargetManager::BeginPlay()
{
	Super::BeginPlay();
	Collider->OnComponentBeginOverlap.AddDynamic(this, &ATargetManager::OnBeginOverlap);

}

// Called every frame
void ATargetManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!finished) {
		
		if (!active && (!needTrigger || needTrigger && boxCollided)) {
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
	for (size_t i = 0; i < civilList.Num(); i++) {
		civilList[i]->raise();
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

void ATargetManager::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {

	if (parentManager == nullptr) {

		boxCollided = true;
	}
	else if (parentManager->isFinished()) {
		boxCollided = true;

	}
}
