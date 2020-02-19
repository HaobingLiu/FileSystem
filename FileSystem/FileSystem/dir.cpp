#include "head.h"

void dir()
{
	list<int>::iterator director_p = myFileSystem.vector_director[current_director_index].director_list.begin();
	cout<<"目录列表:"<<endl;
	while(director_p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *director_p;
		if(index != -1)      // 如果可用
		{
			cout<<myFileSystem.vector_director[index].name<<'\t';
		}
		director_p++;
	}
	cout<<endl;
	list<int>::iterator file_p = myFileSystem.vector_director[current_director_index].file_list.begin();
	cout<<"文件列表:"<<endl;
	while(file_p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *file_p;
		if(index != -1)  //如果可用
		{
			cout<<myFileSystem.vector_file[index].file_name<<'\t';
		}
		
		file_p++;
	}
	cout<<endl;
}