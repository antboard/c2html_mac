#pragma once

#include <string>
using namespace std;
class CFuncRef
{
public:
	CFuncRef(int line, string& func, bool call);
	virtual ~CFuncRef(void);
	void SetLink(string& str){m_strFileLink = str;}
	string& GetPath(){return m_strFileLink;}
	string& GetFileName(){return m_strFileName;}
	string& GetFuncName(){return m_srtFuncName;}

	void SetFileName(const string& file){m_strFileName = file;}
	int GetLineNum(){return m_nLine;}
	bool GetCall(){return m_bCall;}
private:
	string m_strFileLink;
	string m_strFileName;
	int m_nLine;
	string m_srtFuncName;
	bool m_bCall;// call = 1,becall = 0;
};

