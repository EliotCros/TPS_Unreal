// Fill out your copyright notice in the Description page of Project Settings.


#include "AmmoCrate.h"

// Sets default values
AAmmoCrate::AAmmoCrate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Collider = CreateDefaultSubobject<USphereComponent>(FName("Collider"));

}

// Called when the game starts or when spawned
void AAmmoCrate::BeginPlay()
{
	Super::BeginPlay();
	//OnActorBeginOverlap.AddDynamic(this, &AAmmoCrate::WalkOnAmmo);
	Collider->OnComponentBeginOverlap.AddDynamic(this, &AAmmoCrate::OnBeginOverlap);

}

// Called every frame
void AAmmoCrate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

int AAmmoCrate::getAmmoCount(){
	return Count;
}

WeaponType AAmmoCrate::getWeaponType(){
	return ammoType;
}

void AAmmoCrate::WalkOnAmmo(AActor* MyOverlappedActor, AActor* OtherActor)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%lld"), 1));
}

void AAmmoCrate::OnBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%lld"), 2));
		APlayerCharacter* chara = Cast<APlayerCharacter>(OtherActor);
		if (chara != nullptr) {
			chara->WalkOnAmmo(Count, ammoType);
			Destroy();
		}


}


