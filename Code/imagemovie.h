#ifndef IMAGEMOVIE_H
#define IMAGEMOVIE_H

#include "image.h"

// ImageMovie: Represents a movie with a title and poster image
class ImageMovie
{
public:
    QString title;     // Movie title
    Image* posterImage; // Pointer to an Image (Proxy or Real)

    // Constructor: Initializes movie title and poster image path
    ImageMovie(const QString& title, const QString& imagePath);

    // Destructor: Cleans up the poster image
    ~ImageMovie();

    // Display the poster image on a QLabel
    void displayPoster(QLabel* label) const;
};

#endif // IMAGEMOVIE_H
