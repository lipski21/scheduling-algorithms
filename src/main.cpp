#include "algorytmy.cpp"
#include <chrono>
#include <stdlib.h>
#include <experimental/random>

#define LICZBA_ZADAN 10
#define PRZEDZIAL_DOL 1
#define PRZEDZIAL_GORA 10
#define PRINT_ZADANIA false


int losuj_pj(){
  int liczba = 0; 
  experimental::reseed();

  liczba = experimental::randint(PRZEDZIAL_DOL, PRZEDZIAL_GORA);
  return liczba;
}

int main()
{
  vector<Zadanie> zadania;
  for(int i=0; i < LICZBA_ZADAN ; i++){
    zadania.push_back(Zadanie(i+1, losuj_pj()));
  }

if(PRINT_ZADANIA){
  for (Zadanie n : zadania)
    cout << n.getNr_zadania() << ' ' << n.getP() << endl;
}
/*
   vector<Zadanie> zadania = {
      Zadanie(1, 3), // losowe wartości
      Zadanie(2, 7),
      Zadanie(3, 1),
      Zadanie(4, 9),
      Zadanie(5, 5),
      Zadanie(6, 20),
      Zadanie(7, 3)};
*/

  cout << endl << "LSA:" << endl;
  auto start_LSA = chrono::high_resolution_clock::now();
  LSA(zadania, LICZBA_MASZYN);
  auto end_LSA = chrono::high_resolution_clock::now();
  chrono::duration<double> duration_LSA = end_LSA - start_LSA;
  cout << endl << "Czas działania algorytmu to: " << duration_LSA.count() << " sekund" << endl;

  cout << endl << "LPT:" << endl;
  auto start_LPT = chrono::high_resolution_clock::now();
  LPT(zadania, LICZBA_MASZYN);
  auto end_LPT = chrono::high_resolution_clock::now();
  chrono::duration<double> duration_LPT = end_LPT - start_LPT;
  cout << endl << "Czas działania algorytmu to: " << duration_LPT.count() << " sekund" << endl;
  

  cout << endl << "PD:" << endl;
  auto start_PD = chrono::high_resolution_clock::now();
  PD(zadania, LICZBA_MASZYN);
  auto end_PD = chrono::high_resolution_clock::now();
  chrono::duration<double> duration_PD = end_PD - start_PD;
  cout << endl << "Czas działania algorytmu to: " << duration_PD.count() << " sekund" << endl;


  cout << endl << "PZ:" << endl;
  auto start_PZ = chrono::high_resolution_clock::now();
  PZ(zadania, LICZBA_MASZYN);
  auto end_PZ = chrono::high_resolution_clock::now();
  chrono::duration<double> duration_PZ = end_PZ - start_PZ;
  cout << endl << "Czas działania algorytmu to: " << duration_PZ.count() << " sekund" << endl;

  return 0;
}

