#include "aurivia/engine.h"
#include "aurivia/logger.h"
#include <glm/gtc/matrix_transform.hpp>

using namespace Aurivia;

int main(int argc, char* argv[])
{
    Logger::SetLevel(LogLevel::Debug);
    
    Engine engine("AURIVIA - Cube Demo", 1024, 768);
    return engine.Run();
}
