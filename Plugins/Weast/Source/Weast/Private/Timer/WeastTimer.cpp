
#include "Timer/WeastTimer.h"

#include "Common/WeastCommon.h"

#define LOCTEXT_NAMESPACE "WeastTimer"

FWeastTimer::FWeastTimer()
	: Now(FDateTime::Now())
	, Threshold(FTimespan::MaxValue())
	, bIsTickable(false)
{
	
}

FWeastTimer::FWeastTimer(FTimespan InThreshold)
	: Now(FDateTime::Now())
	, Threshold(InThreshold)
	, bIsTickable(false)
{
	
}

FWeastTimer::~FWeastTimer()
{
	Reset();
}

void FWeastTimer::Tick(float DeltaTime)
{
	if(FDateTime::Now() - Now > Threshold)
	{
		Now = FDateTime::Now();
		if(OnWeastTimerTick.IsBound())
		{
			OnWeastTimerTick.Execute();
		}
	}
}

bool FWeastTimer::IsTickable() const
{
	return bIsTickable;
}

TStatId FWeastTimer::GetStatId() const
{
	RETURN_QUICK_DECLARE_CYCLE_STAT(FWeastTimer, STATGROUP_Tickables);
}

//void FWeastTimer::AddReferencedObjects(FReferenceCollector& Collector)
//{
//	Collector.AddReferencedObject();
//}

#undef LOCTEXT_NAMESPACE
