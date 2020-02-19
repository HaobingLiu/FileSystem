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
		if(end != string::npos)  //找到了
		{
			temp = command.substr(begin,end);
			cout<<"分解的参数"<<temp<<endl;
			command_list.push_back(temp);
			while(command.at(++end) == ' ');  // 过滤之后的空格
			begin = end;
		}
		else
		{

		}
	}
	

}