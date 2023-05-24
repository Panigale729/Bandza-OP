#include "stdnt.h"
#include "ivest_tikrinimai.h"


void galutinis_balas(studentas& asmuo) {

    int nd_suma = accumulate(asmuo.nd.begin(), asmuo.nd.end(), 0);

    double nd_pask_v = double(nd_suma) / asmuo.nd.size(); //vidurkis

    //mediana
    sort(asmuo.nd.begin(), asmuo.nd.end());
    double nd_pask_m;

    if (asmuo.nd.size() == 1) {
        nd_pask_m = asmuo.nd[0];
    }
    else if (asmuo.nd.size() % 2 != 0) {
        nd_pask_m = asmuo.nd[asmuo.nd.size() / 2];
    }
    else {
        nd_pask_m = (asmuo.nd[asmuo.nd.size() / 2] + asmuo.nd[asmuo.nd.size() / 2 - 1]) / 2.0;
    }

    asmuo.galutinis_v = 0.4 * nd_pask_v + 0.6 * asmuo.egz;
    asmuo.galutinis_m = 0.4 * nd_pask_m + 0.6 * asmuo.egz;
}

bool rusiuoti_pavard(studentas& x, studentas& y) {
    return x.pavarde < y.pavarde;
}

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
