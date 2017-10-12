using namespace std;

#include <cstdlib>
#include <assert.h>
#include <fstream>
#include <sys/time.h>
#include <vector>
#include <queue>
#include <getopt.h>
#include <string.h>
#include <omp.h>

typedef struct graph {
  int n;
  long m;
  int* out_array;
  long* out_degree_list;
} graph;
#define out_degree(g, n) (g.out_degree_list[n+1] - g.out_degree_list[n])
#define out_vertices(g, n) &g.out_array[g.out_degree_list[n]]

//#include "util.cpp"

void read_graph(char* filename, 
  int& n, long& m, 
  unsigned*& srcs, unsigned*& dsts)
{
  ifstream file_m;
  string line;  
  file_m.open(filename);

  getline(file_m, line, ' ');
  n = atoi(line.c_str());
  getline(file_m, line);
  m = (long)strtoul(line.c_str(), NULL, 0);
  
  unsigned src, dst;
  long counter = 0;
 
  srcs = new unsigned[m];
  dsts = new unsigned[m];
  for (long i = 0; i < m; ++i)
  {
    getline(file_m, line, ' ');   
    src = (unsigned)strtoul(line.c_str(), NULL, 0);
    getline(file_m, line);
    dst = (unsigned)strtoul(line.c_str(), NULL, 0);
    srcs[counter] = src;
    dsts[counter] = dst;
    ++counter;
  }

  file_m.close();
}

void output_bin(long m, unsigned* srcs, unsigned* dsts, char* filename)
{
  FILE *fp;
  fp = fopen(filename, "wb");

  for (long i = 0; i < m; ++i)
  {
    fwrite(&srcs[i], sizeof(unsigned), 1, fp);
    fwrite(&dsts[i], sizeof(unsigned), 1, fp);
  }

  fclose(fp);
}

int main(int argc, char** argv)
{
  setbuf(stdout, NULL);
  srand(time(0));
  if (argc < 3)
  {
    printf("\nUsage: %s [infile] [outfile]\n", argv[0]);
    exit(0);
  }

  int n;
  long m;

  printf("reading in graph ...\n");

  unsigned* srcs;
  unsigned* dsts;
  read_graph(argv[1], n, m, srcs, dsts);

  printf("outputting to %s ...\n", argv[2]);
  output_bin(m, srcs, dsts, argv[2]);

  delete [] srcs;
  delete [] dsts;

  return 0;
}
