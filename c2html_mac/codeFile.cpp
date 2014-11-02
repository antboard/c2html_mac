#include "codeFile.h"
#include "line.h"
#include "word.h"
#include "FuncRef.h"
#include "htmlfile.h"

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

map<string, CFuncRefs*> CCodeFile::m_mapFuncs;
pthread_mutex_t CCodeFile::m_map_mutex;

CCodeFile::CCodeFile(const char* pPath, const char* name)
:CNodeManageFile(pPath, name)
{

}

CCodeFile::~CCodeFile()
{
	vector<CFuncRef*>::iterator it = m_vFuncs.begin();
	while (it != m_vFuncs.end())
	{
		CFuncRef* pFunc = *it;
		if (pFunc)
		{
			delete pFunc;
		}
		it++;
	}

	clearLine();
	
	pthread_mutex_lock(&m_map_mutex);
	map<string, CFuncRefs*>::iterator iMap = m_mapFuncs.begin();
	while (iMap != m_mapFuncs.end())
	{
		CFuncRefs* ref = iMap->second;
		if (ref)
		{
			delete ref;
		}
		iMap++;
	}
	m_mapFuncs.clear();
	pthread_mutex_unlock(&m_map_mutex);
}

void CCodeFile::clearLine()
{
	vector<CLine*>::iterator itLine = m_vLines.begin();
	while (itLine != m_vLines.end())
	{
		CLine* pLine = *itLine;
		if (pLine)
		{
			delete pLine;
		}
		itLine++;
	}
}


bool CCodeFile::parse()
{
	CNodeManageFile::Read();
	ToLine(m_pData, m_len);
	delete m_pData;
	m_pData = NULL;

	bool bRet = true;
	// bRet &= ParseString();// 防止字符串内有注释,还有注释里面有引号...狗日的
	bRet &= ParseBlockCMT();
	bRet &= ParseLineDfn();

	// bRet &= ParseFunction();
	bRet &= ParseFunctionWithBrace();
	return bRet;
}

void CCodeFile::Save()
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
	vector<CLine*>::iterator it = m_vLines.begin();
	while ((it != m_vLines.end()) && bRet)
	{
		CLine* pLine = *it;
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
	clearLine();
	return ;
}

CWord* CCodeFile::GetAllNextWord()
{
	CWord* pWord = NULL;
	if (m_nCurLine < m_vLines.size())
	{
		CLine* pLine = m_vLines[m_nCurLine];
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

CWord* CCodeFile::GetLineNextWord()
{
	CWord* pWord = NULL;
	if (m_nCurLine < m_vLines.size())
	{
		CLine* pLine = m_vLines[m_nCurLine];
		if (pLine)
		{
			pWord = pLine->GetWord(m_nCurWord++);
		}
	}
	return pWord;
}


CLine* CCodeFile::GetNextLine()
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

bool CCodeFile::ParseBlockCMT()
{
	// 扫描注释.
	SetCurLine(0);
	CWord* pWord = NULL;
	CWord* pLastWord = NULL;
	do 
	{
		// 寻找 / *
		while ((pWord = GetAllNextWord()) != NULL)
		{
			string& str = pWord->GetWord();
			if (str == "/*")
			{
				pWord->SetAttrib(EWORD_COMMENT);
				// 标记注释和结束符
				while ((pWord = GetAllNextWord()) != NULL)
				{
					string& str = pWord->GetWord();
					pWord->SetAttrib(EWORD_COMMENT);
					if (str == "*/")
					{
						/*pLastWord = pWord;*/
						break;
					}
				}
			}
			else if (str == "//")
			{
				pWord->SetAttrib(EWORD_COMMENT);
				while ((pWord = GetLineNextWord()) != NULL)
				{
					pWord->SetAttrib(EWORD_COMMENT);
				}
				/*pLastWord = pWord;*/
				continue;
			}
			else if (str == "\"")
			{
				bool bString = true;
				pLastWord = pWord;
				pWord->SetAttrib(EWORD_STRING);
				while ((pWord = GetAllNextWord()) != NULL)
				{
					string& str = pWord->GetWord();
					// 过滤双斜杠
					if (str == "\\")
					{
						int nLine = m_nCurLine;
						int nWord = m_nCurWord;
						CWord* pNext = GetAllNextWord();
						if (pNext && (pNext->GetWord() == "\\"))
						{
							pWord->SetAttrib(EWORD_STRING);
							pNext->SetAttrib(EWORD_STRING);
							continue;
						}
						m_nCurLine = nLine;
						m_nCurWord = nWord;
					}
					if ((str == "\"") && (!pLastWord || (pLastWord->GetWord() != "\\") || (pLastWord->GetNext() != pWord)))
					{
						bString = !bString;	
						pWord->SetAttrib(EWORD_STRING);
						break;
					}
					if (bString)
					{
						pWord->SetAttrib(EWORD_STRING);
					}

					pLastWord = pWord;
				}
			}
			else if (str == "\'")
			{
				bool bString = true;
				pLastWord = pWord;
				pWord->SetAttrib(EWORD_STRING);
				while ((pWord = GetAllNextWord()) != NULL)
				{
					string& str = pWord->GetWord();
					// 过滤双斜杠
					if (str == "\\")
					{
						int nLine = m_nCurLine;
						int nWord = m_nCurWord;
						CWord* pNext = GetAllNextWord();
						if (pNext && (pNext->GetWord() == "\\"))
						{
							pWord->SetAttrib(EWORD_STRING);
							pNext->SetAttrib(EWORD_STRING);
							continue;
						}
						m_nCurLine = nLine;
						m_nCurWord = nWord;
					}
					if ((str == "\'") && (!pLastWord || (pLastWord->GetWord() != "\\") || (pLastWord->GetNext() != pWord)))
					{
						bString = !bString;	
						pWord->SetAttrib(EWORD_STRING);
						break;
					}
					if (bString)
					{
						pWord->SetAttrib(EWORD_STRING);
					}

					pLastWord = pWord;
				}
			}
			pLastWord = NULL;
		}

	} while (pWord);
	return true;
}

 bool CCodeFile::ParseLineDfn()
{
	SetCurLine(0);
	CWord* pWord = NULL;
	int nCount = 0;
	do 
	{
		while ((pWord = GetLineNextWord()) != NULL)
		{
			if (pWord->GetWord() == "#")
			{
				CWord* pNext = GetLineNextWord();
				if (pNext && (pNext->GetWord() == _T("define")))
				{
					do 
					{
						pWord = pNext;
						while ((pNext = GetLineNextWord()) != NULL)
						{
							string& strTag = pNext->GetWord();
							if ((strTag == "{") || (strTag == "}"))
							{
								pNext->SetAttrib(EWORD_STRING);
							}
							if ((strTag == "(") || (strTag == ")"))
							{
								nCount++;
								if (nCount > 1)
								{
									pNext->SetAttrib(EWORD_STRING);
								}
							}
							pWord = pNext;
						}
					} while (pWord && (pWord->GetWord() == "\\") && GetNextLine());
				}
			}
		}
		nCount = 0;
	} while (GetNextLine());
	return true;
}

bool CCodeFile::ParseFunction()
{
	SetCurLine(0);
	CWord* pWord = NULL;
	CWord* pLast = NULL;
	CWord* pLastLast = NULL;

	while ((pWord = GetAllNextWord()) != NULL)
	{
		string& str = pWord->GetWord();
		if (str == "(")
		{
			if (pLast && (pLast->GetAttrib() == EWORD_INIT))
			{
				bool bCall = false;
				if (!pLastLast 
					|| (pLastLast->GetAttrib() != EWORD_KEYWORD) || (pLastLast->GetKeyWordId() > 12))
				{
					bCall = true;
				}
				else
				{
					bCall = false;
				}
				RegFunc(m_nCurLine+1, pLast->GetWord(), bCall);
				pLast->SetAttrib(EWORD_FUNCTION);
			}
		}
		pLastLast = pLast;
		pLast = pWord;
	}

	return true;
}

struct info {
	int count;
	bool recover;
};
bool CCodeFile::ParseFunctionWithBrace()
{
	SetCurLine(0);
	CWord* pWord = NULL;
	CWord* pLast = NULL;
	static int nMismatch = 0;
	int count = 0;
	
	vector<info> vTemp;
	bool bCounting = true;
	while ((pWord = GetAllNextWord()) != NULL)
	{
		if ((pWord->GetAttrib() == EWORD_COMMENT) || (pWord->GetAttrib() == EWORD_STRING))
		{
			continue;
		}
		string& str = pWord->GetWord();
		if ((str == "#")&& (pWord->GetAttrib()== EWORD_SYMBOL))
		{
			int nLine = m_nCurLine;
			int nWord = m_nCurWord;
			struct info i;
			i.count = count;
			i.recover = false;
			CWord* pNext = GetAllNextWord();
			if (pNext && (pNext->GetWord() == _T("if")))
			{
				int nLine = m_nCurLine;
				int nWord = m_nCurWord;
				pNext = GetAllNextWord();
				if (pNext && (pNext->GetWord() == _T("0")))
				{
					i.recover = true;
				}
				m_nCurLine = nLine;
				m_nCurWord = nWord;
				vTemp.push_back(i);
			}
			if (pNext && (pNext->GetWord() == _T("ifdef")))
			{
				vTemp.push_back(i);
			}
			if (pNext && (pNext->GetWord() == _T("ifndef")))
			{
				vTemp.push_back(i);
			}
			if (pNext && (pNext->GetWord() == _T("else")))
			{
				if (vTemp.size() == 0)
				{
					continue;;
				}
				struct info x = vTemp.back();
				count = x.count;
				if (x.recover)
				{
					x.recover = false;
					vTemp.pop_back();
					vTemp.push_back(x);
				}
				continue;
			}
			if (pNext && (pNext->GetWord() == _T("elif")))
			{
				if (vTemp.size() == 0)
				{
					continue;;
				}
				struct info x = vTemp.back();
				count = x.count;
				if (x.recover)
				{
					x.recover = false;
					vTemp.pop_back();
					vTemp.push_back(x);
				}
				continue;
			}
			if (pNext && (pNext->GetWord() == "endif"))
			{
				if (vTemp.size() == 0)
				{
					continue;;
				}
				struct info x = vTemp.back();
				if (x.recover)
				{
					count = x.count;
				}
				
				vTemp.pop_back();
				continue;
			}
			m_nCurLine = nLine;
			m_nCurWord = nWord;
		}
		if (bCounting &&(str == "{") && (pWord->GetAttrib()== EWORD_SYMBOL))
		{
			count++;
		}
		else if (bCounting && (str == "}") && (pWord->GetAttrib()== EWORD_SYMBOL))
		{
			count--;
			//assert(count >= 0);
			if (count < 0)
			{
				count = 0;
				nMismatch++;
				// return false;
			}	
		}
		if ((str == "(") && (pWord->GetAttrib() == EWORD_SYMBOL))
		{
			if (pLast && (pLast->GetAttrib() == EWORD_INIT))
			{
				RegFunc(m_nCurLine+1, pLast->GetWord(), (count > 0));
				pLast->SetAttrib(EWORD_FUNCTION);
			}
		}
		pLast = pWord;
	}

	return (count == 0);
}

void CCodeFile::RegFunc(int line, string& func, bool call )
{
	//屏蔽已知非函数
	if (func.find("define")!= -1)
	{
		return;
	}
	CFuncRef* pRef = new CFuncRef(line, func, call);
	if (pRef)
	{
		PushFunc(pRef);
	}
}

void CCodeFile::ToLine(char* pbuf, unsigned long len)
{
	// 解析成行
	char* pLineStart = pbuf;
	unsigned long i = 0;
	while (i < len)
	{
		if (pbuf[i] == '\n')
		{
			pbuf[i] = 0;
			CLine* pLine = new CLine(pLineStart, (int)m_vLines.size()+1);
			if (pLine)
			{
				m_vLines.push_back(pLine);
			}
			pLineStart = &pbuf[i+1];
		}
		i++;
	}
}


void CCodeFile::PushFunc(CFuncRef* p)
{
	// 添加当前文件路径
	string netPath = "/linux/src";
	netPath +=	m_strPath.c_str();
	string str = netPath + '/' + GetName() + _T(".html");
	p->SetLink(str);
	p->SetFileName(GetName());
	m_vFuncs.push_back(p);
	// 注册索引库
	string& func = p->GetFuncName();
	bool bCall = p->GetCall();
	
	pthread_mutex_lock(&m_map_mutex);
	CFuncRefs* pRefs = m_mapFuncs[func];
	if (!pRefs)
	{
		pRefs = new CFuncRefs();
		m_mapFuncs[func] = pRefs;
	}
	pRefs->PushFuncRef(p, bCall);
	pthread_mutex_unlock(&m_map_mutex);
}

void CCodeFile::OutputHtml()
{
	bool b_del = false;
	string tmp;
	string strPath(OUTPUT_PATH);
	strPath += m_strPath.substr(strlen(CODE_PATH));
	strPath += GetName();
	string strPathFuncList = strPath + "_fn.js";
	string strPathCallList = strPath + _T("_cl.js");
	string strPathBeCallList = strPath + _T("_bcl.js");

	{
		//////////////////////////////////////////////////////////////////////////
		// 保存函数的调用关系
		string strFuncList = _T("var antfn={");
		vector<CFuncRef*>::iterator it = m_vFuncs.begin();
		while (it != m_vFuncs.end())
		{
			CFuncRef* p = *it;
			if (p)
			{
				strFuncList += p->GetFuncName();
				n2str(p->GetLineNum(), tmp);
				strFuncList += "_";
				strFuncList += tmp;
				strFuncList += _T(":");
				if (p->GetCall())
				{
					strFuncList += _T("1,");
				}
				else
				{
					strFuncList += _T("0,");
				}
				b_del = true;
			}
			it++;
		}
		if (b_del)
		{
			strFuncList.pop_back();
			b_del = false;
		}
		strFuncList += _T("};");
		if (strFuncList.size() > 1000*1000)
		{
			int x = (int)strPathFuncList.find(".js");
			strPathFuncList.insert(x, ".huge");
		}
		int nFile = open(strPathFuncList.c_str(), O_WRONLY|O_CREAT|O_TRUNC, 0777);
		if (nFile != -1)
		{
			write(nFile, strFuncList.c_str(), (unsigned int)strFuncList.size());
			close(nFile);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	{	
		// 调用别人
		map<string , bool> bSame_call;
		string strSource = _T("var antcl={");
		vector<CFuncRef*>::iterator it = m_vFuncs.begin();
		while (it != m_vFuncs.end())
		{
			CFuncRef* p = *it;
			if (p)
			{
				string strFunc = p->GetFuncName();
				bool bCall = p->GetCall();
				// 排除重复的
				if (bCall)
				{
					bool b = bSame_call[strFunc];
					if (b)
					{
						it++;
						continue;
					}
					bSame_call[strFunc] = true;
				}
				else
				{
					it++;
					continue;
				}

				strSource += strFunc;
				strSource += _T(":[");
				// 查询
				CFuncRefs* pRefs = m_mapFuncs[strFunc];
				if (pRefs)
				{
					pRefs->OutputString(strSource, !bCall);
				}
				strSource += _T("],");
				b_del = true;
			}
			it++;
		}
		if (b_del) strSource.pop_back();
		strSource += "};";

		if (strSource.size() > 1000*1000)
		{
			int x = (int)strPathCallList.find(".js");
			strPathCallList.insert(x, ".huge");
		}

		int nFile = open(strPathCallList.c_str(), O_WRONLY|O_CREAT|O_TRUNC, 0777);
		if (nFile != -1)
		{
			write(nFile, strSource.c_str(), (unsigned int)strSource.size());
			close(nFile);
		}
	}
	//////////////////////////////////////////////////////////////////////////
	{
		
		// 被别人调用
		b_del = false;
		map<string , bool> bSame_bcall;
		string strSource = _T("var antbcl={");
		vector<CFuncRef*>::iterator it = m_vFuncs.begin();
		while (it != m_vFuncs.end())
		{
			CFuncRef* p = *it;
			if (p)
			{
				string strFunc = p->GetFuncName();
				bool bCall = p->GetCall();

				if (bCall)
				{
					it++;
					continue;
				}
				else
				{// 排除重复的
					bool b = bSame_bcall[strFunc];
					if (b)
					{
						it++;
						continue;
					}
					bSame_bcall[strFunc] = true;
				}

				strSource += strFunc;
				strSource += _T(":[");
				// 查询
				CFuncRefs* pRefs = m_mapFuncs[strFunc];
				if (pRefs)
				{
					pRefs->OutputString(strSource, !bCall);
				}
				strSource += _T("],");
				b_del = true;
			}
			it++;
		}
		if (b_del) strSource.pop_back();
		strSource += "};";

		if (strSource.size() > 1000*1000)
		{
			int x = (int)strPathBeCallList.find(".js");
			strPathBeCallList.insert(x, ".huge");
		}

		int nFile = open(strPathBeCallList.c_str(), O_WRONLY|O_CREAT|O_TRUNC, 0777);
		if (nFile != -1)
		{
			write(nFile, strSource.c_str(), (unsigned int)strSource.size());
			close(nFile);
		}
	}
	return;
}
