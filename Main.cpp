#include <iostream>
#include <vector>
#include "function.hpp"
using namespace std;
//
// double randu(int range_from, int range_to);

int main(){
  int n_num = 5;
  vector<double> loc[2];
  for (int i=0; i< 2; i++){     // creating a 2D array including locations x,y
    for (int j=0; j < n_num; j++){
      loc[i].push_back(randu(0,100));
      cout << loc[i][j] << "\t" ;
      // cout << " ";
    }
    cout << endl;
  }
  return 0;
}
