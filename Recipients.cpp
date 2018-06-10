#include "stdafx.h"
#include "Recipients.h"
#include "DEBUG.h"
#include <iostream>
using namespace std;

Recipients::Recipients(int a) :A(a) {
  if (DEBUG) cout << "Made recipients who need: " << A << "units of blood" << endl;
}
