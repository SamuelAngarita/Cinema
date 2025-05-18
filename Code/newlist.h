#ifndef NEWLIST_H
#define NEWLIST_H

#include <QDialog>
#include <QStandardItemModel>

namespace Ui {
class NewList;
}

class NewList : public QDialog
{
    Q_OBJECT

public:
    // Constructor: Takes the list type and initializes
    explicit NewList(const QString &TheListType, QWidget *parent = nullptr);
    ~NewList();

    // Method to check if a string exists in the first column of the table
    bool isStringInFirstColumn(const QString &searchString);

private slots:
    void on_buttonBack_new_clicked(); // Slot for the back button click
    void on_buttonAdd_new_clicked();  // Slot for the add button click

private:
    Ui::NewList *ui;

    // Helper methods
    void initializeTable();      // Method to set up the table
    void addToCSV(const QString &item); // Append a new item to the CSV
    void ensureHeader(const QString &type); // Ensure proper header exists in the CSV file

    // Member variables
    QStandardItemModel *model;   // Table model for UI
    QString csvFilePath;         // Path to the CSV file
    QString currentHeader;       // The header of the current list
    QStringList currentList;     // Data of the current list
    QString ListType;            // The type of list (e.g., Favorites)
};

#endif // NEWLIST_H
