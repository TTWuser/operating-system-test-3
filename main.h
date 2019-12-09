#pragma once
#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#include<sys/wait.h>

#define MAX_DIR 10
#define MAX_FILE 10
#define MAX_USER 10

#define SYSTEM_DIR "system_dir"
#define SYSTEM_USER "system_user"


typedef enum { false = 0,true = 1 } bool;

//��ʼ��ϵͳ
void initSystem();
//test
void getUser();

//�ļ�
typedef struct {
	char file_name[8];//�ļ���
	int file_size;//�ļ���С
	int permission;//Ȩ��
} File;

//�ļ���
typedef struct {
	char dir_name[8];//�ļ�����
	int file_num;//�ļ�����
	File file_list[MAX_FILE];//���10���ļ�
} Dir;
//�û�
typedef struct  {
	char user_name[8];//�û���
	char user_pass[8];//����
	int permission;//Ȩ��
} User;

//1��Ŀ¼
typedef struct  {
	int dir_num;//�ļ�������
	Dir dir_list[MAX_DIR];
}dir_list_head;

//�û��б�
typedef struct {
	int user_num;
	User user_list[MAX_USER];

} user_list_head;

user_list_head *u_list;//�û��б�

dir_list_head *d_list;//Ŀ¼�б�
//ȫ���û�
User user;
//1.�½��û�
void createUser(User newUser);

//2.�½�Ŀ¼
void createDir(User newUser);

//3.�½��ļ�
void createFile();
//4.ɾ���ļ�
void deleteFile(char *fname);
//5.��¼
bool login(User *newUser);
//6.ע��
void loginOut();
//7.��ʾ�ļ�
void showFiles();
//8.��ʾĿ¼
void showDir();

//�����ļ�
int scanFile(int num, Dir *dir, char *fname);
//�����ļ���
Dir *scanDir(char *uname);

//9.���ļ�
void  openFile(char *fname);
//10.�ر��ļ�
void closeFile();

//11.�����û�
User *scanUser(char *uname);
//update
void updateSys();

//д���û�list�ļ�
void writeUser();

//д���ļ�list�ļ�
void writeDir();
//�˳�ϵͳ
void exitSys();
//test 
void ttt();