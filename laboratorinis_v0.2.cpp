#include "mylib.h"

//strukt�ra studento
struct studentas {
    string vardas = "";
    string pavarde = "";
    vector<int> nd;       //nam� darb� pa�ymi� vektorius
    int egz = 0;          //egzamino pa�ymys
    double galutinis_v = 0; //galutinis pa�ymys = 0.4 * vidurkis (nd) + 0.6 * egz
    double galutinis_m = 0; //galutinis pa�ymys = 0.4 * mediana (nd) + 0.6 * egz
};


//funkcijos deklaracijos
void skaitymas(string skait_fail, vector<studentas>& grupe);        //skaitymas is failo
void spausdinimas(vector<studentas>& grupe, string isvest_fail);  //spausdinimas is failo

vector<studentas> studentu_pildymas();      //pildome studentus
void asmens_pildymas(studentas& asmuo);   //u�pildome vieno studento duomenis

int tikrinti_pazymi();                  //tikriname, ar �vestas pa�ymys yra nuo 0 iki 10
string tikrinti_vard(int v);            //tikriname, ar vardas/pavard� sudaryta/-as tik i� raid�i�
bool tikrinti_bool();                   //tikriname, ar �ved� bool reik�m�


void galutinis_balas(studentas& asmuo); //galutinio balo paskaiciavimas
bool rusiuoti_pavard(studentas& x, studentas& y); //rusiavimui



int main()
{
    setlocale(LC_ALL, "Lithuanian"); //�galiname lietuvi�kas raides

    // PROGRAMOS PRAD�IA
    cout << "Paleidote program�, skirt� studento galutiniam balui apskai�iuoti." << endl;
    cout << "Galutinis balas = 0.4 * nam� darb� pa�ymi� vidurkis/mediana + 0.6 * egzamino pa�ymys." << endl << endl;

    //ziurime, ar reikies skaityti studentus is failo, ar vartotojas pats juos ives
    cout << "Ar norite studentus ir j� rezultatus skaityti i� failo?\n";
    cout << "Jeigu norite skaityti is failo - iveskite �1�\n";
    cout << "Jeigu nenorite skaityti is failo - iveskite �0�\n";

    string isvest_fail = "kursiokai.txt";

    bool skaityti;
    skaityti = tikrinti_bool();

    vector<studentas> grupe;

    if (skaityti) { //skaitome is failo
        
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
            skait_fail = "studentai1000000.txt";
        }
        else if (pasirinkimas == 2) {
            skait_fail = "studentai100000.txt";
        }
        else if (pasirinkimas == 3) {
            skait_fail = "studentai10000.txt";
        }

        cout << endl << "*Vyksta skaitymas is failo ir isvedimas*\n" << endl;

        skaitymas(skait_fail, grupe); //skaitymas ir �ra�ymas vyksta per buffer`�. Is karto pildome studentus.
    }
    else {  //vartotojas pats ivedineja
        grupe = studentu_pildymas();
    }

    //spausdinimas
    spausdinimas(grupe, isvest_fail);

    cout << endl << "*Programa baigta vykdyti*" << endl;

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


        //jeigu nebuvo �vesta pa�ymi�
        if (asmuo.nd.empty()) {
            cout << "Neubvo �vesta nei vieno pa�ymio �iam studentui." << endl;
            cout << "Nam� darb� vidurkis ir mediana bus laikoma/-as 0." << endl;
            nd_pask = 0;

        };

        cout << "�veskite egzamino pa�ym�: " << endl;
        asmuo.egz = tikrinti_pazymi();
    }

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


void skaitymas(string skait_fail, vector<studentas>& grupe) {
    stringstream my_buffer;

    auto start = hrclock::now(); //matuosime laika

    ifstream open_f(skait_fail); //jeigu nepavyko atidaryti failo
    if (!open_f.is_open()) {
        cout << "Nepavyko atidaryti failo." << endl;
        return;
    }

    string first_line;
    getline(open_f, first_line); // nuskaitome ir praignoruojame pirma eilute

    my_buffer << open_f.rdbuf(); //viskas buferyje
    open_f.close(); //nebereikia failo, galime uzdaryti

    duration diff = hrclock::now() - start;
    cout << "Failo nuskaitymas � bufer� u�truko: " << diff.count() << " s\n";

    start = hrclock::now();
    string line;
    while (getline(my_buffer, line)) { //imame is buferio po eilute ir pildom 'asmuo'
        studentas asmuo;
        istringstream iss(line);
        iss >> asmuo.vardas >> asmuo.pavarde;

        int pazymys;
        while (iss >> pazymys) {    //kol skaicius int, tol nuskaitys
            asmuo.nd.push_back(pazymys);
        }

        asmuo.egz = asmuo.nd.back();    //kadangi nuskaiteme visus skaicius i pazymiu vektoriu
        asmuo.nd.pop_back();

        galutinis_balas(asmuo);

        grupe.push_back(asmuo);         //pridedam i vektoriu grupe uzpildytus asmens duomenis

        
    }

    diff = hrclock::now() - start;
    cout << "\nBuferio padalijimas � eilu�i� vektori� ir \nvektoriaus <studentas> u�pildymas truko (su galutinio balo paskaiciavimu): " << diff.count() << " s\n";
  
}


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

void spausdinimas(vector<studentas>& grupe, string isvest_fail) {

    auto start = hrclock::now(); // matuosime laika

    sort(grupe.begin(), grupe.end(), rusiuoti_pavard);

    stringstream output;

    size_t maxVardasLength = 6;  // "VARDAS"
    size_t maxPavardeLength = 8; // "PAVARD�"
    for (const auto& asmuo : grupe) {
        maxVardasLength = max(maxVardasLength, asmuo.vardas.length());
        maxPavardeLength = max(maxPavardeLength, asmuo.pavarde.length());
    }

    // Ivedam viska i outputa (i viena stringa)
    output << endl;
    output << setw(maxVardasLength + 2) << left << "VARDAS";
    output << setw(maxPavardeLength + 2) << left << "PAVARD�";
    output << setw(20) << left << "GALUTINIS (vid.)";
    output << setw(20) << left << "GALUTINIS (med.)" << endl;
    output << string(maxVardasLength + 2, '-');
    output << string(maxPavardeLength + 2, '-');
    output << "-----------------------------------------" << endl;

    for (const auto& asmuo : grupe) {
        output << setw(maxVardasLength + 2) << left << asmuo.vardas;
        output << setw(maxPavardeLength + 2) << left << asmuo.pavarde;
        output << setw(20) << left << fixed << setprecision(2) << asmuo.galutinis_v;
        output << setw(20) << left << fixed << setprecision(2) << asmuo.galutinis_m;
        output << endl;
    }


    // isvedame i faila
    ofstream f_out(isvest_fail);
    if (!f_out.is_open()) {
        cout << "Nepavyko atidaryti isvesties failo." << endl;
        return;
    }
    f_out << output.str(); // irasome i faila duomenis
    f_out.close();

    duration diff = hrclock::now() - start;
    cout << endl << "Duomenu isvedimas uztruko + rusiavimas: " << diff.count() << " s\n";

}

bool rusiuoti_pavard(studentas& x, studentas& y){
    return x.pavarde < y.pavarde;
}