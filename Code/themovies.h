#ifndef THEMOVIES_H
#define THEMOVIES_H

#include <QString>
#include <iostream>


class TheMovies {

public:
    // Member variables
    QString name;
    QString releaseDate;
    QString director;
    QString length; // Maybe change to int later
    QString genre;

    // Default constructor
    TheMovies();

    // Parameterized constructor
    TheMovies(const QString& name, const QString& releaseDate,const QString& director, const QString& length, const QString& genre);


    // Display movie details
    void showMovie() const;
};

#endif // THEMOVIES_H

