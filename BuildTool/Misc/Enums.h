#pragma once

enum class TaskType // �ϴ� ��� ����
{
	TT_LIB =0,
	TT_DLL,
	TT_GEN,
	END,
};

enum class PathType
{
	PT_BUILDTOOLEXE =0,
	PT_SOLUTION,
	PT_PROJECT,
	PT_ENGINEROOT,
	PT_OUTPUT,
	END,
};