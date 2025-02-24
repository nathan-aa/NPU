#ifndef DATABASE_H
#define DATABASE_H
#include "crow.h"
void init_db();
crow::json::wvalue upload_npu(const crow::json::rvalue& body);
crow::json::wvalue search_npu(const std::string& element);
crow::json::wvalue rate_npu(int id, int rating);
#endif