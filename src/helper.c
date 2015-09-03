#include "helper.h"
#include <stdlib.h>
#include <ctype.h>

/*
* 函数 get_roll_number();
* 作用：获取掷骰子所获得的点数，为1到6，函数所用的随机种子在程序初始化时进行设置
* 返回值：掷骰子所获得的点数，为1到6之间
* 作者：张泰然
*/
int get_roll_number()
{
	return rand() % 6 + 1;
}

/*
* 函数 int get_tools_amount(Player *player);
* 参数：player 指向玩家数据结构体的指针，表示某一玩家
* 作用：获取指定玩家的道具的总数
* 返回值：指定玩家的道具的总数
* 作者：张泰然
*/
int get_tools_amount(Player *player)
{
	return player -> block_amount + player -> bomb_amount + player -> robot_amount;
}

/*
* 函数 void str_tolower(char *str);
* 参数：str 指向字符串的指针
* 作用：将字符串中的字母改为小写形式
* 作者：张泰然
*/
void str_tolower(char *str)
{
	char *temp = str;	// 用来指向字符串的指针

	while (*temp != '\0')
	{
		if (isalpha(*temp))
		{
			*temp = tolower(*temp);	// 将字母改为小写形式
		}
		temp++;
	}
}