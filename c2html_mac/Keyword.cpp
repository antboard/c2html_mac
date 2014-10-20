#include "keyword.h"
#include "basedata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// keyword
/*
1 �������͹ؼ��֣�12������
(1) char �������ַ��ͱ������� 
(2) double ������˫���ȱ������� 
(3) enum ������ö������ 
(4) float�����������ͱ������� 
(5) int�� �������ͱ������� 
(6) long �����������ͱ������� 
(7) short �����������ͱ������� 
(8) signed�������з������ͱ������� 
(9) struct�������ṹ��������� 
(10) union�����������壨���ϣ��������� 
(11) unsigned�������޷������ͱ������� 
(12) void �����������޷���ֵ���޲���������������ָ�루�����Ͼ����������ã�
(13) size_t ��string.h��ʹ�ù�

2�������ؼ��֣�12������
Aѭ����� 
(1) for��һ��ѭ�����(����᲻���Դ��� 
(2) do ��ѭ������ѭ���� 
(3) while ��ѭ������ѭ������ 
(4) break��������ǰѭ�� 
(5) continue��������ǰѭ������ʼ��һ��ѭ�� 
B������� 
(1)if: ������� 
(2)else ���������񶨷�֧���� if ���ã� 
(3)goto����������ת��� 
C������� 
(1)switch :���ڿ������ 
(2)case����������֧ 
(3)default����������еġ���������֧ 
D�������
return ���ӳ��򷵻���䣨���Դ�������Ҳ������������

3 �洢���͹ؼ��֣�4����
(1)auto �������Զ����� һ�㲻ʹ�� 
(2)extern�������������������ļ���������Ҳ���Կ��������ñ����� 
(3)register���������������� 
(4)static ��������̬����

4 �����ؼ��֣�4������
(1)const ������ֻ������ 
(2)sizeof�������������ͳ��� 
(3)typedef�����Ը���������ȡ��������Ȼ������������ 
(4)volatile��˵�������ڳ���ִ���пɱ������ظı�
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
	//m_mapKeyWord.insert(map<string, int>::value_type("error", 18));//error���Ҳ����ǹؼ���.��Ҫ�ڳ������#error����
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