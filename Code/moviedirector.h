#ifndef MOVIEDIRECTOR_H
#define MOVIEDIRECTOR_H

#include "moviebuilder.h"

class MovieDirector
{
private:
    MovieBuilder builder; // MovieBuilder instance for creating movies

public:
    // Constructor: Initialize the director with a builder
    MovieDirector(const MovieBuilder& builder);

    // Example methods to construct specific types of movies
    TheMovies constructSportsMovie(); // Constructs a sports-themed movie
    TheMovies constructFamilyMovie(); // Constructs a family-themed movie
};

#endif // MOVIEDIRECTOR_H
