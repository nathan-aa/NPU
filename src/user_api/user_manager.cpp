#include "user_manager.h"
#include <bcrypt/BCrypt.hpp>

crow::json::wvalue UserManager::create_user(const std::string& username, const std::string& email, const std::string& password) {
    std::string hashed_password = BCrypt::generateHash(password);
    return userDAO.create_user(username, email, hashed_password);
}

crow::json::wvalue UserManager::get_user(int id) {
    return userDAO.get_user(id);
}

crow::json::wvalue UserManager::update_user(const std::string& username, const std::string& email   ) {
    return userDAO.create_user(username, email, hashed_password);
}

crow::json::wvalue UserManager::delete_user(int id) {
    return userDAO.delete_user(id);
}

crow::json::wvalue UserManager::authenticate_user(const std::string& email, const std::string& password) {
    return userDAO.authenticate_user(email, password);
}







void setup_user_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/user/create").methods(crow::HTTPMethod::POST)([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("username") || !body.has("email")) return crow::response(400, "Invalid JSON");
        return crow::response(create_user(body["username"].s(), body["email"].s()));
    });

    CROW_ROUTE(app, "/user/get").methods(crow::HTTPMethod::GET)([](const crow::request& req){
        auto params = crow::query_string(req.url_params);
        if (!params.has("id")) return crow::response(400, "Missing user ID");
        return crow::response(get_user(std::stoi(params.get("id"))));
    });

    CROW_ROUTE(app, "/user/update").methods(crow::HTTPMethod::PUT)([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("id") || !body.has("email")) return crow::response(400, "Invalid JSON");
        return crow::response(update_user(body["id"].i(), body["email"].s()));
    });

    CROW_ROUTE(app, "/user/delete").methods(crow::HTTPMethod::DELETE)([](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("id")) return crow::response(400, "Invalid JSON");
        return crow::response(delete_user(body["id"].i()));
    });
}