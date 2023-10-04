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
//int t�pus� v�ltoz� beolvas�sa, ha nem tud sikeresen beolvasni t�rli a v�ltoz� tartalm�t
int beolvasInt(){
    int sikerult, olvasott;
    sikerult = scanf("%d", &olvasott);
    while (sikerult != 1) {
        printf("Sz�mot kell megadni bemenetnek!\n");
        scanf("%*[^\n]");
        sikerult = scanf("%d", &olvasott);
    }
    return olvasott;
}
//v�gtelen hossz� string beolvas�sa, bet�nk�nt foglalja a string mem�ri�j�t
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
//billenty�zetr�l beolvassa a term�k adatait �s be�rja a f�jlba
static void termekFelvetel(){
    int ar;
    printf("A term�k neve: ");
    char *nev=beolvasNev();
    printf("A term�k �ra: ");
    ar=beolvasInt();
    FILE *fmenu;
    fmenu = fopen("menu.txt", "a");
    if(fmenu == NULL){
        printf("menu.txt nev� f�jl megnyit�sa sikertelen");
        return;
    }
    fprintf(fmenu,"%d %s\n",ar,nev);
    fclose(fmenu);
    free(nev);
    printf("Term�k sikeresen felv�ve a men�be.\n");
}
//a men� l�ncolt list�j�t t�lti fel f�jb�l
static menuAdat* beolvasMenu(){
    struct menuAdat *uj;
    struct menuAdat *utolso;
    utolso=uj=NULL;
    FILE *fp;
    fp=fopen("menu.txt","r");
    if(fp==NULL){
        printf("HIBA a f�jl megnyit�s�ban.\n");

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
//egy param�terk�nt �tvett elemet t�r�l a l�ncolt list�b�l
static void menuTorol(menuAdat **menu,char const *etel){
    bool figyelo=false;
    if(menu==NULL){
        printf("Hiba a t�rl�sben.\n");
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

    if(figyelo) printf("Term�k sikeresen t�r�lve a men�b�l.\n");
    else printf("Nem tal�lhato ilyen nev� term�k.\n");

}
//a l�ncolt lista tartalm�t f�jlba �rja
static void menuFajlbaIr(menuAdat *menu){
    if(menu==NULL){
        printf("Hiba a f�jlba �r�sba.\n");
        return;
    }
    FILE *fp;
    fp=fopen("menu.txt","w");
    if(fp==NULL){
        printf("Hiba a menu.txt f�jl megynit�s�ban.");
        return;
    }
    while(menu!=NULL){
        fprintf(fp,"%d %s\n",menu->ar,menu->termek);

        menu=menu->kov;
    }
    if(fclose(fp)){
        printf("Hiba a menu.txt f�jl bez�r�saban.\n");
        return;
    }
}
//l�ncolt lista felszabad�t�sa
void felszabadit(menuAdat *menu){
    while(menu!=NULL){
        menuAdat *temp=menu;
        menu=menu->kov;
        free(temp);
    }
}
//t�r�l egy billenyt�zetr�l beolvasott term�ket a men�b�l
static void termekTorles(){
    printf("A t�r�lend� term�k neve: ");
    char *nev=beolvasNev();
    menuAdat *menu;
    menu=beolvasMenu();
    menuTorol(&menu,nev);
    menuFajlbaIr(menu);
    free(nev);
    felszabadit(menu);
}
//men� ki�rat�sa a k�perny�re
static void menuPrint(){
    FILE *fp;
    fp=fopen("menu.txt","r");
    bool figyel=false;
    if(fp==NULL){
        printf("menu.txt nev� f�jl megnyit�sa sikertelen.\n");
        return;
    }
    int tempAr;
    char tempNev[51];
    while(fscanf(fp,"%d %[^\n]",&tempAr,tempNev)==2){
        printf("%s\t%dFt\n",tempNev,tempAr);
        figyel=true;
    }
    if(figyel==false){
        printf("menu.txt nev� f�jl �res.\n");
    }
    if(fclose(fp)){
        printf("menu.txt nev� f�jl bez�r�sa sikertelen.\n");
        return;
    }
}
//Men� r�gz�t�se men�je
void menuFomenu(){
    bool stop=false;
    while(stop!=true){
    printf("1. �j term�k felv�tele a men�be.\n2. Term�k t�rl�se a men�b�l.\n3. Men� megjelen�t�se.\n4 Visszat�r�s a f�men�be.\n");
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
        printf("�rv�nytelen bemnet. K�rem pr�b�lja �jra.\n");
        break;
    }
    }
}
