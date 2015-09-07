#Rich游戏测试报告  


##测试环境  
*操作系统：Microsoft Windows 7旗舰版  
*CPU：Core i5  
*内存：4.00GB  
*硬盘：240GB  
*Visual C++ 6.0  
##参考资料  
*《Rich游戏需求分析文档》  
*《软件测试技术概论》古乐 史九林遍著/清华大学出版社  
*《软件测试：第二版》Paul.C.Jorgensen 著/机械工业出版社  
##测试时间、人员  
测试时间：2015.9.6~2015.9.7  
人员：胡小意  

##测试覆盖设计  
测试用例覆盖矩阵  
|序号	|函数名称	|测试用例|
|01	|init_map	|TestCase-1|
|02	|output_map	|TestCase-2|

##测试内容  
**函数 void init_map(Game *game) 
**说明：初始化地图

###TestCase-1测试用例
###测试项目名称：init_map
|测试用例编号：TestCase-1	|测试人员：胡小意  测试时间：2015.9.6|
|测试内容：进入visual studio,输入测试用例，看是否出现与预期相同的结果|
|测试环境与系统配置：详见2.4环境描述|
|测试过程	|直接在vc中运行项目，初始化地图然后输出，看是否与预期结果一样|
|测试次数	|1次|
|测试结论	|游戏此功能已经实现|
|备注：	|无|

![图1](http://github.com/xiaoyi27/Rich_06/raw/master/doc/img/huxiaoyi1.png)
预期结果：输出地图上每个坐标的属性
实际结果：正确输出地图上每个坐标的属性

###TestCase-2测试用例
###测试项目名称：
|测试用例编号：TestCase-2	|测试人员：胡小意  测试时间：2015.9.6|
|测试内容：进入vc,输入测试用例，看是否出现与预期相同的结果|
|测试环境与系统配置：详见测试环境|
|测试过程	|直接在vc中运行项目，输出地图|
|测试次数	|3次|
|测试结论	|游戏此功能已经实现|
|备注：	|无|
预期结果：正确输出地图
实际结果：正确输出地图


![图2](http://github.com/xiaoyi27/Rich_06/raw/master/doc/img/huxiaoyi2.png)

##测试任务评估
这次测试主要是进行两个单元测试，第一个单元测试输出数据量较大，只完成了部分数据的测试，基本完成测试任务。
##心得体会
 这次测试我主要完成单元测试的任务，单元测试，是在计算机编程中，针对程序模块（软件设计的最小单位）来进行正确性检验的测试工作。程序单元是应用的最小可测试部件。对于单元测试中单元的含义，一般来说，要根据实际情况去判定其具体含义，如C语言中单元指一个函数，Java里单元指一个类，图形化的软件中可以指一个窗口或一个菜单等。总的来说，单元就是人为规定的最小的被测功能模块。单元测试是在软件开发过程中要进行的最低级别的测试活动，软件的独立单元将在与程序的其他部分相隔离的情况下进行测试。通常来说，程序员每修改一次程序就会进行最少一次单元测试，在编写程序的过程中前后很可能要进行多次单元测试，以证实程序达到软件规格书要求的工作目标，没有程序错误。通过这次测试，我感觉到了单元测试首先要了解程序员的编程思想，这样才能熟练的进行测试。








#测试代码
<pre>
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
        int i;
	i=0;
	init_map(&game);

	// 输出地图
    printf("game.map[%d].owner = %s\n", i, game.map[i].owner);
	printf("game.map[%d].price = %d\n", i, game.map[i].price);
	printf("game.map[%d].tools_type = %s\n", i, game.map[i].tools_type);
	printf("game.map[%d].x = %d\n", i, game.map[i].x);
	printf("game.map[%d].y = %d\n\n", i, game.map[i].y);
	
	for(i=1;i<28;i++)
	{ 
	printf("game.map[%d].owner = %s\n", i, game.map[i].owner);
	printf("game.map[%d].price = %d\n", i, game.map[i].price);
	printf("game.map[%d].tools_type = %s\n", i, game.map[i].tools_type);
	printf("game.map[%d].x = %d\n", i, game.map[i].x);
	printf("game.map[%d].y = %d\n\n", i, game.map[i].y);
	}
	for(i=1;i<7;i++)
	{
	printf("game.map[%d].owner = %s\n", i+28, game.map[i].owner);
	printf("game.map[%d].price = %d\n", i+28, game.map[i].price);
	printf("game.map[%d].tools_type = %s\n", i+28, game.map[i].tools_type);
	printf("game.map[%d].x = %d\n", i+28, game.map[i].x);
	printf("game.map[%d].y = %d\n\n", i+28, game.map[i].y);
    }
	for(i=1;i<28;i++)
	{
	printf("game.map[%d].owner = %s\n", i+35, game.map[i].owner);
	printf("game.map[%d].price = %d\n", i+35, game.map[i].price);
	printf("game.map[%d].tools_type = %s\n", i+35, game.map[i].tools_type);
	printf("game.map[%d].x = %d\n", i+35, game.map[i].x);
	printf("game.map[%d].y = %d\n\n", i+35, game.map[i].y);
    }
	
	return 0;
}

</pre>
<pre>
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
    int i;
	i=0;
	init_map(&game);

	output_map(&game);
	
	return 0;
}
</pre>