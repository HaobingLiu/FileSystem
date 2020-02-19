#include "head.h"




bool write(string file_name,string content)
{
	int pos = IsFileInCurrentDirector(file_name);
	if( pos == -1)
	{
		cout<<"��ǰĿ¼��û��"<<file_name<<"�ļ�"<<endl;
		cout<<"д��ʧ��"<<endl;
		return false;
	}

	if(content != "")  // д������ݲ���ʱ
	{
		int block_pos = myFileSystem.vector_file[pos].beginning_in_dataArea;
		dataBlock* block = &myFileSystem.dataArea[block_pos];
		while((*block).next != -1)            // �ҵ����һ�����ݿ� ��ʼд����
		{
			block_pos = (*block).next;
			block = &myFileSystem.dataArea[block_pos];
		}

		int length = content.length(); //���ݻ�ʣ�ĳ���
		int used = 0;   //������д��ĳ���
		while(1)  
		{
			if(DATA_BLOCK_LENGTH - (*block).used < length)     // ������һ�����ݿ��ʣ��ռ�С������
			{
				for(int i=used;i<DATA_BLOCK_LENGTH - (*block).used + used;i++)
				{
					(*block).content[(*block).used ] = content[i];
					length--;
					used++;
					(*block).used++;
				}
				block_pos = AllocDataBlock();
				(*block).next = block_pos;
				if(block_pos != -1)
				{
					block = &myFileSystem.dataArea[block_pos];  // �ٷ����ռ�
				}
				else
				{
					cout<<"���̿ռ��������޷�д��"<<endl;
					return false;
				}
			}
			else
			{
				for(int i=(*block).used;i<(*block).used + length;i++)
				{
					(*block).content[i] = content[used++];
				}
				(*block).used += length;
				cout<<"д��ɹ���"<<"����"<<block_pos<<"�����ݿ�д��"<<(*block).used<<"�ֽ�"<<endl;
				return true;
			}
		}
	}
	cout<<"д������Ϊ�գ�"<<endl;
	return false;
}