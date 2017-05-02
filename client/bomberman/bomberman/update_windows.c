//
//  update_windows.c
//  Bomberman
//
//  Created by agbo anthony on 13/07/2016.
//  Copyright (c) 2016 agbo anthony. All rights reserved.
//

#include "client.h"
//fonctions servant a updater l'affichage des windows
void Update_IP_Windows(SDL_Renderer* renderer, char* text, SDL_Window* window){
    
    SDL_Color textColor;
    SDL_Rect solidRect;
    SDL_Texture* solidTexture;
    TTF_Font* font;
    int space[4];
    char* acceuil;
    
    acceuil = "Taper l'adddresse IP et le port à rentrer de format x x x x @port";
    SDL_RenderClear(renderer);
    
    // text couleur blanche
    textColor.a = 255;
    textColor.b = 255;
    textColor.g = 255;
    textColor.r = 255;
    //tableau de coordonnée x,y,w,h
    space[0] = 0;
    space[1] = 0;
    space[2] = 1000;
    space[3] = 1000;
    //utilisation de la police
    font = Create_font("/System/Library/Fonts/Helvetica.dfont", 12);
    solidRect = CreateSolid_Rect(0, 0, 100, 500);
    if (strlen(text) == 0){
        solidTexture = CreateSolidTexture(font, textColor, acceuil, renderer, space);
    } else {
        solidTexture = CreateSolidTexture(font, textColor, text, renderer, space);
    }
    
    // Render our text objects ( like normal )
    //SDL_RenderCopy(render, BlueShapes, NULL, &Rect_dest);
    SDL_RenderCopy(renderer, solidTexture, NULL, &solidRect);

    // Render the changes above
    SDL_RenderPresent(renderer);
}

void Update_Windows(SDL_Renderer* renderer, SDL_Window* window){
    SDL_RenderClear(renderer);
    
    // Render the changes above
    SDL_RenderPresent(renderer);
}
