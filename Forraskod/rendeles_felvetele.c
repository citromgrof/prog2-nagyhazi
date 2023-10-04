#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "fomenu.h"
#include "menu_rogzitese_fuggvenyek.h"
#include "asztal_fuggvenyek.h"
#include "rendeles_felvetele.h"
#include "foglaltsagi_terkep_fuggvenyek.h"
#include "szamlazas_fuggvenyek.h"
#include "debugmalloc.h"
//a men�b�l egy term�k �r�t t�r�t� vissza ha nem kapott olyan nevet NULL-ot
static int termekAr(char const *termek){
    FILE *fp;
    fp=fopen("menu.txt","r");
    if(fp==NULL){
        printf("Hiba a menu.txt f�jl megnyit�s�ban.\n");
        return;
    }
    int tempAr;
    char tempNev[51];
    while(fscanf(fp,"%d %[^\n]",&tempAr,tempNev)==2){
        if(strcmp(tempNev,termek)==0){
            return tempAr;
        }
    }
    return NULL;
}
//f�jlba �rja az asztalakot a sz�mla m�dos�t�sa ut�n
void rendelesFelvetelSegito(asztalAdat *asztal,char const *fajlnev,int const n){
    FILE *fp;
    fp = fopen(fajlnev, "w");
    if(fp==NULL){
        printf("Hiba a %s nev� f�jl megnyit�s�ban.\n");
        return;
    }
    for(int i=1;i<n+1;i++){
        fprintf(fp,"%d %d\n",asztal[i].ferohely,asztal[i].szamla);
    }
    if(fclose(fp)){
        printf("Hiba a %s f�jl bez�r�s�ban: %s.\n", fajlnev);
        return;
    }
}
//egy beolvasott term�k �r�t hozz�adja a szint�t beolvasott sorsz�m� asztal sz�m�l�j�hoz(rendel�st vesz fel)
static void rendelesFelvetelFajl(char const *fajlnev){
    int sorszam;
    int n;
    n=asztalSorok(fajlnev);
    printf("Az asztal sorsz�ma: ");
    sorszam=beolvasInt();
    if(sorszam>n || sorszam<1){
        printf("Nincs ilyen sorsz�m� asztal.\n");
        return;
    }
    printf("A rendelend� term�k neve: ");
    char *termek=beolvasNev();
    asztalAdat *asztal=(asztalAdat*) malloc((n+1)*sizeof(asztalAdat));
    asztalBeolvas(asztal,fajlnev);
    int ar;
    ar=termekAr(termek);
    if(ar==NULL){
        printf("A men�ben nincs ilyen nev� term�k.\n");
        return;
    }
    asztal[sorszam].szamla+=ar;
    rendelesFelvetelSegito(asztal,fajlnev,n);
    free(termek);
    free(asztal);
    printf("Rendel�s sikeresen felv�ve.\n");
}
//Rendel�s felv�tele men�je
void rendelesFelvetelMenu(){
    bool stop=false;
    while(stop!=true){
    printf("Az asztal elhelyezked�se: \n\t1. Terasz\n\t2. F�ldszint\n\t3. Emelet\n4. Visszat�r�s a f�men�be.\n");
    int menuPont;
    menuPont=beolvasInt();
    switch(menuPont){
    case 1:
        rendelesFelvetelFajl("terasz.txt");
        stop=true;
        break;
    case 2:
        rendelesFelvetelFajl("foldszint.txt");
        stop=true;
        break;
    case 3:
        rendelesFelvetelFajl("emelet.txt");
        stop=true;
        break;
    case 4:
        stop=true;
        return;
        break;
    default:
        printf("�rv�nytelen bemenet, k�rem pr�b�lja �jra.\n");
    }
    }
}
