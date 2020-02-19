#include "head.h"


void IntoFreeArray()   // ��superstack����ʱ������freeArray
{
	next_free_list_index--;//��0�鿪ʼ
	int index = INDEX_LIST_LENGTH - 1;           // ��ջ����ʼ������Ӵ�С���� INDEX_LIST_LENGTH��ÿ�����
	while(!myFileSystem.superStack.empty())//��ջ����ѹ��������
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
	if(super_stack_number >= INDEX_LIST_LENGTH)  // ��superstack����ʱ������freeArray
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
		IntoSuperStack(temp);//ѹ�볬��ջ
		cout<<"�ͷ���"<<temp<<"�����ݿ�"<<endl;
		if(block.next != -1)
		{
			temp = block.next;
			block = myFileSystem.dataArea[block.next];
		}
		else
			return;
	}
}