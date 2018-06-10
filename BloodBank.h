#pragma once

#include "stdafx.h"
#include  "UnitOfBlood.h"
#include <list>
#include <queue>
#include "Recipients.h"
#include "Distribution.h"

class Calendar;

class BloodBank { //klasa Bank krwi
public:
  int J;  //ilo�� aktualnych jednostek krwi
  bool EO;  //flaga blokowania zam�wie� awartujnych
  bool NO;  //flaga blokowania zam�wie� normalnych
  int get_R() const;


//Dane do statystyk oraz warunk�w ko�ca
  int number_of_blood_spent;
  int number_of_recipients_served;
  int length_of_longest_recipient_queue;


//funkcje odpowiedzialne za kolejk� z krwi�
  void ReadList() ;
  bool DeleteIdUnitsOfBlood(int id);  //usuwanie jednistki krwi o danym ID z banku krwi
  void AddingBloodUnits(int t0);
  bool deleteFirstUnitsOfBlood();
  int get_id_FirstUnitOfBlood() const;
  int get_size_blood_in_bank() const;
  int get_handled_recipients()const;
  int queue_recipients_size()const;
  void inc_handled_recipients();
  Calendar* calendar_;
  

//funkcje odpowiedzialne za obs�ug� kolejki z biorcami
  void GettingToQueue(Recipients* recipients);
  void ReadQueue();
  void DeleteFirstQueue();
//funkcje odpowiedzialne za zbieranie statystyk
  void inc_s_e();
  void inc_s_c();
  void inc_s_u();
  int get_s_e();
  int get_s_c();
  int get_s_u();

  Recipients* get_first_recipient() const;
//funkcje odpowiedzialne za generacje liczb 
  Distribution* get_generate() const;
//
  BloodBank(int r, int j, int z, int kernel);
  ~BloodBank();
private:
  Distribution * generate_;
  int s_e_;
  int s_c_;
  int s_u_;
  int Z_;  //Minimalna liczba jednostek krwi
  int pool_ID;  //pocz�tek adres�w ID
  int R_;  //poziom krwi od kt�rego wysy�amy zam�wienie na dostaw�
  int handled_recipients_;
  std::list<UnitOfBlood> queue_blood;  //lista wska�nik�w na jednostki krwi
  std::queue<Recipients*> queue_of_recipients_;
  void AddBloodUnitsSort(UnitOfBlood unit_of_blood);
};
