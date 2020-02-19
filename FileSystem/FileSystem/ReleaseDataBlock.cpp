#include "head.h"


void IntoFreeArray()   // 当superstack满了时，进入freeArray
{
	next_free_list_index--;//从0组开始
	int index = INDEX_LIST_LENGTH - 1;           // 从栈顶开始，数组从大到小分配 INDEX_LIST_LENGTH：每组个数
	while(!myFileSystem.superStack.empty())//将栈内容压入组链中
	{
		int temp = myFileSystem.superStack.top();
		myFileSystem.free_list[next_free_list_index][index] = temp;
		myFileSystem.superStack.pop();
		index--;
	}
	super_stack_number = 0;
}

void IntoSuperStack(int id)
{
	myFileSystem.superStack.push(id);
	super_stack_number ++;
	if(super_stack_number >= INDEX_LIST_LENGTH)  // 当superstack满了时，进入freeArray
	{
		IntoFreeArray();
	}
}



void ReleaseDataBlock(int index)
{
	int temp = myFileSystem.vector_file[index].beginning_in_dataArea;
	dataBlock block = myFileSystem.dataArea[temp];
	while(1)
	{
		IntoSuperStack(temp);//压入超级栈
		cout<<"释放了"<<temp<<"号数据块"<<endl;
		if(block.next != -1)
		{
			temp = block.next;
			block = myFileSystem.dataArea[block.next];
		}
		else
			return;
	}
}