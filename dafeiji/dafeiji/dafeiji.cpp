#include <graphics.h>
#include <conio.h>
#include<vector>
#include<ctime>
#include <stdlib.h>
#include <stdio.h>
#pragma  comment(lib,"WinMM.Lib")
#include<windows.h>
#include <mmsystem.h>
using namespace std;

bool exitmain;
bool levelchosed=false;
bool click;
int mainwidth=50,mainlength=52;
int score;
int best=0;
int level;
wchar_t scoref[15]; 
wchar_t bestf[15];
wchar_t levelf[2];
int step=10;
int count,count1,count2;//count bulletappear;count1 enemyappear;count2 enenmy move;
int enemyspeed1;
int enemyspeed2;
int enemyspeed3;
int speedi;
int speed1;
int speed2;
int speed3;
int rate;
int beginlevel;
char keyboard;


#define MAXSTAR 200	
int countxingkong=9;
void setxingkong();
void setxingkong2();
struct STAR
{
	double	x;
	int		y;
	double	step;
	int		color;
};

STAR star[MAXSTAR];
void InitStar(int i)
{
	star[i].y = 0;
	star[i].x = rand() % 640;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}
void InitStar2(int i)
{
	star[i].y = 0;
	star[i].x = rand() % 800;
	star[i].step = (rand() % 5000) / 1000.0 + 1;
	star[i].color = (int)(star[i].step * 255 / 6.0 + 0.5);	
	star[i].color = RGB(star[i].color, star[i].color, star[i].color);
}
//星空

class Boat
{
public:
	Boat(int _x, int _y)
	{
		x=_x;
		y=_y;
        loadimage(&img,_T("E:\\picture\\main.jpg"));
        loadimage(&img2,_T("E:\\picture\\main2.jpg")); 
        loadimage(&img3,_T("E:\\picture\\mainexplode.jpg"));
		loadimage(&img4,_T("E:\\picture\\mainexplode2.jpg")); 
		judge=true;
	}
	void setx(int _x) 
	{
		x=_x;
	}
	void sety(int _y)
	{
		y=_y;
	}
	int getx()
	{
		return x;
	}
	int gety()
	{
		return y;
	}
	void setjudge(bool i)
	{
		judge=i;
	}
	bool getjudge()
	{
		return judge;
	}
	void putboat()
	{
        putimage(x-25,y-26,&img,SRCAND);
        putimage(x-25,y-26,&img2,SRCPAINT);
	}
    void explode()
	{
		putimage(x-25,y-26,&img4,SRCAND);
	    putimage(x-25,y-26,&img3,SRCPAINT);
	}
private:
	int x,y;
	IMAGE img,img2,img3,img4;
	bool judge;
};

class Bullet
{
public:
	Bullet(int _x,int _y)
	{
		judge=true;
		x=_x;
		y=_y;
	}
	void move()
	{
		setfillcolor(WHITE);
		setcolor(WHITE);
		fillcircle(x,y-=3,5);
	}
	int getx()
	{
		return x;
	}
	int gety()
	{
		return y;
	}
	void setjudge(bool i)
	{
		judge=i;
	}
	bool getjudge()
	{
		return judge;
	}
private:
	int x,y;
	bool judge;
};

class Enemy
{
public:
	Enemy()
	{
		y=0;
		x=rand()%600+10;
		judge=true;
		width=40;
		length=50;
		num=5;
		loadimage(&img,_T("E:\\picture\\enemy2.jpg"));
		loadimage(&img2,_T("E:\\picture\\enemy.jpg")); 
        loadimage(&img3,_T("E:\\picture\\explode.jpg"));
		loadimage(&img4,_T("E:\\picture\\explode2.jpg")); 
		speed=speedi;
	}
	void move()
	{
		putimage(x,y+=speed,&img,SRCAND);
		putimage(x,y+=speed,&img2,SRCPAINT);
	}
	void stay()
	{
		putimage(x,y,&img,SRCAND);
	    putimage(x,y,&img2,SRCPAINT);
	}
	void explode()
	{
		putimage(x,y,&img4,SRCAND);
	    putimage(x,y,&img3,SRCPAINT);
	}
	void setspeed(int i)
	{
		speed=i;
	}
	void setjudge(bool i)
	{
		judge=i;
	}
	bool getjudge()
	{
		return judge;
	}
    int getx()
	{
		return x;
	}
	int gety()
	{
		return y;
	}
	int getwidth()
	{
		return width;
	}
	int getlength()
	{
		return length;
	}
	int getnum()
	{
		return num;
	}
	void setnum()
	{
		num=num-1;
	}
private:
	bool judge;
	int y,x;
	IMAGE img,img2;
	IMAGE img3,img4;
	int speed;
	int width,length;
	int num;
};
class Enemy2
{
public:
	Enemy2()
	{
		y=-50;
		x=rand()%520+10;
		judge=true;
		width=90;
		length=108;
		num=100;
		loadimage(&img2,_T("E:\\picture\\enemy(2).jpg"));
		loadimage(&img,_T("E:\\picture\\enemy(2)2.jpg")); 
        loadimage(&img3,_T("E:\\picture\\explode.jpg"));
		loadimage(&img4,_T("E:\\picture\\explode2.jpg")); 
		life=4;
		speed=speed2;
	}
	void setspeed(int i)
	{
		speed=i;
	}
	void move()
	{
		putimage(x,y+=speed,&img,SRCAND);
		putimage(x,y+=speed,&img2,SRCPAINT);
	}
	void stay()
	{
		putimage(x,y,&img,SRCAND);
	    putimage(x,y,&img2,SRCPAINT);
	}
	void explode()
	{
		putimage(x+22,y+27,&img4,SRCAND);
	    putimage(x+22,y+27,&img3,SRCPAINT);
	}
	void setjudge(bool i)
	{
		judge=i;
	}
	bool getjudge()
	{
		return judge;
	}
    int getx()
	{
		return x;
	}
	void mlife()
	{
		life=life-1;
	}
	int getlife()
	{
		return life;
	}
	int gety()
	{
		return y;
	}
	int getwidth()
	{
		return width;
	}
	int getlength()
	{
		return length;
	}
	int getnum()
	{
		return num;
	}
	void setnum()
	{
		num=num-1;
	}
private:
	bool judge;
	int y,x;
	IMAGE img,img2;
	IMAGE img3,img4;
	int speed;
	int width,length;
	int num;
	int life;
};
class Enemy3
{
public:
	Enemy3()
	{
		y=-200;
		x=rand()%480+10;
		judge=true;
		width=160;
		length=264;
		num=100;
		loadimage(&img2,_T("E:\\picture\\enemy(3).jpg"));
		loadimage(&img,_T("E:\\picture\\enemy(3)2.jpg")); 
        loadimage(&img3,_T("E:\\picture\\explode.jpg"));
		loadimage(&img4,_T("E:\\picture\\explode2.jpg")); 
		life=8;
		speed=speed3;
	}
	void setspeed(int i)
	{
		speed=i;
	}
	void move()
	{
		putimage(x,y+=speed,&img,SRCAND);
		putimage(x,y+=speed,&img2,SRCPAINT);
	}
	void stay()
	{
		putimage(x,y,&img,SRCAND);
	    putimage(x,y,&img2,SRCPAINT);
	}
	void explode()
	{
		putimage(x+40,y+64,&img4,SRCAND);
	    putimage(x+40,y+64,&img3,SRCPAINT);
	}
	void setjudge(bool i)
	{
		judge=i;
	}
	bool getjudge()
	{
		return judge;
	}
    int getx()
	{
		return x;
	}
	void mlife()
	{
		life=life-1;
	}
	int getlife()
	{
		return life;
	}
	int gety()
	{
		return y;
	}
	int getwidth()
	{
		return width;
	}
	int getlength()
	{
		return length;
	}
	int getnum()
	{
		return num;
	}
	void setnum()
	{
		num=num-1;
	}
private:
	bool judge;
	int y,x;
	IMAGE img,img2;
	IMAGE img3,img4;
	int speed;
	int width,length;
	int num;
	int life;
};
vector <Bullet> allbullet;
vector<Enemy> allenemy;
vector<Enemy2> allenemy2;
vector<Enemy3> allenemy3;

Boat me(320,900);

void judgedied(vector<Enemy>::iterator);
void judgedied2(vector<Enemy2>::iterator);
void judgedied3(vector<Enemy3>::iterator);
void judgecrash(vector<Enemy>::iterator);
void judgecrash2(vector<Enemy2>::iterator);
void judgecrash3(vector<Enemy3>::iterator);
void resetmain(MOUSEMSG);
void drawtextf();
void gameover();
void again();
void judgelevel();
void adjustpara();
void choosebeginlevel();

MOUSEMSG m;	

void main()
{
	while(true)
	{
		initgraph(800, 900);
		count=0,count1=0,count2=0;//count bulletappear;count1 enemyappear;count2 enenmy move;
		enemyspeed1=150;
		enemyspeed2=1500;
		enemyspeed3=5000;
		speedi=1;
		speed1=2;
		speed2=2;
		speed3=1;
		exitmain=false;
		rate=9;
		srand(time(0));
		m=GetMouseMsg();
		me.setjudge(true);
		beginlevel=1;
		level=beginlevel;
		for(int i = 0; i < MAXSTAR; i++)
		{
			InitStar2(i);
			star[i].y = rand() % 900;
		}	
		again();
		if (exitmain==true)
			break;
        for(int i = 0; i < MAXSTAR; i++)
		{
			InitStar(i);
			star[i].y = rand() % 900;
		}	
		score=0;
		while(true)
		{
			judgelevel();
		    adjustpara();
			count1=count1+1;
			count=count+1;
			count2=count2+1;
            if (kbhit())
			{
				keyboard=getch();
				switch(keyboard)
				{
				case 'p':
					do
					{	
						setcolor(WHITE);
	                    settextstyle(20,0,_T("华文琥珀"));
						outtextxy(650,400,_T("P:继续"));
						setcolor(RED);
	                    settextstyle(70,0,_T("华文彩云"));
				        RECT i={0,0,800,900};
				        drawtext(_T("|| 暂停"), &i, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
					}
					while(getch()!='p');
					break;
				case '+':
					if (level<5)
						level=level+1;
					break;
				case '-':
					if (level>1)
						level=level-1;
					break;
				}
			}
			if (keyboard=='q')
			{
				keyboard=' ';
				break;
			}
			if (MouseHit()==true)
			{
				m = GetMouseMsg();
				if (m.x<640)
				{
					me.setx(m.x);
					me.sety(m.y);
				}
				if (count==50)
				{
					Bullet t(me.getx(),me.gety()-20);
					allbullet.push_back(t);
					count=0;
				}
			}
			else
			{
				if (count==50)
				{
					Bullet t(me.getx(),me.gety()-20);
					allbullet.push_back(t);
					count=0;
				}
			}
			if (count1%enemyspeed1==0)
			{
				Enemy t;
				allenemy.push_back(t);
				speedi=rand()%8+speed1;
			}
			if (count1%enemyspeed2==0)
			{
				Enemy2 t;
				allenemy2.push_back(t);
			}
			if (count1%enemyspeed3==0)
			{
				Enemy3 t;
				allenemy3.push_back(t);
				count1=0;
			}
			BeginBatchDraw();
			resetmain(m);
			for(vector<Bullet>::iterator iter=allbullet.begin();iter!=allbullet.end();++iter)
			{
				if ((*iter).getjudge()==true)
					(*iter).move();
			}
			if (allbullet.end()-allbullet.begin()>=10)
				allbullet.erase(allbullet.begin(),allbullet.end()-9);
			if (count2==rate)
			{				
				for(vector<Enemy3>::iterator iter=allenemy3.begin();iter!=allenemy3.end();++iter)
				{	
					judgedied3(iter);
					if ((*iter).getjudge()==true)
						(*iter).move();
					else
					{
						if((*iter).getnum()>0)
						{
							(*iter).explode();
							(*iter).setnum();
						}
					}
					judgecrash3(iter);
				}

				for(vector<Enemy2>::iterator iter=allenemy2.begin();iter!=allenemy2.end();++iter)
				{	
					judgedied2(iter);
					if ((*iter).getjudge()==true)
						(*iter).move();
					else
					{
						if((*iter).getnum()>0)
						{
							(*iter).explode();
							(*iter).setnum();
						}
					}
					judgecrash2(iter);
				}
				for(vector<Enemy>::iterator iter=allenemy.begin();iter!=allenemy.end();++iter)
				{	
					judgedied(iter);
					if ((*iter).getjudge()==true)
						(*iter).move();
					else
					{
						if((*iter).getnum()>0)
						{
							(*iter).explode();
							(*iter).setnum();
						}
					}
					judgecrash(iter);
				}
				count2=0;
			}
			else
			{
				for(vector<Enemy3>::iterator iter=allenemy3.begin();iter!=allenemy3.end();++iter)
				{	
					judgedied3(iter);
					if ((*iter).getjudge()==true)
						(*iter).stay();
					else
					{
						if((*iter).getnum()>0)
						{
							(*iter).explode();
							(*iter).setnum();
						}
					}
					judgecrash3(iter);
				}
				for(vector<Enemy2>::iterator iter=allenemy2.begin();iter!=allenemy2.end();++iter)
				{	
					judgedied2(iter);
					if ((*iter).getjudge()==true)
						(*iter).stay();
					else
					{
						if((*iter).getnum()>0)
						{
							(*iter).explode();
							(*iter).setnum();
						}
					}
					judgecrash2(iter);
				}				
				for(vector<Enemy>::iterator iter=allenemy.begin();iter!=allenemy.end();++iter)
				{
					judgedied(iter);
					if ((*iter).getjudge()==true)
						(*iter).stay();
					else
					{
						if((*iter).getnum()>0)
							(*iter).explode();
					}
					judgecrash(iter);
				}

			}
			EndBatchDraw();
			if (allenemy.end()-allenemy.begin()>=25)
				allenemy.erase(allenemy.begin(),allenemy.end()-24);	
			if (allenemy2.end()-allenemy2.begin()>=5)
				allenemy2.erase(allenemy2.begin(),allenemy2.end()-5);	
			if (allenemy3.end()-allenemy3.begin()>=5)
				allenemy3.erase(allenemy3.begin(),allenemy3.end()-4);	
            if (me.getjudge()==false)
			{
				gameover();
				break;
			}			
		}
	}
	closegraph();
}



void resetmain(MOUSEMSG n)
{
	IMAGE img,img2;
	setfillcolor(BLACK);
	setcolor(BLACK);
	fillrectangle(0,0,800,900);
	setxingkong();
	setcolor(BLUE);
	line(640,0,640,900);
	me.putboat();
	drawtextf();
};


void MoveStar(int i)
{
	setfillcolor(BLACK);
	setcolor(BLACK);
	fillcircle((int)star[i].x, star[i].y, 1);	
	star[i].y += star[i].step;
	if (star[i].y > 900)	InitStar(i);
	setfillcolor(star[i].color);
	setcolor(star[i].color);
	fillcircle((int)star[i].x, star[i].y, 1);
}
void MoveStar2(int i)
{
	setfillcolor(BLACK);
	setcolor(BLACK);
	fillcircle((int)star[i].x, star[i].y, 1);	
	star[i].y += star[i].step;
	if (star[i].y > 900)	InitStar2(i);
	setfillcolor(star[i].color);
	setcolor(star[i].color);
	fillcircle((int)star[i].x, star[i].y, 1);
}

void StayStar(int i)
{
	setfillcolor(star[i].color);
	setcolor(star[i].color);
	fillcircle((int)star[i].x, star[i].y, 1);
}


void setxingkong()
{
	countxingkong=countxingkong+1;
	if (countxingkong==10)
	{
		for(int i = 0; i < MAXSTAR; i++)
			MoveStar(i);
		countxingkong=0;
	}
	else
	{
        for(int i = 0; i < MAXSTAR; i++)
			StayStar(i);
	}
}
void setxingkong2()
{
	countxingkong=countxingkong+1;
	if (countxingkong==10)
	{
		for(int i = 0; i < MAXSTAR; i++)
			MoveStar2(i);
		countxingkong=0;
	}
	else
	{
        for(int i = 0; i < MAXSTAR; i++)
			StayStar(i);
	}
}

//星空


void judgedied(vector<Enemy>::iterator iterenemy)
{
	for(vector<Bullet>::iterator iter=allbullet.begin();iter!=allbullet.end();++iter)
	{
		if ((*iter).getjudge()==true && (*iterenemy).getjudge()==true)
		{
			if (((*iter).getx()>=(*iterenemy).getx() && ((*iter).getx())<=(*iterenemy).getx()+(*iterenemy).getwidth()) && ((*iter).gety()>=(*iterenemy).gety() && ((*iter).gety())<=(*iterenemy).gety()+(*iterenemy).getlength()))
			{
                PlaySound(_T("E:\\picture\\EXPLODE.WAV"),NULL,SND_FILENAME|SND_ASYNC);
				(*iter).setjudge(false);
				(*iterenemy).setjudge(false);
				score=score+200;
			}
		}
	}
}
void judgedied2(vector<Enemy2>::iterator iterenemy)
{
	for(vector<Bullet>::iterator iter=allbullet.begin();iter!=allbullet.end();++iter)
	{
		if ((*iter).getjudge()==true && (*iterenemy).getjudge()==true)
		{
			if (((*iter).getx()>=(*iterenemy).getx() && ((*iter).getx())<=(*iterenemy).getx()+(*iterenemy).getwidth()) && ((*iter).gety()>=(*iterenemy).gety() && ((*iter).gety())<=(*iterenemy).gety()+(*iterenemy).getlength()))
			{
				(*iterenemy).mlife();
			    (*iter).setjudge(false);
				if ((*iterenemy).getlife()<0)
				{
					PlaySound(_T("E:\\picture\\EXPLODE.WAV"),NULL,SND_FILENAME|SND_ASYNC);
					(*iterenemy).setjudge(false);
					score=score+1000;
				}
			}
		}
	}
}
void judgedied3(vector<Enemy3>::iterator iterenemy)
{
	for(vector<Bullet>::iterator iter=allbullet.begin();iter!=allbullet.end();++iter)
	{
		if ((*iter).getjudge()==true && (*iterenemy).getjudge()==true)
		{
			if (((*iter).getx()>=(*iterenemy).getx() && ((*iter).getx())<=(*iterenemy).getx()+(*iterenemy).getwidth()) && ((*iter).gety()>=(*iterenemy).gety() && ((*iter).gety())<=(*iterenemy).gety()+(*iterenemy).getlength()))
			{
				(*iterenemy).mlife();
			    (*iter).setjudge(false);
				if ((*iterenemy).getlife()<0)
				{
					PlaySound(_T("E:\\picture\\EXPLODE.WAV"),NULL,SND_FILENAME|SND_ASYNC);
					(*iterenemy).setjudge(false);
					score=score+10000;
				}
			}
		}
	}
}

void judgecrash(vector<Enemy>::iterator iterenemy)
{
	if ((*iterenemy).getjudge()==true)
	{
		
		if((me.gety()-26>(*iterenemy).gety() && me.gety()-26<(*iterenemy).gety()+(*iterenemy).getlength()) && (me.getx()>(*iterenemy).getx() && me.getx()<(*iterenemy).getx()+(*iterenemy).getwidth()))
		{
			(*iterenemy).setjudge(false);
			me.setjudge(false);
		}
		if((me.gety()+26>(*iterenemy).gety() && me.gety()+26<(*iterenemy).gety()+(*iterenemy).getlength()) && (me.getx()-25>(*iterenemy).getx() && me.getx()-25<(*iterenemy).getx()+(*iterenemy).getwidth()))
		{
			(*iterenemy).setjudge(false);
			me.setjudge(false);
		}
		if((me.gety()+26>(*iterenemy).gety() && me.gety()+26<(*iterenemy).gety()+(*iterenemy).getlength()) && (me.getx()+25>(*iterenemy).getx() && me.getx()+25<(*iterenemy).getx()+(*iterenemy).getwidth()))
		{
			(*iterenemy).setjudge(false);
			me.setjudge(false);
		}
	}
}
void judgecrash2(vector<Enemy2>::iterator iterenemy)
{
	if ((*iterenemy).getjudge()==true)
	{
		
		if((me.gety()-26>(*iterenemy).gety() && me.gety()-26<(*iterenemy).gety()+(*iterenemy).getlength()) && (me.getx()>(*iterenemy).getx() && me.getx()<(*iterenemy).getx()+(*iterenemy).getwidth()))
		{
			(*iterenemy).setjudge(false);
			me.setjudge(false);
		}
		if((me.gety()+26>(*iterenemy).gety() && me.gety()+26<(*iterenemy).gety()+(*iterenemy).getlength()) && (me.getx()-25>(*iterenemy).getx() && me.getx()-25<(*iterenemy).getx()+(*iterenemy).getwidth()))
		{
			(*iterenemy).setjudge(false);
			me.setjudge(false);
		}
		if((me.gety()+26>(*iterenemy).gety() && me.gety()+26<(*iterenemy).gety()+(*iterenemy).getlength()) && (me.getx()+25>(*iterenemy).getx() && me.getx()+25<(*iterenemy).getx()+(*iterenemy).getwidth()))
		{
			(*iterenemy).setjudge(false);
			me.setjudge(false);
		}
	}
}
void judgecrash3(vector<Enemy3>::iterator iterenemy)
{
	if ((*iterenemy).getjudge()==true)
	{
		
		if((me.gety()-26>(*iterenemy).gety() && me.gety()-26<(*iterenemy).gety()+(*iterenemy).getlength()) && (me.getx()>(*iterenemy).getx() && me.getx()<(*iterenemy).getx()+(*iterenemy).getwidth()))
		{
			(*iterenemy).setjudge(false);
			me.setjudge(false);
		}
		if((me.gety()+26>(*iterenemy).gety() && me.gety()+26<(*iterenemy).gety()+(*iterenemy).getlength()) && (me.getx()-25>(*iterenemy).getx() && me.getx()-25<(*iterenemy).getx()+(*iterenemy).getwidth()))
		{
			(*iterenemy).setjudge(false);
			me.setjudge(false);
		}
		if((me.gety()+26>(*iterenemy).gety() && me.gety()+26<(*iterenemy).gety()+(*iterenemy).getlength()) && (me.getx()+25>(*iterenemy).getx() && me.getx()+25<(*iterenemy).getx()+(*iterenemy).getwidth()))
		{
			(*iterenemy).setjudge(false);
			me.setjudge(false);
		}
	}
}


void drawtextf()
{
	setcolor(WHITE);
	settextstyle(20,0,_T("华文琥珀"));
	outtextxy(650,100,_T("得分:"));
	outtextxy(650,200,_T("难度："));
    settextstyle(30,0,_T("微软雅黑"));
	outtextxy(650,400,_T("P:暂停"));
	outtextxy(650,450,_T("Q:退出"));
	outtextxy(650,500,_T("+:增加难度"));
	outtextxy(650,550,_T("-:减小难度"));
    _itow(score,scoref,10);
	_itow(level,levelf,10);
	outtextxy(710,100,scoref);
	outtextxy(710,200,levelf);
}

void again()
{
	if (allenemy.end()-allenemy.begin()!=0)
		allenemy.erase(allenemy.begin(),allenemy.end());
	if (allenemy2.end()-allenemy2.begin()!=0)
		allenemy2.erase(allenemy2.begin(),allenemy2.end());
	if (allenemy3.end()-allenemy3.begin()!=0)
		allenemy3.erase(allenemy3.begin(),allenemy3.end());
	if (allbullet.end()-allbullet.begin()!=0)
		allbullet.erase(allbullet.begin(),allbullet.end());
	while(true)
	{
			BeginBatchDraw();
			setcolor(BLACK);
			setfillcolor(BLACK);
			fillrectangle(0,0,800,900);
			setxingkong2();
			setcolor(WHITE);
            settextstyle(70, 0, _T("黑体"));
			RECT r = {0, 0, 800, 500};
	        drawtext(_T("飞机大战"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			settextstyle(20,0,_T("华文琥珀"));
			RECT n = {250, 120, 500, 550};
	        drawtext(_T("最高分："), &n, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
            if (score>=best)
			   best=score;
            _itow(best,bestf,10);
	        outtextxy(420,326,bestf);
			setcolor(BROWN);
            settextstyle(30,0,_T("微软雅黑"));
	        outtextxy(650,800,_T("制作：汤豪"));
			setcolor(WHITE);
            settextstyle(30,0,_T("华文彩云"));
			RECT k={0,350,800,600};
			drawtext(_T("开始游戏"), &k, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			RECT f={0,350,800,1000};
			drawtext(_T("退出"), &f, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			RECT t={0,350,800,800};
			drawtext(_T("选择难度"), &t, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
			if (MouseHit()==true)
				m = GetMouseMsg();
			if ((m.x>337 && m.x<470) && (m.y>455 && m.y<497))
			{
				setcolor(BLUE);
				RECT i={0,350,800,600};
				drawtext(_T("开始游戏"), &i, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                if(m.uMsg==WM_LBUTTONDOWN)
					break;
			}
			if ((m.x>337 && m.x<470) && (m.y>555 && m.y<597))
			{
				setcolor(BLUE);
				RECT i={0,350,800,800};
				drawtext(_T("选择难度"), &i, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
				if(m.uMsg==WM_LBUTTONDOWN)
				{
					click=true;
				}
				if (levelchosed==true)
					break;
			}
			if ((m.x>370 && m.x<435) && (m.y>655 && m.y<697))
			{
				setcolor(BLUE);
				RECT i={0,350,800,1000};
				drawtext(_T("退出"), &i, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
                if(m.uMsg==WM_LBUTTONDOWN)
				{
					exitmain=true;
				    break;
				}
				
			}
			EndBatchDraw();
			if (click==true)
			{
				click=false;
				choosebeginlevel();
			}
			if (levelchosed==true)
			{
				levelchosed=false;
				break;
			}
	}
}

void gameover()
{
	me.explode();
	int ran=0;
	srand(time(0));
	ran=rand()%2+1;
	/*if (ran==1)
		PlaySound(_T("E:\\picture\\end.WAV"),NULL,SND_FILENAME|SND_ASYNC);
	if (ran==2)
		PlaySound(_T("E:\\picture\\end2.WAV"),NULL,SND_FILENAME|SND_ASYNC);*/
	bool inputjudge=false;
	for (int i=0;i<=900;i++)
	{
		if (kbhit())
		{
			inputjudge=true;break;
		}
		setcolor(WHITE);
		line(0,i,800,i);
		Sleep(1);
	}
	if (inputjudge==false)
	{
		for (int i=900;i>=0;i--)
		{
			setcolor(BLACK);
			line(0,i,800,i);
			Sleep(1);
		}
	}
	setcolor(BLACK);
	setfillcolor(BLACK);
	fillrectangle(0,0,800,900);
	setcolor(WHITE);
    settextstyle(80, 0, _T("幼圆"));
	RECT r={0,0,800,900};
    drawtext(_T("GAME OVER"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	Sleep(3500);
	PlaySound(_T("E:\\picture\\EXPLODE.WAV"),NULL,SND_FILENAME|SND_ASYNC);
}

void judgelevel()
{	
		if (score>20000 && level<2)
			level=2;
		if (score>50000 && level<3 && level>=2)
			level=3;
		if (score>100000 && level<4 && level>=3)
			level=4;
		if (score>200000 && level<5 && level>=4)
			level=5;
}

void adjustpara()
{
	switch (level)
	{
	case 5:
	    enemyspeed1=50;
		enemyspeed2=400;
		enemyspeed3=1000;
		rate=8;
		speed1=5;
		speed2=5;
		speed3=4;
		break;
	case 4:
		enemyspeed1=60;
		enemyspeed2=600;
		enemyspeed3=2000;
		speed1=5;
		speed2=5;
		speed3=4;
		rate=8;
		break;
	case 3:
		enemyspeed1=100;
		enemyspeed2=1000;
		enemyspeed3=3000;
		speed1=3;
		speed2=3;
		speed3=2;
		rate=9;
		break;
	case 2:
		enemyspeed1=100;
		enemyspeed2=1000;
		enemyspeed3=3000;
		speed1=2;
		speed2=2;
		speed3=1;
		rate=9;
		break;
	case 1:
		enemyspeed1=150;
		enemyspeed2=1500;
		enemyspeed3=5000;
		speed1=2;
		speed2=2;
		speed3=1;
		rate=9;
		break;
	}
}
void choosebeginlevel()
{
	for(int i = 0; i < MAXSTAR; i++)
	{
		InitStar2(i);
		star[i].y = rand() % 900;
	}	
	while(true)
	{
		BeginBatchDraw();
		setcolor(BLACK);
		setfillcolor(BLACK);
		fillrectangle(0,0,800,900);
		setxingkong2();
		if (MouseHit()==true)
			m = GetMouseMsg();
		setcolor(WHITE);
		settextstyle(60,0,_T("华文彩云"));
		outtextxy(100,150,_T("难度:"));
		outtextxy(400,300,_T("1"));
		outtextxy(400,400,_T("2"));
		outtextxy(400,500,_T("3"));
		outtextxy(400,600,_T("4"));
		outtextxy(400,700,_T("5"));
		outtextxy(650,800,_T("返回"));
	    if ((m.x>400 && m.x<425) && (m.y>300 && m.y<350))
		{
			level=1;
			setcolor(BLUE);
			outtextxy(400,300,_T("1"));
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				levelchosed=true;
				break;
			}			
		}
	    if ((m.x>400 && m.x<425) && (m.y>400 && m.y<450))
		{
			level=2;
			setcolor(BLUE);
			outtextxy(400,400,_T("2"));
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				levelchosed=true;
				break;
			}			
		}
	    if ((m.x>400 && m.x<425) && (m.y>500 && m.y<550))
		{
			level=3;
			setcolor(BLUE);
			outtextxy(400,500,_T("3"));
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				levelchosed=true;
				break;
			}			
		}
	    if ((m.x>400 && m.x<425) && (m.y>600 && m.y<650))
		{
			level=4;
			setcolor(BLUE);
			outtextxy(400,600,_T("4"));
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				levelchosed=true;
				break;
			}			
		}
	    if ((m.x>400 && m.x<425) && (m.y>700 && m.y<750))
		{
			level=5;
			setcolor(BLUE);
			outtextxy(400,700,_T("5"));
			if(m.uMsg==WM_LBUTTONDOWN)
			{
				levelchosed=true;
				break;
			}			
		}
	    if ((m.x>650 && m.x<765) && (m.y>800 && m.y<860))
		{
			setcolor(BLUE);
		    outtextxy(650,800,_T("返回"));
			if(m.uMsg==WM_LBUTTONDOWN)
				break;
		}
		EndBatchDraw();
	}
}