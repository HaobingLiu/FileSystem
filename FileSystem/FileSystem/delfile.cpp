#include "head.h"

// 删除文件的时候，并不是把 myFileSystem.file_list中的文件删除，只是将其id改成-1，做标记，标示不可用。如果删除，对应的索引结构就全乱了。

bool delfile(string file_name) //删除文件
{
	
	int pos = IsFileInCurrentDirector(file_name);
	if(pos == -1)
	{
		cout<<"当前目录中不包含该文件，删除失败"<<endl;
		return false;
	}
	
	if(myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		cout<<"您没有该文件夹的操作权限!"<<endl;
		return false;
	}

	list<int>::iterator p_list = myFileSystem.vector_director[current_director_index].file_list.begin();
	while(p_list != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p_list;
		if(index != -1 && myFileSystem.vector_file[index].file_name == file_name )
		{
			*p_list = -1;   // 标示为不可用
			ReleaseDataBlock(index);
			break;
		}
		p_list++;
	}
	
	//myFileSystem.vector_director[current_director.id] = current_director;  // 更新目录索引

	//vector<file>::iterator p = myFileSystem.vector_file.begin();
	//p += pos;
	//(*p).id = -1;      //标示为不可用
	//myFileSystem.vector_file.erase(p);  // 从文件索引中删除
	cout<<"删除文件"<<file_name<<"成功"<<endl;
	return true;

	


}