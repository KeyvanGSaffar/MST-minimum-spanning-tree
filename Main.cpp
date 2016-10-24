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
  const int Pth = 1;
  const string n = "n";
  int sq_area = 100;  // square area with this value as side length
  int n_num[] = {5,10,-1};//{5,15,25,35,45,65,85,105,125,145,170,190,200}    // number of nodes
  int alpha = 2;
  for (int node = 0; n_num[node]!=-1; node++){
    // g_node = node;
    double loc_x[n_num[node]];  // an array to represent the location x
    double loc_y[n_num[node]];  // an array to represent the location y
    set<string> nSet; // set of the nodes that are already included
    set<string>::iterator it; // itereator to refer to the elements of the nSet
    set<int> inc_Set;  // for tree formation, the set of vertices included in the tree
    set<int> prim_Set;   // for tree formation, the set of vertices not included in the tree
    set<int>::iterator it_temp; //used to access elemens of sets: inc_Set,prim_Set
    int n_name[n_num[node]];  // an array including the name of all nodes
    double P[n_num[node]][n_num[node]];   // array holding edge values
    int T[n_num[node]][n_num[node]];
    /////////////////////////////////////////////////////////////////////////
    // locating nodes in the square area randomly
    //
    n_locate(n_num[node],alpha,sq_area,loc_x,loc_y);   
    
    // for (int j=0; j < n_num[node]; j++){
    //   cout << setw(12) <<loc_x[j];
    // }
    // cout << endl;
    // for (int j=0; j < n_num[node]; j++){
    //   cout << setw(12) <<loc_x[j];
    // }
    // cout << endl;
 
    //////////////////////////////////////////////////////////////////////////
    // putting nodes name in the n_name array
    //
    for(int i=0; i < n_num[node]; i++){  
      n_name[i] = i;
      prim_Set.insert(i);//(n + to_string(i));
    }
    // for(set<int>::iterator it=prim_Set.begin(); it!=prim_Set.end(); it++){
    //   cout << *it << endl;
    // }
    //////////////////////////////////////////////////////////////////////////
    // filling H with the edges costs
    //
    for(int i=0; i<n_num[node]; i++){   
      for (int j=i; j<n_num[node]; j++) {
        if (i!=j) {
          double temp = pow( (loc_x[i]-loc_x[j]), 2) + pow( (loc_y[i]-loc_y[j]), 2);
          P[i][j] = Pth * (pow( temp, alpha*0.5));
          P[j][i] = P[i][j];
        }else{
          P[i][j] = 0;
        }
      }
    }

    for(int i=0; i<n_num[node]; i++){
      for (int j=0; j<n_num[node]; j++) {
        cout << setw(15) << P[i][j];
      }
      cout << endl;
    }
    //////////////////////////////////////////////////////////////////////////
    //In this part we use the Prim's algorithm o find the MST
    //
    inc_Set.insert(0);  //chosing node 0 as the start point and adding it to inc_Set
    it_temp = prim_Set.find(0); 
    prim_Set.erase(it_temp);  // removing node 1 from prim_Set
    // setting all the tree's (T) elements to 0 value
    for(int i=0; i<n_num[node]; i++){
      for (int j=0; j<n_num[node]; j++) {
        T[i][j] = 0;
      }
    }
    
    while (!prim_Set.empty()){
      double min_cost = 1.0/0.0;
      int s_min_cost;   // showing the start vertex of the next edge of MST  
      int e_min_cost;   // showing the end vertex of the next edge of MST
      // finding the next edge of Minimum Spanning Tree
      for (set<int>::iterator it_i=inc_Set.begin(); it_i!=inc_Set.end(); ++it_i){
        for (set<int>::iterator it_j=prim_Set.begin(); it_j!=prim_Set.end(); ++it_j){
          if (P[*it_i][*it_j] < min_cost){
            min_cost = P[*it_i][*it_j];
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
      T[s_min_cost][e_min_cost] = 1;
      // prim_Set.clear();
    }

    for(int i=0; i<n_num[node]; i++){
      for (int j=0; j<n_num[node]; j++) {
        cout << setw(2) << T[i][j];
      }
      cout << endl;
    }
    //////////////////////////////////////////////////////////////////////////

    //
    nSet.insert("AITF");
    nSet.insert("Google");
    it = nSet.find("Google");
    if (it!=nSet.end()){
      cout << *it <<"\n";
    }
    for (it=nSet.begin(); it!=nSet.end(); ++it)   //set elements can only be accessed by iterators
    cout << *it << "\n";
    // cout << '\n';
  }
  return 0;
}
