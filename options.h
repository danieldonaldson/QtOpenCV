#ifndef OPTIONS_H
#define OPTIONS_H

#include <QString>
#include <QDir>

#define FILTERS_MEDIAN 1
#define FILTERS_GAUSS 2
#define FILTERS_THRESHOLD 4

#define COLOUR_BLUE 4
#define COLOUR_RED 2
#define COLOUR_GREEN 1

class Options
{
public:
    Options();
    int getFilters();
    int getMedianSize();
    int getGaussSize();
    int getThreshold();
    int getValue();
    int getColour();
    QString getFileName();
    void resetDefaults();
    void setFilters(int x);
    void setMedianSize(int x);
    void setGaussSize(int x);
    void setFileName(QString x);
    void setThreshold(int x);
    void setValue(int x);
    void setColour(int x);

private:
    int filters; //boolean of filters, order is median, gaussian,
    int medianSize;
    int gaussSize;
    QString filename;
    int threshold;
    int value;
    int colour;
};

#endif // OPTIONS_H
