// Fill out your copyright notice in the Description page of Project Settings.


#include "BvC_Target.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABvC_Target::ABvC_Target()
{

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(Mesh);

}

//Starting loop for += using the BP version of addition
void ABvC_Target::StartTestIterations(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		 StartSecondLoop(i);
	}
}
//Second loop for += using the BP version of addition
void ABvC_Target::StartSecondLoop(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		Result = UKismetMathLibrary::Add_IntInt(Result, 1);
	}
}

//Starting loop for using the increment version of addition
void ABvC_Target::StartTestIterationsPlusPlus(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		StartSecondLoop(i);
	}
}
//Second loop for using the increment version of addition
void ABvC_Target::StartSecondLoopPlusPlus(int InLastIndex)
{
	for (int i = 1; i <= InLastIndex; i++)
	{
		Result++;
	}
}
