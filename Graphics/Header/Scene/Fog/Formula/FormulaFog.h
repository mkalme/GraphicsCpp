#pragma once
#include "../Fog.h"
#include <string>
#include "CallStack.h"

class FormulaFog : public Fog
{
public:
	bool Enabled;
	Vec3f Color;
	
	double MinimumDistanceToEnable;
	double MinFogIntensity;
	double MaxFogIntensity;

	FormulaFog(std::string formula);

	void GetColorAndIntensity(double t, Vec3f& color, double& intensity) override;
	const std::string GetFormula();
private:
	CallStack* m_callStack;
	std::string m_formula;
};

