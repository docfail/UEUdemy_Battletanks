// Doctor Fail 2018

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

class UProjectileMovementComponent;
class UStaticMeshComponent;
class UParticleSystemComponent;
class URadialForceComponent;


UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void LaunchProjectile(float);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComponent, FVector NormalImpulse, const FHitResult & Hit);

	void OnTimerExpired();

private:
	UProjectileMovementComponent* ProjectileMovement = nullptr;
	UPROPERTY(VisibleAnywhere, Category="Components")
	UStaticMeshComponent* CollisionMesh = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* LaunchBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	UParticleSystemComponent* ImpactBlast = nullptr;
	UPROPERTY(VisibleAnywhere, Category = "Components")
	URadialForceComponent* ExplosionForce = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = "Components")
	float DestroyDelay = 10.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage = 20.0f;
};
