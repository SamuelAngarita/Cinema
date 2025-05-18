#ifndef MOVIESGUI_SEARCH_H
#define MOVIESGUI_SEARCH_H

#include <QDialog>

namespace Ui {
class MoviesGUI_Search;
}

class MoviesGUI_Search : public QDialog
{
    Q_OBJECT

public:
    // Constructor: Initialize the Movies search window
    explicit MoviesGUI_Search(QWidget *parent = nullptr);
    ~MoviesGUI_Search();

    // Check if a specific string exists in the table's first column
    bool isStringInFirstColumn(const QString &searchString);

private slots:
    void on_buttonBack_movies_clicked();  // Slot for the back button click
    void on_buttonSearch_movies_clicked(); // Slot for the search button click

private:
    Ui::MoviesGUI_Search *ui; // UI reference
};

#endif // MOVIESGUI_SEARCH_H
