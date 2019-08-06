/*
	九宫格游戏
	三个同样的图标存在同一排，同一列或者对角线时游戏胜利
	游戏实现：
		打印开始游戏界面
		循环
			玩家1走棋
			打印棋盘状态
			判断是否有人胜利
			没有胜利
				循环
				否则 游戏结束 打印胜利信息
			玩家2走棋
			打印棋盘状态
			判断是否有人胜利
			没有胜利
				循环
				否则 游戏结束 打印胜利信息
注意事项：
斜对角线上的三个连成直线也代表胜利

不能落子在棋盘外面的无效位置

被下过棋子的位置不能再次下子

当九宫格被填满时若无人胜出则打印平局

*/
#include <stdio.h>
#include <stdlib.h>
#define true 1

// 每走一步后判断是否有人胜利
int weather_any_win(char argc[][3], char flag) {

	int i, j;
	int count = 0;
	int anywin = 0;
	//true 代表有人胜利 false 代表没有人胜利
	// 判断横向是否存在一排同样的flag
	for (j=0; j<3; j++) {
		for (i=0; i<3; i++) {
			if (argc[i][j] == flag) {
				count ++;
			}
		}
		//printf("count = %d\n", count);
		if (count == 3) {
			anywin = 1;
		}
		count = 0;
	}

	// 判断纵向是否存在一列同样的flag
	for (i=0; i<3; i++) {
		for (j=0; j<3; j++) {
			if (argc[i][j] == flag) {
				count ++;
			}
		}
		//printf("count = %d\n", count);
		if (count == 3) {
			anywin = 1;
		}
		count = 0;
	}

	// 判断对角线上是否构成一排同样的flag
	for (i=0; i<3; i++) {
        if (argc[i][i] == flag) {
            count ++;
        }
        //printf("count = %d\n", count);
        if (count == 3) {
            anywin = 1;
        }
	}
    count = 0;

	for (i=0; i<3; i++) {
        if (argc[i][2-i] == flag) {
            count ++;
			}
		if (count == 3) {
			anywin = 1;
		}
	}

	return anywin;
}

void print_state(char argc[][3]) {

	int i, j;
	for (i=0; i<3; i++){
		for (j=0; j<3; j++) {
			printf("  %c", argc[i][j]);
		}
		printf("\n");
	}
}

int falling_chess(char a[][3], char flag) {

	int location;
	int i, j;
	char wrong = 'F';
	printf("please falling chess piece\n");
	scanf("%d", &location);
	i = location / 10 - 1;
	j = location % 10 - 1;
    if (a[i][j] == '?') {
        switch (location){
            case 11 : a[0][0] = flag; break;
            case 12 : a[0][1] = flag; break;
            case 13 : a[0][2] = flag; break;
            case 21 : a[1][0] = flag; break;
            case 22 : a[1][1] = flag; break;
            case 23 : a[1][2] = flag; break;
            case 31 : a[2][0] = flag; break;
            case 32 : a[2][1] = flag; break;
            case 33 : a[2][2] = flag; break;
            default :
                printf("The location you entered is invalid. Please re-enter:\n");
                wrong = 'T';
                return wrong;
        }
	} else {
        printf("The chess piece already exists in the position, your position is illegal");
        wrong = 'T';
        return wrong;
	}
	return 0;
}

void game_start(){
	printf("Game start !\n");
	printf("Please choose your role.\n");
}

void game_over(char flag) {

	printf("Game_over\n");
	if (flag == 'x') {
		printf("Winner is %c!\n", flag);
	} else {
		printf("Winner is %c!\n", flag);
	}
}

int main()
{
	char checkerboard[3][3] = {{'?', '?', '?'}, {'?', '?', '?'}, {'?', '?', '?'}};
	char flag = 'x';
	int i, j, full = 1;

	game_start();

	while (true) {
		if (flag == 'x') {
			printf("The x chess piece moves:\n");
		} else {
			printf("The o chess piece moves:\n");
		}

		if (falling_chess(checkerboard, flag) == 'T') {
            continue;
		}

		print_state(checkerboard);
		full = 1;

		for (i=1; i<3; i++) {
            for (j=1; j<3; j++) {
                if (checkerboard[i][j] == '?') {
                    full = 0;
                }
            }
		}
        // 测试九宫格是否满了，若是满了并且没有检测到某方胜利，则输出平局
        //printf("weather_any_win(checkerboard, falg) = %d", weather_any_win(checkerboard, flag));
        //printf("full = %d", full);
		if (weather_any_win(checkerboard, flag)) {
			game_over(flag);
			break;
		} else if (!weather_any_win(checkerboard, flag) && full) {
            printf("Game over, the result is a draw\n");
            break;
		} else {
			printf("Game continue, another person is playing chess\n");
		}

		if (flag == 'x') {
			flag = 'o';
		} else {
			flag = 'x';
		}
	}
	printf("Please press any key to exit the program...");
	getchar();
	return 0;
}
