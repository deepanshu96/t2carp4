#include "PID.h"
#include<math.h>
#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    prev_cte = 0.0;
    int_cte = 0.0;
    diff_cte = 0.0;
    cur_cte = 0.0;
    counter = 0;
    err = 0.0;
    best_err = -1;
    for(int i=0;i<2;i++)
        dp.push_back(1.0);
    p.push_back(Kp);
    p.push_back(Kd);
    curr1 = 0;
    curr2 = 0;
    this->prev_steer = 0;
}

void PID::UpdateError(double cte) {

    //prev_cte

    int_cte += cte;
    diff_cte = cte - prev_cte;
    cur_cte = cte;
    if(counter>1)
        {
         err = cte*cte;
        }
    if(int_cte>35)
        int_cte = 35;
    if(int_cte<-35)
        int_cte = -35;
}

double PID::TotalError() {
    double steer = -1*(p[0] * cur_cte +  p[1] * diff_cte );
    counter += 1;

    if(counter>5000)
        cout<<endl<<p[0]<<" Parameters "<<p[1]<<endl;
    cout<<endl<<counter<<" counter "<<curr1<<" Iteration indexes : "<<curr2<<" ";
    double tol = 0.01;
    if(fabs(dp[0])+fabs(dp[1])>tol && counter>2)
    {
        cout<<"In twiddle"<<endl;
        if(best_err==-1)
            best_err = err;
        else
        {
            if(curr2 == 0)
            {
                p[curr1]+=dp[curr1];
                steer = -1*(p[0] * cur_cte +  p[1] * diff_cte );
                curr2+=1;
                return steer;
            }
            else if(curr2==1)
            {
                if(err<best_err)
                {
                    best_err = err;
                    dp[curr1] *= 1.1;
                    curr2=0;
                    curr1 = (curr1+1)%2;
                    steer = -1*(p[0] * cur_cte +  p[1] * diff_cte );
                    return steer;
                }
                else
                {
                    p[curr1] -= 2*dp[curr1];
                    steer = -1*(p[0] * cur_cte +  p[1] * diff_cte );
                    curr2+=1;
                    return steer;
                }
            }
            else if(curr2==2)
            {
                if(err<best_err)
                {
                    best_err = err;
                    dp[curr1]*=1.1;
                    curr2 = 0;
                    curr1 = (curr1+1)%2;
                    steer = -1*(p[0] * cur_cte +  p[1] * diff_cte );
                    return steer;
                }
                else
                {
                    p[curr1] += dp[curr1];
                    dp[curr1] *= 0.9;
                    curr2 = 0;
                    curr1 = (curr1+1)%2;
                    steer = -1*(p[0] * cur_cte +  p[1] * diff_cte );
                    return steer;
                }
            }
        }
    }
 return steer;
}
