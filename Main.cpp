#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <iomanip>
#include "function.hpp"
#include <cmath>
#include <string.h>   //to use memset
using namespace std;

// double randu(int range_from, int range_to);

int main(){
  const int Pth = 1;
  const string n = "n";
  int sq_area = 400;  // square area with this value as side length
  int n_num[] = {5,-1};//{5,15,25,35,45,65,85,105,125,145,170,190,200}    // number of nodes
  int alpha = 2;
  for (int node = 0; n_num[node]!=-1; node++){

    double loc_x[n_num[node]];  // an array to represent the location x
    double loc_y[n_num[node]];  // an array to represent the location y
    set<string> nSet; // set of the nodes that are already included
    set<string>::iterator it; // itereator to refer to the elements of the nSet
    // set<int> inc_Set;  // for tree formation, the set of vertices included in the tree
    // set<int> prim_Set;   // for tree formation, the set of vertices not included in the tree
    set<int>::iterator it_temp; //used to access elemens of sets: inc_Set,prim_Set
    int n_name[n_num[node]];  // an array including the name of all nodes
    // double P[n_num[node]][n_num[node]];   // array holding edge values
    double P[n_num[node]*n_num[node]];   // array holding edge values
    // int T[n_num[node]][n_num[node]];
    int T[n_num[node]*n_num[node]];
    int center;   // as defined in the paper
    double power;
    int newT[n_num[node]*n_num[node]];
    double p_x[n_num[node]];
    /////////////////////////////////////////////////////////////////////////
    // locating nodes in the square area randomly
    //
    n_locate(n_num[node],sq_area,loc_x,loc_y);  
    
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
    // for(int i=0; i < n_num[node]; i++){  
    //   n_name[i] = i;
    //   prim_Set.insert(i);//(n + to_string(i));
    // }
    // for(set<int>::iterator it=prim_Set.begin(); it!=prim_Set.end(); it++){
    //   cout << *it << endl;
    // }
    memset(p_x,0,n_num[node]*sizeof(double));
    //////////////////////////////////////////////////////////////////////////
    // filling P with the edges costs
    //

    p_generator(n_num[node],Pth,alpha,P,loc_x,loc_y);

    //////////////////////////////////////////////////////////////////////////
    //In this part we use the Prim's algorithm o find the MST
    //
    MST(n_num[node], P, T);

    cout << endl;
    // print_tree(n_num[node],T);
    cout << endl;

    //////////////////////////////////////////////////////////////////////////
    //
    //
    int maxCE = 0;
    int while_cnt = 0;
    while(maxCE<=2){
      maxCE = 0;
      newT_creator_maxCE_update(n_num[node], maxCE, center, power, P, T, newT);
      CE_check(n_num[node],maxCE,center,power,P,T,newT,p_x);
      while_cnt++;
    }

    //////////////////////////////////////////////////////////////////////////
    //
    //

    // nSet.insert("AITF");
    // nSet.insert("Google");
    // it = nSet.find("Google");
    // if (it!=nSet.end()){
    //   cout << *it <<"\n";
    // }
    // for (it=nSet.begin(); it!=nSet.end(); ++it)   //set elements can only be accessed by iterators
    // cout << *it << "\n";
    // cout << '\n';
  }
  return 0;
}



