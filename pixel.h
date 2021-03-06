#ifndef PIXEL_H
#define PIXEL_H

#include <iostream>

#include "dist/jsoncpp/json/json.h"
#include "json_util.h"


struct pixel_t {
    long r, g, b;

    pixel_t() {
        r = g = b = 0;
    }

    pixel_t(long r, long g, long b) : r(r), g(g), b(b) {
    }

    pixel_t operator+(const pixel_t &other) {
        return pixel_t(r + other.r, g + other.g, b + other.b);
    }

    pixel_t operator/(double scale) {
        return pixel_t(r / scale, g / scale, b / scale);
    }

    pixel_t operator/(int scale) {
        return *this / (double) scale;
    }

    pixel_t(Json::Value json_pixel) : r(json_pixel[0].asInt()),
                                      g(json_pixel[1].asInt()),
                                      b(json_pixel[2].asInt()) {
    }

    Json::Value to_json_value() {
        Json::Value json_pixel;
        json_pixel.append((int) r);
        json_pixel.append((int) g);
        json_pixel.append((int) b);
        return json_pixel;
    }

    std::string to_json() {
        return json_to_string(to_json_value());
    }

    static bool from_json(std::string json, pixel_t &res) {
        Json::Value root;
        Json::Reader reader;
        if (reader.parse(json, root, false)) {
            res = pixel_t(root);
            return true;
        }

        return false;
    }

    static pixel_t *from_json_value(Json::Value pixels_json,
                                    int width,
                                    int height) {
        pixel_t *pixels = new pixel_t[width * height];
        for (int i = 0; i < width * height; i++) {
            pixels[i] = pixel_t(pixels_json[i]);
        }

        return pixels;
    }
};

#endif
