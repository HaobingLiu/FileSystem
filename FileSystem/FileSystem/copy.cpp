#include "head.h"

bool ParsePath(string path)  // 把路径解析出来
{
	int begin = 0;
	int ending = 0;
	string accessed;  // 已经过的路径
	bool flag = true;  // 表示是否是第一个目录
	current_director_index=0;//从home开始查找目标目录
	while(ending < strlen(path.c_str()))
	{
		if(path[ending] == '\\')
		{
			string director = path.substr(begin,ending-begin);
			if(flag)
			{
				if(director != "home")             // 首目录必须是home
				{
					cout<<"输入的路径不正确！"<<endl;
					cout<<"请输入绝对路径！如：home\one\two"<<endl;
					return false;
				}
				accessed += director;
				flag = false;
			}
			else
			{
				if(!ntdir(director))  //到下一目录
				{
					cout<<"无法到达"<<accessed<<"路径下的"<<director<<"文件夹"<<endl;
					return false;
				}
				accessed += director;
			}
			begin = ending+1;
			//cout<<"得到的目录是"<<director<<endl;
		}
		ending ++;
	}
	string director = path.substr(begin,ending - begin);
	if(!ntdir(director))
	{
		cout<<"无法到达"<<accessed<<"路径下的"<<director<<"文件夹"<<endl;
		return false;
	}
	cout<<"跳转到"<<path<<"成功！"<<endl;
	return true;
}


void CopyDirector(int pos,int limit)   //复制pos处的目录   limit是为了防止 新建的目录被重复新建 如果发现要新建的目录索引大于或等于
	//limit就不用再新建了
{
	//把pos处目录包含的所有文件夹全部新建，更新last_director
	director current = myFileSystem.vector_director[pos];
	director temp;
	temp.id = myFileSystem.vector_director.size();
	
	temp.name = current.name;
	temp.owner = current.owner;
	temp.last_director = current_director_index;   //更新last_director
	
	list<int>::iterator p = current.file_list.begin();  //文件的索引相同  
	while(p != current.file_list.end())
	{
		temp.file_list.push_back(*p);
		p++;
	}

	myFileSystem.vector_director[current_director_index].director_list.push_back(temp.id);  // 在当前目录中加入新的目录
	myFileSystem.vector_director.push_back(temp);//在目录信息中加入新的目录
	current_director_index = temp.id;	//更新当前目录
	
	p = current.director_list.begin();  // 在当前目录的子目录中继续复制
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
	int strore_director = current_director_index;  //暂存
	int pos = IsFileInCurrentDirector(name);
	if(pos == -1)// 复制的是文件夹
	{
		pos = IsDirectorInCurrentDirector(name);
		if(pos == -1)
		{
			cout<<"当前目录没有"<<name<<"的文件或文件夹"<<endl;
			cout<<"复制失败！"<<endl;
			return false;
		}
		else
		{
			if(myFileSystem.vector_director[pos].owner != current_user.name && myFileSystem.vector_director[pos].owner != "empty")//验证权限
			{
				cout<<"您没有操作"<<name<<"文件夹的权限"<<endl;
				cout<<"复制失败!"<<endl;
				return false;
			}

			if(!ParsePath(path))  //跳转到要复制到的目录中
			{
				cout<<"复制失败！"<<endl;
				return false;
			}
			CopyDirector(pos,myFileSystem.vector_director.size());//从pos复制到
		}
	}
	else  // 复制的是文件
	{
		if(myFileSystem.vector_file[pos].owner != current_user.name && myFileSystem.vector_file[pos].owner != "empty")//验证权限
		{
			cout<<"您没有操作"<<name<<"文件夹的权限"<<endl;
			cout<<"复制失败!"<<endl;
			return false;
		}

		if(!ParsePath(path))    //跳转到要复制到的目录中
		{
			cout<<"复制失败！"<<endl;
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
	for(int i=0;i<block.used;i++)    // 读数据块
	{
			content += block.content[i];   	
	}
	cout<<content<<endl<<block_pos<<endl;

		while((*block1).next != -1)            // 找到最后一块数据块 开始写内容
		{
			block_pos = (*block1).next;
			block1 = &myFileSystem.dataArea[block_pos];
		}

		int length = content.length(); //内容还剩的长度
		int used = 0;   //内容已写入的长度
			if(DATA_BLOCK_LENGTH - (*block1).used < length)     // 如果最后一块数据块的剩余空间小于内容
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
					block1 = &myFileSystem.dataArea[block_pos];  // 再分配块空间
				else
				{
					cout<<"磁盘空间已满，无法写入"<<endl;
					return false;
				}
			}
			else
			{
				for(int i=(*block1).used;i<(*block1).used + length;i++)
					(*block1).content[i] = content[used++];
				(*block1).used += length;
				cout<<"写入成功！"<<"已在"<<block_pos<<"号数据块写入"<<(*block1).used<<"字节"<<endl;
			}
		}

	cout<<"复制成功!"<<endl;
	current_director_index = strore_director;  //恢复当前目录
	return true;
}