#ifndef CREATION_DAO_H
#define CREATION_DAO_H
#include "crow.h"
#include <pqxx/pqxx>

class CreationDAO {
public:
    crow::json::wvalue upload_creation(int user_id, const std::string& description, const std::string& element_name);
    crow::json::wvalue score_creation(int creation_id, int score);
    crow::json::wvalue search_creations(const std::string& element_name, int min_score);
};
#endif