//
//  music.c
//  Bomberman
//
//  Created by agbo anthony on 24/08/2016.
//  Copyright (c) 2016 agbo anthony. All rights reserved.
//

#include "client.h"

char* list_song(int track){
    char * list[50];
    
    list[0] = SONG1_PATH;
    list[2] = SONG2_PATH;
    list[3] = SONG3_PATH;
    return list[track];
}

char* list_effect(int track){
    char * list[50];
    
    list[0] = SONG1_PATH;
    list[2] = SONG2_PATH;
    list[3] = SONG3_PATH;
    return list[track];
}

Mix_Music* Play_song(int track){
    
    char* song;
    
    song = list_song(track);
    
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        fprintf(stdout,"Échec de chargement de la musique (%s)\n",SDL_GetError());
    }
    
    Mix_Music *musique; //Création du pointeur de type Mix_Music
    //musique = Mix_LoadMUS(song); //Chargement de la musique
    //Mix_PlayMusic(musique, -1); //Jouer infiniment la musique
    
    return musique;
}

void Stop_song(Mix_Music *musique){
    
    // Mix_FreeMusic(musique); //Libération de la musique
    Mix_CloseAudio();
}

Mix_Music* Play_effect(int track){
    
    char* song;
    
    song = list_effect(track);
    
    if (Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 4096 ) == -1 )
    {
        fprintf(stdout,"Échec de chargement de la musique (%s)\n",SDL_GetError());
    }
    
    Mix_Music *musique; //Création du pointeur de type Mix_Music
    musique = Mix_LoadMUS(song); //Chargement de la musique
    Mix_PlayMusic(musique, 1); //Jouer infiniment la musique
    
    return musique;
}