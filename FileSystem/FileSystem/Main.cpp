#include "head.h"

int lastest_usernumber = User_NUMBER;
void print()
{
	cout<<"--------------------------------------------------------------------"<<endl;
}

void function();

void MainPage()   // ��ҳ��Ϣ
{
	cout<<"--------------------------ģ���ļ�ϵͳ VFS-----------------------------\n";
	cout<<"              mkdir director_name------------����Ŀ¼\n";
    cout<<"              create file_name---------------�����ļ�\n";
	cout<<"              open file_name-----------------���ļ�\n";
	cout<<"              read file_name-----------------���ļ�\n";	
	cout<<"              write file_name content--------д�ļ�\n";	
	cout<<"              delfile file_name--------------ɾ���ļ�\n";
	cout<<"              close file_name----------------�ر��ļ�\n";
	cout<<"              ls-----------------------------��ʾ��ǰĿ¼�е���Ŀ¼���ļ�\n";
	cout<<"              deldir director_name-----------ɾ���ļ���\n";
	cout<<"              initi--------------------------��ʽ���ļ�ϵͳ\n";
	cout<<"              back --------------------------������һ��Ŀ¼\n";
	cout<<"              cd director_name---------------������һ��Ŀ¼\n";
	cout<<"              copy name des_director_name----�����ļ���ָ��Ŀ¼\n";
	cout<<"              rename old_name new_name-------������\n";
	cout<<"              logout-------------------------���������˳�ϵͳ\n";
	cout<<"              help---------------------------����\n";
}

void CurrentDirector()   // ��ʾ��ǰĿ¼
{
	stack<int> temp;
	director temp_director = myFileSystem.vector_director[current_director_index];// �������Ŀ¼��Ϣ
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
	cout<<"1��ע��   2����¼   ��ѡ��1��0��:"<<endl;
	cin>>choose;
	if(choose==1)
	{
		if(SignIn())
		{
		cout<<"ע��ɹ���"<<current_user.name<<endl;
		MainPage();
		function();
		}
	}
	else
	{
	if(LoginIn())
	{
		cout<<"��½�ɹ���"<<current_user.name<<endl;
		MainPage();
		function();
	}
	else
	{
		cout<<"���ڶ�ε�¼ʧ�ܣ�ϵͳ���Զ��رգ�"<<endl;
		cout<<"��������˳�"<<endl;
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
		cout<<"�Ƿ���ļ�ϵͳ���г�ʼ������ѡ�񣺣�Y/N��"<<endl;
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
				if(Load())   // ���ѳ�ʼ��
				{
					break;
				}
			}
			else
			{
				cout<<"����������������룡"<<endl;
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
		CurrentDirector();   // ��ʾ��ǰĿ¼
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
		bool initi(string director_name);  // ��ʽ���ļ���
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
		cout << "����ָ����������룡" << endl;
		while (1)    // ���˵�ʣ��ָ��
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