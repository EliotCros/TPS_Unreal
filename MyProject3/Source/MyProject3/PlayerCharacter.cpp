// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "PlayerCharacter.h"
#include "target.h"
#include "shoot.h"
#include "WeaponV3.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include <Kismet/GameplayStatics.h>


float RandomFloat(float a, float b) {
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our components
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	//shootComp = CreateDefaultSubobject<Ashoot>(TEXT("ShootComponent"));
	
	CameraSpringArm->SetupAttachment(RootComponent);
	OurCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	//Setting Default Variables and Behavior of the SpringArmComponent
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 400.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;

	CharacterMove = GetCharacterMovement();

	GetMesh()->GetSocketLocation("Muzzle_01");

	MuzzleLocation = GetMesh()->GetSocketLocation("Muzzle_01");

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &APlayerCharacter::WalkOnAmmo);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Weapon == nullptr) {
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("okkk")));
	}


	if (!isSPrinting && CharacterMove->MaxWalkSpeed > 600.0f) {
		CharacterMove->MaxWalkSpeed -= 50.0f;
	}

	if (isAim && OurCamera->FieldOfView >= 50.0f){
		OurCamera->FieldOfView -= 5.f;
	}

	if (!isAim && OurCamera->FieldOfView <= 90.0f){
		OurCamera->FieldOfView += 5.f;
	}


	//Rotate our camera's pitch, but limit it so we're always looking downward
	{
		FRotator NewRotation = CameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CamVelocity.Pitch, camAngleMin, camAngleMax);
		CameraSpringArm->SetWorldRotation(NewRotation);
		float p = NewRotation.Pitch;
	}

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveY", this, &APlayerCharacter::MoveRight);


	PlayerInputComponent->BindAxis("rotateX", this, &APlayerCharacter::AddControllerYawInput);
	PlayerInputComponent->BindAxis("rotateY", this, &APlayerCharacter::Cam_PitchAxis);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::StartJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APlayerCharacter::StopJump);



	PlayerInputComponent->BindAction("shoot", IE_Pressed, this, &APlayerCharacter::startShoot);
	PlayerInputComponent->BindAction("shoot", IE_Released, this, &APlayerCharacter::stopShoot);

	PlayerInputComponent->BindAction("sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction("sprint", IE_Released, this, &APlayerCharacter::StopSprint);

	PlayerInputComponent->BindAction("aim", IE_Pressed, this, &APlayerCharacter::StartAim);
	PlayerInputComponent->BindAction("aim", IE_Released, this, &APlayerCharacter::StopAim);
	PlayerInputComponent->BindAction("reload", IE_Released, this, &APlayerCharacter::reload);


	PlayerInputComponent->BindAction("weapon1", IE_Pressed, this, &APlayerCharacter::ChangeWeapon1);
	PlayerInputComponent->BindAction("weapon2", IE_Pressed, this, &APlayerCharacter::ChangeWeapon2);
	PlayerInputComponent->BindAction("weaponUp", IE_Pressed, this, &APlayerCharacter::ChangeWeaponUp);
	PlayerInputComponent->BindAction("weaponDown", IE_Pressed, this, &APlayerCharacter::ChangeWeaponDown);
}


void APlayerCharacter::MoveForward(float Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	//Get the forward vector
	FVector direction = FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::X);

	// We get the flattened forward look direction and normalize it
	direction = FVector(direction.X, direction.Y, 0.f).GetSafeNormal(); 
	AddMovementInput(direction, Value);
	
}

void APlayerCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);  
}

void APlayerCharacter::StartJump()
{
	bPressedJump = true;
}

void APlayerCharacter::StopJump()
{
	bPressedJump = false;
}

void APlayerCharacter::StartAim()
{
	isAim = true;
	CameraSpringArm->TargetArmLength = 170.0f;
}

void APlayerCharacter::StopAim()
{
	isAim = false;
	CameraSpringArm->TargetArmLength = 230.0f;
}



void APlayerCharacter::ChangeWeapon1() {
	Weapon->changeWeapon(0);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Shootgun")));
}

void APlayerCharacter::ChangeWeapon2() {
	Weapon->changeWeapon(1);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Rifle")));
}
void APlayerCharacter::ChangeWeaponUp() {
	Weapon->changeWeapon(true);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Shootgun")));
}

void APlayerCharacter::ChangeWeaponDown() {
	Weapon->changeWeapon(false);
	//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Rifle")));
}

void APlayerCharacter::Cam_PitchAxis(float AxisValue) {
	// Move at 100 units per second forward or backward
	CamVelocity.Pitch = FMath::Clamp(AxisValue, -1.0f, 1.0f) * camSpeed;
}

void APlayerCharacter::Cam_YawAxis(float AxisValue) {
	// Move at 100 units per second right or left
	CamVelocity.Yaw = FMath::Clamp(AxisValue, -1.0f, 1.0f) * camSpeed;
}


void APlayerCharacter::StartSprint(){
	CharacterMove->MaxWalkSpeed = 1200.0f;
	isSPrinting = true;

}

void APlayerCharacter::StopSprint(){
	isSPrinting = false;

}

#pragma region Shooting

/************************SHOOOTINNG****************/

void APlayerCharacter::shoot() {
	if (Weapon->canShoot()) {
		for (size_t i = 0; i < Weapon->GetNbBullet(); i++) {
			rayShoot();
		}
		Weapon->shooted();
		//Shake camera
		recoil();
	}
}

void APlayerCharacter::recoil() {
	GetWorld()->GetFirstPlayerController()->PlayerCameraManager->StartCameraShake(Weapon->getShake(), 0.5f);
}

void APlayerCharacter::startShoot() {
	isShooting = true;
	tryShoot();
}
void APlayerCharacter::stopShoot() {
	isShooting = false;
}

void APlayerCharacter::tryShoot() {
	if (isShooting) {
		if (GetWorld()->GetTimerManager().GetTimerRemaining(shootTimerHandle) == -1 || GetWorld()->GetTimerManager().GetTimerRemaining(shootTimerHandle) == 0) {

			shoot();
			startShootTimer();
		}
	}
}

void APlayerCharacter::startShootTimer() {
	GetWorld()->GetTimerManager().SetTimer(shootTimerHandle, this, &APlayerCharacter::tryShoot, Weapon->getFireRate(), false);
}
void APlayerCharacter::stopShootTimer() {
	GetWorld()->GetTimerManager().ClearTimer(shootTimerHandle);
}
/*******************************************************/
#pragma endregion

void APlayerCharacter::reload(){
	Weapon->reload();
}

void APlayerCharacter::WalkOnAmmo(AActor* MyOverlappedActor, AActor* OtherActor) {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%lld"), 1));

	if (IAmmoInterface * iAmmo = Cast<IAmmoInterface>(OtherActor)) {
		Weapon->getNewAmmo(iAmmo->getWeaponType(), iAmmo->ammoCount());
	}
}


FVector APlayerCharacter::recoil(FVector aim, float offset_aim) {

	FRotator rot = aim.Rotation();

	float r3 = RandomFloat(-offset_aim, offset_aim);
	rot.Yaw += r3;

	r3 = RandomFloat(-offset_aim, offset_aim);
	rot.Pitch += r3;

	return 	rot.Vector();
}


void APlayerCharacter::rayShoot() {
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.bIgnoreBlocks = false;
	CollisionParams.bIgnoreTouches = false;

	Startcam = OurCamera->GetComponentLocation();
	ForwardVectorCam = OurCamera->GetForwardVector();
	EndCam = (Startcam + ForwardVectorCam * 1000000.0f);
	ForwardVectorPlayer = GetActorForwardVector();
	Startplayer = GetMesh()->GetSocketLocation("Muzzle_01");
	
	if (GetWorld()->LineTraceSingleByChannel(camhit, Startcam, EndCam, ECC_WorldStatic, CollisionParams)) {
		/*
		if (camhit.GetActor()->GetClass()->ImplementsInterface(UMyInterfaceShootable::StaticClass())) {
			IMyInterfaceShootable::Execute_ProcessEvent(camhit.GetActor(), camhit.GetActor()->GetFName(), camhit.Distance);
		}*/
		ForwardAim = FVector(camhit.Location.X - Startplayer.X, camhit.Location.Y - Startplayer.Y, camhit.Location.Z - Startplayer.Z);
		FVector rc = recoil(ForwardAim, Weapon->getSpread());
		rc.Normalize();
		FVector hitpoint = Startplayer +  rc * 100000.0f;

		if (GetWorld()->LineTraceSingleByChannel(Playerhit, Startplayer, hitpoint, ECC_WorldStatic, CollisionParams)) {

			if (Playerhit.GetActor()->GetClass()->ImplementsInterface(UMyInterfaceShootable::StaticClass())) {
				IMyInterfaceShootable::Execute_ProcessEvent(Playerhit.GetActor(), Playerhit.GetActor()->GetFName(), Playerhit.Distance);
			}
		}
		DrawDebugLine(GetWorld(), Startplayer, hitpoint, FColor::Red, false, 10, 0, 1);
		FTransform tr;
		tr.SetLocation(Playerhit.Location);
		UGameplayStatics::SpawnEmitterAtLocation(OurCamera->GetWorld(), PShoot, tr, true);
	}



}