// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "targetV2.h"
#include "GameFramework/Actor.h"
#include "TargetManager.generated.h"

UCLASS()
class MYPROJECT3_API ATargetManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere)
		TArray<ATargetV2*> targetList;
	UPROPERTY(EditAnywhere)
		ATargetManager* parentManager;

	bool finished = false;
	bool active = false;

	void start();//raise the target
	bool testTarget();//test if there is at least one target alive
	bool isFinished();




};
