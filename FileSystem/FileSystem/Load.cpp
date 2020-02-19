#include "head.h"
#include <stdio.h>
// 加载顺序参照 保存的格式

const int BUFF_LENGTH = 513;
char change[BUFF_LENGTH];
extern int lastest_usernumber;

bool LoadVectorDirector(FILE* fd,int director_num)  //加载目录信息
{
	
	for(int i=0;i<director_num;i++)
	{
		director temp;
		fscanf_s(fd,"%d%s",&temp.id,change,BUFF_LENGTH);
		temp.name = change;
		fscanf_s(fd,"%s",change,BUFF_LENGTH);
		temp.owner = change;
		fscanf_s(fd,"%d",&temp.last_director);
		int direcotor_count;
		fscanf_s(fd,"%d",&direcotor_count);
		while(direcotor_count--)       // 载入包含的目录内容
		{
			int director_index;
			fscanf_s(fd,"%d",&director_index);
			temp.director_list.push_back(director_index);
		}
		int file_count;
		fscanf_s(fd,"%d",&file_count);
		while(file_count--)              // 载入包含的文件内容
		{
			int file_index;
			fscanf_s(fd,"%d",&file_index);
			temp.file_list.push_back(file_index);
		}
		myFileSystem.vector_director.push_back(temp);
	}
	cout<<"加载目录信息成功！"<<endl;
	return true;
}


bool LoadVectorFile(FILE* fd,int file_num)  //加载文件信息
{
	while(file_num--)
	{
		file temp;
		fscanf_s(fd,"%d%s",&temp.id,change,BUFF_LENGTH);
		temp.file_name = change;
		fscanf_s(fd,"%d%s",&temp.beginning_in_dataArea,change,BUFF_LENGTH);
		temp.owner = change;
		fscanf_s(fd,"%d%d",&temp.file_length,&temp.begining_in_memory);
		myFileSystem.vector_file.push_back(temp);
	}
	cout<<"加载文件信息成功!"<<endl;
	return true;
}



bool LoadUserInfo(FILE* fd)    // 加载用户信息
{
	for(int i=0;i<lastest_usernumber;i++)
	{
		user temp;
		//user* temp = &myFileSystem.user_info[i];
		fscanf_s(fd,"%s",change,BUFF_LENGTH);
		temp.name = change;
		//(*temp).name = change;
		fscanf_s(fd,"%s",change,BUFF_LENGTH);
		temp.password = change;
		//(*temp).password = change;
		myFileSystem.user_info.push_back(temp);
	}
	cout<<"加载用户信息成功!"<<endl;
	return true;
}


bool LoadFreeList(FILE* fd)   // 加载成组链
{
	for(int i=0;i<INDEX_LIST_NUMBER;i++)
	{
		for(int j=0;j<INDEX_LIST_LENGTH;j++)
		{
			fscanf_s(fd,"%d",&myFileSystem.free_list[i][j]);
			//cout<<"读入了"<<myFileSystem.free_list[i][j]<<endl;
		}
	}
	cout<<"加载成组链信息成功!"<<endl;
	return true;
}

bool LoadSuperStack(FILE* fd)  // 加载超级栈信息
{
	fscanf_s(fd,"%d %d",&next_free_list_index,&super_stack_number);
	int temp = super_stack_number;
	while(temp--)
	{
		int value;
		fscanf_s(fd,"%d",&value);
		myFileSystem.superStack.push(value);
	}
	cout<<"加载超级栈信息成功!"<<endl;
	return true;
}


bool LoadDataArea(FILE* fd)  //加载数据域信息
{
	for(int i=0;i<DATA_BLOCK_NUMBER;i++)
	{
		int is_null;
		fscanf_s(fd,"%d",&is_null);
		dataBlock* temp = (dataBlock*)malloc(sizeof(dataBlock));
		fscanf_s(fd,"%d%d",&(*temp).next,&(*temp).used);
		if(is_null == 0)    // 如果内容不空，则读出来
		{
			fscanf_s(fd,"%s",change,BUFF_LENGTH);
			strcpy((*temp).content,change);
		}
		else  // 内容空则直接赋值
		{
			for(int j=0;j<DATA_BLOCK_NUMBER+1;j++)
			{
				(*temp).content[j] = '\0';
			}
		}
		
		//cout<<"内容"<<change<<endl;
		myFileSystem.dataArea.push_back(*temp);
	}
	cout<<"加载数据域信息成功!"<<endl;
	return true;
}

bool Load()
{
	//Initialize_Root_Path();
	FILE* fd ;
	if(fopen_s(&fd,root_path.c_str(),"r") != 0)
	{
		cout<<"尚未建立文件系统，请先初始化!"<<endl;
		return false;
	}
	
	Initialize_Memory();
	
	int director_num;
	fscanf_s(fd,"%d",&director_num);
	LoadVectorDirector(fd,director_num);
	int file_num;
	fscanf_s(fd,"%d",&file_num);
	LoadVectorFile(fd,file_num);
	LoadUserInfo(fd);
	LoadFreeList(fd);
	LoadSuperStack(fd);
	LoadDataArea(fd);
	current_director_index = 0;
	memory_index = 0;
	cout<<"文件系统加载完毕！"<<endl;
	fclose(fd);
	print();
	return true;
}