#include "command.h"
#include "helper.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ���巿������ */
char *g_house_type[4] = { "�յ�", "é��", "��", "Ħ��¥" };

/*
* ���� char *get_command(char *buffer, int length);
* ������buffer �����洢���������Ļ�����
* ������length �������ĳ���
* ���ã���ȡ��ǰ�������Ĳ�������
* ����ֵ��ָ��洢���������Ļ�������ָ��
* ���ߣ���̩Ȼ
*/
char *get_command(char *buffer, int length)
{
	char *temp;	// ����ָ�򻺳�����ָ��

	do
	{
		temp = buffer;
		fflush(stdin);	// ������뻺����
		fgets(buffer, length, stdin);
		while (*temp != '\0')
		{
			if (*temp == '\n')
			{
				*temp = '\0';	// �����з�����Ϊ'\0'
			}
			temp++;	// ָ����һ���ַ�
		}
	} while (buffer[0] == '\0');

	return buffer;
}

/*
* ���� void parse_command(char *command);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ������command ��ǰ�������Ĳ��������ַ���
* ���ã�������ǰ�������Ĳ������ִ����Ӧ������
* ���ߣ���̩Ȼ
*/
void parse_command(Game *game, char *command)
{
	char *pchar;	// ���ڴ洢�ַ�����ĳ�����ַ����״γ��ֵĵ�ַ
	int number;	// ���ڴ洢��������Ĳ���

	if (strstr(command, "query") != NULL)	// ��������Ϊquery
	{
		query(game, &game->players[game->current_player_index]);
	}
	else if (strstr(command, "help") != NULL)	// ��������Ϊhelp
	{
		help();
	}
	else if (strstr(command, "sell") != NULL)	// ��������Ϊsell n
	{
		pchar = strstr(command, "sell");
		pchar += 4;
		while (isspace(*pchar))
		{
			pchar++;	// �����հ��ַ�
		}
		if (*pchar != '\0')
		{
			number = atoi(pchar);
			sell(game, number);
		}
	}
	else if (strstr(command, "bomb") != NULL)  //��������Ϊbomb n
	{
		pchar = strstr(command, "bomb");
		pchar += 4;
		while (isspace(*pchar))
		{
			pchar++;	// �����հ��ַ�
		}
		if (*pchar != '\0')
		{
			number = atoi(pchar);
			place_bomb(game, number);
		}
	}
	else if (strstr(command, "quit") != NULL)	// ��������Ϊquit
	{
		quit();
	}
	else	// ����Ĳ��ǺϷ�����
	{
		printf("������Ĳ��ǺϷ����������help����鿴�������\n");
	}
	system("pause");	// ��ͣ�Ա�����˸
}

/*
* ���� void roll(Game *game);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ���ã���ǰ�������������
* ���ߣ���̩Ȼ
*/
void roll(Game *game)
{
	int roll_number;	// �������������õĵ���
	Player *current_player;	// ָ��ǰ���

	roll_number = get_roll_number();	// ��ȡ����������õĵ���
	current_player = &game->players[game->current_player_index];	// �ҵ���ǰ���
	if(game->map[(current_player->pos + roll_number) % game->place_num].tools_type != '@')
	{
		current_player->pos = (current_player->pos + roll_number) % game->place_num;	// �ı���ҵ�λ��
		printf("��ǰ����%d��\n", roll_number);
	}else if(game->map[(current_player->pos + roll_number) % game->place_num].tools_type == '@')
	{
		current_player->days = 3;
		current_player->pos = 14;	// ǰ��ҽԺ
		current_player->status = HOSPITAL;
		game->map[(current_player->pos + roll_number) % game->place_num].tools_type = NORMAL;
		printf("�ȵ�ը����ǰ��ҽԺ��Ϣ3�غ�\n");
	}
	system("pause");
}

/*
* ���� void buy_land(Game *game);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ���ã���ǰ��ҹ���һ��δ�����������
* ���ߣ���̩Ȼ
*/
void buy_land(Game *game)		
{
	Player *current_player;	// ָ��ǰ���
	Place *place;	// ָ���������֮��ͣ���ĵؿ飬��Ҫ����ĵؿ�
	char input[10];

	current_player = &game->players[game->current_player_index];	// �ҵ���ǰ���
	place = &game->map[current_player->pos];	// �ҵ�Ҫ����ĵؿ�

	printf("�ÿյ�δ���������Ƿ񻨷�%dԪ����������������Y��y������������ʾ������", place->price);
	fflush(stdin);	// ������뻺����
	fgets(input, 10, stdin);
	if (input[0] == 'Y' || input[0] == 'y')	// ��ҹ���յ�
	{
		if (place->type != LAND)	// Ҫ����ĵؿ鲻�ǿյأ����Ϸ��Ĳ���
		{
			printf("�õؿ鲻�ǿյأ�\n");
			return;
		}

		if (current_player->money >= place->price)	// ����ܹ������ؿ�
		{
			current_player->money -= place->price;	// �����ӵ�е��ʽ��м�ȥ�ؿ�ļ۸�
			place->owner = current_player;	// ���ؿ����˱��Ϊ��ǰ���
			current_player->place_amount++;	// ���������������
			printf("���ع���ɹ���\n");
			printf("������ÿ����ػ�����%dԪ��ʣ��%dԪ���ʽ�\n", place->price, current_player->money);
		}
		else	// ����ʽ���
		{
			printf("�����ʽ��㣬�޷��������أ�\n");
		}
	}
	else	// ��Ҳ�����յ�
	{
		printf("��ѡ���˲���������\n");
	}
}

/*
* ���� void update_land(Game *game);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ���ã���ǰ�������һ���Ѿ����������
* ���ߣ���̩Ȼ
*/
void update_land(Game *game)
{
	Player *current_player;	// ָ��ǰ���
	Place *place;	// ָ���������֮��ͣ���ĵؿ飬��Ҫ�����ĵؿ�
	char input[10];

	current_player = &game->players[game->current_player_index];	// �ҵ���ǰ���
	place = &game->map[current_player->pos];	// �ҵ�Ҫ�����ĵؿ�

	if (place->type != '3')	// �õؿ������
	{
		printf("�õؿ�Ϊ%s���������������Ƿ񻨷�%dԪ������������������Y��y������������ʾ��������", g_house_type[place->type - '0'], place->price);
		fflush(stdin);	// ������뻺����
		fgets(input, 10, stdin);
		if (input[0] == 'Y' || input[0] == 'y')	// ��������ؿ�
		{
			if (current_player->money >= place->price)	// ����ܹ���������ؿ�
			{
				current_player->money -= place->price;	// �����ӵ�е��ʽ��м�ȥ�ؿ�ļ۸�
				place->type++;	// ��������
				if (place->type == '1')	// ����ǰ��������֮��ĵȼ�Ϊ'1'��é�ݣ���ʾ�������˷���
				{
					current_player->house_amount++;	// ��ҷ�����������
				}
				printf("���������ɹ������ڸõؿ�Ϊ%s\n", g_house_type[place->type - '0']);
			}
			else	// ����ʽ���
			{
				printf("�����ʽ��㣬�޷��������أ�\n");
			}
		}
		else	// ��Ҳ������ؿ�
		{
			printf("��ѡ���˲������ؿ�\n");
		}
		system("pause");	// ��ͣ�Ա�����˸
	}
}

/*
* ���� void pay_others_land(Game *game);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ���ã����������֧����·��
* ���ߣ���̩Ȼ
*/
void pay_others_land(Game *game)
{
	// Ŀǰ��ʱ�����ǲ������Լ��ز�������ҽԺ�����

	Player *current_player;	// ָ��ǰ���
	Player *place_owner;	// ָ����ͣ���ؿ������
	Place *place;	// ָ���������֮��ͣ���ĵؿ飬��Ҫ֧����·�ѵĵؿ�
	int outcome;	// ��Ҫ֧���Ĺ�·�ѣ�����ǰ��ҵ�֧��

	current_player = &game->players[game->current_player_index];	// �ҵ���ǰ���
	place = &game->map[current_player->pos];	// �ҵ�Ҫ֧����·�ѵĵؿ�
	place_owner = place->owner;		// �ҵ�Ҫ֧����·�ѵĵؿ������

	outcome = get_place_worth(place) / 2;	 // ����Ҫ֧���Ĺ�·�ѣ�����Ϊ�ô�������ֵ��1/2
	printf("�������ߵ���%s�������ϣ�", place_owner->name);
	switch (place->type)
	{
	case '0':
		printf("�õؿ�Ϊ�յأ�������֧����·�ѣ�\n");
		system("pause");	// ��ͣ�Ա�����˸
		return;
	case '1':
	case '2':
	case '3':
		// ���������ִ�еĴ�����ͬ
		printf("�ô�����Ϊ%s������Ҫ֧����·��%dԪ\n", g_house_type[place->type - '0'], outcome);
		break;
	}
	if (current_player->money >= outcome)	// ����ܹ��������·��
	{
		current_player->money -= outcome;
		place_owner->money += outcome;	// �ز�������ȡ��·��
		printf("��֧����%dԪ��·�ѣ�ʣ��%dԪ���ʽ�\n", outcome, current_player->money);
	}
	else	// ��Ҹ������·��
	{
		// ����Ҹ������·��ʱ�����ȳ��۵�ǰ��ҵ����з������ٳ���֧����·��
		sell_all_houses(game, current_player);
		printf("���޷�֧����·�ѣ�����ϵͳ���Զ������������з���\n");
		if (current_player->money >= outcome)	// ����ܹ��������·��
		{
			current_player->money -= outcome;
			place_owner->money += outcome;	// �ز�������ȡ��·��
			printf("ϵͳ�������������з�������֧����%dԪ��·�ѣ�ʣ��%dԪ���ʽ�\n", outcome, current_player->money);
		}
		else	// �����Ȼ�������·�ѣ���ʱ����������Ʋ�
		{
			printf("�Բ���������������Ȼ�޷�֧����·�ѣ����Ʋ��ˣ�\n");
			eliminate_player(game, current_player);
		}
	}
	system("pause");	// ��ͣ�Ա�����˸
}

/*
* ���� void sell_all_houses(Game *game, Player *player);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ������player ָ��������ݽṹ���ָ�룬��ʾ��ǰ���
* ���ã����۵�ǰ��ҵ����з���
* ���ߣ���̩Ȼ
*/
void sell_all_houses(Game *game, Player *player)
{
	Place *place;	// ָ��ĳ�ؿ��ָ��
	int i;	// ѭ�����Ʊ���

	for (i = 1; i < game->place_num; i++)
	{
		place = &game->map[i];
		if (place->owner == player && place->type != '0')	// ��ĳ��ص������Ǹ�����Ҳ�Ϊ�յ�ʱ��Ҫ���۵��Ƿ���
		{
			sell_one_house(player, place);
		}
	}
}

/*
* ���� void sell_one_house(Player *player, Place *place);
* ������player ָ��������ݽṹ���ָ�룬��ʾ��ǰ���
* ������place ָ��ؿ����ݽṹ���ָ�룬��ʾĳһ�ؿ�
* ���ã�ִ�г��۸����ָ��λ�õķ����Ķ���
* ��ע���ú�����������֤���ɵ�����ȷ��������ȷ
* ���ߣ���̩Ȼ
*/
void sell_one_house(Player *player, Place *place)
{
	int income;		// ���۷�������õ�����

	income = get_place_worth(place) * 2;	// ���ۼ۸�ΪͶ���ܳɱ���2��
	player->money += income;	// ��һ������
	player->house_amount--;	// ��ҷ�����������
	place->type = LAND;	// ���۷�����õؿ��Ϊ�յ�
}

/*
* ���� void eliminate_player(Game *game, Player *player);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ������player ָ��������ݽṹ���ָ�룬��ʾ��ǰ���
* ���ã��Ը����ִ���Ʋ�����
* ���ߣ���̩Ȼ
*/
void eliminate_player(Game *game, Player *player)
{
	Place *place;	// ָ��ĳ�ؿ��ָ��
	int i;	// ѭ�����Ʊ���

	for (i = 1; i < game->place_num; i++)
	{
		place = &game->map[i];
		if (place->owner == player)	// ��ĳ��ص������Ǹ����ʱ
		{
			player->place_amount--;	// �������������i��
			place->type = LAND;	// ���۷�����õؿ��Ϊ�յ�
			place->owner = NULL;	// �������ع黹ϵͳ
		}
	}
	player->money = 0;
	player->point = 0;
	player->pos = 0;
	player->status = OUT;
	player->block_amount = 0;
	player->bomb_amount = 0;
	player->robot_amount = 0;

	game->player_num--;	// ������Ҹ���
}

/*
* ���� void sell(Game *game, int pos);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ������pos �����ڵ�ͼ�ϵľ���λ��
* ���ã���ǰ��ҳ���ָ��λ�õķ���
* ���ߣ���̩Ȼ
*/
void sell(Game *game, int pos)
{
	char input[10];
	Player *current_player;	// ָ��ǰ���
	Place *place;	// ָ�����Ҫ���۷����ĵؿ�

	if (pos < 1 || pos > game->place_num - 1)
	{
		printf("������ľ���λ������\n");
		return;
	}

	current_player = &game->players[game->current_player_index];	// �ҵ���ǰ���
	place = &game->map[pos];	// �ҵ�Ҫ���۵ĵؿ�

	if (place->owner == current_player)	// Ҫ���۷����������ǵ�ǰ��ҵ�
	{
		if (place->type != LAND)	// �ڲ��ǿյص�����²��ܳ��۷���
		{
			printf("��ȷ��Ҫ����λ��%d�ķ�����������������Y��y������������ʾ�����ۣ�", pos);
			fflush(stdin);	// ������뻺����
			fgets(input, 10, stdin);
			if (input[0] == 'Y' || input[0] == 'y')	// ��ҳ��۷���
			{
				sell_one_house(current_player, place);
				printf("��������λ��%d�ķ���\n", pos);
			}
			else	// ��Ҳ����۷���
			{
				printf("��ѡ���˲����۷���\n");
			}
		}
		else	// �յ�û�з������Գ���
		{
			printf("������ĸ�λ�ô�������û�з������Գ��ۣ�\n");
		}
	}
	else	// Ҫ���۵ķ������ǵ�ǰ��ҵ�
	{
		printf("�Բ���������ĸ�λ�ô������ز������ģ�\n");
	}
}

/*
* ���� void query(Game *game, Player *player);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ������player ָ��������ݽṹ���ָ�룬��ʾĳһ���
* ���ã���ʾ����ʲ���Ϣ
* ���ߣ���̩Ȼ
*/
void query(Game *game, Player *player)
{
	int i;	// ѭ�����Ʊ���
	Place *place; // ָ��ĳ�ؿ��ָ��

	printf("%s���ʲ�������ʾ��\n�ʽ�%dԪ\n������%d��\n", player->name, player->money, player->point);
	printf("���ߣ�·��%d������������%d����ը��%d��\n", player->block_amount, player->robot_amount, player->bomb_amount);
	if (player->place_amount != 0)	// ���������
	{
		printf("�̶��ʲ����£�\n����%d�飬����%d�����������£�\n", player->place_amount, player->house_amount);
		printf("\t����\t����λ��\n");
		for (i = 1; i < game->place_num; i++)
		{
			place = &game->map[i];
			if (place->owner == player)	// ��ĳ��ص������Ǹ����ʱ
			{
				printf("\t%s\t%d\n", g_house_type[place->type - '0'], i);
			}
		}
	}
	else	// ���û������
	{
		printf("�̶��ʲ��������غͷ���\n");
	}
}

/*
* ���� void step(Game *game, int number);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ������number ָ�������߲���
* ���ã�ʵ��ң�����ӹ��ܣ�����ָ��������Ĳ���
* ���ߣ���̩Ȼ
*/
void step(Game *game, int number)
{
	Player *current_player;	// ָ��ǰ���

	current_player = &game->players[game->current_player_index];	// �ҵ���ǰ���
	if(game->map[(current_player->pos + number) % game->place_num].tools_type != BOMB)
	{
		current_player->pos = (current_player->pos + number) % game->place_num;	// �ı���ҵ�λ��
		printf("��ǰ����%d��\n", number);
	}else if(game->map[(current_player->pos + number) % game->place_num].tools_type == BOMB)
	{
		game->map[(current_player->pos + number) % game->place_num].tools_type = NORMAL;
		current_player->days = 3;
		current_player->pos = 14;	// ǰ��ҽԺ
		current_player->status = HOSPITAL;
		printf("�ȵ�ը����ǰ��ҽԺ��Ϣ3�غ�\n");
	}
	system("pause");
}

/*
* ���� void help();
* ���ã���ʾ���������ʹ��˵��
* ���ߣ���̩Ȼ
*/
void help()
{
	printf("����\t����˵��\n");
	printf("roll\t����������\n");
	printf("sell n\t�����Լ������ⷿ�������ۼ۸�ΪͶ���ܳɱ���2����nΪ�����ڵ�ͼ�ϵľ���λ��\n");
	printf("query\t��ʾ�Լ��ʲ���Ϣ\n");
	printf("bomb n\t��ҷ���ը�����뵱ǰλ��ǰ��10�����κ�λ��\n");
	printf("help\t�鿴�������\n");
	printf("quit\tǿ���˳�\n");
	printf("step n\tң�����ӣ�nΪָ���Ĳ���\n");
}

/*
* ���� void quit();
* ���ã�ǿ�ƽ�����Ϸ
* ���ߣ���̩Ȼ
*/
void quit()
{
	printf("����������Ϸ��\n");
	exit(0);
}

/*
* ���� void next_player(Game *game);
* ������game ָ����Ϸ���ݽṹ���ָ��
* ���ã���Ȩ����һ�����
* ���ߣ���̩Ȼ
*/
void next_player(Game *game)
{
	Player *player;	// �����洢ĳһ��ҵ�ָ��

	// ������һ����ң��ȼ�����ҵ�״̬������������״̬�����ټ����һ����ң�ֱ��ĳ��ҵ�״̬Ϊ����Ϊֹ
	do
	{
		game->current_player_index = (game->current_player_index + 1) % game->player_num;
		player = &game->players[game->current_player_index];	// �ҵ���һ�����
		if(player->status == HOSPITAL||player->status ==PRISON)
		{
			switch(player->days)
			{
			case 0:
				player->status = NORMAL;
				break;
			case 1:
				system("cls");
				output_map(game);
				printf("%s�»غϿ�ʼ�ж���\n",player->name);
				system("pause");
				break;
			case 2:
			case 3:
				system("cls");
				output_map(game);
				printf("%s����Ҫ��Ϣ%d�غ�......\n",player->name,player->days-1);
				system("pause");
				break;
			default:
				break;
			}
			player->days--;
		}
	} while (player->status != NORMAL);
}

/*
* ���� void place_bomb(Game *game,int number);
* ���� game ָ����Ϸ���ݽṹ���ָ��
* ���� number ���õ�ը�����뵱ǰλ�õ�������
* ���� ����ը��
* ���� �Ƽ���
*/
void place_bomb(Game *game,int number)
{
	Player *current_player;	// ָ��ǰ���
	current_player = &game->players[game->current_player_index];	// �ҵ���ǰ���
	if(current_player->bomb_amount>0)
	{
		if(number>=-10&&number<=10)
		{
			game->map[(current_player->pos + number + game->place_num) % game->place_num].tools_type = BOMB;
			current_player->bomb_amount -= 1;
			printf("�ɹ�����ը��!\n");
		}else{
			printf("��������ը��!\n");
		}
	}
	else{
		printf("û��ը�����޷����ã�\n");
	}
}

/*
* ���� void buy_bomb(Game *game);
* ���� game ָ����Ϸ���ݽṹ���ָ��
* ���� ����ը��
* ���� �Ƽ���
*/
void buy_bomb(Game *game)
{
	char flag;
	printf("�������˵����ݣ��Ƿ���ը����Y or N):");
	scanf("%c",&flag);
	if(flag == 'Y'||flag == 'y')
	{
		if(game->players[game->current_player_index].point>=50)
		{
			game->players[game->current_player_index].bomb_amount += 1;
			game->players[game->current_player_index].point -= 50;
			printf("�ɹ�����\n");
		}else{
			printf("�������㣬�޷�����\n");
		}
	}
}

/*
* ���� void gift(Game *game);
* ���� game ָ����Ϸ���ݽṹ���ָ��
* ���� ��ȡ��Ʒ
* ���� �Ƽ���
*/
void gift(Game *game)
{
	int flag;
	printf("��ӭ������Ʒ�ݣ�\n");
	printf("��ѡ��һ����ϲ������Ʒ��1������2000��2��������200\n");
	scanf("%d",&flag);
	switch(flag)
	{
	case 1:
		game->players[game->current_player_index].money +=2000;
		printf("��ý���2000\n");
		break;
	case 2:
		game->players[game->current_player_index].point +=200;
		printf("��õ�����200\n");
		break;
	default:
		break;
	}
}
