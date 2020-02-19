#include "head.h"
#include <stdio.h>

extern int lastest_usernumber;

/* �����ʽ 
1. vector_director�ĸ���
2.vector_director������
3.vector_file�ĸ���
4.vector_file������
5.user_info����
6.free_list����  �����С����
7.super_stack����
8.data_area����
*/



/*�����ʽ
1.int id
2.char* name
3.char* owner
4.int last_director
5.int director��Ŀ
6.int director_list
7.int file��Ŀ
8.int file_list
*/
bool SaveVectorDirector(FILE* fd)  //����Ŀ¼��Ϣ
{
	vector<director>::iterator p = myFileSystem.vector_director.begin();//����һ����������ָ���һ��Ԫ��
	
	while(p != myFileSystem.vector_director.end())
	{
		int director_num = (*p).director_list.size();
		int file_num = (*p).file_list.size();
		
		fprintf(fd,"%d%s\n%s\n%d\n%d\n",(*p).id,(*p).name.c_str(),(*p).owner.c_str(),(*p).last_director,director_num);
		
		list<int>::iterator p_list = (*p).director_list.begin();  // д��director_list
		while(p_list != (*p).director_list.end())
		{
			fprintf(fd,"%d\n",(*p_list));
			p_list++;
		}

		fprintf(fd,"%d\n",file_num);
		p_list = (*p).file_list.begin();          // д��file_list
		while(p_list != (*p).file_list.end())
		{
			fprintf(fd,"%d\n",(*p_list));
			p_list++;
		}
		p++;
	}
	cout<<"����Ŀ¼��Ϣ�ɹ�"<<endl;
	return true;
}



/*�����ʽ
1.int id
2.char* file_name
3.int beginning_in_dataarea
4.char* owner
5.int file_length
6.int beginning_in_memory
*/
bool SaveVectorFile(FILE* fd)  // �����ļ���Ϣ
{
	vector<file>::iterator p = myFileSystem.vector_file.begin();
	while(p != myFileSystem.vector_file.end())
	{
		fprintf(fd,"%d\n%s\n%d\n%s\n%d\n%d\n",(*p).id,(*p).file_name.c_str(),(*p).beginning_in_dataArea,(*p).owner.c_str(),(*p).file_length,(*p).begining_in_memory);
		p++;
	}
	cout<<"�����ļ���Ϣ�ɹ�"<<endl;
	return true;
}

bool SaveUserInfo(FILE* fd)  // �����û���Ϣ
{

	for(int i=0;i<lastest_usernumber;i++)
	{
		user temp = myFileSystem.user_info[i];
		fprintf(fd,"%s\n%s\n",temp.name.c_str(),temp.password.c_str());
	}
	cout<<"�����û���Ϣ�ɹ�"<<endl;
	return true;
}



bool SaveFreeList(FILE* fd)  //���������
{
	for(int i=0;i<INDEX_LIST_NUMBER;i++)
	{
		for(int j=0;j<INDEX_LIST_LENGTH;j++)
		{
			fprintf(fd,"%d\n",myFileSystem.free_list[i][j]);
		}
	}
	cout<<"����������ɹ�"<<endl;
	return true;
}



/*
1. int next_free_list_index;   // ��һ��Ҫʹ�õ�����  0~INDEX_LIST_NUMBER-1
2. int super_stack_number;     // ����ջ�п���ʹ�õĿ���
3. int ջ������ ����
*/

bool SaveSuperStack(FILE* fd)  // ���泬��ջ
{
	stack<int> temp;
	fprintf(fd,"%d\n%d\n",next_free_list_index,super_stack_number);
	while(!myFileSystem.superStack.empty())   // �����ݱ��浽��һ��ջ�У����򱣴棬�������ص�ʱ��˳��Ŷ�
	{
		int top = myFileSystem.superStack.top();
		temp.push(top);
		myFileSystem.superStack.pop();
	}
	while(!temp.empty())
	{
		fprintf(fd,"%d\n",temp.top());
		temp.pop();
	}
	cout<<"���泬��ջ�ɹ�"<<endl;
	return true;
}



//�����ʽ  int is_null  int next  int used  char* content
bool SaveDataArea(FILE* fd) //��������������
{
	for(int i=0;i<DATA_BLOCK_NUMBER;i++)
	{
		int is_null = 1;    // ������ǣ�1��ʾ�����ǿգ�0��ʾ�ǿ�
		dataBlock temp = myFileSystem.dataArea[i];
		if(temp.content[0] != '\0')       // ����ǿգ����ϱ��
		{
			is_null = 0;
		}
		fprintf(fd,"%d\n%d\n%d\n",is_null,temp.next,temp.used);
		if(is_null == 0)    //�ǿյİ����ݴ���
		{
			fprintf(fd,"%s\n",temp.content);
		}
	}
	cout<<"�������������ݳɹ�"<<endl;
	return true;
}

bool LoginOut()
{
	FILE* fd ;
	if(fopen_s(&fd,root_path.c_str(),"w+") != 0)
	{
		cout<<"���ļ�"<<root_path<<"ʧ�ܣ��޷�����"<<endl;
		return false;
	}
	
	int director_num = myFileSystem.vector_director.size();
	int file_num = myFileSystem.vector_file.size();
	fprintf(fd,"%d\n",director_num);
	SaveVectorDirector(fd);      //д��vector_director����
	fprintf(fd,"%d\n",file_num);
	SaveVectorFile(fd);
	SaveUserInfo(fd);
	SaveFreeList(fd);
	SaveSuperStack(fd);
	SaveDataArea(fd);
	cout<<"�ļ�ϵͳ����ɹ�!"<<endl;
	print();
	fclose(fd);
	return true;
}