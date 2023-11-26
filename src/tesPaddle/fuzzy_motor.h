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
  FuzzyOutput *motor = new FuzzyOutput(1);

  FuzzySet *kurang = new FuzzySet(0, 0, 3, 5);
  SensorDO->addFuzzySet(kurang);
  FuzzySet *sedang = new FuzzySet(4, 6, 7, 9);
  SensorDO->addFuzzySet(sedang);
  FuzzySet *banyak = new FuzzySet(8, 9, 10, 10);
  SensorDO->addFuzzySet(banyak);

  FuzzySet *on = new FuzzySet(0, 0, 0, 0);
  motor->addFuzzySet(on);
  FuzzySet *off = new FuzzySet(1, 1, 1, 1);
  motor->addFuzzySet(off);

  myfuzzy->addFuzzyInput(SensorDO);
  myfuzzy->addFuzzyOutput(motor);

  FuzzyRuleAntecedent *ifSensorKurang1 = new FuzzyRuleAntecedent();
  ifSensorKurang1->joinSingle(kurang);
  FuzzyRuleConsequent *thenMotorOn1 = new FuzzyRuleConsequent();
  thenMotorOn1->addOutput(on);
  FuzzyRule *FuzzyRule1 = new FuzzyRule(1, ifSensorKurang1, thenMotorOn1);
  myfuzzy->addFuzzyRule(FuzzyRule1);

  FuzzyRuleAntecedent *ifSensorSedang2 = new FuzzyRuleAntecedent();
  ifSensorSedang2->joinSingle(sedang);
  FuzzyRuleConsequent *thenMotorOff2 = new FuzzyRuleConsequent();
  thenMotorOff2->addOutput(off);
  FuzzyRule *FuzzyRule2 = new FuzzyRule(2, ifSensorSedang2, thenMotorOff2);
  myfuzzy->addFuzzyRule(FuzzyRule2);

  FuzzyRuleAntecedent *ifSensorBanyak3 = new FuzzyRuleAntecedent();
  ifSensorBanyak3->joinSingle(banyak);
  FuzzyRuleConsequent *thenMotorOff3 = new FuzzyRuleConsequent();
  thenMotorOff3->addOutput(off);
  FuzzyRule *FuzzyRule3 = new FuzzyRule(3, ifSensorBanyak3, thenMotorOff3);
  myfuzzy->addFuzzyRule(FuzzyRule3);  
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