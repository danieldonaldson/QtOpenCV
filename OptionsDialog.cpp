#include "OptionsDialog.h"
#include "ui_OptionsDialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    filters = 0;
    medianSize = 3;
    ui->medianSizeSpin->setValue(medianSize);
    gaussSize = 5;
    ui->gaussSizeSpin->setValue(gaussSize);
    filename = QDir::currentPath() + "/save.jpg";
    ui->fileDirectory->setText(filename);
}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

int OptionsDialog::getFilters()
{
    return filters;
}

int OptionsDialog::getMedianSize()
{
    return medianSize;
}

int OptionsDialog::getGaussSize()
{
    return gaussSize;
}

QString OptionsDialog::getFileName()
{
    return filename;
}

void OptionsDialog::on_pushButton_released()
{
    //save all
    this->close();
}

void OptionsDialog::on_pushButton_2_released()
{
    //reset to defaults

}

void OptionsDialog::on_checkBox_clicked(bool checked)
{
    if (checked)
    {
        filters = filters + 1; //filters | 0001
        ui->medianSizeSpin->setDisabled(false);
    }
    else
    {
        filters = filters - 1; //filters & 1110
        ui->medianSizeSpin->setDisabled(true);
    }

}

void OptionsDialog::on_checkBox_6_clicked(bool checked)
{
    if (checked)
    {
        filters = filters + 2; //filters | 0010
        ui->gaussSizeSpin->setDisabled(false);
    }
    else
    {
        filters = filters - 2; //filters & 1101
        ui->gaussSizeSpin->setDisabled(true);
    }
}

void OptionsDialog::on_gaussSizeSpin_valueChanged(int arg1)
{
    if (arg1 % 2 == 1)
        gaussSize = arg1;
    else
    {
        ui->gaussSizeSpin->setValue(arg1+1);
        gaussSize = arg1+1;
    }
}

void OptionsDialog::on_medianSizeSpin_valueChanged(int arg1)
{
    if (arg1 % 2 == 1)
        medianSize = arg1;
    else
    {
        ui->medianSizeSpin->setValue(arg1+1);
        medianSize = arg1+1;
    }
}

void OptionsDialog::on_toolButton_clicked()
{
    QString filedialog = QFileDialog::getSaveFileName(this,tr("Select Location for image"), QString(), tr("Image Files (*.jpg)"));
    ui->fileDirectory->setText(filedialog);
    filename = filedialog;
}
