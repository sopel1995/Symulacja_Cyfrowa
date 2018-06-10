#pragma once

class UnitOfBlood {
public:
  int ID;
  int T0; //czas na zu¿ycie jednostki krwi
  UnitOfBlood(int id, int t0);   //konstruktor
  ~UnitOfBlood()=default;
};
