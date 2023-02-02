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
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(elapsedTime));
	}
	if (lastManager != nullptr) {
		if (lastManager->finished) {
			displayScore();
		}
	}
	float ok = elapsedTime * 100;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(ok));
	int ok2 = (int)ok % 100;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(ok2));
	float ok3 = (float)(ok - ok2) / 100;
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(ok3));

	float ok4 = (float)(int)elapsedTime + (float)ok2 / 100;
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(ok4));


	time->SetTime(ok4);
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
	score->SetPoint(pointCount);

}

