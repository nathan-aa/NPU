#ifndef USER_DATABASE_H
#define USER_DATABASE_H
#include "crow.h"

// CRUD operations to manage users
crow::json::wvalue authenticate_user(const std::string& email, const std::string& password);
crow::json::wvalue create_user(const std::string& username, const std::string& email);
crow::json::wvalue get_user(int id);
crow::json::wvalue update_user(int id, const std::string& email);
crow::json::wvalue delete_user(int id);
#endif