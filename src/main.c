#include "command.h"
#include "helper.h"
#include "init.h"
#include "types.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
void play_round(Game *game,int id);

int main()
{
	Game game;	// 游戏数据的结构体变量

	// 初始化每位玩家的资金
	init_money(&game);
	// 初始化玩家
	init_players(&game);
	// 初始化地图
	init_map(&game);
	// 初始化游戏中的其他数据
	init_others(&game);

	// 输出地图
	output_map(&game);

	// 以下为游戏主要流程，可根据需要修改代码
	while (1)
	{
	   play_round(&game,game.current_player_index); //根据当前玩家下标，开始该玩家的回合 
	    if(game.player_num<=1)        //如果游戏人数只有1人，判定为胜利者 
	    {
		   printf("恭喜%s，获得游戏胜利！",game.players[game.current_player_index].name); 
		   break;
		} 
		else next_player(&game);   //跳到下一玩家的回合 
				
	} 

	// 游戏所用资源的释放，如果使用了malloc函数分配内存，在这里调用free函数进行释放

	return 0;
}


void play_round(Game *game, int id)
{
	char command[10];
	int pos;
	Place *place;
	char *pchar;	// 用于存储字符串中某命令字符串首次出现的地址
	int number;	// 用于存储部分命令的参数

	system("cls");
	output_map(game);
	show_current_player(game);
	str_tolower(get_command(command, 10));
	while ((strstr(command, "roll") == 0) && (strstr(command, "step") == 0))  //在摇骰子之前，可以执行 很多命令 
	{
		parse_command(game, command);
		system("cls");                //执行每个命令后清屏 
		output_map(game);
		show_current_player(game);
		str_tolower(get_command(command, 10));

	}
	if(strstr(command, "roll"))
	{
		roll(game);      //摇骰子 
	}
	else if(strstr(command, "step"))
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
	
	system("cls");
	output_map(game);    //重绘地图， 更新玩家位置 

	pos = game->players[game->current_player_index].pos;
	place = &game->map[pos];
	if (place->owner == NULL)  //如果土地没有主人，进行判定 
	{
		switch (place->type)
		{
		case LAND:
			buy_land(game);   //是普通空地，进行购买 
			break;
		case HOSPITAL:
			printf("您来到了医院！\n");
			break;
		case PRISON:
			printf("您来到了监狱！\n");
			break;
		case MAGIC_HOUSE:
			printf("您来到了魔法屋！\n");
			break;
		case TOOLS_HOUSE:
			buy_bomb(game);

			break;
		case GIFT_HOUSE:
			printf("您来到礼品屋了！\n");
			break;
		case MINE:
			game->players[game->current_player_index].point += place->price;
			printf("您正处于矿地上！获得点数%d\n",place->price);
			break;
		}
		system("pause");
	}

	else if (place->owner == &game->players[game->current_player_index])  //土地是当前玩家的，升级房屋 
		update_land(game);
	else   
		pay_others_land(game);	   //土地是别人的，支付过路费 

}
