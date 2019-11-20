#ifndef EXIVBACKEND_H
#define EXIVBACKEND_H

#include <QObject>
#include <iostream>
#include <exiv2/exif.hpp>
#include <exiv2/image.hpp>
#include <exiv2/error.hpp>

#include <QDebug>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QScrollArea>
#include <qtmaterialflatbutton.h>

namespace ex2 = Exiv2;

class exivBackend : public QObject
{
    Q_OBJECT
public:
    explicit exivBackend(QObject *parent = nullptr);

signals:

    void MetaTypeDone(QScrollArea* output,int index);
public slots:

    void newImage(QString path);

private:
    ex2::ExifData _exifD;
    ex2::XmpData _xmpD;
    ex2::IptcData _iptcD;

    QWidget *_signalOutput;
    QScrollArea *_scroller;

};

#endif // EXIVBACKEND_H
