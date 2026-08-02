#include <Alegengine/alegengine.hpp>
#include "CollisionGroup.hpp"
#include "WindowOpener.hpp"
#include <sstream>
#include <thread>
#include <chrono>

int main() {
  Aleg::init("side");

  Aleg::Player* obj1 = new Aleg::Player(glm::vec2(200.0f, 0.0f), 
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

  /*obj1->collisionGroup = CustomCollisionGroups::test1;
  obj2->collisionGroup = CustomCollisionGroups::test2;
  obj3->collisionGroup = CustomCollisionGroups::test1;*/

  obj3->setParent(obj1);

  Aleg::Window::windows["main"]->cam->setParent(obj1);

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

  Aleg::ScrollingElement* scroll = new Aleg::ScrollingElement(glm::vec2(0.25f, 0.25f),
                                                             glm::vec2(0.25f, 0.25f),
                                                             0.0f,
                                                             glm::vec3(0.1f, 0.1f, 0.1f),
                                                             0.0f);

  Aleg::Button* button = new Aleg::Button(glm::vec2(0.25f, 0.25f),
                                          glm::vec2(0.25f, 0.25f),
                                          0.0f,
                                          "textures/box.png",
                                          0.1f,
                                          "fonts/Kenney Future Narrow.ttf",
                                          "Hello, alegations !");

  button->setParent(scroll);

  Aleg::Window* testWindow = new Aleg::Window(25.0f, 25.0f, "Test", "test");
  Aleg::Object* testObj = new Aleg::Object(glm::vec2(0.0f, 0.0f),
                                           glm::vec2(300.0f, 100.0f),
                                           0.0f,
                                           "textures/box.png",
                                           0.1f,
                                           testWindow);
  testObj->anchored = true;

  Aleg::Player* p2 = new Aleg::Player(glm::vec2(0.0f, -100.0f), 
                                      glm::vec2(100.0f, 100.0f),
                                      0.0f,
                                      glm::vec3(1.0f, 0.0f, 0.0f),
                                      0.0f,
                                      testWindow);

  testWindow->cam->setParent(p2);

  Aleg::ScreenEffect* effect = new Aleg::ScreenEffect("shaders/AustraliaVert.glsl", "shaders/AustraliaFrag.glsl", "Australia");
  testWindow->screenEffects.push_back(effect);
  effect = new Aleg::ScreenEffect("shaders/AustraliaVert.glsl", "shaders/AustraliaFragH.glsl", "Australia");
  testWindow->screenEffects.push_back(effect);

  //new WindowOpener();

  /*int windowCount = 100;

  for (int i = 1; i < 200; i++) {
    windowCount += 1;
    std::cout << windowCount << "\n";

    std::ostringstream ss;
    ss << "Woondo " << windowCount;

    new Aleg::Window(25.0f, 25.0f, ss.str(), ss.str());

    std::this_thread::sleep_for(std::chrono::milliseconds(16));
  }*/

  /*Aleg::Window* testWindow2 = new Aleg::Window(25.0f, 25.0f, "Test", "test2");
  Aleg::Window* testWindow3 = new Aleg::Window(25.0f, 25.0f, "Test", "test3");*/

  Aleg::mainLoop();
  return 0;
}
