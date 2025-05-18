#include "moviesgui_display.h"
#include "ui_moviesgui_display.h"
#include "moviebuilder.h"
#include <QPixmap> // For handling images
#include "imagemovie.h"
#include <QtCore>
#include <QString>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

// Constructor: Displays movie details using the movie name
MoviesGUI_Display::MoviesGUI_Display(const QString &movieName, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MoviesGUI_Display)
    , m_movieName(movieName)
{
    ui->setupUi(this);

    // Open the movie information file
    QFile file(":/data/MoviesInfo.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed To Open CSV File.";
    }

    QTextStream stream(&file);
    QString posterfile;

    // Search for the selected movie in the file
    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(',');

        if (!fields.isEmpty() && fields[0] == m_movieName) {
            // Build the movie details
            MovieBuilder builder;
            TheMovies LoadMovie = builder.setName(fields[0])
                                      .setDate(fields[1])
                                      .setDirector(fields[2])
                                      .setLength(fields[3])
                                      .setGenre(fields[4])
                                      .buildMovie();

            // Set movie details to labels
            ui->labelTitle_themovie->setText(fields[0]);
            ui->labelDirector_themovie->setText("Director: " + fields[2]);
            ui->labelDate_themovie->setText("Release Date : " + fields[1]);
            ui->labelLength_themovie->setText("Movie Length: " + fields[3]);
            ui->labelGenre_themovie->setText("Genre: " + fields[4]);

            posterfile = fields[5]; // Image filename
            break;
        }
    }
    file.close();

    // Load and display the movie poster
    ImageMovie poster("Poster", ":/images/" + posterfile);
    poster.displayPoster(ui->labelPic_themovie);

    // Populate the rating combo box
    ui->comboBoxRating_themovie->addItems({"5", "4", "3", "2", "1", "0"});

    loadAverageRating(); // Load and display average rating
}

// Destructor: Cleans up the UI
MoviesGUI_Display::~MoviesGUI_Display()
{
    delete ui;
}

// Back Button: Returns to the previous window
void MoviesGUI_Display::on_buttonBack_themovie_clicked()
{
    if (parentWidget()) {
        parentWidget()->show();
    }
    this->close();
}

// Rating Button: Adds a rating for the movie to a CSV file
void MoviesGUI_Display::on_buttonRating_themovie_clicked()
{
    QString selectedRating = ui->comboBoxRating_themovie->currentText();
    int rating = selectedRating.toInt();

    QFile file("Ratings.csv");

    // Read existing ratings
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open Ratings.csv.";
        return;
    }

    QTextStream stream(&file);
    QStringList lines;
    while (!stream.atEnd()) {
        lines.append(stream.readLine());
    }
    file.close();

    // Update the rating for the current movie
    bool movieFound = false;
    for (int i = 0; i < lines.size(); ++i) {
        QStringList fields = lines[i].split(',');
        if (!fields.isEmpty() && fields[0] == m_movieName) {
            fields.append(QString::number(rating));
            lines[i] = fields.join(',');
            movieFound = true;
            break;
        }
    }

    if (!movieFound) {
        lines.append(m_movieName + "," + QString::number(rating));
    }

    // Write updated ratings back to the file
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "Failed to write to Ratings.csv.";
        return;
    }

    QTextStream out(&file);
    for (const QString &line : lines) {
        out << line << "\n";
    }
    file.close();

    loadAverageRating(); // Refresh the average rating
}

// Loads and calculates the average rating for the current movie
void MoviesGUI_Display::loadAverageRating()
{
    QFile file("Ratings.csv");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Failed to open Ratings.csv.";
        return;
    }

    QTextStream stream(&file);

    while (!stream.atEnd()) {
        QString line = stream.readLine();
        QStringList fields = line.split(',');

        if (!fields.isEmpty() && fields[0] == m_movieName) {
            int sum = 0;
            int count = 0;

            // Calculate the average rating
            for (int i = 1; i < fields.size(); ++i) {
                bool ok;
                int rating = fields[i].toInt(&ok);
                if (ok) {
                    sum += rating;
                    ++count;
                }
            }

            if (count > 0) {
                double average = static_cast<double>(sum) / count;
                ui->labelRating_themovie->setText(QString("Average Rating: %1").arg(average, 0, 'f', 1));
            } else {
                ui->labelRating_themovie->setText("No ratings available.");
            }
            break;
        }
    }
    file.close();
}
