// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPawn.h"



// Sets default values
AMyPawn::AMyPawn()
{
	AutoPossessPlayer = EAutoReceiveInput::Player0;
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	//Create our components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	StaticMeshComp = CreateDefaultSubobject <UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	OurCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));

	StaticMeshComp->SetupAttachment(RootComponent);
	CameraSpringArm->SetupAttachment(StaticMeshComp);
	OurCamera->SetupAttachment(CameraSpringArm, USpringArmComponent::SocketName);

	//Setting Default Variables and Behavior of the SpringArmComponent
	CameraSpringArm->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 50.0f), FRotator(-60.0f, 0.0f, 0.0f));
	CameraSpringArm->TargetArmLength = 400.f;
	CameraSpringArm->bEnableCameraLag = true;
	CameraSpringArm->CameraLagSpeed = 3.0f;

}

// Called when the game starts or when spawned
void AMyPawn::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, GetActorForwardVector().ToString());
	if (!CurrentVelocity.IsZero()){
		FVector NewLocation = GetActorLocation();
		NewLocation += GetActorForwardVector() * (CurrentVelocity.X * DeltaTime);
		NewLocation += GetActorRightVector() * (CurrentVelocity.Y * DeltaTime);
		SetActorLocation(NewLocation);
	}




	//Rotate our actor's yaw, which will turn our camera because we're attached to it
	{
		FRotator NewRotation = GetActorRotation();
		NewRotation.Yaw += CamVelocity.Yaw;
		SetActorRotation(NewRotation);
	}
	//Rotate our camera's pitch, but limit it so we're always looking downward
	{
		FRotator NewRotation = CameraSpringArm->GetComponentRotation();
		NewRotation.Pitch = FMath::Clamp(NewRotation.Pitch + CamVelocity.Pitch, -120.0f, 0.0f);
		CameraSpringArm->SetWorldRotation(NewRotation);
	}







}

// Called to bind functionality to input
void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	//Movement
	PlayerInputComponent->BindAxis("MoveX", this, &AMyPawn::Move_XAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &AMyPawn::Move_YAxis);
	//Camera
	PlayerInputComponent->BindAxis("rotateX", this, &AMyPawn::Cam_YawAxis);
	PlayerInputComponent->BindAxis("rotateY", this, &AMyPawn::Cam_PitchAxis);



}

void AMyPawn::Move_XAxis(float AxisValue) {
	// Move at 100 units per second forward or backward
	CurrentVelocity.X = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Speed;
}

void AMyPawn::Move_YAxis(float AxisValue) {

	// Move at 100 units per second right or left
	CurrentVelocity.Y = FMath::Clamp(AxisValue, -1.0f, 1.0f) * Speed;
}


void AMyPawn::Cam_PitchAxis(float AxisValue) {
	// Move at 100 units per second forward or backward
	CamVelocity.Pitch = FMath::Clamp(AxisValue, -1.0f, 1.0f) * camSpeed;
}

void AMyPawn::Cam_YawAxis(float AxisValue) {
	// Move at 100 units per second right or left
	CamVelocity.Yaw = FMath::Clamp(AxisValue, -1.0f, 1.0f) * camSpeed;
}


