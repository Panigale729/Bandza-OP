#include "mylib.h"
#include "stdnt.h"
#include "ivest_tikrinimai.h"
#include "darb_su_fail.h"


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

        try {
            skaitymas(skait_fail, grupe); //skaitymas ir �ra�ymas vyksta per buffer`�. Is karto pildome studentus.
        }
        catch (const exception& e) {
            cout << "Klaida vykdant program�: " << e.what() << endl;
            return 1;
        }

    }
    else {  //vartotojas pats ivedineja
        try {
            grupe = studentu_pildymas();
        }
        catch (const exception& e) {
            cout << "Klaida vykdant program�: " << e.what() << endl;
            return 1;
        }
    }

    //spausdinimas
    spausdinimas(grupe, isvest_fail);

    cout << endl << "*Programa baigta vykdyti*" << endl;

}