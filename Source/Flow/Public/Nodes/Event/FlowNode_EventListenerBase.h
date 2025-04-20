// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#pragma once

#include "CoreMinimal.h"
#include "Nodes/FlowNode.h"
#include "FlowNode_EventListenerBase.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable)
class FLOW_API UFlowNode_EventListenerBase : public UFlowNode
{
	GENERATED_UCLASS_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Event Listener")
	bool bAutoStopListening = true;

	// Automatic Stop Listening After Limited Attempts
	UPROPERTY(EditAnywhere, Category = "Event Listener", meta = ( EditCondition = "bAutoStopListening" ))
	int32 AutoStopListeningLimit = 1;

private:
	UPROPERTY(SaveGame)
	int32 AutoStopListeningCounter = 0;

	UPROPERTY(SaveGame)
	bool bIsStopped = false;

protected:
	UFUNCTION(BlueprintCallable, Category = "FlowNode|Event Listener")
	void FinishTriggerEvent();

	UFUNCTION(BlueprintCallable, Category = "FlowNode|Event Listener")
	void TriggerEventOutput();

	UFUNCTION(BlueprintNativeEvent)
	void OnStartEventListener();

	UFUNCTION(BlueprintNativeEvent)
	void OnStopEventListener();

	virtual void ExecuteInput(const FName& PinName) override;
	virtual void OnLoad_Implementation() override;
	virtual void Cleanup() override;

#if WITH_EDITOR
	virtual FString GetStatusString() const override;
#endif
};
