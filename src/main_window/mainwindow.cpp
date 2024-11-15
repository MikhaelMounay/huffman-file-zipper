#include "mainwindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget* parent) :
    QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);

    //region Window Properties

    const int WINDOW_WIDTH = 640;
    const int WINDOW_HEIGHT = 360;
    this->setBaseSize(WINDOW_WIDTH, WINDOW_HEIGHT); // Not working as expected
    this->setMaximumSize(WINDOW_WIDTH * 1.5, WINDOW_HEIGHT * 1.5);
    this->setMinimumSize(WINDOW_WIDTH / 1.5, WINDOW_HEIGHT / 1.5);
    this->resize(WINDOW_WIDTH, WINDOW_HEIGHT);

    this->setWindowTitle("Huffman File Zipper");

    //endregion

    //region Styles

    // Importing stylesheets
    QFile styleFile(":/styles/mainwindow_styles.qss");
    styleFile.open(QFile::ReadOnly);
    QString styleString = styleFile.readAll();
    this->setStyleSheet(styleString);

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

    ui->label_errorMsg->setVisible(false);
    ui->label_successMsg->setVisible(false);

    // Setting Default focus to the Browse button
    ui->pushButton_browse->setFocus();

    //endregion

    // Business Logic
    isFilePathValid = false;
    isModeCompress = true;
}

MainWindow::~MainWindow() {
    // Styles
    delete shadowEffect_browse;
    delete shadowEffect_submit;
    delete shadowEffect_filePath;

    delete ui;
}

// Slots
void MainWindow::on_lineEdit_filePath_textChanged(const QString& newText) {
    // Hide error/sucess message & mark file as valid initially
    ui->label_errorMsg->setVisible(false);
    ui->label_successMsg->setVisible(false);
    isFilePathValid = true;

    // Show no error if no file is chosen yet
    if (newText.isEmpty()) {
        ui->label_errorMsg->setVisible(false);
        return;
    }

    // Validate chosen file path
    if (!newText.endsWith(".hfz") && !newText.endsWith(".txt")) {
        isModeCompress = true;
        ui->label_errorMsg->setText(
            "Please choose file of specified types only! (.txt | .hfz)");
        ui->label_errorMsg->setVisible(true);

        isFilePathValid = false;
        return;
    }

    // Change submit button text accordingly
    if (newText.endsWith(".hfz")) {
        isModeCompress = false;
        ui->pushButton_submit->setText("Decompress");
    } else {
        isModeCompress = true;
        ui->pushButton_submit->setText("Compress");
    }
}

void MainWindow::on_pushButton_browse_clicked() {
    // Prompt user to choose file
    QString chosenFilePath = QFileDialog::getOpenFileName(
        this, "Choose File", QDir::homePath(),
        "Text Files | HuffmanFileZipper Files (*.txt *.hfz)");

    // Change FilePath line edit accordingly
    ui->lineEdit_filePath->setText(chosenFilePath);

    // Change submit button text & FileDealer file paths accordingly
    if (chosenFilePath.endsWith(".hfz")) {
        fDealer.setDecodedOriginFilePath(chosenFilePath.toStdString());
    } else {
        ui->pushButton_submit->setText("Compress");
    }
}

void MainWindow::on_pushButton_submit_clicked() {
    // Hide success message initially
    ui->label_successMsg->setVisible(false);

    if (!isFilePathValid) {
        return;
    }

    QString chosenFilePath = ui->lineEdit_filePath->text();
    //region Validate the original chosen file path

    // Hide error message & mark file as valid initially
    ui->label_errorMsg->setVisible(false);

    // Check if no file is chosen yet
    if (chosenFilePath.isEmpty()) {
        ui->label_errorMsg->setText("Please choose a file first!");
        ui->label_errorMsg->setVisible(true);
    }

    //endregion

    // Prompt user to choose save destination
    QString fileType;
    if (isModeCompress) {
        fileType = "HuffmanFileZipper Files (*.hfz)";
    } else {
        fileType = "Text Files (*.txt)";
    }

    QString saveToFilePath = QFileDialog::getSaveFileName(
        this, "Save to", QDir::homePath(),
        fileType);

    //region Business Logic

    // Change FileDealer file paths & call its methods accordingly
    if (isModeCompress) {
        fDealer.setDecodedOriginFilePath(chosenFilePath.toStdString());
        fDealer.setEncodedDestinationFilePath(saveToFilePath.toStdString());

        HuffmanTree* huffTree = fDealer.readOriginalDataText();

        bool isSuccess = false;
        if (huffTree) {
            isSuccess = true;
            fDealer.writeEncodedDataBinary(huffTree->getEncodedData(),
                                           *huffTree->getCodewordsMap());
        }

        if (isSuccess) {
            ui->label_successMsg->setText("Compressed and Saved Successfully!");
            ui->label_successMsg->setVisible(true);
        } else {
            ui->label_errorMsg->setText(
                "Something went wrong.. Please try again!");
            ui->label_errorMsg->setVisible(true);
        }
    } else {
        fDealer.setEncodedOriginFilePath(chosenFilePath.toStdString());
        fDealer.setDecodedDestinationFilePath(saveToFilePath.toStdString());

        HuffmanTree* huffTree = fDealer.readEncodedDataBinary();

        bool isSuccess = false;
        if (huffTree != nullptr) {
            isSuccess = true;
            fDealer.writeDecodedDataText(huffTree->getDecodedData());
        }

        if (isSuccess) {
            ui->label_successMsg->setText(
                "Decompressed and Saved Successfully!");
            ui->label_successMsg->setVisible(true);
        } else {
            ui->label_errorMsg->setText(
                "Something went wrong.. Please try again!");
            ui->label_errorMsg->setVisible(true);
        }
    }

    //endregion
}
