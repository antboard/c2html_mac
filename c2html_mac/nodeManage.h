#ifndef __NODE_MANAGE_H__
#define __NODE_MANAGE_H__ 
#include "basedata.h"
/*
* 文件管理集合负责保存文件的层级信息
* 功能：
* 1. 添加目录
* 2. 添加文件 
* 3. 输出文件夹层级
*
*/

class CNodeManageDir;
class CNodeManageFile;
class CMenuOutputFile;
class CNodeManage
 {
 public:
 	CNodeManage();
 	~CNodeManage();

 	bool AddDir(const char* pPath, char* name, int tabs);
 	bool AddFile(const char* pPath, char* name, int tabs);

	void CreateNewPath();
	void OutputHtml(string strFile, string& rPath);

 	static int GetCHFileNum(){return m_nSumCHFile;}
 	static int GetDocFileNum(){return m_nDocFile;}
 	static int GetAsmFileNum(){return m_nAsmFile;}
 	static int GetScriptFileNum(){return m_nScriptFile;}
 	static CNodeManageFile* GetFile();
private:
 	bool AddFileFilter(const char* name);
 	bool AddFile2Cover(CNodeManageFile* pFile);
 	
 private:
 	std::vector<CNodeManageDir*> m_vpDirs;
 	std::vector<CNodeManageFile*> m_vpFiles;

 	static std::vector<CNodeManageFile*> m_vCoverFiles;
 	static int m_nSumCHFile;
 	static int m_nDocFile;
 	static int m_nAsmFile;
 	static int m_nScriptFile;
 }; 

 #endif