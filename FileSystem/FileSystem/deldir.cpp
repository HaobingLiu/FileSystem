#include "head.h"


bool delete_empty_dir(string director_name,int pos)  // ɾ���յ��ļ���
{
	list<int>::iterator p_list = myFileSystem.vector_director[current_director_index].director_list.begin();
	while(p_list != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *p_list;
		if( index != -1 && myFileSystem.vector_director[index].name == director_name)
		{
			//current_director.director_list.erase(p_list);   // �ӵ�ǰĿ¼��ɾ��
			*p_list = -1;   // ��ʾ�ɲ�����
			break;
		}
		p_list++;
	}

	cout<<"ɾ���ļ���"<<director_name<<"�ɹ�"<<endl;
	return true;
}

bool delete_not_empty_dir(string director_name,int pos)   // ɾ���ǿ��ļ���
{
	director temp = myFileSystem.vector_director[current_director_index];
	current_director_index = myFileSystem.vector_director[pos].id;  // ��ǰĿ¼��ʱ ������ļ�����
	
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();          // ɾ����Ŀ¼�������ļ�
	while(p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);
		p++;
	}

	list<int>::iterator dir_p = myFileSystem.vector_director[current_director_index].director_list.begin();
	while(dir_p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		delete_not_empty_dir(myFileSystem.vector_director[*dir_p].name,*dir_p);     // ɾ���ǿ���Ŀ¼
		dir_p++;
	}

	current_director_index = temp.id;  // �ظ���ǰĿ¼
	delete_empty_dir(director_name,pos);  // ɾ���ѿյ��ļ���
	
	return true;
}



bool deldir(string director_name)  // ɾ���ļ���
{

	int pos = IsDirectorInCurrentDirector(director_name); 
	if( pos == -1)
	{
		cout<<"��ǰĿ¼�в�����"<<director_name<<"�ļ���"<<endl;
		cout<<"ɾ��ʧ��"<<endl;
		return false;
	}

	if(myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")
	{
		cout<<"��û�и��ļ��еĲ���Ȩ��!"<<endl;
		return false;
	}

	director temp = myFileSystem.vector_director[pos];

	if(temp.file_list.empty() && temp.director_list.empty())
	{
		delete_empty_dir(director_name,pos);  // ɾ�����ļ���
	}
	else
	{
		cout<<"Ҫɾ����Ŀ¼�ǿգ��Ƿ�ɾ�����������ļ����ļ���?Y/N"<<endl;
		char input;
		cin>>input;
		if(input == 'Y' || input == 'y')
		{
			delete_not_empty_dir(director_name,pos);  // ɾ���ǿ��ļ���
		}
		else
		{
			if(input == 'N' || input == 'n')
			{
				cout<<"����ȡ������ɾ��"<<endl;
				return false;
			}
			else
			{
				cout<<"��������Чָ��"<<endl;
				deldir(director_name);
			}
		}
	}
	return true;
}