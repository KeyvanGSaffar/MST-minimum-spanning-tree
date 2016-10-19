#include<iostream>
#include<vector>

using namespace std;
int main(){
  vector<double> loc[2];
  for (int i=0; i< 2; i++){
    for (int j=0; j < 3; j++){
      loc[i].push_back((i+1)*(j+1));
      cout<< loc[i][j] << endl;
    }
  }
  return 0;
}
