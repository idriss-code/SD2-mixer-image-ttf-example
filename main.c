#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>


/*** fonctionne avec SDL.dll et la collection de .dll de SDL_image x86
les dll sont a mettre dans windows/sytem32 ou windows/sysWOW64 en fonction du systeme
*/

void pause();

int main ( int argc, char** argv )
{
    int x;
    SDL_Surface *image=NULL;
    SDL_Surface *texte=NULL;
    SDL_Rect position,source;
    SDL_Color couleurNoire = {0, 0, 0};//pour ttf

    // initialize SDL video
    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "Unable to init SDL: %s\n", SDL_GetError() );
        return 1;
    }

    TTF_Init(); // intialisation de le SDL_TTF

    TTF_Font * police=NULL;

    police=TTF_OpenFont("boldp.ttf",20);

    texte=TTF_RenderText_Blended(police,"CA MARCHE !!!",couleurNoire);

    // intialisation de le SDL_MIXER

    Mix_Init(MIX_INIT_MP3);
    // start SDL with audio support
    if(SDL_Init(SDL_INIT_AUDIO)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
        exit(1);
    }
    // open 44.1KHz, signed 16bit, system byte order,
    //      stereo audio, using 1024 byte chunks
    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024)==-1) {
        printf("Mix_OpenAudio: %s\n", Mix_GetError());
        exit(2);
    }

    Mix_Music *musique;
    musique = Mix_LoadMUS("test.mp3");
    Mix_VolumeMusic(MIX_MAX_VOLUME / 5);
    Mix_PlayMusic(musique,-1);

    SDL_Window *ecran = SDL_CreateWindow("Ma fenêtre de jeu",
                          SDL_WINDOWPOS_UNDEFINED,
                          SDL_WINDOWPOS_UNDEFINED,
                          640, 480,
                          SDL_WINDOW_OPENGL);
    SDL_FillRect(SDL_GetWindowSurface(ecran),NULL,SDL_MapRGB(SDL_GetWindowSurface(ecran)->format,50,100,50));

    position.x=0;
    position.y=0;
    image = IMG_Load("test.png");
    image = SDL_ConvertSurface(image,SDL_GetWindowSurface(ecran)->format,0);
    SDL_UpperBlit(image,NULL,SDL_GetWindowSurface(ecran),&position);

    source.x=0;
    source.y=0;
    source.h=image->h;
    source.w=image->w;
    position.x=0;
    position.y=50;
    position.h= image->h*2;
    position.w= image->w*2;
    x=SDL_BlitScaled(image,NULL,SDL_GetWindowSurface(ecran),&position);
    printf( "test: %d\n", x);


    position.x=100;
    position.y=100;
    SDL_UpperBlit(texte,NULL,SDL_GetWindowSurface(ecran),&position);


    SDL_UpdateWindowSurface(ecran);

    pause();

    TTF_CloseFont(police);
    TTF_Quit();

    SDL_FreeSurface(image);
    SDL_FreeSurface(texte);
    SDL_DestroyWindow(ecran);

    Mix_FreeMusic(musique);
    Mix_CloseAudio();

    // force a quit
    while(Mix_Init(0))Mix_Quit();

    SDL_Quit();
    return 0;
}


void pause()
{
     int continuer=1;
    SDL_Event evenement;// variable evenement

    while(continuer)
    {
            SDL_WaitEvent(&evenement);
            switch(evenement.type)
            {
                case SDL_QUIT:
                    continuer=0;
            }
    }
}
