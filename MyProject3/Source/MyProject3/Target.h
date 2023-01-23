// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Engine/GameEngine.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Target.generated.h"

UCLASS()
class MYPROJECT3_API ATarget : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATarget();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void killTarget();

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* StaticMeshComp;

	UFUNCTION()
		void raise();
	UFUNCTION()
		void lower();

};
