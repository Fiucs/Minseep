#include "game_module.h"
#include <time.h>
#include <QTime>

game_module::game_module()
{

}

void game_module::initmap(int mrow,int mcow,int mnber)
{


    gamemap.clear();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
   int i=0;
   int j;
   int flag=0;
    mode=15;
   if(mnber==15)
   {
   mwidth=300;
   mheight=360;
   minenumber=15;
   row=mrow;
   cow=mcow;
   sucessnumber=0;//最开始成功排除的数量
   }

    list.push_back(-1);//随机数产生雷
  for(i;i<mnber;)
  {

   int n=qrand()%100;
   if(list[0]==-1)
   {
       list[0]=n;
       i++;
       continue;
   }
   for(j=0;j<i;j++)
   {
  if(n==list[j])
     break;
   }
   if(j==i)
   {
       list.push_back(n);
       i++;
   }

  }


upstate=GOON;
wstate=START;//初始化绘制状态
struct Mineinfo initstate={


    .mine=false,//true 雷 false 没雷
    .minenuber=-1,//雷的个数0~8
    .state=FLAGOFF,
    .mclick=true

};

for(int j=0;j<mrow;j++)//初始化布局，SATRT 无雷false 雷区风险初始值值-1 旗帜FLAGOFF
{
     std::vector<Mineinfo> line;
    for(int k=0;k<mcow;k++)
    {
        line.push_back(initstate);
}
    gamemap.push_back(line);

}

for(int count=0;count<mnber;count++)
{

    qDebug()<<list[count];
    int x=list[count]/mcow;
    int y=list[count]%mcow;
    qDebug("雷坐标：[%d,%d]",x,y);//计算雷区坐标
    gamemap[x][y].mine=true;//有雷

}



   for(i=0;i<mrow;i++)
   {
      for(int j=0;j<mcow;j++)
      {
          qDebug("pos:[%d,%d],minnuber:%d",i,j,gamemap[i][j].minenuber);//测试
          qDebug()<<gamemap[i][j].mine<<gamemap[i][j].state<<gamemap[i][j].mclick;
      }
   }


}

