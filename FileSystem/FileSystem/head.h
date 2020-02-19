#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <string>

using namespace std;
const int DATA_BLOCK_LENGTH = 512 ;  // ���ݿ����ݴ�С
const int DATA_BLOCK_NUMBER = 512 ;  // ���ݿ���Ŀ
const int INDEX_LIST_LENGTH = DATA_BLOCK_LENGTH/sizeof(int);     // ��������ÿ�����
const int INDEX_LIST_NUMBER = sizeof(int);		//  ����������z
const int MAX_FILE_LENGTH = 10;      // ���������ļ����ȣ���ռ���ݿ�������Ŀ
const int User_NUMBER = 8;           // �û���
const string root_path = "d:\\MyFileSystem";

typedef struct file
{
	int id;                // �ļ�������
	string file_name;      // �ļ���
	int    beginning_in_dataArea;     // ���������еĵ�һ��λ��
	string owner;          // �ļ������ߵ�����
	int    file_length;    // �ļ���ռ���ݿ����
	int begining_in_memory;     // ���ڴ��еĵ�һ��λ��
}file;

typedef struct director
{	
	int id;                // Ŀ¼������
	string name;			// Ŀ¼��
	list<int> file_list;   // ��Ŀ¼�е��ļ�����
	list<int> director_list;  // ��Ŀ¼�е��ļ�������
	string owner;           // �ļ���ӵ����
	int last_director;   // ��һ��Ŀ¼        // ��Ŀ¼����һ�� ��Ϊ -1
}director;

typedef struct dataBlock   //���ݿ�
{
	int used;      // ��ʹ�õĿռ�
	int next;      // ��һ�����ݿ�
	char content[DATA_BLOCK_LENGTH+1];  // ���ݿ����� ���һλ��'\0'
}dataBlock;

typedef struct user
{
	string name;
	string password;
}user;

typedef struct openFile
{
	int file_index;  // �ļ�����
	int director_index;  // Ŀ¼����
}openFile;

typedef struct fileSystem      //�ļ�ϵͳ
{
	vector<dataBlock> dataArea;     // ������
	stack<int>        superStack;   // ����ջ
	int free_list[INDEX_LIST_NUMBER][INDEX_LIST_LENGTH];  // ���������飬��ʹ�����ó�-1
	//��free_list[0][127]����freelist[0][0]����free_list[1][127]����free_list[3][0]
	vector<user> user_info;     // �û���Ϣ
	vector<director> vector_director;    // �������Ŀ¼��Ϣ
	vector<file> vector_file;            // ��������ļ���Ϣ
}fileSystem;

extern file current_file;         // ��ǰ�򿪵��ļ�
extern int next_free_list_index;   // ��һ��Ҫʹ�õ�����  0~INDEX_LIST_NUMBER-1
extern int super_stack_number;     // ����ջ�п���ʹ�õĿ���
extern int current_director_index;  // ��ǰĿ¼������
extern user current_user;           // ��ǰ��¼���û�
extern char memory[MAX_FILE_LENGTH][DATA_BLOCK_LENGTH];         // �ڴ�10��512
extern int memory_index;          // �����ڴ�����,����ʼ��λ��
extern fileSystem myFileSystem;     // �ļ�ϵͳ
//extern string  root_path;    // ��Ӳ���еĸ�·��
extern list<openFile> open_file_list;   // �򿪵��ļ�����

extern bool Initialize();      // ��ʼ���ļ�ϵͳ
extern bool LoginIn();           // ��¼ģ��
extern bool SignIn();			//ע��ģ��
extern void print();   // ���ָ���
extern void mkdir(string director_name);   // �½�Ŀ¼
extern void dir();      // ��ʾ��Ŀ¼������
extern bool ntdir(string director_name);  // ǰ����һ��Ŀ¼
extern void ltdir();  // ǰ����һ��Ŀ¼
extern int AllocDataBlock();  // �������ݿ�
extern void ReleaseDataBlock(int index);  // �ͷ����ݿ�
extern bool create(string file_name); //�����ļ�
extern bool delfile(string file_name);  // ɾ���ļ�
extern bool deldir(string director_name); //ɾ��Ŀ¼
extern int IsFileInCurrentDirector(string file_name);  // �ж��ļ��Ƿ��ڵ�ǰĿ¼��      �����ļ�������
extern int IsDirectorInCurrentDirector(string file_name); // �ж��ļ��Ƿ�����ڵ�ǰĿ¼��  ����Ŀ¼������
extern list<openFile>::iterator IsInOpenFileList(int pos);      // �ж��ļ��Ƿ��Ѵ�
extern bool write(string file_name,string content);     // ���ļ�д������
extern bool wrmore(string file_name,string content,int time);     //���ļ�д��ͬһ���ݶ��
extern bool open(string file_name);          // ���ļ������ļ����ݶ����ڴ�
extern bool read(string file_name);   // ���ڴ��н��ļ����ݶ�����
extern bool close(string file_name);  // ���򿪵��ļ��ر�
extern bool LoginOut();              // �˳�ϵͳ������������Ϣ
extern bool Load();              // ���뱣�����Ϣ
extern void Initialize_Memory();   //��ʼ���ڴ�
extern bool rename(string old_name,string new_name);       //������
extern bool copy(string name,string path);   // ����
//extern void Initialize_Root_Path(); // ��ʼ����·��