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
//a menübõl egy termék árát térítí vissza ha nem kapott olyan nevet NULL-ot
static int termekAr(char const *termek){
    FILE *fp;
    fp=fopen("menu.txt","r");
    if(fp==NULL){
        printf("Hiba a menu.txt fájl megnyitásában.\n");
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
//fájlba írja az asztalakot a számla módosítása után
void rendelesFelvetelSegito(asztalAdat *asztal,char const *fajlnev,int const n){
    FILE *fp;
    fp = fopen(fajlnev, "w");
    if(fp==NULL){
        printf("Hiba a %s nevû fájl megnyitásában.\n");
        return;
    }
    for(int i=1;i<n+1;i++){
        fprintf(fp,"%d %d\n",asztal[i].ferohely,asztal[i].szamla);
    }
    if(fclose(fp)){
        printf("Hiba a %s fájl bezárásában: %s.\n", fajlnev);
        return;
    }
}
//egy beolvasott termék árát hozzáadja a szintét beolvasott sorszámú asztal számálájához(rendelést vesz fel)
static void rendelesFelvetelFajl(char const *fajlnev){
    int sorszam;
    int n;
    n=asztalSorok(fajlnev);
    printf("Az asztal sorszáma: ");
    sorszam=beolvasInt();
    if(sorszam>n || sorszam<1){
        printf("Nincs ilyen sorszámú asztal.\n");
        return;
    }
    printf("A rendelendõ termék neve: ");
    char *termek=beolvasNev();
    asztalAdat *asztal=(asztalAdat*) malloc((n+1)*sizeof(asztalAdat));
    asztalBeolvas(asztal,fajlnev);
    int ar;
    ar=termekAr(termek);
    if(ar==NULL){
        printf("A menüben nincs ilyen nevû termék.\n");
        return;
    }
    asztal[sorszam].szamla+=ar;
    rendelesFelvetelSegito(asztal,fajlnev,n);
    free(termek);
    free(asztal);
    printf("Rendelés sikeresen felvéve.\n");
}
//Rendelés felvétele menüje
void rendelesFelvetelMenu(){
    bool stop=false;
    while(stop!=true){
    printf("Az asztal elhelyezkedése: \n\t1. Terasz\n\t2. Földszint\n\t3. Emelet\n4. Visszatérés a fõmenübe.\n");
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
        printf("Érvénytelen bemenet, kérem próbálja újra.\n");
    }
    }
}
