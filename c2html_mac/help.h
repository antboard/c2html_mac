# 本文件是一些常用方法的集合

// 1. 查找
strstr(name, ".gitignore") 找到返回指针。找不到返回null

// 2. 限量执行 

#if DEBUG
	static int test = 0;
	if (++test > 10)
	{
		return;
	}
	fprintf(stderr,"DEBUG: CreateNewPath %s\n", strOutput.c_str());
#endif

// 文件操作
int nFile;
string fileName = m_strPath+m_fileName;
nFile = open(fileName.c_str(), O_RDONLY);
if (nFile == -1)
{
	fprintf(stderr,"ERROR: open file %s error\n", fileName.c_str());
	return false;
}

// 计算路径长度
int x = strlen(CODE_PATH);