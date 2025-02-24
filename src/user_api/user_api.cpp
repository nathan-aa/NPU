#include "user_api.h"

void UserAPI::setup_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/user/create").methods(crow::HTTPMethod::POST)([this](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("username") || !body.has("email") || !body.has("password")) {
            return crow::response(400, "Invalid JSON");
        }

        return crow::response(userManager.create_user(body["username"].s(), body["email"].s(), body["password"].s()));
    });

    CROW_ROUTE(app, "/user/get").methods(crow::HTTPMethod::GET)([this](const crow::request& req){
        auto params = crow::query_string(req.url_params);
        if (!params.has("id")) {
            return crow::response(400, "Missing user ID");
        }

        return crow::response(userManager.get_user(std::stoi(params.get("id"))));
    });

    CROW_ROUTE(app, "/user/update").methods(crow::HTTPMethod::POST)([this](const crow::request& req){
        auto params = crow::query_string(req.url_params);
        auto body = crow::json::load(req.body);

        if (!params.has("id")) {
            return crow::response(400, "Missing user ID");
        }

        if (!body || !body.has("username") || !body.has("email")) {
            return crow::response(400, "Invalid JSON");
        }

        return crow::response(userManager.update_user(std::stoi(params.get("id"), body["username"].s(), body["email"].s())));
    });

    CROW_ROUTE(app, "/user/delete").methods(crow::HTTPMethod::DELETE)([this](const crow::request& req){
        auto params = crow::query_string(req.url_params);
        if (!params.has("id")) {
            return crow::response(400, "Missing user ID");
        }

        return crow::response(userManager.delete_user(std::stoi(params.get("id"))));
    });

    CROW_ROUTE(app, "/user/login").methods(crow::HTTPMethod::POST)([this](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("email") || !body.has("password")) {
            return crow::response(400, "Invalid JSON");
        }

        return crow::response(userManager.authenticate_user(body["email"].s(), body["password"].s()));
    });
}