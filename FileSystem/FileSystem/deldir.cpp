#include "head.h"


bool delete_empty_dir(string director_name,int pos)  // 删除空的文件夹
{
	list<int>::iterator p_list = myFileSystem.vector_director[current_director_index].director_list.begin();
	while(p_list != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *p_list;
		if( index != -1 && myFileSystem.vector_director[index].name == director_name)
		{
			//current_director.director_list.erase(p_list);   // 从当前目录中删除
			*p_list = -1;   // 标示成不可用
			break;
		}
		p_list++;
	}

	cout<<"删除文件夹"<<director_name<<"成功"<<endl;
	return true;
}

bool delete_not_empty_dir(string director_name,int pos)   // 删除非空文件夹
{
	director temp = myFileSystem.vector_director[current_director_index];
	current_director_index = myFileSystem.vector_director[pos].id;  // 当前目录暂时 进入该文件夹内
	
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();          // 删除子目录下所有文件
	while(p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);
		p++;
	}

	list<int>::iterator dir_p = myFileSystem.vector_director[current_director_index].director_list.begin();
	while(dir_p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		delete_not_empty_dir(myFileSystem.vector_director[*dir_p].name,*dir_p);     // 删除非空子目录
		dir_p++;
	}

	current_director_index = temp.id;  // 回复当前目录
	delete_empty_dir(director_name,pos);  // 删除已空的文件夹
	
	return true;
}



bool deldir(string director_name)  // 删除文件夹
{

	int pos = IsDirectorInCurrentDirector(director_name); 
	if( pos == -1)
	{
		cout<<"当前目录中不包含"<<director_name<<"文件夹"<<endl;
		cout<<"删除失败"<<endl;
		return false;
	}

	if(myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")
	{
		cout<<"您没有该文件夹的操作权限!"<<endl;
		return false;
	}

	director temp = myFileSystem.vector_director[pos];

	if(temp.file_list.empty() && temp.director_list.empty())
	{
		delete_empty_dir(director_name,pos);  // 删除空文件夹
	}
	else
	{
		cout<<"要删除的目录非空，是否删除其中所有文件及文件夹?Y/N"<<endl;
		char input;
		cin>>input;
		if(input == 'Y' || input == 'y')
		{
			delete_not_empty_dir(director_name,pos);  // 删除非空文件夹
		}
		else
		{
			if(input == 'N' || input == 'n')
			{
				cout<<"您已取消本次删除"<<endl;
				return false;
			}
			else
			{
				cout<<"请输入有效指令"<<endl;
				deldir(director_name);
			}
		}
	}
	return true;
}