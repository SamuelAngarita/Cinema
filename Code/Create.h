//Factory Pattern Classes and Implementations
#ifndef CREATE_H
#define CREATE_H

#include <QString> // Include QString header for string handling

// Abstract base class for creating lists
class Create {
public:
    virtual QString getName() = 0; // Pure virtual function to get the name of the list
    virtual ~Create() {}           // Virtual destructor
};

// Derived class: Favorites list
class Favorites : public Create {
public:
    QString getName() override; // Override to return the name of the list ("Favorites")
};

// Derived class: ToWatch list
class ToWatch : public Create {
public:
    QString getName() override; // Override to return the name of the list ("To Watch")
};

// Derived class: Diary list
class Diary : public Create {
public:
    QString getName() override; // Override to return the name of the list ("Diary")
};

// Abstract factory class for creating lists
class CreateFactory {
public:
    virtual Create* createList() = 0; // Factory method to create a list
    virtual ~CreateFactory() {}       // Virtual destructor
};

// Factory class for Favorites list
class FavoritesFactory : public CreateFactory {
public:
    Create* createList() override; // Create and return a Favorites list
};

// Factory class for ToWatch list
class ToWatchFactory : public CreateFactory {
public:
    Create* createList() override; // Create and return a ToWatch list
};

// Factory class for Diary list
class DiaryFactory : public CreateFactory {
public:
    Create* createList() override; // Create and return a Diary list
};

#endif // CREATE_H
