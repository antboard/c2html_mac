#ifndef __NODE_MANAGER_DIR_H__
#define __NODE_MANAGER_DIR_H__

#include "basedata.h"
#include "nodeManage.h"

class CNodeManageFile;
class CNodeManageDir
{
public:
	// 注意：必须使用绝对路径
	CNodeManageDir(const char* path, int tabs = 0);
	~CNodeManageDir();
	void CreateNewPath();
    void OutputHtml();
    string GetName();
    string& GetPath(){return m_strPath;}
private:
	string m_strPath;	// 路径
	CNodeManage m_node;	// 目录中的内容是node集	
};

#endif