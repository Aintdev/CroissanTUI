#pragma once
namespace ctui
{
	enum class RunStage
	{
		BeforeResize,
		DuringResizeFrame,
		AfterResize,

		BeforeMeasure,
		AfterMeasure,

		BeforeResolve,
		AfterResolve,

		BeforeRender,
		AfterRender
	};
}
