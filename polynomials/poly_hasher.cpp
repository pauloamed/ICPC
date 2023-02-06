std::mt19937 rng((int) std::chrono::steady_clock::now().time_since_epoch().count());

const int NUM_HASHES = 3;

struct PolyHasher{
  vector<mint> coef[NUM_HASHES];

  PolyHasher(int degree){
    for(int i = 0; i < NUM_HASHES; ++i){
      coef[i] = vector<mint>(degree + 1);
      
      for(int j = 0; j <= degree; ++j){
        uniform_int_distribution<int> dist(0, MOD - 1);
        coef[i][j] = dist(rng);
      }
    }
  }

  array<mint, NUM_HASHES> eval(mint x){
    array<mint, NUM_HASHES> out;
    for(int i = 0; i < NUM_HASHES; ++i){
      for(auto c : coef[i]) out[i] = out[i] * x + c;
    }
    return out;
  }   
};
