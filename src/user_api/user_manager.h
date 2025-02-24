#ifndef USER_MANAGER_H
#define USER_MANAGER_H
#include "user_dao.h"

class UserManager {
public:
    crow::json::wvalue create_user(const std::string& username, const std::string& email, const std::string& password);
    crow::json::wvalue get_user(int id);
    crow::json::wvalue update_user(int id, const std::string& username, const std::string& email);
    crow::json::wvalue delete_user(int id);

    crow::json::wvalue authenticate_user(const std::string& email, const std::string& password);
private:
    UserDAO userDAO;
};