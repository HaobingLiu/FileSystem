#include "head.h"

void dir()
{
	list<int>::iterator director_p = myFileSystem.vector_director[current_director_index].director_list.begin();
	cout<<"Ŀ¼�б�:"<<endl;
	while(director_p != myFileSystem.vector_director[current_director_index].director_list.end())
	{
		int index = *director_p;
		if(index != -1)      // �������
		{
			cout<<myFileSystem.vector_director[index].name<<'\t';
		}
		director_p++;
	}
	cout<<endl;
	list<int>::iterator file_p = myFileSystem.vector_director[current_director_index].file_list.begin();
	cout<<"�ļ��б�:"<<endl;
	while(file_p != myFileSystem.vector_director[current_director_index].file_list.end())
	{
		int index = *file_p;
		if(index != -1)  //�������
		{
			cout<<myFileSystem.vector_file[index].file_name<<'\t';
		}
		
		file_p++;
	}
	cout<<endl;
}