#include "choisemodewindow.h"
#include "ui_choisemodewindow.h"

ChoiseModeWindow::ChoiseModeWindow(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ChoiseModeWindow)
{
    ui->setupUi(this);
}

ChoiseModeWindow::~ChoiseModeWindow()
{
    delete ui;
}
