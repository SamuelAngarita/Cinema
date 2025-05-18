#include "lists.h"
#include "ui_lists.h"
#include <QStringList>
#include <QStandardItemModel>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "newlist.h"
#include "Create.h"

// Constructor: Initializes the UI and reads the data from the CSV file
Lists::Lists(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Lists)
{
    ui->setupUi(this);

    QFile file("Lists.csv"); // File containing lists

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);

        fileLines.clear(); // Clear any existing lines
        while (!stream.atEnd()) {
            fileLines.append(stream.readLine()); // Append each line from the file
        }
        file.close();

        if (!fileLines.isEmpty()) {
            currentIndex = 0; // Start at the first line
            displayLine(currentIndex); // Display the first list
        } else {
            qDebug() << "The file is empty.";
        }
    } else {
        qDebug() << "Failed to open file for reading.";
    }
}

// Destructor: Cleans up the UI memory
Lists::~Lists()
{
    delete ui;
}

// Back button: Closes the current window and returns to the main window
void Lists::on_buttonBack_lists_clicked()
{
    if (parentWidget()) {
        parentWidget()->show(); // Show the parent window
    }
    this->close(); // Close the current window
}

// Next button: Displays the next list if it exists
void Lists::on_buttonNext_lists_clicked()
{
    if (currentIndex + 1 < fileLines.size()) {
        currentIndex++; // Move to the next line
        displayLine(currentIndex); // Display the list
    } else {
        qDebug() << "There is no next list.";
    }
}

// Previous button: Displays the previous list if it exists
void Lists::on_buttonPrevious_lists_clicked()
{
    if (currentIndex - 1 >= 0) {
        currentIndex--; // Move to the previous line
        displayLine(currentIndex); // Display the list
    } else {
        qDebug() << "There is no previous list.";
    }
}

// Helper function: Displays a specific line (list) in the table view
void Lists::displayLine(int index)
{
    if (index < 0 || index >= fileLines.size()) {
        qDebug() << "Index out of bounds.";
        return;
    }

    QString line = fileLines.at(index).trimmed(); // Get the specific line
    if (line.isEmpty()) {
        qDebug() << "The line is empty.";
        return;
    }

    QStringList fields = line.split(',', Qt::SkipEmptyParts); // Split the line into parts
    if (fields.isEmpty()) {
        qDebug() << "No valid data in the line.";
        return;
    }

    QString header = fields.takeFirst(); // The first part is the header
    QStringList dataRows = fields; // Remaining parts are data rows

    QStandardItemModel *model = new QStandardItemModel(dataRows.size(), 1, this);
    model->setHorizontalHeaderLabels({header}); // Set the table header

    QFont headerFont("Arial", 16, QFont::Bold);
    ui->tableDisplayLists_lists->horizontalHeader()->setFont(headerFont);

    // Populate the table rows
    QFont rowFont("Arial", 12);
    for (int row = 0; row < dataRows.size(); ++row) {
        QStandardItem *item = new QStandardItem(dataRows.at(row).trimmed());
        item->setFont(rowFont);
        model->setItem(row, 0, item);
    }

    ui->tableDisplayLists_lists->setModel(model); // Set the model for the table view

    // Resize table to fit data
    ui->tableDisplayLists_lists->verticalHeader()->setDefaultSectionSize(
        ui->tableDisplayLists_lists->height() / (dataRows.size() + 1));
    ui->tableDisplayLists_lists->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

// Create Favorites list and open a new list window
void Lists::on_buttonCreate_lists_clicked()
{
    FavoritesFactory favoritesFactory;
    Create* favorites = favoritesFactory.createList();

    NewList *newlistWindow = new NewList(favorites->getName(), this);
    newlistWindow->show();
    this->hide();
}

// Create "To Watch" list and open a new list window
void Lists::on_buttonCreate_lists_2_clicked()
{
    ToWatchFactory toWatchFactory;
    Create* toWatch = toWatchFactory.createList();

    NewList *newlistWindow = new NewList(toWatch->getName(), this);
    newlistWindow->show();
    this->hide();
}

// Create Diary list and open a new list window
void Lists::on_buttonCreate_lists_3_clicked()
{
    DiaryFactory diaryFactory;
    Create* diary = diaryFactory.createList();

    NewList *newlistWindow = new NewList(diary->getName(), this);
    newlistWindow->show();
    this->hide();
}

// Reload button: Reloads the Lists window
void Lists::on_buttonReload_lists_clicked()
{
    Lists *reloadedWindow = new Lists(this->parentWidget());
    reloadedWindow->show();
    this->close();
}
