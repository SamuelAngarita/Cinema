#ifndef MOVIESGUI_DISPLAY_H
#define MOVIESGUI_DISPLAY_H

#include <QDialog>

namespace Ui {
class MoviesGUI_Display;
}

class MoviesGUI_Display : public QDialog
{
    Q_OBJECT

public:
    // Constructor: Takes a movie name and parent widget
    explicit MoviesGUI_Display(const QString &movieName, QWidget *parent = nullptr);
    ~MoviesGUI_Display();

private slots:
    void on_buttonBack_themovie_clicked(); // Slot for back button click
    void on_buttonRating_themovie_clicked(); // Slot for rating button click

private:
    void loadAverageRating(); // Load and display the average movie rating

    Ui::MoviesGUI_Display *ui; // UI reference
    QString m_movieName;       // Movie name for display purposes
};

#endif // MOVIESGUI_DISPLAY_H
