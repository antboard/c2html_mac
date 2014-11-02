#include "AsmLine.h"
#include "Word.h"
#include "htmlfile.h"
#include "basedata.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

 bool TestBk(string& x);

CAsmLine::CAsmLine(char* pLineStart, int nLine)
	: m_pStart(NULL)
{
	// 设置行号
	m_nLine = nLine;
	int i = 0;
	CWord* pCurWord = NULL;
	string strWord,strBack;
	EWORDTAG ewtag = EWORD_INIT;
	bool bShow = false;
	while(pLineStart[i])
	{
		if ((pLineStart[i] == '\r') ||
			(pLineStart[i] == '\n'))
		{
			i++;
			continue;
		}
		EBYTETAG etag = getWordType(pLineStart[i]);
		// 符号
		switch (etag)
		{
		case EBYTE_TAB:
			strWord = _T("\t");
			ewtag = EWORD_SPACE;
			i++;
			bShow = false;
			break;
		case EBYTE_SPACE:
			strWord = _T(" ");
			ewtag = EWORD_SPACE;
			i++;
			bShow = false;
			break;
		case EBYTE_SYMBOL:// 数学符号--是不是考虑使用连续字符
			strWord = pLineStart[i++];
			strBack = strWord;
			while ((getWordType(pLineStart[i]) == EBYTE_SYMBOL))
			{
				strWord += pLineStart[i++];
				if (TestBk(strWord))
					strBack = strWord;
				else 
				{
					strWord = strBack;
					i--;
					break;
				}

			}
			// 			OutputDebugString(strWord.c_str());
			// 			OutputDebugString(_T("\r\n"));
			ewtag = EWORD_SYMBOL;
			bShow = true;
			break;
		case EBYTE_LETTER:
			strWord = pLineStart[i++];
			while ((getWordType(pLineStart[i]) == EBYTE_LETTER)
				|| (getWordType(pLineStart[i]) == EBYTE_NUM))
			{
				strWord += pLineStart[i++];
			}
			ewtag = EWORD_INIT;
			bShow = true;
			break;
		case EBYTE_NUM:// 数字
			strWord = pLineStart[i++];
			if ((pLineStart[i-1] == '0') && (pLineStart[i] == 'x') )
			{
				strWord += pLineStart[i++];
			}
			while ((getWordType(pLineStart[i]) == EBYTE_NUM)
				|| ((pLineStart[i] <= 'F') && (pLineStart[i] >= 'A'))
				|| ((pLineStart[i] <= 'f') && (pLineStart[i] >= 'a')))
			{
				strWord += pLineStart[i++];
			}
			ewtag = EWORD_NUM;
			bShow = true;
			break;
		default:
			/*OutputDebugString(((LPCSTR)&pLineStart[i]));*/
			i++;
			break;
		}
		CWord* pWord = new CWord(strWord);
		pWord->SetAttrib(ewtag);

		if (bShow)
		{
			m_vWords.push_back(pWord);
		} 
		else
		{
			m_vPadWords.push_back(pWord);
		}
		if (pCurWord)	pCurWord->SetNext(pWord);
		pCurWord = pWord;
		if (!m_pStart)	m_pStart = pCurWord;
	}
}


CAsmLine::~CAsmLine(void)
{
	// 释放下一级数据
	vector<CWord*>::iterator it = m_vWords.begin();
	while(it != m_vWords.end())
	{
		if (*it)
		{
			delete *it;
		}
		it++;
	}
	// 释放下一级数据
	it = m_vPadWords.begin();
	while(it != m_vPadWords.end())
	{
		if (*it)
		{
			delete *it;
		}
		it++;
	}
}

CWord* CAsmLine::GetWord(unsigned int n)
{
	assert(n >= 0);

	if (n < m_vWords.size()) 
	{
		return m_vWords[n]; 
	}
	else
	{
		n = (int)m_vWords.size()-1;
		return NULL;
	}
}

bool CAsmLine::Save(CHtmlFile* html)
{
	string strValue;
	EWORDTAG tag = EWORD_INIT;
	int nId = 0;
	//int nFuncCount = 0;// 函数索引在此处和输出xml的时候都会用到.暂时先不修改.在输出xml时也做一个索引.如果出现bug则统一计数
	CWord* pCurWord = m_pStart;

	if (m_vWords.empty())// 如果没有实质性内容。不用输出空格
	{
		return true;
	}

	// 分析连续的 类型相同的内容,输出
	vector<CWord*>::iterator it = m_vWords.begin();

	tag = ((CWord*)*it)->GetAttrib();
	nId = ((CWord*)*it)->GetKeyWordId();

	assert(pCurWord);
	// 输出所有前缀值
	while ((pCurWord != *it) && pCurWord)
	{
		assert(pCurWord);
		strValue += pCurWord->GetWord();
		pCurWord = pCurWord->GetNext();
	}
	strValue += pCurWord->GetWord();
	pCurWord = pCurWord->GetNext();

	it++;

	while (it != m_vWords.end())
	{
		CWord* pWord = *it;
		if (pWord)
		{
			if ((pWord->GetAttrib() != tag) || (pWord->GetKeyWordId() != nId))// 如果内容不相同
			{
				// 输出当前word之前的所有值
				while ((pCurWord != pWord) && pCurWord)
				{
					assert(pCurWord);
					strValue += pCurWord->GetWord();
					pCurWord = pCurWord->GetNext();
				}
				string strClass = GetClassName(tag, nId);
				if (0)//(tag == EWORD_FUNCTION)
				{
					//html->AddContent(strClass, strValue, m_nLine, nFuncCount++);
				}
				else
				{
					html->AddContent(strClass, strValue);
				}
				strValue = pCurWord->GetWord();
				pCurWord = pCurWord->GetNext();
				tag = pWord->GetAttrib();
				nId = pWord->GetKeyWordId();
			}
			else
			{
				// 输出所有值
				while ((pCurWord != pWord) && pCurWord)
				{
					assert(pCurWord);
					strValue += pCurWord->GetWord();
					pCurWord = pCurWord->GetNext();
				}
				strValue += pCurWord->GetWord();
				pCurWord = pCurWord->GetNext();
			}
		}
		it++;
	}
	if (strValue != "")
	{
		string strClass = GetClassName(tag, nId);
		html->AddContent(strClass, strValue);
	}

	return true;
}


void CAsmLine::StartNewLine(CHtmlFile* html, int zIdx)
{
	char buffer[65];
	string str;
	string strLine = _T("L");
    sprintf(buffer, "%d", m_nLine);
	string strShow(buffer);
	strLine += buffer;

	char cZIdx[65];
    sprintf(cZIdx, "%d", zIdx);
	string strZIdx(cZIdx);
	str = _T("<pre><a name=\"L");
	str += strShow;
	str +=_T("\"><span class=\"CodeMirror-linenumber\">");
	str += strShow;
	str += _T("&nbsp;&nbsp;</span></a>");
	html->Output(str);
}
void CAsmLine::EndNewLine(CHtmlFile* html)
{
	string str = _T("</pre>");
	html->Output(str);
}

string CAsmLine::GetClassName(EWORDTAG tag, int id)
{
	//static char keyword[3][10]={{_T("")},{_T("skeyword1")},{_T("skeyword2")}};
	string strTag = _T("");
	char num[64] = {0};
    sprintf(num, "%d", id);
	switch (tag)
	{
	case EWORD_KEYWORD: 
		// strTag = _T("skeyword");
		strTag = _T("cm-keyword");
		//strTag += num;
		return strTag;
	case EWORD_FUNCTION:
		// strTag = _T("sfunction");
		strTag = _T("cm-atom");
		return strTag;
	case EWORD_SYMBOL:
		// strTag = _T("ssymbol");
		strTag = _T("cm-operator");
		return strTag;
	case EWORD_FILE:
		// strTag = _T("sfile");
		strTag = _T("cm-string");
		return strTag;
	case EWORD_VARIABLE:
		// strTag = _T("svariable");
		strTag = _T("cm-variable");
		return strTag;
	case EWORD_STATIC_VALUE:
		// strTag = _T("sstaticvalue");
		return strTag;
	case EWORD_COMMENT:
		// strTag = _T("scomment");
		strTag = _T("cm-comment");
		return strTag;
	case EWORD_STRING:
		strTag = _T("cm-string");
		return strTag;
	case EWORD_VALUE:
		return strTag;
	case EWORD_SPACE:
		strTag = _T("");
		return strTag;
	case EWORD_NUM:
		strTag = _T("cm-number");
		return strTag;
	case EWORD_INIT:
		strTag = _T("cm-variable");
		return strTag;
	default:
		assert(0);
	}
	return strTag;
}
