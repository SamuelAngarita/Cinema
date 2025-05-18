#ifndef LISTS_H
#define LISTS_H

#include <QDialog>
#include <QStringList>

namespace Ui {
class Lists;
}

// Lists: Represents a dialog for managing different lists
class Lists : public QDialog
{
    Q_OBJECT

public:
    // Constructor and destructor
    explicit Lists(QWidget *parent = nullptr);
    ~Lists();

private slots:
    void on_buttonBack_lists_clicked();      // Slot for back button click
    void on_buttonPrevious_lists_clicked();  // Slot for navigating to the previous list
    void on_buttonNext_lists_clicked();      // Slot for navigating to the next list
    void on_buttonCreate_lists_clicked();    // Slot for creating a new list
    void on_buttonCreate_lists_2_clicked();  // Slot for an alternate create button (2)
    void on_buttonCreate_lists_3_clicked();  // Slot for an alternate create button (3)
    void on_buttonReload_lists_clicked();    // Slot for reloading the list

private:
    void displayLine(int index);  // Helper method to display a specific line in the list

    QStringList fileLines;        // Stores all lines from the CSV file
    int currentIndex = -1;        // Tracks the current index (-1 means no line is loaded)

    Ui::Lists *ui;                // UI reference
};

#endif // LISTS_H
