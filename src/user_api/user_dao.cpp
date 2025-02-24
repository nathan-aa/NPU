#include "user_dao.h"
#include <bcrypt/BCrypt.hpp>
#include <iostream>

const std::string DB_CONN = "dbname=npu_db user=postgres password=yourpassword host=localhost";

crow::json::wvalue UserDAO::create_user(const std::string& username, const std::string& email, const std::string& hashed_password) {
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        txn.exec_params("INSERT INTO users (username, email, password) VALUES ($1, $2, $3);", username, email, hashed_password);
        txn.commit();

        return { {"message", "User created successfully!"} };

    } catch (const std::exception &e) {

        return { {"error", e.what()} };

    }
}

crow::json::wvalue UserDAO::get_user(int id) {
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        pqxx::result res = txn.exec_params("SELECT id, username, email FROM users WHERE id = $1;", id);

        if (res.empty()) {
            return { {"error", "User not found"} };
        }

        return { {"id", res[0]["id"].as<int>()}, {"username", res[0]["username"].as<std::string>()}, {"email", res[0]["email"].as<std::string>()} };

    } catch (const std::exception &e) {

        return { {"error", e.what()} };

    }
}

crow::json::wvalue UserDAO::update_user(int id) {
    // Not implemented
}


crow::json::wvalue UserDAO::delete_user(int id) {
    // Not implemented
}

crow::json::wvalue UserDAO::authenticate_user(const std::string& email, const std::string& password) {
    try {
        pqxx::connection conn(DB_CONN);
        pqxx::work txn(conn);
        pqxx::result res = txn.exec_params("SELECT password FROM users WHERE email = $1;", email);

        if (res.empty()) {
            return { {"error", "Invalid email or password"} };
        }

        std::string stored_hash = res[0]["password"].as<std::string>();
        if (!BCrypt::validatePassword(password, stored_hash)) {
            return { {"error", "Invalid email or password"} };
        }

        return { {"message", "Login successful!"} };

    } catch (const std::exception &e) {

        return { {"error", e.what()} };

    }
}
