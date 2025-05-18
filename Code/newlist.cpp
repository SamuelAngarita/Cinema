#include "newlist.h"
#include "ui_newlist.h"
#include <QStandardItemModel>
#include <QtCore>

// Constructor for the NewList class
NewList::NewList(const QString &TheListType, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NewList)
    , model(new QStandardItemModel(this))
    , csvFilePath("Lists.csv") // File path for storing lists
    , ListType(TheListType)    // Type of list to manage
{
    ui->setupUi(this); // Sets up the UI elements

    // Open the MoviesInfo CSV file for reading
    QFile file(":/data/MoviesInfo.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed To Open CSV File.";
        return;
    }
    qDebug() << "FILE IS OPEN";

    QTextStream stream(&file);

    // Read all lines from the file to determine row count
    QStringList lines;
    while (!stream.atEnd()) {
        lines.append(stream.readLine());
    }
    file.close();

    if (lines.isEmpty()) {
        qDebug() << "The File Is Empty.";
        return;
    }

    // Create a model with rows equal to the number of CSV lines
    QStandardItemModel *model = new QStandardItemModel(lines.size(), 1, this);
    model->setHorizontalHeaderLabels({"Movies"}); // Set column header

    // Populate the model with the first column of each CSV row
    for (int row = 0; row < lines.size(); ++row) {
        QStringList fields = lines[row].split(','); // Split line by comma
        QString firstElement = fields.isEmpty() ? "" : fields.at(0).trimmed();
        QStandardItem *item = new QStandardItem(firstElement);
        model->setItem(row, 0, item);
    }

    // Display the model in the tableView
    ui->tableViewAllMovies_new->setModel(model);
    ui->tableViewAllMovies_new->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);

    ensureHeader(ListType); // Ensure CSV file has a proper header
    initializeTable();      // Initialize the table with existing list data
}

// Destructor for the NewList class
NewList::~NewList()
{
    delete ui; // Clean up UI resources
}

// Back button handler: closes the current window and shows the parent window
void NewList::on_buttonBack_new_clicked()
{
    if (parentWidget()) {
        parentWidget()->show(); // Show the parent window (main window)
    }
    this->close(); // Close this dialog
}

// Function to check if a string exists in the first column of the CSV file
bool NewList::isStringInFirstColumn(const QString &searchString)
{
    QFile file(":/data/MoviesInfo.csv");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed To Open CSV File.";
        return false;
    }

    QTextStream stream(&file);

    // Iterate through each line and check the first column
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(',');

        if (!fields.isEmpty() && fields.at(0).trimmed() == searchString) {
            file.close();
            return true; // Match found
        }
    }

    file.close();
    return false; // No match found
}

// Add button handler: adds a user input movie to the list if it's in the system
void NewList::on_buttonAdd_new_clicked()
{
    QString usermovie = ui->lineEdit_new->text(); // Get user input

    if (isStringInFirstColumn(usermovie)) {
        // If the movie exists in the system, add it to the list
        QString newItem = usermovie;

        if (newItem.isEmpty()) {
            return; // Do nothing if input is empty
        }

        QStandardItem *item = new QStandardItem(newItem);
        model->appendRow(item); // Append the item to the model

        addToCSV(newItem); // Add the movie to the CSV file
    } else {
        qDebug() << usermovie << "Is Not In The System."; // Input movie not found
    }
}

// Initialize the table with the last list saved in the CSV file
void NewList::initializeTable()
{
    QFile file(csvFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading.";
        return;
    }

    QTextStream stream(&file);
    QString lastLine;

    // Read until the last line in the file
    while (!stream.atEnd()) {
        lastLine = stream.readLine().trimmed();
    }
    file.close();

    // If the last line has data, parse it
    if (!lastLine.isEmpty()) {
        currentList = lastLine.split(',', Qt::SkipEmptyParts);

        if (!currentList.isEmpty()) {
            currentHeader = currentList.takeFirst(); // Extract header
        }

        model->clear(); // Clear previous table data
        model->setHorizontalHeaderLabels({currentHeader});

        // Populate the table with list items
        for (const QString &item : currentList) {
            model->appendRow(new QStandardItem(item));
        }
    }

    // Display the model in the tableView
    ui->tableViewNewList_new->setModel(model);
    ui->tableViewNewList_new->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
}

// Add a new item to the last line of the CSV file
void NewList::addToCSV(const QString &item)
{
    QFile file(csvFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open file for reading.";
        return;
    }

    // Read all lines into a list
    QTextStream stream(&file);
    QStringList lines;
    while (!stream.atEnd()) {
        lines.append(stream.readLine());
    }
    file.close();

    if (!lines.isEmpty()) {
        // Append the new item to the last line
        lines.last() += "," + item;
    }

    // Write the updated lines back to the file
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream writeStream(&file);
        for (const QString &line : lines) {
            writeStream << line << "\n";
        }
    }
    file.close();
}

// Ensure the file has a proper header; add it if it’s missing
void NewList::ensureHeader(const QString &type)
{
    QFile file(csvFilePath);
    QTextStream stream(&file);
    QString lastLine;

    // Read until the last line
    while (!stream.atEnd()) {
        lastLine = stream.readLine().trimmed();
    }
    file.close();

    // Add the header if it’s not already there
    if (lastLine != type) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text)) {
            QTextStream writeStream(&file);
            writeStream << type << "\n"; // Write the new header
        }
        file.close();
    }
}
