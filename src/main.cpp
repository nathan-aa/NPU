// src/main.cpp
#include "crow_all.h"
#include "npu_routes.h"
#include "npu_database.h"
#include "user_routes.h"
#include "user_database.h"
#include <iostream>

// Initializing the application and databases.
int main() {
    crow::SimpleApp app;
    init_db();

    setup_npu_routes(app);
    setup_user_routes(app);

    app.port(8080).multithreaded().run();
}

// EOF