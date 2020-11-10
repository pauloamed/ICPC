#include<bits/stdc++.h>
using namespace std;


struct SuffixAutomaton{
    map<char, int> to[2*N]; // transitions graph
    int link[2*N], len[2*N]; // suffix links and len of states (#substrings of the class)
    int last; // indicates the last created state
    int sz; // size of automata

    bool suffix[2*N]; // will mark whether the state is a terminal state (suffix)

    SuffixAutomaton(){
        link[0] = -1; // convinience
        last = 0; // the initial state
        sz = 1; // the initial state
    }

    void addLetter(char c){
        int cur = sz++; // retriving the current state ID
        len[cur] = len[last] + 1; // setting curs len

        // starting to travess automaton through the links
        // until there is already an transition using char c
        // or we reach the last level
        int p = last;
        while(p != -1 && !to[p][c]) {
            to[p][c] = cur; // setting the transition to the created state
            p = link[p]; // acessing next state through suffix link
        }

        if(p == -1){ // we got until the initial state
            // there was no substring like the one we just added
            // so we set our link to the init state
            // (empty string is the longest suffix less than a char)
            link[last] = 0;
        }else{
            int q = to[p][c]; // retriving the already matched state
            // the link of cur must have len[p] + 1
            if(len[q] == len[p] + 1){ // if it is the case
                link[cur] = q; // just set it
            }else{
                // otherwise, create a new state
                // this new state will "divide" q into two states
                // note that this is necessary since there is a new endpos
                // Since q was not the "leader" of its node, we cant attribute
                // this new pos to q's set. Hence, we create a new one

                int r = sz++; // retriving new state ID
                link[last] = r; len[r] = len[p] + 1; // as needed
                link[r] = link[q]; to[r] = to[q]; // r is a copy of q
                link[q] = r; // since r divided q, q now points to r (like linked list insertion)
                while(p != -1 && to[p][c] == q) { // change transitions
                    to[p][c] = q; // setting the transition to the clone state
                    p = link[p]; // acessing next state through suffix link
                }
            }
        }
        last = cur; // updating the last created state
    }

    void markSuffixes(){
        // assuming last is the state of the last char on the string
        int p = last;
        while(p != 0){
            suffix[p] = true;
            p = link[p];
        }
    }
};

int main(){

}
