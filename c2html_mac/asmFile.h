#ifndef __ASM_FILE_H__
#define __ASM_FILE_H__ 
#include "nodeManageFile.h"

class CWord;
class CAsmLine;
class CAsmFile : public CNodeManageFile
{
public:
	CAsmFile(const char* pPath, const char* name);
	~CAsmFile();
	virtual bool parse();
	virtual void OutputHtml(){};
	virtual void Save();
private:
	// 多行管理
	CWord* GetAllNextWord();
	CWord* GetLineNextWord();
	void SetCurLine(int x){m_nCurLine = x;m_nCurWord = 0;}
	CAsmLine* GetNextLine();
	unsigned int m_nCurLine;
	unsigned int m_nCurWord;

private:
	// 扫码块注释
	bool ParseBlockCMT();
	bool ParseLineCMT();
	bool ParseKeyword();
private:
	void ToLine(char* pbuf, unsigned long len);
private:
	vector<CAsmLine*> m_vLines;
};
#endif