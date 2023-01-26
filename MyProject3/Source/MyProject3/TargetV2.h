// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyInterfaceShootable.h"
#include "Kismet/GameplayStatics.h"
#include "TargetV2.generated.h"


UCLASS()
class MYPROJECT3_API ATargetV2 : public AActor, public IMyInterfaceShootable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATargetV2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ProcessEvent_Implementation(FName Name, float Float) override;

	UFUNCTION()
		void killTarget();
	UFUNCTION()
		void reset();

	UFUNCTION()
		void raise();
	UFUNCTION()
		void lower();
	UFUNCTION()
		void Fallen();
	UFUNCTION()
		void emitPoint();

	bool isMoving = false;
	bool raised = false;
	bool fallen = false;
	bool isDead = false;

	//Raise
	bool raising = false;
	bool lowering = false;
	float startHeight;
	float targetHeight = 0;
	UPROPERTY(EditAnywhere)
		float raisedHeight = 50.0f;
	UPROPERTY(EditAnywhere)
		float RaisingSpeed = 90.0f;

	//Rotate
	bool isRotating = false;
	float startRot;
	float targetRotation = 0;
	UPROPERTY(EditAnywhere)
		float FallingAngle = 90.0f;
	UPROPERTY(EditAnywhere)
		float RotatingSpeed = 90.0f;

	UPROPERTY(EditAnywhere)
		int pointVal = 1;

};
