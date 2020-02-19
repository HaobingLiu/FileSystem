#include "head.h"

bool open(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);
	if(pos == -1)
	{
		cout<<"��ǰĿ¼�в������ļ�"<<file_name<<endl;
		cout<<"��ʧ�ܣ�"<<endl;
		return false;
	}

	if(myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		cout<<"��û�и��ļ��Ĳ���Ȩ��!"<<endl;
		return false;
	}
	
	if(myFileSystem.vector_file[pos].file_length > MAX_FILE_LENGTH - memory_index)  // ʣ���ļ��鲻�� Ҫ�򿪵��ļ�
	{
		cout<<"�ڴ�ռ䲻�㣬�޷�����"<<file_name<<"����,��ر������ļ�"<<endl;
		return false;
	}

	if(IsInOpenFileList(pos) != open_file_list.end())   // ����Ƿ��Ѵ�
	{
		cout<<"���ļ��Ѵ򿪣������ظ���"<<endl;
		return false;
	}

	openFile temp;
	temp.file_index = pos;
	temp.director_index = current_director_index;
	open_file_list.push_back(temp);       // ������ļ�����

	int block_pos = myFileSystem.vector_file[pos].beginning_in_dataArea;
	myFileSystem.vector_file[pos].begining_in_memory = memory_index; // �趨��ʼλ��
	dataBlock block ;
	int count = 0;
	
	while(1)
	{
		if(block_pos != -1)
		{
			block = myFileSystem.dataArea[block_pos];
			cout<<"�ڴ����:";
			for(int i=0;i<block.used;i++)    // �����ݿ����ݵ��ڴ�
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
	cout<<"���ļ�"<<file_name<<"�ɹ�!"<<endl;
	cout<<"�������ڴ�"<<count<<"���ֽ�"<<endl;
	return true;
	
}