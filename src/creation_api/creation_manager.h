#ifndef CREATION_MANAGER_H
#define CREATION_MANAGER_H
#include "creation_dao.h"

class CreationManager {
public:
    crow::json::wvalue create_creation(int user_id, const std::string& description, const std::string& element_name);
    crow::json::wvalue get_creation(int user_id, int creation_id);
    crow::json::wvalue update_creation(int user_id, int creation_id, const std::string& description, const std::string& element_name);
    crow::json::wvalue delete_creation(int user_id, int creation_id);

    crow::json::wvalue score_creation(int creation_id, int score);
    crow::json::wvalue search_creations(const std::string& element_name, int min_score);
private:
    CreationDAO creationDAO;
};
#endif