#include "scriptFile.h"
#include "ScriptLine.h"
#include "basedata.h"
#include "htmlfile.h"
#include "Word.h"
#include "nodeManageFile.h"

CScriptFile::CScriptFile(const char* pPath, const char* name)
:CNodeManageFile(pPath, name)
{

}

CScriptFile::~CScriptFile()
{
	vector<CScriptLine*>::iterator it = m_vLines.begin();
	while (it != m_vLines.end())
	{
		CScriptLine* pLine = *it;
		if (pLine)
		{
			delete pLine;
		}
		it++;
	}
}

bool CScriptFile::parse()
{
	CNodeManageFile::Read();
	ToLine(m_pData, m_len);
	delete m_pData;
	m_pData = NULL;

	bool bRet = true;
	bRet &= ParseLineCMT();
	bRet &= ParseString();
	return bRet;
}

void CScriptFile::ToLine(char* pbuf, unsigned long len)
{
	// 解析成行
	char* pLineStart = pbuf;
	unsigned long i = 0;
	while (i < len)
	{
		if (pbuf[i] == '\n')
		{
			pbuf[i] = 0;
			CScriptLine* pLine = new CScriptLine(pLineStart, (int)m_vLines.size()+1);
			if (pLine)
			{
				m_vLines.push_back(pLine);
			}
			pLineStart = &pbuf[i+1];
		}
		i++;
	}
}

void CScriptFile::Save()
{
    // 构造目录路径
    int x = strlen(CODE_PATH);
	bool bRet = true;
	string strHtmlFile(_T(OUTPUT_PATH));
    strHtmlFile += (m_strPath.c_str()+x);// 默认路径中减去磁盘源文件路径
	strHtmlFile += m_fileName;
	strHtmlFile += ".html";

    CHtmlFile* pHtmlFile = new CHtmlFile(strHtmlFile, m_strPath);

	unsigned int nLine = 1;
	// 文件名
	pHtmlFile->AddCFileName(m_fileName);
	int zIndex = (int)m_vLines.size()+10;
	vector<CScriptLine*>::iterator it = m_vLines.begin();
	while ((it != m_vLines.end()) && bRet)
	{
		CScriptLine* pLine = *it;
		if (pLine)
		{
			pLine->StartNewLine(pHtmlFile, zIndex--);
			bRet &= pLine->Save(pHtmlFile);
			pLine->EndNewLine(pHtmlFile);
		}
		nLine++;
		it++;
	}

	delete pHtmlFile;
	return ;
}

CWord* CScriptFile::GetAllNextWord()
{
	CWord* pWord = NULL;
	if (m_nCurLine < m_vLines.size())
	{
		CScriptLine* pLine = m_vLines[m_nCurLine];
		if (pLine)
		{
			pWord = pLine->GetWord(m_nCurWord++);
			if (pWord == NULL)
			{
				m_nCurWord = 0;
				m_nCurLine++;
				pWord = GetAllNextWord();
			}
		}
	}
	return pWord;
}

CWord* CScriptFile::GetLineNextWord()
{
	CWord* pWord = NULL;
	if (m_nCurLine < m_vLines.size())
	{
		CScriptLine* pLine = m_vLines[m_nCurLine];
		if (pLine)
		{
			pWord = pLine->GetWord(m_nCurWord++);
		}
	}
	return pWord;
}


CScriptLine* CScriptFile::GetNextLine()
{
	m_nCurLine++;
	m_nCurWord = 0;
	if (m_nCurLine < m_vLines.size())
	{
		return m_vLines[m_nCurLine];
	}
	else
		return NULL;
}

bool CScriptFile::ParseLineCMT()
{
	SetCurLine(0);
	CWord* pWord = NULL;

	do 
	{
		bool bCmt = false;
		while ((pWord = GetLineNextWord()) != NULL)
		{
			string& str = pWord->GetWord();
			if (str == "#")
			{
				bCmt = true;
			}
			if (bCmt)
			{
				pWord->SetAttrib(EWORD_COMMENT);
			}
		}
	} while (GetNextLine());
	return true;
}

bool CScriptFile::ParseString()
{
	SetCurLine(0);
	CWord* pWord = NULL;
	CWord* pLast = NULL;
	bool bString = false;

	while ((pWord = GetAllNextWord()) != NULL)
	{
		string& str = pWord->GetWord();
		if ((str == "\"") && pLast && (pLast->GetWord() != "\\"))
		{
			bString = !bString;	
			pWord->SetAttrib(EWORD_STRING);
		}
		if (bString)
		{
			pWord->SetAttrib(EWORD_STRING);
		}

		pLast = pWord;
	}

	SetCurLine(0);
	pWord = NULL;
	pLast = NULL;
	bString = false;

	while ((pWord = GetAllNextWord()) != NULL)
	{
		string& str = pWord->GetWord();
		if ((str == "\'") && pLast && (pLast->GetWord() != "\\"))
		{
			bString = !bString;	
			pWord->SetAttrib(EWORD_STRING);
		}
		if (bString)
		{
			pWord->SetAttrib(EWORD_STRING);
		}

		pLast = pWord;
	}

	return true;
}
