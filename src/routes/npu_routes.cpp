// src/routes.cpp

#include "npu_routes.h"
#include "database.h"

void setup_npu_routes(crow::SimpleApp& app) {
    CROW_ROUTE(app, "/npu/upload").methods(crow::HTTPMethod::POST)([](const crow::request& req){
        auto body = crow::json::load(req.body);

        if (!body) {
            return crow::response(400, "Invalid JSON");
        }

        return crow::response(upload_npu(body));
    });

    CROW_ROUTE(app, "/npu/search").methods(crow::HTTPMethod::GET)([](const crow::request& req){
        auto params = crow::query_string(req.url_params);

        if (!params.has("element")) {
            return crow::response(400, "Missing element parameter");
        }

        return crow::response(search_npu(params.get("element")));
    });

    CROW_ROUTE(app, "/npu/rate").methods(crow::HTTPMethod::POST)([](const crow::request& req){
        auto body = crow::json::load(req.body);

        if (!body || !body.has("id") || !body.has("rating")) {
            return crow::response(400, "Invalid JSON");
        }

        return crow::response(rate_npu(body["id"].i(), body["rating"].i()));
    });
}

// EOF