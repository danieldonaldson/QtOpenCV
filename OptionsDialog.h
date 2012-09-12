#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include <opencv/cv.h>

namespace Ui {
class OptionsDialog;
}

class OptionsDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit OptionsDialog(QWidget *parent = 0);
    ~OptionsDialog();
    int getFilters();
    int getMedianSize();
    int getGaussSize();
    QString getFileName();
    
private slots:

    void on_pushButton_released();

    void on_pushButton_2_released();

    void on_checkBox_clicked(bool checked);

    void on_checkBox_6_clicked(bool checked);

    void on_gaussSizeSpin_valueChanged(int arg1);

    void on_medianSizeSpin_valueChanged(int arg1);

    void on_toolButton_clicked();

private:
    Ui::OptionsDialog *ui;
    int filters; //boolean of filters, order is median, gaussian,
    int medianSize;
    int gaussSize;
    QString filename;
};

#endif // OPTIONSDIALOG_H
