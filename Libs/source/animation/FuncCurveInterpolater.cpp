#include "animation/FuncCurveInterpolater.h"
#include "animation/Timeline.h"
#include "math/MathFunctionCurve.h"

namespace izanagi {
namespace animation {
	IZ_FLOAT CFuncCurveInterpolater::GetValue(const CTimeline& timeline)
	{
		IZ_FLOAT time = timeline.GetTime();
		IZ_FLOAT duration = timeline.GetDuration();

		IZ_FLOAT t = time / duration;

		IZ_FLOAT ret = GetValue(t);

		return ret;
	}

	IZ_FLOAT CFuncCurveInterpolater::GetValue(IZ_FLOAT t)
	{
		typedef IZ_FLOAT (*Func)(IZ_FLOAT, const SVector&);

		static Func funcs[] =
		{
			&math::CMathFunctionCurve::ComputeBezier,
			&math::CMathFunctionCurve::ComputeHermite,
			&math::CMathFunctionCurve::ComputeCatmullRom,
		};

		IZ_C_ASSERT(COUNTOF(funcs) == E_ANM_FUNC_CURVE_MODE_NUM);

		IZ_FLOAT ret = (*funcs[m_Mode])(t, m_Param);
		return ret;
	}
}	// namespace animation
}	// namespace izanagi