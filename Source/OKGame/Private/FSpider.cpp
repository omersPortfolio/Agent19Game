// Fill out your copyright notice in the Description page of Project Settings.


#include "FSpider.h"
#include "FSpiderAIController.h"
#include <Kismet/GameplayStatics.h>
#include "FCharacterBase.h"
#include <GameFramework/Actor.h>
#include <BehaviorTree/BehaviorTree.h>

// Sets default values
AFSpider::AFSpider()
{

}

//void AFSpider::MoveToWaypoints()
//{
//	if (EnemyAIController)
//	{
//		if (CurrentWaypoint <= Waypoints.Num())
//		{
//			for (AActor* Waypoint : Waypoints)
//			{
//				AFWaypoint* WaypointItr = Cast<AFWaypoint>(Waypoint);
//
//				if (WaypointItr)
//				{
//					if (WaypointItr->GetWaypointOrder() == CurrentWaypoint)
//					{
//						EnemyAIController->MoveToActor(WaypointItr, 5.0f, false);
//						CurrentWaypoint++;
//						break;
//					}
//				}
//			}
//		}
//		else
//		{
//			for (AActor* Waypoint : Waypoints)
//			{
//				AFWaypoint* WaypointItr = Cast<AFWaypoint>(Waypoint);
//
//				if (WaypointItr)
//				{
//					CurrentWaypoint = 1;
//					EnemyAIController->MoveToActor(WaypointItr, 5.0f, false);
//					break;
//				}
//			}
//
//		}
//	}
//}

//void AFSpider::ChasePlayer()
//{
//	AFCharacterBase* Player = Cast<AFCharacterBase>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
//
//	if (Player)
//	{
//		FVector Location = GetActorLocation();
//		FVector PlayerLocation = Player->GetActorLocation();
//		FVector Distance = (PlayerLocation - Location);
//		if (FVector::Distance(PlayerLocation, Location) <= 500.0f)
//		{
//			State = AIState::Chase;
//			EnemyAIController->MoveToActor(Player, 5.0f);
//		}
//		else
//			if (State == AIState::Chase)
//			{
//				GetWorldTimerManager().ClearTimer(TimerHandle);
//				State = AIState::Idle;
//				GetWorldTimerManager().SetTimer(TimerHandle, this, &AFSpider::MoveToWaypoints, 2.0f, false);
//				State = AIState::Patrol;
//			}
//	}
//
//}

