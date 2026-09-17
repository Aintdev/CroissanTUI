#pragma once
namespace ctui
{
	enum class RunStage
	{
		PreResize,
		DuringResizeFrame,
		PostResize,

		PreMeasure,
		PostMeasure,

		PreResolve,
		PostResolve,

		PreRender,
		PostRender,

		PreShutdown
	};
}
