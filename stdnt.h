#pragma once

#include "mylib.h"


//strukt�ra studento
struct studentas {
    string vardas = "";
    string pavarde = "";
    vector<int> nd;       //nam� darb� pa�ymi� vektorius
    int egz = 0;          //egzamino pa�ymys
    double galutinis_v = 0; //galutinis pa�ymys = 0.4 * vidurkis (nd) + 0.6 * egz
    //double galutinis_m = 0; //galutinis pa�ymys = 0.4 * mediana (nd) + 0.6 * egz
};

void galutinis_balas(studentas& asmuo); //galutinio balo paskaiciavimas
bool rusiuoti_paz(const studentas& x,const studentas& y); //rusiavimui

deque<studentas> studentu_pildymas();      //pildome studentus
void asmens_pildymas(studentas& asmuo);   //u�pildome vieno studento duomenis
