#include "Core/Application.h"
#include <memory>

int main()
{
    std::unique_ptr<Application> app = std::make_unique<Application>(); 

    app->run();
}