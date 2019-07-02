#include<bits/stdc++.h>
using namespace std;

#define MAXN 300

vector<pair<size_t,size_t>> v[MAXN]; // lista de adj com (adj, cap max do arco)

// https://cp-algorithms.com/graph/dinic.html

void bfs(size_t s, size_t t, size_t n, size_t lvl[], vector<size_t> flows[]){

    for(size_t i = 0 ; i < n ; i++) lvl[i] = n; // inicializando a profundidade
    lvl[s] = 0; // profundidade da fonte eh 0 (raiz)


    queue<size_t> q; // Fila da bfs
    q.push(s); // Dou inicio a fila com a fonte

    while(!q.empty()){ // Enquanto nao estiver vazia
        size_t u = q.front(); q.pop();// Recuperando o proximo vertice e retiro-o da fila

        for(size_t i = 0; i < v[u].size(); i++){  // Para cada adjacente do vertice,
            size_t adj_u = v[u][i].first; // recuperando vertice adj a u
            size_t max_flow_x = v[u][i].second; // recuperando fluxo maximo do arco
            size_t cur_flow_x = flows[u][i]; // recuperando fluxo atual do arco
            if(lvl[adj_u] == n){   // Se nao foi visitado ainda,
                if(cur_flow_x < max_flow_x){ // se ainda posso passar (residual)
                    q.push(adj_u); // Visite
                }
            }
        }
    }

    if(lvl[t] == n) return false; // nao consegui acessar t com a bfs
    else return true; // consegui acessar t com a bfs
}

int Graph::sendFlow(size_t x, size_t t, size_t flow, vector<size_t> flows[], int start[])
{
    if (u == t) return flow; // atingiu sumidouro

    // Traverse all adjacent edges one -by - one.
    for (  ; start[u] < adj[u].size(); start[u]++)
    {
        // Pick next edge from adjacency list of u
        Edge &e = adj[u][start[u]];

        if (level[e.v] == level[u]+1 && e.flow < e.C)
        {
            // find minimum flow from u to t
            int curr_flow = min(flow, e.C - e.flow);

            int temp_flow = sendFlow(e.v, curr_flow, t, start);

            // flow is greater than zero
            if (temp_flow > 0)
            {
                // add flow  to current edge
                e.flow += temp_flow;

                // subtract flow from reverse edge
                // of current edge
                adj[e.v][e.rev].flow -= temp_flow;
                return temp_flow;
            }
        }
    }

    return 0;
}


int maxflow(size_t s, size_t t, size_t n){
    if (s == t) return -1; // Caso de borda

    vector<size_t> flows[n]; // vetor auxiliar com fluxos atuais passando por arestas

    // percorrendo lista de adj para construir o vetor auxiliar
    for(size_t i = 0; i < n; ++i)
        for(size_t j = 0; j < v[i].size(); ++j)
            flows[i].push_back(0);

    size_t lvl[n]; // vetor auxiliar com a profundidade calculada dos vertices na bfs



    int total = 0;  // Initialize result

    // Augment the flow while there is path
    // from source to sink
    while(true){
        bfs(s,t,n,lvl,flows); // tentando chegar em t com s
        if(lvl[t] == n) return total; // nao conseguiu, acabou
        else{ // conseguiu, agora passa o fluxo pra t

            // store how many edges are visited
            // from V { 0 to V }
            int *start = new int[V+1];

            // while flow is not zero in graph from S to D
            while (int flow = sendFlow(s, INT_MAX, t, start))

            // Add path flow to overall flow
            total += flow;

        }
    }

    // return maximum flow
    return total;
}
