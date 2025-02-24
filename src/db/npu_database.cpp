#include "npu_database.h"
#include <pqxx/pqxx>
#include <iostream>

const std::string DB_CONN = "dbname=npu_db user=postgres password=yourpassword host=localhost";

void init_db() {
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        txn.exec("CREATE TABLE IF NOT EXISTS npu (id SERIAL PRIMARY KEY, element TEXT, description TEXT, image_url TEXT, rating INTEGER DEFAULT 0);");
        txn.commit();
    } catch (const std::exception &e) {
        std::cerr << "Database error: " << e.what() << std::endl;
        exit(1);
    }
}

crow::json::wvalue upload_npu(const crow::json::rvalue& body) {
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        txn.exec_params("INSERT INTO npu (element, description, image_url) VALUES ($1, $2, $3);", body["element"].s(), body["description"].s(), body["image_url"].s());
        txn.commit();
        return { {"message", "NPU uploaded successfully!"} };
    } catch (const std::exception &e) {
        return { {"error", e.what()} };
    }
}

crow::json::wvalue search_npu(const std::string& element) {
    crow::json::wvalue result;
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        pqxx::result res = txn.exec_params("SELECT id, element, description, image_url, rating FROM npu WHERE element LIKE '%' || $1 || '%';", element);

        for (size_t i = 0; i < res.size(); ++i) {
            result[i]["id"] = res[i]["id"].as<int>();
            result[i]["element"] = res[i]["element"].as<std::string>();
            result[i]["description"] = res[i]["description"].as<std::string>();
            result[i]["image_url"] = res[i]["image_url"].as<std::string>();
            result[i]["rating"] = res[i]["rating"].as<int>();
        }
    } catch (const std::exception &e) {
        return { {"error", e.what()} };
    }
    return result;
}

crow::json::wvalue rate_npu(int id, int rating) {
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        txn.exec_params("UPDATE npu SET rating = rating + $1 WHERE id = $2;", rating, id);
        txn.commit();
        return { {"message", "Rating updated successfully!"} };
    } catch (const std::exception &e) {
        return { {"error", e.what()} };
    }
}
