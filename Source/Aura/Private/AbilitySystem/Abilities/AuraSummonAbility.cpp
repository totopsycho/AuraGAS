// Copyright Tryktel.


#include "AbilitySystem/Abilities/AuraSummonAbility.h"
#include "Kismet/KismetSystemLibrary.h"
#include "NavigationSystem.h"

TArray<FVector> UAuraSummonAbility::GetSpawnLocations()
{
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	const FVector Location = GetAvatarActorFromActorInfo()->GetActorLocation();
	const float DeltaSpread = SpawnSpread / NumMinions;

	const FVector LeftOfSpread = Forward.RotateAngleAxis(-SpawnSpread / 2.f, FVector::UpVector);
	TArray<FVector> SpawnLocations;
	for (int32 i = 0; i < NumMinions; i++)
	{
		const FVector Direction = LeftOfSpread.RotateAngleAxis(DeltaSpread * i, FVector::UpVector);
		const FVector ChosenSpawnLocation = Location + Direction * FMath::RandRange(MinSpawnDistance, MaxSpawnDistance);

		FNavLocation NavLoc;
		UNavigationSystemV1* MyNavSystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (bool bProjectedLocationValid = MyNavSystem->ProjectPointToNavigation(ChosenSpawnLocation, NavLoc))
		{
			SpawnLocations.Add(NavLoc.Location);
		}
		DrawDebugSphere(GetWorld(), NavLoc.Location, 12.f, 12, FColor::Green, false, 3.f);
	}
	return SpawnLocations;
}
