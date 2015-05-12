#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "multimeterdevice.h"
class QLabel;
class QStringList;
class QComboBox;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
//    void set_value(unsigned long val);
    void setValue(const QString val);
    void setUint(const QString unit);
    void RangeListUpdate(const QStringList &);
private:
    MultiMeterDevice *dev;
    QLabel *value_label;
    QLabel * units_label;
    QComboBox *ComboBoxRangeSelect;

};

#endif // MAINWINDOW_H
