#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "menu_rogzitese_fuggvenyek.h"
#include "asztal_fuggvenyek.h"
#include "rendeles_felvetele.h"
#include "foglaltsagi_terkep_fuggvenyek.h"
#include "szamlazas_fuggvenyek.h"
#include "debugmalloc.h"

//Fõ menü
void foMenu(){
    bool stop=false;
    while(stop!=true){
    printf("---------------------------------------------------\n");
    printf("1. Rendlés felvétele.\n2. Számla nyomtatása\n3. Menü rögzítése.\n4. Új asztal felvétele vagy egy meglévõ törlése.\n5. Foglaltsági térkép.\n6. Program leállítása.\n");
    int menuPont;
    menuPont=beolvasInt();
        switch(menuPont){
    case 1:
        //Rendelés felvétele
        rendelesFelvetelMenu();
        break;
    case 2:
        //Számla nyomtatása
        szamlaNyomtatasMenu();
        break;
    case 3:
        //Menü rögzítése
        menuFomenu();
        break;
    case 4:
        //Új asztalfelvétele\törlése
        asztalMenu();
        break;
    case 5:
        //Foglaltsági térkép
        fogalaltsagiTerkep();
        break;
    case 6:
        //Leállítás
        stop=true;
        break;
    default:
        printf("Érvénytelen bemnet, kérem próbálja újra.\n");
        break;
        }
    }
}
