#include "init.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
* 函数 void init_money(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：初始化每位玩家的资金，初始资金范围1000 - 50000，默认10000
* 作者：唐家轩
*/
void init_money(Game *game)
{
	int init_money;
	printf("请输入玩家初始金额(资金范围1000 - 50000)：");
	scanf("%d",&init_money);
	if(init_money>=1000&&init_money<=50000)
	{
		game->init_money=init_money;
	}else{
		game->init_money=10000;
	}
}

/*
* 函数 void init_players(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：初始化游戏中的玩家数据
* 作者：
*/
void init_players(Game *game)
{
	int player_num;
	printf("请输入玩家个数（玩家个数范围为2~4）：");
	scanf("%d",&player_num);
	while(player_num<2||player_num>4)
	{
		printf("请重新输入玩家个数（玩家个数范围为2~4）：");
		scanf("%d",&player_num);
	}
	game->player_num=player_num;
	game->current_player_index=1;
	game->place_num=MAX_PLACE_NUM;
	for(int i=0;i<player_num;i++)
	{
		game->players[i].id=i+1;
		game->players[i].money=game->init_money;	// 玩家所拥有的资金
		game->players[i].point=0;	//玩家所拥有的点数
		game->players[i].pos=0;	// 玩家当前位置，0为起点，向顺时针方向增长坐标
		game->players[i].status=0;	// 玩家的状态，例如在医院里为'H'，在监狱里为'P'
		game->players[i].place_amount=0;	// 固定资产中的土地的数量
		game->players[i].house_amount=0;	// 固定资产中的房屋的数量
		game->players[i].block_amount=0;	// 玩家拥有的路障的数量
		game->players[i].bomb_amount=0;	// 玩家拥有的炸弹的数量
		game->players[i].robot_amount=0;	// 玩家拥有的机器娃娃的数量
		init_player(game,game->players[i].id);
	}
}

/*
*函数 void init_player(Game *game);
*参数：id 当前玩家的id
*作用：初始化游戏玩家的不重复数据
*作者：唐家轩
*/
void init_player(Game *game,int id)
{
	switch(id)
	{
		case 1:
			strcpy(game->players[id-1].name,"钱夫人");
			game->players[id-1].acronym='Q';
			//game->players[id-1].color=223322;
			break;
		case 2:
			strcpy(game->players[id-1].name,"阿土伯");
			game->players[id-1].acronym='A';
			//game->players[id-1].color=223322;
			break;
		case 3:
			strcpy(game->players[id-1].name,"孙小美");
			game->players[id-1].acronym='S';
			//game->players[id-1].color=223322;
			break;
		case 4:
			strcpy(game->players[id-1].name,"金贝贝");
			game->players[id-1].acronym='J';
			//game->players[id-1].color=223322;
			break;
		default:break;
	}
}

/*
* 函数 void init_map(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：初始化游戏中的地图数据
* 作者：
*/
void init_map(Game *game)
{

}

/*
* 函数 void init_others(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：初始化游戏中的其他数据，程序所用的随机种子在此进行设置
* 作者：
*/
void init_others(Game *game)
{
	srand(time(NULL));
}