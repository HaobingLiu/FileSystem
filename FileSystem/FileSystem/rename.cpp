#include "head.h"

bool IsNameInCurrentDirector(string name)  // 判断一个名字是否在当前目录中出现 包括 文件和目录
{
	int pos = IsFileInCurrentDirector(name);     
	if(pos == -1)   // 名字不在文件中
	{
		pos = IsDirectorInCurrentDirector(name);
		if(pos == -1)     //名字不在目录中
		{
			return false;   // 名字不在当前目录
		}
	}
	return true;
}

bool rename(string old_name,string new_name)  // 重命名
{
	if(IsNameInCurrentDirector(new_name) == true)
	{
		cout<<"新名字在当前目录中已存在，无法重新命名"<<endl;
		cout<<"重命名失败！"<<endl;
		return false;
	}

	int pos = IsFileInCurrentDirector(old_name);
	if(pos != -1)  // 如果要重命名的是文件
	{
		myFileSystem.vector_file[pos].file_name = new_name;
		cout<<"重命名成功！"<<endl;
		return true;
	}
	else
	{
		pos = IsDirectorInCurrentDirector(old_name);
		if(pos != -1)  // 重命名的是文件夹
		{
			myFileSystem.vector_director[pos].name = new_name;
			cout<<"重命名成功！"<<endl;
			return true;
		}
		else
		{
			cout<<"你要重命名的文件或文件夹不存在"<<endl;
			cout<<"重命名失败！"<<endl;
			return false;
		}
	}
}