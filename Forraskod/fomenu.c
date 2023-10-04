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

//F� men�
void foMenu(){
    bool stop=false;
    while(stop!=true){
    printf("---------------------------------------------------\n");
    printf("1. Rendl�s felv�tele.\n2. Sz�mla nyomtat�sa\n3. Men� r�gz�t�se.\n4. �j asztal felv�tele vagy egy megl�v� t�rl�se.\n5. Foglalts�gi t�rk�p.\n6. Program le�ll�t�sa.\n");
    int menuPont;
    menuPont=beolvasInt();
        switch(menuPont){
    case 1:
        //Rendel�s felv�tele
        rendelesFelvetelMenu();
        break;
    case 2:
        //Sz�mla nyomtat�sa
        szamlaNyomtatasMenu();
        break;
    case 3:
        //Men� r�gz�t�se
        menuFomenu();
        break;
    case 4:
        //�j asztalfelv�tele\t�rl�se
        asztalMenu();
        break;
    case 5:
        //Foglalts�gi t�rk�p
        fogalaltsagiTerkep();
        break;
    case 6:
        //Le�ll�t�s
        stop=true;
        break;
    default:
        printf("�rv�nytelen bemnet, k�rem pr�b�lja �jra.\n");
        break;
        }
    }
}
