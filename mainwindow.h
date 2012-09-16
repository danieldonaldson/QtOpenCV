#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGridLayout>
#include <QCommandLinkButton>
#include <QMessageBox>
#include <QFileDialog>

#include "QOpenCVWidget.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "options.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(CvCapture *cam, QWidget *parent = 0);
    ~MainWindow();
    
private:
    QOpenCVWidget *cvwidget;
    CvCapture *camera;
    Ui::MainWindow *ui;
    Options *options;

protected:
    void timerEvent(QTimerEvent*);

private slots:
    void on_toolButton_clicked();
    void on_medianCheck_clicked(bool checked);
    void on_gaussCheck_clicked(bool checked);
    void on_medianSizeSpin_valueChanged(int arg1);
    void on_gaussSizeSpin_valueChanged(int arg1);
    void on_pushButton_clicked();
    void on_thresholdCheck_clicked(bool checked);
    void on_thresholdSlider_valueChanged(int value);
    void on_valueSlider_valueChanged(int value);
};

#endif // MAINWINDOW_H
