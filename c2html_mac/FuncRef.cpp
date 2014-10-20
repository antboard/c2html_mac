#include "FuncRef.h"


CFuncRef::CFuncRef(int line, string& func, bool call)
	:m_nLine(line)
	,m_bCall(call)
	,m_srtFuncName(func)
{
}


CFuncRef::~CFuncRef(void)
{
}
