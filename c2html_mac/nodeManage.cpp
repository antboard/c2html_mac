#include "nodeManage.h"
#include "nodeManageDir.h"
#include "nodeManageFile.h"
#include "MenuOutputFile.h"
#include "string.h"

#include "codeFile.h"

// 全局文件声明
std::vector<CNodeManageFile*> CNodeManage::m_vCoverFiles;
int CNodeManage::m_nSumCHFile = 0;
int CNodeManage::m_nDocFile = 0;


CNodeManage::CNodeManage()
{

}

CNodeManage::~CNodeManage()
{
	std::vector<CNodeManageDir*>::iterator it = m_vpDirs.begin();
	while(it != m_vpDirs.end())
	{
		CNodeManageDir* pDir = *it;
		if (pDir)
		{
			delete pDir;
		}
		it++;
	}

	std::vector<CNodeManageFile*>::iterator itFile = m_vpFiles.begin();
	while(it != m_vpDirs.end())
	{
		CNodeManageFile* pFile = *itFile;
		if (pFile)
		{
			delete pFile;
		}
	}
}

bool CNodeManage::AddDir(const char* pPath, char* name, int tabs)
{
	string str(pPath);
	str += name;
	str += "/";

	#ifdef ENABLE_PATH_TIPS
		fprintf(stderr,"%*s%s/\n", tabs, "", name);// 输出目录
	#endif
	CNodeManageDir* pDir = new CNodeManageDir(str.c_str(), tabs);
	if (pDir)
	{
		m_vpDirs.push_back(pDir);
		return true;
	}
	return false;
}

bool CNodeManage::AddFile(const char* pPath, char* name, int tabs)
{
	// 对于文件，过滤掉没用的 
	if (!AddFileFilter(name))
	{
		return true;
	}
	#ifdef ENABLE_PATH_TIPS
		fprintf(stderr,"%*s%s\n", tabs, "", name);
	#endif

	CNodeManageFile* pFile(NULL);
	if (strstr(name, ".c") ||
		strstr(name, ".h"))
	{
		pFile = new CCodeFile(pPath, name);
		m_nSumCHFile++;
	}
	
	if (pFile)
	{
		m_vpFiles.push_back(pFile);
		AddFile2Cover(pFile);
	}
	return true;
}

bool CNodeManage::AddFileFilter(const char* name)
{
	if (strstr(name, ".gitignore") ||
		strstr(name, "scripts") ||
		strstr(name, ".cocci") ||
		strstr(name, ".mailmap") ||
		strstr(name, "firmware")
		)
	{
		return false;
	}
	return true;
}

bool CNodeManage::AddFile2Cover(CNodeManageFile* pFile)
{
	#if DEBUG
	static int test = 0;
	if (++test > 10)
	{
		return true;
	}
	fprintf(stderr,"DEBUG: AddFile2Cover %d to list\n", test);
	#endif
	m_vCoverFiles.push_back(pFile);
	return true;
}

void CNodeManage::CreateNewPath()
{
	std::vector<CNodeManageDir*>::iterator it = m_vpDirs.begin();
	
	while(it != m_vpDirs.end())
	{
		CNodeManageDir* pDir = *it;
		if (pDir)
		{
			pDir->CreateNewPath();
		}	
		it++;
	}
}

void CNodeManage::OutputHtml(string strFile, string& rPath)
{
    char cls[] = "/";
    char cls1[] = "";
	CMenuOutputFile* pHtmlFile = new CMenuOutputFile(strFile);// CHtmlFile
	//int x = strlen(CODE_PATH);
	std::vector<CNodeManageDir*>::iterator itDir = m_vpDirs.begin();
	while(itDir != m_vpDirs.end())
	{
		CNodeManageDir* pDir = *itDir;
		if (pDir)
		{
			string strUri = rPath;
			strUri += pDir->GetName();
			strUri += ".html";
			pHtmlFile->AddMenu(pDir->GetName(), strUri, cls);
		}
		itDir++;
	}

	std::vector<CNodeManageFile*>::iterator itFile = m_vpFiles.begin();
	while(itFile != m_vpFiles.end())
	{
		CNodeManageFile* pFile = *itFile;
		if (pFile)
		{
			string strUri = rPath;
			strUri += pFile->GetName();
			strUri += ".html";
			pHtmlFile->AddMenu(pFile->GetName(), strUri, cls1);
		}
		itFile++;
	}
	delete pHtmlFile;
    
    itDir = m_vpDirs.begin();
	while(itDir != m_vpDirs.end())
	{
		CNodeManageDir* pDir = *itDir;
		if (pDir)
		{
			pDir->OutputHtml();
		}
		itDir++;
	}
}

CNodeManageFile* CNodeManage::GetFile()
{
	if (m_vCoverFiles.size() == 0)
	{
		return NULL;
	}
	// 只允许单线程访问
	CNodeManageFile* pRet = m_vCoverFiles.back();
	m_vCoverFiles.pop_back();
	return pRet;
}