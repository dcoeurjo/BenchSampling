
// counter based rng, cf "Parallel Random Numbers: As Easy as 1, 2, 3"
// https://www.thesalmons.org/john/random123/
// le code est quand meme bien degueu et l'etat interne des generateurs est un peu trop gros.
// openrand a serieusement nettoye l'implem. cf https://github.com/msu-sparta/OpenRAND/blob/main/include/openrand/philox.h

// du coup, plus simple et de qualite raisonnable :
// "PRNS with 32 bits of state"
// https://marc-b-reynolds.github.io/shf/2017/09/27/LPRNS.html
// pas les memes constantes que dans le blog, mais small crush passe sans probleme, donc j'imagine que ca suffit.
// et c'est mieux que std::default_random_engine qui echoue a la moitiee des tests de small crush..
struct FCRNG
{
  unsigned n;
  unsigned key;
  
  FCRNG( ) : n(0), key(123451) {}
  FCRNG( const unsigned s ) : n(), key() { seed(s); }
  
  void seed( const unsigned s ) { n= 0; key= (s << 1) | 1u; }
  
  FCRNG& index( const unsigned i ) { n= i; return *this;}
  
  unsigned sample( ) { return hash(n++ * key); }
  
  unsigned sample_range( const unsigned range )
  {
    // Efficiently Generating a Number in a Range
    // cf http://www.pcg-random.org/posts/bounded-rands.html
    unsigned divisor= (uint64_t(1) << 32) / range;
    if(divisor == 0) return 0;
    
    while(true)
    {
      unsigned x= sample() / divisor;
      if(x < range) return x;
    }
  }
  
  // c++ interface
  unsigned operator() ( ) { return sample(); }
  static constexpr unsigned min( ) { return 0; }
  static constexpr unsigned max( ) { return (uint64_t(1) << 32) -1 ;}
  typedef unsigned result_type;
  
  static unsigned hash( unsigned x )
  {
    x ^= x >> 16;
    x *= 0x21f0aaad;
    x ^= x >> 15;
    x *= 0xd35a2d97;
    x ^= x >> 15;
    return x;
  }
  // cf "hash prospector" https://github.com/skeeto/hash-prospector/blob/master/README.md
};
