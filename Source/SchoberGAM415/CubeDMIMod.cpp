// Fill out your copyright notice in the Description page of Project Settings.


#include "CubeDMIMod.h"
#include "SchoberGAM415Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

// Sets default values
ACubeDMIMod::ACubeDMIMod()
{
    // Enable Tick function to run every frame
    PrimaryActorTick.bCanEverTick = true;

    // Create and initialize box collision component
    boxComp = CreateDefaultSubobject<UBoxComponent>("Box Component");

    // Create and initialize static mesh component for the cube
    cubeMesh = CreateDefaultSubobject<UStaticMeshComponent>("Cube Mesh");

    // Set root component and attach the mesh to the box component
    RootComponent = boxComp;
    cubeMesh->SetupAttachment(boxComp);
}

// Called when the game starts or when spawned
void ACubeDMIMod::BeginPlay()
{
    Super::BeginPlay();

    // Bind overlap event to the OnOverlapBegin function
    boxComp->OnComponentBeginOverlap.AddDynamic(this, &ACubeDMIMod::OnOverlapBegin);

    // Create a dynamic material instance from the base material
    if (baseMat)
    {
        dmiMat = UMaterialInstanceDynamic::Create(baseMat, this);
    }

    // Apply the dynamic material to the cube mesh
    if (cubeMesh)
    {
        cubeMesh->SetMaterial(0, dmiMat);
    }
}

// Called every frame
void ACubeDMIMod::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called when another actor overlaps with the box component
void ACubeDMIMod::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // Cast the overlapping actor to the player character class
    ASchoberGAM415Character* overlappedActor = Cast<ASchoberGAM415Character>(OtherActor);

    if (overlappedActor)
    {
        // Generate random RGB values
        float ranNumX = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
        float ranNumY = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);
        float ranNumZ = UKismetMathLibrary::RandomFloatInRange(0.f, 1.f);

        // Create a random color
        FLinearColor randColor = FLinearColor(ranNumX, ranNumY, ranNumZ, 1.f);

        if (dmiMat)
        {
            // Set the dynamic material color and darkness parameter
            dmiMat->SetVectorParameterValue("Color", randColor);
            dmiMat->SetScalarParameterValue("Darkness", ranNumX);

            // Spawn Niagara particle effect if assigned
            if (colorP)
            {
                UNiagaraComponent* particleComp = UNiagaraFunctionLibrary::SpawnSystemAttached(colorP, OtherComp, NAME_None, FVector(0.f), FRotator(0.f), EAttachLocation::KeepRelativeOffset, true);

                // Pass the random color to the Niagara system
                particleComp->SetNiagaraVariableLinearColor(FString("RandColor"), randColor);
            }
        }
    }
}


