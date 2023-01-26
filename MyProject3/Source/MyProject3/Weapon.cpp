#include "Weapon.h"

// Sets default values for this component's properties
UWeapon::UWeapon()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWeapon::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWeapon::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UWeapon::ChangeToWeapon1() {
	 currentAmmo = 180;
	 maxAmmo = 180;
	 currentClip = 30;
	 maxClip = 30;
	 fireRate = 0.2f;
	 weaponType = 1;
}

void UWeapon::ChangeToWeapon2() {

	currentAmmo = 36;
	maxAmmo = 36;
	currentClip = 6;
	maxClip = 6;
	fireRate = 0.8f;
	weaponType = 2;

}
