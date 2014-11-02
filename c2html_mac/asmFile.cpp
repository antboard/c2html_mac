#include "asmFile.h"
#include "AsmLine.h"
#include "Word.h"
#include "htmlfile.h"

CAsmFile::CAsmFile(const char* pPath, const char* name)
:CNodeManageFile(pPath, name)
{

}

CAsmFile::~CAsmFile()
{
	vector<CAsmLine*>::iterator it = m_vLines.begin();
	while (it != m_vLines.end())
	{
		CAsmLine* pLine = *it;
		if (pLine)
		{
			delete pLine;
		}
		it++;
	}
}

CWord* CAsmFile::GetAllNextWord()
{
	CWord* pWord = NULL;
	if (m_nCurLine < m_vLines.size())
	{
		CAsmLine* pLine = m_vLines[m_nCurLine];
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

CWord* CAsmFile::GetLineNextWord()
{
	CWord* pWord = NULL;
	if (m_nCurLine < m_vLines.size())
	{
		CAsmLine* pLine = m_vLines[m_nCurLine];
		if (pLine)
		{
			pWord = pLine->GetWord(m_nCurWord++);
		}
	}
	return pWord;
}

CAsmLine* CAsmFile::GetNextLine()
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

bool CAsmFile::parse()
{
	CNodeManageFile::Read();
	ToLine(m_pData, m_len);
	delete m_pData;
	m_pData = NULL;

	bool bRet = true;
	bRet &= ParseBlockCMT();
	bRet &= ParseLineCMT();
	bRet &= ParseKeyword();
	return bRet;
}

void CAsmFile::Save()
{
    // 构造目录路径
    int x = strlen(CODE_PATH);
	bool bRet = true;
	string strHtmlFile(_T(OUTPUT_PATH));
    strHtmlFile += (m_strPath.c_str()+x);// 默认路径中减去磁盘源文件路径
	strHtmlFile += m_fileName;
	strHtmlFile += ".html";

	//OutputDebugString(strHtmlFile.c_str());
	//OutputDebugString("\n");
	CHtmlFile* pHtmlFile = new CHtmlFile(strHtmlFile, m_strPath);


	unsigned int nLine = 1;
	// 文件名
	pHtmlFile->AddCFileName(m_fileName);
	int zIndex = (int)m_vLines.size()+10;
	vector<CAsmLine*>::iterator it = m_vLines.begin();
	while ((it != m_vLines.end()) && bRet)
	{
		CAsmLine* pLine = *it;
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


void CAsmFile::ToLine(char* pbuf, unsigned long len)
{
	// 解析成行
	char* pLineStart = pbuf;
	unsigned long i = 0;
	while (i < len)
	{
		if (pbuf[i] == '\n')
		{
			pbuf[i] = 0;
			CAsmLine* pLine = new CAsmLine(pLineStart, (int)m_vLines.size()+1);
			if (pLine)
			{
				m_vLines.push_back(pLine);
			}
			pLineStart = &pbuf[i+1];
		}
		i++;
	}
}

bool CAsmFile::ParseBlockCMT()
{
		// 扫描注释.
	SetCurLine(0);
	CWord* pWord = NULL;
	bool bCmt = false;
	do 
	{
		// 寻找 / *
		while ((pWord = GetAllNextWord()) != NULL)
		{
			string& str = pWord->GetWord();
			if (str == "/*")
			{
				bCmt = true;
				pWord->SetAttrib(EWORD_COMMENT);
				break;
			}
		}
		// 标记注释和结束符
		while ((pWord = GetAllNextWord()) != NULL)
		{
			string& str = pWord->GetWord();
			pWord->SetAttrib(EWORD_COMMENT);
			if (str == "*/")
			{
				bCmt = false;
				break;
			}
		}
	} while (pWord != NULL);
	return (bCmt == false);
}

bool CAsmFile::ParseLineCMT()
{
	SetCurLine(0);
	CWord* pWord = NULL;

	do 
	{
		bool bCmt = false;
		while ((pWord = GetLineNextWord()) != NULL)
		{
			string& str = pWord->GetWord();
			if (str == "@")
			{
				bCmt = true;
			}
			if (bCmt)
			{
				pWord->SetAttrib(EWORD_COMMENT);
			}
		}
	} while (GetNextLine());
	SetCurLine(0);

	do 
	{
		bool bCmt = false;
		while ((pWord = GetLineNextWord()) != NULL)
		{
			string& str = pWord->GetWord();
			if (str == "//")
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

bool CAsmFile::ParseKeyword()
{
	SetCurLine(0);
	CWord* pWord = NULL;

	do 
	{
		// bool bCmt = false;
		while ((pWord = GetLineNextWord()) != NULL)
		{
			if (pWord->GetAttrib() == EWORD_INIT)
			{
				pWord->SetAttrib(EWORD_KEYWORD);
				break;
			}
		}
	} while (GetNextLine());
	return true;
}

