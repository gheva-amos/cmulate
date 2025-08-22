#include <iostream>
#include "game_loop.h"

int main()
{
  cmulate::GameLoop looper(10, 10, 2);
  looper.limit(10.0f);

  looper();
  return 0;
}
