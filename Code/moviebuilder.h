#ifndef MOVIEBUILDER_H
#define MOVIEBUILDER_H

#include "TheMovies.h"

// MovieBuilder: Builder class for constructing TheMovies objects
class MovieBuilder {
private:
    TheMovies movie; // Movie object being constructed

public:
    // Setter methods for updating movie attributes
    MovieBuilder& setName(const QString& nameOfMovie);
    MovieBuilder& setDate(const QString& dateOfMovie);
    MovieBuilder& setDirector(const QString& directorOfMovie);
    MovieBuilder& setLength(const QString& lengthOfMovie);
    MovieBuilder& setGenre(const QString& genreOfMovie);

    // Build and return the constructed movie object
    TheMovies buildMovie() const;
};

#endif // MOVIEBUILDER_H
