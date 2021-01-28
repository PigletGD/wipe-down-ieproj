// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"

// Sets default values
AGrid::AGrid()
{
	UE_LOG(LogTemp, Warning, TEXT("Constructed Grid"));

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Creating the actor components
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));

	this->linesProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("LinesProceduralMesh"));
	this->linesProceduralMesh->SetupAttachment(RootComponent);

	this->selectionProceduralMesh = CreateDefaultSubobject<UProceduralMeshComponent>(TEXT("SelectionProceduralMesh"));
	this->selectionProceduralMesh->SetupAttachment(RootComponent);

	// Initizalizing the grid's variables
	InitializeVariables();

	// Finding the Grid's Material
	static ConstructorHelpers::FObjectFinder<UMaterial> Material(TEXT("Material'/Game/Materials/M_Grid.M_Grid'"));
	if (Material.Object != NULL) { this->gridMaterial = (UMaterial*)Material.Object; UE_LOG(LogTemp, Warning, TEXT("Found")); }
	else UE_LOG(LogTemp, Warning, TEXT("Not Found"));

	// Creating material instances for both the grid and selection mesh
	this->lineMaterialInstance = CreateMaterialInstance(lineColor, lineOpacity);
	this->selectionMaterialInstance = CreateMaterialInstance(selectionColor, selectionOpacity);

	// Setting up necessary arrays to hold the vertices and triangles of the grid
	TArray<FVector> lineVertices;
	TArray<int> lineTriangles;
	
	// Creating the horizontal line geometry (one line created per row + 1 to account for the end)
	for (int i = 0; i <= this->numRows; i++)
	{
		// Gets important values for the line vector
		float lineStart = this->tileSize * i;
		float lineEnd = GetGridWidth();

		// Creates starting and ending point of the line
		FVector start = FVector(lineStart, 0.0f, 0.0f);
		FVector end = FVector(lineStart, lineEnd, 0.0f);

		// Calls function to create line
		CreateLine(start, end, this->lineThickness, lineVertices, lineTriangles);
	}

	// Creating the vertical line geometry (one line created per column + 1 to account for the end)
	for (int i = 0; i <= this->numColumns; i++)
	{
		float lineStart = this->tileSize * i;
		float lineEnd = GetGridHeight();

		FVector startLine = FVector(0.0f, lineStart, 0.0f);
		FVector endLine = FVector(lineEnd, lineStart, 0.0f);

		CreateLine(startLine, endLine, this->lineThickness, lineVertices, lineTriangles);
	}

	// Create procedural mesh for the grid
	linesProceduralMesh->CreateMeshSection(0, lineVertices, lineTriangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), false);
	linesProceduralMesh->SetMaterial(0, lineMaterialInstance);

	// Create selection mesh
	float halfTileSize = this->tileSize * 0.5f;
	FVector startSelection = FVector(0.0f, halfTileSize, 0.0f);
	FVector endSelection = FVector(this->tileSize, halfTileSize, 0.0f);
	TArray<FVector> selectionVertices;
	TArray<int> selectionTriangles;
	CreateLine(startSelection, endSelection, this->tileSize, selectionVertices, selectionTriangles);

	selectionProceduralMesh->SetVisibility(false);
	selectionProceduralMesh->CreateMeshSection(0, selectionVertices, selectionTriangles, TArray<FVector>(), TArray<FVector2D>(), TArray<FColor>(), TArray<FProcMeshTangent>(), false);
	selectionProceduralMesh->SetMaterial(0, selectionMaterialInstance);
}

// Called when the game starts or when spawned
void AGrid::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("Begin Play Grid"));

	this->SetActorHiddenInGame(true);
}

// Called every frame
void AGrid::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// General values once game starts
void AGrid::InitializeVariables()
{
	this->numRows = 20;
	this->numColumns = 20;
	this->tileSize = 200.0f;

	this->lineThickness = 30.0f;
	this->lineColor = FLinearColor(0.487467f, 0.256693f, 0.588542f, 1.0f);
	this->lineOpacity = 0.75f;

	this->selectionColor = FLinearColor(0.640625f, 0.408065f, 0.230225f, 1.0f);
	this->selectionOpacity = 0.5;
}

void AGrid::CreateLine(FVector start, FVector end, float thickness, TArray<FVector>& vertices,
	TArray<int>& triangles)
{
	float halfThickness = thickness * 0.5f;

	// Creates the direction of the line
	FVector normalized = end - start;
	normalized.Normalize(0.0001);
	FVector upVector = FVector(0.0f, 0.0f, 1.0f);
	FVector thicknessDirection = FVector::CrossProduct(normalized, upVector);

	// Creates two new triangles from the new vertices that will be created later
	int triangleIndexCount = vertices.Num();
	TArray<int> newIndexes = TArray<int>();

	newIndexes.Add(triangleIndexCount + 2);
	newIndexes.Add(triangleIndexCount + 1);
	newIndexes.Add(triangleIndexCount);
	newIndexes.Add(triangleIndexCount + 2);
	newIndexes.Add(triangleIndexCount + 3);
	newIndexes.Add(triangleIndexCount + 1);

	// Appends new triangles to existing triangles array
	triangles.Append(newIndexes);

	// Creates four new vertices
	TArray<FVector> newVertices = TArray<FVector>();

	newVertices.Add(CalculateVertexPosition(start, thicknessDirection, halfThickness, true));
	newVertices.Add(CalculateVertexPosition(end, thicknessDirection, halfThickness, true));
	newVertices.Add(CalculateVertexPosition(start, thicknessDirection, halfThickness, false));
	newVertices.Add(CalculateVertexPosition(end, thicknessDirection, halfThickness, false));

	// Appends new vertices to existing vertex array
	vertices.Append(newVertices);
}

FVector AGrid::CalculateVertexPosition(FVector position, FVector thicknessDirection, float halfThickness,
	bool isAdding)
{
	FVector result;

	if (isAdding) result = position + (thicknessDirection * halfThickness);
	else result = position - (thicknessDirection * halfThickness);

	return result;
}

UMaterialInstanceDynamic* AGrid::CreateMaterialInstance(FLinearColor color, float opacity)
{
	// Creates new material instance with retrieved material reference
	UMaterialInstanceDynamic* materialInstance = UMaterialInstanceDynamic::Create(this->gridMaterial, NULL);

	// Looks at available paramaters in the retrieved material and assigns them the proper values
	materialInstance->SetVectorParameterValue(FName(TEXT("Color")), color);
	materialInstance->SetScalarParameterValue(FName(TEXT("Opacity")), opacity);

	return materialInstance;
}

float AGrid::GetGridWidth() const { return this->numColumns * this->tileSize; }

float AGrid::GetGridHeight() const { return this->numRows * this->tileSize; }

bool AGrid::LocationToTile(FVector location, int& row, int& column)
{
	float actorLocationX = GetActorLocation().X;
	float nonFlooredX = (((location.X - actorLocationX) / this->GetGridHeight()) * this->numRows);
	row = (int)floor(nonFlooredX);

	float actorLocationY = GetActorLocation().Y;
	float nonFlooredY = (((location.Y - actorLocationY) / this->GetGridWidth()) * this->numColumns);
	column = (int)floor(nonFlooredY);

	return TileValid(row, column);
}

bool AGrid::TileValid(int row, int column)
{
  if (row >= 0 && row < numRows &&
      column >= 0 && column < numColumns) {
	  return true;
  }

  return false;
}

void AGrid::SetSelectedTile(int row, int column)
{
	FVector gridLocation;
	if(TileToGridLocation(gridLocation, row, column, false))
	{
		this->selectionProceduralMesh->SetVisibility(true);
		FVector newLocation = FVector(gridLocation.X, gridLocation.Y, GetActorLocation().Z);
		this->selectionProceduralMesh->SetWorldLocation(newLocation);
	}
	else
	{
		this->selectionProceduralMesh->SetVisibility(false);
	} 
}

bool AGrid::TileToGridLocation(FVector& gridLocation, int row, int column, bool isCentered)
{
	bool validity = TileValid(row, column);

	if (validity)
	{
		gridLocation.X = (row * this->tileSize) + GetActorLocation().X;
		gridLocation.Y = (column * this->tileSize) + GetActorLocation().Y;

		if (isCentered)
		{
			gridLocation.X += this->tileSize / 2.0f;
			gridLocation.Y += this->tileSize / 2.0f;
		}
	}

	return validity;
}

bool AGrid::TileOccupied(int row, int column)
{
	FString key = FString::Printf(TEXT("%d %d"), row, column);
	return this->BaseMap.Contains(key);
}

void AGrid::SetTileOccupation(int row, int column, AActor* actor)
{
	FString key = FString::Printf(TEXT("%d %d"), row, column);
	this->BaseMap.Add(key, actor);
}

void AGrid::RemoveTileOccupation(int row, int column)
{
	FString key = FString::Printf(TEXT("%d %d"), row, column);
	this->BaseMap.Remove(key);
}

AActor* AGrid::GetTileOccupation(int row, int column)
{
	FString key = FString::Printf(TEXT("%d %d"), row, column);
        if (TileOccupied(row, column)) {
	    return this->BaseMap[key];
        }

        return nullptr;
}