#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QStandardPaths>
#include <QDebug>

#include "exivbackend.h"

const std::vector<QString> exivlist={"jpeg","jpg","png","tiff","orf","webp",
                                            "dng","nef","pef","srw","exv","cr2","crw",
                                            "pgf","psd","jp2"};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void pushImagePath(QString);

private slots:
    void handleTabsFromBackends(QScrollArea *tab,int index);

    void on_OpenButt_clicked();

    void on_OpenBrowse_clicked();

    void on_actionExit_triggered();

    void on_OverwriteCheck_toggled(bool checked);

private:

    bool _firstTime;
    bool _overwrite;
    Ui::MainWindow *ui;
    exivBackend exifMeta;
    QString filePath;
    QString _extention;
};

#endif // MAINWINDOW_H
