#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

string betu[14]; // Tömbelem, amely a magánhangzókat fogja tárolni

class haiku {
private:
    string haik[3]; // Tömbelem, amely a haiku sorait tárolja
    int hiba[3]; // Tömbelem, amely a szótaghibákat tárolja
public:
    int alkalom; // A versek számának nyilvántartása

    void vers() {
        cout << "Adja meg a haikut: " << endl;
        for (int i = 0; i < 3; i++) {
            getline(cin, haik[i]); // Beolvas három sort a felhasználótól
        }
        szotag(); // Meghívja a szótagellenõrzõ függvényt
    }

    void szotag() {
        for (int i = 0; i < 3; i++) {
            hiba[i] = 0; // Inicializálja a hibaszámot nullára
            for (int j = 0; j < haik[i].size(); j++) {
                for (int k = 0; k < 14; k++) {
                    if (haik[i].substr(j) == betu[k]) {
                        hiba[i]++; // Szótaghibák számlálása
                    }
                }
            }
        }
        hibas(); // Meghívja a hibakezelõ függvényt
    }

    void hibas() {
        system("pause"); // Szünetelés a folytatás elõtt
        system("cls"); // Képernyõ törlése

        if ((hiba[0] == 5) && (hiba[2] == 5) && (hiba[1]) == 7) {
            cout << "A szótagok száma megfelelõ: " << endl;
            cout.setf(ios::left);
            for (int i = 0; i < 3; i++) {
                cout << haik[i] << "\t" << hiba[i] << endl; // Kiírja a haikut és a szótaghibák számát
            }
            counter(); // Meghívja a számláló függvényt
        }
        else {
            cout << "A szótagok száma nem megfelelõ: " << endl;
            cout.setf(ios::left);
            for (int i = 0; i < 3; i++) {
                cout << haik[i] << "\t" << hiba[i] << endl; // Kiírja a haikut és a szótaghibák számát
            }
            cout << "\nPróbálja újra!";
            system("pause"); // Szünetelés a folytatás elõtt
            system("cls"); // Képernyõ törlése
            vers(); // Újra meghívja a vers beviteli függvényt
        }
    }

    void counter() {
        alkalom++; // Növeli a versek számát
        ofstream ki("alkalom.txt");
        if (ki.is_open()) {
            ki << alkalom; // Elmenti a versek számát egy fájlba
            ki.close();
        }
        else {
            cerr << "Nem lehet írni a fájlt!"; // Hibakezelés
        }
    }

    void mentés() {
        cout << "Adja meg hogy szeretné elnevezni a versét: ";
        string cim;
        cin >> cim; // Beolvassa a felhasználótól a fájlnevet
        string file = to_string(alkalom) + ".haiku.txt"; // Fájlnév generálása
        ofstream ki(file);
        if (ki.is_open()) {
            for (int i = 0; i < 3; i++) {
                ki << haik[i] << endl; // Elmenti a haikut a fájlba
            }
            ki.close();
        }
    }
};

int main() {
    setlocale(LC_ALL, "hu_HU.utf8"); // Magyar nyelvi környezet beállítása
    ifstream be("magánhangzók.txt");
    if (be.fail()) { cerr << "Hiba a fájl megnyitása során!"; return 1; } // Hibakezelés a fájl megnyitásához
    for (int i = 0; i < 14; i++) {
        getline(be, betu[i]); // Beolvassa a magánhangzókat a fájlból
    }
    be.close();

    haiku h;
    ifstream be2("alkalom.txt");
    if (be2.fail()) { cerr << "Ez az elsõ vers!\n"; } // Hibakezelés, ha nincs elõzõ fájl
    be2 >> h.alkalom; // Beolvassa a versek számát a fájlból
    be2.close();
    h.vers(); // Meghívja a vers beviteli függvényt
}