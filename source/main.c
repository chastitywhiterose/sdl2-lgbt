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
SDL_Surface *surface;
SDL_Renderer *renderer; /*not used in this version. I changed to surfaces*/
SDL_Event e;

/*variables for SDL_image features*/
SDL_Texture *texture;
char filename[256];
int x,y,w,h;


/*variables for SDL_ttf features*/
char text[0x1000];
TTF_Font *font=NULL;
int font_size=20;
char font_filename[256];
int renderstyle=TTF_STYLE_NORMAL;
SDL_Color font_color={0,0,0,255},back_color={128,128,128,255};
SDL_Surface *text_surface;
SDL_Texture *text_texture;
SDL_Rect srcrect,dstrect;
SDL_Rect rect;

int fps=60; /*frames per second*/
int frame=0,lastframe=0,delay,framelimit=1; /*only used for animation demos*/
time_t time0,time1;
int seconds,minutes,hours; /*to keep track of time*/
int sdl_time,sdl_time1;

#include "chaste_the_rainbow.h"

#include "sdl2_ttf-lgbt-surface.h"

#include "sdl2_ttf-lgbt-surface-draw.h"


int main(int argc, char **argv)
{




 if(SDL_Init(SDL_INIT_VIDEO))
 {
  printf( "SDL could not initialize! SDL_Error: %s\n",SDL_GetError());return -1;
 }
 window=SDL_CreateWindow("SDL2 LGBT",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_SHOWN );
 if(window==NULL){printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 surface = SDL_GetWindowSurface( window ); /*get surface for this window*/

 /*create a renderer that can draw to the surface*/
 renderer=SDL_CreateSoftwareRenderer(surface);
 if(renderer==NULL){printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );return -1;}

 printf("SDL Program Compiled Correctly\n");

 SDL_FillRect(surface,NULL,0xFF00FF);
 SDL_UpdateWindowSurface(window);

 /*fill entire screen with current draw color*/
 /*
 SDL_SetRenderDrawColor(renderer,255,255,255,255);
 SDL_RenderClear(renderer);
 SDL_RenderPresent(renderer);
 */

 
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


 /*it is important to initialize the rainbow*/
 chaste_palette_rainbow(40);
 /*chaste_palette_rainbow_pastel(80);*/
 /*chaste_palette_view();*/

font_color.r=255;font_color.g=255;font_color.b=255;

std_master_chars(); /*generate the standard 95 characters, starting with space*/
/*ttf_master_chars();*/ /*run the test demo with SDL_TTF to see the characters on the screen*/

font_color.r=255;font_color.g=255;font_color.b=255;
main_lgbt=lgbt_load_ttf_surface(master_chars);
test_new_lgbt();

/*ttf_test4();*/

/*
font_color.r=255;font_color.g=255;font_color.b=255;
ttf_test2();
font_color.r=0;font_color.g=255;font_color.b=255;
ttf_test3();
*/

 loop=0;
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
