#include <iostream>
#include <QStyle>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "cvmatandqimage.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , positionLabel(this)
    , imageSizeLabel(this)
{
    ui->setupUi(this);

    QCoreApplication::setApplicationName("Testbed");
    setWindowTitle(QCoreApplication::applicationName());

    setupToolBar();

    setupStatusBar();

}

void MainWindow::setupToolBar()
{
    //Toolbar should not be dragged
    ui->toolBar->setMovable(false);

    QAction* loadButton = ui->toolBar->addAction(QIcon(":/icons/square.png"), loadAction);
    QAction* saveButton = ui->toolBar->addAction(QIcon(":/icons/floppyDisk.png"), saveAction);
    QAction* settingsButton = ui->toolBar->addAction(QIcon(":/icons/gear.png"), settingsAction);
    QAction* reprocessButton = ui->toolBar->addAction(QIcon(":/icons/play.png"), reprocessAction);
    QAction* histogramButton = ui->toolBar->addAction(QIcon(":/icons/histogram.png"), histogramAction);

    connect(loadButton, &QAction::triggered, this, [this]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Image to be processed", QString(), "Image Files (*.png *.jpg *.bmp)");
        if(!fileName.isEmpty()) {
            cv::Mat img = cv::imread(fileName.toLocal8Bit().constData());

            QImage imageDisplay = ImageConversion::mat2Image(img);

            QSize newImageSize = imageDisplay.size();
            ui->imageLabel->resize(newImageSize);
            ui->imageLabel->setPixmap(QPixmap::fromImage(imageDisplay));
            ui->imageLabel->setAttribute(Qt::WA_Hover, true);

            QString imageSizeText("%1x%2");
            imageSizeLabel.setText(imageSizeText.arg(newImageSize.width()).arg(newImageSize.height()));

            connect(ui->imageLabel,&ImageDisplay::mouseMoved,this , [this](const QPoint& mousePos) {
                QString text("x=%1;y=%2");
                positionLabel.setText(text.arg(mousePos.x()).arg(mousePos.y()));
            });

            //Set new max window size
            QSize newMaxWindowSize = newImageSize;
            QWidgetList scrollBarList = ui->scrollArea->scrollBarWidgets(Qt::AlignRight | Qt::AlignBottom);
            newMaxWindowSize.setWidth(newMaxWindowSize.width() + QStyle::PM_ScrollBarExtent);
            newMaxWindowSize.setHeight(newMaxWindowSize.height() + ui->toolBar->height() + ui->statusbar->height() + QStyle::PM_ScrollBarExtent);
            setMaximumSize(newMaxWindowSize);
        }
    });
}

void MainWindow::setupStatusBar()
{
    ui->statusbar->addPermanentWidget(&positionLabel);
    ui->statusbar->addPermanentWidget(&imageSizeLabel);
}

MainWindow::~MainWindow()
{
    delete ui;
}

