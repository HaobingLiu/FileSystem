#include "head.h"

bool ParsePath(string path)  // ��·����������
{
	int begin = 0;
	int ending = 0;
	string accessed;  // �Ѿ�����·��
	bool flag = true;  // ��ʾ�Ƿ��ǵ�һ��Ŀ¼
	current_director_index=0;//��home��ʼ����Ŀ��Ŀ¼
	while(ending < strlen(path.c_str()))
	{
		if(path[ending] == '\\')
		{
			string director = path.substr(begin,ending-begin);
			if(flag)
			{
				if(director != "home")             // ��Ŀ¼������home
				{
					cout<<"�����·������ȷ��"<<endl;
					cout<<"���������·�����磺home\one\two"<<endl;
					return false;
				}
				accessed += director;
				flag = false;
			}
			else
			{
				if(!ntdir(director))  //����һĿ¼
				{
					cout<<"�޷�����"<<accessed<<"·���µ�"<<director<<"�ļ���"<<endl;
					return false;
				}
				accessed += director;
			}
			begin = ending+1;
			//cout<<"�õ���Ŀ¼��"<<director<<endl;
		}
		ending ++;
	}
	string director = path.substr(begin,ending - begin);
	if(!ntdir(director))
	{
		cout<<"�޷�����"<<accessed<<"·���µ�"<<director<<"�ļ���"<<endl;
		return false;
	}
	cout<<"��ת��"<<path<<"�ɹ���"<<endl;
	return true;
}


void CopyDirector(int pos,int limit)   //����pos����Ŀ¼   limit��Ϊ�˷�ֹ �½���Ŀ¼���ظ��½� �������Ҫ�½���Ŀ¼�������ڻ����
	//limit�Ͳ������½���
{
	//��pos��Ŀ¼�����������ļ���ȫ���½�������last_director
	director current = myFileSystem.vector_director[pos];
	director temp;
	temp.id = myFileSystem.vector_director.size();
	
	temp.name = current.name;
	temp.owner = current.owner;
	temp.last_director = current_director_index;   //����last_director
	
	list<int>::iterator p = current.file_list.begin();  //�ļ���������ͬ  
	while(p != current.file_list.end())
	{
		temp.file_list.push_back(*p);
		p++;
	}

	myFileSystem.vector_director[current_director_index].director_list.push_back(temp.id);  // �ڵ�ǰĿ¼�м����µ�Ŀ¼
	myFileSystem.vector_director.push_back(temp);//��Ŀ¼��Ϣ�м����µ�Ŀ¼
	current_director_index = temp.id;	//���µ�ǰĿ¼
	
	p = current.director_list.begin();  // �ڵ�ǰĿ¼����Ŀ¼�м�������
	while(p != current.director_list.end())
	{
		if(*p != -1 && *p < limit)
		{
			CopyDirector(*p,limit);
		}
		p++;
	}
}

bool copy(string name,string path)
{
	int strore_director = current_director_index;  //�ݴ�
	int pos = IsFileInCurrentDirector(name);
	if(pos == -1)// ���Ƶ����ļ���
	{
		pos = IsDirectorInCurrentDirector(name);
		if(pos == -1)
		{
			cout<<"��ǰĿ¼û��"<<name<<"���ļ����ļ���"<<endl;
			cout<<"����ʧ�ܣ�"<<endl;
			return false;
		}
		else
		{
			if(myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")//��֤Ȩ��
			{
				cout<<"��û�в���"<<name<<"�ļ��е�Ȩ��"<<endl;
				cout<<"����ʧ��!"<<endl;
				return false;
			}

			if(!ParsePath(path))  //��ת��Ҫ���Ƶ���Ŀ¼��
			{
				cout<<"����ʧ�ܣ�"<<endl;
				return false;
			}
			CopyDirector(pos,myFileSystem.vector_director.size());//��pos���Ƶ�
		}
	}
	else  // ���Ƶ����ļ�
	{
		if(myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")//��֤Ȩ��
		{
			cout<<"��û�в���"<<name<<"�ļ��е�Ȩ��"<<endl;
			cout<<"����ʧ��!"<<endl;
			return false;
		}

		if(!ParsePath(path))    //��ת��Ҫ���Ƶ���Ŀ¼��
		{
			cout<<"����ʧ�ܣ�"<<endl;
			return false;
		}

		//cout<<myFileSystem.vector_file[current_director_index].file_name<<endl;

	file temp;
	temp.id = myFileSystem.vector_file.size();
	temp.file_length = 1;
	temp.owner = current_user.name;
	temp.file_name = name;
	temp.begining_in_memory = 0;
	temp.beginning_in_dataArea = AllocDataBlock();
	myFileSystem.vector_file.push_back(temp);
	myFileSystem.vector_director[current_director_index].file_list.push_back(temp.id);
	
	file temp_original = myFileSystem.vector_file[pos];	
	string content="";
	int block_pos_origin = myFileSystem.vector_file[pos].beginning_in_dataArea;
	int block_pos = temp.beginning_in_dataArea;
	dataBlock block = myFileSystem.dataArea[block_pos_origin];
	dataBlock* block1 = &myFileSystem.dataArea[block_pos];
	for(int i=0;i<block.used;i++)    // �����ݿ�
	{
			content += block.content[i];   	
	}
	cout<<content<<endl<<block_pos<<endl;

		while((*block1).next != -1)            // �ҵ����һ�����ݿ� ��ʼд����
		{
			block_pos = (*block1).next;
			block1 = &myFileSystem.dataArea[block_pos];
		}

		int length = content.length(); //���ݻ�ʣ�ĳ���
		int used = 0;   //������д��ĳ���
			if(DATA_BLOCK_LENGTH - (*block1).used < length)     // ������һ�����ݿ��ʣ��ռ�С������
			{
				for(int i=used;i<DATA_BLOCK_LENGTH - (*block1).used + used;i++)
				{
					(*block1).content[(*block1).used ] = content[i];
					length--;
					used++;
					(*block1).used++;
				}
				block_pos = AllocDataBlock();
				(*block1).next = block_pos;
				if(block_pos != -1)
					block1 = &myFileSystem.dataArea[block_pos];  // �ٷ����ռ�
				else
				{
					cout<<"���̿ռ��������޷�д��"<<endl;
					return false;
				}
			}
			else
			{
				for(int i=(*block1).used;i<(*block1).used + length;i++)
					(*block1).content[i] = content[used++];
				(*block1).used += length;
				cout<<"д��ɹ���"<<"����"<<block_pos<<"�����ݿ�д��"<<(*block1).used<<"�ֽ�"<<endl;
			}
		}

	cout<<"���Ƴɹ�!"<<endl;
	current_director_index = strore_director;  //�ָ���ǰĿ¼
	return true;
}