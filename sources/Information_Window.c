//
//  Information_Window.c
//  Group_Project
//
//  Functions relating to tower monitor and stats monitor
//
//  Created by Michael on 10/11/2014.
//  Copyright (c) 2014 Michael. All rights reserved.
//

#include "../includes/Information_Window.h"
#include "../includes/tower.h"
#include "../includes/gameProperties.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_OUTPUT_STRING 200


void towerMonitor(unsigned int targetTower, char *optionalOutputString) {
    int time = SDL_GetTicks();
    static int lastTower = 0, timeOfCall = 0, optionalStringSet = 0;
    char *outputString;
    static char *optionalString = NULL;

    if(targetTower && !optionalOutputString) {
        outputString = getTowerString(targetTower);
        timeOfCall = SDL_GetTicks();
        lastTower = targetTower;
        optionalStringSet = 0;
    }
    else if(optionalOutputString) {
        outputString = optionalString = optionalOutputString;
        timeOfCall = SDL_GetTicks();
        optionalStringSet = 1;
    }
    else {
        outputString = getDefaultTowerString();
    }
    
    if(timeOfCall != 0 && time - timeOfCall < 10000) {
        if(optionalStringSet) {
            outputString = optionalString;
        }
        else {
            outputString = getTowerString(lastTower);
        }
    }
    
    if(time - timeOfCall > 10000) {
        optionalStringSet = 0;
    }
    
        updateTowerMonitor(outputString);
}

char *getDefaultTowerString() {
    
    char *outputString = malloc(MAX_OUTPUT_STRING);
    char towers[4];
    
    sprintf(outputString, "TOWER MONITOR\n\nActive Towers: ");
    sprintf(towers, "%d", getNumberOfTowers());
    
    strcat(outputString, towers);
    
    return outputString;
}

char *getTowerString(unsigned int targetTower) {
    
    int iRange, iDamage, iSpeed, iAOEpower, iAOErange;
    getStats(&iRange,&iDamage,&iSpeed,&iAOEpower,&iAOErange, targetTower);
    
    char *outputString = malloc(MAX_OUTPUT_STRING);
    char range[4], damage[4], speed[4], AOEdamage[4], AOErange[4];
    
    sprintf(outputString, "TOWER %d\n\nRange: ", targetTower);
    sprintf(range, "%d", iRange);
    sprintf(damage, "%d",iDamage);
    sprintf(speed, "%d", iSpeed);
    sprintf(AOEdamage, "%d",iAOEpower);
    sprintf(AOErange, "%d", iAOErange);

    strcat(outputString, range);
    strcat(outputString, "\nDamage : ");
    strcat(outputString, damage);
    strcat(outputString, "\nSpeed: ");
    strcat(outputString, speed);
    strcat(outputString, "\nAOE damage: ");
    strcat(outputString, AOEdamage);
    strcat(outputString, "\nAOE range: ");
    strcat(outputString, AOErange);
    
    return outputString;
}

void statsMonitor() {
    
    GameProperties properties = getGame(NULL);
    
    int iGold = getGold(properties);
    int iWaveNumber = getWave(properties);
    int iHealth = getHealth(properties);
    
    char outputString[200];
    
    char gold[5], waveNumber[5], health[5];
    
    sprintf(outputString, "\n               STATS MONITOR\n\nGold: ");
    sprintf(gold, "%d", iGold);
    sprintf(waveNumber, "%d", iWaveNumber);
    sprintf(health, "%d", iHealth);
    
    strcat(outputString, gold);
    strcat(outputString, "\nWave Number: ");
    strcat(outputString, waveNumber);
    strcat(outputString, "\nHealth: ");
    strcat(outputString, health);
    
    updateStatsMonitor(outputString);
}

/*void textToTowerMonitor(char *outputString) {
    static char *string = NULL;
    int time = SDL_GetTicks(), timeOfCallSet = 0;
    static int timeOfCall = 0;
    
    if(!timeOfCallSet) {
        timeOfCall = SDL_GetTicks();
        string = outputString;
    }
    
    if(time - timeOfCall > 10000) {
        outputString = getDefaultTowerString();
    }
    
    updateTowerMonitor(outputString);
    
}*/

void manUpgrade()
{
    towerMonitor(-1, "GENERAL COMMANDS MANUAL: \n\nupgrade\n\n type ""upgrade"" followed by a stat\n ( p, r, s, AOEp, AOEr)\n ) followed by a target tower\neg t1, t2, t3...\nExamples:\nupgrade r t2\nupgrade p t3");
}

void manCat()
{
    
    towerMonitor(-1, "GENERAL COMMANDS MANUAL: cat \n type ""cat"" followed by a target eg t1, t2, t3... to display the stats of that target\n");
}
void manMan()
{
    towerMonitor(-1, "GENERAL COMMANDS MANUAL: man \n type ""man"" followed by a command eg upgrade or cat to view the manual entry for that command\n");
}


