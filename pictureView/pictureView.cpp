#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <limits.h>
#include <graphics.h>
#include <tchar.h>

int getdir(char *,FILE *);

int main() {

	IMAGE img;
	int n = 1,c;
	char str[100];
	FILE *readfile;
	// 绘图环境初始化
	initgraph(1280, 720);
	system("dir \"D:\\miku\" /b /s > dir.txt");//读取目录
	if ((readfile = fopen("dir.txt", "r")) == NULL) {
		printf("读取目录失败");
		_getch();
		return 1;
	}

	while (c=getdir(str,readfile)){
		if (c == -1)continue;
		loadimage(&img, str, 0, 0, true);//读取图片
		if (img.getwidth() >= 1280)//调整图片大小
			loadimage(&img, str, 1280, img.getheight() * 1280 / img.getwidth(), true);
		if (img.getheight() >= 720)
			loadimage(&img, str, img.getwidth() * 720 / img.getheight(), 720, true);
		cleardevice();//清除画面 准备显示图片

		putimage(0, 0, &img);
		n++;
		//_getch();_getch();
		Sleep(200);
	}

	fclose(readfile);
	system("del dir.txt");
	return 0;
}

int getdir(char *a,FILE *b) {
	
	int d = 0;
	
	for (char c; (c = fgetc(b)) != '\n'&&d < 100; d++) {
		if (feof(b) != 0)//判断一下是否文件尾
			return 0;
		a[d] = c;
	}
	a[d] = '\0';
	if (d >= 4)
	{
		d -= 4;
		if (strcmp(a + d, ".jpg") != 0)
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	return 1;
}