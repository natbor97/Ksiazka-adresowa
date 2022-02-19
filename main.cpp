#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <conio.h>
#include <vector>
#include <windows.h>
using namespace std;

struct Adresat {
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
    int id=0, idUzytkownika=0;
};

struct Uzytkownik {
    int id=0;
    string nazwa="", haslo="";
};

vector<Adresat>pobierzDaneAdresatow(int iloscAdresatow, Adresat kontakty, int idUzytkownika ) {
    string wiersz="";
    char znak='|';
    vector<Adresat>adresaci;

    fstream plik;
    plik.open("Ksiazka adresowa.txt",ios::in);

    if(plik.good()==true) {
        while(!plik.eof()) {
            for(int i=0; i<iloscAdresatow; i++) {
                getline(plik, wiersz);

                size_t position1=wiersz.find(znak);
                kontakty.id=atoi((wiersz.substr(0,position1)).c_str());

                size_t position2=wiersz.find(znak,position1+1);
                kontakty.idUzytkownika=atoi((wiersz.substr(position1+1,(position2-position1-1))).c_str());

                size_t position3=wiersz.find(znak,position2+1);
                kontakty.imie=wiersz.substr(position2+1,(position3-position2-1));

                size_t position4=wiersz.find(znak,position3+1);
                kontakty.nazwisko = wiersz.substr(position3+1,(position4-position3-1));

                size_t position5=wiersz.find(znak,position4+1);
                kontakty.numerTelefonu=wiersz.substr(position4+1,(position5-position4-1));

                size_t position6=wiersz.find(znak,position5+1);
                kontakty.email=wiersz.substr(position5+1,(position6-position5-1));

                size_t position7=wiersz.find(znak,position6+1);
                kontakty.adres=wiersz.substr(position6+1,(position7-position6-1));

                if(kontakty.idUzytkownika==idUzytkownika){
                adresaci.push_back(kontakty);
                }
            }
        }
    }
    plik.close();
    return adresaci;
}

vector<Uzytkownik>pobierzDaneUzytkownikow(int iloscUzytkownikow, Uzytkownik uzytkownik) {
    string wiersz;
    fstream plik;
    vector<Uzytkownik>uzytkownicy;
    char znak='|';

    plik.open("Uzytkownicy.txt",ios::in);

    if(plik.good()==true) {
        while(!plik.eof()) {
            for(int i=0; i<iloscUzytkownikow; i++) {
                getline(plik, wiersz);

                size_t position1=wiersz.find(znak);
                uzytkownik.id=atoi((wiersz.substr(0,position1)).c_str());

                size_t position2=wiersz.find(znak,position1+1);
                uzytkownik.nazwa=wiersz.substr(position1+1,(position2-position1-1));

                size_t position3=wiersz.find(znak,position2+1);
                uzytkownik.haslo=wiersz.substr(position2+1,(position3-position2-1));

                uzytkownicy.push_back(uzytkownik);
            }
        }
    }
    plik.close();
    return uzytkownicy;
}

int sprawdzIloscAdresatow(int iloscAdresatow) {
    fstream plik;
    plik.open("Ksiazka adresowa.txt",ios::in);

    string wiersz;
    int iloscWierszy=0;

    if(plik.good()==true) {
        while(!plik.eof()) {
            getline(plik,wiersz);
            iloscWierszy++;
        }
        iloscAdresatow=iloscWierszy-1;
        plik.close();
    } else iloscAdresatow=0;

    return iloscAdresatow;
}

int sprawdzIloscUzytkownikow(int iloscUzytkownikow) {
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    string wiersz;
    int iloscWierszy=0;

    if(plik.good()==true) {
        while(!plik.eof()) {
            getline(plik,wiersz);
            iloscWierszy++;
        }
        iloscUzytkownikow=iloscWierszy-1;
        plik.close();
    } else iloscUzytkownikow=0;

    return iloscUzytkownikow;
}

int sprawdzOstatnieId (int iloscAdresatow) {
    string wiersz;
    int ostatnieId=0;
    char znak='|';

    fstream plik;
    plik.open("Ksiazka adresowa.txt", ios::in);

    for (int i=0; i<iloscAdresatow; i++) {
        getline(plik,wiersz);
        size_t position1=wiersz.find(znak);
        ostatnieId=atoi((wiersz.substr(0,position1)).c_str());
    }
    plik.close();

    return ostatnieId;
}

int wprowadzenieDanychAdresatow(int iloscAdresatow, vector<Adresat>adresaci, int idUzytkownika) {
    Adresat dodajAdresata;
    int ostatnieId=sprawdzOstatnieId(iloscAdresatow);

    dodajAdresata.id=ostatnieId+1;
    cout<<"Imie: ";
    cin>>dodajAdresata.imie;
    cout<<"Nazwisko: ";
    cin>>dodajAdresata.nazwisko;
    cout<<"Nr telefonu: ";
    cin.sync();
    getline(cin,dodajAdresata.numerTelefonu);
    cout<<"Email: ";
    cin>>dodajAdresata.email;
    cout<<"Adres: ";
    cin.sync();
    getline(cin,dodajAdresata.adres);

    adresaci.push_back(dodajAdresata);

    fstream plik;
    plik.open ("Ksiazka adresowa.txt", ios::out| ios::app);
    plik<<dodajAdresata.id<<"|"<<idUzytkownika<<"|"<<dodajAdresata.imie<<"|"<<dodajAdresata.nazwisko<<"|";
    plik<<dodajAdresata.numerTelefonu<<"|"<<dodajAdresata.email<<"|"<<dodajAdresata.adres<<"|"<<endl;
    plik.close();
    iloscAdresatow++;

    cout<<"Dodano nowego adresata."<<endl;
    Sleep(1000);

    return iloscAdresatow;
}

void wyszukajAdresataPoImieniu(vector<Adresat>adresaci) {
    string szukaneImie;
    int komunikat_o_braku_imienia=0;
    cout<<"Jakiego imienia szukasz: ";
    cin>>szukaneImie;

    for(int i=0; i<adresaci.size(); i++) {
        if (adresaci[i].imie==szukaneImie) {
            cout<<endl<<adresaci[i].id<<" "<<adresaci[i].imie<<" "
                <<adresaci[i].nazwisko<<" "<<adresaci[i].numerTelefonu<<" "
                <<adresaci[i].email<<" "<<adresaci[i].adres<<endl;
            komunikat_o_braku_imienia++;
        }
    }
    if(komunikat_o_braku_imienia==0) cout<<"Nie ma takiego imienia w Twojej ksiazce"<<endl;
    else cout<<endl<<"Wyswietlono wszystkie kontakty o takim imieniu"<<endl;
    cout<<"Wcisnij 'M', aby wrocic do MENU."<<endl;
    getchar();
    getchar();
}

void wyszukajAdresataPoNazwisku(vector<Adresat>adresaci) {
    string szukaneNazwisko;
    int komunikat_o_braku_nazwiska=0;
    cout<<"Jakiego nazwiska szukasz: ";
    cin>>szukaneNazwisko;

    for(int i=0; i<adresaci.size(); i++) {
        if (adresaci[i].nazwisko==szukaneNazwisko) {
            cout<<endl<<adresaci[i].id<<" "<<adresaci[i].imie<<" "
                <<adresaci[i].nazwisko<<" "<<adresaci[i].numerTelefonu<<" "
                <<adresaci[i].email<<" "<<adresaci[i].adres<<endl;
            komunikat_o_braku_nazwiska++;
        }
    }
    if(komunikat_o_braku_nazwiska==0) cout<<"Nie ma takiego imienia w Twojej ksiazce"<<endl;
    else cout<<endl<<"Wyswietlono wszystkie kontakty o takim nazwisku."<<endl;
    cout<<"Wcisnij 'M', aby wrocic do MENU."<<endl;
    getchar();
    getchar();
}

void wyswietlWszystkichAdresatow(int iloscAdresatow, vector<Adresat>adresaci) {
    cout<<endl<<"Dane adresatow: "<<endl;
    for(int i=0; i<adresaci.size(); i++) {
        cout<<"ID: "<<adresaci[i].id<<endl;
        cout<<"Imie i nazwisko: "<<adresaci[i].imie<<" "<<adresaci[i].nazwisko<<endl;
        cout<<"Numer tel.: "<<adresaci[i].numerTelefonu<<endl;
        cout<<"E-mail: "<<adresaci[i].email<<endl;
        cout<<"Adres: "<<adresaci[i].adres<<endl;
        cout<<endl;
    }
    cout<<"Wcisnij 'M', aby wrocic do MENU."<<endl;
    getchar();
    getchar();
}

void usunAdresata(int iloscAdresatow, vector<Adresat>adresaci, int idUzytkownika) {
    int idAdresataDoUsuniecia;
    char wyborOpcji;
    cout<<"ID adresata ktorego chcesz usunac: ";
    cin>>idAdresataDoUsuniecia;
    int komunikat_o_istnieniu_ID=0;

    for(int i=0; i<adresaci.size(); i++) {
        if (adresaci[i].id==idAdresataDoUsuniecia && adresaci[i].idUzytkownika==idUzytkownika)
            komunikat_o_istnieniu_ID++;
    }

    if(komunikat_o_istnieniu_ID==0) {
        cout<<"Taki kontakt nie istnieje w twojej ksiazce adresowej."<<endl;
    }

    else {
        cout<<"Czy na pewno chcesz usunac adresata o ID: "<<idAdresataDoUsuniecia<<"? [T/N]";
        cin>>wyborOpcji;

        if(wyborOpcji=='T') {

            fstream plik, nowyPlik;
            string wiersz;

            plik.open("Ksiazka adresowa.txt", ios::in);
            nowyPlik.open("Nowa ksiazka adresowa.txt",ios::out);

            for (int i=0; i<iloscAdresatow; i++) {
                getline(plik,wiersz);

                char znak='|';
                size_t position1=wiersz.find(znak);
                int sprawdzenieId=atoi((wiersz.substr(0,position1)).c_str());

                if (sprawdzenieId!=idAdresataDoUsuniecia) {
                    nowyPlik<<wiersz<<endl;
                }
            }
            plik.close();
            nowyPlik.close();

            remove("Ksiazka adresowa.txt");
            rename("Nowa ksiazka adresowa.txt", "Ksiazka adresowa.txt");

            cout<<"Adresat zostal usuniety. "<<endl;
        }
    }
    cout<<"Wcisnij 'M' aby wrocic do MENU.";
    getchar();
    getchar();
}

void edycjaKontaktu (int iloscAdresatow, vector<Adresat> adresaci, int idUzytkownika) {
    int idAdresataDoEdycji;
    char wyborOpcji;
    string zmianaDanych;
    int komunikat_o_istnieniu_ID=0;

    cout<<"ID adresata ktorego dane chcesz edytowac: ";
    cin>>idAdresataDoEdycji;

    for(int i=0; i<adresaci.size(); i++) {
        if(adresaci[i].id==idAdresataDoEdycji && adresaci[i].idUzytkownika==idUzytkownika) {
            komunikat_o_istnieniu_ID++;
        }
    }

    if(komunikat_o_istnieniu_ID==0) cout<<"Taki kontakt nie istnieje w twojej ksiazce adresowej."<<endl;

    else  {
        cout<< "Ktore dane chcesz edytowac? "<<endl;
        cout<< "1. Imie"<<endl;
        cout<< "2. Nazwisko"<<endl;
        cout<< "3. Numer telefonu"<<endl;
        cout<< "4. Email"<<endl;
        cout<< "5. Adres"<<endl;
        cout<< "6. Powrot do menu"<<endl;
        cout<<"Twoj wybor: ";
        cin>>wyborOpcji;
        cout<<endl;

        if(wyborOpcji=='1') {
            for(int i=0; i<adresaci.size(); i++) {
                if(adresaci[i].id==idAdresataDoEdycji) {
                    cout<<"Wprowadz nowe imie: " ;
                    cin>>zmianaDanych;
                    adresaci[i].imie=zmianaDanych;
                    cout<<endl<<"Imie zostalo zmienione."<<endl;
                }
            }
        }

        else if(wyborOpcji=='2') {
            for(int i=0; i<adresaci.size(); i++) {
                if(adresaci[i].id==idAdresataDoEdycji) {
                    cout<< "Wprowadz nowe nazwisko: " ;
                    cin>>zmianaDanych;
                    adresaci[i].nazwisko=zmianaDanych;
                    cout<<endl<<"Nazwisko zostalo zmienione."<<endl;
                }
            }
        }

        else if(wyborOpcji=='3') {
            for(int i=0; i<adresaci.size(); i++) {
                if(adresaci[i].id==idAdresataDoEdycji) {
                    cout<<"Wprowadz nowy numer: " ;
                    cin.sync();
                    getline(cin,zmianaDanych);
                    adresaci[i].numerTelefonu=zmianaDanych;
                    cout<<endl<<"Numer telefonu zostal zmieniony."<< endl;
                }
            }
        }

        else if (wyborOpcji=='4') {
            for(int i=0; i<adresaci.size(); i++) {
                if(adresaci[i].id==idAdresataDoEdycji) {
                    cout<<"Wprowadz nowy email: " ;
                    cin>>zmianaDanych;
                    adresaci[i].email=zmianaDanych;
                    cout<<endl<<"Email zostal zmieniony."<< endl;
                }
            }
        }

        else if (wyborOpcji=='5') {
            for(int i=0; i<adresaci.size(); i++) {
                if(adresaci[i].id==idAdresataDoEdycji) {
                    cout<<"Wprowadz nowy adres: " ;
                    cin.sync();
                    getline(cin,zmianaDanych);
                    adresaci[i].adres=zmianaDanych;
                    cout<<endl<<"Adres zostal zmieniony."<< endl;
                }
            }
        }

        else if (wyborOpcji=='6') cout<<endl;

        fstream plik, nowyPlik;
        string wiersz;

        plik.open("Ksiazka adresowa.txt",ios::in);
        nowyPlik.open("Nowa ksiazka adresowa.txt",ios::out);

        for(int i=0; i<iloscAdresatow; i++) {
            getline(plik,wiersz);

            char znak='|';
            size_t position1=wiersz.find(znak);
            int sprawdzenieId=atoi((wiersz.substr(0,position1)).c_str());

            if (sprawdzenieId==idAdresataDoEdycji) {
                for(int zamiana=0; zamiana<adresaci.size(); zamiana++) {
                    if(adresaci[zamiana].id==idAdresataDoEdycji) {
                        nowyPlik<<adresaci[zamiana].id<<'|'<<adresaci[zamiana].idUzytkownika<<'|'<<adresaci[zamiana].imie<<'|';
                        nowyPlik<<adresaci[zamiana].nazwisko<<'|';
                        nowyPlik<<adresaci[zamiana].numerTelefonu<<'|'<<adresaci[zamiana].email<<'|';
                        nowyPlik<<adresaci[zamiana].adres<<'|'<<endl;
                    }
                }
            } else {
                nowyPlik<<wiersz<<endl;
            }
        }

        plik.close();
        nowyPlik.close();

        remove("Ksiazka adresowa.txt");
        rename("Nowa ksiazka adresowa.txt","Ksiazka adresowa.txt");
    }
}

void rejestracjaUzytkownika(int iloscUzytkownikow, vector<Uzytkownik>uzytkownicy) {
    int id;
    string nazwa, haslo;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwa;

    for(int i=0; i<iloscUzytkownikow; i++) {
        if(uzytkownicy[i].nazwa==nazwa) {
            cout<<"Podana nazwa uzytkownika jest zajeta. Podaj inna nazwe: ";
            cin>>nazwa;
            i--;
        }
    }
    cout<<"Podaj haslo: ";
    cin>>haslo;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);
    if(plik.good()==false) id=1;
    else id=uzytkownicy[iloscUzytkownikow-1].id+1;
    plik.close();

    plik.open("Uzytkownicy.txt", ios::out|ios::app);
    plik<<id<<'|'<<nazwa<<'|'<<haslo<<'|'<<endl;
    plik.close();

    cout<<"Rejestracja przebiegla pomyslnie."<<endl;
    Sleep(1000);
}

int logowanieUzytkownika(int iloscUzytkownikow, vector<Uzytkownik>uzytkownicy) {
    string nazwa, haslo;
    cout<<"Login: ";
    cin>>nazwa;
    int i=0;

    while(i<iloscUzytkownikow) {
            if(uzytkownicy[i].nazwa==nazwa) {
                cout<<"Haslo: ";
                cin>>haslo;
                if(uzytkownicy[i].haslo==haslo) {
                    cout<<"Zalogowano."<<endl;
                    return uzytkownicy[i].id;
                }
                cout<<"Niepoprawne haslo"<<endl;
                return 0;
            } i++;
        }
    cout<<"Nie ma takiego uzytkownika"<<endl;
    Sleep(1000);
    return 0;
}

void zmienHaslo(int iloscUzytkownikow, vector<Uzytkownik>uzytkownicy, int idUzytkownika) {
    fstream plik;
    string haslo;
    cout<<"Podaj nowe haslo: ";
    cin>>haslo;

    for (int i=0; i<iloscUzytkownikow; i++) {
        if (uzytkownicy[i].id==idUzytkownika) {
            uzytkownicy[i].haslo=haslo;
            cout<<"Haslo zostalo zmienione"<<endl;
            Sleep (1000);
        }
    }
    plik.open("Uzytkownicy.txt", ios::out);
    for(int i=0; i<iloscUzytkownikow; i++) {
        plik<<uzytkownicy[i].id <<'|'<< uzytkownicy[i].nazwa<<'|'<<uzytkownicy[i].haslo<<'|'<<endl;
    }
    plik.close();
}

int main() {
    Adresat kontakty;
    Uzytkownik uzytkownik;
    int iloscAdresatow=0;
    int iloscUzytkownikow=0;
    int idAdresata=0;
    int idUzytkownika=0;
    vector<Adresat>adresaci;
    vector<Uzytkownik>uzytkownicy;
    fstream plik;
    char wyborOpcjiPierwszej;
    char wyborOpcjiDrugiej;

    iloscUzytkownikow=sprawdzIloscUzytkownikow(iloscUzytkownikow);
    uzytkownicy=pobierzDaneUzytkownikow(iloscUzytkownikow, uzytkownik);

    while(1) {
        if(idUzytkownika==0) {
            system("cls");
            cout<<"1. Logowanie"<<endl;
            cout<<"2. Rejestracja"<<endl;
            cout<<"3. Zamknij program"<<endl;
            cout<<"Twoj wybor:";
            cin>>wyborOpcjiPierwszej;

            if(wyborOpcjiPierwszej=='1') {
                idUzytkownika=logowanieUzytkownika(iloscUzytkownikow,uzytkownicy);
            }

            else if(wyborOpcjiPierwszej=='2') {
                rejestracjaUzytkownika(iloscUzytkownikow,uzytkownicy);
                iloscUzytkownikow=sprawdzIloscUzytkownikow(iloscUzytkownikow);
                uzytkownicy=pobierzDaneUzytkownikow(iloscUzytkownikow,uzytkownik);
            }

            else if(wyborOpcjiPierwszej=='3') {
                exit(0);
            }

        } else {
            system("cls");
            cout<<"KSIAZKA ADRESOWA"<<endl;
            cout<<"1. Dodaj adresata"<<endl;
            cout<<"2. Wyszukaj po imieniu"<<endl;
            cout<<"3. Wyszukaj po nazwisku"<<endl;
            cout<<"4. Wyswietl wszystkich adresatow"<<endl;
            cout<<"5. Usun adresata"<<endl;
            cout<<"6. Edytuj adresata"<<endl;
            cout<<"7. Zmien haslo"<<endl;
            cout<<"8. Wyloguj sie"<<endl;
            cout<<"9. Zakoncz program"<<endl;
            cout<<"Twoj wybor:";
            cin>>wyborOpcjiDrugiej;

            iloscAdresatow=sprawdzIloscAdresatow(iloscAdresatow);
            adresaci=pobierzDaneAdresatow(iloscAdresatow,kontakty,idUzytkownika);

            if (wyborOpcjiDrugiej=='1') {
                wprowadzenieDanychAdresatow(iloscAdresatow,adresaci,idUzytkownika);
            }

            else if (wyborOpcjiDrugiej=='2') {
                if (iloscAdresatow>0) wyszukajAdresataPoImieniu(adresaci);
                else cout<<endl<<"Nie masz jeszcze adresatow w ksiazce adresowej."<<endl;
            }

            else if (wyborOpcjiDrugiej=='3') {

                if (iloscAdresatow>0) wyszukajAdresataPoNazwisku(adresaci);
                else cout<<endl<<"Nie masz jeszcze adresatow w ksiazce adresowej."<<endl;

            }

            else if (wyborOpcjiDrugiej=='4') {
                if(iloscAdresatow>0) wyswietlWszystkichAdresatow(iloscAdresatow, adresaci);
                else cout<<"Nie masz jeszcze adresatow w ksiazce adresowej"<<endl;
            }

            else if (wyborOpcjiDrugiej=='5') {
                if(iloscAdresatow>0) {
                    usunAdresata(iloscAdresatow, adresaci, idUzytkownika);
                    iloscAdresatow = sprawdzIloscAdresatow(iloscAdresatow);
                } else cout<<"Nie masz jeszcze adresatow w ksiazce adresowej"<<endl;
            }

            else if (wyborOpcjiDrugiej=='6') {
                if(iloscAdresatow>0) {
                    edycjaKontaktu(iloscAdresatow, adresaci, idUzytkownika);
                    Sleep(1000);
                } else cout<<"Nie masz jeszcze adresatow w ksiazce adresowej"<<endl;
            }

            else if (wyborOpcjiDrugiej=='7') {
                zmienHaslo(iloscUzytkownikow, uzytkownicy, idUzytkownika);
                uzytkownicy=pobierzDaneUzytkownikow(iloscUzytkownikow,uzytkownik);
            }

            else if(wyborOpcjiDrugiej=='8') {
                idUzytkownika=0;
            }

            else if (wyborOpcjiDrugiej=='9') {
                exit(0);
            }
        }
    }
    return 0;
}
