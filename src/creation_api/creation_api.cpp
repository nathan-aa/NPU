#include "creation_api.h"

void CreationAPI::setup_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/creation/create").methods(crow::HTTPMethod::POST)([this](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("user_id") || !body.has("description") || !body.has("element_name")) {
            return crow::response(400, "Invalid JSON");
        }

        return crow::response(creationManager.create_creation(body["user_id"].i(), body["description"].s(), body["element_name"].s()));
    });


    CROW_ROUTE(app, "/creation/update").methods(crow::HTTPMethod::PUT)([this](const crow::request& req){
        // Not Implemented
    });

    CROW_ROUTE(app, "/creation/delete").methods(crow::HTTPMethod::DELETE)([this](const crow::request& req){
        // Not Implemented
    });

    CROW_ROUTE(app, "/creation/score").methods(crow::HTTPMethod::POST)([this](const crow::request& req){
        auto body = crow::json::load(req.body);
        if (!body || !body.has("creation_id") || !body.has("score")) {
            return crow::response(400, "Invalid JSON");
        }

        return crow::response(creationManager.score_creation(body["creation_id"].i(), body["score"].i()));
    });

    CROW_ROUTE(app, "/creation/search").methods(crow::HTTPMethod::GET)([this](const crow::request& req){
        auto params = crow::query_string(req.url_params);
        if (!params.has("element_name")) {
            return crow::response(400, "Missing element name");
        }

        int min_score = params.has("min_score") ? std::stoi(params.get("min_score")) : 0;

        return crow::response(creationManager.search_creations(params.get("element_name"), min_score));
    });
}