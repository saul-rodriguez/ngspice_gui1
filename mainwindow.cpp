#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfiledialog.h>
#include <QTextStream>
#include <QProcess>
#include "voltagesource.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEditOP_TEMP->setText("27");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionOpen_Spice_File_triggered()
{
    //QMessageBox("Hola");
    fileName = QFileDialog::getOpenFileName(this,
        tr("Open SPICE File"), "~", tr("Spice Files(*.cir)"));

    QFileInfo fi(fileName);
    QString name = fi.fileName();

    if (!name.compare(""))
        return;

    QStringList aux = name.split(".");

    netlistName = aux[0];

    fileNameSim = fi.path() + "/" + aux[0] + "_sim.cir";

    spice.readSpice(fileName);

    ui->plainTextEditNetlist->clear();

    for (int i=0; i < spice.fileSize; i++) {
        ui->plainTextEditNetlist->appendPlainText(spice.fileLines[i]);
    }

    ui->plainTextEditNetlist->appendPlainText(".end"); //We removed .end from the string buffer

    ui->plainTextEditNetlist->setReadOnly(true);

    //Update source combobox

    int num = ui->comboBox_Source->count();


    for (int i=0; i<NUM_SOURCES; i++) {
        ui->comboBox_Source->removeItem(i);
    }
    //ui->comboBox_Source->clear();
    //int num = ui->comboBox_Source->count();


    for (int i=0; i<spice.SourceNum; i++) {
        ui->comboBox_Source->insertItem(i,spice.source[i].name);
    }

    for (int i=spice.SourceNum; i<NUM_SOURCES; i++) {
        ui->comboBox_Source->removeItem(i);
    }

}

void MainWindow::on_actionBuild_Simulation_File_triggered()
{

    QString control = "";
    QString before = ui->plainTextEditAddBefore->toPlainText();
    QString after = ui->plainTextEditAddAfter->toPlainText();

    //Add simulation parameters coming before a control section
    control += ".TEMP ";
    control += ui->lineEditOP_TEMP->text();
    control += "\n";

    // Add manual control lines before analysis
    control += ".control\n";
    control += "set noaskquit\n";
    control += before;
    control += "\n";


    //Update the control section based on analysis objects
    if (op.enable) {
        control += op.option;
    }

    if (dc.enable) {
        readDCconfig();
        control += dc.option;
    }

    if (ac.enable) {
        readACconfig();
        control += ac.option;
    }

    if (tran.enable) {
        readTRANconfig();
        control += tran.option;
    }

    if (noise.enable) {
        readNOISEconfig();
        control += noise.option;
    }

    if (pss.enable) {
        readPSSconfig();
        control += pss.option;
    }

    // Add manual control lines after analysis
    control += after;
    control += "\nrusage all\n";
    control += ".endc\n";

    spice.control = control;


    //Write the Spice Simulation File
    spice.writeSpice(fileNameSim);


    //Read the simulation file and
    QFile file(fileNameSim);

    if(!file.open(QIODevice::ReadOnly)) {
            qDebug("error opening file");
    }

    QTextStream in(&file);
    QString db = in.readAll();
    file.close();

    //ui->plainTextEditSim->clear();
    ui->plainTextEditSim->setPlainText(db);
}


void MainWindow::on_actionRun_ngspice_triggered()
{
    //Update the simulation with the latest changes from the simulation tab
    updateSimNetlist();

    QString command;
    //command = "/usr/local/bin/ngspice -n -b";
    //command += " -o ";
    //command += netlistName;
    //command += ".log";
    //command += " -r ";
    //command += netlistName;
    //command += ".raw ";

    command = "/usr/local/bin/ngspice ";
    command += fileNameSim;

    QProcess* process;

    process = new QProcess(this);

    /*
    //process.start("gnome-terminal",QStringList() << "-e" << "ngspice a.cir");
    process.start("gnome-terminal",QStringList() << "-e" << command);
    //process.start("xterm",QStringList() << "-e" << command);

   // process.waitForStarted();
   // process.write("ls\n");
    process.waitForFinished(-1);
*/
    process->start("gnome-terminal",QStringList() << "-e" << command);

}

void MainWindow::updateSimNetlist()
{

    QString netlist;

    netlist = ui->plainTextEditSim->toPlainText();

    QFile fout(fileNameSim);

    if(!fout.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug("error opening writing file");
    }

    QTextStream stream( &fout);

    stream << netlist;

    fout.close();


}

void MainWindow::on_OP_checkBox_clicked()
{
    bool state;

    state = ui->OP_checkBox->isChecked();

    if (state) {
        op.enable = true;
    } else {
        op.enable = false;
    }

}

void MainWindow::readACconfig()
{
    if (ui->radioButtonAC_Dec->isChecked()) {
        ac.scale = "dec";
    } else if (ui->radioButtonAC_Lin->isChecked()) {
        ac.scale = "lin";
    } else if (ui->radioButtonAC_Oct->isChecked()) {
        ac.scale = "oct";
    }

    ac.startFrec = ui->lineEditAC_Start->text();
    ac.stopFrec = ui->lineEditAC_Stop->text();
    ac.step = ui->lineEditAC_Step->text();

    ac.getControl();

}

void MainWindow::on_AC_checkBox_clicked()
{
    bool state;

    state = ui->AC_checkBox->isChecked();

    if (state) {
        ac.enable = true;
    } else {
        ac.enable = false;
    }
}

void MainWindow::readDCconfig() {
    dc.src1 = ui->lineEditDC_Src->text();
    dc.start1 = ui->lineEditDC_Start->text();
    dc.stop1 = ui->lineEditDC_Stop->text();
    dc.step1 = ui->lineEditDC_Step->text();

    dc.src2 = ui->lineEditDC_Src2->text();
    dc.start2 = ui->lineEditDC_Start2->text();
    dc.stop2 = ui->lineEditDC_Stop2->text();
    dc.step2 = ui->lineEditDC_Step2->text();

    dc.getControl();
}

void MainWindow::on_DC_checkBox_clicked()
{
    bool state;

    state = ui->DC_checkBox->isChecked();

    if (state) {
        dc.enable = true;
    } else {
        dc.enable = false;
    }
}

void MainWindow::readTRANconfig()
{
    tran.step = ui->lineEditTRAN_step->text();
    tran.stop = ui->lineEditTRAN_stop->text();
    tran.start = ui->lineEditTRAN_start->text();
    tran.max = ui->lineEditTRAN_tmax->text();
    tran.uic = ui->TRAN_uic_checkBox->isChecked();

    tran.getControl();
}


void MainWindow::on_TRAN_checkBox_clicked()
{
    bool state;

    state = ui->TRAN_checkBox->isChecked();

    if (state) {
        tran.enable = true;
    } else {
        tran.enable = false;
    }
}


void MainWindow::on_pushButtonApply_clicked()
{
    int selected_index = ui->comboBox_Source->currentIndex();

    if (selected_index == -1) return; //not source selected

    spice.source[selected_index].option = "";

    if(ui->checkBox_Override->isChecked()) {
        spice.source[selected_index].enable = true;
    } else {
        spice.source[selected_index].enable = false;
    }


    if(ui->checkBox_DC->isChecked()) { //DC
        spice.source[selected_index].dc_enable = true;
        spice.source[selected_index].dc = ui->lineEdit_DC->text();
    } else {
        spice.source[selected_index].dc_enable = false;
        spice.source[selected_index].dc = "";
    }

    if(ui->checkBox_AC->isChecked()) { // AC
        spice.source[selected_index].ac_enable = true;
        spice.source[selected_index].ac = ui->lineEdit_AC->text();
        spice.source[selected_index].acphase = ui->lineEdit_AC_PHASE->text();
    } else {
        spice.source[selected_index].ac_enable = false;
        spice.source[selected_index].ac = "";
        spice.source[selected_index].acphase = "";
    }

    //Read independent transient manual configuration tab info
    updateSourceTrans(selected_index);

    //Create a option line including all the manually added options
    spice.source[selected_index].prepareOption();

}

void MainWindow::on_checkBox_Override_clicked()
{
    on_pushButtonApply_clicked();
}


void MainWindow::on_comboBox_Source_currentIndexChanged(int index)
{
    QString aux = "Source: " + spice.source[index].name;
    ui->labelSOURCE->setText(aux);
    //selected_source_index = index;
    //override enable
    ui->checkBox_Override->setChecked(spice.source[index].enable);

    //DC
    ui->checkBox_DC->setChecked(spice.source[index].dc_enable);
    ui->lineEdit_DC->setText(spice.source[index].dc);

    //AC
    ui->checkBox_AC->setChecked(spice.source[index].ac_enable);
    ui->lineEdit_AC->setText(spice.source[index].ac);
    ui->lineEdit_AC_PHASE->setText(spice.source[index].acphase);

    //TRAN SIN
    ui->lineEditSIN_VO->setText(spice.source[index].sin_vo);
    ui->lineEditSIN_VA->setText(spice.source[index].sin_va);
    ui->lineEditSIN_FREQ->setText(spice.source[index].sin_freq);
    ui->lineEditSIN_TD->setText(spice.source[index].sin_td);
    ui->lineEditSIN_THETA->setText(spice.source[index].sin_theta);

    //TRAN PULSE
    ui->lineEditPULSE_V1->setText(spice.source[index].pulse_v1);
    ui->lineEditPULSE_V2->setText(spice.source[index].pulse_v2);
    ui->lineEditPULSE_TD->setText(spice.source[index].pulse_td);
    ui->lineEditPULSE_TR->setText(spice.source[index].pulse_tr);
    ui->lineEditPULSE_TF->setText(spice.source[index].pulse_tf);
    ui->lineEditPULSE_PW->setText(spice.source[index].pulse_pw);
    ui->lineEditPULSE_PER->setText(spice.source[index].pulse_per);

    //EXP
    ui->lineEditEXP_V1->setText(spice.source[index].exp_v1);
    ui->lineEditEXP_V2->setText(spice.source[index].exp_v2);
    ui->lineEditEXP_TD1->setText(spice.source[index].exp_td1);
    ui->lineEditEXP_TAU1->setText(spice.source[index].exp_tau1);
    ui->lineEditEXP_TD2->setText(spice.source[index].exp_td2);
    ui->lineEditEXP_TAU2->setText(spice.source[index].exp_tau2);

    //PWL
    ui->lineEditPWL->setText(spice.source[index].pwl);

    //AM
    ui->lineEditAM_VA->setText(spice.source[index].am_va);
    ui->lineEditAM_VO->setText(spice.source[index].am_vo);
    ui->lineEditAM_MF->setText(spice.source[index].am_mf);
    ui->lineEditAM_FC->setText(spice.source[index].am_fc);
    ui->lineEditAM_TD->setText(spice.source[index].am_td);

    //FM
    ui->lineEditFM_VO->setText(spice.source[index].fm_vo);
    ui->lineEditFM_VA->setText(spice.source[index].fm_va);
    ui->lineEditFM_FC->setText(spice.source[index].fm_fc);
    ui->lineEditFM_MDI->setText(spice.source[index].fm_mdi);
    ui->lineEditFM_FS->setText(spice.source[index].fm_fs);

    //NOISE
    ui->lineEditNOISE_NA->setText(spice.source[index].noise_na);
    ui->lineEditNOISE_NT->setText(spice.source[index].noise_nt);
    ui->lineEditNOISE_NALPHA->setText(spice.source[index].noise_nalpha);
    ui->lineEditNOISE_NAMP->setText(spice.source[index].noise_namp);
    ui->lineEditNOISE_RTSAM->setText(spice.source[index].noise_rtsam);
    ui->lineEditNOISE_RTSCAPT->setText(spice.source[index].noise_rtscapt);
    ui->lineEditNOISE_RTSEMT->setText(spice.source[index].noise_rtsemt);

    int taux = spice.source[index].tran_source;
    switch (taux) {
        case NONE:
                    ui->radioButtonNONE->setChecked(true);
                    break;
        case SIN:
                    ui->radioButtonSIN->setChecked(true);
                    break;
        case PULSE:
                    ui->radioButtonPULSE->setChecked(true);
                    break;
        case EXP:
                    ui->radioButtonEXP->setChecked(true);
                    break;
        case PWL:
                    ui->radioButtonPWL->setChecked(true);
                    break;
        case AM:
                    ui->radioButtonAM->setChecked(true);
                    break;
        case FM:
                    ui->radioButtonAM->setChecked(true);
                    break;
        case TRNOISE:
                    ui->radioButtonNOISE->setChecked(true);
                    break;
        default:
                    break;
    }
}

void MainWindow::updateSourceTrans(int selected_source_index)
{
    if(ui->radioButtonNONE->isChecked()) { // No indep. transient source
        spice.source[selected_source_index].tran_source = NONE;

    } else if (ui->radioButtonSIN->isChecked()) { // SIN source
        spice.source[selected_source_index].tran_source = SIN;
        spice.source[selected_source_index].sin_vo = ui->lineEditSIN_VO->text();
        spice.source[selected_source_index].sin_va = ui->lineEditSIN_VA->text();
        spice.source[selected_source_index].sin_freq = ui->lineEditSIN_FREQ->text();
        spice.source[selected_source_index].sin_td = ui->lineEditSIN_TD->text();
        spice.source[selected_source_index].sin_theta = ui->lineEditSIN_THETA->text();


    } else if (ui->radioButtonPULSE->isChecked()) { //PULSE
        spice.source[selected_source_index].tran_source = PULSE;
        spice.source[selected_source_index].pulse_v1 = ui->lineEditPULSE_V1->text();
        spice.source[selected_source_index].pulse_v2 = ui->lineEditPULSE_V2->text();
        spice.source[selected_source_index].pulse_td = ui->lineEditPULSE_TD->text();
        spice.source[selected_source_index].pulse_tr = ui->lineEditPULSE_TR->text();
        spice.source[selected_source_index].pulse_tf = ui->lineEditPULSE_TF->text();
        spice.source[selected_source_index].pulse_pw = ui->lineEditPULSE_PW->text();
        spice.source[selected_source_index].pulse_per = ui->lineEditPULSE_PER->text();

    } else if (ui->radioButtonEXP->isChecked()) { //EXP
        spice.source[selected_source_index].tran_source = EXP;
        spice.source[selected_source_index].exp_v1 = ui->lineEditEXP_V1->text();
        spice.source[selected_source_index].exp_v2 = ui->lineEditEXP_V2->text();
        spice.source[selected_source_index].exp_td1 = ui->lineEditEXP_TD1->text();
        spice.source[selected_source_index].exp_tau1 = ui->lineEditEXP_TAU1->text();
        spice.source[selected_source_index].exp_td2 = ui->lineEditEXP_TD2->text();
        spice.source[selected_source_index].exp_tau2 = ui->lineEditEXP_TAU2->text();

    } else if (ui->radioButtonPWL->isChecked()) { //PWL
        spice.source[selected_source_index].tran_source = PWL;
        spice.source[selected_source_index].pwl = ui->lineEditPWL->text();

    } else if (ui->radioButtonFM->isChecked()) { //FM
        spice.source[selected_source_index].tran_source = FM;
        spice.source[selected_source_index].fm_vo = ui->lineEditFM_VO->text();
        spice.source[selected_source_index].fm_va = ui->lineEditFM_VA->text();
        spice.source[selected_source_index].fm_fc = ui->lineEditFM_FC->text();
        spice.source[selected_source_index].fm_mdi = ui->lineEditFM_MDI->text();
        spice.source[selected_source_index].fm_fs = ui->lineEditFM_FS->text();


    } else if (ui->radioButtonAM->isChecked()) { //AM
        spice.source[selected_source_index].tran_source = AM;
        spice.source[selected_source_index].am_va = ui->lineEditAM_VA->text();
        spice.source[selected_source_index].am_vo = ui->lineEditAM_VO->text();
        spice.source[selected_source_index].am_mf = ui->lineEditAM_MF->text();
        spice.source[selected_source_index].am_fc = ui->lineEditAM_FC->text();
        spice.source[selected_source_index].am_td = ui->lineEditAM_TD->text();

    } else if (ui->radioButtonNOISE->isChecked()) { //TRNOISE
        spice.source[selected_source_index].tran_source = TRNOISE;
        spice.source[selected_source_index].noise_na = ui->lineEditNOISE_NA->text();
        spice.source[selected_source_index].noise_nt = ui->lineEditNOISE_NT->text();
        spice.source[selected_source_index].noise_nalpha = ui->lineEditNOISE_NALPHA->text();
        spice.source[selected_source_index].noise_namp = ui->lineEditNOISE_NAMP->text();
        spice.source[selected_source_index].noise_rtsam = ui->lineEditNOISE_RTSAM->text();
        spice.source[selected_source_index].noise_rtscapt = ui->lineEditNOISE_RTSCAPT->text();
        spice.source[selected_source_index].noise_rtsemt = ui->lineEditNOISE_RTSEMT->text();

    }


}

void MainWindow::on_pushButtonApply2_clicked()
{
    on_pushButtonApply_clicked();
}

void MainWindow::readNOISEconfig()
{
    if (ui->radioButtonNO_Dec->isChecked()) {
        noise.scale = "dec";
    } else if (ui->radioButtonNO_Lin->isChecked()) {
        noise.scale = "lin";
    } else if (ui->radioButtonNO_Oct->isChecked()) {
        noise.scale = "oct";
    }

    noise.vout = ui->lineEditNO_VOUT->text();
    noise.vref = ui->lineEditNO_VREF->text();
    noise.src = ui->lineEditNO_SRC->text();
    noise.pts = ui->lineEditNO_Step->text();
    noise.fstart = ui->lineEditNO_Start->text();
    noise.fstop = ui->lineEditNO_Stop->text();
    noise.pts_per_sum = ui->lineEditNO_PTS_PER_SUM->text();

    noise.getControl();
}

void MainWindow::on_NOISE_checkBox_clicked()
{
    bool state;

    state = ui->NOISE_checkBox->isChecked();

    if (state) {
        noise.enable = true;
    } else {
        noise.enable = false;
    }
}

void MainWindow::on_PSS_checkBox_clicked()
{
    bool state;

    state = ui->PSS_checkBox->isChecked();

    if (state) {
        pss.enable = true;
    } else {
        pss.enable = false;
    }
}

void MainWindow::readPSSconfig()
{
    pss.gfreq = ui->lineEditPSS_gfreq->text();
    pss.tstab = ui->lineEditPSS_tstab->text();
    pss.oscnob = ui->lineEditPSS_oscnob->text();
    pss.psspoints = ui->lineEditPSS_psspoints->text();
    pss.harms = ui->lineEditPSS_harms->text();
    pss.sciter = ui->lineEditPSS_sciter->text();
    pss.steadycoeff = ui->lineEditPSS_steadycoeff->text();

    pss.uic = ui->PSS_uic_checkBox->isChecked();

    pss.getControl();


}


