#ifndef GAME_MODULE_H
#define GAME_MODULE_H
#include <vector>
#include<QDebug>
enum posStae{
  FLAGON,
  FLAGOFF


};
struct Mineinfo
{
    bool mine;//true 雷 false 没雷
    int minenuber;//雷的个数0~8
    posStae state;//旗帜有无
    bool mclick;//能否点击 true 可以
};

enum Upstate{
  GAMEOVER,//游戏结束
  GOON//继续


};
enum WindowStae{
    START,//开始
    //RESTART,//重新开始
    ANALYSIS,//算雷数
    SUCESS,  //扫雷成功
    NORMAL //进入实时刷新
};

class game_module
{
public:
    game_module();
    int row;//行
    int cow;//列
    int minenumber;//雷的个数
    int mwidth;//地图宽
    int mheight;//地图高
    WindowStae wstate;//窗口状态
    int mode;//游戏难度
    int sucessnumber;
    Upstate upstate;
    std::vector<std::vector<Mineinfo>> gamemap;//当前鼠标位置处的情况 ，有无雷 ，雷的个数， 旗子状态
    std::vector<int> list;//记录随机生成雷得到容器
    void initmap(int mrow,int mcow,int mnber);


};

#endif // GAME_MODULE_H
