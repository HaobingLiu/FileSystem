#include "head.h"

user current_user;
extern int lastest_usernumber;

bool CheckUser(string name,string password) // �����û��Ƿ��ǳ�ʼ�����û�
{
	for(int i=0;i<lastest_usernumber;i++)
	{
		if(myFileSystem.user_info[i].name == name && myFileSystem.user_info[i].password == password)
		{
			return true;
		}
	} 
	return false;
}

bool SignIn()//ע��ģ��
{
	user new_user;
	string name;
	string password;
	int chance = 5;
	while(chance > 0)
	{
		cout<<"�������û���:";
		cin>>name;
		cout<<"����������:";
		cin>>password;
		if(CheckUser(name,password))
		{
			cout<<"�û����Ѵ��ڣ����������룡������"<<--chance<<"�λ��ᡣ"<<endl;
			print();
		}
		else
		{
			lastest_usernumber++;
			current_user.name = name;
			current_user.password = password;
			myFileSystem.user_info.push_back(current_user);
			myFileSystem.user_info[lastest_usernumber-1].name = name;
			myFileSystem.user_info[lastest_usernumber-1].password = password;
			return true;
		}
	}
	return false;
}



bool LoginIn()    //��¼ģ��
{
	int chance = 5;
	string name;
	string password;
	while(chance > 0)
	{
		cout<<"�������û���:";
		cin>>name;
		cout<<"���������룺";
		cin>>password;

		if(CheckUser(name,password))
		{
			current_user.name = name;
			current_user.password = password;
			return true;
		}
		else
		{
			cout<<"�û������������������"<<--chance<<"�λ���"<<endl;
			print();
		}
	}
	return false;
}