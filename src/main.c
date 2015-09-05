#include "command.h"
#include "helper.h"
#include "init.h"
#include "types.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include<string.h>
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

	system("cls");
	output_map(game);
	show_current_player(game);
	str_tolower(get_command(command, 10));
	while (command != NULL&&strcmp(command, "roll") != 0)  //在摇骰子之前，可以执行 很多命令 
	{
		parse_command(game, command);
		system("cls");                //执行每个命令后清屏 
		output_map(game);
		show_current_player(game);
		str_tolower(get_command(command, 10));
	}
	roll(game);      //摇骰子 
	system("cls");
	output_map(game);    //重绘地图， 更新玩家位置 

	pos = game->players[game->current_player_index].pos;
	place = &game->map[pos];
	if (place->owner == NULL)  //如果土地没有主人，进行判定 
	{
		switch (place->type)
		{
		case '0':
			buy_land(game);   //是普通空地，进行购买 
			break;
		case 'H':
			printf("您来到了医院！");
			break;
		case 'P':
			printf("您来到了监狱！");
			break;
		case '$':
			printf("您正处于矿地上！");
			break;
		}
	}

	else if (place->owner == &game->players[game->current_player_index])  //土地是当前玩家的，升级房屋 
		update_land(game);
	else   
		pay_others_land(game);	   //土地是别人的，支付过路费 

}
