#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "spicefile.h"
#include "op.h"
#include "ac.h"
#include "dc.h"
#include "tran.h"
#include "noise.h"
#include "pss.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    QString fileName;
    QString fileNameSim;
    QString netlistName;

    Op op;
    Ac ac;
    Dc dc;
    Tran tran;
    Noise noise;
    PSS pss;

    //int selected_source_index;

public:
    void readACconfig();
    void readDCconfig();
    void readTRANconfig();
    void readNOISEconfig();
    void readPSSconfig();

    void updateSimNetlist();

    void updateSourceTrans(int selected_source_index);

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionOpen_Spice_File_triggered();
    void on_actionBuild_Simulation_File_triggered();
    void on_actionRun_ngspice_triggered();
    void on_OP_checkBox_clicked();

    void on_AC_checkBox_clicked();

    void on_DC_checkBox_clicked();

    void on_TRAN_checkBox_clicked();

    void on_pushButtonApply_clicked();

    void on_checkBox_Override_clicked();

    void on_comboBox_Source_currentIndexChanged(int index);

    void on_pushButtonApply2_clicked();

    void on_NOISE_checkBox_clicked();

    void on_PSS_checkBox_clicked();

private:
    Ui::MainWindow *ui;
    SpiceFile spice;
};

#endif // MAINWINDOW_H
