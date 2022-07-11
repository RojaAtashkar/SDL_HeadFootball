#include<ctime>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include<cmath>
#include<string>
#include <sstream>
#include <stdio.h>
#include<SDL2/SDL_mixer.h>
#include<fstream>
using namespace std;
//constant  sizes
# define WIDTH 1200
# define HEIGHT 600
# define Y0 40
# define RADIOUS 55
# define player_pic 100
# define player_w 70
# define player_h 70
//different pictures
string back_ground;
string ball;
string player1;
string player2;
string shoeR;
string shoeL;
string goalR;
string goalL;
//variables
double velocity_x0=10;
double velocity_y0=-50;
int  GROUND=430;
int player_vel1=8;
int player_vel2=8;
int x0_shoeL=235;
int x0_shoeR= WIDTH-235;
int GOAL_left=2;
int GOAL_right=3;
int w_shoe=100,h_shoe=100;
int x_gR=110, x_gL=WIDTH-130;;
int w_goal=80, h_goal=250;
int y_gR=GROUND-h_goal+90;
int y_gL=GROUND-h_goal+90;
int x_scoreb=40, y_scoreb=20, w_scoreb=WIDTH-80 ,h_scoreb=60;
bool continueGame=true;
int y_shoeR=GROUND,y_shoeL=GROUND;
int x_shoeR=x0_shoeR,x_shoeL=x0_shoeL;
bool goaled=false;
double x=WIDTH/2;
double y=Y0;
bool power_R=false;
bool power_L=false;
int powerLengthgRight=290;
int powerLengthgLeft=290;
bool rightFiriz=false, leftFirix=false, invisible=false;
int firizDeltha=0,invisibleDeltha=0;
bool startGame=false;
bool jumpR=false,jumpL=false;
bool goalScoredRight=false;
bool goalScoredLeft=false;
bool paused=false, getnamed=false,home=false;;
int h_b=50,w_b=50;
//int x_h=y_scoreb+h_scoreb+10, y_h=w_b+h_b+10, x_p=y_scoreb+h_scoreb+10+w_b+10,y_p=w_b+h_b+10,x_r=y_scoreb+h_scoreb+10+2*w_b+20,y_r=w_b+h_b+10;
int x_p=WIDTH/2-w_b/2,y_p=w_b+h_b+10,x_r=x_p+w_b+10,y_r=w_b+h_b+10,x_h=x_p-10-w_b, y_h=w_b+h_b+10;
string nameR="";
string nameL="";
const int maxrow=20;
string names[maxrow];
int ties[maxrow];
int wins[maxrow];
int losts[maxrow];
int GFs[maxrow];
int GAs[maxrow];
//max power length = 290
int PowerRight, powerLeft;
unsigned int lastTime=0, currentTime,startTime;
 //define some fonts with extension 'ttf'
const char * font_address_01="IranNastaliq.ttf";
const char * font_address_02="HARLOWSI.ttf";
const char * font_address_03="MAGNETOB.ttf";
const char * font_address_04="arial.ttf";
//structures
typedef enum{
     NONE = 0,
     HORIZENTAL = 1,
     VERTICAL = 2,
     HORVER = 3
}short;
//Event
SDL_Event *e = new SDL_Event();
SDL_Event *m = new SDL_Event();
void Default();
void game (SDL_Renderer *m_renderer) ;
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height);
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian);
void help(SDL_Renderer *Renderer,double x_ball,double y_ball,int dx ,bool clicked);
void celebration(SDL_Renderer *m_renderer,int x,int y);
void write(SDL_Renderer *renderer,int x,int y,string te,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num);
void myTextRGBA(SDL_Renderer *renderer,int x,int y,const char * text,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num);
void inputText(SDL_Renderer *renderer,int x,int y,string &inputText,const char * font,int font_size,int R,int G,int B, int A);
void  menueMain(SDL_Renderer *m_renderer);
void chartMenue(SDL_Renderer *m_renderer);
void getNameMenue(SDL_Renderer *m_renderer);
void afterGameMenue(SDL_Renderer *m_renderer);
void aboutMenue(SDL_Renderer *m_renderer);
void settingMenue(SDL_Renderer *m_renderer);
void CharacterMenue(SDL_Renderer *m_renderer);
void guideMenue(SDL_Renderer *m_renderer);
void OpenFile();
void AddRecord(string name,int scored);
void SaveToFile();
void pause(SDL_Renderer *m_renderer);
void restart(SDL_Renderer *m_renderer);
void GOAL(SDL_Renderer *m_renderer,int x,int y,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num,int goal);
void textureRenderer(SDL_Renderer *m_renderer, int font_size ,double angle);
void ballDrop(SDL_Renderer *m_renderer, int font_size ,double angle, double velocity_x, double velocity,double acceleration,bool playerSide );
void TripleClone(SDL_Renderer *m_renderer,int font_size ,double angle, int velocity_x, int velocity,int acceleration,bool playerSide );//1 for R 0for L
void textureRendererTripleClone(SDL_Renderer *m_renderer, int font_size ,double angle,bool playerSide);
void ballDropTripleClone(SDL_Renderer *m_renderer,int font_size ,double angle, double velocity_x, double velocity,double acceleration,bool playerSide,bool TripleCloneSide );
void my_line(SDL_Renderer *Renderer, int x_1, int y_1, int L, double theta,int widht, int R, int G, int B );
void ballDropKichFireBall(SDL_Renderer *m_renderer,int font_size ,double angle, double velocity_x, double velocity,double acceleration,bool playerSide );
void textureRendererKichFireBall(SDL_Renderer *m_renderer, int font_size ,double angle,bool playerSide);
void textureRendererMainMenue(SDL_Renderer *m_renderer, int x_playButton,int y_playbutton,int h_playButton, int w_playButton, int h_button, int w_button);
void punch(SDL_Renderer *m_renderer,int font_size ,double angle, double velocity_x,bool playerSide );
//GROUP 50
//by roja atashkar
int main( int argc, char * argv[] )
{
     for(int x=0;x<maxrow;x++)
    {
        names[x]="-1";
    }
    OpenFile();
    TTF_Init();
    //Initialization of SDL windows
    Uint32 SDL_flags = SDL_INIT_VIDEO | SDL_INIT_TIMER ;
    Uint32 WND_flags = SDL_WINDOW_SHOWN; //SDL_WINDOW_BORDERLESS ;
    SDL_Window * m_window;
    SDL_Renderer * m_renderer;
    //Texture for loading image
    SDL_Init( SDL_flags );
    SDL_CreateWindowAndRenderer(WIDTH,HEIGHT, WND_flags, &m_window, &m_renderer );
    //Pass the focus to the drawing window
    SDL_RaiseWindow(m_window);
    //Get screen resolution
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    // Clear the window with a black background
    SDL_SetRenderDrawColor( m_renderer, 0, 0, 0, 255 );
    SDL_RenderClear( m_renderer );
     //mixer
     SDL_Init(SDL_INIT_AUDIO ||SDL_INIT_VIDEO);
     Mix_OpenAudio(41100,MIX_DEFAULT_FORMAT,2,2048);

   bool quite=false;
    //initial_setup (m_renderer);
     Default();
     menueMain(m_renderer);
     game (m_renderer);
     if(!continueGame)
     afterGameMenue(m_renderer);

    //Finalize and free resources
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
    Mix_Quit();
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
    return 0;

}
void Default()
{
     back_ground="bg1.jpg";
     ball="ball.png";
     player1="player3_L.png";
     player2="player2_R.png";
     shoeR="shoeR.png";
     shoeL="shoeL.png";
     goalL="goalright.png";
     goalR="goalleft.png";
     //1 for tripleClone, 2 for kickFireBall,3 for invisible ball,4 forPunch, 5 for thief
     powerLeft=2;
     PowerRight=3;
     srand(time(NULL));
    }
 void game (SDL_Renderer *m_renderer)
{
     //initialing ttf
    TTF_Init();
    Mix_Music *crowd=Mix_LoadMUS("crowd.mp3");
    Mix_PlayMusic(crowd,-1);
    startTime=SDL_GetTicks();
    lastTime=0;
    double acceleration_y0=3;
    double velocity=velocity_y0;
    double velocity_x=velocity_x0;
    double acceleration=acceleration_y0;
    int x_textL=x_scoreb+w_scoreb/2-103;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    bool goaled=false;
    GOAL_left=0;
    GOAL_right=0;
    int font_size = 30;
    double angle = 0.0;
    int deltha=0;
    textureRenderer(m_renderer,font_size,angle );
    //initial ball drop
     int k=1.5;
     int dy=18;
     Mix_Chunk *goalScored=Mix_LoadWAV("goaled.wav");
     Mix_PlayChannel(-1,goalScored,0);
     while(y<GROUND)
      {
           y+=dy;
           dy*=k;
           textureRenderer(m_renderer,font_size,angle );
      }
    y=GROUND;
    textureRenderer(m_renderer,font_size,angle );
    while(continueGame)
     {
         //timing
         currentTime = SDL_GetTicks()-startTime;
         if (currentTime > lastTime + 1000) {
         lastTime = currentTime;
         if(currentTime/1000>=120)
         {
             continueGame=false;
             return;
         }
         deltha++;
         if(rightFiriz || leftFirix)
         firizDeltha++;
         if(invisible)
         invisibleDeltha++;
    }
    if(invisibleDeltha>=3)
     {
             invisibleDeltha=0;
             invisible=false;
     }
    if(firizDeltha>=3)
     {
         rightFiriz=false;
         leftFirix=false;
         firizDeltha=0;
      }
    if(deltha>=5)
      {
          if(powerLengthgLeft<290)
          {
               powerLengthgLeft+=50;
               if(powerLengthgLeft>290)
               powerLengthgLeft=290;
          }
        if(powerLengthgRight<290)
          {
               powerLengthgRight+=50;
               if(powerLengthgRight>290)
               powerLengthgRight=290;
          }
         deltha=0;
     }
    SDL_PollEvent(e);
    if(e-> type==SDL_KEYDOWN )
     {
        switch(e->key.keysym.sym)
         {
            case SDLK_ESCAPE:
                return;
            case SDLK_RIGHT:
                if(!rightFiriz)
                 x_shoeR+=player_vel2;
                 break;
            case SDLK_UP:
                 if(!rightFiriz)
                 y_shoeR-=player_vel2;
                 break;
            case SDLK_DOWN:
                 if(!rightFiriz)
                 y_shoeR+=player_vel2;
                 break;
            case SDLK_LEFT:
                 if(!rightFiriz)
                x_shoeR-=player_vel2;
                break;
            case SDLK_j:
                if(!rightFiriz)
                {
                    velocity=velocity_y0;
                    double  y_shoeR0=y_shoeR,t;
                    for(t=0.1; t<=25 && y_shoeR<=y_shoeR0 ; t+=0.1)
                    {
                        y_shoeR=( 0.5*acceleration*t*t+velocity*t)+y_shoeR0;
                        velocity+=acceleration*t;
                        textureRenderer(m_renderer,font_size,angle);
                        x_shoeR-=velocity_x;
                    }
                }
                break;
            case SDLK_e:
                if(!leftFirix)
                {
                    int  velocity_j=velocity_y0;
                    double  y_shoeL0=y_shoeL,t;
                    for(t=0.1; t<=25 && y_shoeL<=y_shoeL0 ; t+=0.1)
                    {
                        {
                            y_shoeL=( 0.5*acceleration*t*t+velocity_j*t)+y_shoeL0;
                            velocity_j+=acceleration*t;
                            textureRenderer(m_renderer,font_size,angle);
                        }
                        x_shoeL+=velocity_x;
                    }
                }
                break;
            case SDLK_z:
                if(!leftFirix)
                jumpL=true;
                break;
            case SDLK_d:
                if(!leftFirix)
                x_shoeL+=player_vel1;
                break;
            case SDLK_a:
                if(!leftFirix)
                x_shoeL-=player_vel1;
                break;
            case SDLK_w:
                if(!leftFirix)
                y_shoeL-=player_vel1;
                break;
            case SDLK_s:
                if(!leftFirix)
                y_shoeL+=player_vel1;
                break;
            case SDLK_p:
                if(!rightFiriz)
                    {
                       if(powerLengthgRight==290)
                            power_R=true;
                    }
                    break;
            case SDLK_q:
                if(!leftFirix)
                    {
                        if(powerLengthgLeft==290)
                            power_L=true;
                   }
                break;
         }
    }
    int x_e,y_e;
    if(e->type==SDL_MOUSEBUTTONDOWN)
     {
        x_e=e->motion.x;
        y_e=e->motion.y;
        if(x_e>=x_h && x_e<=x_h+w_b &&y_e<=y_h+h_b && y_e>=y_h &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
         {
            Mix_Chunk *click=Mix_LoadWAV("click.wav");
            Mix_PlayChannel(-1,click,0);
            nameL="";
            nameR="";
            getnamed=false;
            GOAL_left=0;
            GOAL_left=0;
            home=true;
            powerLengthgRight=10;
            powerLengthgRight=10;
            continueGame=false;
            startGame=false;
            break;
         }

         if(x_e>=x_p && x_e<=x_p+w_b &&y_e<=y_p+h_b && y_e>=y_p &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
          {
           Mix_Chunk *click=Mix_LoadWAV("click.wav");
           Mix_PlayChannel(-1,click,0);
           Mix_Pause(Mix_PlayMusic(crowd,-1));
           paused=true;
           pause(m_renderer);
           Mix_Resume(Mix_PlayMusic(crowd,-1));
          }
        if(x_e>=x_r && x_e<=x_r+w_b &&y_e<=y_r+h_b && y_e>=y_r &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
          {
        Mix_Chunk *click=Mix_LoadWAV("click.wav");
        Mix_PlayChannel(-1,click,0);
        restart(m_renderer);
          }
     }
    textureRenderer(m_renderer,font_size,angle );
        //punch
    if(powerLeft==4 && power_L)
    {
        velocity_x=4*velocity_x0;
        power_L=false;
        powerLengthgLeft=10;
        punch(m_renderer,font_size,angle,velocity_x,0);
    }
     if(PowerRight==4 && power_R)
    {
        velocity_x=4*velocity_x0;
        power_R=false;
        powerLengthgRight=10;
        punch(m_renderer,font_size,angle,velocity_x,1);
    }
    //triple clone
    if(PowerRight==1 && power_R)
    {
    power_R=false;
    powerLengthgRight=10;
    TripleClone(m_renderer,font_size ,angle, velocity_x,velocity,acceleration,1);
    }
    if(powerLeft==1 && power_L)
    {
    power_L=false;
    powerLengthgLeft=10;
    TripleClone(m_renderer,font_size ,angle, velocity_x,velocity,acceleration,0 );
    }
     //Kick Fire Ball power
   if(powerLeft==2 && x-x_shoeL-w_shoe<150 &&x-x_shoeL>0&&y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe && power_L)
   {
    velocity_x=velocity_x0;
    velocity=0;
    power_L=false;
    powerLengthgLeft=10;
    ballDropKichFireBall(m_renderer,font_size ,angle,4*velocity_x,velocity, acceleration,0 );
   }
    if(PowerRight==2 && x_shoeR-x-RADIOUS<150 &&x_shoeR-x>0&&y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe &&power_R)
   {
    velocity_x=velocity_x0;
    velocity=0;
    power_R=false;
    powerLengthgRight=10;
    ballDropKichFireBall(m_renderer,font_size ,angle,4*velocity_x,velocity,acceleration,1 );
   }
    //right player simple drop
    if((x_shoeR-x)<=RADIOUS && (x_shoeR-x)>=RADIOUS-10&&y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe)
    {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        if(PowerRight==3 &&power_R)
         {
            power_R=false;
            powerLengthgRight=10;
            invisible=true;
         }
        velocity_x=velocity_x0;
        velocity=velocity_y0;
        ballDrop(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,1 );//1 for R 0 for L;
    }
    //left player simple ball drop
    if((x-x_shoeL)<=w_shoe&& x-x_shoeL>=RADIOUS-5&& y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe)
     {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        if(powerLeft==3 &&power_L)
         {
            power_L=false;
            powerLengthgLeft=10;
            invisible=true;
         }
        velocity_x=velocity_x0;
        velocity=velocity_y0;
        ballDrop(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,0 );//1 for R 0 for L
     }
     //right player head drop invisible ball
     if((x_shoeR+50-x)<=RADIOUS && (x_shoeR+50-x)>=RADIOUS-10&&y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe )
    {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        if(PowerRight==3 &&power_R)
           {
            power_R=false;
            powerLengthgRight=10;
            invisible=true;
            velocity_x=velocity_x0;
            velocity=4*velocity_y0;
            ballDrop(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,1 );
           }
    }
   //left player head drop invisible ball
   if((x- x_shoeR-50)<=w_shoe&& x- x_shoeR-50>=RADIOUS-5&&y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe)
    {
     Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
     Mix_PlayChannel(-1,ballkick,0);
     if(powerLeft==3 &&power_L)
      {
        power_L=false;
        powerLengthgLeft=10;
        invisible=true;
        velocity_x=velocity_x0;
        velocity=4*velocity_y0;
        ballDrop(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,0 );//1 for R 0 for L
      }
    }
    //left player upward ball drop
    if((x-x_shoeL)<=w_shoe-RADIOUS&& x-x_shoeL>=0&& y_shoeL-y<=RADIOUS &&y_shoeL-y>=RADIOUS/2 )
    {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        if(powerLeft==3 &&power_L)
         {
              power_L=false;
              powerLengthgLeft=10;
              invisible=true;
         }
        velocity_x=velocity_x0;
        velocity=4*velocity_y0;
        ballDrop(m_renderer,font_size ,angle,velocity_x,velocity,0.75* acceleration,0 );//1 for R 0 for L
    }
    //right player upward ball drop
    if((x_shoeR-x)<=w_shoe-RADIOUS && (x_shoeR-x)>=0 &&y_shoeR-y<=RADIOUS && y_shoeR-y>=RADIOUS/2)
     {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        if(PowerRight==3 &&power_R)
         {
            power_R=false;
            powerLengthgRight=10;
            invisible=true;
         }
        velocity_x=velocity_x0;
        velocity=4*velocity_y0;
        ballDrop(m_renderer,font_size ,angle,velocity_x,velocity,0.75*acceleration,1 );//1 for R 0 for L
     }
    //GOAL!!
    if( x_gL-x<=w_goal &&x_gL-x>=-RADIOUS/2 &&y>y_gL &&y<y_gL+h_goal)
        {
            GOAL_left++;
            GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,255,255,255,255,angle,NONE,GOAL_left);
            SDL_RenderPresent(m_renderer);
            goaled=true;
            goalScoredRight=true;
        }
    if( x-x_gR<=w_goal &&x-x_gR>=RADIOUS/2 &&y>y_gL &&!goaled&&y<y_gL+h_goal)
        {
           GOAL_right++;
           GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,255,255,255,255,angle,NONE,GOAL_right);
           SDL_RenderPresent(m_renderer);
            goaled=true;
            goalScoredLeft=true;
        }
     // right player backward drop
     if((-x_shoeR+x)<=RADIOUS && (-x_shoeR+x)>=RADIOUS-5&&y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe )
      {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        velocity_x=velocity_x0;
        velocity=0.5*velocity_y0;
        ballDrop(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,0 );
      }
    //left player backward drop
    if((-x+x_shoeL)<=w_shoe&& -x+x_shoeL>=RADIOUS-5&&y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe)
     {
         Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
         Mix_PlayChannel(-1,ballkick,0);
         velocity_x=velocity_x0;
         velocity=0.5*velocity_y0;
         ballDrop(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,1 );//1 for R 0 for L
     }
    if(goaled)
     {
        Mix_Chunk *goalscored=Mix_LoadWAV("goalscored.wav");
        Mix_PlayChannel(-1,goalscored,0);
        y=Y0;
        x=WIDTH/2;
        int  k=1.5;
        int dy=18;
        y_shoeR=GROUND,y_shoeL=GROUND;
        x_shoeR=x0_shoeR,x_shoeL=x0_shoeL;
        while(y<GROUND)
         {
            y+=dy;
            dy*=k;
            textureRenderer(m_renderer,font_size,angle );
         }
        int current,last=SDL_GetTicks(),d=0;
        while(d<3)
          {
           current = SDL_GetTicks();
           if (current > last + 1000)
            {
               last=current;
               d++;
            }
            textureRenderer(m_renderer,font_size,angle);
          }
        Mix_Chunk *goalScored=Mix_LoadWAV("goaled.wav");
        Mix_PlayChannel(-1,goalScored,0);
        if(GOAL_left==4&&GOAL_right==4)
            continueGame=false;
        if(GOAL_right==5||GOAL_left==5)
            continueGame=false;
        goaled=false;
    }

  }
     Mix_FreeMusic(crowd);
     if(home)
     {
         home=false;
         Default();
         menueMain(m_renderer);
        game(m_renderer);
         }
 }
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian)
{
    SDL_Rect rectangle ;
    rectangle.x = x;
    rectangle.y = y;
    rectangle.w = w;
    rectangle.h = h;
    SDL_SetRenderDrawColor(Renderer, R, G, B, 255);
    if(fill_boolian)
    SDL_RenderFillRect(Renderer, &rectangle);
    SDL_RenderDrawRect(Renderer, &rectangle);
    //SDL_RenderPresent(Renderer);
}
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height)
{
    int n = addressOfImage.length();
    char char_array[n+1];
    strcpy(char_array, addressOfImage.c_str());
    SDL_Texture *myTexture;
    myTexture = IMG_LoadTexture( m_renderer, char_array);
    int w1, h1;
    SDL_QueryTexture(myTexture, NULL, NULL, &w1, &h1);
    SDL_Rect texr1;
    texr1.x = xp;
    texr1.y = yp;
    texr1.w = width;
    texr1.h = height;
    SDL_RenderCopy( m_renderer, myTexture, NULL, &texr1);
    SDL_DestroyTexture(myTexture);
}
void write(SDL_Renderer *renderer,int x,int y,string te,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num)
{
    const char* text=te.c_str();
    SDL_Color text_color = { R, G, B, A};
    int mWidth = 0;
	int mHeight = 0;
    SDL_Rect* clip = NULL;
    TTF_Font *gFont = NULL;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip;
    switch(flip_num)
     {
        case 0:
            flip = SDL_FLIP_NONE;
            break;
        case 1:
            flip = SDL_FLIP_HORIZONTAL;
            break;
        case 2:
            flip = SDL_FLIP_VERTICAL;
            break;
        case 3:
            flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
            break;
        default:
            flip = SDL_FLIP_NONE;
     }
    SDL_Texture* mTexture = NULL;
    gFont = TTF_OpenFont(font, font_size);
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text, text_color);
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = {x, y , mWidth, mHeight};
    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
    SDL_DestroyTexture(mTexture);
}
void my_line(SDL_Renderer *Renderer, int x_1, int y_1, int L, double theta,int widht, int R, int G, int B )
{
    int x_2 = x_1 + L*cos(theta);
    int y_2 = y_1 - L*sin(theta);
    thickLineRGBA(Renderer,x_1,y_1,x_2,y_2,widht,R,G,B,255);
}
void myTextRGBA(SDL_Renderer *renderer,int x,int y,const char * text,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num)
{
    SDL_Color text_color = { R, G, B, A};
    int mWidth = 0;
	int mHeight = 0;
    SDL_Rect* clip = NULL;
    TTF_Font *gFont = NULL;
    SDL_Point* center = NULL;
    SDL_RendererFlip flip;
    switch(flip_num)
     {
        case 0:
            flip = SDL_FLIP_NONE;
            break;
        case 1:
            flip = SDL_FLIP_HORIZONTAL;
            break;
        case 2:
            flip = SDL_FLIP_VERTICAL;
            break;
        case 3:
            flip = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
            break;
        default:
            flip = SDL_FLIP_NONE;
     }
    SDL_Texture* mTexture = NULL;
    gFont = TTF_OpenFont(font, font_size);
    SDL_Surface* textSurface = TTF_RenderText_Solid(gFont, text, text_color);
    mWidth = textSurface->w;
    mHeight = textSurface->h;
    mTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_FreeSurface(textSurface);
    SDL_Rect renderQuad = {x, y , mWidth, mHeight};
    SDL_RenderCopyEx(renderer, mTexture, clip, &renderQuad, angle, center, flip);
    SDL_DestroyTexture(mTexture);
}
void inputText(SDL_Renderer *m_renderer,int x,int y,string &inputText,const char * font,int font_size,int R,int G,int B, int A)
{
bool flag=false;
SDL_Event ev ;
SDL_StartTextInput();
while( !flag )
{
//The render text flag
bool renderText = false;
//Handle events on queue
while( SDL_PollEvent( &ev ) != 0)
{
    //User requests quit
    if( (ev.type==SDL_MOUSEBUTTONDOWN && ev.button.button==SDL_BUTTON_RIGHT) )
    {
        flag=true;
        cout<<"n";
    }
    //Special key input
    else if( ev.type == SDL_KEYDOWN )
    {
        //Handle backspace
        if( ev.key.keysym.sym == SDLK_BACKSPACE && inputText.length() > 0 )
        {
            //lop off character
          inputText=inputText.substr(0,inputText.length()-1);
          //SDL_RenderClear(m_renderer);
          write(m_renderer,x,y,inputText,font,30,0,0,0,255,0,NONE);
          SDL_RenderPresent(m_renderer);
          renderText = true;
        }
        //Handle copy
        if( ev.key.keysym.sym == SDLK_c && SDL_GetModState() & KMOD_CTRL )
        {
            SDL_SetClipboardText( inputText.c_str() );
        }
        //Handle paste
        else if( ev.key.keysym.sym == SDLK_v && SDL_GetModState() & KMOD_CTRL )
        {
            inputText = SDL_GetClipboardText();
            renderText = true;
        }
    }
    //Special text input event
    else if( ev.type == SDL_TEXTINPUT )
    {
        //Not copy or pasting
        if( !( SDL_GetModState() & KMOD_CTRL && ( ev.text.text[ 0 ] == 'c' || ev.text.text[ 0 ] == 'C' || ev.text.text[ 0 ] == 'v' || ev.text.text[ 0 ] == 'V' ) ) )
        {
            //Append character
            inputText += ev.text.text;
            renderText = true;
        }
    }
}
    if( renderText )
     {
        //Text is not empty
        if( inputText != "" )
        {
            //Render new text
               write(m_renderer,x,y,inputText,font,30,0,0,0,255,0,NONE);
               SDL_RenderPresent(m_renderer);
        }
        //Text is empty
        else
        {
               write(m_renderer,x,y," ",font,30,0,0,0,255,0,NONE);
               SDL_RenderPresent(m_renderer);
        }
     }

}
 SDL_StopTextInput();
}
void  menueMain(SDL_Renderer *m_renderer)
{
    TTF_Init();
    Mix_Music *menueSound=Mix_LoadMUS("Field.mp3");
    Mix_PlayMusic(menueSound,-1);
    double h_playButton=100,w_playButton=230,h_button=100,w_button=230;
    double x_playButton=WIDTH/2-w_playButton/2,y_playbutton=80;
    double x_set=WIDTH/2-w_playButton/2,y_set=y_playbutton+h_playButton+20;
    double x_a=WIDTH/2-w_playButton/2,y_a=y_set+h_playButton+20;
    double x_e=WIDTH/2-w_playButton/2,y_e=y_a+h_playButton+20;
    int x_c=WIDTH-70-50,y_c=100;
    int x_g=15,y_g=15;
    bool play=true, rightname=true,leftname=false, gotnamed=false;
    int x_m,y_m;
    string stadium="stadium.jpg";
    string playButton="playButton.png";
    string settingButton="settingButton.png";
    string aboutButton="aboutButton.png";
    string exitButton="exitButton.png";
    string cup="cup.png";
    string guide="guide.png";
    while(!startGame)
    {
        texture(m_renderer,0,0,stadium,WIDTH,HEIGHT);
        texture(m_renderer,x_playButton,y_playbutton,playButton,w_playButton,h_playButton);
        texture(m_renderer,x_set,y_set,settingButton,w_button,h_button);
        texture(m_renderer,x_a,y_a,aboutButton,w_button,h_button);
        texture(m_renderer,x_e,y_e,exitButton,w_button,h_button);
        texture(m_renderer,x_g,y_g,guide,w_b,h_b);
        SDL_RenderPresent(m_renderer);
        SDL_PollEvent(m);
        if(m->type==SDL_MOUSEBUTTONDOWN)
         {
            x_m=m->motion.x;
            y_m=m->motion.y;
            texture(m_renderer,0,0,stadium,WIDTH,HEIGHT);
            texture(m_renderer,x_playButton,y_playbutton,playButton,w_playButton,h_playButton);
            texture(m_renderer,x_set,y_set,settingButton,w_button,h_button);
            texture(m_renderer,x_a,y_a,aboutButton,w_button,h_button);
            texture(m_renderer,x_e,y_e,exitButton,w_button,h_button);
            SDL_RenderPresent(m_renderer);
           if(x_m>=x_playButton && x_m<=x_playButton+w_playButton &&y_m<=y_playbutton+h_playButton && y_m>=y_playbutton &&(m->button.button==SDL_BUTTON_LEFT))
            {
                Mix_Chunk *click=Mix_LoadWAV("click.wav");
                Mix_PlayChannel(-1,click,0);
                getNameMenue(m_renderer);
            }
             if(x_m>=x_set  && x_m<=x_set+w_playButton &&y_m<=y_set+h_playButton && y_m>=y_set &&(m->button.button==SDL_BUTTON_LEFT))
            {
                Mix_Chunk *click=Mix_LoadWAV("click.wav");
                Mix_PlayChannel(-1,click,0);
                settingMenue(m_renderer);
            }
            if(x_m>=x_a  && x_m<=x_a+w_playButton &&y_m<=y_a+h_playButton && y_m>=y_a &&(m->button.button==SDL_BUTTON_LEFT))
            {
                Mix_Chunk *click=Mix_LoadWAV("click.wav");
                Mix_PlayChannel(-1,click,0);
                aboutMenue(m_renderer);
            }
             if(x_m>=x_g  && x_m<=x_g+w_playButton &&y_m<=y_g+h_playButton && y_m>=y_g &&(m->button.button==SDL_BUTTON_LEFT))
            {
                Mix_Chunk *click=Mix_LoadWAV("click.wav");
                Mix_PlayChannel(-1,click,0);
                guideMenue(m_renderer);
            }
             if(x_m>=x_e  && x_m<=x_e+w_playButton &&y_m<=y_e+h_playButton && y_m>=y_e &&(m->button.button==SDL_BUTTON_LEFT))
            {
                Mix_Chunk *click=Mix_LoadWAV("click.wav");
                Mix_PlayChannel(-1,click,0);
                return;
            }
        }
    }
    Mix_FreeMusic(menueSound);
}
void settingMenue(SDL_Renderer *m_renderer)
{
    string playmenue="playmenue.png";
    string nextButton="nextButton.png";
    string backButton="backButton.png";
    string bg1="bg1.jpg";
    string bg2="bg2.jpg";
    int y_b=HEIGHT-150,x_b=50,x_n=WIDTH-50-70,y_n=HEIGHT-150;
    int w_bg=(WIDTH-280)/2,h_bg=300,x_bg1=100,y_bg1=145,x_bg2=WIDTH-100-w_bg,y_bg2=145;
    texture(m_renderer,0,0,playmenue,WIDTH,HEIGHT);
    texture(m_renderer,x_b,y_b,backButton,70,70);
    texture(m_renderer,x_n,y_n,nextButton,70,70);
    write(m_renderer,100,50,"Please Chose A Stadium :",font_address_04,35,255,255,255,255,0,NONE );
    texture(m_renderer,x_bg1,y_bg1,bg1,w_bg,h_bg);
    texture(m_renderer,x_bg2,y_bg2,bg2,w_bg,h_bg);
    SDL_RenderPresent(m_renderer);
    bool bg1Chosen=true;
    bool chosen=false;
    bool flag=true;
    int x_m,y_m;
    while(flag)
    {
         SDL_PollEvent(m);
         if(m->type==SDL_MOUSEBUTTONDOWN)
         {  x_m=m->motion.x;
            y_m=m->motion.y;
           if(x_m>=x_bg1 && x_m<=x_bg1+w_bg &&y_m<=y_bg1+h_bg && y_m>=y_bg1 &&(m->button.button==SDL_BUTTON_LEFT))
           {
             Mix_Chunk *click=Mix_LoadWAV("click.wav");
            Mix_PlayChannel(-1,click,0);
            bg1Chosen=true;
            chosen=true;
            back_ground="bg1.jpg";
           }
             if(x_m>=x_bg2 && x_m<=x_bg2+w_bg &&y_m<=y_bg2+h_bg && y_m>=y_bg2 &&(m->button.button==SDL_BUTTON_LEFT))
           {
            Mix_Chunk *click=Mix_LoadWAV("click.wav");
            Mix_PlayChannel(-1,click,0);
            bg1Chosen=false;
            back_ground="bg2.jpg";
            chosen=true;
           }
            if(x_m>=x_n && x_m<=x_n+w_b &&y_m<=y_n+h_b && y_m>=y_b &&(m->button.button==SDL_BUTTON_LEFT))
           {
            Mix_Chunk *click=Mix_LoadWAV("click.wav");
            Mix_PlayChannel(-1,click,0);
            CharacterMenue(m_renderer);
           }
            if(x_m>=x_b && x_m<=x_b+70 &&y_m<=y_b+70 && y_m>=y_b &&(m->button.button==SDL_BUTTON_LEFT))
           {
            Mix_Chunk *click=Mix_LoadWAV("click.wav");
            Mix_PlayChannel(-1,click,0);
            flag=false;
           }
         }
    texture(m_renderer,0,0,playmenue,WIDTH,HEIGHT);
    texture(m_renderer,x_b,y_b,backButton,70,70);
    texture(m_renderer,x_n,y_n,nextButton,70,70);
    write(m_renderer,100,50,"Please Chose A Stadium :",font_address_04,35,255,255,255,255,0,NONE );
    texture(m_renderer,x_bg1,y_bg1,bg1,w_bg,h_bg);
    texture(m_renderer,x_bg2,y_bg2,bg2,w_bg,h_bg);
    if(bg1Chosen && chosen)
    rect(m_renderer,x_bg1,y_bg1,w_bg,h_bg,0,255,0,0);
    if(!bg1Chosen && chosen)
    rect(m_renderer,x_bg2,y_bg2,w_bg,h_bg,0,255,0,0);
    SDL_RenderPresent(m_renderer);

    }

}
void CharacterMenue(SDL_Renderer *m_renderer)
{
    string playmenue="playmenue.png";
    string backButton="backButton.png";
    string player_1="player1_L.png";
    string player_2="player2_L.png";
    string player_3="player3_L.png";
    string player_4="player4_L.png";
    string player_5="player5_L.png";
    int y_b=HEIGHT-150,x_b=50;
    int x_pR1=100,y_pR1=100;
    int w_pic=100,h_pic=100;
    int x_pR2=x_pR1+w_pic+10,y_pR2=100;
    int x_pR3=x_pR2+w_pic+10,y_pR3=100;
    int x_pR4=x_pR3+w_pic+10,y_pR4=100;
    int x_pR5=x_pR4+w_pic+10,y_pR5=100;
    int x_pL1=100,y_pL1=400;
    int x_pL2=x_pL1+w_pic+10,y_pL2=400;
    int x_pL3=x_pL2+w_pic+10,y_pL3=400;
    int x_pL4=x_pL3+w_pic+10,y_pL4=400;
    int x_pL5=x_pL4+w_pic+10,y_pL5=400;
    bool bg1Chosen=true;
    bool chosenR=false, chosenL=false;
    int charR=1,charL=1;
    bool flag=true;
    int x_m,y_m;
    while(flag)
    {
         SDL_PollEvent(m);
         if(m->type==SDL_MOUSEBUTTONDOWN)
         {  x_m=m->motion.x;
            y_m=m->motion.y;
               if(x_m>=x_b && x_m<=x_b+w_b &&y_m<=y_b+h_b && y_m>=y_b &&(m->button.button==SDL_BUTTON_LEFT))
               {
                Mix_Chunk *click=Mix_LoadWAV("click.wav");
                Mix_PlayChannel(-1,click,0);
                flag=false;

               }
                 if(x_m>=x_pR1 && x_m<=x_pR1+w_pic &&y_m<=y_pR1+h_pic && y_m>=y_pR1 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenR=true;
                    charR=1;
                    PowerRight=1;
                    player2="player1_R.png";
               }
                if(x_m>=x_pR2 && x_m<=x_pR2+w_pic &&y_m<=y_pR2+h_pic && y_m>=y_pR2 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenR=true;
                    charR=2;
                    PowerRight=2;
                    player2="player2_R.png";
               }
                if(x_m>=x_pR3 && x_m<=x_pR3+w_pic &&y_m<=y_pR3+h_pic && y_m>=y_pR3 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenR=true;
                    charR=3;
                    PowerRight=3;
                    player2="player3_R.png";
               }
                if(x_m>=x_pR4 && x_m<=x_pR4+w_pic &&y_m<=y_pR4+h_pic && y_m>=y_pR4 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenR=true;
                    charR=4;
                    PowerRight=4;
                    player2="player4_R.png";
               }
                if(x_m>=x_pR5 && x_m<=x_pR5+w_pic &&y_m<=y_pR5+h_pic && y_m>=y_pR5 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenR=true;
                    charR=5;
                    PowerRight=rand()%4+1;;
                    player2="player5_R.png";
               }
                if(x_m>=x_pL1 && x_m<=x_pL1+w_pic &&y_m<=y_pL1+h_pic && y_m>=y_pL1 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenL=true;
                    charL=1;
                    powerLeft=1;
                    player1="player1_L.png";
               }
               if(x_m>=x_pL2 && x_m<=x_pL2+w_pic &&y_m<=y_pL2+h_pic && y_m>=y_pL2 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenL=true;
                    charL=2;
                    powerLeft=2;
                    player1="player2_L.png";
               }
               if(x_m>=x_pL3 && x_m<=x_pL3+w_pic &&y_m<=y_pL3+h_pic && y_m>=y_pL3 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenL=true;
                    charL=3;
                    powerLeft=3;
                    player1="player3_L.png";
               }
               if(x_m>=x_pL4 && x_m<=x_pL4+w_pic &&y_m<=y_pL4+h_pic && y_m>=y_pL4 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenL=true;
                    charL=4;
                    powerLeft=4;
                    player1="player4_L.png";;
               }
               if(x_m>=x_pL5 && x_m<=x_pL5+w_pic &&y_m<=y_pL5+h_pic && y_m>=y_pL5 &&(m->button.button==SDL_BUTTON_LEFT))
               {
                    Mix_Chunk *click=Mix_LoadWAV("click.wav");
                    Mix_PlayChannel(-1,click,0);
                    chosenL=true;
                    charL=5;
                    powerLeft=rand()%4+1;;
                    player1="player5_L.png";;
               }
         }
    texture(m_renderer,0,0,playmenue,WIDTH,HEIGHT);
    texture(m_renderer,x_b,y_b,backButton,70,70);
    write(m_renderer,100,50,"Please Chose Right Player Character :",font_address_04,35,255,255,255,255,0,NONE );
    texture(m_renderer,x_pR1,y_pR1,player_1,w_pic,h_pic);
    texture(m_renderer,x_pR2,y_pR2,player_2,w_pic,h_pic);
    texture(m_renderer,x_pR3,y_pR3,player_3,w_pic,h_pic);
    texture(m_renderer,x_pR4,y_pR4,player_4,w_pic,h_pic);
    texture(m_renderer,x_pR5,y_pR5,player_5,w_pic,h_pic);
    if(chosenR)
    {
        switch(charR)
        {
        case 1:
           rect(m_renderer,x_pR1,y_pR1,w_pic,h_pic,0,255,0,0);
           break;
        case 2:
           rect(m_renderer,x_pR2,y_pR2,w_pic,h_pic,0,255,0,0);
           break;
        case 3:
           rect(m_renderer,x_pR3,y_pR3,w_pic,h_pic,0,255,0,0);
           break;
        case 4:
           rect(m_renderer,x_pR4,y_pR4,w_pic,h_pic,0,255,0,0);
           break;
        case 5:
           rect(m_renderer,x_pR5,y_pR5,w_pic,h_pic,0,255,0,0);
           break;
        }
    }
    if(chosenL)
    {
        switch(charL)
        {
        case 1:
           rect(m_renderer,x_pL1,y_pL1,w_pic,h_pic,0,255,0,0);
           break;
        case 2:
           rect(m_renderer,x_pL2,y_pL2,w_pic,h_pic,0,255,0,0);
           break;
        case 3:
           rect(m_renderer,x_pL3,y_pL3,w_pic,h_pic,0,255,0,0);
           break;
        case 4:
           rect(m_renderer,x_pL4,y_pL4,w_pic,h_pic,0,255,0,0);
           break;
        case 5:
           rect(m_renderer,x_pL5,y_pL5,w_pic,h_pic,0,255,0,0);
           break;
        }
    }
    write(m_renderer,100,350,"Please Chose Left Player Character :",font_address_04,35,255,255,255,255,0,NONE );
    texture(m_renderer,x_pL1,y_pL1,player_1,w_pic,h_pic);
    texture(m_renderer,x_pL2,y_pL2,player_2,w_pic,h_pic);
    texture(m_renderer,x_pL3,y_pL3,player_3,w_pic,h_pic);
    texture(m_renderer,x_pL4,y_pL4,player_4,w_pic,h_pic);
    texture(m_renderer,x_pL5,y_pL5,player_5,w_pic,h_pic);
    SDL_RenderPresent(m_renderer);
    }

}
void aboutMenue(SDL_Renderer *m_renderer)
{
    string backButton="backButton.png";
    string  about="about.JPG";
    int y_b=HEIGHT-150,x_b=50;
    int x_m,y_m;
    bool flag=true;
    string line1="This is a game that had developed by two electrical engineering students as a project in Graphic environment in C++.";
    string line2="This project, actually, is the creation of a simplified version of the game Football Head 2020. Here is a description of this game.";
    string line3="The whole aspect of game consists of menu part and  game part. Parts of menu respectively are play, setting, about and exit.";
    string line4="Part play is used for entering the game segment, the second part, part setting, is used for changing options, here is the third part:)";
    string line5="and you can select exit to quit the game. As we said you can enter the game environment, the main part, by selecting play and then after";
    string line6="writing players names, you can play! The purpose is to be able to score as many goals as possible for the opposing player, and obviously ";
    string line7="the winner is the one whose score is higher!";
    string line8="At the end it is necessary to appreciate from Dr. Arasteh & Dr. Vahdat and all the people who helped us in this case.";
    string line9="Hope  you enjoy playing:D";
    string line10="Roja Atashkar, rojatashkarr@gmail.com";
    string line11="Zahra Esmaeili, zahrasaraesmaeili.pm44@gmail.com";
    texture(m_renderer,0,0,about,WIDTH,HEIGHT);
    write(m_renderer,35,25,line1,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,45,line2,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,65,line3,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,85,line4,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,105,line5,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,125,line6,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,145,line7,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,165,line8,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,185,line9,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,205,line10,font_address_04,20,0,0,0,255,0,NONE);
    write(m_renderer,35,225,line11,font_address_04,20,0,0,0,255,0,NONE);
    texture(m_renderer,x_b,y_b,backButton,70,70);
    SDL_RenderPresent(m_renderer);
    SDL_PollEvent(m);
    while(flag)
    {
        SDL_PollEvent(m);
    if(m->type==SDL_MOUSEBUTTONDOWN)
     {  x_m=m->motion.x;
        y_m=m->motion.y;
        if(x_m>=x_b && x_m<=x_b+h_b &&y_m<=y_b+h_b && y_m>=y_b &&(m->button.button==SDL_BUTTON_LEFT))
           {
            Mix_Chunk *click=Mix_LoadWAV("click.wav");
            Mix_PlayChannel(-1,click,0);
            flag=false;
            break;
           }
     }
    }

}
void guideMenue(SDL_Renderer *m_renderer)
{
     string backButton="backButton.png";
     string guidePic="keyboard.png";
     int y_b=HEIGHT-150,x_b=50;
     int x_m,y_m;
     texture(m_renderer,0,0,guidePic,WIDTH,HEIGHT);
     texture(m_renderer,x_b,y_b,backButton,70,70);
     SDL_RenderPresent(m_renderer);
     bool flag=true;
       while(flag)
    {
        SDL_PollEvent(m);
    if(m->type==SDL_MOUSEBUTTONDOWN)
     {  x_m=m->motion.x;
        y_m=m->motion.y;
        if(x_m>=x_b && x_m<=x_b+h_b &&y_m<=y_b+h_b && y_m>=y_b &&(m->button.button==SDL_BUTTON_LEFT))
           {
            Mix_Chunk *click=Mix_LoadWAV("click.wav");
            Mix_PlayChannel(-1,click,0);
            flag=false;
            break;
           }
     }
    }
}
void OpenFile()
{
    ifstream NAME("Names.txt");
    ifstream WIN("wins.txt");
    ifstream TIE("ties.txt");
    ifstream LOST("losts.txt");
    ifstream GF("GFs.txt");
    ifstream GA("GAs.txt");
    string name;
    int i;
    int x=0;
    int counter=0;
    while(getline(NAME,name))
    {
        names[x]=name;
        x++;
        counter++;
    }
     x=0;
  while(x<=counter)
    {
       GF>>GFs[x];
        x++;
    }
     x=0;
  while(x<=counter)
    {
        GA>>GAs[x];
        x++;
    }
     x=0;
  while(x<=counter)
    {
        WIN>>wins[x];
        x++;
    }
    x=0;
 while(x<=counter)
    {
        TIE>>ties[x];
        x++;
    }
    x=0;
 while(x<=counter)
    {
      LOST>>losts[x];
        x++;
    }
}
void AddRecord(string name,int scored,int GF,int GA)//2 for win 1for tie 0 for lost
{
     int counter=0;
    for(int x=0; x<=maxrow; x++)
    {
        if(names[x]==name)
        {   counter++;
             switch(scored)
            {
            case 2:
                wins[x]++;
                break;
            case 1:
                ties[x]++;
                break;
            case 0:
                losts[x] ++;
                break;
            }
            GFs[x]+=GF;
            GAs[x]+=GA;
             break;
        }
    }
    if(counter==0)
    {
    string newName=name;
    int tie=0;
    int win=0;
    int lost=0;
    switch(scored)
    {
    case 2:
        win++;
        break;
    case 1:
        tie++;
        break;
    case 0:
        lost ++;
        break;
    }
    for(int x=0;x<maxrow; x++)
        {
            if(names[x]=="-1")
            {
                names[x]=newName;
                ties[x]=tie;
                losts[x]=lost;
                wins[x]=win;
                GFs[x]=GF;
                GAs[x]=GA;
              return;
            }
        }
    }
}
void SaveToFile()
{
    ofstream NAME;
    NAME.open("Names.txt");
    ofstream WIN;
    WIN.open("wins.txt");
    ofstream TIE;
    TIE.open("ties.txt");
    ofstream LOST;
    LOST.open("losts.txt");
     ofstream GFF;
    GFF.open("GFs.txt");
     ofstream GAA;
    GAA.open("GAs.txt");
    for(int x=0; x<maxrow; x++)
    {
        if(names[x]=="-1")
            break;
        else
        {
            cout<<"SAVING";
       NAME<<names[x]<<endl;
       WIN<<wins[x]<<endl;
       TIE<<ties[x]<<endl;
       LOST<<losts[x]<<endl;
       GFF<<GFs[x]<<endl;
       GAA<<GAs[x]<<endl;
        }

    }
    cout<<"SAVED";
}
void chartMenue(SDL_Renderer *m_renderer)
{

  string playmenue="playmenue.png";
  string backButton="backButton.png";
  int y_b=HEIGHT-150,x_b=50;
  int x_m,y_m;
  int x_board=45,y_board=50;
  int counter=0;
  int dy=23;
  int y_text=y_board+70;
  texture(m_renderer,0,0,playmenue,WIDTH,HEIGHT);
  rect(m_renderer,x_board,y_board,WIDTH-90,65,0,255,0,1);
  write(m_renderer,x_board+10,y_board+20,"Name",font_address_04,20,0,0,0,255,0,NONE);
  write(m_renderer,x_board+(WIDTH-90)/9,y_board+20,"Played",font_address_04,20,0,0,0,255,0,NONE);
  write(m_renderer,x_board+2*(WIDTH-90)/9,y_board+20,"Won",font_address_04,20,0,0,0,255,0,NONE);
  write(m_renderer,x_board+3*(WIDTH-90)/9,y_board+20,"Drown",font_address_04,20,0,0,0,255,0,NONE);
  write(m_renderer,x_board+4*(WIDTH-90)/9,y_board+20,"Lost",font_address_04,20,0,0,0,255,0,NONE);
  write(m_renderer,x_board+5*(WIDTH-90)/9,y_board+20,"GF",font_address_04,20,0,0,0,255,0,NONE);
  write(m_renderer,x_board+6*(WIDTH-90)/9,y_board+20,"GA",font_address_04,20,0,0,0,255,0,NONE);
  write(m_renderer,x_board+7*(WIDTH-90)/9,y_board+20,"GD",font_address_04,20,0,0,0,255,0,NONE);
  write(m_renderer,x_board+8*(WIDTH-90)/9,y_board+20,"Scored",font_address_04,20,0,0,0,255,0,NONE);
  rect(m_renderer,x_board,y_board+70,WIDTH-140,400,255,255,255,1);
  texture(m_renderer,x_b,y_b,backButton,70,70);
   for(int x=0; x<maxrow;x++)
    {
    if(names[x]!="-1")
        {
        counter++;
        int GDD=GFs[x]-GAs[x];
        int playy=ties[x]+losts[x]+wins[x];
        int Scoree=3*wins[x]+ties[x];
        string win,lost,tie,GA,GD,GF,play,Score;
        stringstream ss;
        ss<<wins[x];
        ss>>win;
        stringstream rr;
        rr<<ties[x];
        rr>>tie;
        stringstream ww;
        ww<<losts[x];
        ww>>lost;
        stringstream pp;
        pp<<GAs[x];
        pp>>GA;
         stringstream uu;
        uu<<GFs[x];
        uu>>GF;
        stringstream aa;
        aa<<GDD;
        aa>>GD;
        stringstream bb;
        bb<<playy;
        bb>>play;
        stringstream ee;
        ee<<Scoree;
        ee>>Score;
      write(m_renderer,x_board+10,y_text,names[x],font_address_04,20,0,0,0,255,0,NONE);
      write(m_renderer,x_board+(WIDTH-90)/9,y_text,play,font_address_04,20,0,0,0,255,0,NONE);
      write(m_renderer,x_board+2*(WIDTH-90)/9,y_text,win,font_address_04,20,0,0,0,255,0,NONE);
      write(m_renderer,x_board+3*(WIDTH-90)/9,y_text,tie,font_address_04,20,0,0,0,255,0,NONE);
      write(m_renderer,x_board+4*(WIDTH-90)/9,y_text,lost,font_address_04,20,0,0,0,255,0,NONE);
      write(m_renderer,x_board+5*(WIDTH-90)/9,y_text,GF,font_address_04,20,0,0,0,255,0,NONE);
      write(m_renderer,x_board+6*(WIDTH-90)/9,y_text,GA,font_address_04,20,0,0,0,255,0,NONE);
      write(m_renderer,x_board+7*(WIDTH-90)/9,y_text,GD,font_address_04,20,0,0,0,255,0,NONE);
      write(m_renderer,x_board+8*(WIDTH-90)/9,y_text,Score,font_address_04,20,0,0,0,255,0,NONE);
      y_text+=dy;
    }
 }
    if(counter==0)
        write(m_renderer,WIDTH/3,y_board+100,"NO PLAYER FOUND !",font_address_04,35,255,0,0,0,0,NONE);
   SDL_RenderPresent(m_renderer);
   bool flag=true;
    while(flag)
    {
          SDL_PollEvent(m);
         if(m->type==SDL_MOUSEBUTTONDOWN)
         {  x_m=m->motion.x;
            y_m=m->motion.y;
                if(x_m>=x_b && x_m<=x_b+70 &&y_m<=y_b+70 && y_m>=y_b &&(m->button.button==SDL_BUTTON_LEFT))
               {
                  Mix_Chunk *click=Mix_LoadWAV("click.wav");
                  Mix_PlayChannel(-1,click,0);
                  return;
               }
         }
    }
}
void getNameMenue(SDL_Renderer *m_renderer)
{
    string playmenue="playmenue.png";
    string nextButton="nextButton.png";
    string backButton="backButton.png";
    string cup="cup.png";
    int nameRfound, nameLfound;
    int x_m,y_m;
    int x_c=WIDTH-70-50,y_c=20;
    int y_b=HEIGHT-150,x_b=50,x_n=WIDTH-50-70,y_n=HEIGHT-150;
    int counterR=0,counterL=0;
    texture(m_renderer,0,0,playmenue,WIDTH,HEIGHT);
    texture(m_renderer,x_b,y_b,backButton,70,70);
    texture(m_renderer,x_n,y_n,nextButton,70,70);
    texture(m_renderer,x_c,y_c,cup,70,70);
    rect(m_renderer,100,100,WIDTH-200,100,255,255,255,1);
    rect(m_renderer,100,250,WIDTH-200,100,255,255,255,1);
    write(m_renderer,100,40,"Please Enter Your Names:",font_address_04,20,0,0,255,255,0.0,NONE);
    write(m_renderer,100,90,"RIGHT player name:",font_address_04,20,0,0,0,255,0.0,NONE);
    write(m_renderer,100,240,"LEFT player name:",font_address_04,20,0,0,0,255,0.0,NONE);
    SDL_RenderPresent(m_renderer);
    if(!getnamed)
    {
        inputText(m_renderer,110,110,nameR,font_address_04,35,0,0,0,255);
        for(int x=0; x<=maxrow; x++)
        {
            if(names[x]==nameR)
            {   counterR++;
                nameRfound=x;
                 break;
            }
        }
        inputText(m_renderer,110,260,nameL,font_address_04,35,0,0,0,255);
        for(int x=0; x<=maxrow; x++)
        {
            if(names[x]==nameL)
            {   counterL++;
                nameLfound=x;
                 break;
            }
        }
        getnamed=true;
    }
    else
    {
        write(m_renderer,110,110,nameR,font_address_04,35,0,0,0,255,0,NONE);
        write(m_renderer,110,260,nameL,font_address_04,35,0,0,0,255,0,NONE);
          if(counterR!=0)
        {
  write(m_renderer,100+10,145,"Name",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+(WIDTH-200)/9,145,"Played",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+2*(WIDTH-200)/9,145,"Won",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+3*(WIDTH-200)/9,145,"Drown",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+4*(WIDTH-200)/9,145,"Lost",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+5*(WIDTH-200)/9,145,"GF",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+6*(WIDTH-200)/9,145,"GA",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+7*(WIDTH-200)/9,145,"GD",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+8*(WIDTH-200)/9,145,"Scored",font_address_04,20,255,0,0,255,0,NONE);
  int GDD=GFs[nameRfound]-GAs[nameRfound];
  int playy=ties[nameRfound]+losts[nameRfound]+wins[nameRfound];
  int Scoree=3*wins[nameRfound]+ties[nameRfound];
  string win,lost,tie,GA,GD,GF,play,Score;
  stringstream ss;
  ss<<wins[nameRfound];
  ss>>win;
  stringstream rr;
  rr<<ties[nameRfound];
  rr>>tie;
  stringstream ww;
  ww<<losts[nameRfound];
  ww>>lost;
  stringstream pp;
  pp<<GAs[nameRfound];
  pp>>GA;
  stringstream uu;
  uu<<GFs[nameRfound];
  uu>>GF;
  stringstream aa;
  aa<<GDD;
  aa>>GD;
  stringstream bb;
  bb<<playy;
  bb>>play;
  stringstream ee;
  ee<<Scoree;
  ee>>Score;
  write(m_renderer,100+10,165,names[nameRfound],font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+(WIDTH-200)/9,165,play,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+2*(WIDTH-200)/9,165,win,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+3*(WIDTH-200)/9,165,tie,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+4*(WIDTH-200)/9,165,lost,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+5*(WIDTH-200)/9,165,GF,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+6*(WIDTH-200)/9,165,GA,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+7*(WIDTH-200)/9,165,GD,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+8*(WIDTH-200)/9,165,Score,font_address_04,20,255,0,0,255,0,NONE);
        }
if(counterL!=0)
 {
  write(m_renderer,100+10,295,"Name",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+(WIDTH-200)/9,295,"Played",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+2*(WIDTH-200)/9,295,"Won",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+3*(WIDTH-200)/9,295,"Drown",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+4*(WIDTH-200)/9,295,"Lost",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+5*(WIDTH-200)/9,295,"GF",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+6*(WIDTH-200)/9,295,"GA",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+7*(WIDTH-200)/9,295,"GD",font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+8*(WIDTH-200)/9,295,"Scored",font_address_04,20,255,0,0,255,0,NONE);
  int GDD=GFs[nameLfound]-GAs[nameLfound];
  int playy=ties[nameLfound]+losts[nameLfound]+wins[nameLfound];
  int Scoree=3*wins[nameLfound]+ties[nameLfound];
  string win,lost,tie,GA,GD,GF,play,Score;
  stringstream ss;
  ss<<wins[nameLfound];
  ss>>win;
  stringstream rr;
  rr<<ties[nameLfound];
  rr>>tie;
  stringstream ww;
  ww<<losts[nameLfound];
  ww>>lost;
  stringstream pp;
  pp<<GAs[nameLfound];
  pp>>GA;
  stringstream uu;
  uu<<GFs[nameLfound];
  uu>>GF;
  stringstream aa;
  aa<<GDD;
  aa>>GD;
  stringstream bb;
  bb<<playy;
  bb>>play;
  stringstream ee;
  ee<<Scoree;
  ee>>Score;
  write(m_renderer,100+10,315,names[nameLfound],font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+(WIDTH-200)/9,315,play,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+2*(WIDTH-200)/9,315,win,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+3*(WIDTH-200)/9,315,tie,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+4*(WIDTH-200)/9,315,lost,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+5*(WIDTH-200)/9,315,GF,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+6*(WIDTH-200)/9,315,GA,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+7*(WIDTH-200)/9,315,GD,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+8*(WIDTH-200)/9,315,Score,font_address_04,20,255,0,0,255,0,NONE);
  }
  SDL_RenderPresent(m_renderer);
    }
bool flag=true;
while(flag)
{
     SDL_PollEvent(m);
     if(m->type==SDL_MOUSEBUTTONDOWN)
         {  x_m=m->motion.x;
            y_m=m->motion.y;
           if(x_m>=x_n && x_m<=x_n+70 &&y_m<=y_n+70 && y_m>=y_n &&(m->button.button==SDL_BUTTON_LEFT))
           {
               Mix_Chunk *click=Mix_LoadWAV("click.wav");
               Mix_PlayChannel(-1,click,0);
              flag=false;
              continueGame=true;
              startGame=true;
               return;
           }
            if(x_m>=x_b && x_m<=x_b+70 &&y_m<=y_b+70 && y_m>=y_b &&(m->button.button==SDL_BUTTON_LEFT))
           {
               Mix_Chunk *click=Mix_LoadWAV("click.wav");
               Mix_PlayChannel(-1,click,0);
               flag=false;
               return;
           }
            if(x_m>=x_c && x_m<=x_c+70 &&y_m<=y_c+70 && y_m>=y_c &&(m->button.button==SDL_BUTTON_LEFT))
           {
               Mix_Chunk *click=Mix_LoadWAV("click.wav");
               Mix_PlayChannel(-1,click,0);
               chartMenue(m_renderer);
           }
     }
    texture(m_renderer,0,0,playmenue,WIDTH,HEIGHT);
    texture(m_renderer,x_b,y_b,backButton,70,70);
    texture(m_renderer,x_n,y_n,nextButton,70,70);
    texture(m_renderer,x_c,y_c,cup,70,70);
    rect(m_renderer,100,100,WIDTH-200,100,255,255,255,1);
    rect(m_renderer,100,250,WIDTH-200,100,255,255,255,1);
    write(m_renderer,100,40,"Please Enter Your Names:",font_address_04,20,0,0,255,255,0.0,NONE);
    write(m_renderer,100,90,"RIGHT player name:",font_address_04,20,0,0,0,255,0.0,NONE);
    write(m_renderer,100,240,"LEFT player name:",font_address_04,20,0,0,0,255,0.0,NONE);
    write(m_renderer,110,110,nameR,font_address_04,35,0,0,0,255,0,NONE);
    write(m_renderer,110,260,nameL,font_address_04,35,0,0,0,255,0,NONE);
    if(counterR!=0)
    {
      write(m_renderer,100+10,145,"Name",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+(WIDTH-200)/9,145,"Played",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+2*(WIDTH-200)/9,145,"Won",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+3*(WIDTH-200)/9,145,"Drown",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+4*(WIDTH-200)/9,145,"Lost",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+5*(WIDTH-200)/9,145,"GF",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+6*(WIDTH-200)/9,145,"GA",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+7*(WIDTH-200)/9,145,"GD",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+8*(WIDTH-200)/9,145,"Scored",font_address_04,20,255,0,0,255,0,NONE);
     int GDD=GFs[nameRfound]-GAs[nameRfound];
     int playy=ties[nameRfound]+losts[nameRfound]+wins[nameRfound];
     int Scoree=3*wins[nameRfound]+ties[nameRfound];
     string win,lost,tie,GA,GD,GF,play,Score;
     stringstream ss;
     ss<<wins[nameRfound];
     ss>>win;
     stringstream rr;
     rr<<ties[nameRfound];
     rr>>tie;
     stringstream ww;
     ww<<losts[nameRfound];
     ww>>lost;
     stringstream pp;
     pp<<GAs[nameRfound];
     pp>>GA;
     stringstream uu;
     uu<<GFs[nameRfound];
     uu>>GF;
     stringstream aa;
     aa<<GDD;
     aa>>GD;
     stringstream bb;
     bb<<playy;
     bb>>play;
     stringstream ee;
     ee<<Scoree;
     ee>>Score;
      write(m_renderer,100+10,165,names[nameRfound],font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+(WIDTH-200)/9,165,play,font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+2*(WIDTH-200)/9,165,win,font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+3*(WIDTH-200)/9,165,tie,font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+4*(WIDTH-200)/9,165,lost,font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+5*(WIDTH-200)/9,165,GF,font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+6*(WIDTH-200)/9,165,GA,font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+7*(WIDTH-200)/9,165,GD,font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+8*(WIDTH-200)/9,165,Score,font_address_04,20,255,0,0,255,0,NONE);
        }
    else
         write(m_renderer,100+10,165,"New player!...WELCOME :D",font_address_04,25,255,0,0,255,0,NONE);
    if(counterL!=0)
    {
      write(m_renderer,100+10,295,"Name",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+(WIDTH-200)/9,295,"Played",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+2*(WIDTH-200)/9,295,"Won",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+3*(WIDTH-200)/9,295,"Drown",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+4*(WIDTH-200)/9,295,"Lost",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+5*(WIDTH-200)/9,295,"GF",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+6*(WIDTH-200)/9,295,"GA",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+7*(WIDTH-200)/9,295,"GD",font_address_04,20,255,0,0,255,0,NONE);
      write(m_renderer,100+8*(WIDTH-200)/9,295,"Scored",font_address_04,20,255,0,0,255,0,NONE);
      int GDD=GFs[nameLfound]-GAs[nameLfound];
      int playy=ties[nameLfound]+losts[nameLfound]+wins[nameLfound];
      int Scoree=3*wins[nameLfound]+ties[nameLfound];
    string win,lost,tie,GA,GD,GF,play,Score;
    stringstream ss;
    ss<<wins[nameLfound];
    ss>>win;
    stringstream rr;
    rr<<ties[nameLfound];
    rr>>tie;
    stringstream ww;
    ww<<losts[nameLfound];
    ww>>lost;
    stringstream pp;
    pp<<GAs[nameLfound];
    pp>>GA;
     stringstream uu;
    uu<<GFs[nameLfound];
    uu>>GF;
    stringstream aa;
    aa<<GDD;
    aa>>GD;
    stringstream bb;
    bb<<playy;
    bb>>play;
    stringstream ee;
    ee<<Scoree;
    ee>>Score;
  write(m_renderer,100+10,315,names[nameLfound],font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+(WIDTH-200)/9,315,play,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+2*(WIDTH-200)/9,315,win,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+3*(WIDTH-200)/9,315,tie,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+4*(WIDTH-200)/9,315,lost,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+5*(WIDTH-200)/9,315,GF,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+6*(WIDTH-200)/9,315,GA,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+7*(WIDTH-200)/9,315,GD,font_address_04,20,255,0,0,255,0,NONE);
  write(m_renderer,100+8*(WIDTH-200)/9,315,Score,font_address_04,20,255,0,0,255,0,NONE);
        }
    else
         write(m_renderer,100+10,315,"New player!...WELCOME :D",font_address_04,25,255,0,0,255,0,NONE);
    SDL_RenderPresent(m_renderer);
    }

}
void afterGameMenue(SDL_Renderer *m_renderer)
{
     string playmenue="playmenue.png",numR,numL;
     string Crown="crown.png";
     string home="home.png";
     bool flag=true , saved=false;
     int x_m,y_m;
     int x_R=50,y_R=200,x_L=WIDTH-50-250,y_L=200,w=250,h=250;
     int x_h=WIDTH-100,y_h=HEIGHT-100,w_h=70,h_h=70;
     stringstream ss;
        ss<<GOAL_right;
        ss>>numR;
    stringstream ww;
        ww<<GOAL_left;
         ww>>numL;

     while(flag)
     {
        texture(m_renderer,0,0,playmenue,WIDTH,HEIGHT);
        texture(m_renderer,x_R,y_R,player1,w,h);
        texture(m_renderer,x_L,y_L,player2,w,h);
        texture(m_renderer,x_h,y_h,home,w_h,h_h);
        write(m_renderer,x_R+w+100,y_R+h/2,numR,font_address_04,60,255,255,255,255,0,NONE);
        write(m_renderer,WIDTH/2-30,y_R+h/2,"___",font_address_04,60,255,255,255,255,0,NONE);
        write(m_renderer,x_L-105,y_L+h/2,numL,font_address_04,60,255,255,255,255,0,NONE);
        if(GOAL_left==GOAL_right )
        {
        write(m_renderer,400,200,"That Was A Tie !!!",font_address_04,40,255,255,255,255,0,NONE);
            if(!saved)
            {
                AddRecord(nameR,1,GOAL_right,GOAL_left);
                AddRecord(nameL,1,GOAL_left,GOAL_right);
                saved=true;
            }
        }
        else if(GOAL_left>GOAL_right)
        {
        write(m_renderer,400,200,"Player "+nameL+" Wins !!!",font_address_04,40,255,255,255,255,0,NONE);
        texture(m_renderer,x_L,y_L-h/2,Crown,w,h/2);
            if(!saved)
            {
                AddRecord(nameR,0,GOAL_right,GOAL_left);
                AddRecord(nameL,2,GOAL_left,GOAL_right);
                saved=true;
            }
        }
        else  if(GOAL_left<GOAL_right)
        {
        write(m_renderer,400,200,"Player "+nameR+" Wins !!!",font_address_04,40,255,255,255,255,0,NONE);
        texture(m_renderer,x_R,y_R-h/2,Crown,w,h/2);
         if(!saved)
            {
                AddRecord(nameR,2,GOAL_right,GOAL_left);
                AddRecord(nameL,0,GOAL_left,GOAL_right);
                saved=true;
            }
        }

     SDL_RenderPresent(m_renderer);
       SDL_PollEvent(m);
         if(m->type==SDL_MOUSEBUTTONDOWN)
         {  x_m=m->motion.x;
            y_m=m->motion.y;
               if(x_m>=x_h && x_m<=x_h+w_h &&y_m<=y_h+h_h && y_m>=y_h &&(m->button.button==SDL_BUTTON_LEFT))
               {
                   Mix_Chunk *click=Mix_LoadWAV("click.wav");
                   Mix_PlayChannel(-1,click,0);
                   flag=false;
               }
         }
     }
    SaveToFile();
}
void GOAL(SDL_Renderer *m_renderer,int x,int y,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num,int goal)
{
       switch (goal)
     {
         case 0:
            myTextRGBA(m_renderer,x,y,"0",font,font_size,R,G,B,A,angle,NONE);
            break;
             case 1:
            myTextRGBA(m_renderer,x,y,"1",font,font_size,R,G,B,A,angle,NONE);
            break;
             case 2:
            myTextRGBA(m_renderer,x,y,"2",font,font_size,R,G,B,A,angle,NONE);
            break;
             case 3:
            myTextRGBA(m_renderer,x,y,"3",font,font_size,R,G,B,A,angle,NONE);
            break;
             case 4:
            myTextRGBA(m_renderer,x,y,"4",font,font_size,R,G,B,A,angle,NONE);
            break;
             case 5:
            myTextRGBA(m_renderer,x,y,"5",font,font_size,R,G,B,A,angle,NONE);
            break;
     }
}
void textureRenderer(SDL_Renderer *m_renderer, int font_size ,double angle)// 0for tie 1 for right 2 for left
{
    int x_textL=x_scoreb+w_scoreb/2-103;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    int R=255,G=255,B=255,A=255;
    int w_f=60,h_f=60;
    string questionmark="questionmarks.png";
    string goal="goal!.png";
    string crown="crown.png";
    string pause="pause.png";
    string start="start.png";
    string home="home.png";
    string fire="powerIcon.png";
    string restart="restart.png";
    int questionmark_pic=70;
      currentTime = SDL_GetTicks()-startTime;
         if (currentTime > lastTime + 1000)
         lastTime = currentTime;
    stringstream ss;
    ss<<currentTime/1000;
    string timestr;
    ss>>timestr;
    if(currentTime/1000>=150)
    {
        continueGame=false;
        return;
    }
    texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
    texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
    texture(m_renderer,x_shoeL-50,y_shoeL-player_h,player1,player_w,player_h);
    texture(m_renderer,x_shoeR+50,y_shoeR-player_h,player2,player_w,player_h);
    texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
    texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
    if(!invisible)
    texture(m_renderer,x,y,ball,RADIOUS,RADIOUS);
    texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
    if(rightFiriz)
        texture(m_renderer,x_shoeR+50,y_shoeR-player_h-questionmark_pic,questionmark,questionmark_pic,questionmark_pic);
    if(leftFirix)
         texture(m_renderer,x_shoeL-50,y_shoeL-player_h-questionmark_pic,questionmark,questionmark_pic,questionmark_pic);
    rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
    write(m_renderer,WIDTH/2,y_scoreb+h_scoreb/2,timestr,font_address_04,font_size,0,0,0,255,angle,NONE);
    texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
    texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
    write(m_renderer,x_scoreb+10,y_scoreb+h_scoreb+10,nameL,font_address_04,35,255,255,255,255,0,NONE);
    write(m_renderer,x_scoreb+w_scoreb-70,y_scoreb+h_scoreb+10,nameR,font_address_04,35,255,255,255,255,0,NONE);
    my_line(m_renderer,x_scoreb+50+player_pic+5,y_scoreb-15+player_pic/2,powerLengthgLeft,0,15,255,0,0);
    my_line(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15+player_pic/2,powerLengthgRight,-3.141592,15,255,0,0);
    texture(m_renderer,x_scoreb+50+player_pic+5+powerLengthgLeft-w_f/2,y_scoreb-15,fire,w_f,h_f);
    texture(m_renderer,w_scoreb-50-player_pic-powerLengthgRight+w_f/2,y_scoreb-15,fire,w_f,h_f);
    GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
    GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
    if(goalScoredRight)
    {
         texture(m_renderer,x_shoeR+50,y_shoeR-player_h-70,crown,70,70);
         //texture(m_renderer,)
    }
     texture(m_renderer,x_h,y_h,home,w_b,h_b);
    if(!paused)
    texture(m_renderer,x_p,y_p,start,w_b,h_b);
    else
    {
    texture(m_renderer,x_p,y_p,pause,w_b,h_b);
    write(m_renderer,100,200,"PAUSED!",font_address_04,45,190,50,50,255,0,NONE);
    }

    texture(m_renderer,x_r,y_r,restart,w_b,h_b);
    SDL_RenderPresent( m_renderer );
    SDL_Delay(2);
    SDL_RenderClear( m_renderer );
}
void textureRendererPunch(SDL_Renderer *m_renderer, int font_size ,double angle,bool side, int x_pu,int y_pu)
{
   int R=255,G=255,B=255,A=255;
   string questionmark="questionmarks.png";
   string punch_L="punch_L.png";
   string punch_R="punch_R.png";
   string goal="goal!.png";
    string pause="pause.png";
    string start="start.png";
    string home="home.png";
    string restart="restart.png";
   int x_textL=x_scoreb+w_scoreb/2-103;
   int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
   int x_textR=x_scoreb+w_scoreb/2+100;
     currentTime = SDL_GetTicks()-startTime;
     if (currentTime > lastTime + 1000)
     lastTime = currentTime;
   if(currentTime/1000>=150)
   {
       continueGame=false;
       return;
   }
   int questionmark_pic=70;
    stringstream ss;
  ss<<currentTime/1000;
  string timestr;
  ss>>timestr;
    texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
    texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
    texture(m_renderer,x_shoeL-50,y_shoeL-player_h,player1,player_w,player_h);
    texture(m_renderer,x_shoeR+50,y_shoeR-player_h,player2,player_w,player_h);
    texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
    texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
    write(m_renderer,x_scoreb+10,y_scoreb+h_scoreb+10,nameL,font_address_04,35,255,255,255,255,0,NONE);
    write(m_renderer,x_scoreb+w_scoreb-70,y_scoreb+h_scoreb+10,nameR,font_address_04,35,255,255,255,255,0,NONE);
    texture(m_renderer,x,y,ball,RADIOUS,RADIOUS);
    texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
    if(rightFiriz)
        texture(m_renderer,x_shoeR+50,y_shoeR-player_h-questionmark_pic,questionmark,questionmark_pic,questionmark_pic);
    if(leftFirix)
         texture(m_renderer,x_shoeL-50,y_shoeL-player_h-questionmark_pic,questionmark,questionmark_pic,questionmark_pic);
        if(side)
            texture(m_renderer,x_pu,y_pu,punch_R,70,70);
        else
           texture(m_renderer,x_pu,y_pu,punch_L,70,70);
    rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
    texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
    texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
    my_line(m_renderer,x_scoreb+50+player_pic+5,y_scoreb-15+player_pic/2,powerLengthgLeft,0,15,255,0,0);
    my_line(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15+player_pic/2,powerLengthgRight,-3.141592,15,255,0,0);
    GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
    GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
//            if(goaled)
//            texture(m_renderer,150,150,goal,WIDTH-300,HEIGHT-300);
   texture(m_renderer,x_h,y_h,home,w_b,h_b);
    if(!paused)
    texture(m_renderer,x_p,y_p,pause,w_b,h_b);
    else
    texture(m_renderer,x_p,y_p,start,w_b,h_b);
    texture(m_renderer,x_r,y_r,restart,w_b,h_b);
    SDL_RenderPresent( m_renderer );
    SDL_Delay(2);
    SDL_RenderClear( m_renderer );
}
void textureRendererMainMenue(SDL_Renderer *m_renderer, int x_playButton,int y_playbutton,int h_playButton, int w_playButton, int h_button, int w_button)
{
    string stadium="stadium.jpg";
    string playButton="playButton.png";
    string settingButton="settingButton.png";
    string soundButton="soundButton.png";
    string ChartButton="ChartButton.png";
    texture(m_renderer,0,0,stadium,WIDTH,HEIGHT);
    texture(m_renderer,x_playButton,y_playbutton,playButton,w_playButton,h_playButton);
    texture(m_renderer,x_playButton+10+w_playButton,y_playbutton,settingButton,w_button,h_button);
    texture(m_renderer,x_playButton,y_playbutton+h_playButton+10,ChartButton,w_button,h_button);
    texture(m_renderer,x_playButton+w_button+10,y_playbutton+h_playButton+10,soundButton,w_button,h_button);
}
void textureRendererKichFireBall(SDL_Renderer *m_renderer, int font_size ,double angle,bool playerSide)
{
   int R=255,G=255,B=255,A=255;
   string questionmark="questionmarks.png";
   string fire="fire.png";
   string fireball_L="fireball_L.png";
   string fireball_R="fireball_R.png";
   string goal="goal!.png";
   string pause="pause.png";
   string start="start.png";
    string home="home.png";
    string restart="restart.png";
   int questionmark_pic=70;
   int h_fire=200;
    currentTime = SDL_GetTicks()-startTime;
     if (currentTime > lastTime + 1000)
     lastTime = currentTime;
   if(currentTime/1000>=150)
   {
       continueGame=false;
       return;
   }
   stringstream ss;
   ss<<currentTime/1000;
   string timestr;
   ss>>timestr;
   int x_textL=x_scoreb+w_scoreb/2-103;
   int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
   int x_textR=x_scoreb+w_scoreb/2+100;
    texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
    texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
    texture(m_renderer,x_shoeL-50,y_shoeL-player_h,player1,player_w,player_h);
    texture(m_renderer,x_shoeR+50,y_shoeR-player_h,player2,player_w,player_h);
    texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
    texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
    write(m_renderer,x_scoreb+10,y_scoreb+h_scoreb+10,nameL,font_address_04,35,255,255,255,255,0,NONE);
    write(m_renderer,x_scoreb+w_scoreb-70,y_scoreb+h_scoreb+10,nameR,font_address_04,35,255,255,255,255,0,NONE);
    if(playerSide)
    texture(m_renderer,x,y,fireball_R,RADIOUS,RADIOUS);
    else
    texture(m_renderer,x,y,fireball_L,RADIOUS,RADIOUS);
    texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
    if(rightFiriz)
        texture(m_renderer,x_shoeR+50,y_shoeR-player_h-questionmark_pic,questionmark,questionmark_pic,questionmark_pic);
    if(leftFirix)
         texture(m_renderer,x_shoeL-50,y_shoeL-player_h-questionmark_pic,questionmark,questionmark_pic,questionmark_pic);
    rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
    texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
    texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
    my_line(m_renderer,x_scoreb+50+player_pic+5,y_scoreb-15+player_pic/2,powerLengthgLeft,0,15,255,0,0);
    my_line(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15+player_pic/2,powerLengthgRight,-3.141592,15,255,0,0);
    GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
    GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
    texture(m_renderer,0,HEIGHT-h_fire,fire,WIDTH,h_fire);
     texture(m_renderer,x_h,y_h,home,w_b,h_b);
    if(!paused)
    texture(m_renderer,x_p,y_p,pause,w_b,h_b);
    else
    texture(m_renderer,x_p,y_p,start,w_b,h_b);
    texture(m_renderer,x_r,y_r,restart,w_b,h_b);
//            if(goaled)
//            texture(m_renderer,150,150,goal,WIDTH-300,HEIGHT-300);
    SDL_RenderPresent( m_renderer );
    SDL_Delay(2);
    SDL_RenderClear( m_renderer );
}
void textureRendererTripleClone(SDL_Renderer *m_renderer, int font_size ,double angle,bool playerSide)
{
      int x_textL=x_scoreb+w_scoreb/2-103;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    int R=255,G=255,B=255,A=255;
    int w_f=60,h_f=60;
    string questionmark="questionmarks.png";
    string goal="goal!.png";
    string crown="crown.png";
    string pause="pause.png";
    string start="start.png";
    string home="home.png";
    string fire="powerIcon.png";
    string restart="restart.png";
    int questionmark_pic=70;
     currentTime = SDL_GetTicks()-startTime;
     if (currentTime > lastTime + 1000)
     lastTime = currentTime;
   if(currentTime/1000>=150)
   {
       continueGame=false;
       return;
   }
    stringstream ss;
    ss<<currentTime/1000;
    string timestr;
    ss>>timestr;
    texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
    texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
    texture(m_renderer,x_shoeL-50,y_shoeL-player_h,player1,player_w,player_h);
    texture(m_renderer,x_shoeR+50,y_shoeR-player_h,player2,player_w,player_h);
    texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
    texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
    write(m_renderer,x_scoreb+10,y_scoreb+h_scoreb+10,nameL,font_address_04,35,255,255,255,255,0,NONE);
    write(m_renderer,x_scoreb+w_scoreb-70,y_scoreb+h_scoreb+10,nameR,font_address_04,35,255,255,255,255,0,NONE);
     if(playerSide)
     {     texture(m_renderer,x_shoeR-w_shoe,y_shoeR,shoeR,w_shoe,h_shoe);
           texture(m_renderer,x_shoeR+w_shoe,y_shoeR,shoeR,w_shoe,h_shoe);
           texture(m_renderer,x_shoeR+50+w_shoe,y_shoeR-100,player2,player_w,player_h);
           texture(m_renderer,x_shoeR+50-w_shoe,y_shoeR-100,player2,player_w,player_h);
     }
     else
    {
          texture(m_renderer,x_shoeL+w_shoe,y_shoeL,shoeL,w_shoe,h_shoe);
          texture(m_renderer,x_shoeL-w_shoe,y_shoeL,shoeL,w_shoe,h_shoe);
          texture(m_renderer,x_shoeL-50-w_shoe,y_shoeL-100,player1,player_w,player_h);
          texture(m_renderer,x_shoeL-50+w_shoe,y_shoeL-100,player1,player_w,player_h);
    }
    if(!invisible)
    texture(m_renderer,x,y,ball,RADIOUS,RADIOUS);
    texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
    if(rightFiriz)
        texture(m_renderer,x_shoeR+50,y_shoeR-player_h-questionmark_pic,questionmark,questionmark_pic,questionmark_pic);
    if(leftFirix)
         texture(m_renderer,x_shoeL-50,y_shoeL-player_h-questionmark_pic,questionmark,questionmark_pic,questionmark_pic);
    rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
    write(m_renderer,WIDTH/2,y_scoreb+h_scoreb/2,timestr,font_address_04,font_size,0,0,0,255,angle,NONE);
    texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
    texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
    my_line(m_renderer,x_scoreb+50+player_pic+5,y_scoreb-15+player_pic/2,powerLengthgLeft,0,15,255,0,0);
    my_line(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15+player_pic/2,powerLengthgRight,-3.141592,15,255,0,0);
    texture(m_renderer,x_scoreb+50+player_pic+5+powerLengthgLeft-w_f/2,y_scoreb-15,fire,w_f,h_f);
    texture(m_renderer,w_scoreb-50-player_pic-powerLengthgRight+w_f/2,y_scoreb-15,fire,w_f,h_f);
    GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
    GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
    if(goalScoredRight)
    {
         texture(m_renderer,x_shoeR+50,y_shoeR-player_h-70,crown,70,70);
         //texture(m_renderer,)
    }
     texture(m_renderer,x_h,y_h,home,w_b,h_b);
    if(!paused)
    texture(m_renderer,x_p,y_p,start,w_b,h_b);
    else
    {
    texture(m_renderer,x_p,y_p,pause,w_b,h_b);
    write(m_renderer,100,200,"PAUSED!",font_address_04,45,190,50,50,255,0,NONE);
    }

    texture(m_renderer,x_r,y_r,restart,w_b,h_b);
    SDL_RenderPresent( m_renderer );
    SDL_Delay(2);
    SDL_RenderClear( m_renderer );
}
void ballDrop(SDL_Renderer *m_renderer,int font_size ,double angle, double velocity_x, double velocity,double acceleration,bool playerSide )
{
    double t;
    int y0=y;
    int R=355,G=255,B=255,A=255;
    bool side=playerSide;
    int last=SDL_GetTicks();
    int current;
    int x_textL=x_scoreb+w_scoreb/2-103;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    int x_e,y_e;
    for(t=0.1; t<=25 && y<=y0 ; t+=0.1)
    {
    y=( 0.5*acceleration*t*t+velocity*t)+y0;
    velocity+=acceleration*t;
    textureRenderer(m_renderer,font_size,angle );
    if(x<0 || x>WIDTH)
    velocity_x = -1*velocity_x;
    if(invisible)
    {
        current = SDL_GetTicks();
          if (current > last + 1000)
            {
              // printf("Report**: %d\n", current);
               last=current;
               invisibleDeltha++;
               //cout<<"in"<<invisibleDeltha<<endl;
          }
    }
      if(invisibleDeltha>=3)
          {
              invisibleDeltha=0;
              invisible=false;
          }
    //ball collision with the head of players
    if((x_shoeR+50-x)<RADIOUS && y<=y_shoeR && y>=y_shoeR-player_h &&!side)
    {
    velocity_x=-1*velocity_x;
    }
    if(x-x_shoeL+50<player_w && y<=y_shoeL && y>=y_shoeL-player_h && side)
    {
    velocity_x=-1*velocity_x;
    }
    // ball collision with goals
    if(x_gL-x<=RADIOUS && x_gL-x>0 && y>y_gL &&y<y_gL+h_goal)
     {
         velocity_x=-1*velocity_x;
     }
     if(x-x_gR<=RADIOUS && x-x_gR>0 && y>y_gR &&y<y_gR+h_goal)
     {
         velocity_x=-1*velocity_x;
     }
      if(y_gL-y<RADIOUS && y_gL-y>0 && x<x_gL+w_goal && x>x_gL)
     {
          t=0;
     velocity=-200;
     y0=y;
     }
      if(y_gR-y<RADIOUS && y_gR-y>0 && x<x_gR+w_goal && x>x_gR)
     {
         t=0;
     velocity=-200;
     y0=y;
     }

      //ball collision with players shoe
        if((x_shoeR-x)<=RADIOUS && (x_shoeR-x)>=0&& y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe &&!side )
        {
        velocity_x=-1*velocity_x;
        }
        if((x-x_shoeL)<=w_shoe&& x-x_shoeL>=0&& y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe && side)
        {
          velocity_x=-1*velocity_x;
        }
    //GOAL!!
    if( x_gL-x<=w_goal &&x_gL-x>=-RADIOUS/2 &&y>y_gL &&y<y_gL+h_goal)
        {
            GOAL_left++;
            GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
            SDL_RenderPresent(m_renderer);
            goaled=true;
        }
    if( x-x_gR<=w_goal &&x-x_gR>=RADIOUS/2 &&y>y_gL &&!goaled&&y<y_gL+h_goal)
        {
           GOAL_right++;
           GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
           SDL_RenderPresent(m_renderer);
            goaled=true;
        }
        if(goaled)
            {
        Mix_Chunk *goalscored=Mix_LoadWAV("goalscored.wav");
        Mix_PlayChannel(-1,goalscored,0);
        y=Y0;
        x=WIDTH/2;
        int  k=1.5;
        int dy=18;
        y_shoeR=GROUND,y_shoeL=GROUND;
        x_shoeR=x0_shoeR,x_shoeL=x0_shoeL;
        while(y<GROUND)
         {
            y+=dy;
            dy*=k;
             textureRenderer(m_renderer,font_size,angle );
         }
          int current,last=SDL_GetTicks(),d=0;
          while(d<3)
          {
               current = SDL_GetTicks();
               if (current > last + 1000)
            {
                  // printf("Report**: %d\n", current);
                   last=current;
                   d++;
                   //cout<<"in"<<invisibleDeltha<<endl;
              }
              textureRenderer(m_renderer,font_size,angle);
          }
        Mix_Chunk *goalScored=Mix_LoadWAV("goaled.wav");
        Mix_PlayChannel(-1,goalScored,0);
      if(GOAL_left==4&&GOAL_right==4)
            continueGame=false;
        if(GOAL_right==5||GOAL_left==5)
            continueGame=false;
        goaled=false;
        break;
        }
      if(side)
        x -= velocity_x;
    else
    x += velocity_x;
    SDL_PollEvent(e);
    if(e-> type==SDL_KEYDOWN )
    {
        switch(e->key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    return;
                case SDLK_RIGHT:
                    if(!rightFiriz)
                     x_shoeR+=player_vel2;
                     break;
                case SDLK_UP:
                     if(!rightFiriz)
                     y_shoeR-=player_vel2;
                     break;
                case SDLK_DOWN:
                     if(!rightFiriz)
                     y_shoeR+=player_vel2;
                     break;
                case SDLK_LEFT:
                     if(!rightFiriz)
                    x_shoeR-=player_vel2;
                break;
                 case SDLK_j:
                if(!rightFiriz)
                {
                    int velocity_j=velocity_y0;
                    double  y_shoeR0=y_shoeR,t;
                    for(t=0.1; t<=25 && y_shoeR<=y_shoeR0 ; t+=0.1)
                    {
                        {
                            y_shoeR=( 0.5*acceleration*t*t+velocity_j*t)+y_shoeR0;
                            velocity_j+=acceleration*t;
                            textureRenderer(m_renderer,font_size,angle);
                        }
                        x_shoeR-=velocity_x0;
                    }
                }
                break;
            case SDLK_e:
                if(!leftFirix)
                {
                    int velocity_j=velocity_y0;
                    double  y_shoeL0=y_shoeL,t;
                    for(t=0.1; t<=25 && y_shoeL<=y_shoeL0 ; t+=0.1)
                    {
                        {
                            y_shoeL=( 0.5*acceleration*t*t+velocity_j*t)+y_shoeL0;
                            velocity_j+=acceleration*t;
                            textureRenderer(m_renderer,font_size,angle);
                        }
                        x_shoeL+=velocity_x;
                    }
                }
                break;
                case SDLK_d:
                    if(!leftFirix)
                    x_shoeL+=player_vel1;
                    break;
                case SDLK_a:
                    if(!leftFirix)
                    x_shoeL-=player_vel1;
                    break;
                     case SDLK_w:
                    if(!leftFirix)
                    y_shoeL-=player_vel1;
                    break;
                     case SDLK_s:
                    if(!leftFirix)
                    y_shoeL+=player_vel1;
                    break;
                     case SDLK_p:
                          if(!rightFiriz)
                        {
                             if(powerLengthgRight==290)
                                power_R=true;
                            if(PowerRight==1)
                            TripleClone(m_renderer,font_size ,angle, velocity_x,velocity,acceleration,1);
                        }
                        break;
                    case SDLK_q:
                        if(!leftFirix)
                        {
                            if(powerLengthgLeft==290)
                                power_L=true;
                            if(powerLeft==1)
                            TripleClone(m_renderer,font_size ,angle, velocity_x,velocity,acceleration,0 );
                        }
                    break;

            }
        }
    if(e->type==SDL_MOUSEBUTTONDOWN)
       {
        x_e=e->motion.x;
        y_e=e->motion.y;
        if(x_e>=x_h && x_e<=x_h+w_b &&y_e<=y_h+h_b && y_e>=y_h &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
        {
            nameL="";
            nameR="";
            getnamed=false;
            GOAL_left=0;
            GOAL_left=0;
            //cout<<"Home";
            home=true;
            powerLengthgRight=10;
            powerLengthgRight=10;
            continueGame=false;
            startGame=false;
           break;
        }

         if(x_e>=x_p && x_e<=x_p+w_b &&y_e<=y_p+h_b && y_e>=y_p &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
        {
           Mix_Chunk *click=Mix_LoadWAV("click.wav");
           Mix_PlayChannel(-1,click,0);
           Mix_Music *crowd=Mix_LoadMUS("crowd.mp3");
           Mix_Pause(Mix_PlayMusic(crowd,-1));
           paused=true;
           pause(m_renderer);
           Mix_Resume(Mix_PlayMusic(crowd,-1));
        }
        if(x_e>=x_r && x_e<=x_r+w_b &&y_e<=y_r+h_b && y_e>=y_r &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
        {
           Mix_Chunk *click=Mix_LoadWAV("click.wav");
           Mix_PlayChannel(-1,click,0);
           restart(m_renderer);
        }
      }
    }
    y=GROUND;
    return;
}
void punch(SDL_Renderer *m_renderer,int font_size ,double angle, double velocity_x,bool playerSide )
{
    int current,last=SDL_GetTicks();
    int punchdeltha=0;
    int dx=2;
    current = SDL_GetTicks();
    int x_pu,y_pu;
    bool leftHit=false;
    bool rightHit=false;
    int x_textL=x_scoreb+w_scoreb/2-103;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    if(playerSide)
    {
        x_pu=x_shoeR-70;
        y_pu=y_shoeR;
    }
    else
    {
        x_pu=x_shoeL+w_shoe;
        y_pu=y_shoeL;
    }
    textureRendererPunch(m_renderer,font_size,angle,playerSide,x_pu,y_pu);
    while(punchdeltha<=5 && velocity_x>0)
    {
        current=SDL_GetTicks();
       if (current > last + 1000) {
            printf("Report: %d\n", current);
            last = current;
            punchdeltha++;
            if(rightFiriz || leftFirix)
                firizDeltha++;
                if(firizDeltha>=3)
                {
                    rightFiriz=false;
                    leftFirix=false;
                }
            cout<<"p"<<punchdeltha<<endl;
          }
    if( (( x_shoeR+50-x_pu<RADIOUS && y<=y_shoeR && y>=y_shoeR-player_h ) ||((x_shoeR-x_pu)<=RADIOUS && (x_shoeR-x_pu)>=0&& y_p>=y_shoeR-RADIOUS && y_pu<=y_shoeR+h_shoe) || ((x_shoeR-x_pu)<=RADIOUS && (x_shoeR-x_p)>=0&&y_shoeR-y_p<=RADIOUS &&y_shoeR-y_p>=0 ))&&!playerSide &&!rightHit )
        {
        x_shoeR+=150;
        dx*=2;
        rightHit=true;
        rightFiriz=true;
        firizDeltha=0;
        }
    if( ((x_pu-x_shoeL+50<player_w && y_pu<=y_shoeL && y_pu>=y_shoeL-player_h) || ((x_pu-x_shoeL)<=w_shoe&& x_pu-x_shoeL>=0&& y_pu>=y_shoeR-RADIOUS && y_pu<=y_shoeR+h_shoe) || ((x_pu-x_shoeL)<=w_shoe&& x_pu-x_shoeL>=0&& y_shoeL-y_pu<=RADIOUS &&y_shoeL-y_pu>=0 ) )&& playerSide&& !leftHit)
        {
            x_shoeL-=150;
            dx*=2;
            leftHit=true;
            leftFirix=true;
            firizDeltha=0;
        }
            textureRendererPunch(m_renderer,font_size,angle,playerSide,x_pu,y_pu);
        if(playerSide)
        x_pu -= velocity_x;
        else
        x_pu += velocity_x;
         cout<<"k";
        //velocity_x-=dx;
    }
cout<<punchdeltha;
}
void ballDropKichFireBall(SDL_Renderer *m_renderer,int font_size ,double angle, double velocity_x, double velocity,double acceleration,bool playerSide )
{
    double t;
    int y0=y;
    int R=355,G=255,B=255,A=255;
    int dx=2;
    bool side=playerSide;
    int last;
    int current;
    bool startTiming=false;
    int x_textL=x_scoreb+w_scoreb/2-103;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    int x_e,y_e;
    while (velocity_x>0)
    {
    velocity_x-=dx;
    textureRendererKichFireBall(m_renderer,font_size,angle,side );
    if(x<0 || x>WIDTH)
    velocity_x = -1*velocity_x;
    //ball collision with the head of players
    if( (( x_shoeR+50-x<RADIOUS && y<=y_shoeR && y>=y_shoeR-player_h ) ||((x_shoeR-x)<=RADIOUS && (x_shoeR-x)>=0&& y>=y_shoeR-RADIOUS && y<=y_shoeR+h_shoe) || ((x_shoeR-x)<=RADIOUS && (x_shoeR-x)>=0&&y_shoeR-y<=RADIOUS &&y_shoeR-y>=0 ))&&!side )
    {
    SDL_Delay(50);
    x_shoeR+=150;
    dx*=2;
    rightFiriz=true;
    startTiming=true;
    last=SDL_GetTicks();
    }
    if( ((x-x_shoeL+50<player_w && y<=y_shoeL && y>=y_shoeL-player_h) || ((x-x_shoeL)<=w_shoe&& x-x_shoeL>=0&& y>=y_shoeR-RADIOUS && y<=y_shoeR+h_shoe) || ((x-x_shoeL)<=w_shoe&& x-x_shoeL>=0&& y_shoeL-y<=RADIOUS &&y_shoeL-y>=0 ) )&& side)
    {
        x_shoeL-=150;
        dx*=2;
        leftFirix=true;
        startTiming=true;
        last=SDL_GetTicks();
    }
    if(startTiming)
    {
          current = SDL_GetTicks();
          if (current > last + 1000)
            {
               printf("Report**: %d\n", current);
               last=current;
               firizDeltha++;
               cout<<"f"<<firizDeltha<<endl;
          }
    }
     if(firizDeltha>=3)
              {
                  rightFiriz=false;
                  leftFirix=false;
                  firizDeltha=0;
                  startTiming=false;
              }
    // ball collision with goals
    if(x_gL-x<=RADIOUS && x_gL-x>0 && y>y_gL &&y<y_gL+h_goal)
     {
         velocity_x=-1*velocity_x;
     }
     if(x-x_gR<=RADIOUS && x-x_gR>0 && y>y_gR &&y<y_gR+h_goal)
     {
         velocity_x=-1*velocity_x;
     }
      if(y_gL-y<RADIOUS && y_gL-y>0 && x<x_gL+w_goal && x>x_gL)
     {
          t=0;
     velocity=-200;
     y0=y;
     }
      if(y_gR-y<RADIOUS && y_gR-y>0 && x<x_gR+w_goal && x>x_gR)
     {
         t=0;
     velocity=-200;
     y0=y;
     }
    //GOAL!!
    if( x_gL-x<=w_goal &&x_gL-x>=-RADIOUS/2 &&y>y_gL &&y<y_gL+h_goal)
        {
            GOAL_left++;
            GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
            SDL_RenderPresent(m_renderer);
            goaled=true;
        }
    if( x-x_gR<=w_goal &&x-x_gR>=RADIOUS/2 &&y>y_gL &&!goaled&&y<y_gL+h_goal)
        {
           GOAL_right++;
           GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
           SDL_RenderPresent(m_renderer);
            goaled=true;
        }
        if(goaled)
            {
        Mix_Chunk *goalscored=Mix_LoadWAV("goalscored.wav");
        Mix_PlayChannel(-1,goalscored,0);
        y=Y0;
        x=WIDTH/2;
        int  k=1.5;
        int dy=18;
        y_shoeR=GROUND,y_shoeL=GROUND;
        x_shoeR=x0_shoeR,x_shoeL=x0_shoeL;
        while(y<GROUND)
         {

            y+=dy;
            dy*=k;
             textureRenderer(m_renderer,font_size,angle );
         }
        int current,last=SDL_GetTicks(),d=0;
          while(d<3)
          {
               current = SDL_GetTicks();
               if (current > last + 1000)
            {
                  // printf("Report**: %d\n", current);
                   last=current;
                   d++;
                   //cout<<"in"<<invisibleDeltha<<endl;
              }
              textureRenderer(m_renderer,font_size,angle);
          }
        Mix_Chunk *goalScored=Mix_LoadWAV("goaled.wav");
        Mix_PlayChannel(-1,goalScored,0);
        if(GOAL_left==4&&GOAL_right==4)
        continueGame=false;
        if(GOAL_right==5||GOAL_left==5)
            continueGame=false;
        while(y<GROUND)
         {

            y+=dy;
            dy*=k;
            textureRendererKichFireBall(m_renderer,font_size,angle,side );
         }
         goaled=false;
        break;
        }
    if(side)
        x -= velocity_x;
    else
    x += velocity_x;
    SDL_PollEvent(e);
    if(e-> type==SDL_KEYDOWN )
    {
        switch(e->key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    return;
                case SDLK_RIGHT:
                    if(!rightFiriz)
                     x_shoeR+=player_vel2;
                     break;
                case SDLK_UP:
                     if(!rightFiriz)
                     y_shoeR-=player_vel2;
                     break;
                case SDLK_DOWN:
                     if(!rightFiriz)
                     y_shoeR+=player_vel2;
                     break;
                case SDLK_LEFT:
                     if(!rightFiriz)
                    x_shoeR-=player_vel2;
                break;
                case SDLK_d:
                    if(!leftFirix)
                    x_shoeL+=player_vel1;
                    break;
                     case SDLK_j:
                if(!rightFiriz)
                {
                    int velocity_j=velocity_y0;
                    double  y_shoeR0=y_shoeR,t;
                    for(t=0.1; t<=25 && y_shoeR<=y_shoeR0 ; t+=0.1)
                    {
                        {
                            y_shoeR=( 0.5*acceleration*t*t+velocity_j*t)+y_shoeR0;
                            velocity_j+=acceleration*t;
                            textureRenderer(m_renderer,font_size,angle);
                        }
                        x_shoeR-=velocity_x;
                    }
                }
                break;
            case SDLK_e:
                if(!leftFirix)
                {
                    int velocity_j=velocity_y0;
                    double  y_shoeL0=y_shoeL,t;
                    for(t=0.1; t<=25 && y_shoeL<=y_shoeL0 ; t+=0.1)
                    {
                        {
                            y_shoeL=( 0.5*acceleration*t*t+velocity_j*t)+y_shoeL0;
                            velocity_j+=acceleration*t;
                            textureRenderer(m_renderer,font_size,angle);
                        }
                        x_shoeL+=velocity_x;
                    }
                }
                break;
                case SDLK_a:
                    if(!leftFirix)
                    x_shoeL-=player_vel1;
                    break;
                     case SDLK_w:
                    if(!leftFirix)
                    y_shoeL-=player_vel1;
                    break;
                     case SDLK_s:
                    if(!leftFirix)
                    y_shoeL+=player_vel1;
                    break;
                     case SDLK_p:
                          if(!rightFiriz)
                        {
                             if(powerLengthgRight==290)
                                power_R=true;
                            if(PowerRight==1)
                            TripleClone(m_renderer,font_size ,angle, velocity_x,velocity,acceleration,1);
                        }
                        break;
                    case SDLK_q:
                        if(!leftFirix)
                        {
                            if(powerLengthgLeft==290)
                                power_L=true;
                            if(powerLeft==1)
                            TripleClone(m_renderer,font_size ,angle, velocity_x,velocity,acceleration,0 );
                        }
                    break;

            }
        }
            if(e->type==SDL_MOUSEBUTTONDOWN)
    {
        x_e=e->motion.x;
        y_e=e->motion.y;
        if(x_e>=x_h && x_e<=x_h+w_b &&y_e<=y_h+h_b && y_e>=y_h &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
        {
            nameL="";
            nameR="";
            getnamed=false;
            GOAL_left=0;
            GOAL_left=0;
            //cout<<"Home";
            home=true;
            powerLengthgRight=10;
            powerLengthgRight=10;
            continueGame=false;
            startGame=false;
           break;
        }

         if(x_e>=x_p && x_e<=x_p+w_b &&y_e<=y_p+h_b && y_e>=y_p &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
        {
           Mix_Chunk *click=Mix_LoadWAV("click.wav");
           Mix_PlayChannel(-1,click,0);
           Mix_Music *crowd=Mix_LoadMUS("crowd.mp3");
           Mix_Pause(Mix_PlayMusic(crowd,-1));
           paused=true;
           pause(m_renderer);
           Mix_Resume(Mix_PlayMusic(crowd,-1));
        }
        if(x_e>=x_r && x_e<=x_r+w_b &&y_e<=y_r+h_b && y_e>=y_r &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
        {
           Mix_Chunk *click=Mix_LoadWAV("click.wav");
           Mix_PlayChannel(-1,click,0);
           restart(m_renderer);
        }
      }
    }
    startTiming=false;
    y=GROUND;
    return;
}
void ballDropTripleClone(SDL_Renderer *m_renderer,int font_size ,double angle, double velocity_x, double velocity,double acceleration,bool playerSide,bool TripleCloneSide )
{
    double t;
    int y0=y;
    int R=355,G=255,B=255,A=255;
    bool side=playerSide;
    int x_textL=x_scoreb+w_scoreb/2-103;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    int x_e,y_e;
    for(t=0.1; t<=25 && y<=y0 ; t+=0.1)
    {
    y=( 0.5*acceleration*t*t+velocity*t)+y0;
    velocity+=acceleration*t;
    textureRendererTripleClone(m_renderer,font_size,angle,TripleCloneSide);
    if(x<0 || x>WIDTH)
    velocity_x = -1*velocity_x;
    //ball collision with the head of players
    if((x_shoeR+50-x)<RADIOUS &&(x_shoeR+50-x)>=0&& y<=y_shoeR && y>=y_shoeR-player_h &&!side)
    {
    velocity_x=-1*velocity_x;
    }
    if(TripleCloneSide)
    {
        if((x_shoeR+50+w_shoe-x)<RADIOUS &&(x_shoeR+50+w_shoe-x)>=0&& y<=y_shoeR && y>=y_shoeR-player_h &&!side)
        {
        velocity_x=-1*velocity_x;
        }
        if((x_shoeR+50-w_shoe-x)<RADIOUS &&(x_shoeR+50-w_shoe-x)>=0&& y<=y_shoeR && y>=y_shoeR-player_h &&!side)
        {
        velocity_x=-1*velocity_x;
        }

    }
    if(x-x_shoeL+50<player_w &&x-x_shoeL+50>=0&& y<=y_shoeL && y>=y_shoeL-player_h && side)
    {
    velocity_x=-1*velocity_x;
    }
    if(!TripleCloneSide)
    {
        if(x-x_shoeL-w_shoe+50<player_w &&x-x_shoeL-w_shoe+50>=0&& y<=y_shoeL && y>=y_shoeL-player_h && side)
            {
            velocity_x=-1*velocity_x;
            }
         if(x-x_shoeL+w_shoe+50<player_w &&x-x_shoeL+w_shoe+50>=0&& y<=y_shoeL && y>=y_shoeL-player_h && side)
            {
            velocity_x=-1*velocity_x;
            }
    }
    // ball collision with goals
    if(x_gL-x<=RADIOUS && x_gL-x>0 && y>y_gL &&y<y_gL+h_goal)
     {
         velocity_x=-1*velocity_x;
     }
     if(x-x_gR<=RADIOUS && x-x_gR>0 && y>y_gR &&y<y_gR+h_goal)
     {
         velocity_x=-1*velocity_x;
     }
      if(y_gL-y<RADIOUS && y_gL-y>0 && x<x_gL+w_goal && x>x_gL)
     {
          t=0;
     velocity=-200;
     y0=y;
     }
      if(y_gR-y<RADIOUS && y_gR-y>0 && x<x_gR+w_goal && x>x_gR)
     {
         t=0;
     velocity=-200;
     y0=y;
     }

      //ball collision with players shoe
        if((x_shoeR-x)<=RADIOUS && (x_shoeR-x)>=0&& y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe &&!side )
        {
        velocity_x=-1*velocity_x;
        }
        if(TripleCloneSide)
        {
            if((x_shoeR+w_shoe-x)<=RADIOUS && (x_shoeR+w_shoe-x)>=0&& y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe &&!side )
            {
            velocity_x=-1*velocity_x;
            }
            if((x_shoeR-w_shoe-x)<=RADIOUS && (x_shoeR-w_shoe-x)>=0&& y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe &&!side )
            {
            velocity_x=-1*velocity_x;
            }
        }
        if((x-x_shoeL)<=w_shoe&& x-x_shoeL>=0&& y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe && side)
        {
          velocity_x=-1*velocity_x;
        }
        if(!TripleCloneSide)
        {
            if((x-x_shoeL-w_shoe)<=w_shoe&& x-x_shoeL-w_shoe>=0&& y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe && side)
            {
              velocity_x=-1*velocity_x;
            }
            if((x-x_shoeL+w_shoe)<=w_shoe&& x-x_shoeL+w_shoe>=0&& y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe && side)
            {
              velocity_x=-1*velocity_x;
            }
        }

    //GOAL!!
    if( x_gL-x<=w_goal &&x_gL-x>=-RADIOUS/2 &&y>y_gL &&y<y_gL+h_goal)
        {
            GOAL_left++;
            GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
            SDL_RenderPresent(m_renderer);
            goaled=true;
        }
    if( x-x_gR<=w_goal &&x-x_gR>=RADIOUS/2 &&y>y_gL &&!goaled&&y<y_gL+h_goal)
        {
           GOAL_right++;
           GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
           SDL_RenderPresent(m_renderer);
            goaled=true;
        }
        if(goaled)
            {
        Mix_Chunk *goalscored=Mix_LoadWAV("goalscored.wav");
        Mix_PlayChannel(-1,goalscored,0);
        y=Y0;
        x=WIDTH/2;
        int  k=1.5;
        int dy=18;
        y_shoeR=GROUND,y_shoeL=GROUND;
        x_shoeR=x0_shoeR,x_shoeL=x0_shoeL;
        while(y<GROUND)
         {
            y+=dy;
            dy*=k;
            textureRendererTripleClone(m_renderer,font_size,angle,TripleCloneSide );
         }
          int current,last=SDL_GetTicks(),d=0;
          while(d<3)
          {
               current = SDL_GetTicks();
               if (current > last + 1000)
            {
                  // printf("Report**: %d\n", current);
                   last=current;
                   d++;
                   //cout<<"in"<<invisibleDeltha<<endl;
              }
              textureRendererTripleClone(m_renderer,font_size,angle,TripleCloneSide);
          }
        Mix_Chunk *goalScored=Mix_LoadWAV("goaled.wav");
        Mix_PlayChannel(-1,goalScored,0);
      if(GOAL_left==4&&GOAL_right==4)
            continueGame=false;
      if(GOAL_right==5||GOAL_left==5)
            continueGame=false;
        goaled=false;
        break;
        }
      if(side)
        x -= velocity_x;
    else
    x += velocity_x;
    SDL_PollEvent(e);
    if(e-> type==SDL_KEYDOWN )
    {
        switch(e->key.keysym.sym)
            {
                case SDLK_ESCAPE:
                    return;
                case SDLK_RIGHT:
                    if(!rightFiriz)
                     x_shoeR+=player_vel2;
                     break;
                case SDLK_UP:
                     if(!rightFiriz)
                     y_shoeR-=player_vel2;
                     break;
                case SDLK_DOWN:
                     if(!rightFiriz)
                     y_shoeR+=player_vel2;
                     break;
                case SDLK_LEFT:
                     if(!rightFiriz)
                    x_shoeR-=player_vel2;
                break;
                case SDLK_j:
                if(!rightFiriz)
                {
                    int velocity_j=velocity_y0;
                    double  y_shoeR0=y_shoeR,t;
                    for(t=0.1; t<=25 && y_shoeR<=y_shoeR0 ; t+=0.1)
                    {
                        {
                            y_shoeR=( 0.5*acceleration*t*t+velocity_j*t)+y_shoeR0;
                            velocity_j+=acceleration*t;
                            textureRenderer(m_renderer,font_size,angle);
                        }
                        x_shoeR-=velocity_x0;
                    }
                }
                break;
            case SDLK_e:
                if(!leftFirix)
                {
                    int velocity_j=velocity_y0;
                    double  y_shoeL0=y_shoeL,t;
                    for(t=0.1; t<=25 && y_shoeL<=y_shoeL0 ; t+=0.1)
                    {
                        {
                            y_shoeL=( 0.5*acceleration*t*t+velocity_j*t)+y_shoeL0;
                            velocity_j+=acceleration*t;
                            textureRenderer(m_renderer,font_size,angle);
                        }
                        x_shoeL+=velocity_x0;
                    }
                }
                break;
                case SDLK_d:
                    if(!leftFirix)
                    x_shoeL+=player_vel1;
                    break;
                case SDLK_a:
                    if(!leftFirix)
                    x_shoeL-=player_vel1;
                    break;
                     case SDLK_w:
                    if(!leftFirix)
                    y_shoeL-=player_vel1;
                    break;
                     case SDLK_s:
                    if(!leftFirix)
                    y_shoeL+=player_vel1;
                    break;
                     case SDLK_p:
                          if(!rightFiriz)
                        {
                             if(powerLengthgRight==290)
                                power_R=true;
                        }
                        break;
                    case SDLK_q:
                        if(!leftFirix)
                        {
                            if(powerLengthgLeft==290)
                                power_L=true;
                        }
                    break;

            }
        }
    if(e->type==SDL_MOUSEBUTTONDOWN)
       {
        x_e=e->motion.x;
        y_e=e->motion.y;
        if(x_e>=x_h && x_e<=x_h+w_b &&y_e<=y_h+h_b && y_e>=y_h &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
        {
            nameL="";
            nameR="";
            getnamed=false;
            GOAL_left=0;
            GOAL_left=0;
            //cout<<"Home";
            home=true;
            powerLengthgRight=10;
            powerLengthgRight=10;
            continueGame=false;
            startGame=false;
           break;
        }

         if(x_e>=x_p && x_e<=x_p+w_b &&y_e<=y_p+h_b && y_e>=y_p &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
        {

           Mix_Chunk *click=Mix_LoadWAV("click.wav");
           Mix_PlayChannel(-1,click,0);
           Mix_Music *crowd=Mix_LoadMUS("crowd.mp3");
           Mix_Pause(Mix_PlayMusic(crowd,-1));
           paused=true;
           pause(m_renderer);
           Mix_Resume(Mix_PlayMusic(crowd,-1));
        }
        if(x_e>=x_r && x_e<=x_r+w_b &&y_e<=y_r+h_b && y_e>=y_r &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
        {
           Mix_Chunk *click=Mix_LoadWAV("click.wav");
           Mix_PlayChannel(-1,click,0);
          restart(m_renderer);
        }
      }
    }
    y=GROUND;
    return;
}
void TripleClone(SDL_Renderer *m_renderer,int font_size ,double angle, int velocity_x, int velocity,int acceleration,bool playerSide )//1 for R 0for L
{
    int x_textL=x_scoreb+w_scoreb/2-103;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    int TripleCloneDelta=0;
    int last=SDL_GetTicks(),current;
    while(TripleCloneDelta<=8)
     {
    current=SDL_GetTicks();
    if (current > last + 1000) {
    last = current;
    TripleCloneDelta++;
    }
    SDL_PollEvent(e);
    if(e-> type==SDL_KEYDOWN )
     {
        switch(e->key.keysym.sym)
         {
            case SDLK_ESCAPE:
                return;
            case SDLK_RIGHT:
                if(!rightFiriz)
                 x_shoeR+=player_vel2;
                 break;
            case SDLK_UP:
                 if(!rightFiriz)
                 y_shoeR-=player_vel2;
                 break;
            case SDLK_DOWN:
                 if(!rightFiriz)
                 y_shoeR+=player_vel2;
                 break;
            case SDLK_LEFT:
                 if(!rightFiriz)
                x_shoeR-=player_vel2;
            case SDLK_o:
                if(!rightFiriz)
                jumpR=true;
                break;
                 case SDLK_j:
                if(!rightFiriz)
                {
                    int velocity_j=velocity_y0;
                    double  y_shoeR0=y_shoeR,t;
                    for(t=0.1; t<=25 && y_shoeR<=y_shoeR0 ; t+=0.1)
                    {
                        {
                            y_shoeR=( 0.5*acceleration*t*t+velocity_j*t)+y_shoeR0;
                            velocity_j+=acceleration*t;
                            textureRenderer(m_renderer,font_size,angle);
                        }
                        x_shoeR-=velocity_x;
                    }
                }
                break;
            case SDLK_e:
                if(!leftFirix)
                {
                    int velocity_j=velocity_y0;
                    double  y_shoeL0=y_shoeL,t;
                    for(t=0.1; t<=25 && y_shoeL<=y_shoeL0 ; t+=0.1)
                    {
                        {
                            y_shoeL=( 0.5*acceleration*t*t+velocity_j*t)+y_shoeL0;
                            velocity_j+=acceleration*t;
                            textureRenderer(m_renderer,font_size,angle);
                        }
                        x_shoeL+=velocity_x;
                    }
                }
                break;
            case SDLK_z:
                if(!leftFirix)
                jumpL=true;
                break;
            case SDLK_d:
                if(!leftFirix)
                x_shoeL+=player_vel1;
                break;
            case SDLK_a:
                if(!leftFirix)
                x_shoeL-=player_vel1;
                break;
            case SDLK_w:
                if(!leftFirix)
                y_shoeL-=player_vel1;
                break;
            case SDLK_s:
                if(!leftFirix)
                y_shoeL+=player_vel1;
                break;
            case SDLK_p:
                if(!rightFiriz)
                    {
                       if(powerLengthgRight==290)
                            power_R=true;
                    }
                    break;
            case SDLK_q:
                if(!leftFirix)
                    {
                        if(powerLengthgLeft==290)
                            power_L=true;
                   }
                break;
         }
    }
    int x_e,y_e;
    if(e->type==SDL_MOUSEBUTTONDOWN)
     {
        x_e=e->motion.x;
        y_e=e->motion.y;
        if(x_e>=x_h && x_e<=x_h+w_b &&y_e<=y_h+h_b && y_e>=y_h &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
         {
            Mix_Chunk *click=Mix_LoadWAV("click.wav");
            Mix_PlayChannel(-1,click,0);
            nameL="";
            nameR="";
            getnamed=false;
            GOAL_left=0;
            GOAL_left=0;
            home=true;
            powerLengthgRight=10;
            powerLengthgRight=10;
            continueGame=false;
            startGame=false;
            break;
         }

         if(x_e>=x_p && x_e<=x_p+w_b &&y_e<=y_p+h_b && y_e>=y_p &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
          {
           Mix_Chunk *click=Mix_LoadWAV("click.wav");
           Mix_PlayChannel(-1,click,0);
           Mix_Music *crowd=Mix_LoadMUS("crowd.mp3");
           Mix_Pause(Mix_PlayMusic(crowd,-1));
           paused=true;
           pause(m_renderer);
           Mix_Resume(Mix_PlayMusic(crowd,-1));
          }
        if(x_e>=x_r && x_e<=x_r+w_b &&y_e<=y_r+h_b && y_e>=y_r &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
          {
        Mix_Chunk *click=Mix_LoadWAV("click.wav");
        Mix_PlayChannel(-1,click,0);
        restart(m_renderer);
          }
     }
    textureRendererTripleClone(m_renderer,font_size,angle,playerSide );

    //right player simple drop
    if((x_shoeR-x)<=RADIOUS && (x_shoeR-x)>=RADIOUS-10&&y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe)
    {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,velocity, acceleration ,1,playerSide);//1 for R 0 for L;
    }
    //right player simple drop triple Clone
    if(playerSide)
    {
         if((x_shoeR+w_shoe-x)<=RADIOUS && (x_shoeR+w_shoe-x)>=RADIOUS-10&&y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe)
            {
                Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
                Mix_PlayChannel(-1,ballkick,0);
                ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,1 ,playerSide);//1 for R 0 for L;
            }
            if((x_shoeR-w_shoe-x)<=RADIOUS && (x_shoeR-w_shoe-x)>=RADIOUS-10&&y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe)
            {
                Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
                Mix_PlayChannel(-1,ballkick,0);
                ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,1 ,playerSide);//1 for R 0 for L;
            }

    }
    //left player Simple ball drop
    if((x-x_shoeL)<=w_shoe&& x-x_shoeL>=RADIOUS-5&& y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe )
     {
         cout<<"1";
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,0,playerSide );//1 for R 0 for L
     }
     //left player Simple ball drop Triple clone
     if(!playerSide)
    {
          if((x-x_shoeL-w_shoe)<=w_shoe&& x-x_shoeL-w_shoe>=RADIOUS-5&& y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe)
             {
                Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
                Mix_PlayChannel(-1,ballkick,0);
                ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,0,playerSide );//1 for R 0 for L
             }
        if((x-x_shoeL+w_shoe)<=w_shoe&& x-x_shoeL+w_shoe>=RADIOUS-5&& y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe )
         {
            Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
            Mix_PlayChannel(-1,ballkick,0);
            ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,velocity, acceleration,0,playerSide );//1 for R 0 for L
         }

    }
      //right player upward ball drop
    if((x_shoeR-x)<=w_shoe-RADIOUS && (x_shoeR-x)>=0 &&y_shoeR-y<=RADIOUS && y_shoeR-y>=RADIOUS/2 && !playerSide)
     {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,4*velocity,0.75*acceleration,1 ,playerSide);//1 for R 0 for L
     }
     //right player upward ball drop Triple clone
     if(playerSide)
     {
          if((x_shoeR+w_shoe-x)<=w_shoe-RADIOUS && (x_shoeR+w_shoe-x)>=0 &&y_shoeR-y<=RADIOUS && y_shoeR-y>=RADIOUS/2 && !playerSide)
         {
            Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
            Mix_PlayChannel(-1,ballkick,0);
            ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,4*velocity,0.75*acceleration,1 ,playerSide);//1 for R 0 for L
         }
         if((x_shoeR-w_shoe-x)<=w_shoe-RADIOUS && (x_shoeR-w_shoe-x)>=0 &&y_shoeR-y<=RADIOUS && y_shoeR-y>=RADIOUS/2 && !playerSide)
         {
            Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
            Mix_PlayChannel(-1,ballkick,0);
            ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,4*velocity,0.75*acceleration,1,playerSide );//1 for R 0 for L
         }
     }
    //left player upward ball drop
    if((x-x_shoeL)<=w_shoe-RADIOUS&& x-x_shoeL>=0&& y_shoeL-y<=RADIOUS &&y_shoeL-y>=RADIOUS/2 && playerSide )
    {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,4*velocity,0.75* acceleration,0,playerSide );//1 for R 0 for L
    }
    if(!playerSide)
    {
        if((x-x_shoeL-w_shoe)<=w_shoe-RADIOUS&& x-x_shoeL-w_shoe>=0&& y_shoeL-y<=RADIOUS &&y_shoeL-y>=RADIOUS/2 && playerSide )
        {
            Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
            Mix_PlayChannel(-1,ballkick,0);
            ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,4*velocity,0.75* acceleration,0,playerSide );//1 for R 0 for L
        }
         if((x-x_shoeL+w_shoe)<=w_shoe-RADIOUS&& x-x_shoeL+w_shoe>=0&& y_shoeL-y<=RADIOUS &&y_shoeL-y>=RADIOUS/2 && playerSide )
        {
            Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
            Mix_PlayChannel(-1,ballkick,0);
            ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,4*velocity,0.75* acceleration,0,playerSide );//1 for R 0 for L
        }

    }
        // right player backward drop
     if((-x_shoeR+x)<=RADIOUS && (-x_shoeR+x)>=RADIOUS-5&&y_shoeR-y<=RADIOUS && y+RADIOUS/2<=y_shoeR+h_shoe && !playerSide)
      {
        Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
        Mix_PlayChannel(-1,ballkick,0);
        ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,0.5*velocity, acceleration,0,playerSide );
      }
    //left player backward drop
    if((-x+x_shoeL)<=w_shoe&& -x+x_shoeL>=RADIOUS-5&&y_shoeL-y<=RADIOUS && y+RADIOUS/2<=y_shoeL+h_shoe && playerSide)
     {
         Mix_Chunk *ballkick=Mix_LoadWAV("ballkick.wav");
         Mix_PlayChannel(-1,ballkick,0);
         ballDropTripleClone(m_renderer,font_size ,angle,velocity_x,0.5*velocity, acceleration,1,playerSide );//1 for R 0 for L
     }
      //GOAL!!
    if( x_gL-x<=w_goal &&x_gL-x>=-RADIOUS/2 &&y>y_gL &&y<y_gL+h_goal)
        {
            GOAL_left++;
            GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,255,255,255,255,angle,NONE,GOAL_left);
            SDL_RenderPresent(m_renderer);
            goaled=true;
            goalScoredRight=true;
        }
    if( x-x_gR<=w_goal &&x-x_gR>=RADIOUS/2 &&y>y_gL &&!goaled&&y<y_gL+h_goal)
        {
           GOAL_right++;
           GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,255,255,255,255,angle,NONE,GOAL_right);
           SDL_RenderPresent(m_renderer);
            goaled=true;
            goalScoredLeft=true;
        }
    if(goaled)
     {
        Mix_Chunk *goalscored=Mix_LoadWAV("goalscored.wav");
        Mix_PlayChannel(-1,goalscored,0);
        y=Y0;
        x=WIDTH/2;
        int  k=1.5;
        int dy=18;
        y_shoeR=GROUND,y_shoeL=GROUND;
        x_shoeR=x0_shoeR,x_shoeL=x0_shoeL;
        while(y<GROUND)
         {
            y+=dy;
            dy*=k;
            textureRendererTripleClone(m_renderer,font_size,angle,playerSide );
         }
        int current,last=SDL_GetTicks(),d=0;
        while(d<3)
          {
           current = SDL_GetTicks();
           if (current > last + 1000)
            {
               last=current;
               d++;
            }
            textureRendererTripleClone(m_renderer,font_size,angle,playerSide);
          }
        Mix_Chunk *goalScored=Mix_LoadWAV("goaled.wav");
        Mix_PlayChannel(-1,goalScored,0);
        if(GOAL_left==4&&GOAL_right==4)
            continueGame=false;
        if(GOAL_right==5||GOAL_left==5)
            continueGame=false;
        goaled=false;
    }

  }
     if(home)
     {
         home=false;
         Default();
         menueMain(m_renderer);
         game( m_renderer);
    }
}
void pause(SDL_Renderer *m_renderer)
{
     int startpause=SDL_GetTicks(),endpause,x_e,y_e;
    textureRenderer(m_renderer,30,0);
    while(paused)
     {
    SDL_PollEvent(e);
    if(e->type==SDL_MOUSEBUTTONDOWN)
    {
        textureRenderer(m_renderer,30,0);
        x_e=e->motion.x;
        y_e=e->motion.y;
        if(x_e>=x_h && x_e<=x_h+w_b &&y_e<=y_h+h_b && y_e>=y_h &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
          {
            Mix_Chunk *click=Mix_LoadWAV("click.wav");
            Mix_PlayChannel(-1,click,0);
            nameL="";
            nameR="";
            getnamed=false;
            GOAL_left=0;
            GOAL_left=0;
            //cout<<"Home";
            home=true;
            powerLengthgRight=10;
            powerLengthgRight=10;
            startGame=false;
           break;
         }

         if(x_e>=x_p && x_e<=x_p+w_b &&y_e<=y_p+h_b && y_e>=y_p &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
         {
             Mix_Chunk *click=Mix_LoadWAV("click.wav");
             Mix_PlayChannel(-1,click,0);
             endpause=SDL_GetTicks();
             int delthaPause=endpause-startpause;
             startTime+=delthaPause;
             paused=false;
         }
        if(x_e>=x_r && x_e<=x_r+w_b &&y_e<=y_r+h_b && y_e>=y_r &&(e->button.button==SDL_BUTTON_LEFT)&&(e->button.clicks==2))
         {
             Mix_Chunk *click=Mix_LoadWAV("click.wav");
             Mix_PlayChannel(-1,click,0);
             restart(m_renderer);
             break;
         }
    }
  }
}
void restart(SDL_Renderer *m_renderer)
{
    GOAL_left=0;
    GOAL_right=0;
    powerLengthgRight=10;
    powerLengthgLeft=10;
    startTime=SDL_GetTicks();
    int x_textL=x_scoreb+w_scoreb/2-103;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    int R=255,G=255,B=255,A=255;
    int font_size=30,angle=0;
    string pause="pause.png";
    string start="start.png";
    string home="home.png";
    string restart="restart.png";
    int questionmark_pic=70;
    stringstream ss;
    ss<<currentTime/1000;
    string timestr;
    ss>>timestr;
    if(currentTime/1000>=150)
    continueGame=false;
    texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
    texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
    texture(m_renderer,x_shoeL-50,y_shoeL-player_h,player1,player_w,player_h);
    texture(m_renderer,x_shoeR+50,y_shoeR-player_h,player2,player_w,player_h);
    texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
    texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
    texture(m_renderer,x,y,ball,RADIOUS,RADIOUS);
    texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
    rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
    write(m_renderer,WIDTH/2,y_scoreb+h_scoreb/2,timestr,font_address_04,font_size,0,0,0,255,angle,NONE);
    texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
    texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
    my_line(m_renderer,x_scoreb+50+player_pic+5,y_scoreb-15+player_pic/2,powerLengthgLeft,0,15,255,0,0);
    my_line(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15+player_pic/2,powerLengthgRight,-3.141592,15,255,0,0);
    GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
    GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
    texture(m_renderer,x_h,y_h,home,w_b,h_b);
    texture(m_renderer,x_p,y_p,start,w_b,h_b);
    texture(m_renderer,x_r,y_r,restart,w_b,h_b);
    write(m_renderer,200,200,"RESTART",font_address_04,50,255,0,0,255,0,NONE);
    SDL_RenderPresent(m_renderer);
    SDL_Delay(2);
    SDL_RenderClear( m_renderer );
    SDL_Delay(2000);
}
