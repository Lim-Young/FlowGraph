// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#include "AddOns/Predicate/FlowNodeAddOn_BoolPredicate.h"

#include "Nodes/FlowNode.h"

UFlowNodeAddOn_BoolPredicate::UFlowNodeAddOn_BoolPredicate()
{
#if WITH_EDITOR
	NodeDisplayStyle = FlowNodeStyle::AddOn_Predicate;
	Category = TEXT("Predicate");
#endif

	InputPins.Empty();
	InputPins.Add(FFlowPin(TEXT("InputBool"), FFlowPinTypeName(FFlowPinTypeNamesStandard::PinTypeNameBool)));
}

bool UFlowNodeAddOn_BoolPredicate::EvaluatePredicate_Implementation() const
{
	const FFlowDataPinResult_Bool InputBool = GetFlowNode()->TryResolveDataPinAsBool(TEXT("InputBool"));
	if (InputBool.Result == EFlowDataPinResolveResult::Success)
	{
		return InputBool.Value;
	}

	return false;
}

EFlowAddOnAcceptResult UFlowNodeAddOn_BoolPredicate::AcceptFlowNodeAddOnParent_Implementation(
	const UFlowNodeBase* ParentTemplate, const TArray<UFlowNodeAddOn*>& AdditionalAddOnsToAssumeAreChildren) const
{
	if (ParentTemplate->IsA<UFlowNodeAddOn>())
	{
		return EFlowAddOnAcceptResult::Reject;
	}

	bool bHasBoolPredicate = false;
	ParentTemplate->ForEachAddOn([&](const UFlowNodeAddOn& AddOn)
	{
		if (AddOn.IsA<UFlowNodeAddOn_BoolPredicate>())
		{
			bHasBoolPredicate = true;
			return EFlowForEachAddOnFunctionReturnValue::BreakWithSuccess;
		}
		return EFlowForEachAddOnFunctionReturnValue::Continue;
	});

	if (bHasBoolPredicate)
	{
		return EFlowAddOnAcceptResult::Reject;
	}

	return EFlowAddOnAcceptResult::Undetermined;
}

#if WITH_EDITOR
FText UFlowNodeAddOn_BoolPredicate::GetNodeTitle() const
{
	FString NodeTitle = Super::GetNodeTitle().ToString();

	if (bReverseResult)
	{
		NodeTitle += TEXT(" (Reverse)");
	}

	return FText::FromString(NodeTitle);
}
#endif
