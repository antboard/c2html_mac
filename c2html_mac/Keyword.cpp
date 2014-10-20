#include "keyword.h"
#include "basedata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// keyword
/*
1 数据类型关键字（12个）：
(1) char ：声明字符型变量或函数 
(2) double ：声明双精度变量或函数 
(3) enum ：声明枚举类型 
(4) float：声明浮点型变量或函数 
(5) int： 声明整型变量或函数 
(6) long ：声明长整型变量或函数 
(7) short ：声明短整型变量或函数 
(8) signed：声明有符号类型变量或函数 
(9) struct：声明结构体变量或函数 
(10) union：声明共用体（联合）数据类型 
(11) unsigned：声明无符号类型变量或函数 
(12) void ：声明函数无返回值或无参数，声明无类型指针（基本上就这三个作用）
(13) size_t 在string.h里使用过

2控制语句关键字（12个）：
A循环语句 
(1) for：一种循环语句(可意会不可言传） 
(2) do ：循环语句的循环体 
(3) while ：循环语句的循环条件 
(4) break：跳出当前循环 
(5) continue：结束当前循环，开始下一轮循环 
B条件语句 
(1)if: 条件语句 
(2)else ：条件语句否定分支（与 if 连用） 
(3)goto：无条件跳转语句 
C开关语句 
(1)switch :用于开关语句 
(2)case：开关语句分支 
(3)default：开关语句中的“其他”分支 
D返回语句
return ：子程序返回语句（可以带参数，也看不带参数）

3 存储类型关键字（4个）
(1)auto ：声明自动变量 一般不使用 
(2)extern：声明变量是在其他文件正声明（也可以看做是引用变量） 
(3)register：声明积存器变量 
(4)static ：声明静态变量

4 其它关键字（4个）：
(1)const ：声明只读变量 
(2)sizeof：计算数据类型长度 
(3)typedef：用以给数据类型取别名（当然还有其他作用 
(4)volatile：说明变量在程序执行中可被隐含地改变
*/
CKeyword::CKeyword()
{
	m_pKeyword = NULL;

	m_mapKeyWord.insert(map<string, int>::value_type("char", 1));
	m_mapKeyWord.insert(map<string, int>::value_type("double", 2));
	m_mapKeyWord.insert(map<string, int>::value_type("enum", 3));
	m_mapKeyWord.insert(map<string, int>::value_type("float", 4));
	m_mapKeyWord.insert(map<string, int>::value_type("int", 5));
	m_mapKeyWord.insert(map<string, int>::value_type("long", 6));
	m_mapKeyWord.insert(map<string, int>::value_type("short", 7));
	m_mapKeyWord.insert(map<string, int>::value_type("signed", 8));
	m_mapKeyWord.insert(map<string, int>::value_type("struct", TAGSTRUCT));
	m_mapKeyWord.insert(map<string, int>::value_type("union", TAGUNION));
	m_mapKeyWord.insert(map<string, int>::value_type("unsigned", 11));
	m_mapKeyWord.insert(map<string, int>::value_type("void", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("size_t", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("u8", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("u16", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("u32", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("u64", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("ssize_t", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("u_char", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("dma_addr_t", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("bool", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("pmd_t", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("pte_t", 12));
	m_mapKeyWord.insert(map<string, int>::value_type("pgtable_t", 12));

	m_mapKeyWord.insert(map<string, int>::value_type("for", 13));
	m_mapKeyWord.insert(map<string, int>::value_type("do", 14));
	m_mapKeyWord.insert(map<string, int>::value_type("while", 15));
	m_mapKeyWord.insert(map<string, int>::value_type("break", 16));
	m_mapKeyWord.insert(map<string, int>::value_type("continue", 17));

	m_mapKeyWord.insert(map<string, int>::value_type("if", 18));
	m_mapKeyWord.insert(map<string, int>::value_type("ifdef", 18));
	m_mapKeyWord.insert(map<string, int>::value_type("ifndef", 18));
	m_mapKeyWord.insert(map<string, int>::value_type("endif", 18));
	m_mapKeyWord.insert(map<string, int>::value_type("undef", 18));
	//m_mapKeyWord.insert(map<string, int>::value_type("error", 18));//error暂且不能是关键字.需要在程序里对#error过滤
	m_mapKeyWord.insert(map<string, int>::value_type("elif", 18));
	m_mapKeyWord.insert(map<string, int>::value_type("else", 19));
	m_mapKeyWord.insert(map<string, int>::value_type("goto", 20));
	m_mapKeyWord.insert(map<string, int>::value_type("switch", 21));
	m_mapKeyWord.insert(map<string, int>::value_type("case", 22));
	m_mapKeyWord.insert(map<string, int>::value_type("default", 23));
	m_mapKeyWord.insert(map<string, int>::value_type("return", 24));

	m_mapKeyWord.insert(map<string, int>::value_type("auto", 25));
	m_mapKeyWord.insert(map<string, int>::value_type("extern", TAGEXTERN));
	m_mapKeyWord.insert(map<string, int>::value_type("register", 27));
	m_mapKeyWord.insert(map<string, int>::value_type("static", TAGSTATIC));

	m_mapKeyWord.insert(map<string, int>::value_type("const", 29));
	m_mapKeyWord.insert(map<string, int>::value_type("sizeof", 30));
	m_mapKeyWord.insert(map<string, int>::value_type("typedef", TAGTYPEDEF));
	m_mapKeyWord.insert(map<string, int>::value_type("volatile", 32));
	m_mapKeyWord.insert(map<string, int>::value_type("inline", 33));

	m_mapKeyWord.insert(map<string, int>::value_type("include", 34));
	m_mapKeyWord.insert(map<string, int>::value_type("define", 35));
	m_mapKeyWord.insert(map<string, int>::value_type("__asm__", 36));
	m_mapKeyWord.insert(map<string, int>::value_type("__volatile__", 37));
	m_mapKeyWord.insert(map<string, int>::value_type("__inline__", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__sum16", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__be32", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__wsum", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__attribute__", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__EXTERN_INLINE", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__iomem", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__cpuinit", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__u32", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__u64", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__used", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__deprecated", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__always_inline", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__devinit", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__attribute_const__", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__user", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__init", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__exit", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("__devexit", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("igcsr32", 38));

	m_mapKeyWord.insert(map<string, int>::value_type("cycles_t", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("unused", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("asmlinkage", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("irqreturn_t", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("pure", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("acpi_status", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("acpi_object_type", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("ACPI_SYSTEM_XFACE", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("acpi_name", 38));
	m_mapKeyWord.insert(map<string, int>::value_type("acpi_mutex", 38));

	//	m_mapKeyWord.insert(map<string, int>::value_type("__EXTERN_INLINE", 38));
	//	m_mapKeyWord.insert(map<string, int>::value_type("__attribute__", 38));
	//	m_mapKeyWord.insert(map<string, int>::value_type("__EXTERN_INLINE", 38));
}

/*

*/