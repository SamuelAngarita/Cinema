#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "lists.h"
#include "moviesgui_search.h"

// Constructor: Initializes the UI components
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// Destructor: Cleans up the UI memory
MainWindow::~MainWindow()
{
    delete ui;
}

// Opens the Movies window and hides the MainWindow
void MainWindow::on_buttonMovies_clicked()
{
    MoviesGUI_Search *moviesWindow = new MoviesGUI_Search(this); // Create Movies window
    moviesWindow->show(); // Show the Movies window
    this->hide(); // Hide the MainWindow
}

// Opens the Lists window and hides the MainWindow
void MainWindow::on_buttonLists_clicked()
{
    Lists *listsWindow = new Lists(this); // Create Lists window
    listsWindow->show(); // Show the Lists window
    this->hide(); // Hide the MainWindow
}
