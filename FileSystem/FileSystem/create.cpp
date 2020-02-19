#include "head.h"

int IsFileInCurrentDirector(string file_name)   // �ж�һ�ļ����Ƿ�����ڵ�ǰĿ¼�����ļ���  �����ڷ��ض�Ӧ������ �����ڷ���-1
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

int IsDirectorInCurrentDirector(string file_name)  // �ж�һ�ļ������Ƿ���ڵĵ�ǰĿ¼����Ŀ¼��
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

bool IsDataAreaFull()   // �ж��������Ƿ�����
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

bool create(string file_name)         // �����ļ�
{
	if(IsFileInCurrentDirector(file_name) != -1)
	{
		cout<<"��Ŀ¼���Ѵ�����Ϊ"<<file_name<<"���ļ�"<<endl;
		cout<<"�ļ�����ʧ��"<<endl;
		return false;
	}
	if(IsDirectorInCurrentDirector(file_name) != -1)
	{
		cout<<"��Ŀ¼���Ѵ�����Ϊ"<<file_name<<"���ļ���"<<endl;
		cout<<"�ļ�����ʧ��"<<endl;
		return false;
	}
	if(IsDataAreaFull())
	{
		cout<<"������������û���㹻�ռ䴴���ļ�"<<endl;
		return false;
	}
	file temp;
	temp.id = myFileSystem.vector_file.size();
	temp.file_length = 1;
	temp.owner = current_user.name;
	temp.file_name = file_name;
	temp.begining_in_memory = 0;
	temp.beginning_in_dataArea = AllocDataBlock();
	cout<<"���ļ�����������ݿ���ǣ�"<<temp.beginning_in_dataArea<<endl;
	myFileSystem.vector_file.push_back(temp);
	myFileSystem.vector_director[current_director_index].file_list.push_back(temp.id);
	return true;
}