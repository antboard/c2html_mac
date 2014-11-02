#include "DocLine.h"
#include "htmlfile.h"
#include "basedata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

string&   replace_all_distinct(string&   str,const   string&   old_value,const   string&   new_value)
{
    for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   {
        if(   (pos=str.find(old_value,pos))!=string::npos   )
            str.replace(pos,old_value.length(),new_value);
        else   break;
    }
    return   str;
}

CDocLine::CDocLine(char* pLineStart, int nLine)
	:m_nLine(nLine)
{
	string str(pLineStart);
    str = replace_all_distinct(str, "&", "&amp");
    str = replace_all_distinct(str, "<", "&lt");
    str = replace_all_distinct(str, ">", "&gt");
    str = replace_all_distinct(str, "\"", "&quot");
    str = replace_all_distinct(str, " ", "&nbsp");
	m_pData = str.c_str();
}


CDocLine::~CDocLine(void)
{
}

void CDocLine::StartNewLine(CHtmlFile* html, int zIdx)
{
	char buffer[65];
	string str;
	string strLine = _T("L");
    sprintf(buffer, "%d", m_nLine);
	string strShow(buffer);
	strLine += buffer;

	char cZIdx[65];
    sprintf(cZIdx, "%d", zIdx);
	string strZIdx(cZIdx);
	str = _T("<pre><a name=\"L");
	str += strShow;
	str +=_T("\"><span class=\"CodeMirror-linenumber\">");
	str += strShow;
	str += _T("&nbsp;&nbsp;</span></a>");
	html->Output(str);
}
void CDocLine::EndNewLine(CHtmlFile* html)
{
	string str = _T("</pre>");
	html->Output(str);
}

bool CDocLine::Save(CHtmlFile* html)
{
	string str(_T("<span class=\"ant-doc\">"));
	str += m_pData;
	str += _T("</span>");
	html->Output(str);
	return true;
}