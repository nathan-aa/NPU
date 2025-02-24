#ifndef USER_API_H
#define USER_API_H
#include "crow.h"
#include "user_manager.h"

class UserAPI {
    public:
        void setup_routes(crow::SimpleApp& app);
    private:
        UserManager userManager;
};
#endif