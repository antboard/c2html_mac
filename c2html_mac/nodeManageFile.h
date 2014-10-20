#ifndef __NODE_MANAGE_FILE
#define __NODE_MANAGE_FILE
#include "basedata.h"

class CNodeManageDir;
class CNodeManage;
class CNodeManageFile
{
public:
	CNodeManageFile(const char* pPath, const char* name);
	virtual ~CNodeManageFile();
	
	virtual bool parse() = 0;
    virtual void Save() = 0;
	const string& GetName(){return m_fileName;}
protected:
	bool Read();

protected:
	char* m_pData;
	long long m_len;

	string m_strPath;	// file path
	string m_fileName;	// file name 
};

#endif