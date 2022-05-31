#include "BaseWindow.h"
#include "ui_BaseWindow.h"

#include <QMessageBox>

#include "Settings.h"

BaseWindow::BaseWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::BaseWindow)
{
    ui->setupUi(this);

    team_window = make_unique<TeamWindow>();
    connect(team_window.get(), SIGNAL(exit()), this, SLOT(resetBaseWindow()));

    user_repository = make_shared<UsersRepository>();
}

BaseWindow::~BaseWindow()
{
    delete ui;
}


void BaseWindow::on_login_btn_clicked()
{
    try
    {
        qInfo(logUserAction()) << "Pressed on login button";
        string login = ui->login_lineEdit->text().toStdString();
        string password = ui->password_lineEdit->text().toStdString();
        shared_ptr<UserBL> user_bl = user_repository->getUser(login, password);
        if (user_bl->getRoleId() == 4)
        {
            //team_window->login(user_bl);
            team_window->show();
            this->hide();
        }
        else
        {
            QMessageBox::information(this, "Error", "No such role");
        }
        qInfo(logUserAction()) << "Login completed";
    }
    catch (BaseError &er)
    {
        resetBaseWindow();
        QMessageBox::information(this, "Error", er.what());
    }
    catch (...)
    {
        QMessageBox::information(this, "Error", "Unexpected Error");
    }
}

void BaseWindow::resetBaseWindow()
{
    this->show();
    Settings::set(Settings::DBUser, Settings::DataBase) = "guest";
    Settings::set(Settings::DBPass, Settings::DataBase) = "guest";
}

