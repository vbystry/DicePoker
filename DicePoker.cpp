#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

int kości[5];
int parowa1;
int parowa2;
int trojkowa;
int czworkowa;
int pokerowa;
int mstritowa;
int dstritowa;
int parz;
int k;

//Proste sortowanie bąbelkowe
//przeznaczone dla tablicy o rozmiarze 5
void sort(int tab[], int n)
{
	for(int i=0;i<n;i++)
	{	
        for(int j=1;j<n-i;j++)
		{
            if(tab[j-1]>tab[j])
		    {
                tab[j] = tab[j] + tab[j-1];
                tab[j-1] = tab[j] - tab[j-1]; 
                tab[j] = tab[j] - tab[j-1];
            }
        }    
    }
}

//Funkcje rzutu i przerzutu
//rzut jest przerzutem na wszystkich kościach
void rzut()
{
    cout << "Kości zostały rzucone...\n";
    for(int i=0; i<5; i++)
    {
        kości[i]=(rand()%6)+1;
    }
    cout << "Twoj rzut:\n";
    for(int i=0; i<5; i++)
    {
        cout << kości[i] << " ";
    }
    cout << "\n";
}

void przerzut(int tab[], int n)
{
    cout << "Kości zostały rzucone...\n";
    for(int i=0; i<n; i++)
    {
        kości[tab[i]-1]=(rand()%6)+1;
    }
    cout << "Twoj rzut:\n";
    for(int i=0; i<5; i++)
    {
        cout << kości[i] << " ";
    }
    cout << "\n";
}

//Funkcja obsługująca gracza
void player()
{
    rzut();
    for(int i=0; i<2; i++)
    {
        cout << "Jeśli chcesz wykonać przerzut, naciśnij 1\n";
        int x;
        cin >> x;
        if(!(x==1)) {break;}
        cout << "ile kości chcesz przerzucić?\n";
        x=0;
        cin >> x;
        if(x>5)
        {
            cout << "wprowadzono nieprawidłową liczbę, sprobuj ponownie\n";
            cin >> x;
            if(x>5)
            {
                cout << "ponownie wprowadzono nieprawidłową liczbę, straciłeś swoją szansę\n";
                return;
            }
            if(x==5) {rzut();}
            else if(x!=0)
            {
                int tab[x];
                cout << "ktore kosci chcesz przerzucic?\n";
                for(int i=0; i<x; i++)
                {
                    cin >> tab[i];
                    cout << "\n";
                }
                przerzut(&tab[0], x);
                x=0;
            }
        }
        if(x==5) {rzut();}
        else if(x!=0)
        {
            int tab[x];
            cout << "ktore kosci chcesz przerzucic?\n";
            for(int i=0; i<x; i++)
            {
                cin >> tab[i];
                cout << "\n";
            }
            przerzut(&tab[0], x);
        }    
        else {break;}
    }
}    

//Algorytm rozpoznawania figur w rzucie
void figury(int tab[])
{
    parz=0;
    parowa1=0;
    parowa2=0;
    trojkowa=0;
    czworkowa=0;
    pokerowa=0;
    for(int i=0; i<4; i++)
    {
        if(tab[i]%2==0) {parz++;}
        if(tab[i]==tab[i+1])
        {
            if(i==3 && !(czworkowa==0)) {pokerowa= czworkowa;}
            else if(i>1 && trojkowa==i) {czworkowa=trojkowa;}
            else if(i>0 && ((parowa1==(i)) || (parowa2==(i)))) {trojkowa=i+1;}
            else if(!(parowa1==0 || tab[i]==tab[parowa1])) {parowa2=i+1;}
            else {parowa1=i+1;}
        }
        else if((tab[i]==i+1) && mstritowa==i) {mstritowa++;}
        else if((tab[i]==i+2) && dstritowa==i) {dstritowa++;}
    }
    if(tab[4]%2==0) {parz++;}
    if((tab[4]==5) && mstritowa==4) {mstritowa++;}
    else if((tab[4]==6) && dstritowa==4) {dstritowa++;}
}

//Funkcja licząca punkty jakie gracz uzyskał w turze
void liczydło()
{
    k=0;
    int kosci2[5];
    for(int i=0; i<5; i++)
    {
        kosci2[i]=kości[i];
    }
    sort(&kosci2[0], 5);
    figury(&kosci2[0]);
    if(pokerowa) {k=5*(kosci2[0])+50;}
    else if(mstritowa==5) {k= 15;}
    else if(dstritowa==5) {k=20;}
    else if(!(czworkowa==0)) {k=kosci2[czworkowa-1]*4+20;}
    else if(!(trojkowa==0))
    {
        if(!((kosci2[trojkowa-1]==kosci2[parowa2-1] || parowa2==0) && (kosci2[trojkowa-1]==kosci2[parowa1-1] || parowa1==0)))
        {
            for(int i=0; i<5; i++)
            {
                k=k+kosci2[i];
            }
            k=k+10;
        }
        else
        {
            k=kosci2[trojkowa-1]*3;
        }
    }
    else if(!(parowa1*parowa2==0)) {k=2*(kosci2[parowa1-1]+kosci2[parowa2-1]);}
    else if(!(parowa1==0)) {k=2*(kosci2[parowa1-1]);}
    if((parz==5) || (!parz)) {k=k+10;}
}

//Funckja obsługująca rundę
void round(int pl_n, int tab[])
{
    for(int i=0; i<pl_n; i++)
    {
        cout << "witaj graczu " << i+1 << "\n";
        player();
        liczydło();
        tab[i]=tab[i]+k;
    }
}

int main()
{
    srand(time( NULL ));
    cout << "podaj liczbe graczy\n";
    int num;
    cin >> num;
    int wyniki[num];
    for(int i=0; i<num; i++)
    {
        wyniki[num]=0;
    }
    int rundowa=1;
    while(rundowa)
    {
        round(num, &wyniki[0]);
        cout << "wyniki po tej rundzie:\n";
        for(int i=0; i<num; i++)
        {
            cout << "gracz " << i+1 << ":\n" << wyniki[i] << "\n";
        }
        cout << "czy jest chęć na rozegranie kolejnej rundy? wprowadź 0 jesli nie\n";
        cin >> rundowa;
    }
}
