#include "image.h"

#include <QPixmap>
#include <QDebug>

// RealImage class: Represents the actual image being loaded and displayed

// Constructor: Initialize the RealImage with the file path
RealImage::RealImage(const QString& path) : filePath(path) {
    loadFromResource(); // Simulate loading image during initialization
}

// Simulated method to load image from a resource
void RealImage::loadFromResource() const {
    qDebug() << "Loading Image From Resources File:" << filePath;
}

// Display method: Set the image on a QLabel
void RealImage::display(QLabel* label) const {
    QPixmap pix(filePath);
    if (pix.isNull()) {
        // If image loading fails
        qDebug() << "Failed To Load Image:" << filePath;
        label->clear();
    } else {
        // If successful, set image to QLabel
        label->setPixmap(pix);
    }
}

// ProxyImage class: Acts as a placeholder and delays RealImage loading

// Constructor: Store file path without loading the image yet
ProxyImage::ProxyImage(const QString& path) : filePath(path), realImage(nullptr) {}

// Destructor: Cleanup RealImage when ProxyImage is destroyed
ProxyImage::~ProxyImage() {
    delete realImage;
}

// Display method: Load and display RealImage only when required
void ProxyImage::display(QLabel* label) const {
    if (realImage == nullptr) {
        realImage = new RealImage(filePath); // Load the image when needed
    }
    realImage->display(label);
}
