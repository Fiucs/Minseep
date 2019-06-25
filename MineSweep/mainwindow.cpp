#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPainter>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("骚雷");

    create.initmap(10,10,15);
    setFixedSize(create.mwidth,create.mheight);
    connect(this,SIGNAL(clicpos()),this,SLOT(shows()));//触发计算
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *event)//绘制地图
{
    QPainter painter(this);
    QPixmap image1(":/res/flag.png");//加载雷 数字之类的贴图
    int i=0;
    switch (create.wstate) {
    case START:

        for(i=0;i<create.row;i++)//
        {
            for(int j=0;j<create.cow;j++)//
            {
                painter.drawPixmap((create.mwidth-24*10)/2+24*j,100+24*i,image1,10*24,0,24,24);//生成初始化的地图
            }


        }
        break;
     case NORMAL:
        for(i=0;i<create.row;i++)//
        {
            for(int j=0;j<create.cow;j++)//
            {
                if(create.gamemap[i][j].mclick   )// //绘制未翻开的板
                {
                    painter.drawPixmap((create.mwidth-24*10)/2+24*j,100+24*i,image1,10*24,0,24,24);

                }


                 if(create.gamemap[i][j].state==FLAGON)//绘制旗帜
                 {
                     //qDebug()<<"在绘制旗帜";
                     painter.drawPixmap((create.mwidth-24*10)/2+24*j,100+24*i,image1,11*24,0,24,24);
                 }
                if(create.gamemap[i][j].state==FLAGOFF  )// //绘制未翻开的板
                {
                    painter.drawPixmap((create.mwidth-24*10)/2+24*j,100+24*i,image1,10*24,0,24,24);

                }
                if(!create.gamemap[i][j].mclick && create.gamemap[i][j].state==FLAGOFF && !create.gamemap[i][j].mine)//绘制数字标
               {
                    //qDebug()<<"在绘制shuzi1"<<create.gamemap[i][j].minenuber<<" "<<i<<","<<j;
                   painter.drawPixmap((create.mwidth-24*10)/2+24*j,100+24*i,image1,create.gamemap[i][j].minenuber*24,0,24,24);
               }

            }


        }

        //绘制空白版 此处特殊情况 要爆开



        //绘制雷区
        if(create.upstate==GAMEOVER)
        {
            for(int i=0;i<create.minenumber;i++)
            {
                int y=create.list[i]/create.cow;//雷y下标
                int x=create.list[i]%create.cow;//雷x下标
                painter.drawPixmap((create.mwidth-24*10)/2+24*x,100+24*y,image1,9*24,0,24,24);

            }
        }
        break;



    default:
        break;
    }


}
void MainWindow::searchall0(int x,int y,int row,int cow)//空块为0时爆开
{

    std::vector<int> posx;//记录雷的x坐标
    std::vector<int> posy;//记录雷的y坐标

    posx.push_back(x-1);//计算点击位置周围8个坐标 记录到 posx,poxy
    posy.push_back(y);

    posx.push_back(x-1);
    posy.push_back(y-1);

    posx.push_back(x-1);
    posy.push_back(y+1);

    posx.push_back(x+1);
    posy.push_back(y);

    posx.push_back(x+1);
    posy.push_back(y-1);

    posx.push_back(x+1);
    posy.push_back(y+1);


    posx.push_back(x);
    posy.push_back(y-1);


    posx.push_back(x);
    posy.push_back(y+1);

    create.gamemap[x][y].minenuber=0;//雷的初始值为0
    qDebug()<<"遍历的坐标"<<x<<","<<y;
for(int i=0;i<8;i++)//计算雷的位置
{
   if(posx[i]>=0 && posx[i]<row&&  posy[i]>=0 &&posy[i]<cow)//判断8个位置处是否在 地图之中
   {
       if(create.gamemap[posx[i]][posy[i]].mine)
       {
      create.gamemap[x][y].minenuber++;//该位置处得到 雷数量计数器+1
      create.gamemap[x][y].mclick=false;

       qDebug()<<"雷的位置"<<"["<<posx[i]<<","<<posy[i]<<"]";
       }
   }

}


if(create.gamemap[x][y].minenuber<=0 &&create.gamemap[x][y].mine==false)
{
   //create.gamemap[x][y].mclick=false;
    create.gamemap[x][y].mclick=false;

    for(int i=0;i<8;i++)//计算雷的位置
    {
       if(posx[i]>=0 && posx[i]<row&&  posy[i]>=0 &&posy[i]<cow)//判断8个位置处是否在 地图之中
       {
            if(create.gamemap[posx[i]][posy[i]].mclick)//递归cha查找空空位置
           searchall0(posx[i],posy[i],row,cow);
       }

    }



}

}


void MainWindow::analysis(int x,int y,std::vector<std::vector<Mineinfo>> gameinfo,int row,int cow)//计算雷数量的函数
{
   // int count=0;//用来临时记录雷的数量
create.wstate=NORMAL;
//    gameinfo[x][y]//点击位置
//    gameinfo[x+1][y]//点击位置的上一层
//    gameinfo[x-1][y]//点击位置的下一层
    //判断 x-1与0的大小 x+1与row的大小 如果x-1<0则在第0层   如果x+1=row 则在最底层
    number=1;

        searchall0(x,y,row,cow);





qDebug()<<"雷数："<<create.gamemap[x][y].minenuber;
    if(gameinfo[x][y].mine==true && false==gameinfo[x][y].mclick)//为真代表有雷游戏结束
        {
        create.gamemap[x][y].mclick=true;
        qDebug()<<"有雷"<<x<<","<<y;
        //游戏结束
        create.upstate=GAMEOVER;
        update();


    }
    else if(create.gamemap[x][y].minenuber!=0)
    {


    update();
    }
    else
        update();


}

void MainWindow::mousePressEvent(QMouseEvent *e)//鼠标左键 点开 爆雷游戏结束 雷数为0爆开一片，不为0显示数字图标 右键插旗
{
    int x,y;
    int startx,starty,stopx,stopy;
    flag=0;
    if(create.minenumber==create.mode)
    {
        startx=30;
        starty=100;
        stopx=270;
        stopy=340;
    }

    if(e->button() ==Qt::LeftButton)
    {
      qDebug()<<"左键："<<"["<<e->x()<<","<<e->y()<<"]";
      x=e->x();
     y=e->y();
     if(x>startx && x<stopx && y>starty && y<stopy)
        {
         //qDebug()<<"格子坐标"<<"["<<(e->y()-100)/24<<","<<(e->x()-30)/24<<"]";
         arryx=(e->y()-100)/24;
         arryy=(e->x()-30)/24;
         create.gamemap[arryx][arryy].mclick=false;//设置该位置为左键不可点击

        }
    }
    else if(e->button() ==Qt::RightButton)
    {

        x=e->x();
       y=e->y();
        if(x>startx && x<stopx && y>starty && y<stopy)
            {
            arryx=(e->y()-100)/24;
            arryy=(e->x()-30)/24;
           // create.gamemap[arryx][arryy].mclick=false;

            if(create.gamemap[arryx][arryy].state==FLAGOFF)
            {
                create.gamemap[arryx][arryy].state=FLAGON;//设置为有旗帜
            }
            else if(create.gamemap[arryx][arryy].state==FLAGON)
            {
                create.gamemap[arryx][arryy].state=FLAGOFF;//设置为有旗帜
            }
            else{

            }

            qDebug()<<"右键："<<"["<<arryx<<","<<arryy<<"]";
            }
        flag=1;
    }
    else
    {}

emit clicpos();



}
void MainWindow::succes()
{
create.sucessnumber=0;
    for(int i=0;i<create.row;i++)
    {
        for(int j=0;j<create.cow;j++)
        {
            if(!create.gamemap[i][j].mclick)
            {
                create.sucessnumber++;
            }
        }

    }
    if(create.row*create.cow-create.sucessnumber==create.minenumber)
        {
       // create.wstate=SUCESS;//成功
        win->setGeometry(create.mwidth/2,create.mheight/4,50,20);
        win->setParent(this);//显示扫雷成功
    }




}
void MainWindow::shows()
{

    if(flag==1 && create.upstate==GOON)
    {
        create.wstate=NORMAL;
        qDebug()<<arryx<<","<<arryy;
        update();
    }
    else{
        if(create.upstate==GOON)
            {
    analysis(arryx,arryy,create.gamemap,create.row,create.cow);
    qDebug()<<"格子坐标"<<"["<<arryx<<","<<arryy<<"]";
    qDebug()<<"右键："<<"["<<arryx<<","<<arryy<<"]";
    succes();//判断雷扫完了没
    qDebug()<<"成功排除的数量"<<create.sucessnumber;
    qDebug()<<"剩余的方块数量"<<create.cow*create.row-create.sucessnumber;
            }
        }

}



void MainWindow::on_actionstart_triggered()
{
    create.initmap(10,10,15);
    update();
}
