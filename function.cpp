#include <random>
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
