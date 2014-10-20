#pragma once
#include "basedata.h"

class CWord
{
public:
	CWord(string& str){m_eWordTag = EWORD_INIT;m_word=str;m_nKeywordId=0;m_pNext=NULL;}
	void SetAttrib(EWORDTAG tag){m_eWordTag = tag;}
	EWORDTAG GetAttrib(){return m_eWordTag;}
	string& GetWord(){return m_word;}
	void OutPutDebugString();
	void SetKeyWordId(int nId){m_nKeywordId = nId;}
	int GetKeyWordId(){return m_nKeywordId;}
	CWord* GetNext(){return m_pNext;}
	void SetNext(CWord* pNext){m_pNext = pNext;}

	BOOL TestWord(char x){return (m_word.size() > 0) ? (m_word[0] == x) : FALSE;}// 用于测试注释的/和定义的#
protected:
private:
	EWORDTAG m_eWordTag;
	string m_word;
	int m_nKeywordId;
	CWord* m_pNext;
};