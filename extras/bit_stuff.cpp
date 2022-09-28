// enumerating submasks 3^N. sos dp (other file) is N2^N
  for(int msk = 0; msk < masks; ++msk){
    for(int smsk = msk; smsk; smsk = (smsk - 1) & msk){
      // smsk is submsk of msk
    }
  }


// (x - 1) & y : iterates through submasks of y
// (x + 1) | y : iterates through supermasks of y

// least significant bit of x: x & (-x)

// __builtin_popcount: counts active bits of int
// __builtin_popcountll: counts active bits of long long
