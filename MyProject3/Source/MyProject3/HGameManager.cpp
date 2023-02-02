// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "HGameManager.h"
#include "Subsystems/PanelExtensionSubsystem.h"
#include "Blueprint/UserWidget.h"
#include <math.h>



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

	PointInstance = CreateWidget<UUserWidget>(GetWorld(), Point);
	PointInstance->AddToViewport();

	TimerInstance = CreateWidget<UUserWidget>(GetWorld(), timer);
	TimerInstance->AddToViewport();

	score = Cast<Uscore>(PointInstance);
	time = Cast<Utimer>(TimerInstance);


	score->SetPoint(pointCount);
	time->SetTime(elapsedTime);

	start();
}

// Called every frame
void AHGameManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (runTimer) {
		elapsedTime += DeltaTime;
	}
	if (lastManager != nullptr) {
		if (lastManager->finished) {


			/******************************END OF GAME****************************/
			displayScore();
		}
	}
	

	


	time->SetTime((int)elapsedTime);
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
}

void AHGameManager::getPoint(int point){
	pointCount += point;
	score->SetPoint(pointCount);

}

