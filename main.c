#include"main.h"

int main()
{
	
	initSystem();

	printf("----welcome !----\n");
	// int choose = 1;
	User newUser;
	char choose_str[16];
	printf("# ");
	scanf("%s", choose_str);
	char name[8], pass[8];
	// printf("cc:%s\n", choose_str);
	while(strcmp(choose_str,"exit")!=0) {
		if(!strcmp(choose_str, "register")) {
			printf("name:");
			scanf("%s", name);
			printf("pass:");
			scanf("%s", pass);
			
			strcpy(newUser.user_name, name);
			strcpy(newUser.user_pass, pass);

			createUser(newUser);
		}else if (!strcmp(choose_str, "login")) {
			printf("name:");
			scanf("%s", name);
			printf("pass:");
			scanf("%s", pass);

			strcpy(newUser.user_name, name);
			strcpy(newUser.user_pass, pass);
			if (login(&newUser) == true) {
				printf("login success!\n");
			}
			else {
				printf("login failed!\n");
			}
		}else if (!strcmp(choose_str, "create")) {
			createFile();
		}else if (!strcmp(choose_str, "dirs")) {
			showDir();
		}else if (!strcmp(choose_str, "dir")) {
			showFiles();
		}else if (!strcmp(choose_str, "open")) {
			printf("input filename:");
			scanf("%s", name);
			openFile(name);
		}else if (!strcmp(choose_str, "delete")) {
			printf("input filename:");
			scanf("%s", name);
			deleteFile(name);
		}else if (!strcmp(choose_str, "loginout")) {
			loginOut();
		}else if (!strcmp(choose_str, "help")) {
				printf("---help---help---\nchoose cmd:<register-register><login-login><dirs-showDirs><dir-showFiles>\n<open-openFile><create-createFile><loginout-loginOut><exit-exit>\n");
		}
		else {
			printf("command error no cmd:%s\n",choose_str);
		}
		printf("# ");
		scanf("%s", choose_str);
	}
	exitSys();
	printf("bye!\n");
	// while (choose!=0) {
	// 	printf("choose<1.register><2.login><3.showDir><4.showFiles><5.createFile><9.loginOut><0.exit>\n");
	// 	char name[8], pass[8];
	// 	printf("please choose:");
	// 	scanf("%d", &choose);
	// 	switch (choose) {
	// 	case 1:
	// 		
	// 		printf("name:");
	// 		scanf("%s", name);
	// 		printf("pass:");
	// 		scanf("%s", pass);
	//
	// 		strcpy(newUser.user_name, name);
	// 		strcpy(newUser.user_pass, pass);
	//
	// 		createUser(newUser);
	// 		break;
	// 	case 2:
	// 		printf("name:");
	// 		scanf("%s", name);
	// 		printf("pass:");
	// 		scanf("%s", pass);
	//
	// 		strcpy(newUser.user_name, name);
	// 		strcpy(newUser.user_pass, pass);
	// 		if(login(&newUser)==true) {
	// 			printf("login success!\n");
	// 		}else {
	// 			printf("login failed!\n");
	// 		}
	// 		break;
	// 	case 3:
	// 		showDir();
	// 		break;
	// 	case 4:
	// 		showFiles();
	// 		break;
	// 	case 5:
	// 		createFile();
	// 		break;
	// 	case 6:
	// 		break;
	// 	case 9:
	// 		loginOut();
	// 		break;
	// 	case 0:
	// 		exitSys();
	// 		break;
	// 	default:
	// 		printf("no operation!");
	// 		break;
	// 	}
	// }
	// wait(0);
	return 0;
}