#include <iostream>
#include <iomanip>
#include <set>
#include <random>
#include <cmath>
#include <string.h>   //to use memset
#include "function.hpp"

using namespace std;

double randu(int range_from,int range_to)
{
  random_device rand_dev;
  // mt19937 generator(0);
  mt19937 generator(rand_dev());
  //generator.seed(1369);
  uniform_real_distribution<double> distribution(range_from,range_to);

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
      cout << setw(15) << P[i*n + j];
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
      cout << setw(2) << T[i*n + j];
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
      if(T[i*n + j] == 1){
        cost += P[i*n + j];
      }
    }
  }
  return cost;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
// void n_locate(int n, int sq_area, double loc_x[], double loc_y[]){
void n_locate(int n, double loc_x[], double loc_y[]){
  double angle;
  double radius;
  for (int j=0; j < n; j++){
    angle = randu(0,1)*2*M_PI;   // x are chosun randomly with unform distribution
    radius = pow(randu(0,1),0.5);   // y are chosun randomly with unform distribution

    loc_x[j] = radius*cos(angle);   // x,y are chosun randomly with unform distribution
    loc_y[j] = radius*sin(angle);   // x,y are chosun randomly with unform distribution
    // cout << setw(9) <<loc[i][j] ;
  }
  // double scale = 1; // in the following for loops we check whether there are any nodes that are closer that 1 unit (meter) to each other. If so, we update the scale to new value and multiply all coordinates by 1/scale.
  // for(int i=0; i<n; i++){
  //   for (int j=i; j<n; j++) {
  //     if (i!=j) {
  //       double temp = pow((loc_x[i]-loc_x[j]), 2) + pow((loc_y[i]-loc_y[j]), 2);
  //       temp = pow(temp, 0.5);
  //       if(temp < scale){
  //         scale = temp;
  //       }
  //     }
  //   }
  // }
  // cout << scale << endl;
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
        P[i*n + j] = Pth * (pow(temp, alpha*0.5));// P[i][j] == P[i*n + (j+1)]
        P[j*n + i] = P[i*n + j];// P[j][i] = P[j*n + (i+1)];
      }else{
        P[i*n + j] = 0;
      }
    }
  }

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
  prim_Set.erase(it_temp);  // removing node 0 from prim_Set
    // setting all the tree's (T) elements to 0 value
  for(int i=0; i<n; i++){
    for (int j=0; j<n; j++) {
      T[i*n + j] = 0;
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
        if (P[(tmp_i)*n + tmp_j] < min_cost) {    // P[*it_i][*it_j] == P[(*it_i)*n + (*it_j + 1)]
          min_cost = P[(tmp_i)*n + tmp_j];
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
    T[s_min_cost*n + e_min_cost] = 1;
    T[e_min_cost*n + s_min_cost] = 1;
    // prim_Set.clear();
  }
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void newT_creator_maxCE_update(int n, double& maxCE, int& center, double& power, double P[], int T[], int newT[]){
  for(int i=0; i<n; i++){     //for all x,y in S do
    for(int j=0; j<n; j++) {  //for all x,y in S do
      if(i!=j && P[i*n+j]!=0){               //for all x,y in S do
        
        double P_prim[n*n]; // a copy of P to be modified as below and 
        for ( int i_p = 0; i_p < n*n; i_p++){
          P_prim[i_p] = P[i_p];   //copy p into P_prim
        }

        for(int i1=0; i1<n; i1++){
          for (int j1=0; j1<n; j1++){
            if(T[i1*n + j1] == 0){
              P_prim[i1*n + j1] = 1.0/0.0;                
            }
          }
        }
        
        for(int k=0; k<n; k++){
          if(k!=i){
            if(P[i*n + k] <= P[i*n + j]){
              P_prim[i*n + k] = 0;
              P_prim[k*n + i] = 0;
            }
          }
        }
        
        // cout << i*n + j << endl;
        // cout << "P_prim" << endl;
        // print_array(n,P_prim);
        // cout << endl;

        int T_prim[n*n];
        MST(n, P_prim, T_prim); 
        
        // cout << "T_prim" << endl;
        // print_tree(n,T_prim);
        // cout << endl;

        double CE_temp;
        double c,c_prim;
        c = tree_cost(n,T,P)/2;
        c_prim = tree_cost(n,T_prim,P_prim)/2;
        CE_temp = (c - c_prim)/P[i*n + j];

        // cout << "CE_temp" << endl;
        // cout << CE_temp << endl;
        // cout << endl;

        if(CE_temp > maxCE){
          maxCE = CE_temp;

          // cout << "maxCE" << endl; 
          // cout << maxCE << endl;
          // cout << endl;
          
          center = i;
          power = P[i*n + j];
          for(int i2=0; i2<n*n; i2++){
            newT[i2] = T_prim[i2];
          }            
        }
        // cout << "newT" << endl;
        // print_tree(n, newT);
        // cout << endl;
        // print_array(n_num[node],P_prim);
      }
    }
  }

  // cout << "maxCE" << endl; 
  // cout << maxCE << endl;
  // cout << endl;
}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void CE_check(int n,double maxCE, int center, double power, double P[],int T[], int newT[], double p_x[]){
  // cout << "maxCE in CE_check" << endl; 
  // cout << maxCE << endl;
  // cout << endl;
  
  
  if(maxCE > 2){

    // cout << "We are in CE_check" <<endl;
    for(int i=0; i<n; i++){
      if(i!=center){
        if (P[center*n + i] <= power){
          P[center*n + i] = 0;
        }
      }
    }

    for ( int j = 0; j < n*n; j++){
      T[j] = newT[j];
    }
    p_x[center] = power;
  }
}

////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void pickup_grape(int n,double p_x[],double P[],int T[]){
  set<int> setA;  // for power assignment, the set of vertices investigated
  set<int> setS_A;  // for tree formation, the set of vertices not investigated
  // putting nodes name in the setS_A
  //
  for(int i1=0; i1 < n; i1++){  
    setS_A.insert(i1);//(n + to_string(i));
  }

  setA.insert(0);  //chosing node 0 as the start point and adding it to inc_Set
  set<int>::iterator it_temp = setS_A.find(0); 
  setS_A.erase(it_temp);  // removing node 0 from setB
  
  while (!setS_A.empty()){
    // int e_min_cost;   // showing the end vertex of the next edge of MST
    // finding the next edge of Minimum Spanning Tree
    for (set<int>::iterator it_i=setA.begin(); it_i!=setA.end(); ++it_i){
      double max_pow = 0;
      int n_max_pow;   // showing the start vertex of the next edge of MST
      set<int> setB;  
 
      for (set<int>::iterator it_j=setS_A.begin(); it_j!=setS_A.end(); ++it_j){
        int tmp_i = *it_i;
        int tmp_j = *it_j;
        if (T[(tmp_i)*n + tmp_j] == 1) {    // P[*it_i][*it_j] == P[(*it_i)*n + (*it_j + 1)]
          setB.insert(tmp_j);
          if (P[(tmp_i)*n + tmp_j] > max_pow){
            max_pow = P[(tmp_i)*n + tmp_j];
            n_max_pow = tmp_i;
          }
        } 

//          cout << s_min_cost << "\t" << e_min_cost << endl;
      }
      if (max_pow != 0){
        p_x[n_max_pow] = max_pow;
        for (set<int>::iterator it=setB.begin(); it!=setB.end(); ++it){
          setA.insert(*it);  //chosing node 0 as the start point and adding it to inc_Set
          setS_A.erase(*it);
        }
        break;
      }

    }

  }

}
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////
void algorithm_CA(int Pth, int alpha, int round, int n_num[], double cost_vec[]){
  for (int node = 0; n_num[node]!=-1; node++){
    double round_sum = 0;
    for(int r=0; r<round; r++){
    
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
      double P_old[n_num[node]*n_num[node]];    // to keep the unchanged powers
      // int T[n_num[node]][n_num[node]];
      int T[n_num[node]*n_num[node]];
      int T_old[n_num[node]*n_num[node]];
      int center;   // as defined in the paper
      double power;
      int newT[n_num[node]*n_num[node]];
      double p_x[n_num[node]];
      /////////////////////////////////////////////////////////////////////////
      // locating nodes in the square area randomly
      //
      n_locate(n_num[node],loc_x,loc_y);      
      //////////////////////////////////////////////////////////////////////////
      // setting arrays' elements to 0 value
      //
      memset(p_x,0,n_num[node]*sizeof(double));
      memset(newT,0,n_num[node]*n_num[node]*sizeof(int));
      //////////////////////////////////////////////////////////////////////////
      // filling P with the edges costs
      //
      p_generator(n_num[node],Pth,alpha,P,loc_x,loc_y);
      memcpy(P_old,P,sizeof(double)*n_num[node]*n_num[node]);
      //////////////////////////////////////////////////////////////////////////
      //In this part we use the Prim's algorithm o find the MST
      //
      MST(n_num[node], P, T);
      memcpy(T_old,T,n_num[node]*n_num[node]*sizeof(int));  // copying the values of T to T_old

      

      //////////////////////////////////////////////////////////////////////////
      //
      //
      double maxCE = 3 ;
      // int while_cnt = 0;
      while(maxCE>2){
        maxCE = 0;
        newT_creator_maxCE_update(n_num[node], maxCE, center, power, P, T, newT);
        CE_check(n_num[node],maxCE,center,power,P,T,newT,p_x);
        // while_cnt++;
      }
      //////////////////////////////////////////////////////////////////////////
      //  Showing the parameters before final stage of ggrape picking up
      //

      // cout << endl;
      // print_array(n_num[node],P);
      // cout<<endl;

      // cout << "while_cnt" << endl;
      // cout << while_cnt << endl;
      // cout << endl;

      // cout << "Print T" << endl;
      // print_tree(n_num[node],T);
      // cout << endl;


      // cout << "p(x) :" << endl;
      // double sum_px=0;
      // for (int i=0; i<n_num[node] ; i++){
      //   cout << p_x[i] << " "; 
      //   sum_px += p_x[i];
      // }
      // cout << endl;
      // cout << endl;
      // cout << "Sum of p(x):" << endl;
      // cout << sum_px << endl;
      // cout << endl;
      
      //////////////////////////////////////////////////////////////////////////
      //  Final Stage
      //
      memset(p_x,0,n_num[node]*sizeof(double)); // clearing p_x
      pickup_grape(n_num[node],p_x,P_old,T);

      // showing parameters after final stage
      // cout << "p(x) final :" << endl;
      // for (int i=0; i<n_num[node] ; i++){
      //   cout << p_x[i] << " "; 
      // }
      // cout << endl;
      double sum_px=0;
      for (int i=0; i<n_num[node] ; i++){
        // cout << p_x[i] << " "; 
        sum_px += p_x[i];
      }
      round_sum += sum_px;
      
      // cout << "MST solution:" << endl;
  
      //////////////////////////////////////////////////////////////////////////
      //  THIS PART IS TO RUN MST FOR COMPARISION PURPOSE
      //  To do so we pass T_old and P_old to MST and pickup_grape functions
      //
      // memset(p_x,0,n_num[node]*sizeof(double)); // clearing p_x
      // pickup_grape(n_num[node],p_x,P_old,T_old);

      // cout << "Print P_old" << endl;
      // print_array(n_num[node],P_old);

      // cout << "Print T_old" << endl;
      // print_tree(n_num[node],T_old);
      // cout << endl;

      // cout << "p(x) MST :" << endl;
      // sum_px=0;
      // for (int i=0; i<n_num[node] ; i++){
      //   cout << p_x[i] << " "; 
      //   sum_px += p_x[i];
      // }
      // cout << endl;
      // cout << "Sum of p(x):" << endl;
      // cout << sum_px << endl;
      // cout << endl;
    }
    cost_vec[node] = round_sum/round;
    cout << "Sum of p(x):" << endl;
    cout << cost_vec[node] << endl;

  }
}