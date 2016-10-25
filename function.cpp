#include <iostream>
#include <iomanip>
#include <set>
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
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void n_locate(int n, int sq_area, double loc_x[], double loc_y[]){

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
        temp = pow(temp, 0.5);
        if( temp < scale){
          scale = temp;
        }
      }
    }
  }
  cout << scale << endl;
  for (int j=0; j < n; j++){  // filling the 2D array with locations x,y
    loc_x[j] *= (1/scale);   // x,y are chosun randomly with unform distribution
    loc_y[j] *= (1/scale);   // x,y are chosun randomly with unform distribution
    // cout << setw(12) <<loc[i][j] ;
  }
  // cout << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void p_generator (int n, int Pth,int alpha, double P[], double loc_x[], double loc_y[]){
  for(int i=0; i<n; i++){   
    for (int j=i; j<n; j++) {
      if (i!=j) {
        double temp = pow( (loc_x[i]-loc_x[j]), 2) + pow( (loc_y[i]-loc_y[j]), 2);
        P[i*n + (j+1)] = Pth * (pow( temp, alpha*0.5));// P[i][j] == P[i*n + (j+1)]
        P[j*n + (i+1)] = P[i*n + (j+1)];// P[j][i] = P[j*n + (i+1)];
      }else{
        P[i*n + (j+1)] = 0;
      }
    }
  }

  for(int i=0; i<n; i++){
    for (int j=0; j<n; j++) {
      cout << setw(15) << P[i*n + (j+1)];
    }
    cout << endl;
  }
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void MST(int n, set<int> inc_Set, set<int> prim_Set, double P[], int T[]){
  inc_Set.insert(0);  //chosing node 0 as the start point and adding it to inc_Set
  set<int>::iterator it_temp = prim_Set.find(0); 
  prim_Set.erase(it_temp);  // removing node 1 from prim_Set
    // setting all the tree's (T) elements to 0 value
  for(int i=0; i<n; i++){
    for (int j=0; j<n; j++) {
      T[i*n + (j+1)] = 0;
    }
  }
  
  while (!prim_Set.empty()){
    double min_cost = 1.0/0.0;
    int s_min_cost;   // showing the start vertex of the next edge of MST  
    int e_min_cost;   // showing the end vertex of the next edge of MST
    // finding the next edge of Minimum Spanning Tree
    for (set<int>::iterator it_i=inc_Set.begin(); it_i!=inc_Set.end(); ++it_i){
      for (set<int>::iterator it_j=prim_Set.begin(); it_j!=prim_Set.end(); ++it_j){
        int tmp_i = *it_i;
        int tmp_j = *it_j;
        if (P[(tmp_i)*n + (tmp_j + 1)] < min_cost) {    // P[*it_i][*it_j] == P[(*it_i)*n + (*it_j + 1)]
          min_cost = P[(tmp_i)*n + (tmp_j + 1)];
          s_min_cost = *it_i;
          e_min_cost = *it_j;
        }
//          cout << s_min_cost << "\t" << e_min_cost << endl;
      }
    }
    // prim_Set.clear();
    inc_Set.insert(e_min_cost);
    it_temp = prim_Set.find(e_min_cost); 
    prim_Set.erase(it_temp);
    T[s_min_cost*n + (e_min_cost + 1)] = 1;
    // prim_Set.clear();
  }
}

