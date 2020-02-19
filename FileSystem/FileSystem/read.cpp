#include "head.h"


list<openFile> open_file_list;

list<openFile>::iterator IsInOpenFileList(int pos)   // pos索引的文件是否在打开文件链表中
{
	list<openFile>::iterator p = open_file_list.begin();
	while(p != open_file_list.end())
	{
		int index = (*p).file_index;
		if(index == pos)
		{
			return p;
		}
		p++;
	}
	return p;
}

bool read(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);
	if(pos == -1)
	{
		cout<<"当前目录不存在"<<file_name<<"文件"<<endl;
		cout<<"读文件失败！"<<endl;
		return false;
	}

	if(IsInOpenFileList(pos) == open_file_list.end())   // 检查文件是否已打开
	{
		cout<<"该文件还未打开，无法读取"<<endl;
		return false;
	}

	int count = 0;
	file temp = myFileSystem.vector_file[pos];
	for(int i=temp.begining_in_memory;i<=temp.begining_in_memory+temp.file_length;i++)
	{
		for(int j=0;j<DATA_BLOCK_LENGTH;j++)
		{
			if(memory[i][j] != '\0')
			{
				count++;
				cout<<memory[i][j];
			}
			else
			{
				break;
			}
		}
	}
	cout<<endl;
	cout<<"共读入"<<count<<"个字节"<<endl;
	return true;
}