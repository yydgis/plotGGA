#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <vector>
#include "dialog.h"

#include "nemagga.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(tr("GGA File: "));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadFile(QString& fileName)
{
    gnssimu_lib::TNEMAGGAReader ggaFile;

    time.clear();
    lat0.clear();
    lat1.clear();
    lon0.clear();
    lon1.clear();
    ht0.clear();
    ht1.clear();
    sat0.clear();
    sat1.clear();

    ggaFile.ReadGGA(fileName.toUtf8());
    int size = ggaFile.vGGA_.size();
    if (size>0)
    {
        gnssimu_lib::TGPGGA gga;
        bool isFirst = false;
        double nullData = qQNaN();
        minTime = 0.0;
        maxTime = 0.0;
        minLat = 0.0;
        maxLat = 0.0;
        minLon = 0.0;
        maxLon = 0.0;
        minHt = 0.0;
        maxHt = 0.0;
        minSat = 0;
        maxSat = 0;
        foreach(gga, ggaFile.vGGA_) {
            time.push_back(gga.time);
            if (gga.solType==4) {
                lat0.push_back(gga.ned[0]);
                lon0.push_back(gga.ned[1]);
                ht0.push_back(gga.ned[2]);
                sat0.push_back(gga.numOfSat);
                lat1.push_back(nullData);
                lon1.push_back(nullData);
                ht1.push_back(nullData);
                sat1.push_back(nullData);
            }
            else {
                lat0.push_back(nullData);
                lon0.push_back(nullData);
                ht0.push_back(nullData);
                sat0.push_back(nullData);
                lat1.push_back(gga.ned[0]);
                lon1.push_back(gga.ned[1]);
                ht1.push_back(gga.ned[2]);
                sat1.push_back(gga.numOfSat);
            }
            if (!isFirst) {
                minTime = maxTime = gga.time;
                minLat = maxLat = gga.ned[0];
                minLon = maxLon = gga.ned[1];
                minHt = maxHt = gga.ned[2];
                minSat = maxSat = gga.numOfSat;
                isFirst = true;
            }
            else {
                if (gga.time< minTime) minTime = gga.time;
                if (gga.time> maxTime) maxTime = gga.time;
                if (gga.ned[0]< minLat) minLat = gga.ned[0];
                if (gga.ned[0]> maxLat) maxLat = gga.ned[0];
                if (gga.ned[1]< minLon) minLon = gga.ned[1];
                if (gga.ned[1]> maxLon) maxLon = gga.ned[1];
                if (gga.ned[2]< minHt ) minHt = gga.ned[2];
                if (gga.ned[2]> maxHt ) maxHt = gga.ned[2];
                if (gga.numOfSat< minSat) minSat = gga.numOfSat;
                if (gga.numOfSat> maxSat) maxSat = gga.numOfSat;
            }


        }
        // create graph and assign data to it:

        ui->customPlot0->addGraph();
        ui->customPlot0->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot0->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, Qt::green, Qt::white, 3));
        ui->customPlot0->graph(0)->setData(time, lat0);
        //ui->customPlot0->graph(0)->setData(lon0, lat0);

        ui->customPlot0->addGraph();
        ui->customPlot0->graph(1)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot0->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 3));
        ui->customPlot0->graph(1)->setData(time, lat1);
        //ui->customPlot0->graph(1)->setData(lon1, lat1);

        ui->customPlot0->xAxis->setLabel("Time [second]");
        ui->customPlot0->yAxis->setLabel("Latitude [radian]");
        //ui->customPlot0->xAxis->setLabel("East  [m]");
        //ui->customPlot0->yAxis->setLabel("North [m]");
        // set axes ranges, so we see all data:
        ui->customPlot0->xAxis->setRange(minTime, maxTime);
        ui->customPlot0->yAxis->setRange(minLat, maxLat);
        //ui->customPlot0->xAxis->setRange(minLon, maxLon);
        //ui->customPlot0->yAxis->setRange(minLat, maxLat);

        ui->customPlot1->addGraph();
        ui->customPlot1->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot1->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, Qt::green, Qt::white, 3));
        ui->customPlot1->graph(0)->setData(time, lon0);

        ui->customPlot1->addGraph();
        ui->customPlot1->graph(1)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot1->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 3));
        ui->customPlot1->graph(1)->setData(time, lon1);

        ui->customPlot1->xAxis->setLabel("Time [second]");
        ui->customPlot1->yAxis->setLabel("Longitude [radian]");
        // set axes ranges, so we see all data:
        ui->customPlot1->xAxis->setRange(minTime, maxTime);
        ui->customPlot1->yAxis->setRange(minLon, maxLon);

        ui->customPlot2->addGraph();
        ui->customPlot2->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot2->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, Qt::green, Qt::white, 3));
        ui->customPlot2->graph(0)->setData(time, ht0);

        ui->customPlot2->addGraph();
        ui->customPlot2->graph(1)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot2->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 3));
        ui->customPlot2->graph(1)->setData(time, ht1);

        ui->customPlot2->xAxis->setLabel("Time [second]");
        ui->customPlot2->yAxis->setLabel("Height [meter]");
        // set axes ranges, so we see all data:
        ui->customPlot2->xAxis->setRange(minTime, maxTime);
        ui->customPlot2->yAxis->setRange(minHt, maxHt);

        // number of satellite
        ui->customPlot3->addGraph();
        ui->customPlot3->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot3->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, Qt::green, Qt::white, 3));
        ui->customPlot3->graph(0)->setData(time, sat0);

        ui->customPlot3->addGraph();
        ui->customPlot3->graph(1)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot3->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 3));
        ui->customPlot3->graph(1)->setData(time, sat1);

        ui->customPlot3->xAxis->setLabel("Time [second]");
        ui->customPlot3->yAxis->setLabel("Number Of Satellite");
        // set axes ranges, so we see all data:
        ui->customPlot3->xAxis->setRange(minTime, maxTime);
        ui->customPlot3->yAxis->setRange(minSat, maxSat);


        ui->customPlot4->addGraph();
        ui->customPlot4->graph(0)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot4->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCross, Qt::green, Qt::white, 3));
        ui->customPlot4->graph(0)->setData(lon0, lat0);

        ui->customPlot4->addGraph();
        ui->customPlot4->graph(1)->setLineStyle(QCPGraph::lsNone);
        ui->customPlot4->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, Qt::red, Qt::white, 3));
        ui->customPlot4->graph(1)->setData(lon1, lat1);

        ui->customPlot4->xAxis->setLabel("East  [m]");
        ui->customPlot4->yAxis->setLabel("North [m]");
        // set axes ranges, so we see all data:
        ui->customPlot4->xAxis->setRange(minLon, maxLon);
        ui->customPlot4->yAxis->setRange(minLat, maxLat);
        ui->customPlot4->yAxis->setScaleRatio(ui->customPlot4->xAxis,1.0);


        // Note: we could have also just called customPlot->rescaleAxes(); instead
        // Allow user to drag axis ranges with mouse, zoom with mouse wheel and select graphs by clicking:
        ui->customPlot0->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->customPlot0->replot();
        ui->customPlot1->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->customPlot1->replot();
        ui->customPlot2->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->customPlot2->replot();
        ui->customPlot3->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->customPlot3->replot();
        ui->customPlot4->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        ui->customPlot4->replot();
    }
}


void MainWindow::on_actionLoad_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open GGA File Name"), "", tr("GGA Files (*.gga)"));
    if (!fileName.isNull())
    {
        loadFile(fileName);
        this->setWindowTitle(tr("GGA File: ")+fileName);
    }

}
