#include "moviesgui_search.h"
#include "ui_moviesgui_search.h"
#include "moviesgui_display.h"
#include <QStandardItemModel>
#include <QtCore>

// Constructor: Initializes the UI and loads the movie data from a CSV file into a table.
MoviesGUI_Search::MoviesGUI_Search(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MoviesGUI_Search)
{
    ui->setupUi(this);

    // Open the CSV file containing movie information
    QFile file(":/data/MoviesInfo.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed To Open CSV File.";
        return;
    }

    QTextStream stream(&file);

    // Read all lines from the file to get the movie list
    QStringList lines;
    while (!stream.atEnd()) {
        lines.append(stream.readLine());
    }
    file.close();

    // Check if the file is empty
    if (lines.isEmpty()) {
        qDebug() << "The File Is Empty.";
        return;
    }

    // Create a model to display movies in the table
    QStandardItemModel *model = new QStandardItemModel(lines.size(), 1, this);
    model->setHorizontalHeaderLabels({"Movies"});

    // Populate the model with movie titles from the first column
    for (int row = 0; row < lines.size(); ++row) {
        QStringList fields = lines[row].split(','); // Split by comma
        QString firstElement = fields.isEmpty() ? "" : fields.at(0).trimmed();
        QStandardItem *item = new QStandardItem(firstElement);
        model->setItem(row, 0, item);
    }

    // Display the movie list in the table view
    ui->tableView_movies->setModel(model);
    ui->tableView_movies->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    // Remove gridlines for a cleaner appearance
    ui->tableView_movies->setShowGrid(false);
}

// Destructor: Cleans up the UI
MoviesGUI_Search::~MoviesGUI_Search()
{
    delete ui;
}

// Back Button: Returns to the parent window
void MoviesGUI_Search::on_buttonBack_movies_clicked()
{
    if (parentWidget()) {
        parentWidget()->show(); // Show the parent window
    }
    this->close(); // Close the current window
}

// Search Button: Searches for a movie title in the file
void MoviesGUI_Search::on_buttonSearch_movies_clicked()
{
    QString usermovie = ui->lineEdit_movies->text();

    // Check if the movie exists in the file
    if (isStringInFirstColumn(usermovie)) {
        // Open the movie display window
        MoviesGUI_Display *themovieWindow = new MoviesGUI_Display(usermovie, this);
        themovieWindow->show();

        // Hide the search window
        this->hide();
    } else {
        qDebug() << usermovie << "is not in the system.";
    }
}

// Helper Function: Checks if a string (movie title) exists in the first column of the file
bool MoviesGUI_Search::isStringInFirstColumn(const QString &searchString)
{
    QFile file(":/data/MoviesInfo.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed To Open CSV File.";
        return false;
    }

    QTextStream stream(&file);

    // Loop through each line and check the first column for the string
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(',');

        if (!fields.isEmpty() && fields.at(0).trimmed() == searchString) {
            file.close();
            return true; // Movie found
        }
    }

    file.close();
    return false; // Movie not found
}
