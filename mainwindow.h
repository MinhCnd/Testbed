#pragma once

#include <QMainWindow>
#include <QFileDialog>

#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

static const QString loadAction = "Load image";
static const QString saveAction = "Save image";
static const QString settingsAction = "Settings";
static const QString reprocessAction = "Reprocess";
static const QString histogramAction = "Histogram";

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

    QLabel positionLabel;
    QLabel imageSizeLabel;
};
