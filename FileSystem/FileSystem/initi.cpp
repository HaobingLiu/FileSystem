#include "head.h"

bool delete_empty_dir1(string director_name,int pos);

bool delete_not_empty_dir1(string director_name,int pos)   // ɾ���ǿ��ļ���
{
	director temp = myFileSystem.vector_director[current_director_index];			//��ǰĿ¼ֵ������ʱĿ¼
	current_director_index = myFileSystem.vector_director[pos].id;					//��ǰĿ¼��ʱ������ļ�����
	
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();          // ɾ����Ŀ¼�������ļ�
	while(p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);							//ɾ���ļ�
		p++;
	}
	list<int>::iterator dir_p = myFileSystem.vector_director[current_director_index].director_list.begin();	//��λ��Ŀ¼�����ͷ��㣬��ֵ��p
	while(dir_p != myFileSystem.vector_director[current_director_index].director_list.end())				//��ָ��û��ָ�������ĩβ
	{
		delete_not_empty_dir1(myFileSystem.vector_director[*dir_p].name,*dir_p);     // ɾ���ǿ���Ŀ¼���ݹ飩
		dir_p++;
	}
	current_director_index = temp.id;  // �ظ���ǰĿ¼���ص���ǰĿ¼��
	delete_empty_dir1(director_name,pos);  // ɾ���ѿյ��ļ���
	return true;
}




bool delete_empty_dir1(string director_name,int pos)  // ɾ���յ��ļ���
{
	list<int>::iterator p_list = myFileSystem.vector_director[current_director_index].director_list.begin();	//ͷָ�븳��p_list
	while(p_list != myFileSystem.vector_director[current_director_index].director_list.end())					//ָ��û�е�Ŀ¼���һ���ڵ�
	{
		int index = *p_list;
		if( index != -1 && myFileSystem.vector_director[index].name == director_name)
		{
			//current_director.director_list.erase(p_list);   // �ӵ�ǰĿ¼��ɾ��
			*p_list = -1;   // ��ʾ�ɲ�����
			return true;
		}
		p_list++;
	}
	return false;
}

bool initi1(string director_name,int pos)   //��ʽ���ǿ��ļ���
{
	director temp = myFileSystem.vector_director[current_director_index];			//��ǰĿ¼ֵ������ʱĿ¼
	current_director_index = myFileSystem.vector_director[pos].id;					//��ǰĿ¼��ʱ������ļ�����
	
	list<int>::iterator p = myFileSystem.vector_director[current_director_index].file_list.begin();          // ɾ����Ŀ¼�������ļ�
	while(p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p;
		delfile(myFileSystem.vector_file[index].file_name);							//ɾ���ļ�
		p++;
	}
	list<int>::iterator dir_p = myFileSystem.vector_director[current_director_index].director_list.begin();	//��λ��Ŀ¼�����ͷ��㣬��ֵ��p
	while(dir_p != myFileSystem.vector_director[current_director_index].director_list.end())				//��ָ��û��ָ�������ĩβ
	{
		delete_not_empty_dir1(myFileSystem.vector_director[*dir_p].name,*dir_p);     // ɾ���ǿ���Ŀ¼���ݹ飩
		dir_p++;
	}
	current_director_index = temp.id;  // �ظ���ǰĿ¼���ص���ǰĿ¼��
	return true;
}


bool initi(string director_name)  // ��ʽ���ļ���
{
	int pos = IsDirectorInCurrentDirector(director_name); 
	if( pos == -1)
	{
		cout<<"��ǰĿ¼�в�����"<<director_name<<"�ļ���"<<endl;
		cout<<"ɾ��ʧ��"<<endl;
		return false;
	}
	if(myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")	//Ȩ��
	{
		cout<<"��û�и��ļ��еĲ���Ȩ��!"<<endl;
		return false;
	}
	director temp = myFileSystem.vector_director[pos];			//
	if(temp.file_list.empty() && temp.director_list.empty())
	{
		cout<<"��ʽ���ɹ���"<<endl;
	}
	else
	{
		cout<<"Ҫ��ʽ����Ŀ¼�ǿգ��Ƿ�ɾ�����������ļ����ļ���?Y/N"<<endl;
		char input;
		cin>>input;
		if(input == 'Y' || input == 'y')
		{
			initi1(director_name,pos);  // ɾ���ǿ��ļ���
		}
		else
		{
			if(input == 'N' || input == 'n')
			{
				cout<<"����ȡ�����θ�ʽ��"<<endl;
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