#include "head.h"

int lastest_usernumber = User_NUMBER;
void print()
{
	cout<<"--------------------------------------------------------------------"<<endl;
}

void function();

void MainPage()   // 主页信息
{
	cout<<"--------------------------模拟文件系统 VFS-----------------------------\n";
	cout<<"              mkdir director_name------------建立目录\n";
    cout<<"              create file_name---------------建立文件\n";
	cout<<"              open file_name-----------------打开文件\n";
	cout<<"              read file_name-----------------读文件\n";	
	cout<<"              write file_name content--------写文件\n";	
	cout<<"              delfile file_name--------------删除文件\n";
	cout<<"              close file_name----------------关闭文件\n";
	cout<<"              ls-----------------------------显示当前目录中的子目录和文件\n";
	cout<<"              deldir director_name-----------删除文件夹\n";
	cout<<"              initi--------------------------格式化文件系统\n";
	cout<<"              back --------------------------返回上一级目录\n";
	cout<<"              cd director_name---------------进入下一级目录\n";
	cout<<"              copy name des_director_name----复制文件到指定目录\n";
	cout<<"              rename old_name new_name-------重命名\n";
	cout<<"              logout-------------------------保存结果并退出系统\n";
	cout<<"              help---------------------------帮助\n";
}

void CurrentDirector()   // 显示当前目录
{
	stack<int> temp;
	director temp_director = myFileSystem.vector_director[current_director_index];// 存放所有目录信息
	while(temp_director.last_director != -1)
	{
		temp.push(temp_director.id);
		temp_director = myFileSystem.vector_director[temp_director.last_director];
	}
	temp.push(temp_director.id);
	while(!temp.empty())
	{
		int index = temp.top();
		cout<<myFileSystem.vector_director[index].name<<">";
		temp.pop();
	}
	cout<<"$";
}
string command;
char ch ;

void choice()
{
	int choose;
	cout<<"1：注册   2：登录   请选择（1或0）:"<<endl;
	cin>>choose;
	if(choose==1)
	{
		if(SignIn())
		{
		cout<<"注册成功！"<<current_user.name<<endl;
		MainPage();
		function();
		}
	}
	else
	{
	if(LoginIn())
	{
		cout<<"登陆成功！"<<current_user.name<<endl;
		MainPage();
		function();
	}
	else
	{
		cout<<"由于多次登录失败，系统将自动关闭！"<<endl;
		cout<<"按任意键退出"<<endl;
		system("pause");
		exit(0);
	}
	}
}

void main()
{
	//Initialize_Root_Path();
	while(1)
	{
		cout<<"是否对文件系统进行初始化，请选择：（Y/N）"<<endl;
		cin>>ch;
		if(ch == 'Y' || ch =='y')
		{
			Initialize();
			break;
		}
		else
		{
			if(ch == 'N' || ch=='n')
			{
				if(Load())   // 若已初始化
				{
					break;
				}
			}
			else
			{
				cout<<"输入错误，请重新输入！"<<endl;
			}
		}
		print();
	}
	choice();
}

void function()
{
	while (true)
	{			
		print();
		CurrentDirector();   // 显示当前目录
		cin >> command;
		string param;

		if (command == "mkdir")			
		{
			cin >> param;
			mkdir(param);
			continue;
		}
		if (command == "ls")
		{
			dir();
			continue;
		}
		if (command == "cd")
		{
			cin >> param;
			ntdir(param);
			continue;
		}
		if (command == "back")
		{
			ltdir();
			continue;
		}
		if (command == "create")
		{
			cin >> param;
			create(param);
			continue;
		}
		if (command == "delfile")
		{
			cin >> param;
			delfile(param);
			continue;
		}
		if (command == "deldir")
		{
			cin >> param;
			deldir(param);
			continue;
		}
		if (command == "write")
		{
			cin >> param;
			string temp;
			cin >> temp;
			write(param, temp);
			continue;
		}
		if (command == "open")
		{
			cin >> param;
			open(param);
			continue;
		}
		if (command == "read")
		{
			cin >> param;
			read(param);
			continue;
		}
		if (command == "close")
		{
			cin >> param;
			close(param);
			continue;
		}
		if (command == "logout")
		{
			LoginOut();
			system("pause");
			system("cls");
			choice();
		}
		bool initi(string director_name);  // 格式化文件夹
		if (command == "initi")
		{
			Initialize();
			continue;
		}
		if (command == "rename")
		{
			cin >> param;
			string str;
			cin >> str;
			rename(param, str);
			continue;
		}
		if (command == "ini")
		{
			cin >> param;
			initi(param);
			continue;
		}
		if (command == "help")
		{
			MainPage();
			continue;
		}
		if (command == "copy")
		{
			cin >> param;
			string str;
			cin >> str;
			copy(param, str);
			continue;
		}
		cout << "错误指令，请重新输入！" << endl;
		while (1)    // 过滤掉剩余指令
		{
			char ch;
			ch = getchar();
			if (ch == '\n')
			{
				break;
			}
		}
	}
	system("pause");
}