#include "SDL.h"
#include <conio.h>
#include <stdlib.h>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include <cmath>
#include <SDL.h>
#include <SDL_ttf.h>
#include <conio.h>
#include <sstream>
#include <fstream>
using namespace std;

typedef struct {
int exist;
int n;
int m;
int strg;
int type;
int img;
/*
1 solid
2 bomb
3 life
4 triple ball
...
*/
} brick;

typedef struct point{
double x;
double y;
} point;

double max(double a,double b)
{
    if(a>b) return a;
    else return b;
}

double min(double a,double b)
{
    if(a<b) return a;
    else return b;
}

int check(double x1,double x2,double y1,double y2,double x,double y)
{
    if(x>min(x1,x2)&&x<max(x1,x2)&&y>min(y1,y2)&&y<max(y1,y2)) return 1;
    else return 0;
}

typedef struct{
int dmg;
int type;
double x;
double y;

} bult;

double ref(double tta,double sine ,char a)
{
    double alpha=asin(sine);
    if(a=='x') return cos(M_PI-tta-2*alpha);
    if(a=='y') return sin(M_PI-tta-2*alpha); ;
}
int dis(double x1,double y1,double x2,double y2,double r)
{
    if((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1)<=r*r) return 1;
    else return 0;
}

void rotate(double &x,double &y,double tta)
{
double t=x;
x=x*cos(tta)-y*sin(tta);
y=t*sin(tta)+y*cos(tta);
}


void ref(double &x,double &y,double tta)
{
    double R=sqrt(x*x+y*y);
    x=R*cos(tta);
    y=R*sin(tta);
    double a=rand()%11;
    double alpha=a*M_PI_4/5/4-M_PI_4/4;
    rotate(x,y,alpha);
}

string inttost(int n)
{
  stringstream ss;
    ss<<n;
    string st;
    ss>>st;
    return st;
}

int toint(string s)
{
    stringstream degree(s);
    int u = 0;
    degree >> u;
    return u;
}

int main(int argc, char *argv[])
{
double w=1200,h=800,X=w/2,Y=h-80,X2=w/2+300,Y2=h-80,x,y,x0=w/2,y0=Y-40-1,t=0,tta=M_PI_2,d=40,d2=70,a,v,temp,T=100,T1=100,
i0,j0,x1,x2,y1,y2,move=0,c=5*d/9,c1=c,mu=0.6,vy=-50,vy0=-50,vx,shift=60,l=180,tb=100,rb,yb,xb,xr,yr;
int live=3,lvl=1,k=0,n=23,k1,k2,k3,k4,S=0,S2=0,kb=0,lv=0,corn1=0,corn2=0,corn3=0,corn4=0,corn1b=0,corn2b=0,corn3b=0,corn4b=0,
txt=1,broken=0,scor=0,dif=1,ld=0,x0r,y0r;
int t1,texW=0,texH=0,texW1=0,texH1=0,texW2=0,texH2=0,save=0,menu=1,game=0,state=0,select=0,wname,hname,select2=1,col,ply2=0,
load=0,pause=0,pause2=0,Tp=100,tm=0,checkline=0,bricks=10,cheat=0,newac=1,rocket=0,mover=0,selectdif=1,over=0,tmu=0,tmu1=0;
string level,score,lives,name,text,account,gamefile,gamename,namefile,accountfile,num;
char chr;
const char* img[n];
img[0]="ball.png";
img[1]="brick1.png";
img[2]="brick2.png";
img[3]="brick3.png";
img[4]="brick4.png";
img[5]="brick5.png";
img[6]="brick6.png";
img[7]="brick7.png";
img[8]="brick8.png";
img[9]="brick9.png";
img[10]="brick10.png";
img[11]="bomb.png";
img[12]="heart.png";
img[13]="rocket.png";
img[14]="rocketbrick.png";
img[15]="explosion.png";
img[16]="superball.png";
img[17]="flash.png";
img[18]="brick9l.png";
img[19]="brick10.png";
img[20]="board2.png";
img[21]="board.png";
img[22]="back.png";

int m=27;
const char* option[m];
option[0]="newgame.png";
option[1]="loadgame.png";
option[2]="quit.png";
option[3]="snewgame.png";
option[4]="sloadgame.png";
option[5]="squit.png";
option[6]="entername.png";
option[7]="pl1.png";
option[8]="spl1.png";
option[9]="pl2.png";
option[10]="spl2.png";
option[11]="choose.png";
option[12]="pause.png";
option[13]="gameover.png";
option[14]="resume.png";
option[15]="sresume.png";
option[16]="save.png";
option[17]="ssave.png";
option[18]="quitgame.png";
option[19]="squitgame.png";
option[20]="bar.png";
option[21]="easy.png";
option[22]="seasy.png";
option[23]="medium.png";
option[24]="smedium.png";
option[25]="hard.png";
option[26]="shard.png";



const char* colors[7];
colors[0]="silver.png";
colors[1]="gold.png";
colors[2]="purple.png";
colors[3]="red.png";
colors[4]="blue.png";
colors[5]="green.png";
colors[6]="frame.png";
//color[7]="";

const char*ballcol[6];
ballcol[0]="ball1.png";
ballcol[1]="ball2.png";
ballcol[2]="ball3.png";
ballcol[3]="ball4.png";
ballcol[4]="ball5.png";
ballcol[5]="ball6.png";




TTF_Init();
TTF_Font * font = TTF_OpenFont("arial.ttf", 40);
TTF_Font * fontname = TTF_OpenFont("arial.ttf", 35);
SDL_Color color = { 0,255, 255 };
SDL_Color colorname={255,255,255};
ifstream readfile;
ofstream writefile;


SDL_Rect gameover= { w/2-200, h/2-100, 400, 200 };
brick brick[8][13];
bult ball;
ball.dmg=lvl;

        SDL_Init(SDL_INIT_VIDEO);

        SDL_Init(SDL_INIT_AUDIO);
        int n1=9;
        SDL_AudioSpec wavSpec[n1];
        Uint32 wavLength[n1];
        Uint8 *wavBuffer[n1];
        SDL_AudioDeviceID deviceId[n1];
        SDL_LoadWAV("mainm.wav", &wavSpec[0], &wavBuffer[0], &wavLength[0]);
        SDL_LoadWAV("ingame.wav", &wavSpec[1], &wavBuffer[1], &wavLength[1]);
        SDL_LoadWAV("hitbrick.wav", &wavSpec[2], &wavBuffer[2], &wavLength[2]);
        SDL_LoadWAV("hitwall.wav", &wavSpec[3], &wavBuffer[3], &wavLength[3]);
        SDL_LoadWAV("hitboard.wav", &wavSpec[4], &wavBuffer[4], &wavLength[4]);
        SDL_LoadWAV("explosion.wav", &wavSpec[5], &wavBuffer[5], &wavLength[5]);
        SDL_LoadWAV("heart.wav", &wavSpec[6], &wavBuffer[6], &wavLength[6]);
        SDL_LoadWAV("launch.wav", &wavSpec[7], &wavBuffer[7], &wavLength[7]);
        SDL_LoadWAV("gameover.wav", &wavSpec[8], &wavBuffer[8], &wavLength[8]);





        for(int i=0;i<n1;i++)
       {
        deviceId[i] = SDL_OpenAudioDevice(NULL, 0, &wavSpec[i], NULL, 0);

       }


        //int suc;
        SDL_QueueAudio(deviceId[0], wavBuffer[0], wavLength[0]);
        SDL_PauseAudioDevice(deviceId[0], 0);


        SDL_Window *window;
        SDL_Renderer *ren;
                SDL_Event *event = new SDL_Event();
                 SDL_Event *event2 = new SDL_Event();



        SDL_Surface * surface,*surface1,*surface2,*surfacename;
        SDL_Texture *textlevel,*textlives,*textscore,*texturename,*texturerocket;
        SDL_Rect rectscore,rectlevel,rectlives;


        SDL_Texture * texture[n];
        SDL_Rect rect[8][13];

        window = SDL_CreateWindow("SDL_CreateTexture",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,w, h,SDL_WINDOW_RESIZABLE);
        ren = SDL_CreateRenderer(window, -1, 0);
        SDL_Texture * textureoption[m];
        SDL_Texture * scolor[7];

            for(int i=0;i<m;i++)
            textureoption[i]=IMG_LoadTexture(ren, option[i]);

            for(int i=0;i<7;i++)
            scolor[i]=IMG_LoadTexture(ren, colors[i]);

                for(int i=1;i<n;i++)
                texture[i] = IMG_LoadTexture(ren, img[i]);

                //const char*imgrocket="rocket.png";
                texturerocket=IMG_LoadTexture(ren, "rocket.png");

                for(int j=0;j<13;j++)
                {
                checkline=0;

                for(int i=0;i<8;i++)
                {
                a=rand()%8;
                if(a!=0)
                {
                a=rand()%20;

                brick[i][j].strg=a-15;
                if(brick[i][j].strg<=0||j>2) {brick[i][j].exist=0; brick[i][j].strg=0;}
                else {brick[i][j].exist=1;}
                if(brick[i][j].exist==1) checkline++;
                brick[i][j].type=0;
                }
                else
                {

                a=rand()%2;
                //if(a==0) brick[i][0].type=1;
                 if(a==1) brick[i][j].type=2;
                else if(a==0) brick[i][j].type=3;
                else if(a==3) brick[i][j].type=4;
                else if(a==4) brick[i][j].type=5;
                else if(a==5) brick[i][j].type=6;
                a=rand()%20;

                brick[i][j].strg=a-15;
                if(brick[i][j].strg<=0||j>2) {brick[i][j].exist=0; brick[i][j].strg=0;}
                else {brick[i][j].exist=1;}
                if(brick[i][j].exist==1) {checkline++; brick[i][0].strg=1;}
                }


                rect[i][j] = { 130+i*120, 10+j*60, 100, 50 };
                }
                if(checkline<6&&j<=2) j--;

                }
        while(1)
        {
        if(menu==1)
        {
            while(1)
            {
                if(tmu1>=10000)
                {
                   SDL_QueueAudio(deviceId[0], wavBuffer[0], wavLength[0]);
        SDL_PauseAudioDevice(deviceId[0], 0);
                tmu1=0;
                //cout<<tmu1<<endl;
                }
                tmu1+=1;
                if(game==1) break;
                SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderClear(ren);
                SDL_Rect rectbackground = { 0, 0, w, h };
                SDL_RenderCopy(ren, texture[22], NULL, &rectbackground);
                if(menu==0) break;
                if(state==0)//enter name
                {
                        SDL_Rect rectname={w/2-300,h/2-25-50,600,50};
                        SDL_RenderCopy(ren, textureoption[6], NULL, &rectname);
                        surfacename = TTF_RenderText_Solid(fontname, name.c_str() , colorname);
                        texturename = SDL_CreateTextureFromSurface(ren, surfacename);
                        SDL_QueryTexture(texturename, NULL, NULL, &wname, &hname);
                        SDL_Rect rectname1={w/2-60,h/2-hname/2-50,wname,hname};
                        SDL_RenderCopy(ren, texturename, NULL, &rectname1);

                }
                if(state==1)//main
                {
                             SDL_Rect rect1={w/2-160,h/2-40-120,320,80},rect2={w/2-160,h/2-40,320,80},rect3={w/2-160,h/2-40+120,320,80};
                             if(select!=1)
                              SDL_RenderCopy(ren, textureoption[0], NULL, &rect1);
                             else
                             SDL_RenderCopy(ren, textureoption[3], NULL, &rect1);
                             if(select!=2)
                             SDL_RenderCopy(ren, textureoption[1], NULL, &rect2);
                             else
                             SDL_RenderCopy(ren, textureoption[4], NULL, &rect2);
                             if(select!=3)
                             SDL_RenderCopy(ren, textureoption[2], NULL, &rect3);
                             else
                             SDL_RenderCopy(ren, textureoption[5], NULL, &rect3);
                }
                   else if(state==2) //new
                    {
                       // SDL_Rect rectname={w/2-300,h/2-25-50,600,50},
                        SDL_Rect choosecolor={w/2-160,h-40-300,320,80};
                        SDL_Rect pl1={w/2-120-130,140,240,60};
                        SDL_Rect pl2={w/2-120+130,140,240,60};

                        SDL_Rect dif1={w/2-120-240,140+180,240,60};
                        SDL_Rect dif2={w/2-120,140+180,240,60};
                        SDL_Rect dif3={w/2-120+240,140+180,240,60};

                        if(selectdif!=1)
                            SDL_RenderCopy(ren, textureoption[21], NULL, &dif1);
                        else
                            SDL_RenderCopy(ren, textureoption[22], NULL, &dif1);
                        if(selectdif!=2)
                            SDL_RenderCopy(ren, textureoption[23], NULL, &dif2);
                        else
                            SDL_RenderCopy(ren, textureoption[24], NULL, &dif2);
                            if(selectdif!=3)
                            SDL_RenderCopy(ren, textureoption[25], NULL, &dif3);
                        else
                            SDL_RenderCopy(ren, textureoption[26], NULL, &dif3);



                       // SDL_RenderCopy(ren, textureoption[6], NULL, &rectname);
                        SDL_RenderCopy(ren, textureoption[11], NULL, &choosecolor);
                        if(select2==1)
                        {
                            SDL_RenderCopy(ren, textureoption[8], NULL, &pl1);
                            SDL_RenderCopy(ren, textureoption[9], NULL, &pl2);
                        }
                        else if(select2==2)
                        {
                            SDL_RenderCopy(ren, textureoption[7], NULL, &pl1);
                            SDL_RenderCopy(ren, textureoption[10], NULL, &pl2);
                        }

                        /*surfacename = TTF_RenderText_Solid(fontname, name.c_str() , colorname);
                        texturename = SDL_CreateTextureFromSurface(ren, surfacename);
                        SDL_QueryTexture(texturename, NULL, NULL, &wname, &hname);
                        SDL_Rect rectname1={w/2-60,h/2-hname/2-50,wname,hname};
                        SDL_RenderCopy(ren, texturename, NULL, &rectname1);*/
                        SDL_Rect rectcol[6],rectframe;

                        for(int i=0;i<6;i++)
                        {
                        rectcol[i]={w/2-250+90*i,h-200,50,50};
                        SDL_RenderCopy(ren, scolor[i], NULL, &rectcol[i]);
                        if(select==i+1)
                        {
                        rectframe={w/2-250+90*i-5,h-200-5,60,60};
                        SDL_RenderCopy(ren, scolor[6], NULL, &rectframe);

                        }
                        }

                    }
                    else if(state==3)//load
                    {
                    if(load==0)
                    {
                    SDL_Rect loadbar={w/2-350,h/2-350,700,700};
                    SDL_RenderCopy(ren, textureoption[12], NULL, &loadbar);
                    SDL_Rect rectbar={w/2-300,h/2-250-25+60*(select-1),600,50};
                    if(select!=0)
                    SDL_RenderCopy(ren, textureoption[20], NULL, &rectbar);
                    //SDL_Rect rectload={w/2-300,h/2-400,600,800};
                    //SDL_RenderCopy(ren, textureoption[12], NULL, &rectload);
                    namefile=name+".txt";
                    readfile.open(namefile.c_str());
                    readfile>>text;
                    //cout<<text<<endl;
                    //cout<<text.length();
                    int fd=text.length();

                    num=inttost(text.length());
                    for(int i=fd;i>0;i--)
                    {
                    text=name+" game "+inttost(i);

                    //SDL_Rect rectname={w/2-300-200,h/2-25+50*i,600,50};
                    //SDL_RenderCopy(ren, textureoption[6], NULL, &rectname);
                    surfacename = TTF_RenderText_Solid(fontname, text.c_str() , colorname);
                    texturename = SDL_CreateTextureFromSurface(ren, surfacename);
                    SDL_QueryTexture(texturename, NULL, NULL, &wname, &hname);
                    SDL_Rect rectname1={w/2-wname/2,h/2-hname/2-250+60*(fd-i),wname,hname};
                    SDL_RenderCopy(ren, texturename, NULL, &rectname1);
                    //readfile>>text;
                    //surfacename = TTF_RenderText_Solid(fontname, name.c_str() , colorname);
                    //texturename = SDL_CreateTextureFromSurface(ren, surfacename);
                    //SDL_QueryTexture(texturename, NULL, NULL, &wname, &hname);
                    //rectname1={w/2+250-wname/2,h/2-hname/2-250+60*i,wname,hname};
                    //SDL_RenderCopy(ren, texturename, NULL, &rectname1);
                    }
                    //cout<<ld;
                    readfile.close();
                    }
                    else if(load==1)
                    {
                        gamefile=gamename+".txt";
                        cout<<endl<<gamefile<<endl;
                        readfile.open(gamefile.c_str());
                        /*for(int i=0;readfile.good();i++)
                        {
                            readfile>>text;
                            if(i+1==select) break;
                        }
                        gamefile=text;
                        string file7=gamefile+".txt";
                        readfile.open(file7.c_str());*/
                        readfile>>dif;
                        readfile>>ply2;
                        readfile>>col;
                        readfile>>broken;
                        readfile>>live;
                        readfile>>lvl;
                        readfile>>scor;
                        readfile>>x0;
                        readfile>>y0;
                        readfile>>move;
                        readfile>>X;
                        readfile>>Y;
                        readfile>>vx;
                        readfile>>vy;
                        readfile>>t;
                        readfile>>Tp;
                        readfile>>rocket;
                        for(int i=0;i<8;i++)
                        for(int j=0;j<13;j++)
                        {
                            readfile>>brick[i][j].exist;
                            readfile>>brick[i][j].strg;
                            readfile>>brick[i][j].type;
                        }
                        //cout<<t;
                        readfile.close();
                        game=1;
                        menu=0;
                        pause=1;
                        select=1;
                        //SDL_Delay(2000);

                    }





                    }

                SDL_RenderPresent(ren);
                SDL_Delay(10);

                        if( SDL_PollEvent( event2 ) )
                if( event2->type == SDL_KEYDOWN )
                {
                    switch(event2->key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        if(state==0) //enter
                        {
                            state=1;
                            readfile.open("accounts.txt");
                            while(readfile.good())
                            {
                                readfile>>text;
                                if(name==text) newac=0;
                            }
                            readfile.close();
                            if(newac==1)
                            {
                            readfile.open("accounts.txt");
                            writefile.open("temp.txt");
                            while(readfile.good())
                            {
                                readfile>>text;
                                writefile<<text<<endl;
                            }
                            readfile.close();
                            writefile.close();
                            writefile.open("accounts.txt");
                            readfile.open("temp.txt");
                            writefile<<name<<endl;
                            while(readfile.good())
                            {
                                readfile>>text;
                                writefile<<text<<endl;
                            }
                            readfile.close();
                            writefile.close();
                            newac=0;
                            }


                        }
                        else if(state==1) //menu
                        {
                        if(select==1)
                            {state=2; select=1;}
                        else if(select==3)

                        {
                            SDL_DestroyWindow(window);
                            SDL_DestroyRenderer(ren);
                            SDL_Quit();
                        }
                        else if(select==2)
                            {
                                namefile=name+".txt";
                                readfile.open(namefile.c_str());
                                   if(readfile.good())
                                   {
                                   state=3; select=0; pause=1; break;
                                   }
                                readfile.close();
                                namefile=name+".txt";
                                readfile.open(namefile.c_str());
                                readfile.close();
                            }
                        }
                        else if(state==2) //new
                        {
                            if(select2==2)
                                ply2=1;
                            col=select-1;
                            texture[0]=IMG_LoadTexture(ren, ballcol[col]);
                            game=1;
                            menu=0;
                            select=0;
                            dif=selectdif;
                            ld=1;
                            text="";
                            namefile=name+".txt";
                            readfile.open(namefile.c_str());
                            readfile>>text;
                            text=text+"1";
                            readfile.close();
                            writefile.open(namefile.c_str());
                            writefile<<text<<endl;
                            gamename=name+" game "+inttost(text.length());
                            cout<<gamename<<endl;

                            /*ld=1;
                            namefile=name+".txt";
                            readfile.open(namefile.c_str());
                            writefile.open("temp.txt");
                            while(readfile.good())
                            {
                                if(getline(readfile,text)) ld++;
                                else break;
                                writefile<<text<<endl;
                            }
                            readfile.close();
                            writefile.close();
                            gamename=name+" game "+inttost(ld);
                            if(ld==1)
                            {
                            cout<<gamename<<endl;
                            writefile.open(namefile.c_str());
                            writefile<<gamename<<endl;
                            writefile.close();
                            }
                            else
                            {
                            readfile.open("temp.txt");
                            writefile.open(namefile.c_str());
                            writefile<<gamename<<endl;
                            while(readfile.good())
                            {
                                if(getline(readfile,text));
                                else break;
                                writefile<<text<<endl;
                            }

                            readfile.close();
                            writefile.close();
                            }*/
                        }
                        else if(state==3) //load
                        {

                            //cout<<;

                            if(select!=0)
                            {
                            cout<<num<<endl;
                            gamename=name+" game "+inttost(toint(num)-select+1);
                            load=1;
                            cout<<endl<<gamename;
                            readfile.close();
                            }

                        }
                        break;
                    case SDLK_RIGHT:
                    select2=2;
                    break;
                    case SDLK_LEFT:
                    select2=1;
                    break;
                    case SDLK_ESCAPE:
                    state=1;
                    break;
                    case SDLK_UP:
                    if(state==1)
                    {
                    if(select==0||select==1) select=3;
                    else select--;
                    }
                    else if(state==2)
                    {
                    if(select==0||select==1) select=6;
                    else select--;
                    }
                    else if(state==3)
                    {
                        if(select==1||select==0) select=toint(num);
                        else select--;
                    }
                    break;
                    case SDLK_DOWN:
                    if(state==1)
                    {
                        if(select==3) select=1;
                        else select++;
                    }
                    else if(state==2)
                    {
                        if(select==6) select==1;
                        else  select++;
                    }
                    else if(state==3)
                    {
                        if(select==toint(num)) select=1;
                        else select++;
                    }
                    break;
                    /*case SDLK_1:
                    selectdif=1;
                    break;
                    case SDLK_2:
                    selectdif=2;
                    break;
                    case SDLK_3:
                    selectdif=3;
                    break;*/
                        case SDLK_DELETE:
                        chr=' ';
                        name=name+chr;
                        break;
                        case SDLK_q:
                        chr='q';
                        name=name+chr;
                        break;
                        case SDLK_w:
                        chr='w';
                        name=name+chr;
                        break;
                        case SDLK_e:
                        chr='e';
                        name=name+chr;
                        break;
                        case SDLK_r:
                        chr='r';
                        name=name+chr;
                        break;
                        case SDLK_t:
                        chr='t';
                        name=name+chr;
                        break;
                        case SDLK_y:
                        chr='y';
                        name=name+chr;
                        break;
                        case SDLK_u:
                        chr='u';
                        name=name+chr;
                        break;
                        case SDLK_i:
                        chr='i';
                        name=name+chr;
                        break;
                        case SDLK_o:
                        chr='o';
                        name=name+chr;
                        break;
                        case SDLK_p:
                        chr='p';
                        name=name+chr;
                        break;
                        case SDLK_a:
                        chr='a';
                        name=name+chr;
                        break;
                        case SDLK_s:
                        chr='s';
                        name=name+chr;
                        break;
                        case SDLK_d:
                        chr='d';
                        name=name+chr;
                        break;
                        case SDLK_f:
                        chr='f';
                        name=name+chr;
                        break;
                        case SDLK_g:
                        chr='g';
                        name=name+chr;
                        break;
                        case SDLK_h:
                        chr='h';
                        name=name+chr;
                        break;
                        case SDLK_j:
                        chr='j';
                        name=name+chr;
                        break;
                        case SDLK_k:
                        chr='k';
                        name=name+chr;
                        break;
                        case SDLK_l:
                        chr='l';
                        name=name+chr;
                        break;
                        case SDLK_z:
                        chr='z';
                        name=name+chr;
                        break;
                        case SDLK_x:
                        chr='x';
                        name=name+chr;
                        break;
                        case SDLK_c:
                        chr='c';
                        name=name+chr;
                        break;
                        case SDLK_v:
                        chr='v';
                        name=name+chr;
                        break;
                        case SDLK_b:
                        chr='b';
                        name=name+chr;
                        break;
                        case SDLK_n:
                        chr='n';
                        name=name+chr;
                        break;
                        case SDLK_m:
                        chr='m';
                        name=name+chr;
                        break;
                        case SDLK_0:
                        chr='0';
                        name=name+chr;
                        break;
                        case SDLK_1:
                            if(state==2)
                                selectdif=1;
                            else
                            {
                        chr='1';
                        name=name+chr;
                            }
                        break;
                        case SDLK_2:
                            if(state==2)
                                selectdif=2;
                            else
                            {
                        chr='2';
                        name=name+chr;
                            }
                        break;
                        case SDLK_3:
                            if(state==2)
                                selectdif=3;
                            else
                            {
                        chr='3';
                        name=name+chr;
                            }
                        break;
                        case SDLK_4:
                        chr='4';
                        name=name+chr;
                        break;
                        case SDLK_5:
                        chr='5';
                        name=name+chr;
                        break;
                        case SDLK_6:
                        chr='6';
                        name=name+chr;
                        break;
                        case SDLK_7:
                        chr='7';
                        name=name+chr;
                        break;
                        case SDLK_8:
                        chr='8';
                        name=name+chr;
                        break;
                        case SDLK_9:
                        chr='9';
                        name=name+chr;
                        break;
                        case SDLK_BACKSPACE:
                        name = name.substr(0, name.size()-1);
                        break;

                    }
                }
            }
        }

       else if(pause==1&&pause2==1&&game==0)
       {

             if(save==1)
        {
           cout<<"saving"<<endl;


            ofstream savefile;
            cout<<"saving"<<endl;
            //cout<<gamename<<endl;
            gamefile=gamename+".txt";
            savefile.open(gamefile.c_str());
            savefile<<dif<<endl;
            savefile<<ply2<<endl;
            savefile<<col<<endl;
            savefile<<broken<<endl;
            savefile<<live<<endl;
            savefile<<lvl<<endl;
            savefile<<scor<<endl;
            savefile<<x0<<endl;
            savefile<<y0<<endl;
            savefile<<move<<endl;
            savefile<<X<<endl;
            savefile<<Y<<endl;
            savefile<<vx<<endl;
            savefile<<vy<<endl;
            savefile<<t<<endl;
            savefile<<Tp<<endl;
            savefile<<rocket<<endl;
            for(int i=0;i<8;i++)
            for(int j=0;j<13;j++)
            {
            savefile<<brick[i][j].exist<<endl;
            savefile<<brick[i][j].strg<<endl;
            savefile<<brick[i][j].type<<endl;
            }
             savefile.close();
            cout<<"saved";





           save=0;
           game=1;
           //pause=0;
           pause2=0;
           //pause=0;

        }

              /*          if( SDL_PollEvent( event2 ) )
                if( event2->type == SDL_KEYDOWN )
                {
                    switch(event2->key.keysym.sym)
                    {
                    case SDLK_SPACE:
                        save=1;
                        break;
                    }
                }*/
            //if(game==1) break;
        }
        else if(game==1)
        {
        if(pause==0||1)
        {
        cout<<dif;
        SDL_CloseAudioDevice(deviceId[0]);
        SDL_FreeWAV(wavBuffer[0]);
        SDL_Delay(200);
        SDL_QueueAudio(deviceId[1], wavBuffer[1], wavLength[1]);
        SDL_PauseAudioDevice(deviceId[1], 0);
        texture[0]=IMG_LoadTexture(ren, ballcol[col]);
        }
        //cout<<col;
        //cout<<"game";
        /*namefile=name+".txt";
        writefile.open(namefile.c_str());
        writefile.close();
        readfile.open(namefile.c_str());
        readfile.close();*/


        while (1) {
            tmu+=1;
            if(tmu>=5000)
            {
                //cout<<tmu<<endl;
                SDL_QueueAudio(deviceId[1], wavBuffer[1], wavLength[1]);
               SDL_PauseAudioDevice(deviceId[1], 0);
                tmu=0;
            }

                if(game==0)
                break;
                load=0;
                int checkall=0;
                if(ball.dmg<=0&&live>0&&over==0)
                {
                            lvl++;
                            ball.dmg=lvl;
                            t=0;
                            x0=w/2;
                            y0=Y-50;
                            T=0;
                            //tta=M_PI_2;
                            vy=vy0;
                            vx=0;
                            j0=j0+1;
                            for(int i=7;i>=0;i--)
                            for(int j=12;j>=0;j--)
                            {
                                brick[i][j+1]=brick[i][j];
                            }
                            checkline=0;
                            while(checkline<6)
                            {
                            checkline=0;
                            for(int i=0;i<8;i++)
                            {
                                a=rand()%6;
                                if(a!=0)
                                {
                                a=rand()%20;
                                if(dif==1)
                                brick[i][0].strg=a-15+lvl;
                                else if(dif==2)
                                brick[i][0].strg=a-15+lvl*lvl;
                                else if(dif==3)
                                brick[i][0].strg=a-15+lvl*lvl*lvl;

                                if(brick[i][0].strg<=0) {brick[i][0].exist=0; brick[i][0].strg=0;}
                                else {brick[i][0].exist=1; }
                                if(brick[i][0].exist==1) checkline++;
                                brick[i][0].n=i;
                                brick[i][0].m=0;
                                brick[i][0].type=0;
                                }
                                else
                                {
                                a=rand()%3;
                                if(a==0) brick[i][0].type=1;
                                else if(a==1) brick[i][0].type=2;
                                else if(a==2) brick[i][0].type=3;
                                else if(a==3) brick[i][0].type=4;
                                else if(a==4) brick[i][0].type=5;
                                else if(a==5) brick[i][0].type=6;
                                a=rand()%20;
                                if(dif==1)
                                brick[i][0].strg=a-15+lvl;
                                else if(dif==2)
                                brick[i][0].strg=a-15+lvl*lvl;
                                else if(dif==3)
                                brick[i][0].strg=a-15+lvl*lvl*lvl;
                                if(brick[i][0].strg<=0) {brick[i][0].exist=0; brick[i][0].strg=0;}
                                else {brick[i][0].exist=1; }
                                if(brick[i][0].exist==1) {checkline++; brick[i][0].strg=1;}
                                }
                            }
                            }

                            lv=1;
                            move=0;
                            Tp=0;
                            txt=1;
                            scor=scor+(lvl-1)*broken;
                            broken=0;


                }
                if(y>=w)
                {
                            t=0;
                            x0=w/2;
                            y0=Y-50;
                            T=0;
                            vy=vy0;
                            vx=0;
                            move=0;
                            txt=1;
                            live--;
                }
                if(move==1)
                {
                x=x0+vx*t;
                y=y0+vy*t;
                }
                else
                {
                x=X+90-d/2;
                y=Y-d;

                }
                SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);
                SDL_RenderClear(ren);

                SDL_Rect rectb = { X, Y, l, 30 };
                SDL_Rect rectb2 = { X2, Y2, l, 30 };

                SDL_Rect rectbackground = { 0, 0, w, h };
                SDL_RenderCopy(ren, texture[22], NULL, &rectbackground);


                SDL_RenderCopy(ren, texture[21], NULL, &rectb);
                if(ply2==1)
                    SDL_RenderCopy(ren, texture[20], NULL, &rectb2);

                for(int i=0;i<8;i++)
                for(int j=0;j<13;j++)
                {
                    if (brick[i][j].strg<=0) brick[i][j].exist=0;
                    if (brick[i][j].exist<=0) brick[i][j].strg=0;

                 if(lv==1)
                 {
                    //SDL_FreeWAV(wavBuffer[2]);
                 rect[i][j] = { 130+i*120, 10+j*60-shift, 100, 50 };
                 //rect[i0][j0] = { 130+i0*120, 10+j0*60-shift, 100, 50 };
                 shift-=0.01;
                 if(shift <=0) {lv=0; shift=60;}
                 }
                if(brick[i][j].exist==1)
                {
                    checkall=1;
                    x1=130+i*120; x2=130+i*120+100; y1=10+60*j; y2=10+60*j+50;
                    t+=0.05;
                    if(move==1)
                    {
                    x=x0+vx*t;
                    y=y0+vy*t;
                    }
                    else
                    {
                    x=X+90-d/2;
                    y=Y-d;
                    }
                    //v=sqrt(vx*vx+vy*vy);
                    //tta=M_PI/6;
                    //double ran=rand()%100;
                    //if(dis(x1,y1+d,x,y,2*d)&&y<=y1+1) {k=1; x0=x-0.05*vx; y0=y-0.05*vy; t=0; rotate(vx,vy,ran*M_PI_2/100); cout<<vx<<endl<<vy;}
                    if(check(x1,x2,y1,y2,x+d/2,y) || check(x1,x2,y1,y2,x+d/2+10,y) || check(x1,x2,y1,y2,x+d/2-10,y))
                        {
                            k=1;
                            if(dis(x1,y1+50,x+d/2,y+d/2,c))
                            corn3=1;
                            else if(dis(x1+100,y1+50,x+d/2,y+d/2,c))
                            corn4=1;
                            else
                            vy=-vy;
                            y0=max(y1,y2); x0=x-0.05*vx; t=0;
                        }
                    else if(check(x1,x2,y1,y2,x+d/2,y+d) || check(x1,x2,y1,y2,x+d/2+10,y+d) || check(x1,x2,y1,y2,x+d/2-10,y+d))
                        {
                            k=1;
                            if(dis(x1,y1,x+d/2,y+d/2,c))
                            corn1=1;
                            else if(dis(x1+100,y1,x+d/2,y+d/2,c))
                            corn2=1;
                            else
                            vy=-vy;
                            y0=min(y1,y2)-d; x0=x-0.05*vx; t=0;
                        }
                    else if(check(x1,x2,y1,y2,x,y+d/2) || check(x1,x2,y1,y2,x,y+d/2+10) || check(x1,x2,y1,y2,x,y+d/2-10))
                        {
                            k=1;
                            if(dis(x1+100,y1,x+d/2,y+d/2,c))
                            corn2=1;
                            else if(dis(x1+100,y1+50,x+d/2,y+d/2,c))
                            corn4=1;
                            else
                            vx=-vx;
                            x0=max(x1,x2); y0=y-0.05*vy; t=0;
                        }
                    else if(check(x1,x2,y1,y2,x+d,y+d/2) || check(x1,x2,y1,y2,x+d,y+d/2+10) || check(x1,x2,y1,y2,x+d,y+d/2-10))
                        {
                            k=1;
                            if(dis(x1,y1,x+d/2,y+d/2,c))
                            corn1=1;
                            else if(dis(x1,y1+50,x+d/2,y+d/2,c))
                            corn3=1;
                            else
                            vx=-vx;
                            x0=min(x1,x2)-d; y0=y-0.05*vy; t=0;
                        }
                    else t-=0.05;
                        if(corn1==1) {ref(vx,vy,3*M_PI_4); corn1=0;}
                        else if(corn2==1) {ref(vx,vy,M_PI_4); corn2=0;}
                        else if(corn3==1) {ref(vx,vy,-3*M_PI_4); corn3=0;}
                        else if(corn4==1) {ref(vx,vy,-M_PI_4); corn4=0;}

                        if(rocket==1)
                        if(check(x1,x2,y1,y2,xr+d2,yr) || check(x1,x2,y1,y2,xr+d2/2,yr) || check(x1,x2,y1,y2,xr,yr))
                        {
                            rocket=0;
                            brick[i-1][j-1].strg=0;
                            brick[i-1][j].strg=0;
                            brick[i-1][j+1].strg=0;
                            brick[i][j-1].strg=0;
                            brick[i][j].strg=0;
                            brick[i][j+1].strg=0;
                            brick[i+1][j-1].strg=0;
                            brick[i+1][j].strg=0;
                            brick[i+1][j+1].strg=0;

                            brick[i-1][j-1].exist=0;
                            brick[i-1][j].exist=0;
                            brick[i-1][j+1].exist=0;
                            brick[i][j-1].exist=0;
                            brick[i][j].exist=0;
                            brick[i][j+1].exist=0;
                            brick[i+1][j-1].exist=0;
                            brick[i+1][j].exist=0;
                            brick[i+1][j+1].exist=0;


                            tb=0;
                            xb=130+i*120+50;
                            yb=10+60*j+25;
                            xr=0;
                            yr=0;
                            mover=0;

                        }
                    if(k==1)
                    {

                        if(lv==0){SDL_QueueAudio(deviceId[2], wavBuffer[2], wavLength[2]);
                        SDL_PauseAudioDevice(deviceId[2], 0);}
                        temp=ball.dmg;
                        if(dif==3)
                        {
                        ball.dmg-=brick[i][j].strg;
                        brick[i][j].strg-=temp;
                        }
                        else
                        {
                        ball.dmg--;
                        brick[i][j].strg-=temp;
                        }
                        if(brick[i][j].strg<=0) broken++;
                        k=0;
                        i0=i;
                        j0=j;
                        T1=50;

                        if(brick[i][j].type==1)
                        {
                            brick[i-1][j-1].strg=0;
                            brick[i-1][j].strg=0;
                            brick[i-1][j+1].strg=0;
                            brick[i][j-1].strg=0;
                            brick[i][j].strg=0;
                            brick[i][j+1].strg=0;
                            brick[i+1][j-1].strg=0;
                            brick[i+1][j].strg=0;
                            brick[i+1][j+1].strg=0;
                            tb=0;
                            xb=130+i*120+50;
                            yb=10+60*j+25;



                        }
                        else if(brick[i][j].type==2)
                        {
                            brick[i][j].strg=0;
                          live++;
                          txt=1;
                          SDL_QueueAudio(deviceId[6], wavBuffer[6], wavLength[6]);
                          SDL_PauseAudioDevice(deviceId[6], 0);
                        }
                        else if(brick[i][j].type==3)
                            rocket=1;
                        else if(brick[i][j].type==4);
                        else if(brick[i][j].type==5);
                        else if(brick[i][j].type==6);
                    }
                        if(brick[i][j].strg<=0)
                        {

                            brick[i][j].strg=0;
                            brick[i][j].exist=0;
                        }
                        t1=brick[i][j].strg;
                        for(;;)
                        {
                        if(t1>10)
                        t1-=10;
                        else
                        break;
                        }

                        //cout<<t1<<endl;
                    if(brick[i][j].strg>0&&(i0!=i||j0!=j))
                    {
                        if(brick[i][j].type==1)
                           SDL_RenderCopy(ren, texture[11], NULL, &rect[i][j]);
                        else if(brick[i][j].type==2)
                            SDL_RenderCopy(ren, texture[12], NULL, &rect[i][j]);
                        else if(brick[i][j].type==3)
                            SDL_RenderCopy(ren, texture[14], NULL, &rect[i][j]);
                        else if(brick[i][j].type==4)
                            SDL_RenderCopy(ren, texture[t1], NULL, &rect[i][j]);
                        else if(brick[i][j].type==5)
                            SDL_RenderCopy(ren, texture[t1], NULL, &rect[i][j]);
                        else if(brick[i][j].type==6)
                            SDL_RenderCopy(ren, texture[t1], NULL, &rect[i][j]);
                        else if(brick[i][j].type==0)
                            SDL_RenderCopy(ren, texture[t1], NULL, &rect[i][j]);
                        k=0;
                    }
          //          if(brick[i][j].exist==1&&(i0!=i||j0!=j))
            //    SDL_RenderCopy(ren, texture[2*t1-1], NULL, &rect[i][j]);
                    if(T1>=0&&i0==i&&j0==j)
                    {
                        SDL_RenderCopy(ren, texture[17], NULL, &rect[i][j]);
                        k=0;
                    }
                 }


                }
                if(checkall>0);
                else ball.dmg=0;
                checkall=0;


                SDL_Delay(10);
                if(x<=0||x>=w-d) {x0=x; y0=y; t=0; vx=-vx;
                        SDL_QueueAudio(deviceId[3], wavBuffer[3], wavLength[3]);
                        SDL_PauseAudioDevice(deviceId[3], 0);}
                if(y<=0) {x0=x; y0=y; t=0; vy=-vy;
                        SDL_QueueAudio(deviceId[3], wavBuffer[3], wavLength[3]);
                        SDL_PauseAudioDevice(deviceId[3], 0);}
                if(k2==1) S=-1;
                if(k1==1) S=1;
                if((k1==1&&k2==1)||(k1==0&&k2==0)) S=0;
                if(k4==1) S2=-1;
                if(k3==1) S2=1;
                if((k3==1&&k4==1)||(k3==0&&k4==0)) S2=0;


                 //x1=X; x2=X+120; y1=Y; y2=Y+60;
                   // t+=0.05;
                    if(move==1)
                    {
                    x=x0+vx*t;
                    y=y0+vy*t;
                    }
                    else
                    {
                    x=X+90-d/2;
                    y=Y-d;
                    }
                    x1=X; x2=X+l; y1=Y; y2=Y+30;
                    t+=0.05;
                    if(check(x1,x2,y1,y2,x+d/2,y) || check(x1,x2,y1,y2,x+d/2+10,y) || check(x1,x2,y1,y2,x+d/2-10,y))
                        {kb=1; x0=x-0.05*vx; y0=max(y1,y2); t=0;
                        if(dis(x1,y1+30,x+d/2,y+d/2,c1)) corn3b=1;
                        else if(dis(x1+l,y1+30,x+d/2,y+d/2,c1)) corn3b=1;
                        else{vy=-vy; vx=vx+S*abs(2*mu*vy);}
                        }
                    else if(check(x1,x2,y1,y2,x+d/2,y+d) || check(x1,x2,y1,y2,x+d/2+10,y+d) || check(x1,x2,y1,y2,x+d/2-10,y+d))
                        {kb=1; x0=x-0.05*vx; y0=min(y1,y2)-d; t=0;
                        if(dis(x1,y1,x+d/2,y+d/2,c1)) corn1b=1;
                        else if(dis(x1+l,y1,x+d/2,y+d/2,c1)) corn2b=1;
                        else{vy=-vy; vx=vx+S*abs(2*mu*vy);}
                        }
                    else if(check(x1,x2,y1,y2,x,y+d/2) || check(x1,x2,y1,y2,x,y+d/2+10) || check(x1,x2,y1,y2,x,y+d/2-10))
                        {kb=1; x0=max(x1,x2); y0=y-0.05*vy; t=0;
                        if(dis(x1+l,y1,x+d/2,y+d/2,c1)) corn2b=1;
                        else if(dis(x1+l,y1+30,x+d/2,y+d/2,c1)) corn4b=1;
                        else {vx=-vx;}
                        }
                    else if(check(x1,x2,y1,y2,x+d,y+d/2) || check(x1,x2,y1,y2,x+d,y+d/2+10) || check(x1,x2,y1,y2,x+d,y+d/2-10))
                        {kb=1; x0=min(x1,x2)-d; y0=y-0.05*vy; t=0;
                        if(dis(x1,y1,x+d/2,y+d/2,c1)) corn1b=1;
                        else if(dis(x1,y1+30,x+d/2,y+d/2,c1)) corn3b=1;
                        else {vx=-vx;}
                        }
                    else t-=0.05;
                    v=sqrt(vx*vx+vy*vy);
                    if(corn1b==1) {vx=-v/sqrt(2); vy=-v/sqrt(2);  corn1b=0;}
                    else if(corn2b==1) {vx=v/sqrt(2); vy=-v/sqrt(2); corn2b=0;}
                   // else if(corn3b==1) {ref(vx,vy,-3*M_PI_4); corn3b=0;}
                    //else if(corn4b==1) {ref(vx,vy,-M_PI_4); corn4b=0;}
                    if(ply2==1)
                    {
                        x1=X2; x2=X2+l; y1=Y2; y2=Y2+30;
                    t+=0.05;
                    if(check(x1,x2,y1,y2,x+d/2,y) || check(x1,x2,y1,y2,x+d/2+10,y) || check(x1,x2,y1,y2,x+d/2-10,y))
                        {kb=1; x0=x-0.05*vx; y0=max(y1,y2); t=0;
                        if(dis(x1,y1+30,x+d/2,y+d/2,c1)) corn3b=1;
                        else if(dis(x1+l,y1+30,x+d/2,y+d/2,c1)) corn3b=1;
                        else{vy=-vy; vx=vx+S2*abs(2*mu*vy);}
                        }
                    else if(check(x1,x2,y1,y2,x+d/2,y+d) || check(x1,x2,y1,y2,x+d/2+10,y+d) || check(x1,x2,y1,y2,x+d/2-10,y+d))
                        { x0=x-0.05*vx; y0=min(y1,y2)-d; t=0;
                        if(dis(x1,y1,x+d/2,y+d/2,c1)) corn1b=1;
                        else if(dis(x1+l,y1,x+d/2,y+d/2,c1)) corn2b=1;
                        else{vy=-vy; vx=vx+S2*abs(2*mu*vy);}
                        }
                    else if(check(x1,x2,y1,y2,x,y+d/2) || check(x1,x2,y1,y2,x,y+d/2+10) || check(x1,x2,y1,y2,x,y+d/2-10))
                        { x0=max(x1,x2); y0=y-0.05*vy; t=0;
                        if(dis(x1+l,y1,x+d/2,y+d/2,c1)) corn2b=1;
                        else if(dis(x1+l,y1+30,x+d/2,y+d/2,c1)) corn4b=1;
                        else {vx=-vx;}
                        }
                    else if(check(x1,x2,y1,y2,x+d,y+d/2) || check(x1,x2,y1,y2,x+d,y+d/2+10) || check(x1,x2,y1,y2,x+d,y+d/2-10))
                        { x0=min(x1,x2)-d; y0=y-0.05*vy; t=0;
                        if(dis(x1,y1,x+d/2,y+d/2,c1)) corn1b=1;
                        else if(dis(x1,y1+30,x+d/2,y+d/2,c1)) corn3b=1;
                        else {vx=-vx;}
                        }
                    else t-=0.05;
                    v=sqrt(vx*vx+vy*vy);
                    if(corn1b==1) {vx=-v/sqrt(2); vy=-v/sqrt(2);  corn1b=0;}
                    else if(corn2b==1) {vx=v/sqrt(2); vy=-v/sqrt(2); corn2b=0;}
                    }

                    if(kb==1)
                    {
                        SDL_QueueAudio(deviceId[4], wavBuffer[4], wavLength[4]);
                        SDL_PauseAudioDevice(deviceId[4], 0);
                        kb=0;
                    }

                if(pause==0&&live>0) t+=0.1;
                if(T1>=0) { T1-=5;}
                /*if(T1<=0)
                {
                    SDL_CloseAudioDevice(deviceId[2]);
                    SDL_FreeWAV(wavBuffer[2]);
                }*/
                if(T1<=0) {j0=-1; i0=-1;}
                if(vy==0) vy=-2;
                if(pause==0) {X+=S*10; X2+=S2*10;}
                if(X>w-l) X=w-l;
                if(X<0) X=0;
                if(X2>w-l) X2=w-l;
                if(X2<0) X2=0;

                T+=1;
                Tp+=1;


                for(int i=0;i<8;i++)
                {
                    if(brick[i][11].strg>0||brick[i][11].exist==1) over=1;
                }
                if(live<=0||over==1)
                    {
                        SDL_Rect end={w/2-400,h/2-400,800,800};
                        SDL_RenderCopy(ren, textureoption[13], NULL, &end);
                        //SDL_QueueAudio(deviceId[8], wavBuffer[8], wavLength[8]);
                        //SDL_PauseAudioDevice(deviceId[8], 0);
                        ball.dmg=0;
                    }

                SDL_Rect dstrect = { x, y, d, d };
                if(ball.dmg>0&&Tp>=100&&live>0)
                SDL_RenderCopy(ren, texture[0], NULL, &dstrect);
                //cout<<x<<endl;
                if(rocket==1)
                {
                    if(yr<=-d2) {rocket=0; mover=0;}
                    if(mover==0)
                    {
                    xr=X+l/2-d2/2;
                    yr=Y-d2;

                    }
                    else if(mover==1)
                    {
                     xr=x0r;
                     yr-=5;
                    }
                   SDL_Rect rectrocket={xr,yr,d2,d2};
                   SDL_RenderCopy(ren, texturerocket, NULL, &rectrocket);
                }
                if(tb<3)
                {
                    if(tb==0)
                    {
                        SDL_QueueAudio(deviceId[5], wavBuffer[5], wavLength[5]);
                        SDL_PauseAudioDevice(deviceId[5], 0);
                    }
                    rb=150*(1-exp(-3*tb/4))+20;
                   //rb=100;
                    SDL_Rect bmb = {xb-rb,yb-rb,2*rb,2*rb};
                    SDL_RenderCopy(ren, texture[15], NULL, &bmb);

                }
                if(tb<=3)   tb+=0.15;


SDL_Color color = { 0,255, 255 };
if(txt==1)
{
level="level:"+inttost(lvl);
score="score:"+inttost(scor);
lives="lives:"+inttost(live);
surface1 = TTF_RenderText_Solid(font, level.c_str() , color);
surface = TTF_RenderText_Solid(font, score.c_str() , color);
surface2 = TTF_RenderText_Solid(font, lives.c_str() , color);
textlevel = SDL_CreateTextureFromSurface(ren, surface1);
textscore = SDL_CreateTextureFromSurface(ren, surface);
textlives = SDL_CreateTextureFromSurface(ren, surface2);
SDL_QueryTexture(textlevel, NULL, NULL, &texW1, &texH1);
SDL_QueryTexture(textscore, NULL, NULL, &texW, &texH);
SDL_QueryTexture(textlives, NULL, NULL, &texW2, &texH2);
rectlevel = { w/2-texW1/2-360, h-50, texW1, texH1 };
rectscore = { w/2-texW/2, h-50, texW, texH };
rectlives = { w/2-texW2/2+360, h-50, texW2, texH2 };
txt=0;
}


SDL_RenderCopy(ren, textlives, NULL, &rectlives);
SDL_RenderCopy(ren, textscore, NULL, &rectscore);
SDL_RenderCopy(ren, textlevel, NULL, &rectlevel);


                if(pause==1)
                {
                SDL_Rect rectpause={w/2-300,h/2-350,600,700};
                SDL_RenderCopy(ren, textureoption[12], NULL, &rectpause);
                SDL_Rect rect1={w/2-160,h/2-40-120,320,80},rect2={w/2-160,h/2-40,320,80},rect3={w/2-160,h/2-40+120,320,80};
                             if(select!=1)
                              SDL_RenderCopy(ren, textureoption[14], NULL, &rect1);
                             else
                             SDL_RenderCopy(ren, textureoption[15], NULL, &rect1);
                             if(select!=2)
                             SDL_RenderCopy(ren, textureoption[16], NULL, &rect2);
                             else
                             SDL_RenderCopy(ren, textureoption[17], NULL, &rect2);
                             if(select!=3)
                             SDL_RenderCopy(ren, textureoption[18], NULL, &rect3);
                             else
                             SDL_RenderCopy(ren, textureoption[19], NULL, &rect3);
                             SDL_Delay(100);
                }

        SDL_RenderPresent(ren);
        if(over==1||live<=0)
        {
            SDL_FreeWAV(wavBuffer[7]);
        }



   if( SDL_PollEvent( event ) )
        if(event->type == SDL_KEYUP)
        {
            switch(event->key.keysym.sym)
            {
                case SDLK_d: k1=0; break;
                case SDLK_a: k2=0; break;
                case SDLK_RIGHT: k3=0; break;
                case SDLK_LEFT: k4=0; break;
            }
        }


        if( event->type == SDL_KEYDOWN )
        {
        switch(event->key.keysym.sym)
        {
        case SDLK_DELETE:
        cheat=1;
        break;
        case SDLK_UP:
        if(select==0||select==1) select=3;
        else select--;
        break;
        case SDLK_DOWN:
        if(select==0||select==3) select=1;
        else select++;
        break;
        case SDLK_RIGHT:
        //if(ply2==1)
            k3=1;
        break;
        case SDLK_LEFT:
        //if(ply2==1)
            k4=1;
        break;
        case SDLK_d:
        k1=1;
        break;

        case SDLK_a:
        k2=1;
        break;

        case SDLK_SPACE:
            if(game==1&&pause==0)
            {
        if(rocket==1)
        {
            SDL_QueueAudio(deviceId[7], wavBuffer[7], wavLength[7]);
                            SDL_PauseAudioDevice(deviceId[7], 0);
           mover=1;
           x0r=xr;
           y0r=yr;
        }
        else if(Tp>=100&&move==0)
        {
        move=1;
        t=0;
        x0=x;
        y0=y;
        vx=0;
        }

            }
        else if(pause==1)
        {
            if(select==2)
            {pause2=1; game=0; save=1;}
        else if(select==1)
            {pause=0; select=0;}
        else if(select==3)
        {game=0; select=0; menu=1; state=1; pause=1; name="";}
        }
        break;
        case SDLK_ESCAPE:
            if(pause==0)
            {
        pause=1;
        select=0;
            }
        else{
            pause=0;
        SDL_Delay(200);
            select=0;
            }
        break;
        case SDLK_0:
            if(cheat==1)
            {
                int w;
                w=rand()%3;
                for(int i=0;i<8;i++)
                    brick[i][w].strg=0;
                    cheat=0;
            }
            break;
        case SDLK_1:
            if(cheat==1)
            {
                for(int j=0;j<3;j++)
                for(int i=0;i<8;i++)
                {
                    brick[i][j].type=1;
                    brick[i][j].strg=1;
                }
                    cheat=0;
            }
        case SDLK_2:
            if(cheat==1)
            {
                live+=10;
                //brick[i][j].type=1;
                cheat=0;
                txt=1;
                for(int j=0;j<3;j++)
                for(int i=0;i<8;i++)

                {
                    brick[i][j].type=2;
                    brick[i][j].strg=1;

                }
            }
        case SDLK_3:
            if(cheat==1)
            {
                rocket=1;
                for(int j=0;j<3;j++)
                for(int i=0;i<8;i++)
                {
                    brick[i][j].type=3;
                    brick[i][j].strg=1;
                }
                    cheat=0;
            }
        case SDLK_4:
            if(cheat==1)
            {
                for(int j=0;j<3;j++)
                for(int i=0;i<8;i++)
                {
                    brick[i][j].strg=1;
                    brick[i][j].type=4;
                }
                    cheat=0;
            }
        }
    }
        }

        }
        }
        SDL_DestroyRenderer(ren);
        SDL_Quit();
}
