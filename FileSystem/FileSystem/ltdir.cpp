#include "head.h"



void ltdir()  // ǰ����һ��Ŀ¼
{
	int index = myFileSystem.vector_director[current_director_index].last_director;
	if(index != -1)
	{
		current_director_index = index;
	}
	else
	{
		cout<<"���Ѿ��ڸ�Ŀ¼�У�����������"<<endl;
	}
}