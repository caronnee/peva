#ifndef ___ENUMS____
#define ___ENUMS____

enum Operation
{
	OperationPlus,
	OperationMinus,
	OperationMultiply,
	OperationDivide,
	OperationModulo,

	OperationLess,
	OperationLessEqual,
	OperationGreater,
	OperationGreaterEqual,
	OperationEqual,
	OperationNotEqual,

	OperationAnd,
	OperationOr,
	OperationNot,

	OperationBoolAnd,
	OperationBoolOr,
	OperationBoolNot
};

enum ObjectFeatures
{
	FeatureIsPlayer,
	FeatureIsWall,
	FeatureIsMissille,
	FeatureIsMoving,
	FeatureLocate,
	FeatureDirection,
	FeatureStep,
	FeatureShoot,
	FeatureHit,
	FeatureTurn,
	FeatureTurnL,
	FeatureTurnR,
	FeatureWait,
	FeatureTarget,
	FeatureSee
};

#endif
