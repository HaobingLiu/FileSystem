#include "head.h"

user current_user;
extern int lastest_usernumber;

bool CheckUser(string name,string password) // 检查该用户是否是初始化的用户
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

bool SignIn()//注册模块
{
	user new_user;
	string name;
	string password;
	int chance = 5;
	while(chance > 0)
	{
		cout<<"请输入用户名:";
		cin>>name;
		cout<<"请输入密码:";
		cin>>password;
		if(CheckUser(name,password))
		{
			cout<<"用户名已存在，请重新输入！您还有"<<--chance<<"次机会。"<<endl;
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



bool LoginIn()    //登录模块
{
	int chance = 5;
	string name;
	string password;
	while(chance > 0)
	{
		cout<<"请输入用户名:";
		cin>>name;
		cout<<"请输入密码：";
		cin>>password;

		if(CheckUser(name,password))
		{
			current_user.name = name;
			current_user.password = password;
			return true;
		}
		else
		{
			cout<<"用户名或密码错误，您还有"<<--chance<<"次机会"<<endl;
			print();
		}
	}
	return false;
}