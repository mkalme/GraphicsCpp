#include "../../../../Header/Scene/Fog/Formula/FormulaFog.h"
#include "../../../../Header/Scene/Fog/Formula/FormulaParser.h"

FormulaFog::FormulaFog(std::string formula) {
	m_callStack = FormulaParser().Parse(formula);
	m_formula = formula;
}

void FormulaFog::GetColorAndIntensity(double t, Vec3f& color, double& intensity) {
	if (!Enabled || t < MinimumDistanceToEnable) {
		color = Vec3f(0);
		intensity = 0;
		return;
	}

	color = Color;
	intensity = m_callStack->GetValue(t);

	intensity = fmax(intensity, MinFogIntensity);
	intensity = fmin(intensity, MaxFogIntensity);
}

const std::string FormulaFog::GetFormula() {
	return m_formula;
}
