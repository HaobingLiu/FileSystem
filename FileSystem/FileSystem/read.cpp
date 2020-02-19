#include "head.h"


list<openFile> open_file_list;

list<openFile>::iterator IsInOpenFileList(int pos)   // pos�������ļ��Ƿ��ڴ��ļ�������
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
		cout<<"��ǰĿ¼������"<<file_name<<"�ļ�"<<endl;
		cout<<"���ļ�ʧ�ܣ�"<<endl;
		return false;
	}

	if(IsInOpenFileList(pos) == open_file_list.end())   // ����ļ��Ƿ��Ѵ�
	{
		cout<<"���ļ���δ�򿪣��޷���ȡ"<<endl;
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
	cout<<"������"<<count<<"���ֽ�"<<endl;
	return true;
}