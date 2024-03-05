#include <cassert>
#include <cstring>
#include <random>

extern "C"
{
#include <TestU01.h>
#include <swrite.h>
}


struct FCRNG
{
  unsigned n;
  unsigned key;

  FCRNG() : n(0), key(123451) {}
  FCRNG(const unsigned s) : n(), key() { seed(s); }

  void seed(const unsigned s)
  {
    n = 0;
    key = (s << 1) | 1u;
  }

  FCRNG &index(const unsigned i)
  {
    n = i;
    return *this;
  }

  unsigned sample() { return hash(n++ * key); }

  unsigned sample_range(const unsigned range)
  {
    // Efficiently Generating a Number in a Range
    // cf http://www.pcg-random.org/posts/bounded-rands.html
    unsigned divisor = (uint64_t(1) << 32) / range;
    if (divisor == 0)
      return 0;

    while (true)
    {
      unsigned x = sample() / divisor;
      if (x < range)
        return x;
    }
  }

  // c++ interface
  unsigned operator()() { return sample(); }
  static constexpr unsigned min() { return 0; }
  static constexpr unsigned max() { return (uint64_t(1) << 32) - 1; }
  typedef unsigned result_type;

  static unsigned hash(unsigned x)
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

struct rng_state
{
  //~ std::default_random_engine rng;
  FCRNG rng;

  std::uniform_real_distribution<double> uniform;

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
  return float(x) / float(uint64_t(1) << 32);
  //return double(uint64_t(x) << 20) / double(uint64_t(1) << 52);
}

void write_rng(void *_state)
{
  rng_state *state = (rng_state *)_state;
  printf("CRNG seed(%x) n(%u) d(%u)\n", state->seed, state->n, state->d);
}

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
  //~ bbattery_Crush(rng);    // 15min
  //~ bbattery_BigCrush(rng); // 1h30

  release(rng);
  return 0;
}
