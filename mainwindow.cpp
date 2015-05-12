#include "mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QStringList>
#include <QLabel>
#include <multimeterdevice.h>
#include <iostream>
#include <stdio.h>

#include <qcustomplot.h>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    dev = new MultiMeterDevice(this);
    QWidget * center_widget = new QWidget;
    QVBoxLayout *main_layout = new QVBoxLayout;
    QHBoxLayout *control_bar_Layout = new QHBoxLayout;
/***Control bar initial***/
    QComboBox *ComboBoxModeSelect = new QComboBox;
    ComboBoxModeSelect->addItems(dev->get_measure_dev_list());
    ComboBoxModeSelect->show();

    control_bar_Layout->addWidget(ComboBoxModeSelect);


    ComboBoxRangeSelect = new QComboBox;
    ComboBoxRangeSelect->addItems(dev->getRangeStringList());

//    ComboBoxModeSelect->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed );
//    ComboBoxRangeSelect->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed );

    QObject::connect(ComboBoxModeSelect, SIGNAL(currentIndexChanged(int)), \
                     dev, SLOT(ModeChanged(int)));
    QObject::connect(ComboBoxRangeSelect, SIGNAL(currentIndexChanged(int)),\
                     dev, SLOT(RangeChanged(int)));
    QObject::connect(dev, SIGNAL(RangeListChanged(const QStringList &)), \
                     this, SLOT(RangeListUpdate(const QStringList &)));

    control_bar_Layout->addWidget(ComboBoxRangeSelect);

    main_layout->addLayout(control_bar_Layout);

    QHBoxLayout *value_layout = new QHBoxLayout;
    value_label = new QLabel;
    value_label->setText("----------------");
    QFont ft;
    ft.setPointSize(28);
    value_label->setFont(ft);
    value_label->adjustSize();
    value_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed );

    units_label = new QLabel;
    units_label->setText("mV");
    units_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed );

//    units_label->setFont(ft);
    value_layout->addWidget(value_label);
    value_layout->addWidget(units_label);

    main_layout->addLayout(value_layout);

    QLabel *oriadc = new QLabel;
    oriadc->setText("OriAdc");
    oriadc->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed );

    value_layout->addWidget(oriadc);

    //this->layout()->addWidget(mainwidget);
//    //
    QObject::connect(dev, SIGNAL(ValueChanged(const QString &)), value_label,SLOT(setText(const QString &)));
    QObject::connect(dev, SIGNAL(UnitChanged(const QString &)), units_label,SLOT(setText(const QString &)));
    QObject::connect(dev, SIGNAL(OriginalAdcChanged(QString)), oriadc,SLOT(setText(const QString &)));

    QHBoxLayout *grap_Layout = new QHBoxLayout;

    QCustomPlot *customPlot = new QCustomPlot;
//    customPlot->setBaseSize(500,600);//
//    customPlot->setMinimumSize(480, 320);
//customPlot->setMaximumSize(480,240);

    QVector<double> x(101), y(101);
    for(int i=0; i<101; i++){
        x[i] = i/50.0 -1;
        y[i] = x[i] * x[i];
    }
    // create graph and assign data to it:
    customPlot->addGraph();
//    customPlot->setMaximumSize(QSize(320,200));
    customPlot->graph(0)->setData(x, y);
    // give the axes some labels:
//    customPlot->xAxis->setLabel("x");
 //   customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    customPlot->xAxis->setRange(-1, 1);
    customPlot->yAxis->setRange(0, 1);
    customPlot->replot();

    customPlot->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding );

    grap_Layout->addWidget(customPlot);

    main_layout->addLayout(grap_Layout);
main_layout->SetMinimumSize;

    center_widget->setLayout(main_layout);
    this->setCentralWidget(center_widget);
    this->setMinimumSize(QSize(320, 240));
//    this->setLayout(main_layout);

    this->show();
    std::cout<<"Windows Height:"<< main_layout->sizeHint().height()<<std::endl;
}

void MainWindow::setValue(const QString val){
//    std::cout<<" MainWindow::setValue "<<std::endl;
    value_label->setText(val);
}
void MainWindow::setUint(const QString unit){

}

void MainWindow::RangeListUpdate(const QStringList & rl){
    ComboBoxRangeSelect->clear();
    ComboBoxRangeSelect->addItems(rl);
}
//void MainWindow::set_value(unsigned long val)
//{
//    static char buf[20];
//    sprintf(buf,"%ld",val);
//    value_label->setText(buf);
////    std::cout<<"set value"<< val <<std::endl;
//}


MainWindow::~MainWindow()
{

}
