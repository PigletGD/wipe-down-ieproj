// Fill out your copyright notice in the Description page of Project Settings.


#include "ScatPlayer.h"
#include "WipeDownGameInstance.h"

// Sets default values
AScatPlayer::AScatPlayer()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructed Scat Player"));

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

	//InitializeTower();
}

// Called when the game starts or when spawned
void AScatPlayer::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Begin Play Scat Player"));

	this->wipeDownGameMode = (AWipeDownGameMode*)GetWorld()->GetAuthGameMode();

	if (!this->wipeDownGameMode->IsA(AWipeDownGameMode::StaticClass())) {
		UE_LOG(LogTemp, Warning, TEXT("Not Wipe Down Game Mode: %s + %s"), *this->wipeDownGameMode->GetClass()->GetName(), *GetWorld()->GetAuthGameMode()->GetName());
		this->wipeDownGameMode = nullptr;
	}
	else UE_LOG(LogTemp, Warning, TEXT("Got Game Mode"));

	this->zLocation = 810;

	this->isWalking = false;

	this->buildModeOn = false;

	this->walkingSound->bLooping = true;
	this->walkingSound->Volume = 0;
	UGameplayStatics::PlaySound2D(this, walkingSound);

	//this->bgMusic->bLooping = true;
	//UGameplayStatics::PlaySound2D(this, bgMusic);
}

// Called every frame
void AScatPlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	this->CameraTargetPoint->SetRelativeLocation(CameraDistanceOffset + GetCapsuleComponent()->GetRelativeLocation());

	if (this->buildModeOn)
	{
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
				gridLocation.Z = zLocation;
				this->Spawned->SetActorLocation(gridLocation);
			}

			//this->Spawned->SetActorLocation(this->GetActorLocation());

			// Sets the selected tile to location regardless of whether mouse is on grid
			grid->SetSelectedTile(this->row, this->column);
		}
	}
	if((isMovingForward != 0 || isMovingSidewards != 0) && !isWalking)
	{
		walkingSound->Volume = 7;
		isWalking = true;
	}
	else if(isMovingForward == 0 && isMovingSidewards == 0 && isWalking)
	{
		walkingSound->Volume = 0;
		isWalking = false;
	}
}

// Called to bind functionality to input
void AScatPlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (PlayerInputComponent != nullptr)
	{
		Super::SetupPlayerInputComponent(PlayerInputComponent);

		// Sets up movement
		/*PlayerInputComponent->BindAxis("MoveForward", this, &AScatPlayer::MoveForward);
		PlayerInputComponent->BindAxis("MoveRight", this, &AScatPlayer::MoveRight);
		PlayerInputComponent->BindAxis("CamRotate", this, &AScatPlayer::RotateCamera);
        PlayerInputComponent->BindAction("Spawn", IE_Pressed, this, &AScatPlayer::Build);
        PlayerInputComponent->BindAction("ToggleBuild", IE_Pressed, this, &AScatPlayer::ToggleBuild);
        PlayerInputComponent->BindAction("CancelBuild", IE_Pressed, this, &AScatPlayer::CancelBuild);*/
	}

	APlayerController* PlayerController = this->GetWorld()->GetFirstPlayerController();
	PlayerController->bShowMouseCursor = true;
}

void AScatPlayer::MoveForward(float Axis)
{
	FRotator CamRotation = this->CameraTargetPoint->GetComponentTransform().Rotator();
	FRotator CamYawRotation(0, CamRotation.Yaw, 0);

    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector Direction = FRotationMatrix(CamYawRotation).GetUnitAxis(EAxis::X);
    AddMovementInput(Direction, Axis);
	this->isMovingForward = Axis;
}

void AScatPlayer::MoveRight(float Axis)
{
	FRotator CamRotation = this->CameraTargetPoint->GetComponentTransform().Rotator();
	FRotator CamYawRotation(0, CamRotation.Yaw, 0);

    const FRotator Rotation = Controller->GetControlRotation();
    const FRotator YawRotation(0, Rotation.Yaw, 0);

    const FVector Direction = FRotationMatrix(CamYawRotation).GetUnitAxis(EAxis::Y);
    AddMovementInput(Direction, Axis);
	this->isMovingSidewards = Axis;
}

void AScatPlayer::RotateCamera(float Axis) {
	FRotator CamRotation = this->CameraTargetPoint->GetComponentTransform().Rotator();
	
	this->CameraTargetPoint->SetRelativeRotation(FRotator(CamRotation.Pitch, CamRotation.Yaw + Axis, CamRotation.Roll));
	
}

void AScatPlayer::Build()
{
	if (this->buildModeOn)
	{
		if (Spawned == nullptr)
		{
			AGrid* grid = this->wipeDownGameMode->GetGrid();

			FVector gridLocation;
			grid->TileToGridLocation(gridLocation, this->row, this->column, true);

			FVector location = this->GetOwner()->GetActorLocation();
			FRotator rotation = this->GetOwner()->GetActorRotation();

			//if (Tower != nullptr)
			//	this->Spawned = GetWorld()->SpawnActor<AActor>(Tower, location, rotation);

			if (Tower != nullptr) {
				this->Spawned = GetWorld()->SpawnActor<AActor>(Tower->GetClass(), location, rotation);
				//this->Spawned->SetActorHiddenInGame(false);
				this->Spawned->SetActorTickEnabled(false);
				this->Spawned->SetActorEnableCollision(false);
			}
			//else UE_LOG(LogTemp, Warning, TEXT("Could not find"));
		}
		else if (HitResult.GetActor() != nullptr)
		{
			//
			AGrid* grid = this->wipeDownGameMode->GetGrid();
			UWipeDownGameInstance* gameInstance = Cast<UWipeDownGameInstance>(GetWorld()->GetGameInstance());

			UE_LOG(LogTemp, Warning, TEXT("Row: %d Col: %d"), this->row, this->column);

			if (!grid->TileOccupied(this->row, this->column) && gameInstance->GetMoney() >= Tower->towerPrice) {
				grid->SetTileOccupation(this->row, this->column, this->Spawned);
				this->Spawned->SetActorTickEnabled(true);
				this->Spawned->SetActorEnableCollision(true);
				((ATower*)(this->Spawned))->SetCoords(this->row, this->column);
				gameInstance->SpendMoney(Tower->towerPrice);
				UStaticMeshComponent* mesh = Cast<UStaticMeshComponent>(Spawned->GetDefaultSubobjectByName(TEXT("StaticMesh")));
				if (mesh == nullptr) mesh = Cast<UStaticMeshComponent>(Spawned->GetDefaultSubobjectByName(TEXT("BaseMesh")));
				ATower* temp = Cast<ATower>(Spawned);
				mesh->SetMaterial(0, temp->physicalMaterial);
				Spawned = nullptr;
				UGameplayStatics::PlaySound2D(this, buildSound);
				// UE_LOG(LogTemp, Warning, TEXT("Spawned"));
			}
			else {
				// UE_LOG(LogTemp, Warning, TEXT("Tile Occupied"));
				Spawned->Destroy();
			}
			//
			Spawned = nullptr;
		}
	}
}

void AScatPlayer::CancelBuild()
{
	if (this->buildModeOn && Spawned != nullptr)
	{
		Spawned->Destroy();
		Spawned = nullptr;
	}
}

void AScatPlayer::ToggleBuild()
{
	bool temp = true;

	if (this->wipeDownGameMode->GetGrid() == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("Grid is null"));
		temp = false;
	}

	if (temp) {
		AGrid* grid = this->wipeDownGameMode->GetGrid();
		this->buildModeOn = !this->buildModeOn;

		if (this->buildModeOn)
		{
			grid->SetActorHiddenInGame(false);

			if (this->Spawned != nullptr)
				this->Spawned->SetActorHiddenInGame(false);
		}
		else
		{
			grid->SetActorHiddenInGame(true);

			if (this->Spawned != nullptr)
				this->Spawned->SetActorHiddenInGame(true);
		}
	}
}

void AScatPlayer::ToggleShooting()
{
	this->Tower = this->Shooting;
}

void AScatPlayer::ToggleWall()
{
	this->Tower = this->Wall;
}

void AScatPlayer::ToggleBathBomb()
{
	this->Tower = this->BathBomb;
}