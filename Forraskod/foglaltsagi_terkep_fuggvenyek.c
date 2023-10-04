#include <stdio.h>
#include <stdlib.h>
#include "fomenu.h"
#include "menu_rogzitese_fuggvenyek.h"
#include "asztal_fuggvenyek.h"
#include "rendeles_felvetele.h"
#include "foglaltsagi_terkep_fuggvenyek.h"
#include "szamlazas_fuggvenyek.h"
#include "debugmalloc.h"
//Ki�rja azokat az asztalokat ahol a sz�mla 0
static void uresAsztalok(char *fajlnev){
    int i=0;
    int db=0;
    FILE *fp;
    fp =fopen(fajlnev,"r");\
    if(fp==NULL){
        printf("Hiba a %s nev� f�jl megnyit�s�ban.\n");
        return;
    }
    int tempFerohely,tempSzamla;
    while(fscanf(fp,"%d %d",&tempFerohely,&tempSzamla)==2){
        i++;
        if(tempSzamla==0){
            printf("\t%d sorsz�m� asztal %d f�r�hely.\n",i,tempFerohely);
        }
        else{
            db++;
        }
    }
    if(i==db)
        printf("\tNincs �res asztal.\n");
}
//Minden helys�gben az �res asztalok ki�rat�sa
void fogalaltsagiTerkep(){
    printf("�res asztalok:\n");
    printf("Terasz:\n");
    uresAsztalok("terasz.txt");
    printf("F�ldszint:\n");
    uresAsztalok("foldszint.txt");
    printf("Emelet:\n");
    uresAsztalok("emelet.txt");
}
