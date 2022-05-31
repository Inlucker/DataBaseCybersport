#include "TeamWindow.h"
#include "ui_TeamWindow.h"

#include "Logger.h"

TeamWindow::TeamWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamWindow)
{
    ui->setupUi(this);
}

TeamWindow::~TeamWindow()
{
    delete ui;
}

void TeamWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button";
    this->hide();
    //moderator_controller->logout();
    emit exit();
}

