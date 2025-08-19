#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <SDL.h>

#include <SDL_ttf.h>

/*variables that apply for any program I create that uses SDL2*/
int width=1280,height=720;
int loop=1;
int Window_Flags=0;
SDL_Window *window;
SDL_Renderer *renderer;
SDL_Event e;

/*variables for SDL_image features*/
SDL_Texture *texture;
char filename[256];
int x,y,w,h;


/*variables for SDL_ttf features*/
char text[0x1000];
TTF_Font *font=NULL;
int font_size=60;
char font_filename[256];
int renderstyle=TTF_STYLE_NORMAL;
SDL_Color font_color={0,0,0,255},back_color={128,128,128,255};
SDL_Surface *text_surface;
SDL_Texture *text_texture;
SDL_Rect srcrect,dstrect;

#include "sdl2_ttf-lgbt.h"

int fps=60; /*frames per second*/

int frame=0,lastframe=0,delay,framelimit=1; /*only used for animation demos*/
time_t time0,time1;
int seconds,minutes,hours; /*to keep track of time*/
int sdl_time,sdl_time1;

char gamename[256];
int blocks_used=7;
SDL_Rect rect;

char movetext[256],move_id;
int text_x; /*the x position of where text will go*/

FILE *fp; /*to save a file of moves played*/
char filename[256]; /*name of move log file*/
FILE *fp_input; /*file to get input from instead of the keyboard*/

int main(int argc, char **argv)
{




 if(SDL_Init(SDL_INIT_VIDEO))
 {
  printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;
 }
 window=SDL_CreateWindow("SDL2 LGBT",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}
 renderer = SDL_CreateRenderer(window,-1,0);
 if(renderer==NULL){printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 printf("SDL Program Compiled Correctly\n");

 /*fill entire screen with current draw color*/
 SDL_SetRenderDrawColor(renderer,255,255,255,255);
 SDL_RenderClear(renderer);

  SDL_RenderPresent(renderer);
 
 /* Initialize the TTF library */
 if(TTF_Init() < 0)
 {
  SDL_Log("Couldn't initialize TTF: %s\n",SDL_GetError());
  SDL_Quit();
  return(2);
 }

 /*strcpy(font_filename,"font/editundo.ttf");*/

 /*strcpy(font_filename,"font/hack/Hack-Regular.ttf");*/

 strcpy(font_filename,"font/hack/Hack-Bold.ttf");

 font = TTF_OpenFont(font_filename, font_size);
 if (font == NULL)
 {
  SDL_Log("Couldn't load %d pt font from %s: %s\n",
                    font_size, font_filename, SDL_GetError());

 }
 else
 {
  printf("font file '%s'loaded\n",font_filename);
  TTF_SetFontStyle(font, renderstyle);
  TTF_SetFontKerning(font, 0);
 }


 strcpy(text,"Chastity White Rose");

font_color.r=0;font_color.g=0;font_color.b=0;
ttf_test();
font_color.r=255;font_color.g=255;font_color.b=255;
ttf_test2();
font_color.r=0;font_color.g=255;font_color.b=255;
ttf_test3();

 loop=1;
 while(loop)
 {
  while(SDL_PollEvent(&e))
  {
   if(e.type == SDL_QUIT){loop=0;}
   if(e.type == SDL_KEYUP)
   {
    if(e.key.keysym.sym==SDLK_ESCAPE){loop=0;}
   }
  }
 }


 TTF_CloseFont(font);
 TTF_Quit();

 SDL_DestroyRenderer(renderer);
 SDL_DestroyWindow(window);
 SDL_Quit();
 return 0;
}
