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

//初始化系统
void initSystem();
//test
void getUser();

//文件
typedef struct {
	char file_name[8];//文件名
	int file_size;//文件大小
	int permission;//权限
} File;

//文件夹
typedef struct {
	char dir_name[8];//文件夹名
	int file_num;//文件数量
	File file_list[MAX_FILE];//最多10个文件
} Dir;
//用户
typedef struct  {
	char user_name[8];//用户名
	char user_pass[8];//密码
	int permission;//权限
} User;

//1级目录
typedef struct  {
	int dir_num;//文件夹数量
	Dir dir_list[MAX_DIR];
}dir_list_head;

//用户列表
typedef struct {
	int user_num;
	User user_list[MAX_USER];

} user_list_head;

user_list_head *u_list;//用户列表

dir_list_head *d_list;//目录列表
//全局用户
User user;
//1.新建用户
void createUser(User newUser);

//2.新建目录
void createDir(User newUser);

//3.新建文件
void createFile();
//4.删除文件
void deleteFile(char *fname);
//5.登录
bool login(User *newUser);
//6.注销
void loginOut();
//7.显示文件
void showFiles();
//8.显示目录
void showDir();

//查找文件
int scanFile(int num, Dir *dir, char *fname);
//查找文件夹
Dir *scanDir(char *uname);

//9.打开文件
void  openFile(char *fname);
//10.关闭文件
void closeFile();

//11.查找用户
User *scanUser(char *uname);
//update
void updateSys();

//写入用户list文件
void writeUser();

//写入文件list文件
void writeDir();
//退出系统
void exitSys();
//test 
void ttt();