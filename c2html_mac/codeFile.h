#ifndef __CODE_FILE_H__
#define __CODE_FILE_H__

#include "funcRef.h"
#include "funcRefs.h"
#include "nodeManageFile.h"

#include <pthread.h>

class CLine;
class CWord;

class CCodeFile : public CNodeManageFile
{
public:
	CCodeFile(const char* pPath, const char* name);
	~CCodeFile();
	
	virtual bool parse();
	virtual void OutputHtml();
	virtual void Save();

	void PushFunc(CFuncRef* p);
	
	static bool InitMapLock()
	{
		if (pthread_mutex_init(&m_map_mutex, NULL))
		{
			fprintf(stderr,"ERROR: init mutex error\n");
			return false;
		}
		return true;
	}
private:
	// 多行管理
	CWord* GetAllNextWord();
	CWord* GetLineNextWord();
	void SetCurLine(int x){m_nCurLine = x;m_nCurWord = 0;}
	CLine* GetNextLine();
	unsigned int m_nCurLine;
	unsigned int m_nCurWord;

private:
	// 扫码块注释
	bool ParseBlockCMT();
	bool ParseLineDfn();
	// 函数扫描
	bool ParseFunction();
	bool ParseFunctionWithBrace();
	// string 扫描
	// bool ParseString();
private:
	void RegFunc(int line, string& func, bool call);
	void ToLine(char* pbuf, unsigned long len);

private:
	static pthread_mutex_t m_map_mutex;
	vector<CFuncRef*> m_vFuncs;
	vector<CLine*> m_vLines;
	static map<string, CFuncRefs*> m_mapFuncs;
};

#endif