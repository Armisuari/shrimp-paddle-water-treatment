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
  FuzzyOutput *motor = new FuzzyOutput(1);

  FuzzySet *kurang = new FuzzySet(0, 0, 2, 4);
  SensorDO->addFuzzySet(kurang);
  FuzzySet *sedang = new FuzzySet(3, 5, 7, 8);
  SensorDO->addFuzzySet(sedang);
  FuzzySet *banyak = new FuzzySet(7, 9, 10, 10);
  SensorDO->addFuzzySet(banyak);

  FuzzySet *mati = new FuzzySet(0, 0, 20, 30);
  motor->addFuzzySet(mati);
  FuzzySet *pelan = new FuzzySet(20, 30, 40, 50);
  motor->addFuzzySet(pelan);
  FuzzySet *Msedang = new FuzzySet(40, 50, 70, 80);
  motor->addFuzzySet(Msedang);
  FuzzySet *cepat = new FuzzySet(70, 80, 100, 100);
  motor->addFuzzySet(cepat);

  fuzzy->addFuzzyInput(SensorDO);
  fuzzy->addFuzzyOutput(motor);

  FuzzyRuleAntecedent *ifSensorKurang1 = new FuzzyRuleAntecedent();
  ifSensorKurang1->joinSingle(kurang);
  FuzzyRuleConsequent *thenMotorCepat1 = new FuzzyRuleConsequent();
  thenMotorCepat1->addOutput(cepat);
  FuzzyRule *FuzzyRule1 = new FuzzyRule(1, ifSensorKurang1, thenMotorCepat1);
  fuzzy->addFuzzyRule(FuzzyRule1);

  FuzzyRuleAntecedent *ifSensorSedang2 = new FuzzyRuleAntecedent();
  ifSensorSedang2->joinSingle(sedang);
  FuzzyRuleConsequent *thenMotorSedang2 = new FuzzyRuleConsequent();
  thenMotorSedang2->addOutput(Msedang);
  FuzzyRule *FuzzyRule2 = new FuzzyRule(2, ifSensorSedang2, thenMotorSedang2);
  fuzzy->addFuzzyRule(FuzzyRule2);

  FuzzyRuleAntecedent *ifSensorSedang3 = new FuzzyRuleAntecedent();
  ifSensorSedang3->joinSingle(sedang);
  FuzzyRuleConsequent *thenMotorPelan3 = new FuzzyRuleConsequent();
  thenMotorPelan3->addOutput(pelan);
  FuzzyRule *FuzzyRule3 = new FuzzyRule(3, ifSensorSedang3, thenMotorPelan3);
  fuzzy->addFuzzyRule(FuzzyRule3);

  FuzzyRuleAntecedent *ifSensorBanyak4 = new FuzzyRuleAntecedent();
  ifSensorBanyak4->joinSingle(banyak);
  FuzzyRuleConsequent *thenMotorMati4 = new FuzzyRuleConsequent();
  thenMotorMati4->addOutput(mati);
  FuzzyRule *FuzzyRule4 = new FuzzyRule(4, ifSensorBanyak4, thenMotorMati4);
  fuzzy->addFuzzyRule(FuzzyRule4);
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