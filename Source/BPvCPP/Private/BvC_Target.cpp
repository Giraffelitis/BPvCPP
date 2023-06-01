// Fill out your copyright notice in the Description page of Project Settings.


#include "BvC_Target.h"
#include "Components/SphereComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
ABvC_Target::ABvC_Target()
{

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	RootComponent = Mesh;
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetupAttachment(Mesh);

	MethodTextRender = CreateDefaultSubobject<UTextRenderComponent>("Method Text");
	MethodTextRender->SetupAttachment(Mesh);
	IterationsTextRender = CreateDefaultSubobject<UTextRenderComponent>("Iterations Text");
	IterationsTextRender->SetupAttachment(Mesh);
	TimeTextRender = CreateDefaultSubobject<UTextRenderComponent>("Time Text");
	TimeTextRender->SetupAttachment(Mesh);
	CalculationsTextRender = CreateDefaultSubobject<UTextRenderComponent>("Calculations Text");
	CalculationsTextRender->SetupAttachment(Mesh);
}

void ABvC_Target::BeginPlay()
{
	Super::BeginPlay();

	MethodTextRender->SetText(MethodText);
	IterationsTextRender->SetText(IterationsText);
}

void ABvC_Target::SetStartTime()
{
	StartTime = FPlatformTime::Seconds();
}

void ABvC_Target::CalculateElapsedTime()
{
	TimeElapsed =  FPlatformTime::Seconds() - StartTime;
}

//Collect results and update TextRenderComponents
void ABvC_Target::CollectResults()
{
	TotalCalculationsText = FText::AsNumber(NumOfCalculations);
	CalculationsTextRender->SetText(TotalCalculationsText);
	
	FString TempString = FString::SanitizeFloat(TimeElapsed);
	ElapsedTimeText = FText::FromString(TempString);
	TimeTextRender->SetText(ElapsedTimeText);
		
	UE_LOG(LogTemp, Warning, TEXT("@@@ BvC TestID: %d"), TestID);
	UE_LOG(LogTemp, Warning, TEXT("@@@ BvC Number of Planned Iterations: %d"), NumOfIterations);
	UE_LOG(LogTemp, Warning, TEXT("@@@ BvC Total Number of Calculations: %d"), NumOfCalculations);
	UE_LOG(LogTemp, Warning, TEXT("@@@ BvC Elapsed Time: %f"), TimeElapsed);
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
		NumOfCalculations = UKismetMathLibrary::Add_IntInt(NumOfCalculations, 1);
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
		NumOfCalculations++;
	}
}
