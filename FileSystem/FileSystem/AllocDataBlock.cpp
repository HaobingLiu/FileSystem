#include "head.h"


void IntoSuperStack()  // free������볬��ջ
{
	for(int i=0;i<INDEX_LIST_LENGTH;i++) // ��������ÿ�����128
	{
		int param = myFileSystem.free_list[next_free_list_index][i];// ����������  ʹ�õ�ʱ���С����   ��ʹ�����ó�-1
		// ��һ��Ҫʹ�õ�����  0~INDEX_LIST_NUMBER-1 next_free_list_index
		myFileSystem.superStack.push(param);
		myFileSystem.free_list[next_free_list_index][i] = -1;  //�����õ�������Ϊ-1
	}

	super_stack_number = INDEX_LIST_LENGTH;

	if(next_free_list_index < INDEX_LIST_NUMBER)  // ���û�����һ���+1
	{
		next_free_list_index++;
	}
}

int AllocDataBlock()   //�������ݿ�
{
	if(myFileSystem.superStack.empty())
	{
		IntoSuperStack();   // ��free����볬��ջ
	}
	int result = myFileSystem.superStack.top();
	myFileSystem.superStack.pop();
	super_stack_number--;
	return result;
}