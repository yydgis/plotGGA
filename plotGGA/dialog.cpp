#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setAxisLabel(QString& xLabel, QString& yLabel)
{
    ui->customPlot->xAxis->setLabel(xLabel);
    ui->customPlot->yAxis->setLabel(yLabel);
}

void Dialog::setData(QVector<double>& x, QVector<double>& y, QCPScatterStyle scatterStyle)
{
    dialog.ui->customPlot->addGraph();
    int index = ui->customPlot->graphCount();
    ui->customPlot->graph(index-1)->setLineStyle(QCPGraph::lsNone);
    ui->customPlot->graph(index-1)->setScatterStyle(scatterStyle);
    ui->customPlot->graph(index-1)->setData(x, y);

    ui->customPlot->xAxis->rescale(true);

    ui->customPlot->yAxis->rescale(true);

}
