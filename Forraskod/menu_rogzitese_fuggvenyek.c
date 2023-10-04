#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "fomenu.h"
#include "menu_rogzitese_fuggvenyek.h"
#include "asztal_fuggvenyek.h"
#include "rendeles_felvetele.h"
#include "foglaltsagi_terkep_fuggvenyek.h"
#include "szamlazas_fuggvenyek.h"
#include "debugmalloc.h"
//int típusú változó beolvasása, ha nem tud sikeresen beolvasni törli a változó tartalmát
int beolvasInt(){
    int sikerult, olvasott;
    sikerult = scanf("%d", &olvasott);
    while (sikerult != 1) {
        printf("Számot kell megadni bemenetnek!\n");
        scanf("%*[^\n]");
        sikerult = scanf("%d", &olvasott);
    }
    return olvasott;
}
//végtelen hosszú string beolvasása, betünként foglalja a string memóriáját
char *beolvasNev(){
    int   hossz = 2, utolso = 0;
    char *string=(char*) malloc(sizeof(char));
    getchar();
    while((string[utolso] = getchar()) != '\n' )
    {
         string = (char *) realloc(string, sizeof(char) * hossz);
         hossz++;
         utolso++;
    }
    string[utolso]='\0';
    return string;
}
//billentyüzetrõl beolvassa a termék adatait és beírja a fájlba
static void termekFelvetel(){
    int ar;
    printf("A termék neve: ");
    char *nev=beolvasNev();
    printf("A termék ára: ");
    ar=beolvasInt();
    FILE *fmenu;
    fmenu = fopen("menu.txt", "a");
    if(fmenu == NULL){
        printf("menu.txt nevû fájl megnyitása sikertelen");
        return;
    }
    fprintf(fmenu,"%d %s\n",ar,nev);
    fclose(fmenu);
    free(nev);
    printf("Termék sikeresen felvéve a menübe.\n");
}
//a menü láncolt listáját tölti fel fájból
static menuAdat* beolvasMenu(){
    struct menuAdat *uj;
    struct menuAdat *utolso;
    utolso=uj=NULL;
    FILE *fp;
    fp=fopen("menu.txt","r");
    if(fp==NULL){
        printf("HIBA a fájl megnyitásában.\n");

    }
    int tempAr;
    char tempNev[51];
    while(fscanf(fp,"%d %[^\n]",&tempAr,tempNev)==2){
        if(uj==NULL){
            uj=utolso=(menuAdat*) malloc(sizeof(menuAdat));
        }
        else{
            utolso->kov=(menuAdat*) malloc(sizeof(menuAdat));
            utolso=utolso->kov;
        }
        utolso->ar=tempAr;
        strcpy(utolso->termek,tempNev);
    }
    utolso->kov=NULL;
    fclose(fp);
    return uj;
}
//egy paraméterként átvett elemet töröl a láncolt listából
static void menuTorol(menuAdat **menu,char const *etel){
    bool figyelo=false;
    if(menu==NULL){
        printf("Hiba a törlésben.\n");
        return;
    }
    menuAdat *torolendo;
    if(strcmp((*menu)->termek,etel)==0){
        torolendo=*menu;
        *menu=(*menu)->kov;
        free(torolendo);
        figyelo=true;
    }
    else{
        struct menuAdat *uj=(*menu);
        while(uj->kov!=NULL){
            if(strcmp(uj->kov->termek,etel)==0){
            torolendo=uj->kov;
            uj->kov=uj->kov->kov;
            free(torolendo);
            figyelo=true;
            break;
            }
            else
                uj=uj->kov;
            }
    }

    if(figyelo) printf("Termék sikeresen törölve a menübõl.\n");
    else printf("Nem találhato ilyen nevû termék.\n");

}
//a láncolt lista tartalmát fájlba írja
static void menuFajlbaIr(menuAdat *menu){
    if(menu==NULL){
        printf("Hiba a fájlba írásba.\n");
        return;
    }
    FILE *fp;
    fp=fopen("menu.txt","w");
    if(fp==NULL){
        printf("Hiba a menu.txt fájl megynitásában.");
        return;
    }
    while(menu!=NULL){
        fprintf(fp,"%d %s\n",menu->ar,menu->termek);

        menu=menu->kov;
    }
    if(fclose(fp)){
        printf("Hiba a menu.txt fájl bezárásaban.\n");
        return;
    }
}
//láncolt lista felszabadítása
void felszabadit(menuAdat *menu){
    while(menu!=NULL){
        menuAdat *temp=menu;
        menu=menu->kov;
        free(temp);
    }
}
//töröl egy billenytüzetrõl beolvasott terméket a menübõl
static void termekTorles(){
    printf("A törölendõ termék neve: ");
    char *nev=beolvasNev();
    menuAdat *menu;
    menu=beolvasMenu();
    menuTorol(&menu,nev);
    menuFajlbaIr(menu);
    free(nev);
    felszabadit(menu);
}
//menü kiíratása a képernyõre
static void menuPrint(){
    FILE *fp;
    fp=fopen("menu.txt","r");
    bool figyel=false;
    if(fp==NULL){
        printf("menu.txt nevû fájl megnyitása sikertelen.\n");
        return;
    }
    int tempAr;
    char tempNev[51];
    while(fscanf(fp,"%d %[^\n]",&tempAr,tempNev)==2){
        printf("%s\t%dFt\n",tempNev,tempAr);
        figyel=true;
    }
    if(figyel==false){
        printf("menu.txt nevû fájl üres.\n");
    }
    if(fclose(fp)){
        printf("menu.txt nevû fájl bezárása sikertelen.\n");
        return;
    }
}
//Menü rögzítése menüje
void menuFomenu(){
    bool stop=false;
    while(stop!=true){
    printf("1. Új termék felvétele a menübe.\n2. Termék törlése a menübõl.\n3. Menü megjelenítése.\n4 Visszatérés a fõmenübe.\n");
    int menuPont;
    menuPont=beolvasInt();
    switch(menuPont){
    case 1:
        termekFelvetel();
        stop=true;
        break;
    case 2:
        termekTorles();
        stop=true;
        break;
    case 3:
        menuPrint();
        stop=true;
        break;
    case 4:
        stop=true;
        return;
        break;
    default:
        printf("Érvénytelen bemnet. Kérem próbálja újra.\n");
        break;
    }
    }
}
