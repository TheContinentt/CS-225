<<<<<<< HEAD
#include "Image.h"
//#include "Image.cpp"
#include "cs225/PNG.h"

using namespace cs225;

int main() {
  Image alma;

  alma.readFromFile("alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");
  
  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  alma.readFromFile("alma.png");
  alma.scale(2);
  alma.writeToFile("scale2x.png");
/*
  alma.readFromFile("alma.png");
  alma.scale(1500, 1000);
  alma.writeToFile("scaletest.png");
*/
  return 0;
}
=======
#include "Image.h"
//#include "Image.cpp"
#include "cs225/PNG.h"

using namespace cs225;

int main() {
  Image alma;

  alma.readFromFile("alma.png");
  alma.lighten(0.2);
  alma.writeToFile("lighten.png");
  
  alma.readFromFile("alma.png");
  alma.saturate(0.2);
  alma.writeToFile("saturate.png");

  alma.readFromFile("alma.png");
  alma.scale(2);
  alma.writeToFile("scale2x.png");
/*
  alma.readFromFile("alma.png");
  alma.scale(1500, 1000);
  alma.writeToFile("scaletest.png");
*/
  return 0;
}
>>>>>>> e73ee3ea7fbda9b3ac609f670b78729a8adece6d
