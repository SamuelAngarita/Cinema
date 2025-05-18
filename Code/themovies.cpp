#include "TheMovies.h"

// Default constructor
TheMovies::TheMovies()
    : name(""), releaseDate(""), director(""), length(""), genre("") {}

// Parameterized constructor
TheMovies::TheMovies(const QString& name, const QString& releaseDate, const QString& director, const QString& length, const QString& genre)
    : name(name), releaseDate(releaseDate), director(director), length(length), genre(genre) {}

// Display movie details
void TheMovies::showMovie() const {
    std::cout << name.toStdString() << " released in " << releaseDate.toStdString() << ", directed by " << director.toStdString()
              << ". Length: " << length.toStdString() << " mins, Genre: " << genre.toStdString() << std::endl;
}
