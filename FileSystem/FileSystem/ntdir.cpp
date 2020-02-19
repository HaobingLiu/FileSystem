#include "head.h"

bool ntdir(string director_name)
{
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].director_list.begin();
	while(p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *p;
		if(myFileSystem.vector_director[index].name == director_name) // 检查目录名
		{
			if(myFileSystem.vector_director[index].owner == current_user.name || myFileSystem.vector_director[index].owner == "empty")//检查权限
			{
				current_director_index = index;
				return true;
			}
			else
			{
				cout<<"您没有该文件夹的操作权限"<<endl;
				return false;
			}
		}
		p++;
	}
	cout<<"您要前往的目录不存在"<<endl;
	return false;
}