#include <cmath>
#include <iostream>
#include "PID.h"
#include <math.h>

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	PID::Kp = Kp;
	PID::Ki = Ki;
	PID::Kd = Kd;
	p_err = 0.0;
	d_err = 0.0;
	i_err = 0.0;
	step = 1;

	// twiddle parameters
	dp = { 0.1*Kp, 0.1*Kd, 0.1*Ki };
	steps_end = 100;
	steps_eval = 2000;
	total_error = 0;
	best_error = std::numeric_limits<double>::max();
	twiddle = true;
	dp_index = 2;
	tune_down = false;
	tune_up = false;

}

void PID::UpdateError(double cte) {
	
	if (step == 1){
		prev_cte = cte;
	}
	
	p_err = cte;
	d_err = cte - prev_cte;
	prev_cte = cte;
	i_err += cte;

	// twiddle here
	/*
	
	if (step < steps_eval) {
		total_error += pow(cte, 2);
		cout << "total_error: " << total_error << endl;
	}
	*/

	//if (twiddle && step % (steps_end + steps_eval) == 0) {
	if (twiddle && step <= (steps_end + steps_eval)) {
		total_error = pow(cte, 2);
		cout << "twiddle - step: " << step << "   P: " << Kp << " I: " << Ki << " D: " << Kd << endl;
		if (total_error < best_error) {
			best_error = total_error;
			if (step != steps_end + steps_eval) {
				dp[dp_index] *= 1.1;
			}
			dp_index = (dp_index + 1) % 3;
			tune_up = tune_down = false;
		}
		if (!tune_up && !tune_down) {
			cout << "here 1!" << endl;
			Add_dp(dp_index, dp[dp_index]);
			tune_up = true;
		}
		else if (tune_up && !tune_down) {
			cout << "here 2!" << endl;
			Add_dp(dp_index, -2.0 * dp[dp_index]);
			tune_down = true;
		}
		else {
			cout << "here 3!" << endl;
			Add_dp(dp_index, dp[dp_index]);
			dp[dp_index] *= 0.9;
			dp_index = (dp_index + 1) % 3;
			tune_up = tune_down = false;
		}
		//total_error = 0;
	}
	step++;

}

double PID::TotalError() {
	return -Kp * p_err - Kd * d_err - Ki * i_err;
}

void PID::Add_dp(int index, double whattoadd) {
	if (index == 0) {
		Kp += whattoadd;
	}
	else if (index == 1) {
		Kd += whattoadd;
	}
	else if (index == 2) {
		Ki += whattoadd;
	}
	else {
		cout << "index error!" << endl;
	}
}

int PID::GetStep() {
	return step;
}