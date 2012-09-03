
#include "QOpenCVWidget.h"

// Constructor
QOpenCVWidget::QOpenCVWidget(QWidget *parent) : QWidget(parent) {
    layout = new QVBoxLayout;
    imagelabel = new QLabel;
    QImage dummy(100,100,QImage::Format_RGB32);
    image = dummy;
    layout->addWidget(imagelabel);
    for (int x = 0; x < 100; x ++) {
        for (int y =0; y < 100; y++) {
            image.setPixel(x,y,qRgb(x, y, y));
        }
    }
    imagelabel->setPixmap(QPixmap::fromImage(image));

    setLayout(layout);
}

QOpenCVWidget::~QOpenCVWidget(void) {
    
}

QImage IplImage2QImage(const IplImage *iplImage)
{
    QImage img(iplImage->width, iplImage->height, QImage::Format_RGB32);
    int iplIndex, iplLineStart;
    // switch between bit depths
    switch (iplImage->depth) {
        case IPL_DEPTH_8U:
            switch (iplImage->nChannels) {
                case 3:
                    iplIndex = 0; iplLineStart = 0;
                    for (int y = 0; y < iplImage->height; y++) {
                        unsigned char red,green,blue;
                        iplIndex = iplLineStart;
                        for (int x = 0; x < iplImage->width; x++) {
                            // DO it
                            red = iplImage->imageData[iplIndex+2];
                            green = iplImage->imageData[iplIndex+1];
                            blue = iplImage->imageData[iplIndex+0];

                            img.setPixel(x,y,qRgb(red, green, blue));
                            iplIndex += 3;
                        }
                        iplLineStart += iplImage->widthStep;
                    }
                    break;
                default:
                    printf("This number of channels is not supported\n");
                    break;
            }
            break;
        default:
            printf("This type of IplImage is not implemented in QOpenCVWidget\n");
            break;
    }
    return img;
}

void QOpenCVWidget::putImage(IplImage *cvimage) {

    image = IplImage2QImage(cvimage);
    imagelabel->setPixmap(QPixmap::fromImage(image));
}

