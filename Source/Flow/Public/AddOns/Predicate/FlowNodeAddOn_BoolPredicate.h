// Copyright https://github.com/MothCocoon/FlowGraph/graphs/contributors

#pragma once

#include "CoreMinimal.h"
#include "AddOns/FlowNodeAddOn.h"
#include "Interfaces/FlowPredicateInterface.h"
#include "FlowNodeAddOn_BoolPredicate.generated.h"

/**
 * Base predicate for boolean values
 */
UCLASS(MinimalApi, NotBlueprintable, meta = (DisplayName = "Bool Predicate"))
class UFlowNodeAddOn_BoolPredicate : public UFlowNodeAddOn, public IFlowPredicateInterface
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = "Predicate")
	bool bReverseResult = false;

public:
	UFlowNodeAddOn_BoolPredicate();

	// IFlowPredicateInterface
	virtual bool EvaluatePredicate_Implementation() const override;
	// --

	virtual EFlowAddOnAcceptResult AcceptFlowNodeAddOnParent_Implementation(const UFlowNodeBase* ParentTemplate,
	                                                                        const TArray<UFlowNodeAddOn*>&
	                                                                        AdditionalAddOnsToAssumeAreChildren)
	const override;

#if WITH_EDITOR
	virtual FText GetNodeTitle() const override;
#endif
};
