#include <stdio.h>
#include <stdlib.h>
#include "fomenu.h"
#include "menu_rogzitese_fuggvenyek.h"
#include "asztal_fuggvenyek.h"
#include "rendeles_felvetele.h"
#include "foglaltsagi_terkep_fuggvenyek.h"
#include "szamlazas_fuggvenyek.h"
#include "debugmalloc.h"
//Kiírja azokat az asztalokat ahol a számla 0
static void uresAsztalok(char *fajlnev){
    int i=0;
    int db=0;
    FILE *fp;
    fp =fopen(fajlnev,"r");\
    if(fp==NULL){
        printf("Hiba a %s nevû fájl megnyitásában.\n");
        return;
    }
    int tempFerohely,tempSzamla;
    while(fscanf(fp,"%d %d",&tempFerohely,&tempSzamla)==2){
        i++;
        if(tempSzamla==0){
            printf("\t%d sorszámú asztal %d férõhely.\n",i,tempFerohely);
        }
        else{
            db++;
        }
    }
    if(i==db)
        printf("\tNincs üres asztal.\n");
}
//Minden helységben az üres asztalok kiíratása
void fogalaltsagiTerkep(){
    printf("Üres asztalok:\n");
    printf("Terasz:\n");
    uresAsztalok("terasz.txt");
    printf("Földszint:\n");
    uresAsztalok("foldszint.txt");
    printf("Emelet:\n");
    uresAsztalok("emelet.txt");
}
