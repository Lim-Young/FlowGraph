// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors


#include "Nodes/Event/FlowNode_EventListenerBase.h"

UFlowNode_EventListenerBase::UFlowNode_EventListenerBase(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
#if WITH_EDITOR
	Category = TEXT("Event Listener");
	NodeDisplayStyle = FlowNodeStyle::Condition;
#endif

	InputPins.Empty();
	InputPins.Add(FFlowPin(TEXT("Start")));
	InputPins.Add(FFlowPin(TEXT("Stop")));

	OutputPins.Empty();
	OutputPins.Add(FFlowPin(TEXT("Triggered")));
	OutputPins.Add(FFlowPin(TEXT("Stopped")));
}

void UFlowNode_EventListenerBase::FinishTriggerEvent()
{
	if (bAutoStopListening)
	{
		AutoStopListeningCounter++;

		if (AutoStopListeningCounter >= AutoStopListeningLimit)
		{
			ExecuteInput(TEXT("Stop"));
			AutoStopListeningCounter = 0;
		}
	}
}

void UFlowNode_EventListenerBase::TriggerEventOutput()
{
	TriggerOutput(TEXT("Triggered"));
}

void UFlowNode_EventListenerBase::OnStartEventListener_Implementation()
{
}

void UFlowNode_EventListenerBase::OnStopEventListener_Implementation()
{
}

void UFlowNode_EventListenerBase::ExecuteInput(const FName& PinName)
{
	if (PinName == TEXT("Start"))
	{
		OnStartEventListener();
		bIsStopped = false;
	}
	else if (PinName == TEXT("Stop"))
	{
		TriggerOutput(TEXT("Stopped"), true);
		bIsStopped = true;
	}
}

void UFlowNode_EventListenerBase::OnLoad_Implementation()
{
	if (!bIsStopped)
	{
		TriggerInput(TEXT("Start"));
	}
}

void UFlowNode_EventListenerBase::Cleanup()
{
	Super::Cleanup();

	OnStopEventListener();
}

#if WITH_EDITOR
FString UFlowNode_EventListenerBase::GetStatusString() const
{
	return bIsStopped
		       ? FString::Printf(TEXT("Stopped"))
		       : (bAutoStopListening
			          ? FString::Printf(
				          TEXT("Auto Stop Listening (%d/%d)"), AutoStopListeningCounter, AutoStopListeningLimit)
			          : FString::Printf(TEXT("Listening")));
}
#endif
