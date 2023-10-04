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
//Egy új asztal nyitása
static void asztalFelFajlba(char const *fajlnev){
    int fo,szamla=0;
    printf("Hány személyes legyen az asztal?\n");
    fo=beolvasInt();
    FILE *fp;
    fp = fopen(fajlnev, "a");
    if(fp==NULL){
        printf("%s fájl megnyitása sikertelen.");
        return;
    }
    fprintf(fp,"%d %d\n", fo,szamla);
    if(fclose(fp)){
        printf("Hiba a %s fájl bezárásában.\n", fajlnev);
        return;
    }
    printf("Asztal sikeresen felvéve.\n");
}
//fájlból olvas asztalokat
void asztalBeolvas(asztalAdat *asztal, char const *fajlnev){
    FILE *fp;
    fp = fopen(fajlnev, "r");
    if(fp==NULL){
        printf("%s nevû fájl megnyitása sikertelen.",fajlnev);
        return;
    }
    int i=1;
    while(fscanf(fp,"%d %d",&asztal[i].ferohely,&asztal[i].szamla)==2){
        i++;
    }
    if(fclose(fp)){
        printf("Hiba a %s fájl bezárásában.\n", fajlnev);
        return;
    }
}
//Visszatéríti hány sor van a fájlban memóriafogaláshoz
int asztalSorok(char const *fajlnev){
    int n=0;
    FILE *fp;
    fp = fopen(fajlnev,"r");
    if(fp==NULL){
        printf("%s fájl megnyitása sikertelen.");
        return NULL;
    }
    int temp1,temp2;
    while(fscanf(fp,"%d %d",&temp1,&temp2)==2){
        n++;
    }
    if(fclose(fp)){
        printf("Hiba a %s fájl bezárásában.\n", fajlnev);
        return NULL;
    }
    return n;
}
//beolvasott sorszámú asztalon kívül, minden mást ír fájlba
static void asztalTorolFajlba(char const *fajlnev){
    int sorszam;
    int n;
    n=asztalSorok(fajlnev);
    if(n==0){
        printf("Nincsenek adatok %s fájlban\n",fajlnev);
        return;
    }
    printf("A törölendõ asztal sorszáma: ");
    sorszam=beolvasInt();
    if(sorszam<0 || sorszam>n+1){
        printf("Nincs ilyen sorszámú asztal.\n");
        return;
    }
    asztalAdat *asztal = (asztalAdat*) malloc((n+1) * sizeof(asztalAdat));
    asztalBeolvas(asztal,fajlnev);
    FILE *fp;
    fp = fopen(fajlnev, "w");
    if(fp==NULL){
        printf("Hiba a %s nevû fájl megnyitásában.\n");
        return;
    }
    if(sorszam==n){
        for(int i=1;i<n;i++){
            fprintf(fp, "%d %d\n", asztal[i].ferohely, asztal[i].szamla);
        }
    }
    else{
        for(int i=sorszam;i<n;i++){
            asztal[i].ferohely=asztal[i+1].ferohely;
            asztal[i].szamla=asztal[i+1].szamla;
        }

        for(int i=1;i<n;i++){
            fprintf(fp,"%d %d\n",asztal[i].ferohely,asztal[i].szamla);
        }
    }
    if(fclose(fp)){
        printf("Hiba a %s fájl bezárásában.\n", fajlnev);
        return;
    }
    printf("Asztal sikeresen törölve\n");
    free(asztal);
}
//Új asztal hozzáadása menü
static void asztalFelvetel(){
    bool stop=false;
    while(stop!=true){
    printf("Hol van az új asztal?\n\t1. Terasz\n\t2. Földszint\n\t3. Emelet\n4. Visszatérés a fõmenübe.\n");
    int menuPont;
    menuPont=beolvasInt();
    switch(menuPont){
        case 1:
            asztalFelFajlba("terasz.txt");
            stop=true;
            break;
        case 2:
            asztalFelFajlba("foldszint.txt");
            stop=true;
            break;
        case 3:
            asztalFelFajlba("emelet.txt");
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
//Meglévõ asztal törlése menü
static void asztalTorles(){
    bool stop=false;
    while(stop!=true){
    printf("Hol van a törölendõ asztal?\n\t1. Terasz\n\t2. Földszint\n\t3. Emelet\n4. Visszatérés a fõmenübe.\n");
    int menuPont;
    menuPont=beolvasInt();
    switch(menuPont){
        case 1:
            asztalTorolFajlba("terasz.txt");
            stop=true;
            break;
        case 2:
            asztalTorolFajlba("foldszint.txt");
            stop=true;
            break;
        case 3:
            asztalTorolFajlba("emelet.txt");
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
//Asztal kezelés menü
void asztalMenu(){
    bool stop=false;
    while(stop!=true){
    printf("1. Új asztal felvétele.\n2. Asztal törlése.\n3. Visszatérés a fõmenübe.\n");
    int menuPont;
    menuPont=beolvasInt();
    switch(menuPont){
    case 1:
        //asztalfelvétel
        asztalFelvetel();
        stop=true;
        break;
    case 2:
        //asztal törles
        asztalTorles();
        stop=true;
        break;
    case 3:
        //fõ menü
        stop=true;
        return;
        break;
    default:
        printf("Érvénytelen bemnet. Kérem próbálja újra.\n");
        break;
    }
    }
}
