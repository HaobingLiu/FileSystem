#include "head.h"


bool close(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);
	
	if(pos == -1)
	{
		cout<<"当前目录不存在"<<file_name<<"文件"<<endl;
		cout<<"读文件失败！"<<endl;
		return false;
	}

	list<openFile>::iterator open_file_p = IsInOpenFileList(pos); 
	if(open_file_p == open_file_list.end())   // 检查文件是否已打开
	{
		cout<<"该文件还未打开，无法关闭"<<endl;
		return false;
	}

	file temp = myFileSystem.vector_file[pos];
	for(int i=temp.begining_in_memory;i<=temp.begining_in_memory+temp.file_length;i++)
	{
		for(int j=0;j<DATA_BLOCK_LENGTH;j++)
		{
			if(memory[i][j] != '\0')
			{
				memory[i][j] = '\0';//释放内存
			}
			else
			{
				break;
			}
		}
	}
	open_file_list.erase(open_file_p);   //从打开链表中删除
	cout<<"关闭文件"<<file_name<<"成功"<<endl;
	return true;
}