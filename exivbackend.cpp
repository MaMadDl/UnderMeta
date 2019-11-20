#include "exivbackend.h"

exivBackend::exivBackend(QObject *parent) : QObject(parent),_signalOutput(new QWidget)
{

}

void exivBackend::newImage(QString path)
{
    _scroller= new QScrollArea();
    _signalOutput=new QWidget(_scroller);
    QGridLayout *frame=new QGridLayout(_signalOutput);
    try{
    ex2::Image::UniquePtr image=ex2::ImageFactory::open(path.toStdString());
    if(image.get() == nullptr)
        return;
    image->readMetadata();
    _exifD = image->exifData();
    _xmpD  = image->xmpData();
    _iptcD = image->iptcData();
    if (!_exifD.empty()) {
        int count=0;
        std::cout<<"Exif Scope\n";
        ex2::ExifData::const_iterator end=_exifD.end();
        for (ex2::ExifData::const_iterator i= _exifD.begin(); i != end; ++i) {
            if(i->tagLabel()!=""){
                /*
                std::cout<<i->tagLabel()<<"\t"
                     << "0x" << std::setw(4) << std::setfill('0') << std::right
                     << std::hex << i->tag() << std::dec << "\t"
                     << i->groupName() << "\t"
                     << i->typeName() << "\t"
                     << i->count() << "\t"
                     << i->print(&_exifD)
                     << "\n";
                     */

                QLabel *lbl=new QLabel(QString(i->tagLabel().c_str()));
                frame->addWidget(lbl,count,0,Qt::AlignLeft);
            }
            else {
                QLabel *lbl=new QLabel(QString("0x")+QString::number(i->tag(),16));
                frame->addWidget(lbl,count,0,Qt::AlignLeft);

            }
            QLabel *ltag=new QLabel(QString::fromStdString(i->print()).trimmed());
            if(ltag->text().size()>40){
//                ltag->text().chop(ltag->text().size()-40);
                ltag->setText(ltag->text().remove(40,ltag->text().size()-40));
                ltag->setWordWrap(true);
            }
            frame->addWidget(ltag,count,1,Qt::AlignLeft);

            ///TODO add stuff for other types

            QtMaterialFlatButton *btn=new QtMaterialFlatButton("...");
            btn->setFontSize(16);
            btn->setHaloVisible(false);
            btn->setForegroundColor(QColor(255,255,255));

            ///TODO add Button Signals connections
            frame->addWidget(btn,count,2,Qt::AlignRight);
            count++;
        }
        _scroller->setWidget(_signalOutput);
        emit MetaTypeDone(_scroller,1);
    }
    //reInitilize for next use
    _scroller= new QScrollArea();
    _signalOutput=new QWidget(_scroller);
    frame=new QGridLayout(_signalOutput);
    if(!_xmpD.empty()){
        std::cout<<"XMP Scope\n";
        int count=0;
        ex2::XmpData::const_iterator end=_xmpD.end();
        for (ex2::XmpData::const_iterator i= _xmpD.begin(); i != end; ++i) {
            //std::cout << i->key() << "\t" << i->typeName() << "\t" << i->count() << "\t" << "\n";
            if(i->tagLabel()!=""){
                QLabel *lbl=new QLabel(QString(i->tagLabel().c_str()));
                frame->addWidget(lbl,count,0,Qt::AlignLeft);
            }
            else{
                QLabel *lbl=new QLabel(QString("0x")+QString::number(i->tag(),16));
                frame->addWidget(lbl,count,0,Qt::AlignLeft);
            }

            QLabel *ltag=new QLabel(QString::fromStdString(i->print()).trimmed());
            if(ltag->text().size()>40){
                ltag->setText(ltag->text().remove(40,ltag->text().size()-40));
                ltag->setWordWrap(true);
            }
            frame->addWidget(ltag,count,1,Qt::AlignLeft);

            QtMaterialFlatButton *btn=new QtMaterialFlatButton("...");
            btn->setFontSize(16);
            btn->setHaloVisible(false);
            btn->setForegroundColor(QColor(255,255,255));

            ///TODO add Button Signals connections
            frame->addWidget(btn,count,2,Qt::AlignRight);
            count++;

        }
        _scroller->setWidget(_signalOutput);
        emit MetaTypeDone(_scroller,2);
    }
    }

    _scroller= new QScrollArea();
    _signalOutput=new QWidget(_scroller);
    frame=new QGridLayout(_signalOutput);
    if(!_iptcD.empty()){
        std::cout<<"IPTC Scope\n";
        int count =0 ;
        ex2::IptcData::const_iterator end=_iptcD.end();
        for (ex2::IptcData::const_iterator i= _iptcD.begin(); i != end; ++i) {
//            std::cout << i->key() << "\n";
            if(i->tagLabel()!=""){
                QLabel *lbl=new QLabel(QString(i->tagLabel().c_str()));
                frame->addWidget(lbl,count,0,Qt::AlignLeft);
            }
            else{
                QLabel *lbl=new QLabel(QString("0x")+QString::number(i->tag(),16));
                frame->addWidget(lbl,count,0,Qt::AlignLeft);
            }
            QLabel *ltag=new QLabel(QString::fromStdString(i->print()).trimmed());
            if(ltag->text().size()>40){
                ltag->setText(ltag->text().remove(40,ltag->text().size()-40));
                ltag->setWordWrap(true);
            }
            frame->addWidget(ltag,count,1,Qt::AlignLeft);

            QtMaterialFlatButton *btn=new QtMaterialFlatButton("...");
            btn->setFontSize(16);
            btn->setHaloVisible(false);
            btn->setForegroundColor(QColor(255,255,255));

            ///TODO add Button Signals connections
            frame->addWidget(btn,count,2,Qt::AlignRight);
            count++;
        }
        _scroller->setWidget(_signalOutput);
        emit MetaTypeDone(_scroller,3);
    }
    }
    }
    catch(ex2::AnyError& e)
    {
        std::cout << "Caught Exiv2 exception '" << e << "'\n";
    }
    return;
}
