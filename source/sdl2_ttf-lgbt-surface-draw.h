

struct lgbt
{
 Uint32 width,height,bpp;
 Uint32 *pixels;
};

struct lgbt main_lgbt;

int main_color=0xFFFFFF; /*global color for all drawn text*/

/*loads data into an lgbt image by first loading a bitmap file and then copying all the data over*/

struct lgbt lgbt_load_ttf_surface(const char *s)
{
 int x,y;
 SDL_Surface *temp_surface,*temp_surface1;
 Uint32 *ssp; /*ssp is short for Source Surface Pointer*/
 struct lgbt new_lgbt;

 TTF_SetFontSize(font,font_size); /*set the font size for rendered surface by SDL_TTF*/

 /*load bitmap to temporary surface*/
 temp_surface=TTF_RenderText_Solid(font, s, font_color);

 /*convert to BGRA32 pixel format for easy handling for later functions*/
 temp_surface1=SDL_ConvertSurfaceFormat(temp_surface, SDL_PIXELFORMAT_BGRA32, 0);

 /*set the initial data for the lgbt structure copied from the SDL_Surface*/
 new_lgbt.width=temp_surface1->w;
 new_lgbt.height=temp_surface1->h;
 new_lgbt.bpp=32;

 printf("new_lgbt width=%d height=%d bpp=%d\n",new_lgbt.width,new_lgbt.height,new_lgbt.bpp);

 new_lgbt.pixels=(uint32_t*)malloc((new_lgbt.width*new_lgbt.height)*sizeof(*new_lgbt.pixels));
 if(new_lgbt.pixels==NULL){printf("Error: malloc failed,\n");}
 else
 {
  printf("Allocated the pixels for lgbt image.\n");

  ssp=(Uint32*)temp_surface1->pixels;

  /*copy the pixels from the surface to this structure*/
  y=0;
  while(y<new_lgbt.height)
  {
   x=0;
   while(x<new_lgbt.width)
   {
    new_lgbt.pixels[x+y*new_lgbt.width]=ssp[x+y*new_lgbt.width] & 0xFFFFFF;
    /*printf("%06X %d,%d\n",new_lgbt.pixels[x+y*new_lgbt.width],x,y);*/
    x++;
   }
   y++;
  }
  
 }

 SDL_FreeSurface(temp_surface);
 SDL_FreeSurface(temp_surface1);

 return new_lgbt;
}





/*
This uses direct pixel access of the source lgbt font to draw only when the source pixel is not black.
*/
void lgbt_draw_text(const char *s,int cx,int cy,int scale)
{
 int x,y,i,c,cx_start=cx;
 int sx,sy,sx2,sy2,dx,dy; /*x,y coordinates for both source and destination*/
 Uint32 pixel,r,g,b; /*pixel that will be read from*/
 SDL_Rect rect_source,rect_dest;
 int char_width=main_lgbt.width/95; /*there are 95 characters in my font files*/
 int char_height=main_lgbt.height;

 printf("Size of loaded font is %d,%d\n",char_width,char_height);

 if(main_lgbt.pixels==NULL){/*printf("Error: Font is NULL!\n");*/return;}

 i=0;
 while(s[i]!=0)
 {
  c=s[i];
  if(c=='\n'){ cx=cx_start; cy+=char_height*scale;}
  else
  {
   x=(c-' ')*char_width;
   y=0*char_height;

   /*set up source rectangle where this character will be copied from*/
   rect_source.x=x;
   rect_source.y=y;
   rect_source.w=char_width;
   rect_source.h=char_height;
 
   /*Now for the ultra complicated stuff that only Chastity can read and understand!*/
   sx2=rect_source.x+rect_source.w;
   sy2=rect_source.y+rect_source.h;
   
   dx=cx;
   dy=cy;
   
   sy=rect_source.y;
   while(sy<sy2)
   {
    dx=cx;
    sx=rect_source.x;
    while(sx<sx2)
    {
     pixel=main_lgbt.pixels[sx+sy*main_lgbt.width];

     /*printf("%06X %d,%d\n",pixel,sx,sy);*/

     pixel&=0xFFFFFF;
     
     if(pixel!=0x000000) /*only if source pixel is nonzero(not black) draw square to destination*/
     {
      rect_dest.x=dx;
      rect_dest.y=dy;
      rect_dest.w=scale;
      rect_dest.h=scale;
      
      pixel=main_color;
      
      r=(pixel&0xFF0000)>>16;
      g=(pixel&0x00FF00)>>8;
      b=(pixel&0x0000FF);
      
      /*SDL_SetRenderDrawColor(renderer,r,g,b,255);
      SDL_RenderFillRect(renderer,&rect_dest);*/

SDL_FillRect(surface,&rect_dest,pixel);
      
     }
     
     sx++;
     dx+=scale;
    }
    sy++;
    dy+=scale;
   }
   /*End of really complicated section*/
   cx+=char_width*scale;
  }
  i++;
 }

}






void test_new_lgbt()
{
 SDL_FillRect(surface,NULL,0x7f7f7f);

 lgbt_draw_text("This program is the prototype of my library LGBT:\n\nLight Graphics Binary Text",0,0,1);

 lgbt_draw_text("Text using SDL_ttf for extremely gay programmers",0,font_size*10,1);

 SDL_UpdateWindowSurface(window);

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

}

