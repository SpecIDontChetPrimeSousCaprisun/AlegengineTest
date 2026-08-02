#include "WindowOpener.hpp"
#include <sstream>

int WindowOpener::windowCount = 100;

WindowOpener::WindowOpener() : Object(glm::vec2(0.0f, 0.0f), glm::vec2(0.0f, 0.0f), 0.0f, glm::vec3(0.0f, 0.0f, 0.0f), 0.0f) {}

void WindowOpener::beforeUpdate() {
  if (windowCount > 105) return;
  windowCount += 1;
  std::cout << windowCount << "\n";

  std::ostringstream ss;
  ss << "Woondo " << windowCount;

  new Aleg::Window(25.0f, 25.0f, ss.str(), ss.str());
}
