#include <set>

using namespace std;

#ifndef MINIMUM_SPANNING_TREE
#define MINIMUM_SPANNING_TREE
  double randu(int, int);
  void n_locate(int, double[], double[]);
  void p_generator (int, int, int, double[], double[], double[]);
  void MST(int, double[], int[]);
  void print_array(int , double[]);
  void print_tree(int, int[]);
  double tree_cost(int, int[], double[]);
  void newT_creator_maxCE_update(int, double&, int&, double&, double[], int[], int[]);
  void CE_check(int, double, int, double, double[], int[], int[], double[]);
  void pickup_grape(int n,double[],double[],int[]);
#endif 