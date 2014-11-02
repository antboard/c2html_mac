#pragma once
#include "basedata.h"

#include <vector>
using namespace std;

class CWord;
class CHtmlFile;
class CAsmLine
{
public:
	CAsmLine(char* pLineStart, int nLine);
	virtual ~CAsmLine(void);

	// 获取下一个元素 
	CWord* GetWord(unsigned int n);

	bool Save(CHtmlFile* html);
	void StartNewLine(CHtmlFile* html, int zIdx);
	void EndNewLine(CHtmlFile* html);

	string GetClassName(EWORDTAG tag, int id);
private:
	int m_nLine;
	CWord* m_pStart;	// 当前行开始的字指针。
	vector<CWord*> m_vWords;
	vector<CWord*> m_vPadWords;
};

