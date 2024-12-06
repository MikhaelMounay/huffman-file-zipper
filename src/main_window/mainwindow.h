#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsDropShadowEffect>

#include "../file_dealer/FileDealer.h"

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow() override;

private slots:
    void on_lineEdit_filePath_textChanged(const QString& newText);
    void on_pushButton_browse_clicked();
    void on_checkBox_passwordProtected_stateChanged(int arg1);
    void on_pushButton_submit_clicked();

private:
    Ui::MainWindow* ui;

    // Styles
    QGraphicsDropShadowEffect* shadowEffect_browse;
    QGraphicsDropShadowEffect* shadowEffect_submit;
    QGraphicsDropShadowEffect* shadowEffect_filePath;

    // Business Logic
    bool isFilePathValid;
    bool isModeCompress;
    FileDealer fDealer;

    // Helper Functions
    bool compress(const string& chosenFilePath, const string& saveToFilePath,
                  bool isToBinary, string password = "");
    bool decompress(const string& chosenFilePath, const string& saveToFilePath,
                    bool isFromBinary);
    bool isPasswordProtected(const string& chosenFilePath);
};


#endif //MAINWINDOW_H
