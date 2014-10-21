#include "nodeManage.h"
#include "nodeManageDir.h"
#include "nodeManageFile.h"

#include <unistd.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <pthread.h>

#define THREAD_MAX 1

pthread_mutex_t vec_mutex;

void n2str(int n, string& str)
{
    char tmp[65];
    sprintf(tmp, "%x", n);
    str = tmp;
}

void* TransforThreat(void* arg)
{
	while(1)
	{
		pthread_mutex_lock(&vec_mutex);
		CNodeManageFile* pFile = CNodeManage::GetFile();
		pthread_mutex_unlock(&vec_mutex);
		if (!pFile)
		{
			break;
		}
		pFile->parse();
        pFile->Save();
	}
	return 0;
}

int main(int argc,char* argv[])
{
	char curdir[] = CODE_PATH;// "/Users/jiangyichun/Downloads/code/linux-stable/";
	char* topdir = curdir;
	if(argc >= 2)
		topdir = argv[1];    
	fprintf(stderr,"Directory scan of %s:/n", topdir);  
	//printdir(topdir, 0);   
	CNodeManageDir dir(topdir, 0);
	fprintf(stderr,"all c/h file number is %d\n", CNodeManage::GetCHFileNum());
	// 创建新路径
	dir.CreateNewPath();
	// 输出html路径
    dir.OutputHtml();
	if (pthread_mutex_init(&vec_mutex, NULL))
	{
		fprintf(stderr,"ERROR: init mutex error\n");
		return -1;
	}
	// 转换文件到html
	pthread_t id[THREAD_MAX];
	for (int i = 0; i < THREAD_MAX; ++i)
	{
		if (pthread_create(&id[i], NULL, TransforThreat, NULL))
		{
			fprintf(stderr,"ERROR: pthread_create FAILER\n");
			return 0;
		}
	}

	fprintf(stderr,"waiting....\n");
	for (int i = 0; i < THREAD_MAX; ++i)
	{
		if (pthread_join(id[0], NULL))
		{
			fprintf(stderr,"waiting..FAILER\n");
		}
	}

	pthread_mutex_destroy(&vec_mutex);
	exit(0);
}