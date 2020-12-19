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
    this->CameraBoom->TargetArmLength = 1200.0f;
    this->CameraBoom->SetupAttachment(this->CameraTargetPoint);

    this->FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
    this->FollowCamera->SetupAttachment(this->CameraBoom, USpringArmComponent::SocketName);
    this->FollowCamera->bUsePawnControlRotation = false; // Ensures camera does not rotate relative to spring arm

	InitializeTower();
}

// Called when the game starts or when spawned
void AScatPlayer::BeginPlay()
{
	Super::BeginPlay();

	this->wipeDownGameMode = (AWipeDownGameMode*)GetWorld()->GetAuthGameMode();

	if (this->wipeDownGameMode != nullptr) {
          UE_LOG(LogTemp, Warning, TEXT("Found Game Mode"));
	}
    else {
      UE_LOG(LogTemp, Warning, TEXT("Game Mode Not Found"));
    }

    
}

// Called every frame
void AScatPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

        this->CameraTargetPoint->SetRelativeLocation(CameraDistanceOffset + GetCapsuleComponent()->GetRelativeLocation());

        // Selection Mode
		if (Spawned != nullptr)
		{
			// Grabs grid reference
			AGrid* grid = this->wipeDownGameMode->GetGrid();

			// Out variables for functions
			FVector location;
			FRotator rotation;
			FVector mousePos;
			FVector mouseRot;

			// Returns location and rotation based on viewpoint
			this->GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(location, rotation);

			// Grabs character controller
			APlayerController* PlayerController = this->GetWorld()->GetFirstPlayerController();

			//get mouse position onto world. out mousePos, out mouseRot
			PlayerController->DeprojectMousePositionToWorld(mousePos, mouseRot);

			// Calculates line for ray cast
			FVector lineTraceEnd = location + mouseRot * this->Distance;

			//get hitresult
			FCollisionQueryParams traceParams(FName(TEXT("tracequery")), false, this->GetOwner());
			FCollisionObjectQueryParams objectTypeParams(ECollisionChannel::ECC_WorldStatic);
			this->GetWorld()->LineTraceSingleByObjectType(HitResult, location, lineTraceEnd, objectTypeParams, traceParams);

			// Check if hit result aligns with grid
			
			bool valid = grid->LocationToTile(this->HitResult.Location, this->row, this->column);
			
			if (!valid || !HitResult.bBlockingHit)
			{
				// Despawns and hide selection and building if raycast does not hit grid
				this->Spawned->SetActorHiddenInGame(true);
				this->row = -90;
				this->column = -90;
			}
			else
			{
				// Shows selection grid and clamps building to center of tile if otherwise
				this->Spawned->SetActorHiddenInGame(false);
				FVector gridLocation;
				grid->TileToGridLocation(gridLocation, this->row, this->column, true);
				gridLocation.Z = this->Spawned->GetActorLocation().Z;
				this->Spawned->SetActorLocation(gridLocation);
			}

			// Sets the selected tile to location regardless of whether mouse is on grid
			grid->SetSelectedTile(this->row, this->column);
		}
}

// Called to bind functionality to input
void AScatPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (PlayerInputComponent != nullptr)
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		// Sets up movement
		PlayerInputComponent->BindAxis("MoveForward", this, &AScatPlayer::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AScatPlayer::MoveRight);
        PlayerInputComponent->BindAction("Spawn", IE_Pressed, this, &AScatPlayer::Build);
	}

	APlayerController* PlayerController = this->GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = true;
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

void AScatPlayer::Build()
{
	if (Spawned == nullptr)
	{
		FVector location = this->GetOwner()->GetActorLocation();
		FRotator rotation = this->GetOwner()->GetActorRotation();

		if (Tower != nullptr)
			this->Spawned = GetWorld()->SpawnActor<AActor>(Tower, location, rotation);
	}
	else if (HitResult.GetActor() != nullptr)
	{
		AGrid* grid = this->wipeDownGameMode->GetGrid();

		if (!grid->TileOccupied(this->row, this->column)) {
			grid->SetTileOccupation(this->row, this->column, this->Spawned);
			Spawned = nullptr;
			UE_LOG(LogTemp, Warning, TEXT("Spawned"));
		}
		else {
			UE_LOG(LogTemp, Warning, TEXT("Tile Occupied"));
		}
		
	}

	
}

void AScatPlayer::InitializeTower()
{
    static ConstructorHelpers::FObjectFinder<UBlueprint> TowerBlueprint(TEXT("Blueprint'/Game/Blueprints/Tower_BP.Tower_BP'"));
	if (TowerBlueprint.Object != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Found"));
        this->Tower = (UClass*)TowerBlueprint.Object->GeneratedClass;
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Could Not Find"));
	}
}