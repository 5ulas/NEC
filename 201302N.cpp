#include <iostream>
#include <fstream> // ifstream
#include <algorithm> // swap
#include <iomanip> // setw

using namespace std;

struct Duomenys{
       string miestas;
       string apskritis;
       int skaicius;
};
struct Rezultatai{
      string apskritis;
      int maz = 0;
      int viso = 0;
};

void Nuskaitymas(int &n, Duomenys A[]);
void Naujas(int n, int &m, Duomenys A[], Rezultatai B[], int &z);
int Yra(int m, string zodis, Rezultatai B[]);
void Rikiaviams(int m, Rezultatai B[]);

int main()
{
    int n , m, z;
    Duomenys A[100];
    Rezultatai B[100];
    Nuskaitymas(n,A);
    Naujas(n,m,A,B,z);
    Rikiaviams(m,B);
    cout << m << endl;
    for(int i = 0; i < m; i++){
        cout << B[i].apskritis << B[i].maz << " " << B[i].viso << endl;
    }
}

void Nuskaitymas(int &n, Duomenys A[])
{
    ifstream GET("201302.txt");
    GET >> n;
    GET.ignore(80, '\n');;
    char eil1[21], eil2[14];
    for(int i = 0; i < n; i++){
        GET.get(eil1, 21);
        A[i].miestas = eil1;
        GET.get(eil2, 14);
        A[i].apskritis = eil2;
        GET >> A[i].skaicius;
        GET.ignore(80, '\n');
    }
    GET.close();
}

void Naujas(int n, int &m, Duomenys A[], Rezultatai B[], int &z)
{
    m = 0;
    z = 0;
    string zodis;
    for(int i = 0; i < n; i++){
        zodis = A[i].apskritis;
        int k = Yra(m,zodis,B);
        if(k >= 0)
        {
            B[k].viso += A[i].skaicius; // jeigu rado pasikartojima, rasto indekso vietoje pridedam [i] apskrities gyv. skaiciu
            if(A[i].skaicius < B[k].maz)
            {
                B[k].maz = A[i].skaicius;
            }
        }
        else if(k < 0)
        {
            B[m].maz = A[i].skaicius;
            B[m].apskritis = A[i].apskritis; // Nera pasikartojimo -> pildoma struktura nauja apskritimi
            B[m].viso += A[i].skaicius;
            m++;
        }
    }
}

int Yra(int m, string zodis, Rezultatai B[])
{
    for(int i = 0; i <= m; i++){
        if(zodis == B[i].apskritis)
        {
                return i;
        }
        }
    return -1;
}

void Rikiaviams(int m, Rezultatai B[])
{
    for(int i = 0; i < m; i++){
        if(B[i].maz > B[i+1].maz){
            swap(B[i],B[i+1]);
        }
        else if(B[i].maz == B[i+1].maz){            // abeceles tvarka
            if(B[i].apskritis > B[i+1].apskritis){
            swap(B[i],B[i+1]);
            }
        }
    }
}
