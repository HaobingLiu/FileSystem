#include "head.h"
#include <list>

list<string> command_list;
void ParseCommand(string command)
{
	unsigned begin = 0;
	unsigned end = 0;
	string temp;
	while(end < command.length())
	{
		end = command.find(' ',begin);
		if(end != string::npos)  //�ҵ���
		{
			temp = command.substr(begin,end);
			cout<<"�ֽ�Ĳ���"<<temp<<endl;
			command_list.push_back(temp);
			while(command.at(++end) == ' ');  // ����֮��Ŀո�
			begin = end;
		}
		else
		{

		}
	}
	

}