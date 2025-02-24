#ifndef CREATION_MANAGER_H
#define CREATION_MANAGER_H
#include "creation_dao.h"

class CreationManager {
public:
    crow::json::wvalue upload_creation(int user_id, const std::string& description, const std::string& element_name);
    crow::json::wvalue score_creation(int creation_id, int score);
    crow::json::wvalue search_creations(const std::string& element_name, int min_score);
private:
    CreationDAO creationDAO;
};
#endif