#include "head.h"


void IntoSuperStack()  // free数组进入超级栈
{
	for(int i=0;i<INDEX_LIST_LENGTH;i++) // 成组链中每组个数128
	{
		int param = myFileSystem.free_list[next_free_list_index][i];// 成组链数组  使用的时候从小到大   被使用了置成-1
		// 下一组要使用的组数  0~INDEX_LIST_NUMBER-1 next_free_list_index
		myFileSystem.superStack.push(param);
		myFileSystem.free_list[next_free_list_index][i] = -1;  //正在用的那组置为-1
	}

	super_stack_number = INDEX_LIST_LENGTH;

	if(next_free_list_index < INDEX_LIST_NUMBER)  // 如果没到最后一块就+1
	{
		next_free_list_index++;
	}
}

int AllocDataBlock()   //分配数据块
{
	if(myFileSystem.superStack.empty())
	{
		IntoSuperStack();   // 从free组进入超级栈
	}
	int result = myFileSystem.superStack.top();
	myFileSystem.superStack.pop();
	super_stack_number--;
	return result;
}