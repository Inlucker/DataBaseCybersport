#include "StudioWindow.h"
#include "ui_StudioWindow.h"

#include "Logger.h"
#include "Settings.h"

StudioWindow::StudioWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StudioWindow)
{
    ui->setupUi(this);

    studio_controller = make_unique<StudioController>();

    commentator_repository = make_shared<CommentatorRepository>();

    ui->delete_user_btn->hide();
}

StudioWindow::~StudioWindow()
{
    delete ui;
}

void StudioWindow::login(shared_ptr<UserBL> user_bl, string role)
{
    studio_controller->login(user_bl);
    QVariant r(QString::fromStdString(role));
    Settings::set(Settings::DBUser, Settings::DataBase) = r;
    Settings::set(Settings::DBPass, Settings::DataBase) = r;
}

void StudioWindow::on_exit_btn_clicked()
{
    qInfo(logUserAction()) << "Pressed EXIT button in StudioWindow";
    this->hide();
    studio_controller->logout();
    emit exit();
}

void StudioWindow::updateFreeCommentatorsList()
{

}

