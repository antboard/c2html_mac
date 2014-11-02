#ifndef __BASE_DATA_H__
#define __BASE_DATA_H__

#include <string>
#include <vector>
#include <map>
using namespace std;
#define BOOL int
#define FALSE -1
#define TRUE 0
#define _T

#define CODE_PATH "/Users/jiangyichun/Downloads/code/linux-stable/"
#define OUTPUT_PATH "/Users/jiangyichun/Downloads/code/linux-weboutput/"
#define JS_PATH "/linux/src/"
#define INDEX_NAME "linux-3.14.22"
// 枚举到的目录提示
// #define ENABLE_PATH_TIPS 

#define TAGSTRUCT 9
#define TAGUNION 10
#define TAGTYPEDEF 31
#define TAGSTRUCTNAME 36
#define TAGEXTERN 26
#define TAGSTATIC 28
#define TAGNEWKEYWORD 38
#define MACROFUNCTAG 39

void n2str(int n, string& str);
void GetDir(char* path, string& dir);

enum EWORDTAG
{
	EWORD_INIT,			// 初始化值
	EWORD_KEYWORD,		// 关键字
	EWORD_FUNCTION,		// 函数名
	EWORD_MACROFUNC,    // 宏定义函数
	EWORD_SYMBOL,		// 符号
	EWORD_FILE,			// 文件名
	EWORD_PATH,			// 路径名
	EWORD_VARIABLE,		// 变量
	EWORD_SPACE,		// 空格
	EWORD_DEFINE_NAME,	// 宏定义的名称
	EWORD_STATIC_VALUE,	// 宏定义的静态值
	EWORD_COMMENT,		// 注释
	EWORD_NUM,			// 数字
	EWORD_VALUE,		// 赋值内容
	EWORD_STRUCT_NAME,	// 结构体名
	EWORD_STRUCT_VAR,	// 结构体变量名
	EWORD_UNION_NAME,	// 结构体名
	EWORD_UNION_VAR,	// 结构体变量名
	EWORD_ENUM_NAME,	// enum类型名
	EWORD_ENUM_VALUE,	// enum变量
	EWORD_TYPEDEF_NAME,	// typedef类型名
	EWORD_TYPEDEF_VALUE,// typedef变量
	EWORD_ASM_TAG,      // ASM 函数标记
	EWORD_STRING,		// 字符串
};


enum EBYTETAG
{
	EBYTE_NONE,		// 未知
	EBYTE_TAB,		// TAB
	EBYTE_SPACE,	// 空格
	EBYTE_SYMBOL,	// 数学符号
	EBYTE_LETTER,	// 英文字符
	EBYTE_NUM,		// 数字
};

EBYTETAG getWordType(unsigned char n);

#endif