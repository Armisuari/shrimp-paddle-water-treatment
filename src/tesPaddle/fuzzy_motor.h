#pragma once
#include "Fuzzy.h"

Fuzzy *myfuzzy = new Fuzzy();

typedef struct
{
  void begin();
  bool setinput(int index, float input);
  bool fuzify();
  int output();
} FuzzyHandler;

void FuzzyHandler::begin()
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

  FuzzySet *on = new FuzzySet(0, 0, 0, 0);
  motor->addFuzzySet(on);
  FuzzySet *off = new FuzzySet(1, 1, 1, 1);
  motor->addFuzzySet(off);

  myfuzzy->addFuzzyInput(SensorDO);
  myfuzzy->addFuzzyInput(SensorpH);
  myfuzzy->addFuzzyOutput(motor);

  //Rule 1
  FuzzyRuleAntecedent *DO_Rendah_pH_Rendah1 = new FuzzyRuleAntecedent();
  DO_Rendah_pH_Rendah1->joinWithAND(DO_kurang, pH_kurang);
  FuzzyRuleConsequent *On1 = new FuzzyRuleConsequent();
  On1->addOutput(on);
  FuzzyRule *fuzzyRule1 = new FuzzyRule(1,DO_Rendah_pH_Rendah1, On1);
  myfuzzy->addFuzzyRule(fuzzyRule1);

  //Rule 2
  FuzzyRuleAntecedent *DO_Rendah_pH_Sedang2 = new FuzzyRuleAntecedent();
  DO_Rendah_pH_Sedang2->joinWithAND(DO_kurang, pH_sedang);
  FuzzyRuleConsequent *On2 = new FuzzyRuleConsequent();
  On2->addOutput(on);
  FuzzyRule *fuzzyRule2 = new FuzzyRule(2,DO_Rendah_pH_Sedang2, On2);
  myfuzzy->addFuzzyRule(fuzzyRule2);

  //Rule 3
  FuzzyRuleAntecedent *DO_Rendah_pH_Banyak3 = new FuzzyRuleAntecedent();
  DO_Rendah_pH_Banyak3->joinWithAND(DO_kurang, pH_banyak);
  FuzzyRuleConsequent *On3 = new FuzzyRuleConsequent();
  On3->addOutput(on);
  FuzzyRule *fuzzyRule3 = new FuzzyRule(3,DO_Rendah_pH_Banyak3, On3);
  myfuzzy->addFuzzyRule(fuzzyRule3);

  //Rule 4
  FuzzyRuleAntecedent *DO_Sedand_pH_Kurang4 = new FuzzyRuleAntecedent();
  DO_Sedand_pH_Kurang4->joinWithAND(DO_sedang, pH_kurang);
  FuzzyRuleConsequent *On4 = new FuzzyRuleConsequent();
  On4->addOutput(on);
  FuzzyRule *fuzzyRule4 = new FuzzyRule(4,DO_Sedand_pH_Kurang4, On4);
  myfuzzy->addFuzzyRule(fuzzyRule4);

  //Rule 5
  FuzzyRuleAntecedent *DO_Sedand_pH_Sedang5 = new FuzzyRuleAntecedent();
  DO_Sedand_pH_Sedang5->joinWithAND(DO_sedang, pH_sedang);
  FuzzyRuleConsequent *On5 = new FuzzyRuleConsequent();
  On5->addOutput(on);
  FuzzyRule *fuzzyRule5 = new FuzzyRule(5,DO_Sedand_pH_Sedang5, On5);
  myfuzzy->addFuzzyRule(fuzzyRule5);

  //Rule 6
  FuzzyRuleAntecedent *DO_Sedand_pH_Banyak6 = new FuzzyRuleAntecedent();
  DO_Sedand_pH_Banyak6->joinWithAND(DO_sedang, pH_banyak);
  FuzzyRuleConsequent *On6 = new FuzzyRuleConsequent();
  On6->addOutput(on);
  FuzzyRule *fuzzyRule6 = new FuzzyRule(6,DO_Sedand_pH_Banyak6, On6);
  myfuzzy->addFuzzyRule(fuzzyRule6);

  //Rule 7
  FuzzyRuleAntecedent *DO_Banyak_pH_Kurang7 = new FuzzyRuleAntecedent();
  DO_Banyak_pH_Kurang7->joinWithAND(DO_banyak, pH_kurang);
  FuzzyRuleConsequent *On7 = new FuzzyRuleConsequent();
  On7->addOutput(on);
  FuzzyRule *fuzzyRule7 = new FuzzyRule(7,DO_Banyak_pH_Kurang7, On7);
  myfuzzy->addFuzzyRule(fuzzyRule7);

  //Rule 8
  FuzzyRuleAntecedent *DO_Banyak_pH_Sedang8 = new FuzzyRuleAntecedent();
  DO_Banyak_pH_Sedang8->joinWithAND(DO_banyak, pH_sedang);
  FuzzyRuleConsequent *On8 = new FuzzyRuleConsequent();
  On8->addOutput(on);
  FuzzyRule *fuzzyRule8 = new FuzzyRule(8,DO_Banyak_pH_Sedang8, On8);
  myfuzzy->addFuzzyRule(fuzzyRule8);

  //Rule 9
  FuzzyRuleAntecedent *DO_Banyak_pH_Banyak9 = new FuzzyRuleAntecedent();
  DO_Banyak_pH_Banyak9->joinWithAND(DO_banyak, pH_banyak);
  FuzzyRuleConsequent *Off9 = new FuzzyRuleConsequent();
  Off9->addOutput(off);
  FuzzyRule *fuzzyRule9 = new FuzzyRule(9,DO_Banyak_pH_Banyak9, Off9);
  myfuzzy->addFuzzyRule(fuzzyRule9);  
}

bool FuzzyHandler::setinput(int index, float input)
{
  // Mengatur input untuk fuzzy dengan indeks yang ditentukan
  return myfuzzy->setInput(index, input);
}

bool FuzzyHandler::fuzify()
{
  // Memulai proses fuzzifikasi
  return myfuzzy->fuzzify();
}

int FuzzyHandler::output()
{
  // Mendapatkan nilai keluaran fuzzy
  return myfuzzy->defuzzify(1);
}