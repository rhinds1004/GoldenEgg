// Fill out your copyright notice in the Description page of Project Settings.

#include "FireProjectile.h"


int AFireProjectile::Prox_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	//don't hit non root components
	if (OtherComp != OtherActor->GetRootComponent())
	{
		return -1;
	}
	DoDamage(OtherActor, OtherComp);
	Destroy();
	return 0;
}

int AFireProjectile::DoDamage(AActor * OtherActor, UPrimitiveComponent * OtherComp)
{
	if (!OtherActor || !OtherComp)
	{
		return -1;
	}
	OtherActor->TakeDamage(Damage, FDamageEvent(KnockbackDamageType), NULL, this);
	return 0;
}

