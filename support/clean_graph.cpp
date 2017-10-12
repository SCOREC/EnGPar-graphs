#include <fstream>
#include <cassert>
#include <vector>
#include <set>
typedef long unsigned int num_t;

num_t pos(num_t s, num_t d, num_t length) {
  return s*length+d;
}
num_t reverse(num_t p, num_t length) {
  num_t s = p/length;
  num_t d = p%length;
  return pos(d,s,length);
}
int main(int argc, char* argv[]) {
  assert(argc==3);
  std::ifstream in_str(argv[1]);
  assert(in_str);
  num_t n,m;
  in_str>>n>>m;
  std::vector<num_t> srcs,dests;
  std::set<num_t> verts;
  std::set<num_t> edges;  
  //Remove Self Edges
  for (int i=0;i<m;i++) {
    num_t s,d;
    in_str>>s>>d;
    if (s==d)
      continue;
    srcs.push_back(s);
    dests.push_back(d);
    verts.insert(s);
    verts.insert(d);
    edges.insert(pos(s,d,n));
  }
  in_str.close();

  //Make the graph bidirectional
  std::set<num_t>::iterator itr;
  for(itr=edges.begin();itr!=edges.end();itr++) {
    num_t pos = reverse(*itr,n);
    if (edges.find(pos)==edges.end()) {
      srcs.push_back(pos/n);
      dests.push_back(pos%n);
    }
  }
  

  //Check that each vertex is a source or dest
  int num_deleted=0;
  int tempn = n;
  for (num_t i=0;i<tempn;i++) {
    if (verts.find(i)==verts.end()) {
      n--;
      for (num_t j=0;j<srcs.size();j++) {
        if (i-num_deleted<srcs[j])
          srcs[j]--;
        if (i-num_deleted<dests[j])
          dests[j]--;
      }
      num_deleted++;
    }
  }
  std::ofstream out_str(argv[2]);
  out_str<<n<<' '<<srcs.size()<<'\n';
  for (num_t i=0;i<srcs.size();i++) {
    out_str<<srcs[i]<<' '<<dests[i]<<'\n';
  }
  out_str.close();
  return 0;
}
