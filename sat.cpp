#include "ruby/ruby.h"
#include <vector>
#include <string>
#include <iostream>
#include <map>
#include <cmath>

using namespace std;

#define MAX_V 10000
#define HALF_V MAX_V/2

struct scc{
  int V;
  vector<int> g[MAX_V],rg[MAX_V],re;
  bool f[MAX_V];
  int comp[MAX_V];

  scc(int v):V(v){};

  void add(int f,int t){
    g[f].push_back(t);
    rg[t].push_back(f);
  }

  void DFS(int v){
    f[v]=true;
    for(int i=0;i<g[v].size();i++){
      if(!f[g[v][i]])DFS(g[v][i]);
    }
    re.push_back(v);
  }

  void RDFS(int v,int k){
    f[v]=true;
    comp[v]=k;
    for(int i=0;i<rg[v].size();i++){
      if(!f[rg[v][i]])RDFS(rg[v][i],k);
    }
  }

  int build(){
    memset(f,false,sizeof(f));
    re.clear();
    for(int v=0;v<V;v++){
      if(!f[v])DFS(v);
    } 
    memset(f,false,sizeof(f));
    int k=0;
    for(int i=re.size()-1;i>=0;i--){
      if(!f[re[i]])RDFS(re[i],k++);
    }
    return k;
  }
};

static int convert_num(int n, const int base)
{
  if(n<0){
    return abs(n)+base;
  }else{
    return n;
  }
}

static int reverse_num(int n, const int base)
{
  if(n<base){
    return n+base;
  }else{
    return n-base;
  }
}

VALUE wrap_solver_init(VALUE self)
{
  cout << "Hello World!" << endl;
  return Qnil;
}

VALUE wrap_solve_sat(VALUE self, VALUE literal_num, VALUE boolean)
{
  int c_literal_num = NUM2INT(literal_num);
  if(c_literal_num*2 >= MAX_V){
    return Qnil;
  }

  scc sat_solver(c_literal_num*2);
  for(int i=0;i<RARRAY_LEN(boolean);i++){
    VALUE tag = RARRAY_PTR(boolean)[i];
    if(RARRAY_LEN(tag)<2)continue;
    if(RARRAY_LEN(tag)>2)return Qnil;
    int x = convert_num(NUM2INT(RARRAY_PTR(tag)[0]), c_literal_num) - 1;
    int y = convert_num(NUM2INT(RARRAY_PTR(tag)[1]), c_literal_num) - 1;
    sat_solver.add(reverse_num(x, c_literal_num), y);
    sat_solver.add(reverse_num(y, c_literal_num), x);
    cout << convert_num(NUM2INT(RARRAY_PTR(tag)[0]), c_literal_num) << endl;
    cout << convert_num(NUM2INT(RARRAY_PTR(tag)[1]), c_literal_num) << endl;
  }

  sat_solver.build();

  VALUE ret_comp = rb_ary_new();
  for(int i=0;i<c_literal_num;i++){
    if(sat_solver.comp[i] == sat_solver.comp[c_literal_num + i]){
      return Qfalse;
    }
    if(sat_solver.comp[i] > sat_solver.comp[c_literal_num + i]){
      rb_ary_push(ret_comp, Qtrue);
    }else{
      rb_ary_push(ret_comp, Qfalse);
    }
  }

  cout << "solved" << endl;
  for(int i=1;i<=sat_solver.V;i++){
    cout << sat_solver.comp[i] << endl;
  }
  return ret_comp;
}

extern "C" void Init_SATSolver()
{
  VALUE val = rb_define_class("SatSolver", rb_cObject);

  rb_define_private_method(val, "initialize", RUBY_METHOD_FUNC(wrap_solver_init), 0);
  rb_define_method(val, "solve", RUBY_METHOD_FUNC(wrap_solve_sat), 2);

}
