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
	int initial_money;
	printf("请输入玩家初始金额(资金范围1000 - 50000)：");
	scanf("%d",&initial_money);
	if(initial_money>=1000&&initial_money<=50000)
	{
		game->initial_money=initial_money;
	}else{
		game->initial_money=10000;
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
	char number[MAX_PLAYER_NUM+1] ;
	int i;	// 循环控制变量
	printf("请选择2~4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）：\n");
	scanf("%s",number);
	while(analyse_players(number))
	{
		printf("请选择2~4位不重复玩家，输入编号即可（1、钱夫人；2、阿土伯；3、孙小美；4、金贝贝）：\n");
		scanf("%s",number);
	}
	game->player_num=strlen(number);
	for(i=0;i<strlen(number);i++)
	{
		game->players[i].id=number[i]-'0';
		game->players[i].money=game->initial_money;	// 玩家所拥有的资金
		game->players[i].point=0;	//玩家所拥有的点数
		game->players[i].days=0;
		game->players[i].pos=0;	// 玩家当前位置，0为起点，向顺时针方向增长坐标
		game->players[i].status=NORMAL;	// 玩家的状态，例如在医院里为'H'，在监狱里为'P'
		game->players[i].place_amount=0;	// 固定资产中的土地的数量
		game->players[i].house_amount=0;	// 固定资产中的房屋的数量
		game->players[i].block_amount=0;	// 玩家拥有的路障的数量
		game->players[i].bomb_amount=0;	// 玩家拥有的炸弹的数量
		game->players[i].robot_amount=0;	// 玩家拥有的机器娃娃的数量
		init_player(game,i,number[i]);
	}
}

/*
* 函数 void init_player(Game *game,int index,char number);
* 参数：game 指向游戏数据结构体的指针
* 参数：index 当前玩家的下标
* 参数：number 当前玩家的名字标识
* 作用：初始化游戏玩家的不重复数据
* 作者：唐家轩
*/
void init_player(Game *game,int index,char number)
{
	switch(number)
	{
		case '1':
			strcpy(game->players[index].name,"钱夫人");
			game->players[index].acronym='Q';
			//game->players[index].color=223322;
			break;
		case '2':
			strcpy(game->players[index].name,"阿土伯");
			game->players[index].acronym='A';
			//game->players[index].color=223322;
			break;
		case '3':
			strcpy(game->players[index].name,"孙小美");
			game->players[index].acronym='S';
			//game->players[index].color=223322;
			break;
		case '4':
			strcpy(game->players[index].name,"金贝贝");
			game->players[index].acronym='J';
			//game->players[index].color=223322;
			break;
		default:break;
	}
}

/*
* 函数 int analyse_players(char *number);
* 参数：number 输入的玩家编号数组的指针
* 作用：分析输入的玩家编号和个数是否合法
* 作者：唐家轩
*/
int analyse_players(char *number)
{
	int flag=0;										//flag为标识符；
	int count1=0,count2=0,count3=0,count4=0;		//count1,count2,count3,count4分别表示编号1，2，3，4的个数；
	int i;		// 循环控制变量
	if(strlen(number)<2||strlen(number)>4)
	{
		flag++;
	}
	for(i=0;i<strlen(number);i++)				//统计各个编号的个数
	{
		switch(number[i])
		{
			case '1':
				count1++;
				break;
			case '2':
				count2++;
				break;
			case '3':
				count3++;
				break;
			case '4':
				count4++;
				break;
			default:
				flag++;
				break;
		}
	}
	if(count1>1||count2>1||count3>1||count4>1)
		{
			flag++;
		}
	return flag;
}

/*
* 函数 void init_map(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：初始化游戏中的地图数据
* 作者：唐家轩
*/
void init_map(Game *game)
{
	int i;			// 循环控制变量
	game->current_player_index=0;
	game->place_num=MAX_PLACE_NUM;
	//初始化起点S；
	game->map[0].type=START;
	game->map[0].owner=NULL;
	game->map[0].price=0;
	game->map[0].tools_type='\0';
	game->map[0].x=0;
	game->map[0].y=0;
	//初始化地段1；
	for(i=1;i<28;i++)
	{
		game->map[i].type=LAND;
		game->map[i].owner=NULL;
		game->map[i].price=200;
		game->map[i].tools_type='\0';
		game->map[i].x=0;
		game->map[i].y=i;
	}
	//初始化医院H；
	game->map[14].type=HOSPITAL;
	game->map[14].price=0;
	//初始化道具屋T；
	game->map[28].type=TOOLS_HOUSE;
	game->map[28].owner=NULL;
	game->map[28].price=0;
	game->map[28].tools_type='\0';
	game->map[28].x=0;
	game->map[28].y=28;
	//初始化地段2；
	for(i=1;i<7;i++)
	{
		game->map[i+28].type=LAND;
		game->map[i+28].owner=NULL;
		game->map[i+28].price=500;
		game->map[i+28].tools_type='\0';
		game->map[i+28].x=i;
		game->map[i+28].y=28;
	}
	//初始化礼品屋G；
	game->map[35].type=GIFT_HOUSE;
	game->map[35].owner=NULL;
	game->map[35].price=0;
	game->map[35].tools_type='\0';
	game->map[35].x=7;
	game->map[35].y=28;
	//初始化地段3；
	for(i=1;i<28;i++)
	{
		game->map[i+35].type=LAND;
		game->map[i+35].owner=NULL;
		game->map[i+35].price=300;
		game->map[i+35].tools_type='\0';
		game->map[i+35].x=7;
		game->map[i+35].y=28-i;
	}
	//初始化监狱P；
	game->map[49].type=PRISON;
	game->map[49].price=0;
	//初始化魔法屋M；
	game->map[63].type=MAGIC_HOUSE;
	game->map[63].owner=NULL;
	game->map[63].price=0;
	game->map[63].tools_type='\0';
	game->map[63].x=7;
	game->map[63].y=0;
	//初始化矿地$；
	for(i=1;i<7;i++)
	{
		game->map[i+63].type=MINE;
		game->map[i+63].owner=NULL;
		game->map[i+63].tools_type='\0';
		game->map[i+63].x=7-i;
		game->map[i+63].y=0;
	}
	game->map[64].price=20;
	game->map[65].price=80;
	game->map[66].price=100;
	game->map[67].price=40;
	game->map[68].price=80;
	game->map[69].price=60;
}

/*
* 函数 void init_others(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：初始化游戏中的其他数据，程序所用的随机种子在此进行设置
* 作者：唐家轩
*/
void init_others(Game *game)
{
	srand(time(NULL));
}