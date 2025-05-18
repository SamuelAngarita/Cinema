#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCore> // Include Qt core headers for additional functionality

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

// MainWindow: Represents the main window of the application
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor and destructor
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_buttonMovies_clicked(); // Slot for Movies button click
    void on_buttonLists_clicked();  // Slot for Lists button click

private:
    Ui::MainWindow *ui; // UI reference
};

#endif // MAINWINDOW_H
