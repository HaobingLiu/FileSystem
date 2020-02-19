#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <string>

using namespace std;
const int DATA_BLOCK_LENGTH = 512 ;  // 数据块内容大小
const int DATA_BLOCK_NUMBER = 512 ;  // 数据块数目
const int INDEX_LIST_LENGTH = DATA_BLOCK_LENGTH/sizeof(int);     // 成组链中每组个数
const int INDEX_LIST_NUMBER = sizeof(int);		//  成组链组数z
const int MAX_FILE_LENGTH = 10;      // 允许的最大文件长度，即占数据块的最大数目
const int User_NUMBER = 8;           // 用户数
const string root_path = "d:\\MyFileSystem";

typedef struct file
{
	int id;                // 文件索引号
	string file_name;      // 文件名
	int    beginning_in_dataArea;     // 在数据域中的第一个位置
	string owner;          // 文件所有者的名字
	int    file_length;    // 文件所占数据块块数
	int begining_in_memory;     // 在内存中的第一个位置
}file;

typedef struct director
{	
	int id;                // 目录索引号
	string name;			// 目录名
	list<int> file_list;   // 本目录中的文件链表
	list<int> director_list;  // 本目录中的文件夹链表
	string owner;           // 文件夹拥有者
	int last_director;   // 上一级目录        // 根目录的上一级 设为 -1
}director;

typedef struct dataBlock   //数据块
{
	int used;      // 已使用的空间
	int next;      // 下一个数据块
	char content[DATA_BLOCK_LENGTH+1];  // 数据块内容 最后一位放'\0'
}dataBlock;

typedef struct user
{
	string name;
	string password;
}user;

typedef struct openFile
{
	int file_index;  // 文件索引
	int director_index;  // 目录索引
}openFile;

typedef struct fileSystem      //文件系统
{
	vector<dataBlock> dataArea;     // 数据域
	stack<int>        superStack;   // 超级栈
	int free_list[INDEX_LIST_NUMBER][INDEX_LIST_LENGTH];  // 成组链数组，被使用了置成-1
	//从free_list[0][127]——freelist[0][0]——free_list[1][127]——free_list[3][0]
	vector<user> user_info;     // 用户信息
	vector<director> vector_director;    // 存放所有目录信息
	vector<file> vector_file;            // 存放所有文件信息
}fileSystem;

extern file current_file;         // 当前打开的文件
extern int next_free_list_index;   // 下一组要使用的组数  0~INDEX_LIST_NUMBER-1
extern int super_stack_number;     // 超级栈中可以使用的块数
extern int current_director_index;  // 当前目录的索引
extern user current_user;           // 当前登录的用户
extern char memory[MAX_FILE_LENGTH][DATA_BLOCK_LENGTH];         // 内存10×512
extern int memory_index;          // 可用内存索引,即开始的位置
extern fileSystem myFileSystem;     // 文件系统
//extern string  root_path;    // 于硬盘中的根路径
extern list<openFile> open_file_list;   // 打开的文件链表

extern bool Initialize();      // 初始化文件系统
extern bool LoginIn();           // 登录模块
extern bool SignIn();			//注册模块
extern void print();   // 画分割线
extern void mkdir(string director_name);   // 新建目录
extern void dir();      // 显示该目录下内容
extern bool ntdir(string director_name);  // 前往下一级目录
extern void ltdir();  // 前往上一级目录
extern int AllocDataBlock();  // 分配数据块
extern void ReleaseDataBlock(int index);  // 释放数据块
extern bool create(string file_name); //创建文件
extern bool delfile(string file_name);  // 删除文件
extern bool deldir(string director_name); //删除目录
extern int IsFileInCurrentDirector(string file_name);  // 判断文件是否在当前目录中      返回文件索引号
extern int IsDirectorInCurrentDirector(string file_name); // 判断文件是否存在于当前目录中  返回目录索引号
extern list<openFile>::iterator IsInOpenFileList(int pos);      // 判断文件是否已打开
extern bool write(string file_name,string content);     // 向文件写入内容
extern bool wrmore(string file_name,string content,int time);     //向文件写入同一内容多次
extern bool open(string file_name);          // 打开文件，将文件内容读到内存
extern bool read(string file_name);   // 从内存中将文件内容读出来
extern bool close(string file_name);  // 将打开的文件关闭
extern bool LoginOut();              // 退出系统，保存已有信息
extern bool Load();              // 载入保存的信息
extern void Initialize_Memory();   //初始化内存
extern bool rename(string old_name,string new_name);       //重命名
extern bool copy(string name,string path);   // 复制
//extern void Initialize_Root_Path(); // 初始化根路径