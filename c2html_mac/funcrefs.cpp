#include "FuncRefs.h"
#include "basedata.h"

CFuncRefs::CFuncRefs(void)
{
}


CFuncRefs::~CFuncRefs(void)
{
}

void CFuncRefs::PushFuncRef(CFuncRef* p, bool call)
{
	if (call)
	{
		m_call.push_back(p);
	}
	else
	{
		m_bCall.push_back(p);
	}
}

void CFuncRefs::OutputString(string& str, bool call)
{
	int opCount = 0;
	bool b_del = false;
	if (call)
	{
		vector<CFuncRef*>::iterator it = m_call.begin();
		while (it != m_call.end())
		{
			CFuncRef* pRef = *it;
			if (pRef)
			{
				str += _T("{p:\"");
				str += pRef->GetPath();
				str += _T("\",f:\"");
				str += pRef->GetFileName();
				//str += _T("\",c:\"");
				//str += pRef->GetFuncName();
				str += _T("\",l:");
				string tmp;
				n2str(pRef->GetLineNum(), tmp);
				str += tmp;
				str += _T("},");
				b_del = true;
			}
			it++;
			opCount++;
			if (opCount > 10)
			{
				str += _T("{p:\"\", f:\"more...\",l:\"\"},");
				break;
			}
		}
	}
	else
	{
		vector<CFuncRef*>::iterator it = m_bCall.begin();
		while (it != m_bCall.end())
		{
			CFuncRef* pRef = *it;
			if (pRef)
			{
				str += _T("{p:\"");
				str += pRef->GetPath();
				str += _T("\",f:\"");
				str += pRef->GetFileName();
				//str += _T("\",c:\"");
				//str += pRef->GetFuncName();
				str += _T("\",l:");
				string tmp;
				n2str(pRef->GetLineNum(), tmp);
				str += tmp;
				str += _T("},");
				b_del = true;
			}
			it++;
			opCount++;
			if (opCount > 10)
			{
				str += _T("{p:\"\", f:\"more...\",l:\"\"},");
				break;
			}
		}
	}
	if (b_del)
	{
		str.pop_back();// É¾³ý×îºóµÄ¶ººÅ
	}
}
