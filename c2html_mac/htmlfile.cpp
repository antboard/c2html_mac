#include "htmlfile.h"
#include "basedata.h"

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CHtmlFile::CHtmlFile(string& strfile, string& strCFile)
{
	m_strSaveFile = strfile;
	m_strSourceT = _T("<!DOCTYPE html>");
	m_strSourceT += _T("<html>");
	m_strSourceT += _T("<head>");
	m_strSourceT += _T("<meta charset=\"utf-8\">");
	m_strSourceT += _T("<meta name=\"keywords\" content=\"linux, &#x6E90;&#x4EE3;&#x7801;, antriver, &#x7740;&#x8272;, &#x5728;&#x7EBF;&#x9605;&#x8BFB;\" />");
	m_strSourceT += _T("<script src=\"/javascripts/jquery-2.1.1.min.js\"></script>");
    m_strSourceT += _T("<script src=\"");
    m_strSourceT += JS_PATH;
    m_strSourceT += ("srchead.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>");
	m_strSourceT += _T("</head>");
	m_strSourceT += _T("<body>");

	m_strSourceT += _T("<div class=\"CodeMirror cm-s-3024-night\" id=\"core-code\">");
}
CHtmlFile::~CHtmlFile()
{
	m_strSourceE += "<br/><br/><br/><br/><br/><br/><br/><br/><br/><br/></div>";
    m_strSourceE += _T("<script src=\"");
    m_strSourceE += JS_PATH;
    m_strSourceE += ("srcfoot.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>");

	m_strSourceE += _T("</body>");
	m_strSourceE += _T("</html>");
	if (m_strSourceC.size() > 1000*1000)
	{
		string tmpfile = m_strSaveFile;
		int x = (int)m_strSaveFile.find(".html");
		m_strSaveFile.insert(x, ".huge");
		string strtag = _T("<span>&#x8FD9;&#x662F;&#x4E00;&#x4E2A;&#x5F88;&#x5927;&#x7684;&#x6587;&#x4EF6;,&#x4E3A;&#x4E86;&#x4E0D;&#x5FC5;&#x8981;&#x7684;&#x6D41;&#x91CF;&#x635F;&#x5931;,&#x8BF7;&#x4F60;&#x81EA;&#x5DF1;&#x786E;&#x8BA4;&#x662F;&#x5426;&#x6709;&#x8DB3;&#x591F;&#x6D41;&#x91CF;&#x6253;&#x5F00;&#x4ED6;.&#x53EF;&#x80FD;&#x5728;100k&#x5230;1MB&#x4E4B;&#x95F4;..</span><br/><br/>");
// 		strtag +=_T("<a href=\"/linux/src/");
// 		strtag += m_strSaveFile.c_str()+25;
// 		strtag += _T("\">click here open this huge file</a>");

		strtag += _T("<a href=\"#\" class=\"cm-string\" onClick=\"wantJmp()\">&#x5982;&#x679C;wifi&#x73AF;&#x5883;&#x8BF7;&#x70B9;&#x51FB;&#x6211;,&#x6253;&#x5F00;~~~</a>");
        strtag += _T("</script><script src=\"");
        strtag += JS_PATH;
        strtag += ("hugefile.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>");
		int nFile = open(tmpfile.c_str(), O_WRONLY|O_CREAT|O_TRUNC, 0777);
		if (nFile != -1)
		{
			write(nFile, m_strSourceT.c_str(), (unsigned int)m_strSourceT.size());
			write(nFile, strtag.c_str(), (unsigned int)strtag.size());
			write(nFile, m_strSourceE.c_str(), (unsigned int)m_strSourceE.size());
			close(nFile);
		}
		// CFile save((LPCTSTR)tmpfile.c_str(), CFile::modeWrite | CFile::modeCreate);
		// assert(save);
		// if (save)
		// {
		// 	save.Write(m_strSourceT.c_str(), (unsigned int)m_strSourceT.size());
		// 	save.Write(strtag.c_str(), (unsigned int)strtag.size());
		// 	save.Write(m_strSourceE.c_str(), (unsigned int)m_strSourceE.size());
		// 	save.Close();
		// }

	}
	int nFile = open(m_strSaveFile.c_str(),  O_WRONLY|O_CREAT|O_TRUNC, 0777);
	if (nFile != -1)
	{
		write(nFile, m_strSourceT.c_str(), (unsigned int)m_strSourceT.size());
		write(nFile, m_strSourceC.c_str(), (unsigned int)m_strSourceC.size());
		write(nFile,m_strSourceE.c_str(), (unsigned int)m_strSourceE.size());
		close(nFile);
	}
	// CFile save((LPCTSTR)m_strSaveFile.c_str(), CFile::modeWrite | CFile::modeCreate);
	// assert(save);
	// if (save)
	// {
	// 	save.Write(m_strSourceT.c_str(), (unsigned int)m_strSourceT.size());
	// 	save.Write(m_strSourceC.c_str(), (unsigned int)m_strSourceC.size());
	// 	save.Write(m_strSourceE.c_str(), (unsigned int)m_strSourceE.size());
	// 	save.Close();
	// }
	return;
}

/*CHtmlFile::~CHtmlFile()
{

	//预转换，得到所需空间的大小 
	int wcsLen = (int)::MultiByteToWideChar(CP_UTF8, NULL, m_strSource.c_str(),(int) m_strSource.size(), NULL, 0); 
	//分配空间要给'\0'留个空间，MultiByteToWideChar不会给'\0'空间 
	wchar_t* wszString = new wchar_t[wcsLen + 1]; 
	//转换 
	::MultiByteToWideChar(CP_UTF8, NULL, m_strSource.c_str(), (int)m_strSource.size(), wszString, wcsLen); 
	//最后加上'\0' 
	wszString[wcsLen] = '\0'; 

	CFile save((LPCTSTR)m_strSaveFile.c_str(), CFile::modeWrite | CFile::modeCreate);
	assert(save);
	if (save)
	{
		//save.Write("\xff\xfe", 2); 
		save.Write(wszString, wcsLen);
		save.Close();
	}
	return;
}
*/

void CHtmlFile::AddContent(string& strClass, string& strContent, int nLine, int nIdx)
{
	// <span class="comment">/*</span>
	m_strSourceC += _T("<ul class=\"");
	m_strSourceC += strClass;
	m_strSourceC += _T("\"");

	assert(nLine != 0);
	char str[100];
	sprintf(str, "L%dI%d", nLine, nIdx);
	m_strSourceC += "id=\"";
	m_strSourceC += str;
	m_strSourceC += "\"";

	m_strSourceC += _T(">");
	m_strSourceC += strContent;
	m_strSourceC += _T("</ul>");
}

void CHtmlFile::AddContent(string& strClass, string& strContent)
{
	// <span class="comment">/*</span>
	m_strSourceC += _T("<span");
	if (strClass != "")
	{
		m_strSourceC += _T(" class=\"");
		m_strSourceC += strClass;
		m_strSourceC += _T("\"");
	}
	
	m_strSourceC += _T(">");
	m_strSourceC += strContent;
	m_strSourceC += _T("</span>");
}

void CHtmlFile::AddCFileName(string& strfile)
{
	// 删除Linux之前所有字符
	unsigned long i = strfile.find("/");// 只保留第一级文件
	if (i == string::npos)
	{
		i = 0;
	}
	m_strCFile = strfile.substr(i, strfile.size());
}

// void CHtmlFile::AddMenu(const string& strtag, string& strLink, char* cls)
// {
// 	CString str(strLink.c_str()+1);
// 	str.Replace('/', '@');
// 	//<div><a href="/xxx/xx.x.html">xxx.x</div>
// 	m_strSource += "<div><a href=\"#/source/";
// 	m_strSource += str.GetBuffer();
// 	m_strSource += "\"";
// 	m_strSource += "class=\"";
// 	m_strSource += cls;
// 	m_strSource += "\"";
// 	m_strSource += ">";
// 	m_strSource += strtag;
// 	m_strSource += "</div>";
// }