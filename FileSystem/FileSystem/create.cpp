#include "head.h"

int IsFileInCurrentDirector(string file_name)   // 判断一文件名是否存在于当前目录的子文件中  若存在返回对应索引号 不存在返回-1
{
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();
	while(p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		if(index != -1 && myFileSystem.vector_file[index].file_name == file_name)
		{
			return index;
		}
		p++;
	}
	return -1;
}

int IsDirectorInCurrentDirector(string file_name)  // 判断一文件夹名是否存在的当前目录的子目录中
{
	//bool flag = false;
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].director_list.begin();

	while(p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *p;
		if(index != -1 && myFileSystem.vector_director[index].name == file_name )
		{
			return *p;
		}
		p++;
	}
	return -1;
}

bool IsDataAreaFull()   // 判断数据域是否已满
{
	if(myFileSystem.superStack.empty() && myFileSystem.free_list[INDEX_LIST_NUMBER -1][0] == -1)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool create(string file_name)         // 创建文件
{
	if(IsFileInCurrentDirector(file_name) != -1)
	{
		cout<<"本目录中已存在名为"<<file_name<<"的文件"<<endl;
		cout<<"文件创建失败"<<endl;
		return false;
	}
	if(IsDirectorInCurrentDirector(file_name) != -1)
	{
		cout<<"本目录中已存在名为"<<file_name<<"的文件夹"<<endl;
		cout<<"文件创建失败"<<endl;
		return false;
	}
	if(IsDataAreaFull())
	{
		cout<<"数据域已满，没有足够空间创建文件"<<endl;
		return false;
	}
	file temp;
	temp.id = myFileSystem.vector_file.size();
	temp.file_length = 1;
	temp.owner = current_user.name;
	temp.file_name = file_name;
	temp.begining_in_memory = 0;
	temp.beginning_in_dataArea = AllocDataBlock();
	cout<<"该文件被分配的数据块号是："<<temp.beginning_in_dataArea<<endl;
	myFileSystem.vector_file.push_back(temp);
	myFileSystem.vector_director[current_director_index].file_list.push_back(temp.id);
	return true;
}