#include "head.h"

bool ntdir(string director_name)
{
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].director_list.begin();
	while(p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *p;
		if(myFileSystem.vector_director[index].name == director_name) // ���Ŀ¼��
		{
			if(myFileSystem.vector_director[index].owner == current_user.name || myFileSystem.vector_director[index].owner == "empty")//���Ȩ��
			{
				current_director_index = index;
				return true;
			}
			else
			{
				cout<<"��û�и��ļ��еĲ���Ȩ��"<<endl;
				return false;
			}
		}
		p++;
	}
	cout<<"��Ҫǰ����Ŀ¼������"<<endl;
	return false;
}