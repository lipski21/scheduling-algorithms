#include "../inc/algorytmy.hpp"

//sortowanie malejco i przydzielanie zada na wolna maszyne
void LPT(vector<Zadanie> lista_zadan, int liczba_maszyn)
{

  sort(lista_zadan.begin(), lista_zadan.end(), porownaj_zadania);

  vector<int> c_max(liczba_maszyn, 0); // c_max dla kazdej z maszyn osobno

  int nr_maszyny = 0;
  for (const auto &Zadanie : lista_zadan)
  { // rozdzielanie zadań na zmiane
    for (int i = 0; i < liczba_maszyn; i++)
    {
      if (c_max[i] < c_max[nr_maszyny])
      { // znalezienie maszyny z aktualnie najmniejszym c_max
        nr_maszyny = i;
      }
    }
    c_max[nr_maszyny] += Zadanie.getP();
    if (PRINT_ALL)
      cout << "Przydzielono zadanie numer: " << Zadanie.getNr_zadania() << " do maszyny numer: " << nr_maszyny + 1 << endl;
  }

  int max_c_max = 0;

  for (int i = 0; i < liczba_maszyn; i++)
  { // znalezenie maszyny z najwiekszym c_max
    if (c_max[i] > max_c_max)
    {
      max_c_max = c_max[i];
    }
  }

  cout << "c_max to: " << max_c_max << endl;
}

//Bez sortowania zadan przydziela pokolei na wolna maszyne
void LSA(vector<Zadanie> lista_zadan, int liczba_maszyn)
{

  //sort(lista_zadan.begin(), lista_zadan.end(), porownaj_zadania);

  vector<int> c_max(liczba_maszyn, 0); // c_max dla kazdej z maszyn osobno

  int nr_maszyny = 0;
  for (const auto &Zadanie : lista_zadan)
  {
    for (int i = 0; i < liczba_maszyn; i++)
    {
      if (c_max[i] < c_max[nr_maszyny])
      { // znalezienie maszyny z aktualnie najmniejszym c_max
        nr_maszyny = i;
      }
    }
    c_max[nr_maszyny] += Zadanie.getP(); // i dodanie do niego zadania
    if (PRINT_ALL)
      cout << "Przydzielono zadanie numer: " << Zadanie.getNr_zadania() << " do maszyny numer: " << nr_maszyny + 1 << endl;
  }

  int max_c_max = 0;

  for (int i = 0; i < liczba_maszyn; i++)
  { // znaleznie najmniejszego c_max
    if (c_max[i] > max_c_max)
    {
      max_c_max = c_max[i];
    }
  }

  cout << "c_max to: " << max_c_max << endl;
}

void PD(vector<Zadanie> lista_zadan, int liczba_maszyn)
{
  int Kl = 0;
  int n = lista_zadan.size();

  // Sumowanie Kl = suma p_j
  for (const auto &Zadanie : lista_zadan)
  {
    Kl += Zadanie.getP();
  }
  Kl = (Kl / 2) + 1;

  // Definiowanie tablicy i wypeienie jej zerami
  int T[n + 1][Kl];
  for (int j = 0; j < n + 1; j++)
    for (int k = 0; k < Kl; k++)
    {
      T[j][k] = 0;
    }

  // Wypeienie kolumny zerowej samymi jedynkami (Dodatkwe zadanie zerowe ma p_j=0 dlatego moze sie wykonac zawsze)
  for (int j = 0; j < n + 1; j++)
    T[j][0] = 1;

  // Petla ostateczna do liczenia tablicy dynamicznej
  for (int j = 1; j < n + 1; j++)
  {
    for (int k = 1; k < Kl; k++)
    {
      if (T[j - 1][k] == 1)
        T[j][k] = 1;
      if (k >= lista_zadan[j - 1].getP())
      {
        if (T[j - 1][k - lista_zadan[j - 1].getP()] == 1)
        {
          T[j][k] = 1;
        }
      }
    }
  }

  // ladne wyswietlenie tablicy dynamicznej
  if (PRINT_ALL)
  {
    cout << "  ";
    for (int k = 0; k < Kl; k++)
    {
      cout << k << " ";
    }
    cout << endl;
    for (int j = 0; j < n + 1; j++)
    {
      cout << j << " ";
      for (int k = 0; k < Kl; k++)
      {
        cout << T[j][k];
        if (k < 9)
          cout << " ";
        else
          cout << "  ";
      }
      cout << endl;
    }
  }
  // Back
  int a = n;
  int c = n;
  int b = Kl - 1;
  int l = 0;
  int lista_zadan_maszyny1[n];

  while (a > 0 && b > 0)
  {
    if (T[a][b] == 1)
    {
      lista_zadan_maszyny1[l++] = a;
      b -= lista_zadan[a - 1].getP();
      a = 0;
      c--;
      while (T[a][b] != 1)
      {
        a++;
        if (a > c)
        {
          a = lista_zadan_maszyny1[--l];
          b += lista_zadan[a - 1].getP();
          a--;
          c++;
          continue;
        }
      }
    }
    else
    {
      b--;
    }
  }

  vector<int> c_max(liczba_maszyn, 0);

  if (PRINT_ALL)
    cout << "Do maszyny numer: 1 przydzielono zadania numer: ";
  for (int i = 0; i < l; i++)
  {
    if (PRINT_ALL)
      cout << lista_zadan_maszyny1[i] << " ";
    c_max[0] += lista_zadan[lista_zadan_maszyny1[i] - 1].getP();
    lista_zadan.erase(lista_zadan.begin() + (lista_zadan_maszyny1[i] - 1));
  }
  if (PRINT_ALL)
    cout << endl;

  if (PRINT_ALL)
    cout << "Do maszyny numer: 2 przydzielono zadania numer: ";
  for (int i = 0; i < lista_zadan.size(); i++)
  {
    if (PRINT_ALL)
      cout << lista_zadan[i].getNr_zadania() << " ";
    c_max[1] += lista_zadan[i].getP();
  }
  if (PRINT_ALL)
    cout << endl;

  int max_c_max = 0;

  for (int i = 0; i < liczba_maszyn; i++)
  { // znaleznie najmniejszego c_max
    if (c_max[i] > max_c_max)
    {
      max_c_max = c_max[i];
    }
  }

  cout << "c_max to: " << max_c_max << endl;
}

unsigned Pot2(unsigned n)
{
  unsigned p;

  p = 1;
  while (n-- > 0)
    p += p;
  return (p);
}

void Gray(unsigned n)
{
  unsigned i, p;

  p = Pot2(n);

  for (i = 0; i < p; i++){
    //cout << i << endl;
    WyrazyGraya[i] = i ^ (i >> 1);
  }

}

void Pisz_PZ(unsigned n)
{
  unsigned i, kg, p, m;

  p = Pot2(n);
  for (i = 0; i < p / 2; i++)
  {
    kg = WyrazyGraya[i];
    cout << i << " ";
    for (m = p >> 1; m > 0; m >>= 1)
      cout << ((kg & m) ? "1" : "0");
    cout << endl;
  };
}

void Licz_PZ(vector<Zadanie> lista_zadan, int liczba_maszyn)
{
  unsigned kg, p, m, n, wynik;
  vector<int> c_max(liczba_maszyn, 0);
  vector<int> c_min(liczba_maszyn, 100000);
  n = lista_zadan.size();

  p = Pot2(n);
  for (int i = 0; i < p / 2; i++)
  {
    c_max[0] = 0;
    c_max[1] = 0;
    kg = WyrazyGraya[i];
    
    for (int q = 0, m = p >> 1; m > 0; m >>= 1, q++)
    {
      ((kg & m) ? c_max[0] += lista_zadan[q].getP() : c_max[1] += lista_zadan[q].getP());
    }

    if (c_max[0] == c_max[1])
    {
      c_min[0] = c_max[0];
      c_min[1] = c_max[1];
      wynik = kg;
      break;
    }
    else if (c_max[0] + 1 == c_max[1] || c_max[0] - 1 == c_max[1])
    {
      c_min[0] = c_max[0];
      c_min[1] = c_max[1];
      wynik = kg;
    }
    else if (c_max[0] + 2 == c_max[1] || c_max[0] - 2 == c_max[1])
    {
      c_min[0] = c_max[0];
      c_min[1] = c_max[1];
      wynik = kg;
    }
  }

  cout << "c_max_1 to: " << c_min[0] << endl;
  cout << "c_max_2 to: " << c_min[1] << endl;
  int max_c_max = 0;

  for (int i = 0; i < liczba_maszyn; i++)
  { // znaleznie najmniejszego c_max
    if (c_min[i] > max_c_max)
    {
      max_c_max = c_min[i];
    }
  }
  if (PRINT_ALL)
  {
    for (int q = 0, m = p >> 1; m > 0; m >>= 1, q++)
    {
      ((wynik & m) ? cout << "Przydzielono zadanie numer: " << q + 1 << " do maszyny numer: 1" << endl : cout << "Przydzielono zadanie numer: " << q + 1 << " do maszyny numer: 2" << endl);
    }
  }
  cout << "C_max to: " << max_c_max << endl;
}

void PZ(vector<Zadanie> lista_zadan, int liczba_maszyn)
{
  int n = lista_zadan.size();
  Gray(n);
  if (PRINT_GRAY)
  {
    cout << "Generacja kodu Gray'a\n"
            "---------------------\n";
    cout << endl;
    Pisz_PZ(n);
  }
  Licz_PZ(lista_zadan, liczba_maszyn);
}
