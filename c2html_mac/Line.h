#ifndef __LINE_H__
#define __LINE_H__

#include "basedata.h"
#include <vector>

using namespace std;

class CWord;
class CHtmlFile;
class CLine
{
public:
	CLine(char* pLineStart, int nLine);
	virtual ~CLine(void);

	bool IsEnd(unsigned int n){if (n >= m_vWords.size()-1)return true;else return false;}
	int GetLine(){return m_nLine;}
	BOOL Empty(){return m_vWords.empty();}
	int Size(){return (int)m_vWords.size();}

	// 获取下一个元素
	CWord* GetWord(unsigned int n);

// 	bool IsLonely(){return m_bLonely;}
// 	void ClearLonely(){m_bLonely = false;}

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

#endif