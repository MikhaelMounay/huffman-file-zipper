#include "mainwindow.h"
#include "ui_MainWindow.h"

#include <QFile>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    // Window Properties
    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 360;
    this->setBaseSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Not working as expected
    this->setMaximumSize(WINDOW_WIDTH * 1.5, WINDOW_HEIGHT * 1.5);
    this->setMinimumSize(WINDOW_WIDTH / 1.5, WINDOW_HEIGHT / 1.5);
    this->resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    this->setWindowTitle("Huffman File Zipper");

    // Importing stylesheets
    QFile styleFile(":/styles/mainwindow_styles.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleString = styleFile.readAll();
    this->setStyleSheet(styleString);

    // Styles
    shadowEffect_browse = new QGraphicsDropShadowEffect;
    shadowEffect_browse->setBlurRadius(1);
    shadowEffect_browse->setOffset(0, 1);
    shadowEffect_browse->setColor(QColor(0, 0, 0, 50));
    ui->pushButton_browse->setGraphicsEffect(shadowEffect_browse);

    shadowEffect_submit = new QGraphicsDropShadowEffect;
    shadowEffect_submit->setBlurRadius(1);
    shadowEffect_submit->setOffset(0, 1);
    shadowEffect_submit->setColor(QColor(0, 0, 0, 50));
    ui->pushButton_submit->setGraphicsEffect(shadowEffect_submit);

    shadowEffect_filePath = new QGraphicsDropShadowEffect;
    shadowEffect_filePath->setBlurRadius(1);
    shadowEffect_filePath->setOffset(0, 1);
    shadowEffect_filePath->setColor(QColor(0, 0, 0, 50));
    ui->lineEdit_filePath->setGraphicsEffect(shadowEffect_filePath);

    // Setting Default focus to the Browse button
    ui->pushButton_browse->setFocus();
}

MainWindow::~MainWindow() {
    // Styles
    delete shadowEffect_browse;
    delete shadowEffect_submit;
    delete shadowEffect_filePath;

    delete ui;
}
