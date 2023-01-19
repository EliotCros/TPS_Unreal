// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "shoot.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h" 
#include "GameFramework/SpringArmComponent.h"
//#include "ActorLineTrace.generated.h"
//#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameEngine.h"
#include "MyPawn.generated.h"

UCLASS()
class MYPROJECT3_API AMyPawn : public APawn
{
	GENERATED_BODY()


public:
	// Sets default values for this pawn's properties
	AMyPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UPROPERTY(EditAnywhere)
		class USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere)
		class UCameraComponent* OurCamera;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComp;

	UPROPERTY(EditAnywhere)
<<<<<<< HEAD
		Ashoot* shootComp;
	UPROPERTY(EditAnywhere)
		float Speed = 200.0f;
	UPROPERTY(EditAnywhere)
=======
		float Speed = 200.0f;
	UPROPERTY(EditAnywhere)
>>>>>>> b3691a7e43cde5ec5ee1b8f3eda5f37f43476cb0
		float camSpeed = 200.0f;
	UPROPERTY(EditAnywhere)
		float camAngleMax = 50.0f;
	UPROPERTY(EditAnywhere)
		float camAngleMin = -89.0f;



	//Input functions
	void Move_XAxis(float AxisValue);
	void Move_YAxis(float AxisValue);

	//Input Cam
	void Cam_PitchAxis(float AxisValue);
	void Cam_YawAxis(float AxisValue);

	//Input variables
	FVector CurrentVelocity;
	FRotator CamVelocity;
	bool onGround;


};
