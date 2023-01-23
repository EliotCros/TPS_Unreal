// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "target.h"
#include "shoot.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h" 
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
	//shootComp = CreateDefaultSubobject<Ashoot>(TEXT("ShootComponent"));
	
	CameraSpringArm->SetupAttachment(RootComponent);
	OurCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	//Setting Default Variables and Behavior of the SpringArmComponent
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 400.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;


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



	PlayerInputComponent->BindAction("shoot", IE_Released, this, &APlayerCharacter::shoot);
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

void APlayerCharacter::Cam_PitchAxis(float AxisValue) {
	// Move at 100 units per second forward or backward
	CamVelocity.Pitch = FMath::Clamp(AxisValue, -1.0f, 1.0f) * camSpeed;
}

void APlayerCharacter::Cam_YawAxis(float AxisValue) {
	// Move at 100 units per second right or left
	CamVelocity.Yaw = FMath::Clamp(AxisValue, -1.0f, 1.0f) * camSpeed;
}


void APlayerCharacter::shoot() {
	FCollisionQueryParams CollisionParams;
	CollisionParams.AddIgnoredActor(this);

	Startcam = OurCamera->GetComponentLocation();
	ForwardVectorCam = OurCamera->GetForwardVector();
	EndCam = (ForwardVectorCam * 1000000.0f);
	ForwardVectorPlayer = GetActorForwardVector();




	if (ActorLineTraceSingle(camhit, Startcam, EndCam, ECC_WorldStatic, CollisionParams))
	{
		EndPlayer = camhit.Location;
	}
	if (ActorLineTraceSingle(Playerhit, Startplayer, EndPlayer, ECC_WorldStatic, CollisionParams))
	{
		try
		{
			ATarget* target = Cast<ATarget>(Playerhit.GetActor());
			target->killTarget();
		}
		catch (const std::exception&)
		{
			//pass
		}

	}
	DrawDebugLine(GetWorld(), Startcam, EndCam, FColor::Red, false, 1, 0, 1);


}