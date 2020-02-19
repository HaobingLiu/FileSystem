#include "head.h"

bool open(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);
	if(pos == -1)
	{
		cout<<"当前目录中不存在文件"<<file_name<<endl;
		cout<<"打开失败！"<<endl;
		return false;
	}

	if(myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		cout<<"您没有该文件的操作权限!"<<endl;
		return false;
	}
	
	if(myFileSystem.vector_file[pos].file_length > MAX_FILE_LENGTH - memory_index)  // 剩余文件块不够 要打开的文件
	{
		cout<<"内存空间不足，无法读入"<<file_name<<"内容,请关闭无用文件"<<endl;
		return false;
	}

	if(IsInOpenFileList(pos) != open_file_list.end())   // 检查是否已打开
	{
		cout<<"本文件已打开，请勿重复打开"<<endl;
		return false;
	}

	openFile temp;
	temp.file_index = pos;
	temp.director_index = current_director_index;
	open_file_list.push_back(temp);       // 加入打开文件链表

	int block_pos = myFileSystem.vector_file[pos].beginning_in_dataArea;
	myFileSystem.vector_file[pos].begining_in_memory = memory_index; // 设定起始位置
	dataBlock block ;
	int count = 0;
	
	while(1)
	{
		if(block_pos != -1)
		{
			block = myFileSystem.dataArea[block_pos];
			cout<<"内存读入:";
			for(int i=0;i<block.used;i++)    // 读数据块内容到内存
			{
				count++;
				memory[memory_index][i] = block.content[i];   
				cout<<block.content[i];
			}
			memory_index++;
			cout<<endl;
			block_pos = block.next;
		}
		else
		{
			break;
		}
	}
	cout<<"打开文件"<<file_name<<"成功!"<<endl;
	cout<<"共读入内存"<<count<<"个字节"<<endl;
	return true;
	
}