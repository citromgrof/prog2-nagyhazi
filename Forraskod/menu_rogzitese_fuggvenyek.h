#ifndef MENU_ROGZITESE_FUGGVENYEK_H_INCLUDED
#define MENU_ROGZITESE_FUGGVENYEK_H_INCLUDED
//Egy term�k adatainak l�ncolt list�ba val� t�rol�s�hoz sz�ks�ges strukt�ra
typedef struct menuAdat{
    char termek[51];
    int ar;
    struct menuAdat *kov;
}menuAdat;

int beolvasInt();
char *beolvasNev();
void menuFomenu();

#endif // MENU_ROGZITESE_FUGGVENYEK_H_INCLUDED
