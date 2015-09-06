#include "command.h"
#include "helper.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* 定义房产类型 */
char *g_house_type[4] = { "空地", "茅屋", "洋房", "摩天楼" };

/*
* 函数 char *get_command(char *buffer, int length);
* 参数：buffer 用来存储输入的命令的缓冲区
* 参数：length 缓冲区的长度
* 作用：获取当前玩家输入的操作命令
* 返回值：指向存储输入的命令的缓冲区的指针
* 作者：张泰然
*/
char *get_command(char *buffer, int length)
{
	char *temp;	// 用来指向缓冲区的指针

	do
	{
		temp = buffer;
		fflush(stdin);	// 清空输入缓冲区
		fgets(buffer, length, stdin);
		while (*temp != '\0')
		{
			if (*temp == '\n')
			{
				*temp = '\0';	// 将换行符处理为'\0'
			}
			temp++;	// 指向下一个字符
		}
	} while (buffer[0] == '\0');

	return buffer;
}

/*
* 函数 void parse_command(char *command);
* 参数：game 指向游戏数据结构体的指针
* 参数：command 当前玩家输入的操作命令字符串
* 作用：解析当前玩家输入的操作命令，执行相应的命令
* 作者：张泰然
*/
void parse_command(Game *game, char *command)
{
	char *pchar;	// 用于存储字符串中某命令字符串首次出现的地址
	int number;	// 用于存储部分命令的参数

	if (strstr(command, "query") != NULL)	// 输入命令为query
	{
		query(game, &game->players[game->current_player_index]);
	}
	else if (strstr(command, "help") != NULL)	// 输入命令为help
	{
		help();
	}
	else if (strstr(command, "sell") != NULL)	// 输入命令为sell n
	{
		pchar = strstr(command, "sell");
		pchar += 4;
		while (isspace(*pchar))
		{
			pchar++;	// 跳过空白字符
		}
		if (*pchar != '\0')
		{
			number = atoi(pchar);
			sell(game, number);
		}
	}
	else if (strstr(command, "step") != NULL)	// 输入命令为step n
	{
		pchar = strstr(command, "step");
		pchar += 4;
		while (isspace(*pchar))
		{
			pchar++;	// 跳过空白字符
		}
		if (*pchar != '\0')
		{
			number = atoi(pchar);
			step(game, number);
		}
	}
	else if (strstr(command, "quit") != NULL)	// 输入命令为quit
	{
		quit();
	}
	else	// 输入的不是合法命令
	{
		printf("您输入的不是合法命令，请输入help命令查看命令帮助\n");
	}
	system("pause");	// 暂停以避免闪烁
}

/*
* 函数 void roll(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：当前玩家掷骰子行走
* 作者：张泰然
*/
void roll(Game *game)
{
	int roll_number;	// 玩家掷骰子所获得的点数
	Player *current_player;	// 指向当前玩家

	roll_number = get_roll_number();	// 获取掷骰子所获得的点数
	current_player = &game->players[game->current_player_index];	// 找到当前玩家
	
	current_player->pos = (current_player->pos + roll_number) % game->place_num;	// 改变玩家的位置

	printf("您前进了%d步\n", roll_number);
	system("pause");	// 暂停以避免闪烁

	// 暂时不考虑路上有道具的情况

}

/*
* 函数 void buy_land(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：当前玩家购买一块未被购买的土地
* 作者：张泰然
*/
void buy_land(Game *game)		
{
	Player *current_player;	// 指向当前玩家
	Place *place;	// 指向玩家行走之后停留的地块，即要购买的地块
	char input[10];

	current_player = &game->players[game->current_player_index];	// 找到当前玩家
	place = &game->map[current_player->pos];	// 找到要购买的地块

	printf("该空地未被购买，您是否花费%d元购买？若购买请输入Y或y，输入其他表示不购买：", place->price);
	fflush(stdin);	// 清空输入缓冲区
	fgets(input, 10, stdin);
	if (input[0] == 'Y' || input[0] == 'y')	// 玩家购买空地
	{
		if (place->type != LAND)	// 要购买的地块不是空地，不合法的操作
		{
			printf("该地块不是空地！\n");
			return;
		}

		if (current_player->money >= place->price)	// 玩家能够买的起地块
		{
			current_player->money -= place->price;	// 从玩家拥有的资金中减去地块的价格
			place->owner = current_player;	// 将地块主人标记为当前玩家
			current_player->place_amount++;	// 玩家土地数量增加
			printf("土地购买成功！\n");
			printf("您购买该块土地花费了%d元，剩余%d元的资金\n", place->price, current_player->money);
		}
		else	// 玩家资金不足
		{
			printf("您的资金不足，无法购买土地！\n");
		}
	}
	else	// 玩家不购买空地
	{
		printf("您选择了不购买土地\n");
	}
	system("pause");	// 暂停以避免闪烁
}

/*
* 函数 void update_land(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：当前玩家升级一块已经购买的土地
* 作者：张泰然
*/
void update_land(Game *game)
{
	Player *current_player;	// 指向当前玩家
	Place *place;	// 指向玩家行走之后停留的地块，即要升级的地块
	char input[10];

	current_player = &game->players[game->current_player_index];	// 找到当前玩家
	place = &game->map[current_player->pos];	// 找到要升级的地块

	if (place->type != '3')	// 该地块可升级
	{
		printf("该地块为%s，可以升级，您是否花费%d元升级？若升级请输入Y或y，输入其他表示不升级：", g_house_type[place->type - '0'], place->price);
		fflush(stdin);	// 清空输入缓冲区
		fgets(input, 10, stdin);
		if (input[0] == 'Y' || input[0] == 'y')	// 玩家升级地块
		{
			if (current_player->money >= place->price)	// 玩家能够升级的起地块
			{
				current_player->money -= place->price;	// 从玩家拥有的资金中减去地块的价格
				place->type++;	// 土地升级
				if (place->type == '1')	// 若当前土地升级之后的等级为'1'，茅屋，表示刚增加了房屋
				{
					current_player->house_amount++;	// 玩家房屋数量增加
				}
				printf("土地升级成功！现在该地块为%s\n", g_house_type[place->type - '0']);
			}
			else	// 玩家资金不足
			{
				printf("您的资金不足，无法升级土地！\n");
			}
		}
		else	// 玩家不升级地块
		{
			printf("您选择了不升级地块\n");
		}
		system("pause");	// 暂停以避免闪烁
	}
}

/*
* 函数 void pay_others_land(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：向其他玩家支付过路费
* 作者：张泰然
*/
void pay_others_land(Game *game)
{
	// 目前暂时不考虑财神附体以及地产主人在医院或监狱

	Player *current_player;	// 指向当前玩家
	Player *place_owner;	// 指向所停留地块的主人
	Place *place;	// 指向玩家行走之后停留的地块，即要支付过路费的地块
	int outcome;	// 所要支付的过路费，即当前玩家的支出

	current_player = &game->players[game->current_player_index];	// 找到当前玩家
	place = &game->map[current_player->pos];	// 找到要支付过路费的地块
	place_owner = place->owner;		// 找到要支付过路费的地块的主人

	outcome = get_place_worth(place) / 2;	 // 计算要支付的过路费，费用为该处房产价值的1/2
	printf("您现在走到了%s的土地上，", place_owner->name);
	switch (place->type)
	{
	case '0':
		printf("该地块为空地，您无需支付过路费！\n");
		system("pause");	// 暂停以避免闪烁
		return;
	case '1':
	case '2':
	case '3':
		// 这三种情况执行的代码相同
		printf("该处房产为%s，您需要支付过路费%d元\n", g_house_type[place->type - '0'], outcome);
		break;
	}
	if (current_player->money >= outcome)	// 玩家能够付的起过路费
	{
		current_player->money -= outcome;
		place_owner->money += outcome;	// 地产主人收取过路费
		printf("您支付了%d元过路费，剩余%d元的资金\n", outcome, current_player->money);
	}
	else	// 玩家付不起过路费
	{
		// 当玩家付不起过路费时，首先出售当前玩家的所有房产，再尝试支付过路费
		sell_all_houses(game, current_player);
		printf("您无法支付过路费，现在系统将自动出售您的所有房产\n");
		if (current_player->money >= outcome)	// 玩家能够付的起过路费
		{
			current_player->money -= outcome;
			place_owner->money += outcome;	// 地产主人收取过路费
			printf("系统出售了您的所有房产后，您支付了%d元过路费，剩余%d元的资金\n", outcome, current_player->money);
		}
		else	// 玩家仍然付不起过路费，此时该玩家宣告破产
		{
			printf("对不起，由于您现在仍然无法支付过路费，您破产了！\n");
			eliminate_player(game, current_player);
		}
	}
	system("pause");	// 暂停以避免闪烁
}

/*
* 函数 void sell_all_houses(Game *game, Player *player);
* 参数：game 指向游戏数据结构体的指针
* 参数：player 指向玩家数据结构体的指针，表示当前玩家
* 作用：出售当前玩家的所有房产
* 作者：张泰然
*/
void sell_all_houses(Game *game, Player *player)
{
	Place *place;	// 指向某地块的指针
	int i;	// 循环控制变量

	for (i = 1; i < game->place_num; i++)
	{
		place = &game->map[i];
		if (place->owner == player && place->type != '0')	// 当某块地的主人是该玩家且不为空地时，要出售的是房产
		{
			sell_one_house(player, place);
		}
	}
}

/*
* 函数 void sell_one_house(Player *player, Place *place);
* 参数：player 指向玩家数据结构体的指针，表示当前玩家
* 参数：place 指向地块数据结构体的指针，表示某一地块
* 作用：执行出售该玩家指定位置的房产的动作
* 备注：该函数不进行验证，由调用者确保参数正确
* 作者：张泰然
*/
void sell_one_house(Player *player, Place *place)
{
	int income;		// 出售房产所获得的收入

	income = get_place_worth(place) * 2;	// 出售价格为投资总成本的2倍
	player->money += income;	// 玩家获得收入
	player->house_amount--;	// 玩家房屋数量减少
	place->type = LAND;	// 出售房产后该地块成为空地
}

/*
* 函数 void eliminate_player(Game *game, Player *player);
* 参数：game 指向游戏数据结构体的指针
* 参数：player 指向玩家数据结构体的指针，表示当前玩家
* 作用：对该玩家执行破产处理
* 作者：张泰然
*/
void eliminate_player(Game *game, Player *player)
{
	Place *place;	// 指向某地块的指针
	int i;	// 循环控制变量

	for (i = 1; i < game->place_num; i++)
	{
		place = &game->map[i];
		if (place->owner == player)	// 当某块地的主人是该玩家时
		{
			player->place_amount--;	// 玩家土地数量减i少
			place->type = LAND;	// 出售房产后该地块成为空地
			place->owner = NULL;	// 将该土地归还系统
		}
	}
	player->money = 0;
	player->point = 0;
	player->pos = 0;
	player->status = OUT;
	player->block_amount = 0;
	player->bomb_amount = 0;
	player->robot_amount = 0;
}

/*
* 函数 void sell(Game *game, int pos);
* 参数：game 指向游戏数据结构体的指针
* 参数：pos 房产在地图上的绝对位置
* 作用：当前玩家出售指定位置的房产
* 作者：张泰然
*/
void sell(Game *game, int pos)
{
	char input[10];
	Player *current_player;	// 指向当前玩家
	Place *place;	// 指向玩家要出售房产的地块

	if (pos < 1 || pos > game->place_num - 1)
	{
		printf("您输入的绝对位置有误！\n");
		return;
	}

	current_player = &game->players[game->current_player_index];	// 找到当前玩家
	place = &game->map[pos];	// 找到要出售的地块

	if (place->owner == current_player)	// 要出售房产的土地是当前玩家的
	{
		if (place->type != LAND)	// 在不是空地的情况下才能出售房产
		{
			printf("您确定要出售位于%d的房产吗？若出售请输入Y或y，输入其他表示不出售：", pos);
			fflush(stdin);	// 清空输入缓冲区
			fgets(input, 10, stdin);
			if (input[0] == 'Y' || input[0] == 'y')	// 玩家出售房产
			{
				sell_one_house(current_player, place);
			}
			else	// 玩家不出售房产
			{
				printf("您选择了不出售房产\n");
			}
		}
		else	// 空地没有房产可以出售
		{
			printf("您输入的该位置处的土地没有房产可以出售！\n");
		}
	}
	else	// 要出售的房产不是当前玩家的
	{
		printf("对不起，您输入的该位置处的土地不是您的！\n");
	}
}

/*
* 函数 void query(Game *game, Player *player);
* 参数：game 指向游戏数据结构体的指针
* 参数：player 指向玩家数据结构体的指针，表示某一玩家
* 作用：显示玩家资产信息
* 作者：张泰然
*/
void query(Game *game, Player *player)
{
	int i;	// 循环控制变量
	Place *place; // 指向某地块的指针

	printf("%s有资产如下所示：\n资金：%d元\n点数：%d点\n", player->name, player->money, player->point);
	printf("道具：路障%d个，机器娃娃%d个，炸弹%d个\n", player->block_amount, player->robot_amount, player->bomb_amount);
	if (player->place_amount != 0)	// 玩家有土地
	{
		printf("固定资产如下：\n土地%d块，房屋%d栋，具体如下：\n", player->place_amount, player->house_amount);
		printf("\t类型\t绝对位置\n");
		for (i = 1; i < game->place_num; i++)
		{
			place = &game->map[i];
			if (place->owner == player)	// 当某块地的主人是该玩家时
			{
				printf("\t%s\t%d\n", g_house_type[place->type - '0'], i);
			}
		}
	}
	else	// 玩家没有土地
	{
		printf("固定资产：无土地和房屋\n");
	}
}

/*
* 函数 void step(Game *game, int number);
* 参数：game 指向游戏数据结构体的指针
* 参数：number 指定的行走步数
* 作用：实现遥控骰子功能，行走指定的任意的步数
* 作者：张泰然
*/
void step(Game *game, int number)
{
	Player *current_player;	// 指向当前玩家

	current_player = &game->players[game->current_player_index];	// 找到当前玩家
	current_player->pos = (current_player->pos + number) % game->place_num;	// 改变玩家的位置
	printf("您前进了%d步\n", number);
}

/*
* 函数 void help();
* 作用：显示各个命令的使用说明
* 作者：张泰然
*/
void help()
{
	printf("命令\t功能说明\n");
	printf("roll\t掷骰子命令\n");
	printf("sell n\t出售自己的任意房产，出售价格为投资总成本的2倍，n为房产在地图上的绝对位置\n");
	printf("query\t显示自家资产信息\n");
	printf("help\t查看命令帮助\n");
	printf("quit\t强制退出\n");
	printf("step n\t遥控骰子，n为指定的步数\n");
}

/*
* 函数 void quit();
* 作用：强制结束游戏
* 作者：张泰然
*/
void quit()
{
	printf("即将结束游戏！\n");
	exit(0);
}

/*
* 函数 void next_player(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：交权给下一个玩家
* 作者：张泰然
*/
void next_player(Game *game)
{
	Player *player;	// 用来存储某一玩家的指针

	// 对于下一个玩家，先检查该玩家的状态，若不是正常状态，则再检查下一个玩家，直到某玩家的状态为正常为止
	do
	{
		game->current_player_index = (game->current_player_index + 1) % game->player_num;
		player = &game->players[game->current_player_index];	// 找到下一个玩家
	} while (player->status != NORMAL);
}