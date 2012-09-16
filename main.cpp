#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <assert.h>
#include <QApplication>
#include <QWidget>
#include <QVBoxLayout>
#include "QOpenCVWidget.h"
#include "MyCameraWindow.h"
#include "mainwindow.h"

int main(int argc, char **argv) {
    CvCapture * camera = cvCreateCameraCapture(1);
    assert(camera);
    IplImage * image=cvQueryFrame(camera);
    assert(image);
    //cvSetCaptureProperty(camera,CV_CAP_PROP_GAIN,1);

    printf("Image depth=%i\n", image->depth);
    printf("Image nChannels=%i\n", image->nChannels);

    QApplication app(argc, argv);
    //MyCameraWindow *mainWin = new MyCameraWindow(camera);
    MainWindow *mainWin = new MainWindow(camera);
    mainWin->setWindowTitle("OpenCV --> QtImage");
    mainWin->show();    
    int retval = app.exec();
    
    cvReleaseCapture(&camera);
    
    return retval;
}

