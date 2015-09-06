#Rich游戏测试报告  


##测试环境  
*操作系统：Microsoft Windows 10专业版  
*CPU：Core i5  
*内存：4.00GB  
*硬盘：240GB  
*Visual studio 2013  
##参考资料  
*《Rich游戏需求分析文档》  
*《软件测试技术概论》古乐 史九林遍著/清华大学出版社  
*《软件测试：第二版》Paul.C.Jorgensen 著/机械工业出版社  
##测试时间、人员  
测试时间：2015.9.6~2015.9.7  
人员：陈捷  

##测试覆盖设计  
测试用例覆盖矩阵  
|序号	|函数名称	|测试用例|
|01	|init_money	|TestCase-1|
|02	|init_players	|TestCase-2|
|03	|init_player	|TestCase-3|

##测试内容  
**函数 void init_money(Game *game)**  
**说明：初始化每位玩家的资金，玩家可以自主选择初始资金范围1000 - 50000，若不在这个范围之内，则资金默认为10000。**  

###TestCase-1测试用例
###测试项目名称：init_money
|测试用例编号：TestCase-1	|测试人员：陈捷	测试时间：2015.9.6|
|测试内容：进入visual studio,输入测试用例，看是否出现与预期相同的结果|
|测试环境与系统配置：详见2.4环境描述|
|测试过程	|直接在visual studio中运行项目，输入各种玩家可能输入的金币初始值，查看测试结果是否与规则一致，正常范围为1000-50000，多于或少于这个值都会默认玩家选择的金币数为10000。|
|测试次数	|3次|
|测试结论	|游戏此功能已经实现|
|实现限制：	|在Visual studio环境中|
|备注：	|无|


1.输入金额：999  
预期输出：10000  
输出金额：10000  
![图1](https://github.com/cj3532/Rich_06/raw/master/doc/img/cj-1.png)
2.输入金额：20000   
预期输出：20000  
输出金额：20000  
![图2](https://github.com/cj3532/Rich_06/raw/master/doc/img/cj-2.png)
3.输入金额：60000  
预期输出：50000  
输出金额：50000  
![图3](https://github.com/cj3532/Rich_06/raw/master/doc/img/cj-3.png)
**函数 void init_players(Game *game)**
**说明：初始化游戏中的玩家数据，用户根据提示选择游戏人物，可以选择2-4名人物，若不在此范围内游戏出错。**

###TestCase-2测试用例
###测试项目名称：
|测试用例编号：TestCase-2	|测试人员：陈捷	测试时间：2015.9.6|
|测试内容：进入visual studio,输入测试用例，看是否出现与预期相同的结果|
|测试环境与系统配置：详见测试环境|
|测试过程	|直接在visual studio中运行项目，输入各种玩家可能输入的玩家人数，规定玩家人数为2-4人，如果少于2人和多于4人，程序都不能正常运行。|
|测试次数	|3次|
|测试结论	|游戏此功能已经实现|
|实现限制：	|在Visual studio环境中|
|备注：	|无|


1.输入序号;1234  
预期输出：game.player_num=4  
输出结果：game.player_num=4  
![图4](https://github.com/cj3532/Rich_06/raw/master/doc/img/cj-4.png)

2.输入序号：12345  
预期输出：无  
输出结果：无  
![图5](https://github.com/cj3532/Rich_06/raw/master/doc/img/cj-5.png)
3.输入序号:1  
预期输出：无  
输出结果：无  
![图6](https://github.com/cj3532/Rich_06/raw/master/doc/img/cj-6.png)
4.输入序号：12  
预期输出：game.player_num=2  
输出结果：game.player_num=2  
![图7](https://github.com/cj3532/Rich_06/raw/master/doc/img/cj-7.png)
**函数 void init_player(Game *game,int index,char number);**
**作用：初始化游戏玩家的不重复数据**
###TestCase-3测试用例
###测试项目名称：
|测试用例编号：TestCase-3	|测试人员：陈捷	测试时间：2015.9.6|
|测试内容：进入visual studio,输入测试用例，看是否出现与预期相同的结果|
|测试环境与系统配置：详见测试环境|
|测试过程	|直接在visual studio中运行项目，查看在初始状态下，每块地皮的状态，包括所有者，位置，价格，用地类型，和道具类型等|
|测试次数	|1次|
|测试次数	|3次|
|测试结论	|游戏此功能已经实现|
|实现限制：	|在Visual studio环境中|
|备注：	|无|
![图8](https://github.com/cj3532/Rich_06/raw/master/doc/img/cj-8.png)

显示了地图中每一块地皮的类型，所有者，价格等基本信息。
##测试任务评估
本次测试执行准备充足，进行了一部分函数的单元测试，完成了既定的目标，但由于经验以及对工具使用不熟练，因此还有待提高和加强。
##心得体会
 我在这次软件实习中担任的是软件测试的工作，主要采用的是单元测试。单元测试，是指对软件中的最小可测试单元进行检查和验证。对于单元测试中单元的含义，一般来说，要根据实际情况去判定其具体含义，如C语言中单元指一个函数，Java里单元指一个类，图形化的软件中可以指一个窗口或一个菜单等。总的来说，单元就是人为规定的最小的被测功能模块。单元测试是在软件开发过程中要进行的最低级别的测试活动，软件的独立单元将在与程序的其他部分相隔离的情况下进行测试。在这次测试中，我明白了软件测试看起来简单，但也是需要在对程序有一定基础的了解上才能实施的。








#测试代码
<pre>
#include "command.h"
#include "helper.h"
#include "init.h"
#include "types.h"
#include "view.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
	Game game;	// 游戏数据的结构体变量
	int i;

	初始化每位玩家的资金
	init_money(&game);
	初始化玩家
	init_players(&game);
	初始化地图
	init_map(&game);
	初始化游戏中的其他数据
	init_others(&game);

	printf("game.initial_money = %d\n", game.initial_money);
	
	printf("game.player_num = %d\n", game.player_num);
	printf("game.place_num = %d\n", game.place_num);
	printf("game.current_player_index = %d\n", game.current_player_index);
	printf("\n");
	for (i = 0; i < game.place_num; i++)
	{
		printf("map[%d].type = %c\n", i, game.map[i].type);
		printf("map[%d].owner = %d\n", i, game.map[i].owner);
		printf("map[%d].price = %d\n", i, game.map[i].price);
		printf("map[%d].tools_type = %c\n", i, game.map[i].tools_type);
		printf("map[%d].x = %d\n", i, game.map[i].x);
		printf("map[%d].y = %d\n\n", i, game.map[i].y);
	}
}
</pre>