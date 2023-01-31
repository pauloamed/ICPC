const int MAXB = 19;
const int MAX = 500000;
const int MAXN = (MAXB + 1) * MAX;

namespace trie{
  int nxt_node = 0;
  int child[MAXN][2];
  int size[MAXN];

  void init(){
    memset(child, -1, sizeof child);
  }

  bool get_bit(int x, int i){
    return (x >> i) & 1;
  }

  int add(int num, int node = 0, int curr_bit = MAXB){
    int curr_node = nxt_node++;
    if(node == -1) size[curr_node] = 1;
    else size[curr_node] = size[node] + 1;

    if(curr_bit == -1) return curr_node;
      
    int b = get_bit(num, curr_bit);
    if(node == -1){
      child[curr_node][b] = add(
        num, -1, curr_bit - 1
      );
      child[curr_node][!b] = -1;
    }else{
      child[curr_node][b] = add(
        num, child[node][b], curr_bit - 1
      );
      child[curr_node][!b] = child[node][!b];
    }
    
    return curr_node;
  }

  int query(int num, int minus, int plus, int curr_bit = MAXB){
    if(curr_bit == -1) return 0;
    int b = !get_bit(num, curr_bit);

    assert(plus != -1);

    int goal_child_size = 0;
    if(minus != -1 && child[minus][b] != -1){
      goal_child_size -= size[child[minus][b]];
    }
    if(child[plus][b] != -1){
      goal_child_size += size[child[plus][b]];
    }

    int curr_in = size[plus];
    if(minus != -1) curr_in -= size[minus];

    if(goal_child_size > 0){
      if(minus != -1 && child[minus][b] != -1) 
        minus = child[minus][b];
      else minus = -1;

      return (1 << (curr_bit)) + query(num, minus, child[plus][b], curr_bit - 1);
    }else{
      if(minus != -1 && child[minus][!b] != -1) 
        minus = child[minus][!b];
      else minus = -1;

      return query(num, minus, child[plus][!b], curr_bit - 1);
    }
  }
}
