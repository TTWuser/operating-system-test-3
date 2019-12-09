#include "main.h"
void initSystem() {
	//初始化系统
	u_list = (user_list_head*)malloc(sizeof(user_list_head));
	d_list = (dir_list_head*)malloc(sizeof(dir_list_head));

	u_list->user_num = 0;
	d_list->dir_num = 0;

	strcpy(user.user_name, "nnn");
	strcpy(user.user_pass, "nnn");
	
	FILE *fp, *ufp;
	fp = fopen(SYSTEM_DIR, "r");
	ufp = fopen(SYSTEM_USER, "r");

	if (fp == NULL) {
		printf("init sys_dir is un-ok\n");
		return;
	}
	else {
		printf("init sys_dir is ok\n");

	}
	if (ufp == NULL) {
		printf("init sys_usr is un-ok\n");
		return;
	}
	else {
		printf("init sys_usr is ok\n");
	}
	int d_num = 0;

	while (getc(ufp) != EOF) {
		d_num++;
	}
	if ((d_num == 0) || (d_num != sizeof(user_list_head))) {
		printf("system file is break down\n");
		return;
	}
	d_num = 0;
	while (getc(fp) != EOF) {
		d_num++;
	}

	if ((d_num == 0) || (d_num != sizeof(dir_list_head))) {
		printf("system file is break down\n");
		return;
	}
	fseek(fp, 0, SEEK_SET);
	fseek(ufp, 0, SEEK_SET);
	// dir_list_head *dd_list=(dir_list_head *)malloc(sizeof(dir_list_head));
	// user_list_head *uu_list=(user_list_head *)malloc(sizeof(user_list_head));

	fread(d_list, sizeof(dir_list_head), 1, fp);
	fread(u_list, sizeof(user_list_head), 1, ufp);

	// printf("size:%d,dnum:%d,seek addr:%d++\n", sizeof(dir_list_head), d_num, ftell(fp));
	// printf("size:%d,dnum:%d,seek addr:%d++\n", sizeof(user_list_head), d_num, ftell(ufp));

	// for (int i = 0; i < d_list->dir_num; i++) {
	// 	printf("init dirname:%s--\n", (d_list->dir_list+i)->dir_name);
	// }
	// for (int i = 0; i < u_list->user_num; i++) {
	// 	printf("init username:%s--\n", (u_list->user_list+i)->user_name);
	// }
	// u_list.user_num = uu_list->user_num;
	// for(int i=0;i<MAX_USER;i++) {
	// 	u_list.user_list[i] = uu_list->user_list[i];
	// }
	//
	// d_list.dir_num = dd_list->dir_num;
	// for(int i=0;i<MAX_DIR;i++) {
	// 	d_list.dir_list[i] = dd_list->dir_list[i];
	// 	printf("init dirname:%s--%s\n", dd_list->dir_list[i].dir_name, d_list.dir_list[i].dir_name);
	// }
	printf("init system complete!\n");

	// free(dd_list);
	// free(uu_list);
	// 
	fclose(fp);
	fclose(ufp);
}

void createUser(User newUser) {
	if (u_list->user_num == MAX_USER) {
		printf("用户数量已经满员,不能添加!\n");
		return;
	}

	u_list->user_num++;
	//struct *new_user = (struct user*)malloc(sizeof(struct user));
	(*(u_list->user_list+(u_list->user_num-1))) =newUser;

	printf("user is created user_name:%s---ddd:%s\n", newUser.user_name, (*(u_list->user_list + (u_list->user_num - 1))).user_name);

	//写入用户文件
	writeUser();
	//自动添加文件夹
	createDir(newUser);
}

void createDir(User newUser) {
	if (d_list->dir_num == MAX_DIR) {
		printf("dir num is full!\n");
		return;
	}
	Dir new_dir;
	char fname[8];
	strncpy(fname, newUser.user_name,8);
	new_dir.file_num = 0;
	strcpy(new_dir.dir_name, fname);
	// printf("dir--name:%s--num:%d\n", new_dir.dir_name, new_dir.file_num);
	d_list->dir_num++;
	
	(*(d_list->dir_list+(d_list->dir_num-1))) = new_dir;
	// printf("dir is created dir_name:%s,dirname:%s,lldirname:%s\n", new_dir.dir_name, (*(d_list->dir_list + (d_list->dir_num - 1))).dir_name, (*(d_list->dir_list)).dir_name);
	writeDir();
}

User *scanUser(char *uname) {
	User *uuser=NULL;

	if (u_list->user_num == 0) {
		printf("no user please register!\n");
		return uuser;
	}
	
	for (int i = 0; i < u_list->user_num; i++) {
		if (!strcmp((*(u_list->user_list+i)).user_name,uname)) {
			uuser = (u_list->user_list + i);
		}
	}
	return uuser;
}

bool login(User *newUser) {
	
	User *thisuser = scanUser(newUser->user_name);
	// printf("user-login:%s,%s\n", thisuser->user_name, thisuser->user_pass);
	if (thisuser == NULL) {
		printf("no user:%s\n", user.user_name);
		return false;
	}

	// printf("loginuuu:%s", newUser->user_name);
	// printf("logipppp:%s", newUser->user_pass);
	if (strcmp(thisuser->user_pass , newUser->user_pass)==0) {
		strcpy(user.user_name, newUser->user_name);
		strcpy(user.user_pass, newUser->user_pass);
		return true;
	}
	strcpy(user.user_name, "nnn");
	strcpy(user.user_pass, "nnn");
	return false;
}
Dir *scanDir(char *uname) {
	Dir *dir = NULL;
	for (int i = 0; i < d_list->dir_num; i++) {
		if (!strcmp((*(d_list->dir_list+i)).dir_name ,uname)) {
			dir = (d_list->dir_list + i);
		}
	}
	return dir;
}
//新建文件 
void createFile() {
	// printf("tttttt:%s\n", user.user_name);
	if (strncmp(user.user_name, "nnn", 3) == 0) {
		printf("no login please login!\n");
		return;
	}
	char *file_name = (char*)malloc(sizeof(char)*8);
	int permission;

	printf("please enter filename(max 8B):");
	scanf("%s", file_name);

	printf("\nplease enter permission(1,2,3):");
	scanf("%d", &permission);

	char str[128];
	printf("\nplease enter your text (max:128B)\n");
	scanf("%s", &str);
	int i = strlen(str);
	// printf("length:%d\n", i);
	
	File file;
	strncpy(file.file_name, file_name,8);
	
	file.permission = permission;
	file.file_size = i;
	free(file_name);
	
	char target[i];
	strncpy(target, str, i);
	// printf("file-name:%s\n", file.file_name);
	FILE *ffp = fopen(file.file_name, "w");
	if (ffp == NULL) {
		printf("error\n");
		return;
	}

	if (fwrite(target, i, 1, ffp) != 1) {
		printf("error could not save\n");
		fclose(ffp);
		return;
	}

	fflush(ffp);
	fclose(ffp);

	Dir *dir = scanDir(user.user_name);
	// printf("---uuu-:%d,%s\n", (dir == NULL), user.user_name);

	if (dir == NULL) {
		return;
	}
	// printf("---nodeID:%d\n", dir->file_num);
	strcpy((dir->file_list + (dir->file_num))->file_name, file.file_name);
	(dir->file_list + (dir->file_num))->file_size = file.file_size;
	(dir->file_list + (dir->file_num))->permission = file.permission;
	dir->file_num++;
	// printf("---nodeID2:%d\n", dir->file_num);

	printf("ddd:--%s-create success ,fnum:%d\n", dir->dir_name, dir->file_num);

	// printf("file->name:%s,per:%d,size:%d\n", file.file_name, file.permission, file.file_size);
	writeDir();
}

void  openFile(char *fname) {
	if (strncmp(user.user_name, "nnn", 3) == 0) {
		printf("no login please login!\n");
		return;
	}
	Dir *dir = scanDir(user.user_name);
	if(dir==NULL) {
		printf("no dir in system!\n");
		return;
	}if(dir->file_num==0) {
		printf("no files!\n");
		return;
	}
	File *file=NULL;

	for(int i=0;i<dir->file_num;i++) {
		if(strcmp((*(dir->file_list+i)).file_name,fname)==0) {
			file = (dir->file_list + i);
		}
	}
	if(file==NULL) {
		printf("no file :%s", fname);
		return;
	}
	char *str = (char*)malloc(sizeof(char)*(file->file_size));
	FILE *fp = fopen(file->file_name, "r");

	if(fread(str, file->file_size, 1, fp)!=1) {
		printf("read file failed!\n");
		fclose(fp);
		free(str);
		return;
	}

	printf("file context:%s\n", str);
	free(fp);
	fclose(fp);
	printf("complete!\n");
}
void showDir(){
	if(d_list->dir_num==0) {
		printf("no dir in system\n");
		return;
	}
	printf("-------this all dir-------\n");
	printf("--- dir_name -- file_num ---\n");
	for(int i=0;i<d_list->dir_num;i++) {
		printf("|--- %s --- %d \n", (*(d_list->dir_list+i)).dir_name, (*(d_list->dir_list + i)).file_num);
	}
	printf("complete!\n");
	
}


void showFiles() {
	// printf("uuuuu:%s\n", user.user_name);
	if(strncmp(user.user_name, "nnn", 3) ==0) {
		printf("no login please login!\n");
		return;
	}
	if (d_list->dir_num == 0) {
		printf("no dir in system\n");
		return;
	}

	Dir *dir = scanDir(user.user_name);
	if(dir==NULL) {
		printf("no dir !\n");
		return;
	}
	if (dir->file_num == 0) {
		printf("dir is empty!\n");
		return;
	}
	printf("-n:%s\n",(*dir).dir_name);
	for(int i=0;i< dir->file_num;i++) {
		printf("---|-n:%s---s:%d---p:%d\n", (*(dir->file_list + i)).file_name, (*(dir->file_list + i)).file_size, (*(dir->file_list + i)).permission);
	}
	printf("complete!\n");
}

//注销
void loginOut() {
	writeDir();
	writeUser();
	strcpy(user.user_name, "nnn");
	strcpy(user.user_pass, "nnn");
}

void exitSys() {
	free(u_list);
	free(d_list);
}


void writeUser() {
	FILE *ufp;
	ufp = fopen(SYSTEM_USER, "w");
	if(ufp==NULL) {
		printf("open file failed!\n");
		return;
	}
	if(fwrite(u_list, sizeof(user_list_head), 1, ufp)==1) {
		printf("save user success!\n");
	}
	fflush(ufp);
	fclose(ufp);
}

void writeDir() {
	FILE *fp;

	fp = fopen(SYSTEM_DIR, "w");
	if (fp == NULL) {
		printf("open file failed!\n");
		return;
	}
	if (fwrite(d_list, sizeof(dir_list_head), 1, fp) == 1) {
		printf("save dir success!\n");
	}
	fflush(fp);
	fclose(fp);
}


void ttt() {
	User *user, uu={
		"name",
		"pass",
		10
	};

	user = &uu;

	printf("1user--%s--%s--%d\n", user->user_name, user->user_pass, user->permission);
	printf("2user--%s--%s--%d\n", uu.user_name, uu.user_pass, uu.permission);
	strcpy(user->user_name, "nnuuun");
	strcpy(user->user_pass, "nnuuun");
	user->permission = 12;
	printf("1user--%s--%s--%d\n", user->user_name, user->user_pass, user->permission);
	printf("2user--%s--%s--%d\n", uu.user_name, uu.user_pass, uu.permission);
	
}

void deleteFile(char *fname) {

	Dir *dir = scanDir(user.user_name);
	if (dir == NULL || dir->file_num == 0) {
		printf("no files\n");
		return;
	}
	int index = scanFile(dir->file_num, dir, fname);
	printf("index:%d\n", index);
	if (index != 10) {
		
		if (remove(fname) != 0) {
			printf("delete file failed!\n");
			return;
		}

		for (index; index < dir->file_num; index++) {
			(*(dir->file_list + index)) = (*(dir->file_list + (index + 1)));
		}

		dir->file_num--;
		printf("delete file success!\n");

		writeDir();
		updateSys();
		return;
	}
	printf("sys error!");
}

void updateSys() {
	FILE *fp, *ufp;
	fp = fopen(SYSTEM_DIR, "r");
	ufp = fopen(SYSTEM_USER, "r");

	if (fp == NULL) {
		printf("update sys_dir is un-ok\n");
		return;
	}
	else {
		printf("update sys_dir is ok\n");

	}
	if (ufp == NULL) {
		printf("update sys_usr is un-ok\n");
		return;
	}
	else {
		printf("update sys_usr is ok\n");
	}
	int d_num = 0;

	while (getc(ufp) != EOF) {
		d_num++;
	}
	printf("num--%d", d_num);
	if ((d_num == 0) || (d_num != sizeof(user_list_head))) {
		printf("system file is break down\n");
		fclose(fp);
		fclose(ufp);
		return;
	}
	d_num = 0;
	while (getc(fp) != EOF) {
		d_num++;
	}

	if ((d_num == 0) || (d_num != sizeof(dir_list_head))) {
		printf("system file is break down\n");
		fclose(fp);
		fclose(ufp);
		return;
	}
	fseek(fp, 0, SEEK_SET);
	fseek(ufp, 0, SEEK_SET);

	fread(d_list, sizeof(dir_list_head), 1, fp);
	fread(u_list, sizeof(user_list_head), 1, ufp);

	fclose(fp);
	fclose(ufp);
}

int scanFile(int num,Dir *dir,char *fname) {
	printf("num:%d,fname:%s\n", num, fname);
	for(int i=0;i<num;i++) {
		printf("fname:%s\n", (*(dir->file_list + i)).file_name);
		if(strcmp((*(dir->file_list+i)).file_name,fname)==0) {
			return i;
		}
	}
	return 10;
}