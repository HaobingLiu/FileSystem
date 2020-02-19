#include"head.h"
#include <stdlib.h>
#include <stdio.h>

fileSystem myFileSystem;
int memory_index;
char memory[MAX_FILE_LENGTH][DATA_BLOCK_LENGTH];
int current_director_index;// ��ǰĿ¼������
int next_free_list_index; // ��һ��Ҫʹ�õ�����  0~INDEX_LIST_NUMBER-1
int super_stack_number;// ����ջ�п���ʹ�õĿ���

void Initialize_dataBlock()  //��ʼ�����ݿ�
{
	for(int i=0;i<DATA_BLOCK_NUMBER;i++)// ���ݿ���Ŀ
	{
		dataBlock temp ;
		temp.next = -1;
		temp.used = 0;
		for(int j=0;j<DATA_BLOCK_LENGTH+1;j++)
		{
			temp.content[j] = '\0';//��ʱ����������Ϊ0
		}
		myFileSystem.dataArea.push_back(temp);//��vectorβ����������
		//cout<<"ÿ���С"<<sizeof(temp)<<endl;
	}
	//cout<<"���ݿ���Ŀ"<<myFileSystem.dataArea.size()<<endl;
	cout<<"��ʼ��������ɹ���"<<endl;
	return ;
}


void Initialize_Index_List()  //��ʼ��������
{
	
	next_free_list_index = 0;// ��һ��Ҫʹ�õ�����  0~INDEX_LIST_NUMBER-1
	super_stack_number = 0;// ����ջ�п���ʹ�õĿ���
	while(!myFileSystem.superStack.empty())//�������ջ���գ���ջ������ȫ��pop��ȥ
	{
		myFileSystem.superStack.pop();
	}
	for(int i=0;i<INDEX_LIST_NUMBER;i++)//  ����������z
	{
		for(int j=INDEX_LIST_LENGTH-1;j>=0;j--)// ��������ÿ�����
		{
			myFileSystem.free_list[i][j] = i*INDEX_LIST_LENGTH + INDEX_LIST_LENGTH - j -1;//[0][127]~[0][0]:0~127  [1][127]~[1][0]:128~128+127
			//cout<<i<<","<<j<<myFileSystem.free_list[i][j]<<endl;
		}
	}
	cout<<"��ʼ���������ɹ���"<<endl;
	return ;
}


void Initialize_User_Info()   // ��ʼ���û���Ϣ
{
	myFileSystem.user_info.clear();
	user users[8];
	char temp[6]; 
	strcpy_s(temp,"user");
	for(int i=0;i<8;i++)
	{
		temp[4] = (char)i+49;//'1'~'8'
		temp[5] = '\0';
		myFileSystem.user_info.push_back(users[i]);
		myFileSystem.user_info[i].name = temp;
		myFileSystem.user_info[i].password = temp;
	}
	cout<<"��ʼ���û���Ϣ�ɹ�!"<<endl;
}


void Initialize_Vector_Director()   //��ʼ��Ŀ¼��Ϣ
{
	myFileSystem.vector_director.clear();//�������Ŀ¼��Ϣ
	director first;
	first.last_director = -1;
	first.id = 0;
	first.name = "home";
	first.owner = "empty";
	myFileSystem.vector_director.push_back(first);
	cout<<"��ʼ��Ŀ¼��Ϣ�ɹ�!"<<endl;
}



/*
void Initialize_Root_Path()   //��ʼ����·��
{
	root_path = "d:\\MyFileSystem";
	while(1)
	{
		cout<<"�����ñ��ļ�ϵͳ�ĸ�Ŀ¼��Ĭ��Ϊ��"<<root_path<<endl;
		cout<<"�Ƿ���ģ�Y/N"<<endl;
		char input ;
		
		while(1)
		{
			cin>>input;
			if(input == 'Y' || input == 'y')
			{
				cout<<"�������µĸ�Ŀ¼"<<endl;
				string temp;
				cin>>temp;
				if(temp[1] == ':' && temp[2] == '\\'&& ((temp[0] >= 'c' && temp[0]<='g') || ((temp[0] >= 'C' && temp[0]<='G'))) )
				{
					cout<<"���ĸ�Ŀ¼�ɹ���"<<endl;
					root_path = temp;
					print();
					return ;
				}
				else
				{
					cout<<"����ĸ�Ŀ¼�������Ϲ淶!"<<endl;
					break;
				}
			}
			else
			{
				if(input == 'N' || input == 'n')
				{
					//cout<<"��ʼ��������ȡ����"<<endl;
					print();
					return;
				}
				else
				{
					cout<<"����ָ������������Y/N"<<endl;
				}
			}
		}
		print();
	}
	
	
}
*/
void Initialize_Memory()  // ��ʼ���ڴ�
{
	memory_index = 0;// �����ڴ�����,����ʼ��λ��
	for(int i=0;i<MAX_FILE_LENGTH;i++)// ���������ļ����ȣ���ռ���ݿ�������Ŀ
	{
		for(int j=0;j<DATA_BLOCK_LENGTH;j++)// ���ݿ����ݴ�С
		{
			memory[i][j]='\0';
		}
	}
	cout<<"��ʼ���ڴ�ɹ�!"<<endl;
}


bool Initialize()  // ��ʼ��
{
	//Initialize_Root_Path();        // ��ʼ����·��
	Initialize_Vector_Director();   // ��ʼ���ļ�����Ϣ
	current_director_index = 0;		// ��ǰĿ¼������
	open_file_list.clear();			// �򿪵��ļ�����
	myFileSystem.vector_file.clear();// ��������ļ���Ϣ
	Initialize_Memory();
	Initialize_dataBlock();			// ��ʼ�����ݿ�
	Initialize_Index_List();		// ��ʼ��������
	Initialize_User_Info();			// ��ʼ���û���Ϣ
	print();
	return true;
}



