#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Duomenys{
        string pavadinimas;
        int technika[10]{0};
        int artisiskumas[10]{0};
        int galutinis = 0;
};

void Nuskaitymas(int &n, int &k, Duomenys A[]);
void MinMax(int i, int k, Duomenys A[], int &didt, int &mazt, int &dida, int &maza);
void Rikiavimas(int n, Duomenys A[]);

int main()
{
    Duomenys A[100];
    int n,k, didt = 0, mazt = 0, dida = 0, maza = 0;
    Nuskaitymas(n,k,A);
    for(int i = 0; i < n; i++){
        MinMax(i,k,A,didt,mazt,dida,maza); // randa didziausia ir maziausia bala is artistiskumo ir tech.
        for(int j = 0; j < k; j++){
        A[i].galutinis += A[i].technika[j] + A[i].artisiskumas[j]; // visi balai 1 poros
        }

        A[i].galutinis = A[i].galutinis - didt - mazt - dida - maza; // atimami MinMax() rasti balai is visu ir gaunam galutinius
    }
        Rikiavimas(n,A);

for(int s = 0; s < n; s++){

    cout << setw(20) << left << A[s].pavadinimas << A[s].galutinis << endl;
}

}

void Nuskaitymas(int &n, int &k, Duomenys A[])
{
    ifstream GET("U2.txt");
    GET >> n >> k;
    GET.ignore(80, '\n');
    char eil[21];
    for(int i = 0; i < n; i++){
        GET.get(eil, 21);
        A[i].pavadinimas = eil;
        GET.ignore(80, '\n');
        for(int j = 0; j < k; j++){
            GET >> A[i].technika[j];
        }
        GET.ignore(80, '\n');
        for(int l = 0; l < k; l++){
            GET >> A[i].artisiskumas[l];
        }
        GET.ignore(80, '\n');
    }
    GET.close();
}

void MinMax(int i, int k, Duomenys A[], int &didt, int &mazt, int &dida, int &maza)
{
    didt = A[i].technika[0];
    dida = A[i].artisiskumas[0];
    mazt = A[i].technika[0];
    maza = A[i].artisiskumas[0];

    for(int z = 1; z < k; z++)
    {
        if(A[i].technika[z] > didt){    // i poros numeris
            didt = A[i].technika[z];
        }
        if(A[i].artisiskumas[z] > dida){
            dida = A[i].artisiskumas[z];
        }
        if(A[i].technika[z] < mazt){
            mazt = A[i].technika[z];
        }
        if(A[i].artisiskumas[z] < maza){
            maza = A[i].artisiskumas[z];
        }
    }
}

void Rikiavimas(int n, Duomenys A[])    // rikiavimas balu mazejimo tvarka
{
    for(int j = 0; j < n; j++){
    for(int i = 1; i < n; i++){
        if(A[i].galutinis < A[j].galutinis)
        {
            swap(A[i].galutinis,A[j].galutinis);
            swap(A[i].pavadinimas,A[j].pavadinimas);
        }
    }
 }
}
