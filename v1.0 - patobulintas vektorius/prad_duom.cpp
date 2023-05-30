#include "darb_su_fail.h"
#include "mylib.h"
#include "generavimas.h"
#include "ivest_tikrinimai.h"
#include "stdnt.h"

#include <string>
#include <vector>
#include <algorithm>
#include <execution>


//-------------------------------------------------------------------------------------------------------------------------------------------------------
//GAUNAME PRADINIUS STUDENTU DUOMENIS

void darbas_su_generuotais(vector<studentas>& grupe, bool skirstymas) {
    long long int stud_sk = 1000; //maziausias failas
    int n = 0;

    vector<studentas> silpnuciai;
    vector<studentas> gudruciai;

    cout << "Jeigu nenorite dirbti su (is anksto) sugeneruotais failais - iveskite �1�\n";
    cout << "Jeigu norite dirbti su (is anksto) sugeneruotais failais - iveskite �0�\n";

    bool generavimas_fail;
    generavimas_fail = tikrinti_bool();


    for (auto& i : input_files) {

        auto start = hrclock::now(); // matuosime laika

        cout << endl << "Failo dydis:" << stud_sk << endl;
        if(generavimas_fail) generavimas(i, stud_sk);
        skaitymas(i, grupe);    //reikia laiko
        rikiavimas(grupe);      //reikia laiko

        //spausdinimas(grupe, sorted[n]);

        if (skirstymas) {
            skirstymas_2(grupe, silpnuciai, gudruciai); //i 2 naujus vektorius, istrinant sena. reikia laiko
            spausdinimas(silpnuciai, silpnuciai_out[n]);
            spausdinimas(gudruciai, gudruciai_out[n]);
        }
        else {
            skirstymas_1(grupe, silpnuciai);  //Nauju budu: tik silpnucius iskelti i atskira faila
            spausdinimas(silpnuciai, silpnuciai_out[n]);
            spausdinimas(grupe, gudruciai_out[n]);
        }

        duration diff = hrclock::now() - start;

       // cout << endl << stud_sk << " irasu testo laikas: " << diff.count() << "s" << endl;

        stud_sk *= 10;
        n++;
        system("pause");

        grupe.clear();
        silpnuciai.clear();
        gudruciai.clear();

    }
}



void darbas_su_paruostais(vector<studentas>& grupe) {
    string isvest_fail = "txt_failai/kursiokai.txt";

    cout << "Pasirinkite student� fail�: " << endl;
    cout << "1. studentai1000000.txt" << endl;
    cout << "2. studentai100000.txt" << endl;
    cout << "3. studentai10000.txt" << endl;
    cout << "�veskite pasirinkimo numer�: ";

    bool gera_ivest = false;
    int pasirinkimas;

    //tikriname ivesti
    while (!gera_ivest) {

        while (!(cin >> pasirinkimas)) {
            cin.clear(); // pasaliname error flag`us
            cin.ignore(INT_MAX, '\n'); // praignoruojame bloga ivesti
            cout << "Iveskite teising� pasirinkimo numer� (1-3): ";
        }
        cin.ignore(); // ignoruojame \n

        if (pasirinkimas >= 1 && pasirinkimas <= 3) {
            gera_ivest = true;
        }
        else {
            cout << "Iveskite teising� pasirinkimo numer� (1-3): ";
        }
    }

    string skait_fail;

    if (pasirinkimas == 1) {
        skait_fail = "txt_failai/studentai1000000.txt";
    }
    else if (pasirinkimas == 2) {
        skait_fail = "txt_failai/studentai100000.txt";
    }
    else if (pasirinkimas == 3) {
        skait_fail = "txt_failai/studentai10000.txt";
    }

    cout << endl << "*Vyksta skaitymas is failo ir isvedimas*\n" << endl;

    try {
        skaitymas(skait_fail, grupe); //skaitymas ir �ra�ymas vyksta per buffer`�. Is karto pildome studentus.
    }
    catch (const exception& e) {
        cout << "Klaida vykdant program�: " << e.what() << endl;
        return;
    }

    rikiavimas(grupe);

    spausdinimas(grupe, isvest_fail);

}



void darbas_su_ivedimu(vector<studentas>& grupe) {
    string isvest_fail = "txt_failai/kursiokai.txt";

    try {
        grupe = studentu_pildymas();
    }
    catch (const exception& e) {
        cout << "Klaida vykdant program�: " << e.what() << endl;
        return;
    }

    spausdinimas(grupe, isvest_fail);

}

//-----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
//DARBAS SU IVEDIMU

vector<studentas> studentu_pildymas() {

    bool testi = true;
    vector<studentas> grupe;

    while (testi) { //tikrinam, ar vartotojas nori �vesti dar student� + �vedimas

        grupe.push_back(studentas());   //pridedame nauj� student� � vektori�.
        asmens_pildymas(grupe.back());   //pildome paskutinio prid�to studento duomenis
        galutinis_balas(grupe.back());

        //ar t�sti toliau �vedin�ti studentus?
        cout << "Jeigu norite t�sti student� �vedim� - �veskite �1�" << endl << "Jeigu nenorite t�sti studento �vedimo - �veskite �0�" << endl << endl;
        testi = tikrinti_bool();
    }

    rikiavimas(grupe);

    return grupe;
}


void asmens_pildymas(studentas& asmuo) { //u�pildome vieno studento duomenis

    //vardas, pavard�
    asmuo.vardas = tikrinti_vard(1);
    asmuo.pavarde = tikrinti_vard(2);

    //pa�ymiai
    int paz_sk = 0;
    double nd_pask = 0; //paskai�iuota pagal vidurk� arba median�

    //�i�rime, ar vartotojas nori, jog pa�ymiai (ir j� skai�ius), egzamino balas b�t� sugeneruojami atsitiktinai
    bool generuoti;

    cout << endl << "Jeigu norite t�sti, jog pa�ymi� skai�ius, pa�ymiai ir egzamino balas b�t� generuojami atsitiktinai �veskite �1�" << endl;
    cout << "Jeigu nenorite atsitiktinio generavimo �veskite �0�" << endl;
    generuoti = tikrinti_bool();

    if (generuoti) {
        //pagerintas atsitiktinio skai�iaus generavimas
        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<int> paz_sk_dist(3, 10);
        uniform_int_distribution<int> paz_dist(0, 10);

        paz_sk = paz_sk_dist(gen);
        asmuo.nd.resize(paz_sk); //resizinam`e vektori� atitinkamai

        for (int i = 0; i < paz_sk; i++) {  //u�pildome nd vektori� pa�ymiais
            asmuo.nd[i] = paz_dist(gen); //generuojame nuo 0 iki 10
        }

        asmuo.egz = paz_dist(gen);  //generuojame nuo 0 iki 10

    }
    else {

        //nam� darb� pa�ymiai
        cout << "�veskite pa�ymius (nuo 0 iki 10):" << endl;
        cout << "Norint baigti pa�ymi� �vedim�, �veskite bet kok� simbol�/-ius (i�skyrus pa�ymius):" << endl;

        asmuo.nd.reserve(10); //u�rezervuojame vietos 10 pa�ymi� (kiek ir atsitiktinai generuojam). I�vengsim nereikalingo atminties perskirstymo.

        int p; //vienas pa�ymys

        while (cin >> p && p >= 0 && p <= 10) {
            //Rei�kia �ved� pa�ym�
            asmuo.nd.push_back(p);
        }

        asmuo.nd.shrink_to_fit(); //kad element� skai�ius vektoriuje sutapt� su jo dyd�iu

        cin.clear(); //i�triname error flag`us
        cin.ignore(INT_MAX, '\n'); //praignoruojame, kas liko i� neteisingos �vesties


        if (asmuo.nd.empty()) {
            throw runtime_error("Studento " + asmuo.vardas + " " + asmuo.pavarde + " nam� darb� pa�ymi� n�ra.");
        }

        cout << "�veskite egzamino pa�ym�: " << endl;
        asmuo.egz = tikrinti_pazymi();
    }

    cout << "�io studento duomenys s�kmingai �ra�yti" << endl << endl;
}