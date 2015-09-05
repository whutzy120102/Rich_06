#include "view.h"
#include <stdio.h>
#include <stdlib.h>

/*
* 函数 void output_map(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：输出游戏的地图
* 作者：
*/
void output_map(Game *game)
{
	int i;
	char **map;
	map = init_print_map(game);
	for(i=0;i < game->player_num;i++)
	{
		player_place(game->players[i],map);
	}
	print(map);
	return;
}

/*
* 函数 void show_current_player(Game *game);
* 参数：game 指向游戏数据结构体的指针
* 作用：显示当前玩家
* 作者：
*/
void show_current_player(Game *game)
{
	Player current_player;
	int current_player_index;
	current_player_index = game->current_player_index;
	current_player = game->players[current_player_index];
	printf("%s> \n",current_player.name);
	return;
}

/**
*初始化地图 
**/
char ** init_print_map(Game *game)
{
	int i,j;
	char **map;
	int index_top,index_left,index_right,index_buttom;
	index_top = 0; index_left = 69; index_right = 29; index_buttom = 63;
	map = (char**) malloc(8*sizeof(char*));
	for(i=0;i<8;i++)
	{
		map[i] = (char*) malloc(29*sizeof(char));
		for(j=0;j<29;j++)
		{
			map[i][j] = ' ';
			if(i == 0)
			{
				map[i][j] = game->map[index_top].type;
				//该土地上有道具 
				if(game->map[index_top].tools_type != NULL)
				{
					map[i][j] = game->map[index_top].tools_type;
				}
				index_top++;
			}
			if(i == 7)
			{
				map[i][j] = game->map[index_buttom].type;
				//该土地上有道具 
				if(game->map[index_buttom].tools_type != NULL)
				{
					map[i][j] = game->map[index_buttom].tools_type;
				}
				index_buttom--;
			}
			if( j == 0 && i != 0 && i != 7)
			{
				map[i][j] = game->map[index_left].type;
				//该土地上有道具 
				if(game->map[index_left].tools_type != NULL)
				{
					map[i][j] = game->map[index_left].tools_type;
				}
				index_left--;
			}
			if(j == 28 && i != 0 && i != 7)
			{
				map[i][j] = game->map[index_right].type;
				//该土地上有道具 
				if(game->map[index_right].tools_type != NULL)
				{
					map[i][j] = game->map[index_right].tools_type;
				}
				index_right++;
			}
		}
	}
	return map;
} 

/**
*在map中标注玩家所在位置 
**/
void player_place(Player player,char **map)
{
	int index_top,index_left,index_right,index_buttom;
	index_top = 0; index_left = 69; index_right = 29; index_buttom = 63; 
	unsigned int pos = player.pos;
	if(pos >= 0 && pos < 29)
	{
		map[0][pos] = player.acronym;
	}
	else if(pos > 28 && pos < 35)
	{
		map[pos-28][28] = player.acronym;
	}
	else if(pos > 34 && pos < 64)
	{
		map[7][63-pos] = player.acronym;
	}
	else
	{
		map[70-pos][0] = player.acronym;
	}
	return;
}

/**
*打印地图 
**/
void print(char **map)
{
	int i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<29;j++)
		{
			printf("%c ",map[i][j]);
		}
		printf("\n");
	}
	return;
}

