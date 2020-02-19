#include "head.h"




bool write(string file_name,string content)
{
	int pos = IsFileInCurrentDirector(file_name);
	if( pos == -1)
	{
		cout<<"当前目录中没有"<<file_name<<"文件"<<endl;
		cout<<"写入失败"<<endl;
		return false;
	}

	if(content != "")  // 写入的内容不空时
	{
		int block_pos = myFileSystem.vector_file[pos].beginning_in_dataArea;
		dataBlock* block = &myFileSystem.dataArea[block_pos];
		while((*block).next != -1)            // 找到最后一块数据块 开始写内容
		{
			block_pos = (*block).next;
			block = &myFileSystem.dataArea[block_pos];
		}

		int length = content.length(); //内容还剩的长度
		int used = 0;   //内容已写入的长度
		while(1)  
		{
			if(DATA_BLOCK_LENGTH - (*block).used < length)     // 如果最后一块数据块的剩余空间小于内容
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
					block = &myFileSystem.dataArea[block_pos];  // 再分配块空间
				}
				else
				{
					cout<<"磁盘空间已满，无法写入"<<endl;
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
				cout<<"写入成功！"<<"已在"<<block_pos<<"号数据块写入"<<(*block).used<<"字节"<<endl;
				return true;
			}
		}
	}
	cout<<"写入内容为空！"<<endl;
	return false;
}