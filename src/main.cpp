#include <Alegengine/alegengine.hpp>
#include "CollisionGroup.hpp"

int main() {
  Aleg::init("side");

  Aleg::Player* obj1 = new Aleg::Player(glm::vec2(100.0f, 0.0f), 
                                        glm::vec2(100.0f, 100.0f),
                                        0.0f,
                                        glm::vec3(1.0f, 0.0f, 0.0f),
                                        0.0f);

  Aleg::Object* obj2 = new Aleg::Object(glm::vec2(700.0f, 500.0f), 
                                        glm::vec2(100.0f, 100.0f),
                                        0.0f,
                                        "textures/box.png",
                                        0.0f);

  Aleg::Object* obj3 = new Aleg::Object(glm::vec2(150.0f, 50.0f), 
                                        glm::vec2(100.0f, 100.0f),
                                        0.0f,
                                        "textures/box.png",
                                        0.1f);

  obj1->collisionGroup = CustomCollisionGroups::test1;
  obj2->collisionGroup = CustomCollisionGroups::test2;
  obj3->collisionGroup = CustomCollisionGroups::test1;

  obj3->parent = obj1;

  Aleg::Camera::currentCamera->parent = obj1;

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
