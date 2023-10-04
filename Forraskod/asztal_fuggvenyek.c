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
//Egy �j asztal nyit�sa
static void asztalFelFajlba(char const *fajlnev){
    int fo,szamla=0;
    printf("H�ny szem�lyes legyen az asztal?\n");
    fo=beolvasInt();
    FILE *fp;
    fp = fopen(fajlnev, "a");
    if(fp==NULL){
        printf("%s f�jl megnyit�sa sikertelen.");
        return;
    }
    fprintf(fp,"%d %d\n", fo,szamla);
    if(fclose(fp)){
        printf("Hiba a %s f�jl bez�r�s�ban.\n", fajlnev);
        return;
    }
    printf("Asztal sikeresen felv�ve.\n");
}
//f�jlb�l olvas asztalokat
void asztalBeolvas(asztalAdat *asztal, char const *fajlnev){
    FILE *fp;
    fp = fopen(fajlnev, "r");
    if(fp==NULL){
        printf("%s nev� f�jl megnyit�sa sikertelen.",fajlnev);
        return;
    }
    int i=1;
    while(fscanf(fp,"%d %d",&asztal[i].ferohely,&asztal[i].szamla)==2){
        i++;
    }
    if(fclose(fp)){
        printf("Hiba a %s f�jl bez�r�s�ban.\n", fajlnev);
        return;
    }
}
//Visszat�r�ti h�ny sor van a f�jlban mem�riafogal�shoz
int asztalSorok(char const *fajlnev){
    int n=0;
    FILE *fp;
    fp = fopen(fajlnev,"r");
    if(fp==NULL){
        printf("%s f�jl megnyit�sa sikertelen.");
        return NULL;
    }
    int temp1,temp2;
    while(fscanf(fp,"%d %d",&temp1,&temp2)==2){
        n++;
    }
    if(fclose(fp)){
        printf("Hiba a %s f�jl bez�r�s�ban.\n", fajlnev);
        return NULL;
    }
    return n;
}
//beolvasott sorsz�m� asztalon k�v�l, minden m�st �r f�jlba
static void asztalTorolFajlba(char const *fajlnev){
    int sorszam;
    int n;
    n=asztalSorok(fajlnev);
    if(n==0){
        printf("Nincsenek adatok %s f�jlban\n",fajlnev);
        return;
    }
    printf("A t�r�lend� asztal sorsz�ma: ");
    sorszam=beolvasInt();
    if(sorszam<0 || sorszam>n+1){
        printf("Nincs ilyen sorsz�m� asztal.\n");
        return;
    }
    asztalAdat *asztal = (asztalAdat*) malloc((n+1) * sizeof(asztalAdat));
    asztalBeolvas(asztal,fajlnev);
    FILE *fp;
    fp = fopen(fajlnev, "w");
    if(fp==NULL){
        printf("Hiba a %s nev� f�jl megnyit�s�ban.\n");
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
        printf("Hiba a %s f�jl bez�r�s�ban.\n", fajlnev);
        return;
    }
    printf("Asztal sikeresen t�r�lve\n");
    free(asztal);
}
//�j asztal hozz�ad�sa men�
static void asztalFelvetel(){
    bool stop=false;
    while(stop!=true){
    printf("Hol van az �j asztal?\n\t1. Terasz\n\t2. F�ldszint\n\t3. Emelet\n4. Visszat�r�s a f�men�be.\n");
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
            printf("�rv�nytelen bemnet. K�rem pr�b�lja �jra.\n");
            break;
    }
    }
}
//Megl�v� asztal t�rl�se men�
static void asztalTorles(){
    bool stop=false;
    while(stop!=true){
    printf("Hol van a t�r�lend� asztal?\n\t1. Terasz\n\t2. F�ldszint\n\t3. Emelet\n4. Visszat�r�s a f�men�be.\n");
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
            printf("�rv�nytelen bemnet. K�rem pr�b�lja �jra.\n");

            break;
    }
    }
}
//Asztal kezel�s men�
void asztalMenu(){
    bool stop=false;
    while(stop!=true){
    printf("1. �j asztal felv�tele.\n2. Asztal t�rl�se.\n3. Visszat�r�s a f�men�be.\n");
    int menuPont;
    menuPont=beolvasInt();
    switch(menuPont){
    case 1:
        //asztalfelv�tel
        asztalFelvetel();
        stop=true;
        break;
    case 2:
        //asztal t�rles
        asztalTorles();
        stop=true;
        break;
    case 3:
        //f� men�
        stop=true;
        return;
        break;
    default:
        printf("�rv�nytelen bemnet. K�rem pr�b�lja �jra.\n");
        break;
    }
    }
}
