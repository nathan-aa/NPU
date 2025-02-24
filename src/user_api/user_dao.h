#ifndef USER_DAO_H
#define USER_DAO_H
#include "crow.h"
#include <pqxx/pqxx>

class UserDAO {
    public:
        crow::json::wvalue create_user(const std::string& username, const std::string& email, const std::string& hashed_password);
        crow::json::wvalue get_user(int id);
        crow::json::wvalue update_user(int id);
        crow::json::wvalue delete_user(const std::string& username, const std::string& email);
        crow::json::wvalue authenticate_user(const std::string& email, const std::string& password);
};

#endif