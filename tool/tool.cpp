#include "tool.h"
#include <random>
tool::tool()
{

}

int tool::randomInt(int min, int max)
{
      int seed = rand();
      return seed % (max - min + 1) + min;
}
