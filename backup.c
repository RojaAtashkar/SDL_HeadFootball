#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL2/SDL2_gfx.h>
#include <string>
#include<cmath>
#include<string>
using namespace std;
//constant  sizes
# define WIDTH 1200
# define HEIGHT 600
# define Y0 40
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
int RADIOUS=80;
int velocity_x0=25;
int velocity_y0=-200;
int acceleration_y0=6;
int player_w=85;
int player_h=85;
int player_vel1=6;
int player_vel2=6;
int x0_shoeL=235;
int x0_shoeR= WIDTH-235;
int GROUND;
int GOAL_left;
int GOAL_right;
//structures
typedef enum{
     NONE = 0,
     HORIZENTAL = 1,
     VERTICAL = 2,
     HORVER = 3
}short;
void pic();
void initial_setup (SDL_Renderer *m_renderer) ;
void texture(SDL_Renderer *m_renderer,int xp,int yp,string addressOfImage,int width,int height);
void rect(SDL_Renderer *Renderer, int x,int y,int w,int h,int R, int G, int B, int fill_boolian);
void help(SDL_Renderer *Renderer,double x_ball,double y_ball,int dx ,bool clicked);
void celebration(SDL_Renderer *m_renderer,int x,int y);
void myTextRGBA(SDL_Renderer *renderer,int x,int y,const char * text,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num);
void GOAL(SDL_Renderer *m_renderer,int x,int y,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num,int goal);
int main( int argc, char * argv[] )
{
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



    //initial_setup (m_renderer);
     pic();
    initial_setup (m_renderer);
    cout<<GOAL_left<<" "<<GOAL_right;
    //Finalize and free resources
    SDL_DestroyWindow( m_window );
    SDL_DestroyRenderer( m_renderer );
	IMG_Quit();
	SDL_Quit();
    return 0;

}
void pic()
{
    GROUND=430;
     back_ground="bg1.jpg";
     ball="ball.png";
     player1="player1.png";
     player2="player22.png";
     shoeR="shoeR.png";
     shoeL="shoeL.png";
     goalL="goalright.png";
     goalR="goalleft.png";
}
 void initial_setup (SDL_Renderer *m_renderer)
 {
        TTF_Init();
     // balls movement
     bool continueGame=true;
     int x=WIDTH/2;
     double MO=1;
     double velocity=velocity_y0;
     double velocity_x=velocity_x0;
     double t;
     double y0=Y0;
     double y=0;
     int w_shoe=100,h_shoe=100;
     int y_shoeR=GROUND,y_shoeL=GROUND;
     int x_shoeR=x0_shoeR,x_shoeL=x0_shoeL;
     int x_p1=x_shoeL-50, y_p1=y_shoeL-50;
     int x_p2=x_shoeR+50, y_p2=y_shoeR-50;
     int w_goal=100, h_goal=300;
     int x_gR=110, y_gR=GROUND-h_goal+90;
     int x_gL=WIDTH-130, y_gL=GROUND-h_goal+90;
     int acceleration=acceleration_y0;
     bool goaled=false;
     GOAL_left=0;
    GOAL_right=0;
     //score board setup
     int x_scoreb=40, y_scoreb=20, w_scoreb=WIDTH-80 ,h_scoreb=60;
     int player_pic=100;
     //text for goal numbers
    const char * font_address_01="IranNastaliq.ttf"; //define some fonts with extension 'ttf'
    const char * font_address_02="HARLOWSI.ttf";
    const char * font_address_03="MAGNETOB.ttf";
    const char * font_address_04="arial.ttf";
    int font_size = 30;
    double angle = 0.0;
    int x_textL=x_scoreb+w_scoreb/2-100;
    int y_textL=y_scoreb+h_scoreb/2, y_textR=y_scoreb+h_scoreb/2;
    int x_textR=x_scoreb+w_scoreb/2+100;
    int R=255;
    int G =255;
    int B=255;
    int A=255;
        SDL_Event *e = new SDL_Event();
        texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
        texture(m_renderer,x_shoeL-50,y_shoeL-100,player1,player_w,player_h);
        texture(m_renderer,x_shoeR+50,y_shoeR-100,player2,player_w,player_h);
        texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
        texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
        texture(m_renderer,x,y,ball,RADIOUS,RADIOUS);
        texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
        texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
        rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
        texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
        texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
        GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
        GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
        SDL_RenderPresent( m_renderer );
        SDL_Delay(2);
        SDL_RenderClear( m_renderer );
             //initial ball drop
     int k=1.5;
     int dy=18;
     while(y<GROUND)
     {
         y+=dy;
         dy*=k;
            texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
            texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
            texture(m_renderer,x_shoeR+50,y_shoeR-100,player2,player_w,player_h);
            texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
            texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
            texture(m_renderer,x,y,ball,RADIOUS,RADIOUS);
            texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
            texture(m_renderer,x_shoeL-50,y_shoeL-100,player1,player_w,player_h);
            rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
            texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
            texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
            GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
              GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
            SDL_RenderPresent( m_renderer );
            SDL_Delay(2);
            SDL_RenderClear( m_renderer );
     }
    while(continueGame)
     {
        SDL_PollEvent(e);
        if(e-> type==SDL_KEYDOWN )
         {
            switch(e->key.keysym.sym)
             {
                case SDLK_ESCAPE:
                     continueGame=false;
                     break;
                case SDLK_RIGHT:
                     x_shoeR+=player_vel2;
                     break;
                case SDLK_UP:
                     y_shoeR+=player_vel2;
                     break;
                case SDLK_DOWN:
                     y_shoeR-=player_vel2;
                     break;
                case SDLK_LEFT:
                    x_shoeR-=player_vel2;
                    break;
                case SDLK_d:
                    x_shoeL+=player_vel1;
                    break;
                case SDLK_a:
                    x_shoeL-=player_vel1;
                    break;
             }
         }
            texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
            texture(m_renderer,x_shoeL-50,y_shoeL-100,player1,player_w,player_h);
            texture(m_renderer,x_shoeR+50,y_shoeR-100,player2,player_w,player_h);
            texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
            texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
            texture(m_renderer,x,y,ball,RADIOUS,RADIOUS);
            texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
            texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
            rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
            texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
            texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
            GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
            GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
            SDL_RenderPresent( m_renderer );
            SDL_Delay(2);
            SDL_RenderClear( m_renderer );
            //right player simple drop
        if((x_shoeR-x)<=RADIOUS && (x_shoeR-x)>0&& y>=y_shoeR&& y<(y_shoeR+h_shoe))
            {
                y0=y;
                velocity_x=velocity_x0;
                velocity=velocity_y0;
                if(x<0 || x>WIDTH)
                velocity_x = -velocity_x;
                for(t=0.1; t<25; t+=0.1)
                  {
                    y=( 0.5*acceleration*t*t+velocity*t)*MO+y0;
                    velocity+=acceleration*t;
                    texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
                    texture(m_renderer,x_shoeL-50,y_shoeL-100,player1,player_w,player_h);
                    texture(m_renderer,x_shoeR+50,y_shoeR-100,player2,player_w,player_h);
                    texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
                    texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
                    texture(m_renderer,x,y,ball,RADIOUS,RADIOUS);
                    texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
                    texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
                    rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
                    texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
                    texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
                    GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
                    GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
                    SDL_RenderPresent( m_renderer );
                    SDL_Delay(25);
                    SDL_RenderClear( m_renderer );
                    if(x<0 || x>WIDTH)
                        velocity_x = -velocity_x;

                    //ball collision with the head of players
                    if(abs(x-x_shoeR-50)<RADIOUS && y<=y_shoeR && y>=y_shoeR-100)
                      {
                        velocity_x=-velocity_x;

                      }
                    if(abs(x-x_shoeL+50)<RADIOUS && y<=y_shoeL && y>=y_shoeL-100)
                      {
                        velocity_x=-velocity_x;

                      }
                    // ball collision with goals
                     if(x_gL-x<=RADIOUS && x_gL-x>0 && y>y_gL &&y<y_gL+h_goal)
                         {
                             velocity_x=-velocity_x;
                         }
                         if(x-x_gR<=RADIOUS && x-x_gR>0 && y>y_gR &&y<y_gR+h_goal)
                         {
                             velocity_x=-velocity_x;
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

                    x -= velocity_x;
                    //GOAL!!
                     if( x-x_gL<w_goal &&x-x_gL>0 &&y>y_gL &&y<y_gL+h_goal)
                            {
                                GOAL_left++;
                                 GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
                                  SDL_RenderPresent(m_renderer);
                            }
                        if( x_gR-x<w_goal &&x_gR-x>0 &&y>y_gL &&y<y_gL+h_goal)
                            {
                               GOAL_right++;
                                GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
                                 SDL_RenderPresent(m_renderer);
                            }
                       if( y>=GROUND )
                       break;
                       SDL_PollEvent(e);
                       if(e-> type==SDL_KEYDOWN )
                        {
                            switch(e->key.keysym.sym)
                                {
                                    case SDLK_ESCAPE:
                                        continueGame=false;
                                        break;
                                    case SDLK_RIGHT:
                                         x_shoeR+=player_vel2;
                                         break;
                                    case SDLK_UP:
                                         y_shoeR+=player_vel2;
                                         break;
                                    case SDLK_DOWN:
                                         y_shoeR-=player_vel2;
                                         break;
                                    case SDLK_LEFT:
                                        x_shoeR-=player_vel2;
                                    break;
                                    case SDLK_d:
                                        x_shoeL+=player_vel1;
                                        break;
                                    case SDLK_a:
                                        x_shoeL-=player_vel1;
                                      break;
                                }
                            }
                }
                goaled=false;
            }
             //left player simple ball drop
            if((x-x_shoeL)<=RADIOUS&& x-x_shoeL>0&& y>=y_shoeL && y<=y_shoeL+h_shoe)
             {
                 y0=y;
                 velocity_x=velocity_x0;
                 velocity=velocity_y0;
                 for(t=0.1; t<25;t+=0.1)
                    {
                        y=( 0.5*acceleration*t*t +velocity*t)*MO+y0;
                        velocity+=acceleration*t;
                        texture(m_renderer,0,0,back_ground,WIDTH,HEIGHT);
                        texture(m_renderer,x_shoeR+50,y_shoeR-100,player2,player_w,player_h);
                        texture(m_renderer,x_shoeL,y_shoeL,shoeL,w_shoe,h_shoe);
                        texture(m_renderer,x_shoeR,y_shoeR,shoeR,w_shoe,h_shoe);
                        texture(m_renderer,x,y,ball,RADIOUS,RADIOUS);
                        texture(m_renderer,x_gL,y_gL,goalL,w_goal,h_goal);
                        texture(m_renderer,x_gR,y_gR,goalR,w_goal,h_goal);
                        rect(m_renderer,x_scoreb,y_scoreb,w_scoreb,h_scoreb,50,100,255,1);
                        texture(m_renderer,x_scoreb+50,y_scoreb-15,player1,player_pic,player_pic);
                        texture(m_renderer,x_scoreb+w_scoreb-50-player_pic,y_scoreb-15,player2,player_pic,player_pic);
                        GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
                        GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
                        SDL_RenderPresent( m_renderer );
                        SDL_Delay(2);
                        SDL_RenderClear( m_renderer );
                        if(x<0 || x>WIDTH)
                            velocity_x = -velocity_x;
                             //ball collision with the head of players
                        if(abs(x-x_shoeR-50)<RADIOUS && y<=y_shoeR && y>=y_shoeR-100)
                          {
                             velocity_x=-velocity_x;
                          }
                           if(abs(x-x_shoeL+50)<RADIOUS && y<=y_shoeL && y>=y_shoeL-100)
                            {
                             velocity_x=-velocity_x;
                            }
                            // ball collision with goals
                         if(x_gL-x<=RADIOUS && x_gL-x>0 && y>y_gL &&y<y_gL+h_goal)
                         {
                             velocity_x=-velocity_x;
                         }
                         if(x-x_gR<=RADIOUS && x-x_gR>0 && y>y_gR &&y<y_gR+h_goal)
                         {
                             velocity_x=-velocity_x;
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
                            x += velocity_x;
                            //GOAL!!
                        if( x-x_gL<w_goal &&x-x_gL>0 &&y>y_gL && velocity_x<0 &&y<y_gL+h_goal)
                            {
                                GOAL_left++;
                                 GOAL(m_renderer,x_textL,y_textL,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_left);
                                  SDL_RenderPresent(m_renderer);
                            }
                        if( x_gR-x<w_goal &&x_gR-x>0 &&y>y_gL &&velocity>0 &&y<y_gL+h_goal)
                            {
                               GOAL_right++;
                              GOAL(m_renderer,x_textR,y_textR,font_address_04,font_size,R,G,B,A,angle,NONE,GOAL_right);
                              SDL_RenderPresent(m_renderer);
                            }
                        if( y>=GROUND )
                            break;
                        SDL_PollEvent(e);
                        if(e-> type==SDL_KEYDOWN )
                        {
                            switch(e->key.keysym.sym)
                                {
                                case SDLK_ESCAPE:
                                    continueGame=false;
                                    break;
                                case SDLK_RIGHT:
                                     x_shoeR+=player_vel2;
                                     break;
                                case SDLK_UP:
                                     y_shoeR+=player_vel2;
                                     break;
                                case SDLK_DOWN:
                                     y_shoeR-=player_vel2;
                                     break;
                                case SDLK_LEFT:
                                    x_shoeR-=player_vel2;
                                break;
                                case SDLK_d:
                                    x_shoeL+=player_vel1;
                                    break;
                                case SDLK_a:
                                    x_shoeL-=player_vel1;
                                    break;
                             }
                     }

            }
        }
        goaled=false;
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
    SDL_RenderFillRect(Renderer, &rectangle);
    SDL_RenderDrawRect(Renderer, &rectangle);
    //SDL_RenderPresent(Renderer);
}
void help(SDL_Renderer *Renderer,double x_ball,double y_ball,int dx ,bool clicked)
{
    int y_help=0,y0=y_ball+20,x_help=x_ball+20;
    double velocity =-200;
    if(!clicked)
    {
    for(double time=0;time<3.8;time+=0.1){
    y_help=(0.5*3*time*time+velocity*time)+y0;
    velocity+=3*time;
    filledEllipseRGBA(Renderer,x_help,y_help,1,1,255,255,0,255);
    x_help+=dx;

    }
    }
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
//void celebration(SDL_Renderer *m_renderer,int x,int y)
//{
//
//    int i=1;
//    for(i=1 ; i<=25 ; i++)
//    {
//        string si="frame_apngframe";
//        si+=to_string(i);
//        si+="1.png";
//        texture(m_renderer,0,0,"bg.png",1200,700);
//        texture(m_renderer,x,y,"ball1.png",40,40);
//        texture(m_renderer,135,275,"basket.png",100,75);
//        SDL_Delay(50);
//        texture(m_renderer,0,0,si,1200,700);
//        SDL_RenderPresent( m_renderer );
//    }
//     texture(m_renderer,0,0,"bg.png",1200,700);
//     texture(m_renderer,x,y,"ball1.png",40,40);
//     texture(m_renderer,135,275,"basket.png",100,75);
//     SDL_RenderPresent( m_renderer );
//}
void myTextRGBA(SDL_Renderer *renderer,int x,int y,const char * text,const char * font,int font_size,int R,int G,int B, int A,double angle,short flip_num)
{
    SDL_Color text_color = { R, G, B, A};
    int mWidth = 0;
	int mHeight = 0;
    SDL_Rect* clip = NULL;
    TTF_Font *gFont = NULL;
    SDL_Point* center = NULL;

    SDL_RendererFlip flip;
    switch(flip_num){
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

