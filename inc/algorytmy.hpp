#pragma once
#include "zadanie.hpp"
#define PRINT_GRAY false
#define PRINT_ALL true

unsigned WyrazyGraya[1024];

void LPT(vector<Zadanie> lista_zadan, int liczba_maszyn);

void LSA(vector<Zadanie> lista_zadan, int liczba_maszyn);

void PD(vector<Zadanie> lista_zadan, int liczba_maszyn);

void PZ(vector<Zadanie> lista_zadan, int liczba_maszyn);

void Licz_PZ(vector<Zadanie> lista_zadan, int liczba_maszyn);

void Pisz_PZ(unsigned n);

void Gray(unsigned n);

unsigned Pot2(unsigned n);
