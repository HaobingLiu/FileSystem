#include "head.h"

// ɾ���ļ���ʱ�򣬲����ǰ� myFileSystem.file_list�е��ļ�ɾ����ֻ�ǽ���id�ĳ�-1������ǣ���ʾ�����á����ɾ������Ӧ�������ṹ��ȫ���ˡ�

bool delfile(string file_name) //ɾ���ļ�
{
	
	int pos = IsFileInCurrentDirector(file_name);
	if(pos == -1)
	{
		cout<<"��ǰĿ¼�в��������ļ���ɾ��ʧ��"<<endl;
		return false;
	}
	
	if(myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")
	{
		cout<<"��û�и��ļ��еĲ���Ȩ��!"<<endl;
		return false;
	}

	list<int>::iterator p_list = myFileSystem.vector_director[current_director_index].file_list.begin();
	while(p_list != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *p_list;
		if(index != -1 && myFileSystem.vector_file[index].file_name == file_name )
		{
			*p_list = -1;   // ��ʾΪ������
			ReleaseDataBlock(index);
			break;
		}
		p_list++;
	}
	
	//myFileSystem.vector_director[current_director.id] = current_director;  // ����Ŀ¼����

	//vector<file>::iterator p = myFileSystem.vector_file.begin();
	//p += pos;
	//(*p).id = -1;      //��ʾΪ������
	//myFileSystem.vector_file.erase(p);  // ���ļ�������ɾ��
	cout<<"ɾ���ļ�"<<file_name<<"�ɹ�"<<endl;
	return true;

	


}