#include "mainwindow.h"
#include "ui_MainWindow.h"

#include <QFileDialog>
#include <QInputDialog>
#include <utility>
#include <fstream>

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

    ui->lineEdit_password->setVisible(false);

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
    if (!newText.endsWith(".hfz") && !newText.endsWith(".hfzb") && !newText.
        endsWith(".txt")) {
        isModeCompress = true;
        ui->label_errorMsg->setText(
            "Please choose file of specified types only! (.txt | .hfz)");
        ui->label_errorMsg->setVisible(true);

        isFilePathValid = false;
        return;
    }

    // Change submit button text accordingly
    if (newText.endsWith(".hfz") || newText.endsWith(".hfzb")) {
        isModeCompress = false;
        ui->pushButton_submit->setText("Decompress");

        ui->checkBox_toBinary->setVisible(false);

        ui->checkBox_passwordProtected->setChecked(false);
        ui->checkBox_passwordProtected->setVisible(false);
        ui->lineEdit_password->setVisible(false);
    } else {
        isModeCompress = true;
        ui->pushButton_submit->setText("Compress");

        ui->checkBox_toBinary->setVisible(true);

        ui->checkBox_passwordProtected->setVisible(true);
        ui->checkBox_passwordProtected->setChecked(false);
        ui->lineEdit_password->setVisible(false);
    }
}

void MainWindow::on_pushButton_browse_clicked() {
    // Prompt user to choose file
    QString chosenFilePath = QFileDialog::getOpenFileName(
        this, "Choose File", QDir::homePath(),
        "Text Files | HuffmanFileZipper (Binary) Files (*.txt *.hfz *.hfzb)");

    // Change FilePath line edit accordingly
    ui->lineEdit_filePath->setText(chosenFilePath);
}

void MainWindow::on_checkBox_passwordProtected_stateChanged(int arg1) {
    if (ui->checkBox_passwordProtected->isChecked()) {
        ui->lineEdit_password->setVisible(true);
    } else {
        ui->lineEdit_password->setVisible(false);
    }
}

void MainWindow::on_pushButton_submit_clicked() {
    // Hide success message initially
    ui->label_successMsg->setVisible(false);

    if (!isFilePathValid) {
        return;
    }

    //region Validate the original chosen file path
    QString chosenFilePath = ui->lineEdit_filePath->text();

    // Hide error message & mark file as valid initially
    ui->label_errorMsg->setVisible(false);

    // Check if no file is chosen yet
    if (chosenFilePath.isEmpty()) {
        ui->label_errorMsg->setText("Please choose a file first!");
        ui->label_errorMsg->setVisible(true);
        return;
    }

    // Prompt user to choose save destination
    QString fileType;
    bool isToBinary = ui->checkBox_toBinary->isChecked();
    if (isModeCompress) {
        if (isToBinary) {
            fileType = "HuffmanFileZipper Binary Files (*.hfzb)";
        } else {
            fileType = "HuffmanFileZipper Binary (*.hfz)";
        }
    } else {
        fileType = "Text Files (*.txt)";
    }

    QString saveToFilePath = QFileDialog::getSaveFileName(
        this, "Save to", QDir::homePath(),
        fileType);

    // Validate the save-to file path
    if (saveToFilePath.isEmpty()) {
        ui->label_errorMsg->setText("Please specify a place to save to!");
        ui->label_errorMsg->setVisible(true);
        return;
    }

    // Validate the password
    if (isModeCompress && ui->checkBox_passwordProtected->isChecked() && ui->
        lineEdit_password->text().isEmpty()) {
        ui->label_errorMsg->setText("Please provide a password!");
        ui->label_errorMsg->setVisible(true);
        return;
    }

    //endregion

    //region Business Logic

    // Use Helper functions to (de)compress and show success/error messages
    if (isModeCompress) {
        string password;
        if (ui->checkBox_passwordProtected->isChecked()) {
            password = ui->lineEdit_password->text().toStdString();
        }

        if (compress(chosenFilePath.toStdString(), saveToFilePath.toStdString(),
                     isToBinary, password)) {
            ui->label_successMsg->setText("Compressed and Saved Successfully!");
            ui->label_successMsg->setVisible(true);
        } else {
            ui->label_errorMsg->setText(
                "Something went wrong.. Please try again!");
            ui->label_errorMsg->setVisible(true);
        }
    } else {
        if (decompress(chosenFilePath.toStdString(),
                       saveToFilePath.toStdString(),
                       chosenFilePath.endsWith(".hfzb"))) {
            ui->label_successMsg->setText(
                "Decompressed and Saved Successfully!");
            ui->label_successMsg->setVisible(true);
        } else {
            ui->label_errorMsg->setText(
                "Something went wrong or incorrect password.. Please try again!");
            ui->label_errorMsg->setVisible(true);
        }
    }

    //endregion
}

// Helper Functions
bool MainWindow::compress(const string& chosenFilePath,
                          const string& saveToFilePath, bool isToBinary,
                          string password) {
    // Change FileDealer file paths & call its methods accordingly
    fDealer.setDecodedOriginFilePath(chosenFilePath);
    fDealer.setEncodedDestinationFilePath(saveToFilePath);

    HuffmanTree* huffTree = fDealer.readOriginalDataText();

    if (huffTree == nullptr) {
        return false;
    }

    // Save compressed file either as binary .hfzb or .hfz
    if (isToBinary) {
        fDealer.writeEncodedDataBinary(huffTree->getEncodedData(),
                                       *huffTree->getCodewordsMap(),
                                       std::move(password));
    } else {
        fDealer.writeEncodedDataText(huffTree->getEncodedData(),
                                     *huffTree->getCodewordsMap());
    }

    return true;
}

bool MainWindow::decompress(const string& chosenFilePath,
                            const string& saveToFilePath, bool isFromBinary) {
    // Change FileDealer file paths & call its methods accordingly
    fDealer.setEncodedOriginFilePath(chosenFilePath);
    fDealer.setDecodedDestinationFilePath(saveToFilePath);

    QString password;
    if (isPasswordProtected(chosenFilePath)) {
        bool ok;
        password = QInputDialog::getText(this, "File Password", "Password",
                                         QLineEdit::Password, "", &ok);
        if (!ok) {
            return false;
        }
    }

    HuffmanTree* huffTree;

    if (isFromBinary) {
        huffTree = fDealer.readEncodedDataBinary(password.toStdString());
    } else {
        huffTree = fDealer.readEncodedDataText();
    }

    if (huffTree == nullptr) {
        return false;
    }

    fDealer.writeDecodedDataText(huffTree->getDecodedData());

    return true;
}

bool MainWindow::isPasswordProtected(const string& chosenFilePath) {
    ifstream inFile(chosenFilePath, ios::binary);
    if (!inFile.is_open()) {
        return false;
    }

    char passwordProtectedFlag;
    inFile.read(&passwordProtectedFlag, sizeof(char));

    inFile.close();
    return (passwordProtectedFlag == '1');
}
