#include <cassert>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <set>

typedef long long unsigned int num_t;
num_t pos(num_t i,num_t j, num_t w) {
  return i*w+j;
}
int main(int argc, char* argv[]) {
  assert(argc==4);

  num_t n = atoi(argv[1]);
  num_t m = atoi(argv[2]);
  assert(m>n);
  assert(m%2==0);
  std::set<num_t> used;
  std::ofstream out_str(argv[3]);
  out_str<<n<<" "<<2*m<<'\n';
  for (num_t i=0;i<n;i++) {
    num_t j;
    do {
      j = rand() % n;
      while (j==i)
        j = rand() % n;
    }
    while (used.find(pos(i,j,n))!=used.end());
    out_str<<i<<' '<<j<<'\n';
    out_str<<j<<' ' <<i<<'\n';
    used.insert(pos(i,j,n));
    used.insert(pos(j,i,n));    
  }
  for (num_t k=0;k<m-n;k++) {
    num_t i;
    num_t j;
    do {
      i = rand() % n;
      j = rand() % n;
      while (j==i)
        j = rand() % n;
    }
    while (used.find(pos(i,j,n))!=used.end());
    out_str<<i<<' '<<j<<'\n';
    out_str<<j<<' ' <<i<<'\n';
    used.insert(pos(i,j,n));
    used.insert(pos(j,i,n));
  }
  out_str.close();
}
