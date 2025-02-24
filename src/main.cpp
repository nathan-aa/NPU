#include "crow.h"
#include "routes.h"
#include "database.h"
#include "user_api.h"
#include "creation_api.h"
#include <iostream>

// Initialize database and setup routes
int main() {
    crow::SimpleApp app;
    init_db();

    UserAPI userAPI;
    userAPI.setup_routes(app);

    CreationAPI creationAPI;
    creationAPI.setup_routes(app);

    app.port(8080).multithreaded().run();
}
