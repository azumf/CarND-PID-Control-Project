#ifndef PID_H
#define PID_H
#include<vector>

class PID {
public:
  /*
  * Errors
  */
  double p_error;
  double i_error;
  double d_error;

  /*
  * Coefficients
  */ 
  double Kp;
  double Ki;
  double Kd;
  /*
  * helpers
  */
  int n_params;
  int steps_end;
  int steps_eval;
  int dp_index;
  double total_error;
  double best_error;
  double d_err;
  double i_err;
  double prev_cte;
  double p_err;
  int step;
  std::vector<double> dp;
  bool twiddle;
  double tune_up;
  double tune_down;

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

  /*
  * Helper function for twiddle
  */
  void Add_dp(int index, double whattoadd);

  int GetStep();
};

#endif /* PID_H */
