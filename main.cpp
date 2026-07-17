#include <Alegengine/alegengine.hpp>

int main() {
  Aleg::init();

  new Aleg::Object(glm::vec2(0.0f, 0.0f), 
                   glm::vec2(100.0f, 100.0f),
                   0.0f,
                   glm::vec3(1.0f, 0.0f, 0.0f),
                   0.0f);

  Aleg::Object* platform = new Aleg::Object(glm::vec2(-50.0f, 500.0f), 
                                            glm::vec2(1000.0f, 100.0f),
                                            0.0f,
                                            glm::vec3(1.0f, 0.0f, 0.0f),
                                            0.0f);

  platform->anchored = true;
  platform->rotation = 10.0f;

  Aleg::mainLoop();
  return 0;
}
