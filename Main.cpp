#include <iostream>
#include <vector>
#include <random>
// #include <boost/random/uniform_real.hpp>
// #include "boost/random/uniform_real.hpp"
// #include <boost/assert.hpp>
using namespace std;
//
double randu(int range_from, int range_to);

int main(){
  int n_num = 5;
  // boost::random::uniform_int_distribution<> six(1,6);
  vector<double> loc[2];
  for (int i=0; i< 2; i++){
    for (int j=0; j < 3; j++){
      loc[i].push_back((i+1)*(j+1));
      cout<< randu(0,100) << endl;
    }
  }
  return 0;
}
//
// double randu(int range_from, int range_to){
//   random_device rand_dev;
//   mt19937 generator(rand_dev());
//   uniform_int_distribution<double> distr(range_from, range_to);
//   return distr(generator);
// }

double randu(int range_from,int range_to)
{
  random_device rand_dev;
  mt19937 generator(rand_dev());
  uniform_real_distribution<double> distribution(range_to,range_from);

  double number = distribution(generator);
  // cout << number << endl;
  return number;
}
