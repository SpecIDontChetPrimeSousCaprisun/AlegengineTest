#include <Alegengine/alegengine.hpp>
#include <shaders/AustraliaVert.h>
#include <shaders/AustraliaFrag.h>
#include <shaders/AustraliaFragH.h>
#include <textures/box.h>
#include <fonts/KenneyFutureNarrow.h>
#include <sstream>
#include <thread>
#include <chrono>

#include "CollisionGroup.hpp"
#include "WindowOpener.hpp"

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
                                        box_png,
                                        box_png_len,
                                        0.0f);

  Aleg::Object* obj3 = new Aleg::Object(glm::vec2(150.0f, 50.0f), 
                                        glm::vec2(100.0f, 100.0f),
                                        0.0f,
                                        box_png,
                                        box_png_len,
                                        0.1f); 

  Aleg::PointLight* light = new Aleg::PointLight(glm::vec2(0.0f, 0.0f),
                                                 500.0f,
                                                 100.0f,
                                                 glm::vec3(1.0f, 0.5f, 0.0f),
                                                 Aleg::Window::currentWindow);

  light->setParent(obj1);

  obj1->collisionGroup = CustomCollisionGroups::test1;
  obj2->collisionGroup = CustomCollisionGroups::test2;
  obj3->collisionGroup = CustomCollisionGroups::test1;

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

  for (int i = 0; i < 30; i++) {
    Aleg::Button* button = new Aleg::Button(glm::vec2(0.25f, 0.25f),
                                            glm::vec2(0.25f, 2.5f),
                                            0.0f,
                                            box_png,
                                            box_png_len,
                                            0.1f,
                                            KenneyFutureNarrow_ttf,
                                            KenneyFutureNarrow_ttf_len,
                                            "Hello, alegations !");

    button->setParent(scroll);
  }

  scroll->layout = "Grid";

  Aleg::Window* testWindow = new Aleg::Window(25.0f, 25.0f, "Test", "test");
  Aleg::Object* testObj = new Aleg::Object(glm::vec2(0.0f, 0.0f),
                                           glm::vec2(300.0f, 100.0f),
                                           0.0f,
                                           box_png,
                                           box_png_len,
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

  Aleg::UIElement* testButton = new Aleg::UIElement(glm::vec2(0.0f, 0.0f),
                   glm::vec2(0.25f, 0.25f),
                   0.0f,
                   box_png,
                   box_png_len,
                   0.5f,
                   testWindow);

  Aleg::Tween<glm::vec2>* testTween = new Aleg::Tween<glm::vec2>(&testButton->position,
                                                                 testButton->position,
                                                                 glm::vec2(0.9f, 0.0f),
                                                                 5.0f,
                                                                 testWindow,
                                                                 Aleg::Ease::back,
                                                                 Aleg::EaseDirection::InOut);

  testTween->play();

  testButton->setParent(testWindow->parent);

  Aleg::ScreenEffect* effect = new Aleg::ScreenEffect((const char*)AustraliaVert_glsl, (const char*)AustraliaFrag_glsl, "Australia");
  testWindow->screenEffects.push_back(effect);
  effect = new Aleg::ScreenEffect((const char*)AustraliaVert_glsl, (const char*)AustraliaFragH_glsl, "AustraliaH");
  testWindow->screenEffects.push_back(effect);
 
  Aleg::mainLoop();
  return 0;
}
