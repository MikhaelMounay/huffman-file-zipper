#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsDropShadowEffect>

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

private:
    Ui::MainWindow* ui;

    // Styles
    QGraphicsDropShadowEffect* shadowEffect_browse;
    QGraphicsDropShadowEffect* shadowEffect_submit;
    QGraphicsDropShadowEffect* shadowEffect_filePath;
};


#endif //MAINWINDOW_H
