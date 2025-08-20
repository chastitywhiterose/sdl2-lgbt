/*
This files contains functions I wrote to place text from a string to the exact screen location I want
the dimensions of the window are global variables.
*/

/*
this version of the function just copies the surface created to the screen surface. It does not create a "texture" or use the modern SDL2 API because this is slower.
*/

void ttf_print(char *text,int x,int y)
{
 TTF_SizeText(font, text, &w, &h);
 /*printf("Predicted area to render string\n'%s'\nwill be size w=%d,h=%d\n",text,w,h);*/

 /*text_surface=TTF_RenderText_Solid(font, text, font_color);*/

 text_surface=TTF_RenderText_Blended(font, text, font_color);

 /*text_surface=TTF_RenderText_Shaded(font, text, font_color,back_color);*/

 w=text_surface->w;
 h=text_surface->h;

 /*printf("Actual surface size is w=%d,h=%d\n",w,h);*/

 srcrect.x=0;
 srcrect.y=0;
 srcrect.w=w;
 srcrect.h=h;

 dstrect=srcrect;
 dstrect.x=x;
 dstrect.y=y;

 SDL_BlitSurface(text_surface,&srcrect,surface,&dstrect);
 /*free the surface because we have drawn it and are done with it*/
 SDL_FreeSurface(text_surface);
}

void ttf_print_wrapped(char *text,int x,int y)
{
 /*text_surface=TTF_RenderText_Solid_Wrapped(font, text, font_color,width);*/

 text_surface=TTF_RenderText_Blended_Wrapped(font, text, font_color,width);

 /*text_surface=TTF_RenderText_Shaded_Wrapped(font, text, font_color,back_color,width);*/

  w=text_surface->w;
 h=text_surface->h;

 /*printf("Actual surface size is w=%d,h=%d\n",w,h);*/

 srcrect.x=0;
 srcrect.y=0;
 srcrect.w=w;
 srcrect.h=h;

 dstrect=srcrect;
 dstrect.x=x;
 dstrect.y=y;

 SDL_BlitSurface(text_surface,&srcrect,surface,&dstrect);
 /*free the surface because we have drawn it and are done with it*/
 SDL_FreeSurface(text_surface);
}
















void ttf_test()
{
 SDL_FillRect(surface,NULL,0xFFFFFF);

 ttf_print("Chastity White Rose",0,0);
 ttf_print("The Vegan Virgin",0,font_size*1);

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









void ttf_test2()
{

 SDL_FillRect(surface,NULL,0x000000);

 ttf_print_wrapped("I am Chastity White Rose, the Vegan Virgin! I am the creator of the video games Chaste Tris, Chaste Puyo, and Chaste Panel.",0,0);


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



void ttf_test3()
{

 SDL_FillRect(surface,NULL,0x000000);

 ttf_print_wrapped("Light\nGraphics\nBinary\nText",0,0);


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

/*animation of frame number*/
void ttf_test4()
{
 delay=1000/fps;

 loop=1;
 while(loop)
 {

/*drawing section begin*/
 SDL_FillRect(surface,NULL,0xFFFFFF);

 ttf_print("Chastity White Rose",0,0);
 ttf_print("The Vegan Virgin",0,font_size*1);

 sprintf(text,"frame: %d <-- this number changes every frame!",frame);
 frame++;

 ttf_print(text,0,font_size*3);

 ttf_print_wrapped("This program is the prototype of my library LGBT:\n\nLight Graphics Binary Text",0,font_size*5);

 ttf_print_wrapped("Text using SDL_ttf for extremely gay programmers",0,font_size*10);

 SDL_UpdateWindowSurface(window);


  /*drawing section end*/

  sdl_time = SDL_GetTicks();
  sdl_time1 = sdl_time+delay;

  /*time loop used to slow the game down so users can see it*/
  while(loop==1 && sdl_time<sdl_time1)
  {
   sdl_time=SDL_GetTicks();
  }

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
