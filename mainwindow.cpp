#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _firstTime(false),
    _overwrite(false),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
//    qRegisterMetaType<QScrollArea>("QScrollArea");
    ui->OverwriteCheck->applyPreset(Material::CheckablePreset);
//    ui->ReadMetaWidget->addTab("");
    connect(this,SIGNAL(pushImagePath(QString)),&exifMeta,SLOT(newImage(QString)));
    connect(&exifMeta ,SIGNAL(MetaTypeDone(QScrollArea*,int)),this,SLOT(handleTabsFromBackends(QScrollArea*,int)));
    filePath=QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
    _extention="";

    /*
    QScrollArea *mainArea=new QScrollArea();
    QWidget *mainWid=new QWidget();

    //    mainWid.set;
    QGridLayout *frm=new QGridLayout(mainWid);
    for (int i=0;i<=20;++i) {
        QLabel *lbl=new QLabel(&"hello layout"[i]);
        frm->addWidget(lbl,i,0);
        QPushButton *btn=new QPushButton();
        frm->addWidget(btn,i,1);
    }

    mainArea->setWidget(mainWid);
    ui->ReadMetaWidget->addTab(mainArea,"test1");
*/

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::handleTabsFromBackends(QScrollArea* tab, int index)
{
    switch (index) {
    case 0: //GeneralTab //position 0
        ui->ReadMetaWidget->removeTab(index);
        ui->ReadMetaWidget->insertTab(index,tab,"General");
        break;
    case 1: //Exif Tab //Position 1
        ui->ReadMetaWidget->removeTab(index);
        ui->ReadMetaWidget->insertTab(index,tab,"Exif");
        break;
    case 2://XMP tab //Position 2
        ui->ReadMetaWidget->removeTab(index);
        ui->ReadMetaWidget->insertTab(index,tab,"Xmp");
        break;
    case 3:// IPTC tab //Position 3
        ui->ReadMetaWidget->removeTab(index);
        ui->ReadMetaWidget->insertTab(index,tab,"IPTC");
        break;
    }
}

void MainWindow::on_OpenButt_clicked()
{
    foreach (QString x, exivlist) {
        if(_extention==x){
            emit pushImagePath(ui->OpenLine->text());
            return;
        }
    }
    ///TODO Add extention seperation
    ///
    QtMaterialDialog *err=new QtMaterialDialog();
    err->showDialog();


}

void MainWindow::on_OpenBrowse_clicked()
{

    QString Path=QFileDialog::getOpenFileName(this,
                                              tr("Open File"),
                                              filePath,
                                              "All Files (*.*)");
    ui->OpenLine->setText(Path);
    filePath=QFileInfo(Path).path();
    _extention =QFileInfo(Path).suffix();

}

void MainWindow::on_actionExit_triggered()
{
    QApplication::quit();
}

void MainWindow::on_OverwriteCheck_toggled(bool checked)
{
    _overwrite=checked;
}
