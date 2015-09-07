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
	Game game;	// ��Ϸ���ݵĽṹ�����

	// ��ʼ��ÿλ��ҵ��ʽ�
	init_money(&game);

	// ��ʼ�����
	init_players(&game);
	// ��ʼ����ͼ
	init_map(&game);
	// ��ʼ����Ϸ�е���������
	init_others(&game);

	// �����ͼ
	output_map(&game);

	// ����Ϊ��Ϸ��Ҫ���̣��ɸ�����Ҫ�޸Ĵ���
	while (1)
	{
	   play_round(&game,game.current_player_index); //���ݵ�ǰ����±꣬��ʼ����ҵĻغ� 
	    if(game.player_num<=1)        //�����Ϸ����ֻ��1�ˣ��ж�Ϊʤ���� 
	    {
		   printf("��ϲ%s�������Ϸʤ����",game.players[game.current_player_index].name); 
		   break;
		} 
		else next_player(&game);   //������һ��ҵĻغ� 
				
	} 

	// ��Ϸ������Դ���ͷţ����ʹ����malloc���������ڴ棬���������free���������ͷ�

	return 0;
}


void play_round(Game *game, int id)
{
	char command[10];
	int pos;
	Place *place;
	char *pchar;	// ���ڴ洢�ַ�����ĳ�����ַ����״γ��ֵĵ�ַ
	int number;	// ���ڴ洢��������Ĳ���
	Player *current_player;	// ָ��ǰ���

	system("cls");
	output_map(game);
	show_current_player(game);
	str_tolower(get_command(command, 10));
	while ((strstr(command, "roll") == 0) && (strstr(command, "step") == 0))  //��ҡ����֮ǰ������ִ�� �ܶ����� 
	{
		parse_command(game, command);
		system("cls");                //ִ��ÿ����������� 
		output_map(game);
		show_current_player(game);
		str_tolower(get_command(command, 10));

	}
	if(strstr(command, "roll"))
	{
		roll(game);      //ҡ���� 
	}
	else if(strstr(command, "step"))
	{
		pchar = strstr(command, "step");
		pchar += 4;
		while (isspace(*pchar))
		{
			pchar++;	// �����հ��ַ�
		}
		if (*pchar != '\0')
		{
			number = atoi(pchar);
			step(game, number);
		}
	}
	
	system("cls");
	output_map(game);    //�ػ��ͼ�� �������λ�� 

	pos = game->players[game->current_player_index].pos;
	place = &game->map[pos];
	if (place->owner == NULL)  //�������û�����ˣ������ж� 
	{
		switch (place->type)
		{
		case LAND:
			buy_land(game);   //����ͨ�յأ����й��� 
			break;
		case HOSPITAL:
			printf("��������ҽԺ��\n");
			break;
		case PRISON:
			printf("�������˼�������Ϣ���غϣ�\n");
			current_player = &game->players[game->current_player_index];	// �ҵ���ǰ���
			current_player->status = PRISON;
			current_player->days = 2;
			break;
		case MAGIC_HOUSE:
			printf("��������ħ���ݣ�\n");
			break;
		case TOOLS_HOUSE:
			buy_bomb(game);
			break;
		case GIFT_HOUSE:
			gift(game);
			break;
		case MINE:
			game->players[game->current_player_index].point += place->price;
			printf("�������ڿ���ϣ���õ���%d\n",place->price);
			break;
		}
		system("pause");
	}

	else if (place->owner == &game->players[game->current_player_index])  //�����ǵ�ǰ��ҵģ��������� 
		update_land(game);
	else   
		pay_others_land(game);	   //�����Ǳ��˵ģ�֧����·�� 

}
