#include "user_manager.h"
#include <bcrypt/BCrypt.hpp>

crow::json::wvalue UserManager::create_user(const std::string& username, const std::string& email, const std::string& password) {
    std::string hashed_password = BCrypt::generateHash(password);
    return userDAO.create_user(username, email, hashed_password);
}

crow::json::wvalue UserManager::get_user(int id) {
    return userDAO.get_user(id);
}


crow::json::wvalue UserManager::update_user(int id, const std::string& username, const std::string& email) {
    return userDAO.update_user(id, username, email);
}

crow::json::wvalue UserManager::delete_user(int id) {
    return userDAO.delete_user(id);
}


crow::json::wvalue UserManager::authenticate_user(const std::string& email, const std::string& password) {
    return userDAO.authenticate_user(email, password);
}