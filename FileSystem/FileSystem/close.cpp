#include "head.h"


bool close(string file_name)
{
	int pos = IsFileInCurrentDirector(file_name);
	
	if(pos == -1)
	{
		cout<<"��ǰĿ¼������"<<file_name<<"�ļ�"<<endl;
		cout<<"���ļ�ʧ�ܣ�"<<endl;
		return false;
	}

	list<openFile>::iterator open_file_p = IsInOpenFileList(pos); 
	if(open_file_p == open_file_list.end())   // ����ļ��Ƿ��Ѵ�
	{
		cout<<"���ļ���δ�򿪣��޷��ر�"<<endl;
		return false;
	}

	file temp = myFileSystem.vector_file[pos];
	for(int i=temp.begining_in_memory;i<=temp.begining_in_memory+temp.file_length;i++)
	{
		for(int j=0;j<DATA_BLOCK_LENGTH;j++)
		{
			if(memory[i][j] != '\0')
			{
				memory[i][j] = '\0';//�ͷ��ڴ�
			}
			else
			{
				break;
			}
		}
	}
	open_file_list.erase(open_file_p);   //�Ӵ�������ɾ��
	cout<<"�ر��ļ�"<<file_name<<"�ɹ�"<<endl;
	return true;
}