// Fill out your copyright notice in the Description page of Project Settings.


#include "ScatPlayer.h"

// Sets default values
AScatPlayer::AScatPlayer()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

    // Resize capsule collider to what is specified in parameters
    GetCapsuleComponent()->InitCapsuleSize(42.0f, 96.0f);
    //GetCapsuleComponent()->SetRelativeLocation(FVector(0.0f, 0.0f, 0.0f));
    GetMesh()->SetRelativeRotation(FRotator(0.0f, 270.0f, 0.0f));
	
    this->AutoPossessPlayer = EAutoReceiveInput::Player0;

    bUseControllerRotationPitch = false;
    bUseControllerRotationRoll = false;
    bUseControllerRotationYaw = false;

    GetCharacterMovement()->bOrientRotationToMovement = true; // Rotates character based on direction of movement
    GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f); // Sets rotation rate speed

    this->CameraTargetPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Camera Transform"));
    this->CameraTargetPoint->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));
    this->CameraTargetPoint->SetRelativeRotation(FRotator(-55.0f, 0.0f, 0.0f));
    this->CameraTargetPoint->SetupAttachment(RootComponent);

    this->CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
    this->CameraBoom->TargetArmLength = 1500.0f;
    this->CameraBoom->SetupAttachment(this->CameraTargetPoint);

    this->FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
    this->FollowCamera->SetupAttachment(this->CameraBoom, USpringArmComponent::SocketName);
    this->FollowCamera->bUsePawnControlRotation = false; // Ensures camera does not rotate relative to spring arm
}

// Called when the game starts or when spawned
void AScatPlayer::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScatPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    this->CameraTargetPoint->SetRelativeLocation(CameraDistanceOffset + GetCapsuleComponent()->GetRelativeLocation());
}

// Called to bind functionality to input
void AScatPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

    // Sets up movement
    PlayerInputComponent->BindAxis("MoveForward", this, &AScatPlayer::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AScatPlayer::MoveRight);
}

void AScatPlayer::MoveForward(float Axis)
{
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(Direction, Axis);
}

void AScatPlayer::MoveRight(float Axis)
{
    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(Direction, Axis);
}