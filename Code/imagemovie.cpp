#include "imagemovie.h"

// Constructor for ImageMovie
ImageMovie::ImageMovie(const QString& title, const QString& imagePath)
    : title(title), posterImage(new ProxyImage(imagePath)) {}

// Destructor to clean up allocated ProxyImage
ImageMovie::~ImageMovie() {
    delete posterImage;
}

// Method to display the movie poster using QLabel
void ImageMovie::displayPoster(QLabel* label) const {
    posterImage->display(label);
}
