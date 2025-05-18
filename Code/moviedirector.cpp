#include "moviedirector.h"

MovieDirector::MovieDirector(const MovieBuilder& builder) : builder(builder) {}

TheMovies MovieDirector::constructSportsMovie() {//Example change later
    return builder.setName("Fast & Furious")
    .setDate("2001-06-22")
        .setDirector("Rob Cohen")
        .setLength("106")
        .setGenre("Action")
        .buildMovie();
}

TheMovies MovieDirector::constructFamilyMovie() { //Example change later
    return builder.setName("Finding Nemo")
    .setDate("2003-05-30")
        .setDirector("Andrew Stanton")
        .setLength("100")
        .setGenre("Animation")
        .buildMovie();
}
