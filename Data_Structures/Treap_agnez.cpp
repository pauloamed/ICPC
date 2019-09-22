int bigrand(){ return ((rand() << 16) ^ rand()); } 
struct Treap{
	struct Node{
	int val, pri, tam;
	Node *l, *r;
	Node(){}
	Node(int v): val(v), pri(bigrand()), tam(1), l(NULL), r(NULL){}
	} *root;
	Treap(): root(NULL){}
	int size(Node*node){return node==NULL?0:node->tam;}
	void upd(Node*node){
		if(node == NULL) return;
		node->tam = size(node->l) + size(node->r) + 1;
	}
	Node* merge(Node *l, Node *r){
		if(l == NULL) return r;
		if(r == NULL) return l;
		if(l->pri > r->pri){
			l->r = merge(l->r, r);
			upd(l);
			return l;
		}
			r->l = merge(l, r->l);
			upd(r);
			return r;
	}
	void split(Node *node, int v, Node *&a, Node *&b){
		if(node == NULL){ a = b = NULL; return; }
		if(node->val <= v){
			split(node->r, v, node->r, b);
			a = node; upd(a);
		}else{
			split(node->l, v, a, node->l);
			b = node; upd(b);
		}
	}
	void modify(Node *&node, int v){ //Codar essa função apenas se o tempo tiver apertado
		if(node == NULL){ node = new Node(v); return; }
		if(node->val >= v){
			modify(node->l, v);
			if(node->pri < node->l->pri){
				Node *tmp = node->l;
				node->l = tmp->r;
				tmp->r = node;
				node = tmp;
				upd(node->r);
			}
		}else{
			modify(node->r, v);
			if(node->pri < node->r->pri){
				Node *tmp = node->r;
				node->r = tmp->l;
				tmp->l = node;
				node = tmp;
				upd(node->l);
			}
		}
		upd(node);
	}
};
