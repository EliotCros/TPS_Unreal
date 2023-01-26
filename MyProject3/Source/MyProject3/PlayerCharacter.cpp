// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "target.h"
#include "shoot.h"
#include "Weapon.h"
#include "Math/UnrealMathUtility.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h" 
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;

 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Create our components
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	Weapon = CreateDefaultSubobject<UWeapon>(TEXT("weapon"));
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


}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//shoot();

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



	PlayerInputComponent->BindAction("shoot", IE_Pressed, this, &APlayerCharacter::shoot);
	PlayerInputComponent->BindAction("shoot", IE_Released, this, &APlayerCharacter::shootReleased);

	PlayerInputComponent->BindAction("sprint", IE_Pressed, this, &APlayerCharacter::StartSprint);
	PlayerInputComponent->BindAction("sprint", IE_Released, this, &APlayerCharacter::StopSprint);

	PlayerInputComponent->BindAction("aim", IE_Pressed, this, &APlayerCharacter::StartAim);
	PlayerInputComponent->BindAction("aim", IE_Released, this, &APlayerCharacter::StopAim);


	PlayerInputComponent->BindAction("weapon1", IE_Pressed, this, &APlayerCharacter::ChangeWeapon1);
	PlayerInputComponent->BindAction("weapon2", IE_Pressed, this, &APlayerCharacter::ChangeWeapon2);
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
	Weapon->ChangeToWeapon1();
}

void APlayerCharacter::ChangeWeapon2() {
	Weapon->ChangeToWeapon2();

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
void APlayerCharacter::shootReleased() {
	isShooting = false;
	GetWorld()->GetTimerManager().ClearTimer(shootTimerHandle);

}

void APlayerCharacter::shoot() {
	rayShoot();
	GetWorld()->GetTimerManager().SetTimer(shootTimerHandle, this, &APlayerCharacter::rayShoot, 0.2f, true);
}

FVector APlayerCharacter::recoil(FVector aim) {

	float offset = -offset_aim + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (offset_aim + offset_aim)));
	aim.X += offset;
	offset = -offset_aim + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (offset_aim + offset_aim)));
	aim.Z += offset;
	offset = -offset_aim + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (offset_aim + offset_aim)));
	aim.Y += offset;

	return aim;

}


void APlayerCharacter::rayShoot() {
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::SanitizeFloat(2));
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.bIgnoreBlocks = false;
	CollisionParams.bIgnoreTouches = false;

	Startcam = OurCamera->GetComponentLocation();
	ForwardVectorCam = OurCamera->GetForwardVector();
	EndCam = (ForwardVectorCam * 1000000.0f);
	ForwardVectorPlayer = GetActorForwardVector();
	Startplayer = GetMesh()->GetSocketLocation("Muzzle_01");
	
	if (GetWorld()->LineTraceSingleByChannel(Playerhit, Startcam, EndCam, ECC_WorldStatic, CollisionParams)) {

		if (Playerhit.GetActor()->GetClass()->ImplementsInterface(UMyInterfaceShootable::StaticClass())) {
			IMyInterfaceShootable::Execute_ProcessEvent(Playerhit.GetActor(), Playerhit.GetActor()->GetFName(), Playerhit.Distance);
		}
	}

	FVector hitpoint = recoil(Playerhit.Location);
	ForwardAim = FVector(hitpoint.X - Startplayer.X, hitpoint.Y - Startplayer.Y, hitpoint.Z - Startplayer.Z) * 1000.0f;

	if (GetWorld()->LineTraceSingleByChannel(Playerhit, Startplayer, ForwardAim, ECC_WorldStatic, CollisionParams)) {

		if (Playerhit.GetActor()->GetClass()->ImplementsInterface(UMyInterfaceShootable::StaticClass())) {
			IMyInterfaceShootable::Execute_ProcessEvent(Playerhit.GetActor(), Playerhit.GetActor()->GetFName(), Playerhit.Distance);
		}
	}
	DrawDebugLine(GetWorld(), Startplayer, ForwardAim, FColor::Red, false, 1, 0, 1);
}