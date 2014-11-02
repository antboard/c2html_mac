#pragma once

#include "Word.h"

#include <vector>
#include <string>
using namespace std;

class CHtmlFile;
class CScriptLine
{
public:
	CScriptLine(char* pLineStart, int nLine);
	virtual ~CScriptLine(void);

	bool Save(CHtmlFile* html);
	void StartNewLine(CHtmlFile* html, int zIdx);
	void EndNewLine(CHtmlFile* html);

	// 获取下一个元素
	CWord* GetWord(unsigned int n);
	string GetClassName(EWORDTAG tag, int id);
private:
	int m_nLine;
	CWord* m_pStart;	// 当前行开始的字指针。
	vector<CWord*> m_vWords;
	vector<CWord*> m_vPadWords;
};

