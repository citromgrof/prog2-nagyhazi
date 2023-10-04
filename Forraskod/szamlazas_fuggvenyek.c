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

//Sz�mla nyomtat�sa meger�s�t�s�nek men�je
static int szamlanyomtatasMegerosites(){
    int menuPont;
        menuPont=beolvasInt();
        switch(menuPont){
        case 1:
            printf("Kifizetett �sszeg, sz�mla t�rl�se.\n");
            return 1;
            break;
        case 2:
            printf("Ki nem fizetett �sszeg, visszat�r�s a f�men�be.\n");
            return 2;
            break;
        default:
            printf("�rv�nytelen bemenet, k�rem pr�b�lja �jra.\n");
            szamlanyomtatasMegerosites();
            break;
        }
}
//Billenty�zetr�l beolvasott sorsz�m� asztal sz�ml�j�nak 0-ra �ll�t�sa ha a meger�s�t�s 1-et t�r�t vissza
static void szamlaNyomtatasFajl(char const *fajlnev){
    int sorszam;
    int n;
    n=asztalSorok(fajlnev);
    printf("Az asztal sorsz�ma: ");
    sorszam=beolvasInt();
    if(sorszam>n || sorszam<1){
        printf("Nincs ilyen sorsz�m� asztal.\n");
        return;
    }
    asztalAdat *asztal=(asztalAdat*) malloc((n+1)*sizeof(asztalAdat));
    asztalBeolvas(asztal,fajlnev);
    if(asztal[sorszam].szamla==0){
        printf("Nincs sz�mla az asztaln�l.\n");
    }
    else{
        printf("-------------------------------\n");
        printf("A befizetend� �sszeg: %dFt\n", asztal[sorszam].szamla);
        printf("-------------------------------\n");
        printf("Ki lett fizetve az �sszeg?\n1. Igen\n2. Nem\n");
        if(szamlanyomtatasMegerosites()==1){
        asztal[sorszam].szamla=0;
        rendelesFelvetelSegito(asztal,fajlnev,n);
        }
    }
    free(asztal);
}
//Sz�mla nyomtat�sa men�
void szamlaNyomtatasMenu(){
    bool stop=false;
    while(stop!=true){
    printf("Az asztal elhelyezked�se: \n\t1.Terasz\n\t2. F�ldszint\n\t3. Emelet\n4. Visszat�r�s a f�men�be.\n");
    int menuPont;
    menuPont=beolvasInt();
    switch(menuPont){
    case 1:
        szamlaNyomtatasFajl("terasz.txt");
        stop=true;
        break;
    case 2:
        szamlaNyomtatasFajl("foldszint.txt");
        stop=true;
        break;
    case 3:
        szamlaNyomtatasFajl("emelet.txt");
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

