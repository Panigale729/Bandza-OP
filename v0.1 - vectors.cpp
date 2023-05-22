#include "Mylib.h"


//strukt�ra studento
struct studentas {
    string vardas = "";
    string pavarde = "";
    vector<int> nd;       //nam� darb� pa�ymi� vektorius
    int egz = 0;          //egzamino pa�ymys
    double galutinis = 0; //galutinis pa�ymys = 0.4 * vidurkis/mediana (nd) + 0.6 * egz
};


//funkcijos deklaracijos
char pradzia();                                   //pradinis tekstas + pasirinkimas, kaip skai�iuoti galutin� bal�

vector<studentas> studentu_pildymas(char x);     //pildome studentus
void asmens_pildymas(studentas& asmuo, char x);   //u�pildome vieno studento duomenis

int tikrinti_pazymi();                            //tikriname, ar �vestas pa�ymys yra nuo 0 iki 10
string tikrinti_vard(int v);                      //tikriname, ar vardas/pavard� sudaryta/-as tik i� raid�i�
bool tikrinti_bool();                             //tikriname, ar �ved� bool reik�m�

void spausdinti(char x, vector<studentas>& grupe); //spausdinimas
void asmens_spausdinimas(studentas& asmuo);        //spausdiname vieno studento rezultatus

string didziosios(string a);                      //Ver�ia vardo ir pavard�s raides � did�i�sias



int main()
{
    setlocale(LC_ALL, "Lithuanian"); //�galiname lietuvi�kas raides

    // PROGRAMOS PRAD�IA
    char x = pradzia(); // x yra 'v' - vidurkiui arba 'm' - medianai

    // STUDENT� �VEDIMAS (�VEDAME STUDENT�, KIEK TIK NORIME)
    vector<studentas> grupe = studentu_pildymas(x);

    // SPAUSDINIMAS
    spausdinti(x, grupe);
}



char pradzia() {
    cout << "Paleidote program�, skirt� studento galutiniam balui apskai�iuoti." << endl;
    cout << "Galutinis balas = 0.4 * nam� darb� pa�ymi� vidurkis/mediana + 0.6 * egzamino pa�ymys." << endl << endl;
    cout << "Pasirinkite, k� naudosite galutinio balo skai�iavimui: " << endl;
    cout << "Vidurk� - �veskite raid� �v�. " << endl;
    cout << "Median� - �veskite raid� �m�. " << endl;
    cout << "J�s� pasirinkimas: ";

    string a;
    getline(cin, a);
    //tikriname �vest�
    while (a != "v" && a != "m") {
        cout << "Neteisinga �vestis. Bandykite dar kart� (�veskite: �v� arba �m�). " << endl;
        getline(cin, a);
    }

    cout << "Pasirinkimas i�saugotas." << endl << endl;
    cout << "Prad�kite student� �vedim�." << endl << endl;

    char x = a[0];

    return x;
}



vector<studentas> studentu_pildymas(char x) {

    bool testi = true;
    vector<studentas> grupe;

    while (testi) { //tikrinam, ar vartotojas nori �vesti dar student� + �vedimas

        grupe.push_back(studentas());   //pridedame nauj� student� � vektori�.
        asmens_pildymas(grupe.back(), x);   //pildome paskutinio prid�to studento duomenis

        //ar t�sti toliau �vedin�ti studentus?
        cout << "Jeigu norite t�sti student� �vedim� - �veskite �1�" << endl << "Jeigu nenorite t�sti studento �vedimo - �veskite �0�" << endl << endl;
        testi = tikrinti_bool();
    }

    return grupe;
}



void asmens_pildymas(studentas& asmuo, char x) { //u�pildome vieno studento duomenis

    //vardas, pavard�
    asmuo.vardas = tikrinti_vard(1);
    asmuo.pavarde = tikrinti_vard(2);

    //pa�ymiai
    int nd_suma = 0;
    int paz_sk = 0;
    double nd_pask = 0; //paskai�iuota pagal vidurk� arba median�

    //�i�rime, ar vartotojas nori, jog pa�ymiai (ir j� skai�ius), egzamino balas b�t� sugeneruojami atsitiktinai
    bool generuoti;

    cout << endl << "Jeigu norite t�sti, jog pa�ymi� skai�ius, pa�ymiai ir egzamino balas b�t� generuojami atsitiktinai �veskite �1�" << endl;
    cout << "Jeigu nenorite atsitiktinio generavimo �veskite �0�" << endl;
    generuoti = tikrinti_bool();

    if (generuoti) {
        srand(time(NULL)); //nustatome seed`� atsitiktinio generatoriaus

        int paz_sk = rand() % 8 + 3; //sugeneruojame atsitiktin� skai�i� pa�ymi� (nuo 3 iki 10)
        asmuo.nd.resize(paz_sk); //resizinam`e vektori� atitinkamai

        for (int i = 0; i < paz_sk; i++) {  //u�pildome nd vektori� pa�ymiais
            asmuo.nd[i] = rand() % 11; 
        }

        asmuo.egz = rand() % 11; //generuojame nuo 0 iki 10

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
            nd_suma += p; //pa�ymi� suma
        }

        asmuo.nd.shrink_to_fit(); //kad element� skai�ius vektoriuje sutapt� su jo dyd�iu

        cin.clear(); //i�triname error flag`us
        cin.ignore(INT_MAX, '\n'); //praignoruojame, kas liko i� neteisingos �vesties


        //jeigu nebuvo �vesta pa�ymi�
        if (asmuo.nd.empty()) {
            cout << "Neuvo �vesta nei vieno pa�ymio �iam studentui." << endl;

            if (x == 'v') {
                cout << "Nam� darb� vidurkis bus laikomas 0." << endl;
            }
            else {
                cout << "Nam� darb� mediana bus laikoma 0." << endl;
            }

            nd_pask = 0;

        };

        cout << "�veskite egzamino pa�ym�: " << endl;
        asmuo.egz = tikrinti_pazymi();
    }

    //ska�iuojame galutin� bal�

    //skai�iuojame nd galutin� pagal vidurk�
    if (!asmuo.nd.empty()) {    //jeinu pa�ymi� vektorius n�ra tus�ias

        //skai�iuojame pagal vidurk�
        if (x == 'v') {
                nd_pask = double(nd_suma) / asmuo.nd.size();
         }

        //skai�iuojame nd galutin� pagal median�
        else {
             sort(asmuo.nd.begin(), asmuo.nd.end());

             if (asmuo.nd.size() % 2 != 0) nd_pask = asmuo.nd[asmuo.nd.size() / 2];
             else nd_pask = (asmuo.nd[asmuo.nd.size() / 2] + asmuo.nd[asmuo.nd.size() / 2 - 1]) / 2; 
         }
    }
    


    asmuo.galutinis = 0.4 * nd_pask + 0.6 * asmuo.egz; //paskai�iuojame galutin� bal�

    cout << "�io studento duomenys s�kmingai �ra�yti" << endl << endl;
}



string tikrinti_vard(int v) {

    if (v == 1) {
        cout << "�veskite studento vard�:" << endl;
    }
    else {
        cout << endl << "�veskite studento pavard�: " << endl;
    }

    string vard;
    getline(cin, vard);

    for (char& c : vard) {
        if (!isalpha(c)) { //�i�rime, ar raid�
            if (v == 1) {
                cout << endl << "Neteisinga �vestis. Vardas turi b�ti tik is raid�i�. Bandykite dar kart�." << endl;
                return tikrinti_vard(1);
            }
            else {
                cout << endl << "Neteisinga �vestis. Pavard� turi b�ti tik is raid�i�. Bandykite dar kart�." << endl;
                return tikrinti_vard(2);
            }

        }
    }

    return vard; //rei�kia viskas gerai ir galime naudoti tok� varda/pavard�
}

bool tikrinti_bool() {
    string ivest;
    getline(cin, ivest);
    while (ivest != "0" && ivest != "1") {
        cout << "Neteisinga �vestis. Bandykite dar kart� (�veskite: �0� arba �1�)." << endl;
        getline(cin, ivest);
    }

    bool x = ivest == "1" ? 1 : 0; //priskiriame 1 arba 0

    return x;
}

int tikrinti_pazymi() {

    int a;
    cin >> a;

    while (a < 0 || a > 10 || cin.fail()) {
        cin.clear(); //i�triname error flag`us
        cin.ignore(INT_MAX, '\n'); //praignoruojame, kas liko i� neteisingos �vesties
        cout << "Neteisinga �vestis (turi b�ti nuo 0 iki 10). Bandykite dar kart�." << endl;
        cin >> a;
    }

    cin.clear();
    cin.ignore(INT_MAX, '\n');

    return a;
}




void spausdinti(char x, vector<studentas>& grupe) {
    //LENTELE
    cout << endl;
    cout << setw(10) << left << "VARDAS";
    cout << setw(15) << left << "PAVARD�";

    if (x == 'v')
        cout << setw(25) << left << "GALUTINIS (vid.)" << endl;
    else
        cout << setw(25) << left << "GALUTINIS (med.)" << endl;

    cout << "------------------------------------------------------------";

    for (int i = 0; i < grupe.size(); i++) asmens_spausdinimas(grupe[i]);

}

void  asmens_spausdinimas(studentas& asmuo) {

    //paver�iame � did�i�sias raides
    asmuo.vardas = didziosios(asmuo.vardas);
    asmuo.pavarde = didziosios(asmuo.pavarde);

    cout << endl;
    cout << setw(10) << left << asmuo.vardas;
    cout << setw(15) << left << asmuo.pavarde;
    cout << setw(15) << left << fixed << setprecision(2) << asmuo.galutinis << endl;

}


string didziosios(string a) {

    for (char& c : a) {
        c = toupper(c);
    }

    return a;
}