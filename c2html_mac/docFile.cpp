#include "docFile.h"
#include "docline.h"
#include "htmlfile.h"

CDocFile::CDocFile(const char* pPath, const char* name)
: CNodeManageFile(pPath, name)
{

}

CDocFile::~CDocFile()
{
	vector<CDocLine*>::iterator it = m_vLines.begin();
	while (it != m_vLines.end())
	{
		CDocLine* pLine = *it;
		if (pLine)
		{
			delete pLine;
		}
		it++;
	}
	m_vLines.clear();
}

bool CDocFile::parse()
{
	CNodeManageFile::Read();
	ToLine(m_pData, m_len);
	delete m_pData;
	m_pData = NULL;
    return true;
}

void CDocFile::ToLine(char* pbuf, unsigned long len)
{
	// 解析成行
	char* pLineStart = pbuf;
	unsigned long i = 0;
	while (i < len)
	{
		if (pbuf[i] == '\n')
		{
			pbuf[i] = 0;
			CDocLine* pLine = new CDocLine(pLineStart, (int)m_vLines.size()+1);
			if (pLine)
			{
				m_vLines.push_back(pLine);
			}
			pLineStart = &pbuf[i+1];
		}
		i++;
	}
}

void CDocFile::Save()
{
    // 构造目录路径
    int x = strlen(CODE_PATH);
	string strHtmlFile(_T(OUTPUT_PATH));
    strHtmlFile += (m_strPath.c_str()+x);// 默认路径中减去磁盘源文件路径
    strHtmlFile += m_fileName;
	strHtmlFile += _T(".html");

	CHtmlFile* pHtmlFile = new CHtmlFile(strHtmlFile, m_strPath);


	unsigned int nLine = 1;
	// 文件名
	pHtmlFile->AddCFileName(m_fileName);
	int zIndex = (int)m_vLines.size()+10;
	bool bRet = true;
	vector<CDocLine*>::iterator it = m_vLines.begin();
	while ((it != m_vLines.end()) && bRet)
	{
		CDocLine* pLine = *it;
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