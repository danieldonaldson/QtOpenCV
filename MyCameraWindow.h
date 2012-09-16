#ifndef MYCAMERAWINDOW_H_
#define MYCAMERAWINDOW_H_

#include <QWidget>
#include <QGridLayout>
#include <QCommandLinkButton>
#include <QMessageBox>
#include "QOpenCVWidget.h"
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "OptionsDialog.h"


class MyCameraWindow : public QWidget
{
    Q_OBJECT
    private:
        QOpenCVWidget *cvwidget;
        CvCapture *camera;
        QGridLayout *layout;
        QCommandLinkButton *closeButton;
        QCommandLinkButton *optionsButton;
        QCommandLinkButton *captureButton;

        OptionsDialog options;
        
    public:
        MyCameraWindow(CvCapture *cam, QWidget *parent=0);
         
    protected:
        void timerEvent(QTimerEvent*);

private slots:
        void closeButtonClicked();
        void optionsButtonClicked();
        void captureButtonClicked();
};


#endif /*MYCAMERAWINDOW_H_*/
