// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AmmoInterface.h"
#include "WeaponV3.h"
#include "Components/SphereComponent.h"
#include "PlayerCharacter.h"
#include "AmmoCrate.generated.h"

UCLASS()
class MYPROJECT3_API AAmmoCrate : public AActor, public IAmmoInterface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAmmoCrate();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
	WeaponType ammoType = WeaponType::RIFLE;
	UPROPERTY(EditAnywhere)
	int Count = 10;

	virtual int getAmmoCount();
	virtual WeaponType getWeaponType();
	void WalkOnAmmo(AActor* MyOverlappedActor, AActor* OtherActor);


	USphereComponent* Collider;
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
