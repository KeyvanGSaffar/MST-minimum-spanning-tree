#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include "function.hpp"
#include <cmath>
using namespace std;

// double randu(int range_from, int range_to);

int main(){
  
  int sq_area = 100;  // square area with this value as side length
  int n_num[] = {5,10,-1};//{5,15,25,35,45,65,85,105,125,145,170,190,200}    // number of nodes
  int alpha = 2;
  for (int node = 0; n_num[node]!=-1; node++){
    double loc[2][n_num[node]];  // a dynamic array to represent the location x,y
    set<string> nSet; // set of the nodes that are already included
    set<string>::iterator it; // itereator to refer to the elements of the nSet
    string n_name[n_num[node]];  // an array including the name of all nodes
    double H[n_num[node]][n_num[node]];   // array holding edge values
    /////////////////////////////////////////////////////////////////////////
    for (int i=0; i< 2; i++){     // filling the 2D array with locations x,y
      for (int j=0; j < n_num[node]; j++){
        loc[i][j] = randu(0,sq_area);   // x,y are chosun randomly with unform distribution
        // cout << setw(9) <<loc[i][j] ;
      }
      // cout << endl;
    }
    double scale = 1;
    for(int i=0; i<n_num[node]; i++){
      for (int j=i; j<n_num[node]; j++) {
        if (i!=j) {
          double temp = pow((loc[1][i]-loc[1][j]), 2) + pow((loc[2][i]-loc[2][j]), 2);
          if( temp < scale){
            scale = pow( temp, -alpha*0.5);
          }
        }
      }
    }
    for (int i=0; i< 2; i++){     // filling the 2D array with locations x,y
      for (int j=0; j < n_num[node]; j++){
        loc[i][j] *= (1/scale);   // x,y are chosun randomly with unform distribution
        cout << setw(12) <<loc[i][j] ;
      }
      cout << endl;
    }

    //////////////////////////////////////////////////////////////////////////
    for(int i=0; i < n_num[node]; i++){  // putting nodes name in the n_name array
      string temp = "n";
      n_name[i] = temp + to_string(i);
    }
    // for(int i=0; i < n_num; i++){
    //   cout << n_name[i] << endl;
    // }
    //////////////////////////////////////////////////////////////////////////
    for(int i=0; i<n_num[node]; i++){
      for (int j=i; j<n_num[node]; j++) {
        if (i!=j) {
          double temp = pow( (loc[1][i]-loc[1][j]), 2) + pow( (loc[2][i]-loc[2][j]), 2);
          H[i][j] = (pow( temp, -alpha*0.5));
          H[j][i] = 0;
        }else{
          H[i][j] = 0;
        }
      }
    }

    for(int i=0; i<n_num[node]; i++){
      for (int j=0; j<n_num[node]; j++) {
        cout << setw(15) << H[i][j];
      }
      cout << endl;
    }
    //////////////////////////////////////////////////////////////////////////
    nSet.insert("AITF");
    nSet.insert("Google");
    it = nSet.find("Google");
    if (it!=nSet.end()){
      cout << *it <<"\n";
  }
  for (it=nSet.begin(); it!=nSet.end(); ++it)
  cout << *it << "\n";
  // cout << '\n';
  }
  return 0;
}
