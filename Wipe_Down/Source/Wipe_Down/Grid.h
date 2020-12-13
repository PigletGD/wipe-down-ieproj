// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ProceduralMeshComponent.h"
#include "Grid.generated.h"

UCLASS()
class WIPE_DOWN_API AGrid : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrid();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Add Dictionary for grid information holding here

private:
	void InitializeVariables();

	void CreateLine(FVector start, FVector end, float thickness, TArray<FVector>& vertices, TArray<int>& triangles);
	FVector CalculateVertexPosition(FVector position, FVector thicknessDirection, float halfThickness, bool isAdding);

	UMaterialInstanceDynamic* CreateMaterialInstance(FLinearColor color, float opacity);

	float GetGridWidth() const;
	float GetGridHeight() const;

	UPROPERTY(EditAnywhere) UProceduralMeshComponent* linesProceduralMesh;
	UPROPERTY(EditAnywhere) UProceduralMeshComponent* selectionProceduralMesh;

	UPROPERTY(EditAnywhere) int numRows;
	UPROPERTY(EditAnywhere) int numColumns;
	UPROPERTY(EditAnywhere) float tileSize;

	UPROPERTY(EditAnywhere) float lineThickness;
	UPROPERTY(EditAnywhere) FLinearColor  lineColor;
	UPROPERTY(EditAnywhere) float lineOpacity;

	UPROPERTY(EditAnywhere) FLinearColor  selectionColor;
	UPROPERTY(EditAnywhere) float selectionOpacity;

	UPROPERTY(EditAnywhere) UMaterial* gridMaterial;
	UMaterialInstanceDynamic* lineMaterialInstance;
	UMaterialInstanceDynamic* selectionMaterialInstance;
};
