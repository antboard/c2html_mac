#pragma once
#include "basedata.h"

#include <assert.h>
#include <string>
#include <map>

using namespace std;

class CKeyword
{
public:
	CKeyword(void);
	virtual ~CKeyword(void){};
public:
	BOOL IsKeyWord(const string& str)
	{
		map<string, int>::iterator it = m_mapKeyWord.find(str);
		if (it != m_mapKeyWord.end())
		{
			return it->second;
		}
		return 0;
	}
	void AddKeyWord(const string& str)
	{
		m_mapKeyWord[str] = TAGNEWKEYWORD;
	}
protected:
	/*static */CKeyword* m_pKeyword;
	map<string, int> m_mapKeyWord;
};

