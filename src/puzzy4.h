#pragma once
#include "Fuzzy.h"

Fuzzy *fuzzy = new Fuzzy();

typedef struct
{
  void begin();
  bool setinput(int index, float input);
  bool fuzify();
  int output();
} FuzzyHandler;

void FuzzyHandler::begin()
{

// Fuzzy Input 2 pH
  FuzzyInput *pH = new FuzzyInput(1);
  FuzzySet *pH_Rendah = new FuzzySet(0, 0, 4, 5);
  pH->addFuzzySet(pH_Rendah);
  FuzzySet *pH_Normal = new FuzzySet(4, 5, 7, 8);
  pH->addFuzzySet(pH_Normal);
  FuzzySet *pH_Banyak = new FuzzySet(7, 8, 12, 12);
  pH->addFuzzySet(pH_Banyak);
  fuzzy->addFuzzyInput(pH);

// Fuzzy Input 4 DO
  FuzzyInput *DO = new FuzzyInput(2);
  FuzzySet *DO_Rendah = new FuzzySet(0, 0, 2, 4);
  DO->addFuzzySet(DO_Rendah);
  FuzzySet *DO_Normal = new FuzzySet(3, 5, 6, 8);
  DO->addFuzzySet(DO_Normal);
  FuzzySet *DO_Banyak = new FuzzySet(8, 10, 12, 12);
  DO->addFuzzySet(DO_Banyak);
  fuzzy->addFuzzyInput(DO);

// Fuzzy Input 5 Jarak
  FuzzyInput *Jarak = new FuzzyInput(3);
  FuzzySet *Jarak_Dangkal = new FuzzySet(0, 0, 30, 70);
  Jarak->addFuzzySet(Jarak_Dangkal);
  FuzzySet *Jarak_Sedang = new FuzzySet(50, 70, 80, 100);
  Jarak->addFuzzySet(Jarak_Sedang);
  FuzzySet *Jarak_Dalam = new FuzzySet(80, 120, 150, 150);
  Jarak->addFuzzySet(Jarak_Dalam);
  fuzzy->addFuzzyInput(Jarak);

// Fuzzy Input 6 EC
  FuzzyInput *EC = new FuzzyInput(4);
  FuzzySet *EC_Rendah = new FuzzySet(0, 0, 2000, 4500);
  EC->addFuzzySet(EC_Rendah);
  FuzzySet *EC_Normal = new FuzzySet(4000, 4500, 4500, 5000);
  EC->addFuzzySet(EC_Normal);
  FuzzySet *EC_Tinggi = new FuzzySet(4500, 7000, 8000, 8000);
  EC->addFuzzySet(EC_Tinggi);
  fuzzy->addFuzzyInput(EC);  

// Fuzzy Output
  FuzzyOutput *Notif = new FuzzyOutput(1);
  FuzzySet *Aman = new FuzzySet(0, 0, 0, 0);
  Notif->addFuzzySet(Aman);
  FuzzySet *Ganti = new FuzzySet(1, 1, 1, 1);
  Notif->addFuzzySet(Ganti);
  fuzzy->addFuzzyOutput(Notif);

  // Rule 3
FuzzyRuleAntecedent *pH_Rendah_DO_Rendah3 = new FuzzyRuleAntecedent();
pH_Rendah_DO_Rendah3->joinWithAND(pH_Rendah, DO_Rendah);
FuzzyRuleAntecedent *pH_Rendah_DO_Rendah_Jarak_Dangkal3 = new FuzzyRuleAntecedent();
pH_Rendah_DO_Rendah_Jarak_Dangkal3->joinWithAND(pH_Rendah_DO_Rendah3, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_DO_Rendah_Jarak_Dangkal_EC_Tinggi3 = new FuzzyRuleAntecedent();
pH_Rendah_DO_Rendah_Jarak_Dangkal_EC_Tinggi3->joinWithAND(pH_Rendah_DO_Rendah_Jarak_Dangkal3, EC_Tinggi);
FuzzyRuleConsequent *Ganti3 = new FuzzyRuleConsequent();
Ganti3->addOutput(Ganti);
FuzzyRule *fuzzyRule3 = new FuzzyRule(3, pH_Rendah_DO_Rendah_Jarak_Dangkal_EC_Tinggi3, Ganti3);
fuzzy->addFuzzyRule(fuzzyRule3);


// Rule 21
FuzzyRuleAntecedent *pH_Rendah_DO_Banyak21 = new FuzzyRuleAntecedent();
pH_Rendah_DO_Banyak21->joinWithAND(pH_Rendah, DO_Banyak);
FuzzyRuleAntecedent *pH_Rendah_DO_Banyak_Jarak_Dangkal21 = new FuzzyRuleAntecedent();
pH_Rendah_DO_Banyak_Jarak_Dangkal21->joinWithAND(pH_Rendah_DO_Banyak21, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_DO_Banyak_Jarak_Dangkal_EC_Tinggi21 = new FuzzyRuleAntecedent();
pH_Rendah_DO_Banyak_Jarak_Dangkal_EC_Tinggi21->joinWithAND(pH_Rendah_DO_Banyak_Jarak_Dangkal21, EC_Tinggi);
FuzzyRuleConsequent *Ganti21 = new FuzzyRuleConsequent();
Ganti21->addOutput(Ganti);
FuzzyRule *fuzzyRule21 = new FuzzyRule(21, pH_Rendah_DO_Banyak_Jarak_Dangkal_EC_Tinggi21, Ganti21);
fuzzy->addFuzzyRule(fuzzyRule21);

// Rule 57
FuzzyRuleAntecedent *pH_Banyak_DO_Rendah57 = new FuzzyRuleAntecedent();
pH_Banyak_DO_Rendah57->joinWithAND(pH_Banyak, DO_Rendah);
FuzzyRuleAntecedent *pH_Banyak_DO_Rendah_Jarak_Dangkal57 = new FuzzyRuleAntecedent();
pH_Banyak_DO_Rendah_Jarak_Dangkal57->joinWithAND(pH_Banyak_DO_Rendah57, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_DO_Rendah_Jarak_Dangkal_EC_Tinggi57 = new FuzzyRuleAntecedent();
pH_Banyak_DO_Rendah_Jarak_Dangkal_EC_Tinggi57->joinWithAND(pH_Banyak_DO_Rendah_Jarak_Dangkal57, EC_Tinggi);
FuzzyRuleConsequent *Ganti57 = new FuzzyRuleConsequent();
Ganti57->addOutput(Ganti);
FuzzyRule *fuzzyRule57 = new FuzzyRule(57, pH_Banyak_DO_Rendah_Jarak_Dangkal_EC_Tinggi57, Ganti57);
fuzzy->addFuzzyRule(fuzzyRule57);


// Rule 75
FuzzyRuleAntecedent *pH_Banyak_DO_Banyak75 = new FuzzyRuleAntecedent();
pH_Banyak_DO_Banyak75->joinWithAND(pH_Banyak, DO_Banyak);
FuzzyRuleAntecedent *pH_Banyak_DO_Banyak_Jarak_Dangkal75 = new FuzzyRuleAntecedent();
pH_Banyak_DO_Banyak_Jarak_Dangkal75->joinWithAND(pH_Banyak_DO_Banyak75, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_DO_Banyak_Jarak_Dangkal_EC_Tinggi75 = new FuzzyRuleAntecedent();
pH_Banyak_DO_Banyak_Jarak_Dangkal_EC_Tinggi75->joinWithAND(pH_Banyak_DO_Banyak_Jarak_Dangkal75, EC_Tinggi);
FuzzyRuleConsequent *Ganti75 = new FuzzyRuleConsequent();
Ganti75->addOutput(Ganti);
FuzzyRule *fuzzyRule75 = new FuzzyRule(75, pH_Banyak_DO_Banyak_Jarak_Dangkal_EC_Tinggi75, Ganti75);
fuzzy->addFuzzyRule(fuzzyRule75);
}

bool FuzzyHandler::setinput(int index, float input)
{
  // Mengatur input untuk fuzzy dengan indeks yang ditentukan
  return fuzzy->setInput(index, input);
}

bool FuzzyHandler::fuzify()
{
  // Memulai proses fuzzifikasi
  return fuzzy->fuzzify();
}

int FuzzyHandler::output()
{
  // Mendapatkan nilai keluaran fuzzy
  return fuzzy->defuzzify(1);
}