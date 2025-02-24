#include "creation_dao.h"
#include <iostream>

const std::string DB_CONN = "dbname=npu_db user=postgres password=yourpassword host=localhost";

crow::json::wvalue CreationDAO::upload_creation(int user_id, const std::string& description, const std::string& element_name) {
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        txn.exec_params("INSERT INTO creations (user_id, description, element_name) VALUES ($1, $2, $3);", user_id, description, element_name);
        txn.commit();

        return { {"message", "Creation uploaded successfully!"} };

    } catch (const std::exception &e) {

        return { {"error", e.what()} };

    }
}

crow::json::wvalue CreationDAO::score_creation(int creation_id, int score) {
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        txn.exec_params("INSERT INTO scores (creation_id, score) VALUES ($1, $2);", creation_id, score);
        txn.commit();

        return { {"message", "Score submitted successfully!"} };

    } catch (const std::exception &e) {

        return { {"error", e.what()} };

    }
}

crow::json::wvalue CreationDAO::search_creations(const std::string& element_name, int min_score) {
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        pqxx::result res = txn.exec_params("SELECT c.id, c.user_id, c.description FROM creations c LEFT JOIN scores s ON c.id = s.creation_id WHERE c.element_name = $1 GROUP BY c.id HAVING COALESCE(AVG(s.score), 0) >= $2;", element_name, min_score);

        crow::json::wvalue result;

        for (const auto& row : res) {
            crow::json::wvalue entry;
            entry["id"] = row["id"].as<int>();
            entry["user_id"] = row["user_id"].as<int>();
            entry["description"] = row["description"].as<std::string>();
            result["creations"].push_back(std::move(entry));
        }

        return result;

    } catch (const std::exception &e) {

        return { {"error", e.what()} };

    }
}
