#include "mainwindow.h"
#include "ui_mainwindow.h"
MainWindow::MainWindow(CvCapture *cam, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    camera = cam;
    options = new Options();
    cvwidget = new QOpenCVWidget(this);
    ui->setupUi(this);
    ui->cvwidget = cvwidget;
    ui->cvwidget->resize(640,480);

    ui->fileDirectory->setText(options->getFileName());
    ui->medianCheck->setChecked(options->getFilters() & FILTERS_MEDIAN);
    ui->gaussCheck->setChecked(options->getFilters() & FILTERS_GAUSS);
    ui->medianSizeSpin->setValue(options->getMedianSize());
    ui->gaussSizeSpin->setValue(options->getGaussSize());
    ui->thresholdSlider->setValue(options->getThreshold());
    ui->valueSlider->setValue(options->getValue());
    ui->blueRadio->setChecked(options->getColour() & COLOUR_BLUE);
    ui->greenRadio->setChecked(options->getColour() & COLOUR_GREEN);
    ui->redRadio->setChecked(options->getColour() & COLOUR_RED);

    startTimer(40);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void convertGrayscale(IplImage *img, IplImage *dst)
{
//    dst = cvCreateImage( cvSize(img->width,img->height),
//                                   IPL_DEPTH_8U,
//                                   1 );
//    for (int row = 0; row <img->height;row++)
//    {
//                for (int col = 0;col <img->width;col++)
//                {
//                    dst[row,col] = (img[row,col][0] * 0.114 + img[row,col][1] * 0.587 + img[row,col][2] * 0.299);
//                }
//    }
    int iplIndex, iplLineStart;
    iplIndex = 0; iplLineStart = 0;
    for (int y = 0; y < img->height; y++) {
        unsigned char red,green,blue;
        iplIndex = iplLineStart;
        for (int x = 0; x < img->width; x++) {
            // DO it
            //red = iplImage->imageData[iplIndex+2];
            //green = iplImage->imageData[iplIndex+1];
            //blue = iplImage->imageData[iplIndex+0];
            dst->imageData[iplIndex+0] = 0; //blue
            dst->imageData[iplIndex+1] = img->imageData[iplIndex+1];
            dst->imageData[iplIndex+2] = 0; //red
            //img.setPixel(x,y,qRgb(red, green, blue));
            iplIndex += 3;
        }
        iplLineStart += img->widthStep;
    }
//    IplImage *newFrameImage32F = cvCreateImage(cvSize(img->width,img->height), IPL_DEPTH_32F, 3);
//    cvConvertScale(img,newFrameImage32F);

//    IplImage *newFrameImageGS_32F = cvCreateImage (cvSize(img->width,img->height), IPL_DEPTH_32F, 1);
//    cvCvtColor(newFrameImage32F,newFrameImageGS_32F,CV_RGB2GRAY);

//    dst = cvCreateImage (cvSize(img->width,img->height), IPL_DEPTH_8U, 1);
//    cvConvertScale(newFrameImageGS_32F,dst);
}

void MainWindow::timerEvent(QTimerEvent*) {
    IplImage *image=cvQueryFrame(camera);
    IplImage* dst = cvCreateImage (cvSize(image->width,image->height), IPL_DEPTH_8U, 3);
    //convertGrayscale(image,dst);
    //if (options->getColour())
    //{
    //    cvCvtColor(image,img_bw,CV_BGR2GRAY);
    //}
    int filters = options->getFilters();
    if (filters & FILTERS_MEDIAN)
        cvSmooth(image,image,CV_MEDIAN,options->getMedianSize());
    if (filters & FILTERS_GAUSS)
        cvSmooth(image,image,CV_GAUSSIAN,options->getGaussSize(),options->getGaussSize());
    if (filters & FILTERS_THRESHOLD)
        cvThreshold(image,image,options->getThreshold(),options->getValue(),CV_THRESH_BINARY);
    cvwidget->putImage(image);
}

void MainWindow::on_toolButton_clicked()
{
    QString filedialog = QFileDialog::getSaveFileName(this,tr("Select Location for image"), QString(), tr("Image Files (*.jpg)"));
    ui->fileDirectory->setText(filedialog);
    options->setFileName(filedialog);
}

void MainWindow::on_medianCheck_clicked(bool checked)
{
    if (checked)
    {
        options->setFilters(options->getFilters() + FILTERS_MEDIAN); //filters | 0001
        ui->medianSizeSpin->setDisabled(false);
    }
    else
    {
        options->setFilters(options->getFilters() - FILTERS_MEDIAN); //filters & 1110
        ui->medianSizeSpin->setDisabled(true);
    }
}

void MainWindow::on_gaussCheck_clicked(bool checked)
{
    if (checked)
    {
        options->setFilters(options->getFilters() + FILTERS_GAUSS); //filters | 0010
        ui->gaussSizeSpin->setDisabled(false);
    }
    else
    {
        options->setFilters(options->getFilters() - FILTERS_GAUSS); //filters & 1101
        ui->gaussSizeSpin->setDisabled(true);
    }
}

void MainWindow::on_medianSizeSpin_valueChanged(int arg1)
{
    if (arg1 % 2 == 1)
        options->setMedianSize(arg1);
    else
    {
        ui->medianSizeSpin->setValue(arg1+1);
        options->setMedianSize(arg1+1);
    }
}

void MainWindow::on_gaussSizeSpin_valueChanged(int arg1)
{
    if (arg1 % 2 == 1)
        options->setGaussSize(arg1);
    else
    {
        ui->gaussSizeSpin->setValue(arg1+1);
        options->setGaussSize(arg1+1);
    }
}

void MainWindow::on_pushButton_clicked()
{
    QString filename = options->getFileName();
    cvwidget->saveImage(filename);
    //printf(filename.toLocal8Bit().data());
}

void MainWindow::on_thresholdCheck_clicked(bool checked)
{
    if (checked)
    {
        options->setFilters(options->getFilters() + FILTERS_THRESHOLD); //filters | 0100

    }
    else
    {
        options->setFilters(options->getFilters() - FILTERS_THRESHOLD);

    }
}

void MainWindow::on_thresholdSlider_valueChanged(int value)
{
    ui->thresholdLabel->setText(QString::number(value));
    options->setThreshold(value);
}

void MainWindow::on_valueSlider_valueChanged(int value)
{
    ui->valueLabel->setText(QString::number(value));
    options->setValue(value);
}
