#include <set>

#ifndef RANDU
#define RANDU
  double randu(int range_from, int range_to);
#endif

#ifndef N_LOCATE
#define N_LOCATE
  void n_locate(int n, int sq_area, double loc_x[], double loc_y[]);
#endif  

#ifndef P_GENERATOR
#define P_GENERATOR
  void p_generator (int n, int Pth,int alpha, double P[], double loc_x[], double loc_y[]);
#endif 

void MST(int n, set<int> inc_Set, set<int> prim_Set, double P[], int T[]);