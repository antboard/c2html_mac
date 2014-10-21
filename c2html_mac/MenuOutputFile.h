#pragma once
#include <string>
#include <assert.h>
using namespace std;


class CMenuOutputFile
{
public:
	CMenuOutputFile(string& strSave);
	virtual ~CMenuOutputFile(void);
	void AddMenu(const string& strtag, string& strLink, char* cls);
private:
	string m_strSaveFile;
	string m_strSource;
};

