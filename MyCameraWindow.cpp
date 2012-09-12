
#include "MyCameraWindow.h"

MyCameraWindow::MyCameraWindow(CvCapture *cam, QWidget *parent) : QWidget(parent) {
    camera = cam;
    layout = new QGridLayout();
    cvwidget = new QOpenCVWidget(this);
    layout->addWidget(cvwidget,0,0,1,3);
    closeButton = new QCommandLinkButton(tr("Close"));
    optionsButton = new QCommandLinkButton(tr("Options"));
    captureButton = new QCommandLinkButton(tr("Capture Image"));
    layout->addWidget(closeButton,1,2);
    layout->addWidget(optionsButton,1,0);
    layout->addWidget(captureButton,1,1);
    setLayout(layout);
    resize(640, 480);

    connect(closeButton,SIGNAL(clicked()),this,SLOT(closeButtonClicked()));
    connect(captureButton,SIGNAL(clicked()),this,SLOT(captureButtonClicked()));
    connect(optionsButton,SIGNAL(clicked()),this,SLOT(optionsButtonClicked()));

    startTimer(40);  // 25 fps = 40ms
 }

void MyCameraWindow::timerEvent(QTimerEvent*) {
    IplImage *image=cvQueryFrame(camera);
    int filters = options.getFilters();
    if (filters & 1)
        cvSmooth(image,image,CV_MEDIAN,options.getMedianSize());
    if (filters & 2)
        cvSmooth(image,image,CV_GAUSSIAN,options.getGaussSize(),options.getGaussSize());
    cvwidget->putImage(image);
}

void MyCameraWindow::closeButtonClicked()
{
    QMessageBox msgBox;
    msgBox.setText("Are you sure you want to exit?");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::Yes);
    int ret = msgBox.exec();
    switch (ret) {
    case QMessageBox::Yes:
        close();
        break;
    case QMessageBox::No:
        break;
    }
}

void MyCameraWindow::optionsButtonClicked()
{
    options.exec();
    printf("%d",options.getFilters());

}

void MyCameraWindow::captureButtonClicked()
{
    QString filename = options.getFileName();
    cvwidget->saveImage(filename);
    printf(filename.toLocal8Bit().data());
}

