#include <random>
#include <cmath>
#include "function.hpp"

using namespace std;

double randu(int range_from,int range_to)
{
  random_device rand_dev;
  mt19937 generator(rand_dev());
  uniform_real_distribution<double> distribution(range_to,range_from);

  double number = distribution(generator);
  // cout << number << endl;
  return number;
}

void n_locate(int n, int alpha, int sq_area, double loc_x[], double loc_y[]){
  
  for (int j=0; j < n; j++){
    loc_x[j] = randu(0,sq_area);   // x are chosun randomly with unform distribution
    loc_x[j] = randu(0,sq_area);   // y are chosun randomly with unform distribution
    // cout << setw(9) <<loc[i][j] ;
  }
  double scale = 1; // in the following for loops we check whether there are any nodes that are closer that 1 unit (meter) to each other. If so, we update the scale to new value and multiply all coordinates by 1/scale.
  for(int i=0; i<n; i++){
    for (int j=i; j < n; j++) {
      if (i!=j) {
        double temp = pow((loc_x[i]-loc_x[j]), 2) + pow((loc_y[i]-loc_y[j]), 2);
        if( temp < scale){
          scale = pow( temp, -alpha*0.5);
        }
      }
    }
  }
  for (int j=0; j < n; j++){  // filling the 2D array with locations x,y
    loc_x[j] *= (1/scale);   // x,y are chosun randomly with unform distribution
    loc_y[j] *= (1/scale);   // x,y are chosun randomly with unform distribution
    // cout << setw(12) <<loc[i][j] ;
  }
  // cout << endl;
}