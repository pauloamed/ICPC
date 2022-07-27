#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
using namespace std;
typedef tree<
  int, 
  null_type/*int para map*/, 
  less<int>, 
  rb_tree_tag, 
  tree_order_statistics_node_update
  > Tree;

int main(){
	Tree s;
	s.insert(1); 
	s.insert(3);
	cout << s.order_of_key(2) << endl; // the number of elements in the s less than 2
	cout << *s.find_by_order(0) << endl; // print the 0-th smallest number in s(0-based)
	Tree::node_iterator root = s.node_begin(); s.node_end();
	//Se for map, pode usar (**root).first, (**root).second;
	Tree Y;
	s.split(1,Y);
	s.join(Y);
	s.lower_bound(10);
	Tree::iterator it = (s.lower_bound(1));
	Tree::node_iterator n_it = it.m_p_nd; //converte para node_iterator
}
