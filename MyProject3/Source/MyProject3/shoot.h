// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Engine/GameEngine.h"

#include "shoot.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h" 
#include "GameFramework/SpringArmComponent.h"
//#include "ActorLineTrace.generated.h"
//#include "ConstructorHelpers.h"
#include "DrawDebugHelpers.h"
#include "Engine/GameEngine.h"

#include "shoot.generated.h"


UCLASS()
class MYPROJECT3_API Ashoot : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	Ashoot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void shoot();

	UPROPERTY(EditAnywhere)
		class UCameraComponent* CameraRay;

	void setcam(UCameraComponent* camera);

	

	FVector camLocation;
	FVector camForward;

};
