#include "MenuOutputFile.h"
#include "basedata.h"

#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define _T



CMenuOutputFile::CMenuOutputFile(string& strSave)
{
	m_strSaveFile = strSave;
	m_strSource += _T("<!DOCTYPE html>");
	m_strSource += _T("<html>");
	m_strSource += _T("<head>");
	m_strSource += _T("<meta charset=\"utf-8\">");
	m_strSource += _T("<meta name=\"keywords\" content=\"linux, &#x6E90;&#x4EE3;&#x7801;, antriver, &#x7740;&#x8272;, &#x5728;&#x7EBF;&#x9605;&#x8BFB;\" />");
	m_strSource += _T("<script src=\"/javascripts/jquery-2.1.1.min.js\"></script>");
    m_strSource += _T("<script src=\"");
    m_strSource += JS_PATH;
    m_strSource += ("srchead.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>");
	m_strSource += _T("</head>");
	m_strSource += _T("<body>");

	m_strSource += _T("<div class=\"CodeMirror cm-s-3024-night\" id=\"core-code\">");
    int static_len = strlen(OUTPUT_PATH);
    // 计算父目录;
	int x = (int)m_strSaveFile.rfind("/");
	if ((x == -1) || x <= static_len)
	{
        m_strSource += "<a href=\"";
        m_strSource += JS_PATH;
        m_strSource += INDEX_NAME;
        m_strSource += ".html\"><span class=\"ant-dir\">linux src</span></a><br/>";
		return;
	}
	x -= static_len;
	string strPrt = m_strSaveFile.substr(static_len,x);
	m_strSource += "<a href=\"";
    m_strSource += JS_PATH;
	m_strSource += strPrt.c_str();
	m_strSource += ".html";
	m_strSource += "\">";
	m_strSource += "<span class=\"ant-dir\">";
	m_strSource += strPrt.c_str();
	m_strSource += "/";
	m_strSource += "</span>";
	m_strSource += "</a><br/>";
	m_strSource += "<a>";
	m_strSource += "<span class=\"ant-dir\">&#x5F53;&#x524D;&#x76EE;&#x5F55;:";
	m_strSource += m_strSaveFile.substr(static_len,(int)m_strSaveFile.rfind(".html")-static_len);
	m_strSource += "/</span></a><br/>";
}


CMenuOutputFile::~CMenuOutputFile(void)
{
	m_strSource += "</div>";
    m_strSource += _T("<script src=\"");
    m_strSource += JS_PATH;
    m_strSource += ("srcfoot.min.js\" type=\"text/javascript\" charset=\"utf-8\"></script>");

	m_strSource += _T("</body>");
	m_strSource += _T("</html>");

#if DEBUG
	static int test = 0;
	if (++test > 10)
	{
		return;
	}
	fprintf(stderr,"DEBUG: CreateNewPath %s\n", m_strSaveFile.c_str());
#endif
	
	int nFile = open(m_strSaveFile.c_str(),  O_WRONLY|O_CREAT|O_TRUNC, 0777);
	if (nFile != -1)
	{
		write(nFile, m_strSource.c_str(), (unsigned int)m_strSource.size());
		close(nFile);
	}
	return;
}

void CMenuOutputFile::AddMenu(const string& strtag, string& strLink, char* cls)
{
	if (strstr(strLink.c_str(), ".gitignore") != NULL)
	{
		return;
	}
	m_strSource += "<a href=\"";
	m_strSource += JS_PATH;
    m_strSource += INDEX_NAME;
    m_strSource += "/";
	m_strSource += strLink.c_str();
	m_strSource += "\">";
	m_strSource += "<span class=\"ant-dir\">";
	m_strSource += strtag;
	m_strSource += cls;
	m_strSource += "</span>";
	m_strSource += "<a><br/>";
}
