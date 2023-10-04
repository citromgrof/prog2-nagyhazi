#ifndef MENU_ROGZITESE_FUGGVENYEK_H_INCLUDED
#define MENU_ROGZITESE_FUGGVENYEK_H_INCLUDED
//Egy termék adatainak láncolt listába való tárolásához szükséges struktúra
typedef struct menuAdat{
    char termek[51];
    int ar;
    struct menuAdat *kov;
}menuAdat;

int beolvasInt();
char *beolvasNev();
void menuFomenu();

#endif // MENU_ROGZITESE_FUGGVENYEK_H_INCLUDED
