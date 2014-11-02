#pragma once

#include <string>
using namespace std;

class CHtmlFile;
class CDocLine
{
public:
	CDocLine(char* pLineStart, int nLine);
	virtual ~CDocLine(void);

	bool Save(CHtmlFile* html);
	void StartNewLine(CHtmlFile* html, int zIdx);
	void EndNewLine(CHtmlFile* html);
private:
	int m_nLine;
	string m_pData;	// 当前行开始的字指针。
};

