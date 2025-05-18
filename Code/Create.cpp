//Factory Pattern Implementation
#include "Create.h"

//Implementation for Favorites
QString Favorites::getName() {
    return "Favorites";
}

//Implementation for ToWatch
QString ToWatch::getName() {
    return "To Watch";
}

//Implementation for Diary
QString Diary::getName() {
    return "Diary";
}

//Implementation for FavoritesFactory
Create* FavoritesFactory::createList() {
    return new Favorites();
}

//Implementation for ToWatchFactory
Create* ToWatchFactory::createList() {
    return new ToWatch();
}

//Implementation for DiaryFactory
Create* DiaryFactory::createList() {
    return new Diary();
}
