#include "head.h"

bool IsNameInCurrentDirector(string name)  // �ж�һ�������Ƿ��ڵ�ǰĿ¼�г��� ���� �ļ���Ŀ¼
{
	int pos = IsFileInCurrentDirector(name);     
	if(pos == -1)   // ���ֲ����ļ���
	{
		pos = IsDirectorInCurrentDirector(name);
		if(pos == -1)     //���ֲ���Ŀ¼��
		{
			return false;   // ���ֲ��ڵ�ǰĿ¼
		}
	}
	return true;
}

bool rename(string old_name,string new_name)  // ������
{
	if(IsNameInCurrentDirector(new_name) == true)
	{
		cout<<"�������ڵ�ǰĿ¼���Ѵ��ڣ��޷���������"<<endl;
		cout<<"������ʧ�ܣ�"<<endl;
		return false;
	}

	int pos = IsFileInCurrentDirector(old_name);
	if(pos != -1)  // ���Ҫ�����������ļ�
	{
		myFileSystem.vector_file[pos].file_name = new_name;
		cout<<"�������ɹ���"<<endl;
		return true;
	}
	else
	{
		pos = IsDirectorInCurrentDirector(old_name);
		if(pos != -1)  // �����������ļ���
		{
			myFileSystem.vector_director[pos].name = new_name;
			cout<<"�������ɹ���"<<endl;
			return true;
		}
		else
		{
			cout<<"��Ҫ���������ļ����ļ��в�����"<<endl;
			cout<<"������ʧ�ܣ�"<<endl;
			return false;
		}
	}
}