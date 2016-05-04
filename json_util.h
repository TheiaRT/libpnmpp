#ifndef JSON_UTIL_H
#define JSON_UTIL_H

#include "dist/jsoncpp/json/json.h"


std::string json_to_string(const Json::Value &root);
bool string_to_json(const std::string &in, Json::Value &root);

#endif
