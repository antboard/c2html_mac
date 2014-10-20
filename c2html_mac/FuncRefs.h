#pragma once
#include "FuncRef.h"
#include <vector>
using namespace std;

class CFuncRefs
{
public:
	CFuncRefs(void);
	virtual ~CFuncRefs(void);
	void PushFuncRef(CFuncRef* p, bool call);
	void OutputString(string& str, bool call);

	int GetCalls(){return (int)m_call.size();}
	int GetBeCalls(){return (int)m_bCall.size();}
private:
	vector<CFuncRef*> m_call;
	vector<CFuncRef*> m_bCall;
};

