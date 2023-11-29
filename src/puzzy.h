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
  FuzzySet *EC_Tinggi = new FuzzySet(4500, 5000, 5000, 8000);
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

// Rule 2
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah2 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah2->joinWithAND(pH_Rendah, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal2 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal2->joinWithAND(pH_Rendah_Kekeruhan_Rendah2, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal_EC_Normal2 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal_EC_Normal2->joinWithAND(pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal2, EC_Normal);
FuzzyRuleConsequent *Ganti2 = new FuzzyRuleConsequent();
Ganti2->addOutput(Ganti);
FuzzyRule *fuzzyRule2 = new FuzzyRule(2, pH_Rendah_Kekeruhan_Rendah_Jarak_Dangkal_EC_Normal2, Ganti2);
fuzzy->addFuzzyRule(fuzzyRule2);

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

// Rule 4
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah4 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah4->joinWithAND(pH_Rendah, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang4 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang4->joinWithAND(pH_Rendah_Kekeruhan_Rendah4, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang_EC_Rendah4 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang_EC_Rendah4->joinWithAND(pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang4, EC_Rendah);
FuzzyRuleConsequent *Ganti4 = new FuzzyRuleConsequent();
Ganti4->addOutput(Ganti);
FuzzyRule *fuzzyRule4 = new FuzzyRule(4, pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang_EC_Rendah4, Ganti4);
fuzzy->addFuzzyRule(fuzzyRule4);

// Rule 5
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah5 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah5->joinWithAND(pH_Rendah, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang5 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang5->joinWithAND(pH_Rendah_Kekeruhan_Rendah5, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang_EC_Normal5 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang_EC_Normal5->joinWithAND(pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang5, EC_Normal);
FuzzyRuleConsequent *Ganti5 = new FuzzyRuleConsequent();
Ganti5->addOutput(Ganti);
FuzzyRule *fuzzyRule5 = new FuzzyRule(5, pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang_EC_Normal5, Ganti5);
fuzzy->addFuzzyRule(fuzzyRule5);

// Rule 6
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah6 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah6->joinWithAND(pH_Rendah, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang6 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang6->joinWithAND(pH_Rendah_Kekeruhan_Rendah6, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang_EC_Tinggi6 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang_EC_Tinggi6->joinWithAND(pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang6, EC_Tinggi);
FuzzyRuleConsequent *Ganti6 = new FuzzyRuleConsequent();
Ganti6->addOutput(Ganti);
FuzzyRule *fuzzyRule6 = new FuzzyRule(6, pH_Rendah_Kekeruhan_Rendah_Jarak_Sedang_EC_Tinggi6, Ganti6);
fuzzy->addFuzzyRule(fuzzyRule6);

// Rule 7
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah7 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah7->joinWithAND(pH_Rendah, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam7 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam7->joinWithAND(pH_Rendah_Kekeruhan_Rendah7, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam_EC_Rendah7 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam_EC_Rendah7->joinWithAND(pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam7, EC_Rendah);
FuzzyRuleConsequent *Ganti7 = new FuzzyRuleConsequent();
Ganti7->addOutput(Ganti);
FuzzyRule *fuzzyRule7 = new FuzzyRule(7, pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam_EC_Rendah7, Ganti7);
fuzzy->addFuzzyRule(fuzzyRule7);

// Rule 8
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah8 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah8->joinWithAND(pH_Rendah, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam8 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam8->joinWithAND(pH_Rendah_Kekeruhan_Rendah8, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam_EC_Normal8 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam_EC_Normal8->joinWithAND(pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam8, EC_Normal);
FuzzyRuleConsequent *Ganti8 = new FuzzyRuleConsequent();
Ganti8->addOutput(Ganti);
FuzzyRule *fuzzyRule8 = new FuzzyRule(8, pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam_EC_Normal8, Ganti8);
fuzzy->addFuzzyRule(fuzzyRule8);

// Rule 9
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah9 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah9->joinWithAND(pH_Rendah, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam9 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam9->joinWithAND(pH_Rendah_Kekeruhan_Rendah9, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam_EC_Tinggi9 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam_EC_Tinggi9->joinWithAND(pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam9, EC_Tinggi);
FuzzyRuleConsequent *Ganti9 = new FuzzyRuleConsequent();
Ganti9->addOutput(Ganti);
FuzzyRule *fuzzyRule9 = new FuzzyRule(9, pH_Rendah_Kekeruhan_Rendah_Jarak_Dalam_EC_Tinggi9, Ganti9);
fuzzy->addFuzzyRule(fuzzyRule9);

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

// Rule 11
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal11 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal11->joinWithAND(pH_Rendah, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal11 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal11->joinWithAND(pH_Rendah_Kekeruhan_Normal11, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal_EC_Normal11 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal_EC_Normal11->joinWithAND(pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal11, EC_Normal);
FuzzyRuleConsequent *Ganti11 = new FuzzyRuleConsequent();
Ganti11->addOutput(Ganti);
FuzzyRule *fuzzyRule11 = new FuzzyRule(11, pH_Rendah_Kekeruhan_Normal_Jarak_Dangkal_EC_Normal11, Ganti11);
fuzzy->addFuzzyRule(fuzzyRule11);

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

// Rule 13
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal13 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal13->joinWithAND(pH_Rendah, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Sedang13 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Sedang13->joinWithAND(pH_Rendah_Kekeruhan_Normal13, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Sedang_EC_Rendah13 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Sedang_EC_Rendah13->joinWithAND(pH_Rendah_Kekeruhan_Normal_Jarak_Sedang13, EC_Rendah);
FuzzyRuleConsequent *Ganti13 = new FuzzyRuleConsequent();
Ganti13->addOutput(Ganti);
FuzzyRule *fuzzyRule13 = new FuzzyRule(13, pH_Rendah_Kekeruhan_Normal_Jarak_Sedang_EC_Rendah13, Ganti13);
fuzzy->addFuzzyRule(fuzzyRule13);

// Rule 14
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal14 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal14->joinWithAND(pH_Rendah, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Sedang14 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Sedang14->joinWithAND(pH_Rendah_Kekeruhan_Normal14, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Sedang_EC_Normal14 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Sedang_EC_Normal14->joinWithAND(pH_Rendah_Kekeruhan_Normal_Jarak_Sedang14, EC_Normal);
FuzzyRuleConsequent *Ganti14 = new FuzzyRuleConsequent();
Ganti14->addOutput(Ganti);
FuzzyRule *fuzzyRule14 = new FuzzyRule(14, pH_Rendah_Kekeruhan_Normal_Jarak_Sedang_EC_Normal14, Ganti14);
fuzzy->addFuzzyRule(fuzzyRule14);

// Rule 15
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal15 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal15->joinWithAND(pH_Rendah, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Sedang15 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Sedang15->joinWithAND(pH_Rendah_Kekeruhan_Normal15, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Sedang_EC_Tinggi15 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Sedang_EC_Tinggi15->joinWithAND(pH_Rendah_Kekeruhan_Normal_Jarak_Sedang15, EC_Tinggi);
FuzzyRuleConsequent *Ganti15 = new FuzzyRuleConsequent();
Ganti15->addOutput(Ganti);
FuzzyRule *fuzzyRule15 = new FuzzyRule(15, pH_Rendah_Kekeruhan_Normal_Jarak_Sedang_EC_Tinggi15, Ganti15);
fuzzy->addFuzzyRule(fuzzyRule15);

// Rule 16
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal16 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal16->joinWithAND(pH_Rendah, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dalam16 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dalam16->joinWithAND(pH_Rendah_Kekeruhan_Normal16, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dalam_EC_Rendah16 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dalam_EC_Rendah16->joinWithAND(pH_Rendah_Kekeruhan_Normal_Jarak_Dalam16, EC_Rendah);
FuzzyRuleConsequent *Ganti16 = new FuzzyRuleConsequent();
Ganti16->addOutput(Ganti);
FuzzyRule *fuzzyRule16 = new FuzzyRule(16, pH_Rendah_Kekeruhan_Normal_Jarak_Dalam_EC_Rendah16, Ganti16);
fuzzy->addFuzzyRule(fuzzyRule16);

// Rule 17
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal17 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal17->joinWithAND(pH_Rendah, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dalam17 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dalam17->joinWithAND(pH_Rendah_Kekeruhan_Normal17, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dalam_EC_Normal17 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dalam_EC_Normal17->joinWithAND(pH_Rendah_Kekeruhan_Normal_Jarak_Dalam17, EC_Normal);
FuzzyRuleConsequent *Ganti17 = new FuzzyRuleConsequent();
Ganti17->addOutput(Ganti);
FuzzyRule *fuzzyRule17 = new FuzzyRule(17, pH_Rendah_Kekeruhan_Normal_Jarak_Dalam_EC_Normal17, Ganti17);
fuzzy->addFuzzyRule(fuzzyRule17);

// Rule 18
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal18 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal18->joinWithAND(pH_Rendah, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dalam18 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dalam18->joinWithAND(pH_Rendah_Kekeruhan_Normal18, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Normal_Jarak_Dalam_EC_Tinggi18 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Normal_Jarak_Dalam_EC_Tinggi18->joinWithAND(pH_Rendah_Kekeruhan_Normal_Jarak_Dalam18, EC_Tinggi);
FuzzyRuleConsequent *Ganti18 = new FuzzyRuleConsequent();
Ganti18->addOutput(Ganti);
FuzzyRule *fuzzyRule18 = new FuzzyRule(18, pH_Rendah_Kekeruhan_Normal_Jarak_Dalam_EC_Tinggi18, Ganti18);
fuzzy->addFuzzyRule(fuzzyRule18);

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

// Rule 23
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak23 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak23->joinWithAND(pH_Rendah, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang23 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang23->joinWithAND(pH_Rendah_Kekeruhan_Banyak23, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang_EC_Normal23 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang_EC_Normal23->joinWithAND(pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang23, EC_Normal);
FuzzyRuleConsequent *Ganti23 = new FuzzyRuleConsequent();
Ganti23->addOutput(Ganti);
FuzzyRule *fuzzyRule23 = new FuzzyRule(23, pH_Rendah_Kekeruhan_Banyak_Jarak_Sedang_EC_Normal23, Ganti23);
fuzzy->addFuzzyRule(fuzzyRule23);

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

// Rule 26
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak26 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak26->joinWithAND(pH_Rendah, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam26 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam26->joinWithAND(pH_Rendah_Kekeruhan_Banyak26, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam_EC_Normal26 = new FuzzyRuleAntecedent();
pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam_EC_Normal26->joinWithAND(pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam26, EC_Normal);
FuzzyRuleConsequent *Ganti26 = new FuzzyRuleConsequent();
Ganti26->addOutput(Ganti);
FuzzyRule *fuzzyRule26 = new FuzzyRule(26, pH_Rendah_Kekeruhan_Banyak_Jarak_Dalam_EC_Normal26, Ganti26);
fuzzy->addFuzzyRule(fuzzyRule26);

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

// Rule 28
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah28 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah28->joinWithAND(pH_Normal, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal28 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal28->joinWithAND(pH_Normal_Kekeruhan_Rendah28, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal_EC_Rendah28 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal_EC_Rendah28->joinWithAND(pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal28, EC_Rendah);
FuzzyRuleConsequent *Ganti28 = new FuzzyRuleConsequent();
Ganti28->addOutput(Ganti);
FuzzyRule *fuzzyRule28 = new FuzzyRule(28, pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal_EC_Rendah28, Ganti28);
fuzzy->addFuzzyRule(fuzzyRule28);

// Rule 29
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah29 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah29->joinWithAND(pH_Normal, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal29 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal29->joinWithAND(pH_Normal_Kekeruhan_Rendah29, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal_EC_Normal29 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal_EC_Normal29->joinWithAND(pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal29, EC_Normal);
FuzzyRuleConsequent *Ganti29 = new FuzzyRuleConsequent();
Ganti29->addOutput(Ganti);
FuzzyRule *fuzzyRule29 = new FuzzyRule(29, pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal_EC_Normal29, Ganti29);
fuzzy->addFuzzyRule(fuzzyRule29);

// Rule 30
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah30 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah30->joinWithAND(pH_Normal, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal30 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal30->joinWithAND(pH_Normal_Kekeruhan_Rendah30, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal_EC_Tinggi30 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal_EC_Tinggi30->joinWithAND(pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal30, EC_Tinggi);
FuzzyRuleConsequent *Ganti30 = new FuzzyRuleConsequent();
Ganti30->addOutput(Ganti);
FuzzyRule *fuzzyRule30 = new FuzzyRule(30, pH_Normal_Kekeruhan_Rendah_Jarak_Dangkal_EC_Tinggi30, Ganti30);
fuzzy->addFuzzyRule(fuzzyRule30);

// Rule 31
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah31 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah31->joinWithAND(pH_Normal, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Sedang31 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Sedang31->joinWithAND(pH_Normal_Kekeruhan_Rendah31, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Sedang_EC_Rendah31 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Sedang_EC_Rendah31->joinWithAND(pH_Normal_Kekeruhan_Rendah_Jarak_Sedang31, EC_Rendah);
FuzzyRuleConsequent *Ganti31 = new FuzzyRuleConsequent();
Ganti31->addOutput(Ganti);
FuzzyRule *fuzzyRule31 = new FuzzyRule(31, pH_Normal_Kekeruhan_Rendah_Jarak_Sedang_EC_Rendah31, Ganti31);
fuzzy->addFuzzyRule(fuzzyRule31);

// Rule 32
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah32 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah32->joinWithAND(pH_Normal, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Sedang32 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Sedang32->joinWithAND(pH_Normal_Kekeruhan_Rendah32, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Sedang_EC_Normal32 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Sedang_EC_Normal32->joinWithAND(pH_Normal_Kekeruhan_Rendah_Jarak_Sedang32, EC_Normal);
FuzzyRuleConsequent *Ganti32 = new FuzzyRuleConsequent();
Ganti32->addOutput(Ganti);
FuzzyRule *fuzzyRule32 = new FuzzyRule(32, pH_Normal_Kekeruhan_Rendah_Jarak_Sedang_EC_Normal32, Ganti32);
fuzzy->addFuzzyRule(fuzzyRule32);

// Rule 33
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah33 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah33->joinWithAND(pH_Normal, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Sedang33 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Sedang33->joinWithAND(pH_Normal_Kekeruhan_Rendah33, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Sedang_EC_Tinggi33 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Sedang_EC_Tinggi33->joinWithAND(pH_Normal_Kekeruhan_Rendah_Jarak_Sedang33, EC_Tinggi);
FuzzyRuleConsequent *Ganti33 = new FuzzyRuleConsequent();
Ganti33->addOutput(Ganti);
FuzzyRule *fuzzyRule33 = new FuzzyRule(33, pH_Normal_Kekeruhan_Rendah_Jarak_Sedang_EC_Tinggi33, Ganti33);
fuzzy->addFuzzyRule(fuzzyRule33);

// Rule 34
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah34 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah34->joinWithAND(pH_Normal, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dalam34 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dalam34->joinWithAND(pH_Normal_Kekeruhan_Rendah34, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dalam_EC_Rendah34 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dalam_EC_Rendah34->joinWithAND(pH_Normal_Kekeruhan_Rendah_Jarak_Dalam34, EC_Rendah);
FuzzyRuleConsequent *Ganti34 = new FuzzyRuleConsequent();
Ganti34->addOutput(Ganti);
FuzzyRule *fuzzyRule34 = new FuzzyRule(34, pH_Normal_Kekeruhan_Rendah_Jarak_Dalam_EC_Rendah34, Ganti34);
fuzzy->addFuzzyRule(fuzzyRule34);

// Rule 35
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah35 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah35->joinWithAND(pH_Normal, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dalam35 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dalam35->joinWithAND(pH_Normal_Kekeruhan_Rendah35, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dalam_EC_Normal35 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dalam_EC_Normal35->joinWithAND(pH_Normal_Kekeruhan_Rendah_Jarak_Dalam35, EC_Normal);
FuzzyRuleConsequent *Ganti35 = new FuzzyRuleConsequent();
Ganti35->addOutput(Ganti);
FuzzyRule *fuzzyRule35 = new FuzzyRule(35, pH_Normal_Kekeruhan_Rendah_Jarak_Dalam_EC_Normal35, Ganti35);
fuzzy->addFuzzyRule(fuzzyRule35);

// Rule 36
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah36 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah36->joinWithAND(pH_Normal, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dalam36 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dalam36->joinWithAND(pH_Normal_Kekeruhan_Rendah36, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Rendah_Jarak_Dalam_EC_Tinggi36 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Rendah_Jarak_Dalam_EC_Tinggi36->joinWithAND(pH_Normal_Kekeruhan_Rendah_Jarak_Dalam36, EC_Tinggi);
FuzzyRuleConsequent *Ganti36 = new FuzzyRuleConsequent();
Ganti36->addOutput(Ganti);
FuzzyRule *fuzzyRule36 = new FuzzyRule(36, pH_Normal_Kekeruhan_Rendah_Jarak_Dalam_EC_Tinggi36, Ganti36);
fuzzy->addFuzzyRule(fuzzyRule36);

// Rule 37
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal37 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal37->joinWithAND(pH_Normal, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dangkal37 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dangkal37->joinWithAND(pH_Normal_Kekeruhan_Normal37, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dangkal_EC_Rendah37 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dangkal_EC_Rendah37->joinWithAND(pH_Normal_Kekeruhan_Normal_Jarak_Dangkal37, EC_Rendah);
FuzzyRuleConsequent *Ganti37 = new FuzzyRuleConsequent();
Ganti37->addOutput(Ganti);
FuzzyRule *fuzzyRule37 = new FuzzyRule(37, pH_Normal_Kekeruhan_Normal_Jarak_Dangkal_EC_Rendah37, Ganti37);
fuzzy->addFuzzyRule(fuzzyRule37);

// Rule 38
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal38 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal38->joinWithAND(pH_Normal, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dangkal38 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dangkal38->joinWithAND(pH_Normal_Kekeruhan_Normal38, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dangkal_EC_Normal38 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dangkal_EC_Normal38->joinWithAND(pH_Normal_Kekeruhan_Normal_Jarak_Dangkal38, EC_Normal);
FuzzyRuleConsequent *Ganti38 = new FuzzyRuleConsequent();
Ganti38->addOutput(Ganti);
FuzzyRule *fuzzyRule38 = new FuzzyRule(38, pH_Normal_Kekeruhan_Normal_Jarak_Dangkal_EC_Normal38, Ganti38);
fuzzy->addFuzzyRule(fuzzyRule38);

// Rule 39
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal39 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal39->joinWithAND(pH_Normal, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dangkal39 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dangkal39->joinWithAND(pH_Normal_Kekeruhan_Normal39, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dangkal_EC_Tinggi39 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dangkal_EC_Tinggi39->joinWithAND(pH_Normal_Kekeruhan_Normal_Jarak_Dangkal39, EC_Tinggi);
FuzzyRuleConsequent *Ganti39 = new FuzzyRuleConsequent();
Ganti39->addOutput(Ganti);
FuzzyRule *fuzzyRule39 = new FuzzyRule(39, pH_Normal_Kekeruhan_Normal_Jarak_Dangkal_EC_Tinggi39, Ganti39);
fuzzy->addFuzzyRule(fuzzyRule39);

// Rule 40
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal40 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal40->joinWithAND(pH_Normal, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Sedang40 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Sedang40->joinWithAND(pH_Normal_Kekeruhan_Normal40, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Sedang_EC_Rendah40 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Sedang_EC_Rendah40->joinWithAND(pH_Normal_Kekeruhan_Normal_Jarak_Sedang40, EC_Rendah);
FuzzyRuleConsequent *Aman40 = new FuzzyRuleConsequent();
Aman40->addOutput(Aman);
FuzzyRule *fuzzyRule40 = new FuzzyRule(40, pH_Normal_Kekeruhan_Normal_Jarak_Sedang_EC_Rendah40, Aman40);
fuzzy->addFuzzyRule(fuzzyRule40);

// Rule 41
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal41 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal41->joinWithAND(pH_Normal, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Sedang41 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Sedang41->joinWithAND(pH_Normal_Kekeruhan_Normal41, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Sedang_EC_Normal41 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Sedang_EC_Normal41->joinWithAND(pH_Normal_Kekeruhan_Normal_Jarak_Sedang41, EC_Normal);
FuzzyRuleConsequent *Aman41 = new FuzzyRuleConsequent();
Aman41->addOutput(Aman);
FuzzyRule *fuzzyRule41 = new FuzzyRule(41, pH_Normal_Kekeruhan_Normal_Jarak_Sedang_EC_Normal41, Aman41);
fuzzy->addFuzzyRule(fuzzyRule41);

// Rule 42
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal42 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal42->joinWithAND(pH_Normal, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Sedang42 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Sedang42->joinWithAND(pH_Normal_Kekeruhan_Normal42, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Sedang_EC_Tinggi42 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Sedang_EC_Tinggi42->joinWithAND(pH_Normal_Kekeruhan_Normal_Jarak_Sedang42, EC_Tinggi);
FuzzyRuleConsequent *Ganti42 = new FuzzyRuleConsequent();
Ganti42->addOutput(Ganti);
FuzzyRule *fuzzyRule42 = new FuzzyRule(42, pH_Normal_Kekeruhan_Normal_Jarak_Sedang_EC_Tinggi42, Ganti42);
fuzzy->addFuzzyRule(fuzzyRule42);

// Rule 43
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal43 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal43->joinWithAND(pH_Normal, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dalam43 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dalam43->joinWithAND(pH_Normal_Kekeruhan_Normal43, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dalam_EC_Rendah43 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dalam_EC_Rendah43->joinWithAND(pH_Normal_Kekeruhan_Normal_Jarak_Dalam43, EC_Rendah);
FuzzyRuleConsequent *Aman43 = new FuzzyRuleConsequent();
Aman43->addOutput(Aman);
FuzzyRule *fuzzyRule43 = new FuzzyRule(43, pH_Normal_Kekeruhan_Normal_Jarak_Dalam_EC_Rendah43, Aman43);
fuzzy->addFuzzyRule(fuzzyRule43);

// Rule 44
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal44 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal44->joinWithAND(pH_Normal, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dalam44 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dalam44->joinWithAND(pH_Normal_Kekeruhan_Normal44, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dalam_EC_Normal44 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dalam_EC_Normal44->joinWithAND(pH_Normal_Kekeruhan_Normal_Jarak_Dalam44, EC_Normal);
FuzzyRuleConsequent *Aman44 = new FuzzyRuleConsequent();
Aman44->addOutput(Aman);
FuzzyRule *fuzzyRule44 = new FuzzyRule(44, pH_Normal_Kekeruhan_Normal_Jarak_Dalam_EC_Normal44, Aman44);
fuzzy->addFuzzyRule(fuzzyRule44);

// Rule 45
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal45 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal45->joinWithAND(pH_Normal, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dalam45 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dalam45->joinWithAND(pH_Normal_Kekeruhan_Normal45, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Normal_Jarak_Dalam_EC_Tinggi45 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Normal_Jarak_Dalam_EC_Tinggi45->joinWithAND(pH_Normal_Kekeruhan_Normal_Jarak_Dalam45, EC_Tinggi);
FuzzyRuleConsequent *Ganti45 = new FuzzyRuleConsequent();
Ganti45->addOutput(Ganti);
FuzzyRule *fuzzyRule45 = new FuzzyRule(45, pH_Normal_Kekeruhan_Normal_Jarak_Dalam_EC_Tinggi45, Ganti45);
fuzzy->addFuzzyRule(fuzzyRule45);

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

// Rule 47
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak47 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak47->joinWithAND(pH_Normal, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal47 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal47->joinWithAND(pH_Normal_Kekeruhan_Banyak47, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal_EC_Normal47 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal_EC_Normal47->joinWithAND(pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal47, EC_Normal);
FuzzyRuleConsequent *Ganti47 = new FuzzyRuleConsequent();
Ganti47->addOutput(Ganti);
FuzzyRule *fuzzyRule47 = new FuzzyRule(47, pH_Normal_Kekeruhan_Banyak_Jarak_Dangkal_EC_Normal47, Ganti47);
fuzzy->addFuzzyRule(fuzzyRule47);

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

// Rule 49
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak49 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak49->joinWithAND(pH_Normal, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Sedang49 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Sedang49->joinWithAND(pH_Normal_Kekeruhan_Banyak49, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Sedang_EC_Rendah49 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Sedang_EC_Rendah49->joinWithAND(pH_Normal_Kekeruhan_Banyak_Jarak_Sedang49, EC_Rendah);
FuzzyRuleConsequent *Ganti49 = new FuzzyRuleConsequent();
Ganti49->addOutput(Ganti);
FuzzyRule *fuzzyRule49 = new FuzzyRule(49, pH_Normal_Kekeruhan_Banyak_Jarak_Sedang_EC_Rendah49, Ganti49);
fuzzy->addFuzzyRule(fuzzyRule49);

// Rule 50
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak50 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak50->joinWithAND(pH_Normal, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Sedang50 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Sedang50->joinWithAND(pH_Normal_Kekeruhan_Banyak50, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Sedang_EC_Normal50 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Sedang_EC_Normal50->joinWithAND(pH_Normal_Kekeruhan_Banyak_Jarak_Sedang50, EC_Normal);
FuzzyRuleConsequent *Ganti50 = new FuzzyRuleConsequent();
Ganti50->addOutput(Ganti);
FuzzyRule *fuzzyRule50 = new FuzzyRule(50, pH_Normal_Kekeruhan_Banyak_Jarak_Sedang_EC_Normal50, Ganti50);
fuzzy->addFuzzyRule(fuzzyRule50);

// Rule 51
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak51 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak51->joinWithAND(pH_Normal, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Sedang51 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Sedang51->joinWithAND(pH_Normal_Kekeruhan_Banyak51, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Sedang_EC_Tinggi51 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Sedang_EC_Tinggi51->joinWithAND(pH_Normal_Kekeruhan_Banyak_Jarak_Sedang51, EC_Tinggi);
FuzzyRuleConsequent *Ganti51 = new FuzzyRuleConsequent();
Ganti51->addOutput(Ganti);
FuzzyRule *fuzzyRule51 = new FuzzyRule(51, pH_Normal_Kekeruhan_Banyak_Jarak_Sedang_EC_Tinggi51, Ganti51);
fuzzy->addFuzzyRule(fuzzyRule51);

// Rule 52
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak52 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak52->joinWithAND(pH_Normal, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dalam52 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dalam52->joinWithAND(pH_Normal_Kekeruhan_Banyak52, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dalam_EC_Rendah52 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dalam_EC_Rendah52->joinWithAND(pH_Normal_Kekeruhan_Banyak_Jarak_Dalam52, EC_Rendah);
FuzzyRuleConsequent *Ganti52 = new FuzzyRuleConsequent();
Ganti52->addOutput(Ganti);
FuzzyRule *fuzzyRule52 = new FuzzyRule(52, pH_Normal_Kekeruhan_Banyak_Jarak_Dalam_EC_Rendah52, Ganti52);
fuzzy->addFuzzyRule(fuzzyRule52);

// Rule 53
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak53 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak53->joinWithAND(pH_Normal, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dalam53 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dalam53->joinWithAND(pH_Normal_Kekeruhan_Banyak53, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dalam_EC_Normal53 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dalam_EC_Normal53->joinWithAND(pH_Normal_Kekeruhan_Banyak_Jarak_Dalam53, EC_Normal);
FuzzyRuleConsequent *Ganti53 = new FuzzyRuleConsequent();
Ganti53->addOutput(Ganti);
FuzzyRule *fuzzyRule53 = new FuzzyRule(53, pH_Normal_Kekeruhan_Banyak_Jarak_Dalam_EC_Normal53, Ganti53);
fuzzy->addFuzzyRule(fuzzyRule53);

// Rule 54
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak54 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak54->joinWithAND(pH_Normal, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dalam54 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dalam54->joinWithAND(pH_Normal_Kekeruhan_Banyak54, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Normal_Kekeruhan_Banyak_Jarak_Dalam_EC_Tinggi54 = new FuzzyRuleAntecedent();
pH_Normal_Kekeruhan_Banyak_Jarak_Dalam_EC_Tinggi54->joinWithAND(pH_Normal_Kekeruhan_Banyak_Jarak_Dalam54, EC_Tinggi);
FuzzyRuleConsequent *Ganti54 = new FuzzyRuleConsequent();
Ganti54->addOutput(Ganti);
FuzzyRule *fuzzyRule54 = new FuzzyRule(54, pH_Normal_Kekeruhan_Banyak_Jarak_Dalam_EC_Tinggi54, Ganti54);
fuzzy->addFuzzyRule(fuzzyRule54);

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

// Rule 56
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah56 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah56->joinWithAND(pH_Banyak, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal56 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal56->joinWithAND(pH_Banyak_Kekeruhan_Rendah56, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal_EC_Normal56 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal_EC_Normal56->joinWithAND(pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal56, EC_Normal);
FuzzyRuleConsequent *Ganti56 = new FuzzyRuleConsequent();
Ganti56->addOutput(Ganti);
FuzzyRule *fuzzyRule56 = new FuzzyRule(56, pH_Banyak_Kekeruhan_Rendah_Jarak_Dangkal_EC_Normal56, Ganti56);
fuzzy->addFuzzyRule(fuzzyRule56);

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

// Rule 58
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah58 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah58->joinWithAND(pH_Banyak, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang58 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang58->joinWithAND(pH_Banyak_Kekeruhan_Rendah58, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang_EC_Rendah58 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang_EC_Rendah58->joinWithAND(pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang58, EC_Rendah);
FuzzyRuleConsequent *Ganti58 = new FuzzyRuleConsequent();
Ganti58->addOutput(Ganti);
FuzzyRule *fuzzyRule58 = new FuzzyRule(58, pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang_EC_Rendah58, Ganti58);
fuzzy->addFuzzyRule(fuzzyRule58);

// Rule 59
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah59 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah59->joinWithAND(pH_Banyak, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang59 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang59->joinWithAND(pH_Banyak_Kekeruhan_Rendah59, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang_EC_Normal59 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang_EC_Normal59->joinWithAND(pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang59, EC_Normal);
FuzzyRuleConsequent *Ganti59 = new FuzzyRuleConsequent();
Ganti59->addOutput(Ganti);
FuzzyRule *fuzzyRule59 = new FuzzyRule(59, pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang_EC_Normal59, Ganti59);
fuzzy->addFuzzyRule(fuzzyRule59);

// Rule 60
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah60 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah60->joinWithAND(pH_Banyak, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang60 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang60->joinWithAND(pH_Banyak_Kekeruhan_Rendah60, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang_EC_Tinggi60 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang_EC_Tinggi60->joinWithAND(pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang60, EC_Tinggi);
FuzzyRuleConsequent *Ganti60 = new FuzzyRuleConsequent();
Ganti60->addOutput(Ganti);
FuzzyRule *fuzzyRule60 = new FuzzyRule(60, pH_Banyak_Kekeruhan_Rendah_Jarak_Sedang_EC_Tinggi60, Ganti60);
fuzzy->addFuzzyRule(fuzzyRule60);

// Rule 61
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah61 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah61->joinWithAND(pH_Banyak, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam61 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam61->joinWithAND(pH_Banyak_Kekeruhan_Rendah61, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam_EC_Rendah61 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam_EC_Rendah61->joinWithAND(pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam61, EC_Rendah);
FuzzyRuleConsequent *Ganti61 = new FuzzyRuleConsequent();
Ganti61->addOutput(Ganti);
FuzzyRule *fuzzyRule61 = new FuzzyRule(61, pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam_EC_Rendah61, Ganti61);
fuzzy->addFuzzyRule(fuzzyRule61);

// Rule 62
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah62 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah62->joinWithAND(pH_Banyak, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam62 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam62->joinWithAND(pH_Banyak_Kekeruhan_Rendah62, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam_EC_Normal62 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam_EC_Normal62->joinWithAND(pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam62, EC_Normal);
FuzzyRuleConsequent *Ganti62 = new FuzzyRuleConsequent();
Ganti62->addOutput(Ganti);
FuzzyRule *fuzzyRule62 = new FuzzyRule(62, pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam_EC_Normal62, Ganti62);
fuzzy->addFuzzyRule(fuzzyRule62);

// Rule 63
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah63 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah63->joinWithAND(pH_Banyak, Kekeruhan_Rendah);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam63 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam63->joinWithAND(pH_Banyak_Kekeruhan_Rendah63, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam_EC_Tinggi63 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam_EC_Tinggi63->joinWithAND(pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam63, EC_Tinggi);
FuzzyRuleConsequent *Ganti63 = new FuzzyRuleConsequent();
Ganti63->addOutput(Ganti);
FuzzyRule *fuzzyRule63 = new FuzzyRule(63, pH_Banyak_Kekeruhan_Rendah_Jarak_Dalam_EC_Tinggi63, Ganti63);
fuzzy->addFuzzyRule(fuzzyRule63);

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

// Rule 65
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal65 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal65->joinWithAND(pH_Banyak, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal65 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal65->joinWithAND(pH_Banyak_Kekeruhan_Normal65, Jarak_Dangkal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal_EC_Normal65 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal_EC_Normal65->joinWithAND(pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal65, EC_Normal);
FuzzyRuleConsequent *Ganti65 = new FuzzyRuleConsequent();
Ganti65->addOutput(Ganti);
FuzzyRule *fuzzyRule65 = new FuzzyRule(65, pH_Banyak_Kekeruhan_Normal_Jarak_Dangkal_EC_Normal65, Ganti65);
fuzzy->addFuzzyRule(fuzzyRule65);

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

// Rule 67
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal67 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal67->joinWithAND(pH_Banyak, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Sedang67 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Sedang67->joinWithAND(pH_Banyak_Kekeruhan_Normal67, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Sedang_EC_Rendah67 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Sedang_EC_Rendah67->joinWithAND(pH_Banyak_Kekeruhan_Normal_Jarak_Sedang67, EC_Rendah);
FuzzyRuleConsequent *Ganti67 = new FuzzyRuleConsequent();
Ganti67->addOutput(Ganti);
FuzzyRule *fuzzyRule67 = new FuzzyRule(67, pH_Banyak_Kekeruhan_Normal_Jarak_Sedang_EC_Rendah67, Ganti67);
fuzzy->addFuzzyRule(fuzzyRule67);

// Rule 68
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal68 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal68->joinWithAND(pH_Banyak, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Sedang68 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Sedang68->joinWithAND(pH_Banyak_Kekeruhan_Normal68, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Sedang_EC_Normal68 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Sedang_EC_Normal68->joinWithAND(pH_Banyak_Kekeruhan_Normal_Jarak_Sedang68, EC_Normal);
FuzzyRuleConsequent *Ganti68 = new FuzzyRuleConsequent();
Ganti68->addOutput(Ganti);
FuzzyRule *fuzzyRule68 = new FuzzyRule(68, pH_Banyak_Kekeruhan_Normal_Jarak_Sedang_EC_Normal68, Ganti68);
fuzzy->addFuzzyRule(fuzzyRule68);

// Rule 69
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal69 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal69->joinWithAND(pH_Banyak, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Sedang69 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Sedang69->joinWithAND(pH_Banyak_Kekeruhan_Normal69, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Sedang_EC_Tinggi69 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Sedang_EC_Tinggi69->joinWithAND(pH_Banyak_Kekeruhan_Normal_Jarak_Sedang69, EC_Tinggi);
FuzzyRuleConsequent *Ganti69 = new FuzzyRuleConsequent();
Ganti69->addOutput(Ganti);
FuzzyRule *fuzzyRule69 = new FuzzyRule(69, pH_Banyak_Kekeruhan_Normal_Jarak_Sedang_EC_Tinggi69, Ganti69);
fuzzy->addFuzzyRule(fuzzyRule69);

// Rule 70
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal70 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal70->joinWithAND(pH_Banyak, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dalam70 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dalam70->joinWithAND(pH_Banyak_Kekeruhan_Normal70, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dalam_EC_Rendah70 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dalam_EC_Rendah70->joinWithAND(pH_Banyak_Kekeruhan_Normal_Jarak_Dalam70, EC_Rendah);
FuzzyRuleConsequent *Ganti70 = new FuzzyRuleConsequent();
Ganti70->addOutput(Ganti);
FuzzyRule *fuzzyRule70 = new FuzzyRule(70, pH_Banyak_Kekeruhan_Normal_Jarak_Dalam_EC_Rendah70, Ganti70);
fuzzy->addFuzzyRule(fuzzyRule70);

// Rule 71
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal71 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal71->joinWithAND(pH_Banyak, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dalam71 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dalam71->joinWithAND(pH_Banyak_Kekeruhan_Normal71, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dalam_EC_Normal71 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dalam_EC_Normal71->joinWithAND(pH_Banyak_Kekeruhan_Normal_Jarak_Dalam71, EC_Normal);
FuzzyRuleConsequent *Ganti71 = new FuzzyRuleConsequent();
Ganti71->addOutput(Ganti);
FuzzyRule *fuzzyRule71 = new FuzzyRule(71, pH_Banyak_Kekeruhan_Normal_Jarak_Dalam_EC_Normal71, Ganti71);
fuzzy->addFuzzyRule(fuzzyRule71);

// Rule 72
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal72 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal72->joinWithAND(pH_Banyak, Kekeruhan_Normal);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dalam72 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dalam72->joinWithAND(pH_Banyak_Kekeruhan_Normal72, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Normal_Jarak_Dalam_EC_Tinggi72 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Normal_Jarak_Dalam_EC_Tinggi72->joinWithAND(pH_Banyak_Kekeruhan_Normal_Jarak_Dalam72, EC_Tinggi);
FuzzyRuleConsequent *Ganti72 = new FuzzyRuleConsequent();
Ganti72->addOutput(Ganti);
FuzzyRule *fuzzyRule72 = new FuzzyRule(72, pH_Banyak_Kekeruhan_Normal_Jarak_Dalam_EC_Tinggi72, Ganti72);
fuzzy->addFuzzyRule(fuzzyRule72);

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

// Rule 77
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak77 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak77->joinWithAND(pH_Banyak, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang77 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang77->joinWithAND(pH_Banyak_Kekeruhan_Banyak77, Jarak_Sedang);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang_EC_Normal77 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang_EC_Normal77->joinWithAND(pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang77, EC_Normal);
FuzzyRuleConsequent *Ganti77 = new FuzzyRuleConsequent();
Ganti77->addOutput(Ganti);
FuzzyRule *fuzzyRule77 = new FuzzyRule(77, pH_Banyak_Kekeruhan_Banyak_Jarak_Sedang_EC_Normal77, Ganti77);
fuzzy->addFuzzyRule(fuzzyRule77);

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

// Rule 80
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak80 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak80->joinWithAND(pH_Banyak, Kekeruhan_Banyak);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam80 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam80->joinWithAND(pH_Banyak_Kekeruhan_Banyak80, Jarak_Dalam);
FuzzyRuleAntecedent *pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam_EC_Normal80 = new FuzzyRuleAntecedent();
pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam_EC_Normal80->joinWithAND(pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam80, EC_Normal);
FuzzyRuleConsequent *Ganti80 = new FuzzyRuleConsequent();
Ganti80->addOutput(Ganti);
FuzzyRule *fuzzyRule80 = new FuzzyRule(80, pH_Banyak_Kekeruhan_Banyak_Jarak_Dalam_EC_Normal80, Ganti80);
fuzzy->addFuzzyRule(fuzzyRule80);

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