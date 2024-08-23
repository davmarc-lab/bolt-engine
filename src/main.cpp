#include "Core/Engine/BoltEngine.hpp"

#include <memory>

int main() {
    std::unique_ptr<BoltEngine> engine = std::make_unique<BoltEngine>();

    engine->init();
    engine->run();
    
    return 0;
}
