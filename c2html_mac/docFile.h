#ifndef __DOC_FILE_H__
#define __DOC_FILE_H__

#include "nodeManageFile.h"

class CDocLine;

class CDocFile : public CNodeManageFile
{
public:
	CDocFile(const char* pPath, const char* name);
	~CDocFile();

	virtual bool parse();
	virtual void OutputHtml(){};
	virtual void Save();
private:
	void ToLine(char* pbuf, unsigned long len);
private:
	vector<CDocLine*> m_vLines;
};

#endif