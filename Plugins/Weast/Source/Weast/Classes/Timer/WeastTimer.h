#pragma once

#include "CoreMinimal.h"

#include "TickableEditorObject.h"

DECLARE_DELEGATE(FOnWeastTimerTick)

class FWeastTimer : public FTickableEditorObject/*, public FGCObject*/
{
public:
	FWeastTimer();
	FWeastTimer(FTimespan InThreshold);
	virtual ~FWeastTimer() override;

public:
	//START Overriding from FTickableEditorObject

	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;

	//END Overriding from FTickableEditorObject

	//START Overriding from FGCObject

	//virtual void AddReferencedObjects(FReferenceCollector& Collector) override;

	//END Overriding from FGCObject

	inline void SetThreshold(FTimespan InThreshold)
	{
		Threshold = InThreshold;
	}

	inline void SetIsTickable(bool IsTickable)
	{
		if(bIsTickable != IsTickable && IsTickable)
		{
			Now = FDateTime::Now();
		}
		bIsTickable = IsTickable;
	}

	void ListenOnWeastTimerTick(FOnWeastTimerTick InOnWeastTimerTick)
	{
		OnWeastTimerTick = InOnWeastTimerTick;
	}

	void Reset()
	{
		OnWeastTimerTick.Unbind();
		bIsTickable = false;
	}

private:
	FOnWeastTimerTick OnWeastTimerTick;
	FDateTime Now;
	FTimespan Threshold;
	bool bIsTickable;
};
