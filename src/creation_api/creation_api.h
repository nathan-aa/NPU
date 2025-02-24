#ifndef CREATION_API_H
#define CREATION_API_H
#include "crow.h"
#include "creation_manager.h"

class CreationAPI {
public:
    void setup_routes(crow::SimpleApp& app);
private:
    CreationManager creationManager;
};
#endif