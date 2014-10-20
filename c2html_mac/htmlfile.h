#ifndef HTMLFILE_H
#define HTMLFILE_H

#include <string>
#include <assert.h>

using namespace std;

class CHtmlFile
{
public:
	CHtmlFile(string& strfile, string& strCFile);
	virtual ~CHtmlFile();

	void Output(string & str){m_strSourceC += str;}
	void AddContent(string& strClass, string& strContent, int nLine, int nIdx);
	void AddContent(string& strClass, string& strContent);
	void AddCFileName(string& strfile);
	// void AddMenu(const string& strtag, string& strLink, char* cls);
	//	void StartNewLine(int nLine);
	//	void EndNewLine(){m_strSource += _T("</div>");}
private:
	string m_strSaveFile;// 保存文件的位置

	string m_strCFile;// 最上面显示的一些非源代码的信息
	string m_strSourceT;
	string m_strSourceC;
	string m_strSourceE;
};

#endif

