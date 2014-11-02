#include "basedata.h"

void GetDir(char* path, string& dir)
{
	// 从目录中获取最后的目录名
    string dirPath = path;
    unsigned long l = dirPath.length();
    unsigned long menuIdx = dirPath.rfind("/", dirPath.length()-2);
    dir = dirPath.substr(menuIdx + 1, l - menuIdx -2);
}