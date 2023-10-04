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

//Számla nyomtatása megerõsítésének menüje
static int szamlanyomtatasMegerosites(){
    int menuPont;
        menuPont=beolvasInt();
        switch(menuPont){
        case 1:
            printf("Kifizetett összeg, számla törlése.\n");
            return 1;
            break;
        case 2:
            printf("Ki nem fizetett összeg, visszatérés a fõmenübe.\n");
            return 2;
            break;
        default:
            printf("Érvénytelen bemenet, kérem próbálja újra.\n");
            szamlanyomtatasMegerosites();
            break;
        }
}
//Billentyüzetrõl beolvasott sorszámú asztal számlájának 0-ra állítása ha a megerõsítés 1-et térít vissza
static void szamlaNyomtatasFajl(char const *fajlnev){
    int sorszam;
    int n;
    n=asztalSorok(fajlnev);
    printf("Az asztal sorszáma: ");
    sorszam=beolvasInt();
    if(sorszam>n || sorszam<1){
        printf("Nincs ilyen sorszámú asztal.\n");
        return;
    }
    asztalAdat *asztal=(asztalAdat*) malloc((n+1)*sizeof(asztalAdat));
    asztalBeolvas(asztal,fajlnev);
    if(asztal[sorszam].szamla==0){
        printf("Nincs számla az asztalnál.\n");
    }
    else{
        printf("-------------------------------\n");
        printf("A befizetendõ összeg: %dFt\n", asztal[sorszam].szamla);
        printf("-------------------------------\n");
        printf("Ki lett fizetve az összeg?\n1. Igen\n2. Nem\n");
        if(szamlanyomtatasMegerosites()==1){
        asztal[sorszam].szamla=0;
        rendelesFelvetelSegito(asztal,fajlnev,n);
        }
    }
    free(asztal);
}
//Számla nyomtatása menü
void szamlaNyomtatasMenu(){
    bool stop=false;
    while(stop!=true){
    printf("Az asztal elhelyezkedése: \n\t1.Terasz\n\t2. Földszint\n\t3. Emelet\n4. Visszatérés a fõmenübe.\n");
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
        printf("Érvénytelen bemenet, kérem próbálja újra.\n");

    }
    }
}

