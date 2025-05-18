#ifndef IMAGE_H
#define IMAGE_H

#include <QLabel>
#include <QString>

// Base class: Image (Abstract class with virtual methods)
class Image
{
public:
    virtual void display(QLabel* label) const = 0; // Pure virtual method to display an image
    virtual ~Image() = default;                   // Virtual destructor
};

// RealImage: Represents the actual image
class RealImage : public Image {
private:
    QString filePath; // File path for the image

    void loadFromResource() const; // Internal method to load the image

public:
    explicit RealImage(const QString& path);  // Constructor to initialize file path
    void display(QLabel* label) const override; // Override to display the image
};

// ProxyImage: A proxy class that defers loading RealImage
class ProxyImage : public Image {
private:
    QString filePath;            // File path for the image
    mutable RealImage* realImage; // Lazily initialized RealImage object

public:
    explicit ProxyImage(const QString& path); // Constructor
    ~ProxyImage() override;                   // Destructor to clean up RealImage

    void display(QLabel* label) const override; // Override to display the image
};

#endif // IMAGE_H
