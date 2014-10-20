#include "nodeManageFile.h"

#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>


CNodeManageFile::CNodeManageFile(const char* pPath, const char* name)
{
	m_strPath = pPath;
	m_fileName = name;
	m_pData = NULL;
}

CNodeManageFile::~CNodeManageFile()
{
	if (m_pData)
	{
		delete m_pData;
	}

}

bool CNodeManageFile::Read()
{
	int nFile;
	string fileName = m_strPath+m_fileName;
	nFile = open(fileName.c_str(), O_RDONLY);
	if (nFile == -1)
	{
		fprintf(stderr,"ERROR: open file %s error\n", fileName.c_str());
		return false;
	}

	// 获得文件长度
	m_len = lseek(nFile, 0, SEEK_END);
	lseek(nFile, 0, SEEK_SET);
	if (m_len == -1)
	{
		fprintf(stderr,"ERROR: lseek file %s error\n", fileName.c_str());
		return false;
	}

	m_pData = new char[m_len];
	if (-1 == read(nFile, m_pData, m_len))
	{
		fprintf(stderr,"ERROR: read file %s error\n", fileName.c_str());
	}
	close(nFile);
	return true;
}