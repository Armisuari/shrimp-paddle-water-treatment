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

// Fuzzy Input 4 Kekeruhan
  FuzzyInput *Kekeruhan = new FuzzyInput(2);
  FuzzySet *Kekeruhan_Rendah = new FuzzySet(0, 0, 200, 400);
  Kekeruhan->addFuzzySet(Kekeruhan_Rendah);
  FuzzySet *Kekeruhan_Normal = new FuzzySet(200, 400, 600, 800);
  Kekeruhan->addFuzzySet(Kekeruhan_Normal);
  FuzzySet *Kekeruhan_Banyak = new FuzzySet(600, 800, 1000, 1000);
  Kekeruhan->addFuzzySet(Kekeruhan_Banyak);
  fuzzy->addFuzzyInput(Kekeruhan);

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

  // Rule 1
  FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah1 = new FuzzyRuleAntecedent();
  pH_Rendah_Kekeruhan_Rendah1->joinWithAND(pH_Rendah, Kekeruhan_Rendah);
  FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal1  = new FuzzyRuleAntecedent();
  pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal1->joinWithAND(pH_Rendah_Kekeruhan_Rendah1, Jarak_Dangkal);
  FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal_EC_Rendah1  = new FuzzyRuleAntecedent();
  pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal_EC_Rendah1->joinWithAND(pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal1, EC_Rendah);
  FuzzyRuleConsequent *Ganti1 = new FuzzyRuleConsequent();
  Ganti1->addOutput(Ganti);
  FuzzyRule *fuzzyRule1 = new FuzzyRule(1,pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal_EC_Rendah1, Ganti1);
  fuzzy->addFuzzyRule(fuzzyRule1);

// Rule 3
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah3 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah3->joinWithAND(pH_Rendah, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal3 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal3->joinWithAND(pH_Rendah_Kekeruhan_Rendah3, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal_EC_Tinggi3 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal_EC_Tinggi3->joinWithAND(pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal3, EC_Tinggi);
FuzzyRuleConsequent *Ganti3 = new FuzzyRuleConsequent();
Ganti3->addOutput(Ganti);
FuzzyRule *fuzzyRule3 = new FuzzyRule(3, pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal_EC_Tinggi3, Ganti3);
fuzzy->addFuzzyRule(fuzzyRule3);

// Rule 10
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal10 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal10->joinWithAND(pH_Rendah, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal10 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal10->joinWithAND(pH_Rendah_Kekeruhan_Normal10, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal_EC_Rendah10 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal_EC_Rendah10->joinWithAND(pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal10, EC_Rendah);
FuzzyRuleConsequent *Ganti10 = new FuzzyRuleConsequent();
Ganti10->addOutput(Ganti);
FuzzyRule *fuzzyRule10 = new FuzzyRule(10, pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal_EC_Rendah10, Ganti10);
fuzzy->addFuzzyRule(fuzzyRule10);

// Rule 12
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal12 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal12->joinWithAND(pH_Rendah, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal12 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal12->joinWithAND(pH_Rendah_Kekeruhan_Normal12, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal_EC_Tinggi12 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal_EC_Tinggi12->joinWithAND(pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal12, EC_Tinggi);
FuzzyRuleConsequent *Ganti12 = new FuzzyRuleConsequent();
Ganti12->addOutput(Ganti);
FuzzyRule *fuzzyRule12 = new FuzzyRule(12, pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal_EC_Tinggi12, Ganti12);
fuzzy->addFuzzyRule(fuzzyRule12);

// Rule 19
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak19 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak19->joinWithAND(pH_Rendah, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal19 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal19->joinWithAND(pH_Rendah_Kekeruhan_Banyak19, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal_EC_Rendah19 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal_EC_Rendah19->joinWithAND(pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal19, EC_Rendah);
FuzzyRuleConsequent *Ganti19 = new FuzzyRuleConsequent();
Ganti19->addOutput(Ganti);
FuzzyRule *fuzzyRule19 = new FuzzyRule(19, pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal_EC_Rendah19, Ganti19);
fuzzy->addFuzzyRule(fuzzyRule19);

// Rule 20
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak20 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak20->joinWithAND(pH_Rendah, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal20 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal20->joinWithAND(pH_Rendah_Kekeruhan_Banyak20, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal_EC_Normal20 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal_EC_Normal20->joinWithAND(pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal20, EC_Normal);
FuzzyRuleConsequent *Ganti20 = new FuzzyRuleConsequent();
Ganti20->addOutput(Ganti);
FuzzyRule *fuzzyRule20 = new FuzzyRule(20, pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal_EC_Normal20, Ganti20);
fuzzy->addFuzzyRule(fuzzyRule20);

// Rule 21
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak21 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak21->joinWithAND(pH_Rendah, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal21 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal21->joinWithAND(pH_Rendah_Kekeruhan_Banyak21, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal_EC_Tinggi21 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal_EC_Tinggi21->joinWithAND(pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal21, EC_Tinggi);
FuzzyRuleConsequent *Ganti21 = new FuzzyRuleConsequent();
Ganti21->addOutput(Ganti);
FuzzyRule *fuzzyRule21 = new FuzzyRule(21, pH_Rendah_Kekeruhan_Banyak_Jarak_Dangkal_EC_Tinggi21, Ganti21);
fuzzy->addFuzzyRule(fuzzyRule21);

// Rule 22
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak22 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak22->joinWithAND(pH_Rendah, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang22 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang22->joinWithAND(pH_Rendah_Kekeruhan_Banyak22, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang_EC_Rendah22 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang_EC_Rendah22->joinWithAND(pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang22, EC_Rendah);
FuzzyRuleConsequent *Ganti22 = new FuzzyRuleConsequent();
Ganti22->addOutput(Ganti);
FuzzyRule *fuzzyRule22 = new FuzzyRule(22, pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang_EC_Rendah22, Ganti22);
fuzzy->addFuzzyRule(fuzzyRule22);

// Rule 24
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak24 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak24->joinWithAND(pH_Rendah, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang24 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang24->joinWithAND(pH_Rendah_Kekeruhan_Banyak24, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang_EC_Tinggi24 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang_EC_Tinggi24->joinWithAND(pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang24, EC_Tinggi);
FuzzyRuleConsequent *Ganti24 = new FuzzyRuleConsequent();
Ganti24->addOutput(Ganti);
FuzzyRule *fuzzyRule24 = new FuzzyRule(24, pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang_EC_Tinggi24, Ganti24);
fuzzy->addFuzzyRule(fuzzyRule24);

// Rule 25
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak25 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak25->joinWithAND(pH_Rendah, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam25 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam25->joinWithAND(pH_Rendah_Kekeruhan_Banyak25, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam_EC_Rendah25 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam_EC_Rendah25->joinWithAND(pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam25, EC_Rendah);
FuzzyRuleConsequent *Ganti25 = new FuzzyRuleConsequent();
Ganti25->addOutput(Ganti);
FuzzyRule *fuzzyRule25 = new FuzzyRule(25, pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam_EC_Rendah25, Ganti25);
fuzzy->addFuzzyRule(fuzzyRule25);

// Rule 27
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak27 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak27->joinWithAND(pH_Rendah, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam27 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam27->joinWithAND(pH_Rendah_Kekeruhan_Banyak27, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam_EC_Tinggi27 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam_EC_Tinggi27->joinWithAND(pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam27, EC_Tinggi);
FuzzyRuleConsequent *Ganti27 = new FuzzyRuleConsequent();
Ganti27->addOutput(Ganti);
FuzzyRule *fuzzyRule27 = new FuzzyRule(27, pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam_EC_Tinggi27, Ganti27);
fuzzy->addFuzzyRule(fuzzyRule27);

// Rule 46
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak46 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak46->joinWithAND(pH_Normal, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal46 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal46->joinWithAND(pH_Normal_Kekeruhan_Banyak46, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal_EC_Rendah46 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal_EC_Rendah46->joinWithAND(pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal46, EC_Rendah);
FuzzyRuleConsequent *Ganti46 = new FuzzyRuleConsequent();
Ganti46->addOutput(Ganti);
FuzzyRule *fuzzyRule46 = new FuzzyRule(46, pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal_EC_Rendah46, Ganti46);
fuzzy->addFuzzyRule(fuzzyRule46);

// Rule 48
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak48 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak48->joinWithAND(pH_Normal, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal48 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal48->joinWithAND(pH_Normal_Kekeruhan_Banyak48, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal_EC_Tinggi48 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal_EC_Tinggi48->joinWithAND(pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal48, EC_Tinggi);
FuzzyRuleConsequent *Ganti48 = new FuzzyRuleConsequent();
Ganti48->addOutput(Ganti);
FuzzyRule *fuzzyRule48 = new FuzzyRule(48, pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal_EC_Tinggi48, Ganti48);
fuzzy->addFuzzyRule(fuzzyRule48);

// Rule 55
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah55 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah55->joinWithAND(pH_Banyak, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal55 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal55->joinWithAND(pH_Banyak_Kekeruhan_Rendah55, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal_EC_Rendah55 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal_EC_Rendah55->joinWithAND(pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal55, EC_Rendah);
FuzzyRuleConsequent *Ganti55 = new FuzzyRuleConsequent();
Ganti55->addOutput(Ganti);
FuzzyRule *fuzzyRule55 = new FuzzyRule(55, pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal_EC_Rendah55, Ganti55);
fuzzy->addFuzzyRule(fuzzyRule55);

// Rule 57
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah57 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah57->joinWithAND(pH_Banyak, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal57 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal57->joinWithAND(pH_Banyak_Kekeruhan_Rendah57, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal_EC_Tinggi57 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal_EC_Tinggi57->joinWithAND(pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal57, EC_Tinggi);
FuzzyRuleConsequent *Ganti57 = new FuzzyRuleConsequent();
Ganti57->addOutput(Ganti);
FuzzyRule *fuzzyRule57 = new FuzzyRule(57, pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal_EC_Tinggi57, Ganti57);
fuzzy->addFuzzyRule(fuzzyRule57);

// Rule 64
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal64 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal64->joinWithAND(pH_Banyak, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal64 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal64->joinWithAND(pH_Banyak_Kekeruhan_Normal64, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal_EC_Rendah64 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal_EC_Rendah64->joinWithAND(pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal64, EC_Rendah);
FuzzyRuleConsequent *Ganti64 = new FuzzyRuleConsequent();
Ganti64->addOutput(Ganti);
FuzzyRule *fuzzyRule64 = new FuzzyRule(64, pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal_EC_Rendah64, Ganti64);
fuzzy->addFuzzyRule(fuzzyRule64);

// Rule 66
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal66 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal66->joinWithAND(pH_Banyak, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal66 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal66->joinWithAND(pH_Banyak_Kekeruhan_Normal66, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal_EC_Tinggi66 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal_EC_Tinggi66->joinWithAND(pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal66, EC_Tinggi);
FuzzyRuleConsequent *Ganti66 = new FuzzyRuleConsequent();
Ganti66->addOutput(Ganti);
FuzzyRule *fuzzyRule66 = new FuzzyRule(66, pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal_EC_Tinggi66, Ganti66);
fuzzy->addFuzzyRule(fuzzyRule66);

// Rule 73
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak73 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak73->joinWithAND(pH_Banyak, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal73 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal73->joinWithAND(pH_Banyak_Kekeruhan_Banyak73, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal_EC_Rendah73 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal_EC_Rendah73->joinWithAND(pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal73, EC_Rendah);
FuzzyRuleConsequent *Ganti73 = new FuzzyRuleConsequent();
Ganti73->addOutput(Ganti);
FuzzyRule *fuzzyRule73 = new FuzzyRule(73, pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal_EC_Rendah73, Ganti73);
fuzzy->addFuzzyRule(fuzzyRule73);

// Rule 74
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak74 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak74->joinWithAND(pH_Banyak, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal74 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal74->joinWithAND(pH_Banyak_Kekeruhan_Banyak74, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal_EC_Normal74 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal_EC_Normal74->joinWithAND(pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal74, EC_Normal);
FuzzyRuleConsequent *Ganti74 = new FuzzyRuleConsequent();
Ganti74->addOutput(Ganti);
FuzzyRule *fuzzyRule74 = new FuzzyRule(74, pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal_EC_Normal74, Ganti74);
fuzzy->addFuzzyRule(fuzzyRule74);

// Rule 75
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak75 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak75->joinWithAND(pH_Banyak, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal75 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal75->joinWithAND(pH_Banyak_Kekeruhan_Banyak75, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal_EC_Tinggi75 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal_EC_Tinggi75->joinWithAND(pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal75, EC_Tinggi);
FuzzyRuleConsequent *Ganti75 = new FuzzyRuleConsequent();
Ganti75->addOutput(Ganti);
FuzzyRule *fuzzyRule75 = new FuzzyRule(75, pH_Banyak_Kekeruhan_Banyak_Jarak_Dangkal_EC_Tinggi75, Ganti75);
fuzzy->addFuzzyRule(fuzzyRule75);

// Rule 76
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak76 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak76->joinWithAND(pH_Banyak, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang76 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang76->joinWithAND(pH_Banyak_Kekeruhan_Banyak76, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang_EC_Rendah76 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang_EC_Rendah76->joinWithAND(pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang76, EC_Rendah);
FuzzyRuleConsequent *Ganti76 = new FuzzyRuleConsequent();
Ganti76->addOutput(Ganti);
FuzzyRule *fuzzyRule76 = new FuzzyRule(76, pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang_EC_Rendah76, Ganti76);
fuzzy->addFuzzyRule(fuzzyRule76);

// Rule 78
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak78 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak78->joinWithAND(pH_Banyak, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang78 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang78->joinWithAND(pH_Banyak_Kekeruhan_Banyak78, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang_EC_Tinggi78 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang_EC_Tinggi78->joinWithAND(pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang78, EC_Tinggi);
FuzzyRuleConsequent *Ganti78 = new FuzzyRuleConsequent();
Ganti78->addOutput(Ganti);
FuzzyRule *fuzzyRule78 = new FuzzyRule(78, pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang_EC_Tinggi78, Ganti78);
fuzzy->addFuzzyRule(fuzzyRule78);

// Rule 79
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak79 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak79->joinWithAND(pH_Banyak, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam79 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam79->joinWithAND(pH_Banyak_Kekeruhan_Banyak79, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam_EC_Rendah79 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam_EC_Rendah79->joinWithAND(pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam79, EC_Rendah);
FuzzyRuleConsequent *Ganti79 = new FuzzyRuleConsequent();
Ganti79->addOutput(Ganti);
FuzzyRule *fuzzyRule79 = new FuzzyRule(79, pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam_EC_Rendah79, Ganti79);
fuzzy->addFuzzyRule(fuzzyRule79);

// Rule 81
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak81 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak81->joinWithAND(pH_Banyak, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam81 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam81->joinWithAND(pH_Banyak_Kekeruhan_Banyak81, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam_EC_Tinggi81 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam_EC_Tinggi81->joinWithAND(pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam81, EC_Tinggi);
FuzzyRuleConsequent *Ganti81 = new FuzzyRuleConsequent();
Ganti81->addOutput(Ganti);
FuzzyRule *fuzzyRule81 = new FuzzyRule(81, pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam_EC_Tinggi81, Ganti81);
fuzzy->addFuzzyRule(fuzzyRule81);
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