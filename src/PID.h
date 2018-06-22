#ifndef PID_H
#define PID_H
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

class PID {
public:
  /*
  * Errors
  */

  /*
  * Coefficients
  */
  double Kp;
  double Ki;
  double Kd;

  double int_cte;
  double prev_cte;
  double diff_cte;
  double cur_cte;
  bool check1;//checks if previous cte has been initialized or not
  long counter;
  double err;
  double best_err;
  vector<double> p;
  vector<double> dp;
  long curr1;
  long curr2;
  double prev_steer;
  /*
  * Constructor
  */
  PID();

  /*
  * Destructor.
  */
  virtual ~PID();

  /*
  * Initialize PID.
  */
  void Init(double Kp, double Ki, double Kd);

  /*
  * Update the PID error variables given cross track error.
  */
  void UpdateError(double cte);

  /*
  * Calculate the total PID error.
  */
  double TotalError();
};

#endif /* PID_H */
