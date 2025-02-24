#include "creation_manager.h"

crow::json::wvalue CreationManager::upload_creation(int user_id, const std::string& description, const std::string& element_name) {
    return creationDAO.upload_creation(user_id, description, element_name);
}

crow::json::wvalue CreationManager::score_creation(int creation_id, int score) {
    return creationDAO.score_creation(creation_id, score);
}

crow::json::wvalue CreationManager::search_creations(const std::string& element_name, int min_score) {
    return creationDAO.search_creations(element_name, min_score);
}