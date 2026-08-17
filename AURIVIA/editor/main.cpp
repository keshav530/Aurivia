#include "aurivia/engine.h"
#include "aurivia/logger.h"

using namespace Aurivia;

int main(int argc, char* argv[])
{
    Logger::SetLevel(LogLevel::Debug);
    
    Engine engine("AURIVIA Editor", 1280, 720);
    return engine.Run();
}
