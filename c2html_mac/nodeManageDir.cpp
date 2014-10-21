#include "nodeManageDir.h"
#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

CNodeManageDir::CNodeManageDir(const char* path, int tabs)
{
	// 
	m_strPath = path;

	DIR *dp;
	struct dirent *entry;
	struct stat statbuf;

	if ((dp = opendir(path)) == NULL)
	{
		fprintf(stderr, "err: can not open directory %s\n", path);
		return;
	}

	chdir(path);
	while((entry = readdir(dp)) != NULL)
	{
		// 读取目录项
		lstat(entry->d_name, &statbuf);
		if (S_ISDIR(statbuf.st_mode))
		{
			if (strcmp(".", entry->d_name) == 0 ||
				strcmp(".git", entry->d_name) == 0 ||
				strcmp("..", entry->d_name) == 0)
			{
				continue;
			}
			m_node.AddDir(m_strPath.c_str(), entry->d_name, tabs+4);
		}
		else
		{
			m_node.AddFile(m_strPath.c_str(), entry->d_name, tabs+4);
		}
	}
	chdir("..");
	closedir(dp);
}

CNodeManageDir::~CNodeManageDir()
{

}

void CNodeManageDir::CreateNewPath()
{
	// 构造目录路径
	string strOutput = OUTPUT_PATH;
	int x = strlen(CODE_PATH);
	strOutput += (m_strPath.c_str()+x);

	if (mkdir(strOutput.c_str(), 0777))
	{
		// 判断目录是否存在
		DIR* p = opendir(strOutput.c_str());
		if (!p)
		{
			fprintf(stderr,"ERROR: CreateNewPath %s error\n", strOutput.c_str());
			return;
		}
		closedir(p);
		
	}
	m_node.CreateNewPath();
}

void CNodeManageDir::OutputHtml()
{
	// 构造输出目录
	string strPath(OUTPUT_PATH);
	int x = strlen(CODE_PATH);
    if (m_strPath.length() == x) {
        strPath += "linux";
    }
	strPath += m_strPath.substr(x, m_strPath.length()-x-1);// 默认路径中减去磁盘源文件路径
	strPath += ".html";

	string strRelativePath = (m_strPath.c_str()+x);
	// 创建html文件
	m_node.OutputHtml(strPath, strRelativePath);
}

string CNodeManageDir::GetName()
{
    int l = (int)m_strPath.length();
    int n = (int)m_strPath.rfind("/", l-2);
    string str = m_strPath.substr(n+1, l-n-2);
    return str;
}


