#include <iostream>
#include <ctime>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

string betu[14]; // T�mbelem, amely a mag�nhangz�kat fogja t�rolni

class haiku {
private:
    string haik[3]; // T�mbelem, amely a haiku sorait t�rolja
    int hiba[3]; // T�mbelem, amely a sz�taghib�kat t�rolja
public:
    int alkalom; // A versek sz�m�nak nyilv�ntart�sa

    void vers() {
        cout << "Adja meg a haikut: " << endl;
        for (int i = 0; i < 3; i++) {
            getline(cin, haik[i]); // Beolvas h�rom sort a felhaszn�l�t�l
        }
        szotag(); // Megh�vja a sz�tagellen�rz� f�ggv�nyt
    }

    void szotag() {
        for (int i = 0; i < 3; i++) {
            hiba[i] = 0; // Inicializ�lja a hibasz�mot null�ra
            for (int j = 0; j < haik[i].size(); j++) {
                for (int k = 0; k < 14; k++) {
                    if (haik[i].substr(j) == betu[k]) {
                        hiba[i]++; // Sz�taghib�k sz�ml�l�sa
                    }
                }
            }
        }
        hibas(); // Megh�vja a hibakezel� f�ggv�nyt
    }

    void hibas() {
        system("pause"); // Sz�netel�s a folytat�s el�tt
        system("cls"); // K�perny� t�rl�se

        if ((hiba[0] == 5) && (hiba[2] == 5) && (hiba[1]) == 7) {
            cout << "A sz�tagok sz�ma megfelel�: " << endl;
            cout.setf(ios::left);
            for (int i = 0; i < 3; i++) {
                cout << haik[i] << "\t" << hiba[i] << endl; // Ki�rja a haikut �s a sz�taghib�k sz�m�t
            }
            counter(); // Megh�vja a sz�ml�l� f�ggv�nyt
        }
        else {
            cout << "A sz�tagok sz�ma nem megfelel�: " << endl;
            cout.setf(ios::left);
            for (int i = 0; i < 3; i++) {
                cout << haik[i] << "\t" << hiba[i] << endl; // Ki�rja a haikut �s a sz�taghib�k sz�m�t
            }
            cout << "\nPr�b�lja �jra!";
            system("pause"); // Sz�netel�s a folytat�s el�tt
            system("cls"); // K�perny� t�rl�se
            vers(); // �jra megh�vja a vers beviteli f�ggv�nyt
        }
    }

    void counter() {
        alkalom++; // N�veli a versek sz�m�t
        ofstream ki("alkalom.txt");
        if (ki.is_open()) {
            ki << alkalom; // Elmenti a versek sz�m�t egy f�jlba
            ki.close();
        }
        else {
            cerr << "Nem lehet �rni a f�jlt!"; // Hibakezel�s
        }
    }

    void ment�s() {
        cout << "Adja meg hogy szeretn� elnevezni a vers�t: ";
        string cim;
        cin >> cim; // Beolvassa a felhaszn�l�t�l a f�jlnevet
        string file = to_string(alkalom) + ".haiku.txt"; // F�jln�v gener�l�sa
        ofstream ki(file);
        if (ki.is_open()) {
            for (int i = 0; i < 3; i++) {
                ki << haik[i] << endl; // Elmenti a haikut a f�jlba
            }
            ki.close();
        }
    }
};

int main() {
    setlocale(LC_ALL, "hu_HU.utf8"); // Magyar nyelvi k�rnyezet be�ll�t�sa
    ifstream be("mag�nhangz�k.txt");
    if (be.fail()) { cerr << "Hiba a f�jl megnyit�sa sor�n!"; return 1; } // Hibakezel�s a f�jl megnyit�s�hoz
    for (int i = 0; i < 14; i++) {
        getline(be, betu[i]); // Beolvassa a mag�nhangz�kat a f�jlb�l
    }
    be.close();

    haiku h;
    ifstream be2("alkalom.txt");
    if (be2.fail()) { cerr << "Ez az els� vers!\n"; } // Hibakezel�s, ha nincs el�z� f�jl
    be2 >> h.alkalom; // Beolvassa a versek sz�m�t a f�jlb�l
    be2.close();
    h.vers(); // Megh�vja a vers beviteli f�ggv�nyt
}