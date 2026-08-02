#include <Alegengine/alegengine.hpp>

class WindowOpener : public Aleg::Object {
public:
  WindowOpener();

  static int windowCount;
protected:
  void beforeUpdate() override;
};
