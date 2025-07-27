// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PerlinProcTerrain.generated.h"

class UProceduralMeshComponent;
class UMaterialInterface;

UCLASS()
class SCHOBERGAM415_API APerlinProcTerrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerlinProcTerrain();

	// Number of vertices in the X direction
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int XSize = 0;

	// Number of vertices in the Y direction
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		int YSize = 0;

	// Multiplier for height (Z-axis) based on noise
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Meta = (ClampMin = 0))
		float ZMultiplier = 1.0f;

	// Controls frequency of Perlin noise
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0))
		float NoiseScale = 1.0f;

	// Distance between each vertex
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float Scale = 0;

	// Controls how UVs are scaled across the mesh
	UPROPERTY(EditAnywhere, Meta = (ClampMin = 0.000001))
		float UVScale = 0;

	// Radius around the impact point for terrain modification
	UPROPERTY(EditAnywhere)
		float radius;

	// Depth offset applied during terrain deformation
	UPROPERTY(EditAnywhere)
		FVector Depth;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Material to apply to the procedural mesh
	UPROPERTY(EditAnywhere)
		UMaterialInterface* Mat;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Alters mesh geometry based on impact point
	UFUNCTION()
		void AlterMesh(FVector impactPoint);

private:
	// Procedural mesh component
	UProceduralMeshComponent* ProcMesh;

	// List of all mesh vertices
	TArray<FVector> Vertices;

	// Triangle indices for mesh construction
	TArray<int> Triangles;

	// UV coordinates for texturing
	TArray<FVector2D> UV0;

	// Normals for lighting calculations
	TArray<FVector> Normals;

	// Vertex colors for visual feedback or effects
	TArray<FColor> UpVertexColors;

	// ID for the mesh section being modified
	int sectionID = 0;

	// Generates vertices based on parameters
	void CreateVertices();

	// Generates triangle indices to form mesh surface
	void CreateTriangles();

};
