#include "TeamWindow.h"
#include "ui_TeamWindow.h"

#include "Logger.h"
#include "Settings.h"

TeamWindow::TeamWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeamWindow)
{
    ui->setupUi(this);

    team_controller = make_unique<TeamController>();
}

TeamWindow::~TeamWindow()
{
    delete ui;
}

void TeamWindow::login(shared_ptr<UserBL> user_bl, string role)
{
    team_controller->login(user_bl);
    //users_repository->setRole(user_bl->getRole(), user_bl->getRole());
    QVariant r(QString::fromStdString(role));
    Settings::set(Settings::DBUser, Settings::DataBase) = r;
    Settings::set(Settings::DBPass, Settings::DataBase) = r;
    updateFreePlayersList();
    //updateMyPlayerList();
}

void TeamWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button";
    this->hide();
    team_controller->logout();
    emit exit();
}

void TeamWindow::updateFreePlayersList()
{

}

