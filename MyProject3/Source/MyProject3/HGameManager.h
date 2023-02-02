// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Target.h"
#include "timer.h"
#include "ammo.h"
#include "TargetManager.h"
#include "GameFramework/Actor.h"
#include "score.h"
#include "HGameManager.generated.h"

UCLASS()
class MYPROJECT3_API AHGameManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHGameManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;



	UFUNCTION()
		void start();

	UFUNCTION()
		void reset();

	UFUNCTION()
		void displayScore();
	UFUNCTION()
		void getPoint(int point);
	
	UPROPERTY(EditAnywhere)
		ATargetManager* lastManager;
	

	int pointCount = 0;

	float elapsedTime = -1.0f;
	bool runTimer = false;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> Point;
	UUserWidget* PointInstance;

	UPROPERTY(EditAnywhere)
		Uscore* score;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> timer;
	UUserWidget* TimerInstance;

	UPROPERTY(EditAnywhere)
		Utimer* time;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UUserWidget> ammowidget;
	UUserWidget* ammoInstnace;

	UPROPERTY(EditAnywhere)
		Uammo* ammo;

};
	



