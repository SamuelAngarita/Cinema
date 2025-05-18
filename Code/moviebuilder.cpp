#include "MovieBuilder.h"

// Sets the name of the movie and returns the builder object
MovieBuilder& MovieBuilder::setName(const QString& nameOfMovie) {
    movie.name = nameOfMovie;
    return *this;
}

// Sets the release date of the movie and returns the builder object
MovieBuilder& MovieBuilder::setDate(const QString& dateOfMovie) {
    movie.releaseDate = dateOfMovie;
    return *this;
}

// Sets the director's name and returns the builder object
MovieBuilder& MovieBuilder::setDirector(const QString& directorOfMovie) {
    movie.director = directorOfMovie;
    return *this;
}

// Sets the length/duration of the movie and returns the builder object
MovieBuilder& MovieBuilder::setLength(const QString& lengthOfMovie) {
    movie.length = lengthOfMovie;
    return *this;
}

// Sets the genre of the movie and returns the builder object
MovieBuilder& MovieBuilder::setGenre(const QString& genreOfMovie) {
    movie.genre = genreOfMovie;
    return *this;
}

// Builds and returns the fully constructed movie object
TheMovies MovieBuilder::buildMovie() const {
    return movie; // Return a copy of the constructed movie
}
