#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionLoad_File_triggered();

private:
    Ui::MainWindow *ui;
    void loadFile(QString &fileName);

    QVector<double> time, lat0, lon0, ht0, sat0
                        , lat1, lon1, ht1, sat1;
    double minTime;
    double maxTime;
    double minLat;
    double maxLat;
    double minLon;
    double maxLon;
    double minHt;
    double maxHt;
    int minSat;
    int maxSat;

};

#endif // MAINWINDOW_H
