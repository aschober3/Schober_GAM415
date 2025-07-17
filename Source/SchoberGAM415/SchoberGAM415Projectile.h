// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SchoberGAM415Projectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS(config=Game)
class ASchoberGAM415Projectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	UProjectileMovementComponent* ProjectileMovement;
	
	// Static mesh component for the projectile's visible 3D model
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ballMesh;

	// Base material used for the projectile before any dynamic changes
	UPROPERTY(EditAnywhere)
		UMaterialInterface* baseMat;

	// Randomized color assigned to the projectile at runtime
	UPROPERTY()
		FLinearColor randColor;

	// Material to be applied to the projectile when fired or spawned
	UPROPERTY(EditAnywhere)
		UMaterialInterface* projMat;

	// Dynamic material instance used to apply runtime visual changes (e.g., color)
	UPROPERTY()
		UMaterialInstanceDynamic* dmiMat;

public:
	ASchoberGAM415Projectile();

protected:
	virtual void BeginPlay();

public:
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }
};

