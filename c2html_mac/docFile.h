#ifndef __DOC_FILE_H__
#define __DOC_FILE_H__

#include "nodeManageFile.h"

class CDocFile : public CNodeManageFile
{
public:
	CDocFile(const char* pPath, const char* name);
	~CDocFile();

	virtual bool parse(){return true;}
	
};

#endif