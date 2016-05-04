#include <iostream>
#include <sstream>

#include "json_util.h"


std::string json_to_string(const Json::Value &root) {
    Json::StreamWriterBuilder builder;
    /* Strip whitespace from output to reduce size. */
    builder.settings_["indentation"] = "";
    std::string out = Json::writeString(builder, root);
    return out;
}

bool string_to_json(const std::string &in, Json::Value &root) {
    Json::CharReaderBuilder builder;
    Json::CharReader *reader = builder.newCharReader();
    std::string errs;
    const char *in_s = in.c_str();
    if (reader->parse(in_s, in_s + in.size(), &root, &errs) == false) {
        delete reader;
        return false;
    }

    delete reader;
    return true;
}
