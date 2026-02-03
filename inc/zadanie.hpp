#pragma once
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define LICZBA_MASZYN 2

class Zadanie{
private:
  int nr_zadania; 
  int p;  //czas wykonywania

public:
  Zadanie(int nr, int _p) : nr_zadania(nr), p(_p) {} //konstruktor

  int getNr_zadania() const {return nr_zadania;}
  int getP() const {return p;}
};


bool porownaj_zadania(const Zadanie& a, const Zadanie& b) {
  return a.getP() > b.getP();
}
