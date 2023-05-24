#include "ivest_tikrinimai.h"


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