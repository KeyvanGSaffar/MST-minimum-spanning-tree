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
void print_array(int n,double P[]){
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
void print_tree(int n,int T[]){
  for(int i=0; i<n; i++){
    for (int j=0; j<n; j++) {
      cout << setw(2) << T[i*n+(j+1)];
    }
    cout << endl;
  }
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
double tree_cost(int n, int T[], double P[]){
  double cost = 0;
  for(int i=0; i<n; i++){
    for(int j=0; j<n; j++){
      if(T[i*n + (j+1)] == 1){
        cost += P[i*n + (j+1)];
      }
    }
  }
  return cost;
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

  print_array(n,P);
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void MST(int n, double P[], int T[]){
  set<int> inc_Set;  // for tree formation, the set of vertices included in the tree
  set<int> prim_Set;   // for tree formation, the set of vertices not included in the tree

  // putting nodes name in the n_name array
  //
  for(int i1=0; i1 < n; i1++){  
    prim_Set.insert(i1);//(n + to_string(i));
  }

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
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void newT_creator_maxCE_update(int n, int maxCE, int center, double power, double P[], int T[], int newT[]){
  for(int i=0; i<n; i++){     //for all x,y in S do
    for(int j=i; j<n; j++) {  //for all x,y in S do
      if(i!=j){               //for all x,y in S do
        
        double P_prim[n*n]; // a copy of P to be modified as below and 
        for ( int i_p = 0; i_p < n*n; i_p++){
          P_prim[i_p] = P[i_p];   //copy p into P_prim
        }

        for(int i1=0; i1<n; i1++){
          for (int j1=0; j1<n; j1++){
            if(T[i1*n + (j1+1)] == 0){
              P_prim[i1*n + (j1+1)] = 1.0/0.0;                
            }
          }
        }

        for(int k=0; k<n;k++){
          if(k!=i){
            if(P[i*n + (k+1)] <= P[i*n + (j+1)]){
              P_prim[i*n + (k+1)] = 0;
            }
          }
        }
        
        int T_prim[n*n];
        MST(n, P_prim, T_prim); 
        
        double CE_temp;
        double c,c_prim;
        c = tree_cost(n,T,P);
        c_prim = tree_cost(n,T_prim,P_prim);
        CE_temp = (c_prim)/P[i*n + (j+1)];
        if(CE_temp > maxCE){
          maxCE = CE_temp;
          cout << maxCE << endl;
          center = i;
          power = P[i*n + (j+1)];
          for(int i2=0; i2<n*n; i2++){
            newT[i2] = T_prim[i2];
          }            
        }
        // print_array(n_num[node],P_prim);
      }
    }
  }
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void CE_check(int n,double maxCE, int center, double power, double P[],int T[], int newT[], double p_x[]){
  if(maxCE > 2){
    cout << "We are in CE_check" <<endl;
    for(int i=0; i<n; i++){
      if(i!=center){
        P[center*n + (i+1)] = 0;
      }
    }

    for ( int j = 0; j < n*n; j++){
      T[j] = newT[j];
    }
    p_x[center] = power;
  }
}