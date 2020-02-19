#include "head.h"



void ltdir()  // 前往上一级目录
{
	int index = myFileSystem.vector_director[current_director_index].last_director;
	if(index != -1)
	{
		current_director_index = index;
	}
	else
	{
		cout<<"您已经在根目录中，不能再向上"<<endl;
	}
}