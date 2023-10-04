#ifndef ASZTAL_FUGGVENYEK_H_INCLUDED
#define ASZTAL_FUGGVENYEK_H_INCLUDED
//Egy asztal adatainak eltárolásához szükséges sutruktúra
typedef struct asztalAdat{
    int szamla;
    int ferohely;
}asztalAdat;
void asztalBeolvas(asztalAdat *asztal, char const *fajlnev);
int asztalSorok(char const *fajlnev);
void asztalMenu();

#endif // ASZTAL_FUGGVENYEK_H_INCLUDED
