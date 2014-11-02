#ifndef __SCRIPT_FILE_H__
#define __SCRIPT_FILE_H__ 
#include "basedata.h"
#include "nodeManageFile.h"

class CWord;
class CScriptLine;
class CNodeManageFile;
class CScriptFile : public CNodeManageFile
{
public:
	CScriptFile(const char* pPath, const char* name);
	~CScriptFile();
	virtual bool parse();
	virtual void OutputHtml(){};
	void Save();

private:
	// 多行管理
	CWord* GetAllNextWord();
	CWord* GetLineNextWord();
	void SetCurLine(int x){m_nCurLine = x;m_nCurWord = 0;}
	CScriptLine* GetNextLine();
	unsigned int m_nCurLine;
	unsigned int m_nCurWord;

private:
	bool ParseLineCMT();
	// string 扫描
	bool ParseString();
private:
	void ToLine(char* pbuf, unsigned long len);
private:
	vector<CScriptLine*> m_vLines;
};
#endif