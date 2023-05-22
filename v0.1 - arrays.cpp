#include "Mylib.h"


//strukt�ra studento
struct studentas{
    string vardas = "";
    string pavarde = "";
    int paz_sk = 0;       //nam� darb� (nd) pazymiu skai�ius
    int* nd = nullptr;    //nam� darb� pa�ymi� masyvas (rodykl� � j�)
    int egz = 0;          //egzamino pa�ymys
    double galutinis = 0; //galutinis pa�ymys = 0.4 * vidurkis/mediana (nd) + 0.6 * egz
};


//funkcijos deklaracijos
char pradzia();                                   //pradinis tekstas + pasirinkimas, kaip skai�iuoti galutin� bal�

studentas* studentu_pildymas(int& n, char x);     //pildome studentus
void asmens_pildymas(studentas &asmuo, char x);   //u�pildome vieno studento duomenis

int tikrinti_pazymi();                            //tikriname, ar �vestas pa�ymys yra nuo 0 iki 10
string tikrinti_vard(int v);                      //tikriname, ar vardas/pavard� sudaryta/-as tik i� raid�i�
bool tikrinti_bool();                             //tikriname, ar �ved� bool reik�m�

void spausdinti(char x, int n, studentas* grupe); //spausdinimas
void asmens_spausdinimas(studentas &asmuo);       //spausdiname vieno studento rezultatus

string didziosios(string a);                      //Ver�ia vardo ir pavard�s reaides � did�i�sias



int main()
{
    setlocale(LC_ALL, "Lithuanian"); //�galiname lietuvi�kas raides

    // PROGRAMOS PRAD�IA
    char x = pradzia(); // x yra 'v' - vidurkiui arba 'm' - medianai

    // DINAMINIS MASYVAS STUDENT� �VEDIMUI (�VEDAME STUDENT�, KIEK TIK NORIME)
    int n = 0;
    studentas* grupe = studentu_pildymas(n, x);

    // SPAUSDINIMAS
    spausdinti(x,n,grupe);
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



studentas* studentu_pildymas(int& n, char x) {

    bool testi = true;
    studentas* grupe = nullptr;

    while (testi) { //tikrinam, ar vartotojas nori �vesti dar student�

        studentas* laikinas = new studentas[n]; //rodykl� "laikinas" rodo � naujai sukurt� atminties viet�, kuri yra stukt�ros masyvo[n] "studentas" dyd�io
        copy(grupe, grupe + n, laikinas);       //nukopijuojame pirmo studento duomenis � kit� atminties viet�, kuri� pasiekiame per rodykl� "laikinas"
        delete[] grupe;                         //i�trinam rodykl� "grupe", nes t� pat� turime atminties vietoje "laikinas".

        n++;                                    //padidinam masyv�/student� skaici�.
        grupe = new studentas[n];               //sukuriam nauj� atminties viet�, bet jau ji bus didesn�.
        copy(laikinas, laikinas + n - 1, grupe);//nukopijuojame � j� preaitus duomenis
        delete[] laikinas;                      //praeiti duomenys nebereikalingi - i�trinam rodykl� "laikinas"

        asmens_pildymas(grupe[n - 1], x);       //pridedame nauj� duomen� (nauj� student�)


        //ar t�sti toliau �vedin�ti studentus?
        cout << "Jeigu norite t�sti student� �vedim� - �veskite �1�" << endl << "Jeigu nenorite t�sti studento �vedimo - �veskite �0�" << endl << endl;
        testi = tikrinti_bool();

    }

    return grupe;
}



void asmens_pildymas(studentas &asmuo, char x) { //u�pildome vieno studento duomenis

    //vardas, pavard�
    asmuo.vardas = tikrinti_vard(1);
    asmuo.pavarde = tikrinti_vard(2);

    //pa�ymiai
    int nd_suma = 0;
    double nd_pask = 0; //paskai�iuota pagal vidurk� arba median�
    
    //�i�rime, ar vartotojas nori, jog pa�ymiai (ir j� skai�ius), egzamino balas b�t� sugeneruojami atsitiktinai
    bool generuoti;

    cout << endl << "Jeigu norite t�sti, jog pa�ymi� skai�ius, pa�ymiai ir egzamino balas b�t� generuojami atsitiktinai �veskite �1�"<< endl;
    cout << "Jeigu nenorite atsitiktinio generavimo �veskite �0�" << endl;
    generuoti = tikrinti_bool();

    if (generuoti) {
        srand(time(NULL)); //nustatome seed`� atsitiktinio generatoriaus

        asmuo.paz_sk = rand() % 8 + 3; //sugeneruojame atsitiktin� skai�i� pa�ymi� (nuo 3 iki 10)
        asmuo.nd = new int[asmuo.paz_sk]; //sukuriame vietos pa�ymi� masyvui;

        for (int i = 0; i < asmuo.paz_sk; i++) {
            asmuo.nd[i] = rand() % 11; //generuojame nuo 0 iki 10
            nd_suma += asmuo.nd[i];    //sumuojame pa=ymius
        }

        asmuo.egz = rand() % 11; //generuojame nuo 0 iki 10

    }
    else {

        //nam� darb� pa�ymiai
        cout << "�veskite pa�ymius (nuo 0 iki 10):" << endl;
        cout << "Norint baigti pa�ymi� �vedim�, �veskite bet kok� simbol�/-ius (i�skyrus pa�ymius):" << endl;

        int p; //vienas pa�ymys

        while (cin >> p && p >= 0 && p <= 10) {
            //Rei�kia �ved� pa�ym�
            int* temp = new int[asmuo.paz_sk + 1];          //Sukuriam nauj� atminties viet�, kad u�tekt� vietos ir naujam pa�ymiui
            copy(asmuo.nd, asmuo.nd + asmuo.paz_sk, temp);  //nukopijuojam seno masyvo duomenis � nauj� masyv� temp
            delete[] asmuo.nd;  //atlaisvinam sen� masyv� (nebereikalingas)

            asmuo.nd = temp; //nukreipiam rodykl� � nauj� masyv�
            asmuo.nd[asmuo.paz_sk] = p; //�vedame nauj� pa�ym�
            asmuo.paz_sk++; //padidinam �vest� pa�ymi� skai�i�

            nd_suma += p; //pa�ymi� suma

        }

        cin.clear(); //i�triname error flag`us
        cin.ignore(INT_MAX, '\n'); //praignoruojame, kas liko i� neteisingos �vesties


        //jeigu nebuvo �vesta pa�ymi�
        if (asmuo.paz_sk == 0) {
            cout << "Neuvo �vesta nei vieno pa�ymio �iam studentui." << endl;

            if (x == 'v') {
                cout << "Nam� darb� vidurkis bus laikomas 0." << endl;
            }
            else {
                cout << "Nam� darb� mediana bus laikoma 0." << endl;
            }
            
        };


        cout << "�veskite egzamino pa�ym�: " << endl;
        asmuo.egz = tikrinti_pazymi();
    }

    //ska�iuojame galutin� bal�

    //skai�iuojame nd galutin� pagal vidurk�
    if (x == 'v') {
        if (asmuo.paz_sk == 0) nd_pask = 0; //jei n�ra �vesta pa�ymi�
        else nd_pask = double(nd_suma) / asmuo.paz_sk;
        }

    //skai�iuojame nd galutin� pagal median�
    else{
        if (asmuo.paz_sk == 0) nd_pask = 0; //jei n�ra �vesta pa�ymi�
        else {
            sort(asmuo.nd, asmuo.nd + asmuo.paz_sk);

            if (asmuo.paz_sk % 2 != 0) nd_pask = asmuo.nd[asmuo.paz_sk / 2];
            else nd_pask = (asmuo.nd[asmuo.paz_sk / 2] + asmuo.nd[asmuo.paz_sk / 2 - 1]) / 2;
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




void spausdinti(char x, int n, studentas* grupe) {
    //LENTELE
    cout << endl;
    cout << setw(10) << left << "VARDAS";
    cout << setw(15) << left << "PAVARD�";

    if (x == 'v')
        cout << setw(25) << left << "GALUTINIS (vid.)" << endl;
    else
        cout << setw(25) << left << "GALUTINIS (med.)" << endl;

    cout << "------------------------------------------------------------";

    for (int i = 0; i < n; i++) asmens_spausdinimas(*(grupe + i));

    delete[] grupe;
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