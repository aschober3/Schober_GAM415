// Fill out your copyright notice in the Description page of Project Settings.


#include "PerlinProcTerrain.h"
#include "ProceduralMeshComponent.h"
#include "KismetProceduralMeshLibrary.h"

// Sets default values
APerlinProcTerrain::APerlinProcTerrain()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create the procedural mesh component
	ProcMesh = CreateDefaultSubobject<UProceduralMeshComponent>("Procedural Mesh");

	// Attach the procedural mesh to the root component of the actor
	ProcMesh->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void APerlinProcTerrain::BeginPlay()
{
	Super::BeginPlay();

	// Generate vertex positions for the mesh
	CreateVertices();

	// Generate triangle indices to define mesh faces
	CreateTriangles();

	// Create a mesh section using the generated data
	ProcMesh->CreateMeshSection(sectionID, Vertices, Triangles, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>(), true);

	// Apply the selected material to the mesh
	ProcMesh->SetMaterial(0, Mat);
	
}

// Called every frame
void APerlinProcTerrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerlinProcTerrain::AlterMesh(FVector impactPoint)
{
	// Loop through all vertices in the mesh
	for (int i = 0; i < Vertices.Num(); i++)
	{
		// Convert impact point to local space relative to actor's location
		FVector tempVector = impactPoint - this->GetActorLocation();

		// Check if the vertex is within the radius of the impact point
		if (FVector(Vertices[i] - tempVector).Size() < radius)
		{
			// Move the vertex downward by the depth vector
			Vertices[i] = Vertices[i] - Depth;

			// Update the mesh section with the modified vertices
			ProcMesh->UpdateMeshSection(sectionID, Vertices, Normals, UV0, UpVertexColors, TArray<FProcMeshTangent>());
		}
	}
}

void APerlinProcTerrain::CreateVertices()
{
	// Loop through grid dimensions to generate vertices
	for (int X = 0; X <= XSize; X++)
	{
		for (int Y = 0; Y <= YSize; Y++)
		{
			// Generate height using Perlin noise and apply vertical scaling
			float Z = FMath::PerlinNoise2D(FVector2D(X * NoiseScale + 0.1, Y * NoiseScale + 0.1)) * ZMultiplier;

			// Debug message to show generated height value
			GEngine->AddOnScreenDebugMessage(-1, 999.0f, FColor::Yellow, FString::Printf(TEXT("Z %f"), Z));

			// Add vertex position to the list
			Vertices.Add(FVector(X * Scale, Y * Scale, Z));

			// Add corresponding UV coordinates
			UV0.Add(FVector2D(X * UVScale, Y * UVScale));
		}
	}
}

void APerlinProcTerrain::CreateTriangles()
{
	int Vertex = 0;

	// Loop through the grid to define triangles for each quad
	for (int X = 0; X <= XSize; X++)
	{
		for (int Y = 0; Y < YSize; Y++)
		{
			// First triangle of the quad
			Triangles.Add(Vertex);
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 1);

			// Second triangle of the quad
			Triangles.Add(Vertex + 1);
			Triangles.Add(Vertex + YSize + 2);
			Triangles.Add(Vertex + YSize + 1);

			// Move to the next vertex in the row
			Vertex++;
		}

		// Skip the extra vertex at the end of the row
		Vertex++;
	}
}

