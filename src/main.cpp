#include <Alegengine/alegengine.hpp>

int main() {
  Aleg::init();

  new Aleg::Object(glm::vec2(100.0f, 0.0f), 
                   glm::vec2(100.0f, 100.0f),
                   0.0f,
                   glm::vec3(1.0f, 0.0f, 0.0f),
                   0.0f);

  new Aleg::Object(glm::vec2(700.0f, 500.0f), 
                   glm::vec2(100.0f, 100.0f),
                   0.0f,
                   glm::vec3(0.0f, 1.0f, 0.0f),
                   0.0f);

  Aleg::Object* testDelete = new Aleg::Object(glm::vec2(110.0f, 0.0f), 
                             glm::vec2(100.0f, 100.0f),
                             0.0f,
                             glm::vec3(1.0f, 0.0f, 0.0f),
                             0.0f);

  Aleg::Object* platform = new Aleg::Object(glm::vec2(-50.0f, 500.0f), 
                                            glm::vec2(750.0f, 50.0f),
                                            0.0f,
                                            glm::vec3(0.0f, 0.5f, 1.0f),
                                            0.0f);

  Aleg::Object* platform2 = new Aleg::Object(glm::vec2(0.0f, 700.0f),
                                             glm::vec2(1000000.0f, 50.0f),
                                             0.0f,
                                             glm::vec3(0.0f, 0.5f, 1.0f),
                                             0.0f);

  platform2->anchored = true;

  platform->anchored = true;
  platform->rotation = 30.0f;

  testDelete->pendDelete();

  Aleg::mainLoop();
  return 0;
}
