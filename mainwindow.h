#pragma once

#include <QMainWindow>
#include <QFileDialog>

#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

#include <memory>

static const QString loadAction = "Load image";
static const QString saveAction = "Save image";
static const QString settingsAction = "Settings";
static const QString reprocessAction = "Reprocess";
static const QString histogramAction = "Histogram";

namespace cv {
    class Mat;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    void setupToolBar();

    void setupStatusBar();

    void scanImageAndIncrease(cv::Mat& image);

    std::unique_ptr<cv::Mat> xImage;

    QLabel positionLabel;
    QLabel imageSizeLabel;
};
