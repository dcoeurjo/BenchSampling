#include <cassert>
#include <cstring>
#include <random>

extern "C"
{
#include <TestU01.h>
#include <swrite.h>
}

#include "RNGExamples.h"

struct SimpleRNG
{
  unsigned n;
  unsigned key;

  SimpleRNG() : n(0), key(123451) {}
  SimpleRNG(const unsigned s) : n(), key() { seed(s); }

  void seed(const unsigned s)
  {
    n = 0;
    key = (s << 1) | 1u;
  }

  unsigned sample() 
  {
    return n * key ; //Eurk
  }

  // c++ interface
  unsigned operator()() 
  {
    return sample();
  }
};


//****************************
//***** TESTU01 WRAPPER
struct rng_state
{
  //~ std::default_random_engine rng;
  
  SimpleRNG rng;
  
  unsigned seed;
  unsigned n;
  unsigned d;
};

unsigned long uint_rng(void *_param, void *_state)
{
  rng_state *state = (rng_state *)_state;
  state->n++;
  return state->rng();
}

double double_rng(void *_param, void *_state)
{
  rng_state *state = (rng_state *)_state;
  state->d++;
  unsigned x = state->rng();
  return double(uint64_t(x) << 20) / double(uint64_t(1) << 52);  //unbiased uint -> double
}

void write_rng(void *_state)
{
  rng_state *state = (rng_state *)_state;
  printf("SimpleRNG seed(%x) n(%u) d(%u)\n", state->seed, state->n, state->d);
}

//****************************
unif01_Gen *create(unsigned seed)
{
  unif01_Gen *rng = new unif01_Gen;
  rng_state *state = new rng_state;

  state->rng.seed(seed);
  state->seed = seed;

  char name[1024];
  sprintf(name, "RNG seed(%x)", seed);

  rng->param = nullptr;
  rng->state = state;
  rng->name = strdup(name);
  rng->Write = write_rng;
  rng->GetU01 = double_rng;
  rng->GetBits = uint_rng;

  return rng;
}

void release(unif01_Gen *rng)
{
  free(rng->name);
  delete (rng_state *)rng->state;
  delete rng;
}

int main(int argc, char **argv)
{
  std::random_device hwseed;
  unsigned seed = hwseed();

  unif01_Gen *rng = create(seed);

  swrite_Basic = FALSE; // affiche uniquement le resume...

  bbattery_SmallCrush(rng); // quelques secondes
  //bbattery_Crush(rng);    // 15min
  //~ bbattery_BigCrush(rng); // 1h30

  release(rng);
  return 0;
}
