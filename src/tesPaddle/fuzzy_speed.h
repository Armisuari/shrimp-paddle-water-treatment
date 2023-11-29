#include <Arduino.h>
#pragma once
#include "Fuzzy.h"

Fuzzy *fuzzy = new Fuzzy();

typedef struct
{
  void begin();
  bool setinput(int index, float input);
  bool fuzify();
  int output();
} FuzzyHandlerS;

void FuzzyHandlerS::begin()
{
  FuzzyInput *SensorDO = new FuzzyInput(1);
  FuzzyInput *SensorpH = new FuzzyInput(2);
  FuzzyOutput *motor = new FuzzyOutput(1);

  FuzzySet *DO_kurang = new FuzzySet(0, 0, 2, 4);
  SensorDO->addFuzzySet(DO_kurang);
  FuzzySet *DO_sedang = new FuzzySet(3, 5, 7, 8);
  SensorDO->addFuzzySet(DO_sedang);
  FuzzySet *DO_banyak = new FuzzySet(7, 9, 10, 10);
  SensorDO->addFuzzySet(DO_banyak);

  FuzzySet *pH_kurang = new FuzzySet(0, 0, 4, 5);
  SensorpH->addFuzzySet(pH_kurang);
  FuzzySet *pH_sedang = new FuzzySet(4, 5, 7, 8);
  SensorpH->addFuzzySet(pH_sedang);
  FuzzySet *pH_banyak = new FuzzySet(7, 8, 12, 12);
  SensorpH->addFuzzySet(pH_banyak);

  FuzzySet *mati = new FuzzySet(0, 0, 20, 30);
  motor->addFuzzySet(mati);
  FuzzySet *pelan = new FuzzySet(20, 30, 40, 50);
  motor->addFuzzySet(pelan);
  FuzzySet *Msedang = new FuzzySet(40, 50, 70, 80);
  motor->addFuzzySet(Msedang);
  FuzzySet *cepat = new FuzzySet(70, 80, 100, 100);
  motor->addFuzzySet(cepat);

  fuzzy->addFuzzyInput(SensorDO);
  fuzzy->addFuzzyInput(SensorpH);
  fuzzy->addFuzzyOutput(motor);

  //Rule 1
  FuzzyRuleAntecedent *DO_Rendah_pH_Rendah1 = new FuzzyRuleAntecedent();
  DO_Rendah_pH_Rendah1->joinWithAND(DO_kurang, pH_kurang);
  FuzzyRuleConsequent *Cepat1 = new FuzzyRuleConsequent();
  Cepat1->addOutput(cepat);
  FuzzyRule *fuzzyRule1 = new FuzzyRule(1,DO_Rendah_pH_Rendah1, Cepat1);
  fuzzy->addFuzzyRule(fuzzyRule1);

  //Rule 2
  FuzzyRuleAntecedent *DO_Rendah_pH_Sedang2 = new FuzzyRuleAntecedent();
  DO_Rendah_pH_Sedang2->joinWithAND(DO_kurang, pH_sedang);
  FuzzyRuleConsequent *Cepat2 = new FuzzyRuleConsequent();
  Cepat2->addOutput(cepat);
  FuzzyRule *fuzzyRule2 = new FuzzyRule(2,DO_Rendah_pH_Sedang2, Cepat2);
  fuzzy->addFuzzyRule(fuzzyRule2);

  //Rule 3
  FuzzyRuleAntecedent *DO_Rendah_pH_Banyak3 = new FuzzyRuleAntecedent();
  DO_Rendah_pH_Banyak3->joinWithAND(DO_kurang, pH_banyak);
  FuzzyRuleConsequent *MSedang3 = new FuzzyRuleConsequent();
  MSedang3->addOutput(Msedang);
  FuzzyRule *fuzzyRule3 = new FuzzyRule(3,DO_Rendah_pH_Banyak3, MSedang3);
  fuzzy->addFuzzyRule(fuzzyRule3);

  //Rule 4
  FuzzyRuleAntecedent *DO_Sedand_pH_Kurang4 = new FuzzyRuleAntecedent();
  DO_Sedand_pH_Kurang4->joinWithAND(DO_sedang, pH_kurang);
  FuzzyRuleConsequent *MSedang4 = new FuzzyRuleConsequent();
  MSedang4->addOutput(Msedang);
  FuzzyRule *fuzzyRule4 = new FuzzyRule(4,DO_Sedand_pH_Kurang4, MSedang4);
  fuzzy->addFuzzyRule(fuzzyRule4);

  //Rule 5
  FuzzyRuleAntecedent *DO_Sedand_pH_Sedang5 = new FuzzyRuleAntecedent();
  DO_Sedand_pH_Sedang5->joinWithAND(DO_sedang, pH_sedang);
  FuzzyRuleConsequent *MSedang5 = new FuzzyRuleConsequent();
  MSedang5->addOutput(Msedang);
  FuzzyRule *fuzzyRule5 = new FuzzyRule(5,DO_Sedand_pH_Sedang5, MSedang5);
  fuzzy->addFuzzyRule(fuzzyRule5);

  //Rule 6
  FuzzyRuleAntecedent *DO_Sedand_pH_Banyak6 = new FuzzyRuleAntecedent();
  DO_Sedand_pH_Banyak6->joinWithAND(DO_sedang, pH_banyak);
  FuzzyRuleConsequent *Pelan6 = new FuzzyRuleConsequent();
  Pelan6->addOutput(pelan);
  FuzzyRule *fuzzyRule6 = new FuzzyRule(6,DO_Sedand_pH_Banyak6, Pelan6);
  fuzzy->addFuzzyRule(fuzzyRule6);

  //Rule 7
  FuzzyRuleAntecedent *DO_Banyak_pH_Kurang7 = new FuzzyRuleAntecedent();
  DO_Banyak_pH_Kurang7->joinWithAND(DO_banyak, pH_kurang);
  FuzzyRuleConsequent *Msedang7 = new FuzzyRuleConsequent();
  Msedang7->addOutput(Msedang);
  FuzzyRule *fuzzyRule7 = new FuzzyRule(7,DO_Banyak_pH_Kurang7, Msedang7);
  fuzzy->addFuzzyRule(fuzzyRule7);

  //Rule 8
  FuzzyRuleAntecedent *DO_Banyak_pH_Sedang8 = new FuzzyRuleAntecedent();
  DO_Banyak_pH_Sedang8->joinWithAND(DO_banyak, pH_sedang);
  FuzzyRuleConsequent *Pelan8 = new FuzzyRuleConsequent();
  Pelan8->addOutput(pelan);
  FuzzyRule *fuzzyRule8 = new FuzzyRule(8,DO_Banyak_pH_Sedang8, Pelan8);
  fuzzy->addFuzzyRule(fuzzyRule8);

  //Rule 9
  FuzzyRuleAntecedent *DO_Banyak_pH_Banyak9 = new FuzzyRuleAntecedent();
  DO_Banyak_pH_Banyak9->joinWithAND(DO_banyak, pH_banyak);
  FuzzyRuleConsequent *mati9 = new FuzzyRuleConsequent();
  mati9->addOutput(mati);
  FuzzyRule *fuzzyRule9 = new FuzzyRule(9,DO_Banyak_pH_Banyak9, mati9);
  fuzzy->addFuzzyRule(fuzzyRule9);

}

bool FuzzyHandlerS::setinput(int index, float input)
{
  // Mengatur input untuk fuzzy dengan indeks yang ditentukan
  return fuzzy->setInput(index, input);
}

bool FuzzyHandlerS::fuzify()
{
  // Memulai proses fuzzifikasi
  return fuzzy->fuzzify();
}

int FuzzyHandlerS::output()
{
  // Mendapatkan nilai keluaran fuzzy
  return fuzzy->defuzzify(1);
}