#include <fstream>

#include "pnm_image.h"

PnmImage::PnmImage(size_t width, size_t height, long denom) {
    init(width, height, denom);
}

PnmImage::PnmImage(size_t width, size_t height) {
    init(width, height, 255);
}

PnmImage::~PnmImage() {
    delete [] pixels;
}

void PnmImage::init(size_t width, size_t height, long denom) {
    this->width = width;
    this->height = height;
    this->denominator = denom;

    this->pixels = new pixel_t[width * height];
}

PnmImage PnmImage::read(FILE *fp) {
    /* read from file tho */
    return PnmImage(100, 100, 255);
}

bool PnmImage::write(std::string filename) const {
    FILE *fp = fopen(filename.c_str(), "w+");
    bool res = write(fp);
    fclose(fp);
    return res;
}

bool PnmImage::write(FILE *fp) const {
    if (fp == NULL) {
        return false;
    }

    fprintf(fp, "P3\n");
    fprintf(fp, "%lu %lu\n", width, height);
    fprintf(fp, "%lu\n", denominator);
    for (size_t i = 0; i < height * width; i++) {
        pixel_t pix = pixels[i];
        fprintf(fp, " %lu %lu %lu", pix.r, pix.g, pix.b);
        if (i % height == 0) {
            fprintf(fp, "\n");
        }
    }

    return true;
}

bool PnmImage::set_pixel(size_t x, size_t y, pixel_t pixel) {
    if (x >= width || y >= height) {
        return false;
    }

    if (pixels == NULL) {
        return false;
    }

    pixels[y * width + x] = pixel;
    return true;
}

pixel_t PnmImage::get_pixel(size_t x, size_t y) const {
    return pixels[y * width + x];
}

pixel_t *PnmImage::get_pixels() const {
    return pixels;
}

size_t PnmImage::get_width() const {
    return width;
}

size_t PnmImage::get_height() const {
    return height;
}

void PnmImage::insert_chunk(pixel_t *chunk,
                            size_t startx,
                            size_t starty,
                            size_t width,
                            size_t height) {
    for (size_t x = 0; x < width; x++) {
        for (size_t y = 0; y < height; y++) {
            set_pixel(x + startx, y + starty, chunk[y * width + x]);
        }
    }
}

long PnmImage::get_denominator() const {
    return denominator;
}

void PnmImage::map(map_function f) {
    for (size_t y = 0; y < height; y++) {
        for (size_t x = 0; x < width; x++) {
            pixels[y * width + x] = f(this, pixels[y * width + x], x, y);
        }
    }
}
