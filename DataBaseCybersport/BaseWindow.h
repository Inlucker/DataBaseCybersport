#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <memory>

using namespace std;

#include "TeamWindow.h"
#include "StudioWindow.h"
#include "TournamentWindow.h"
#include "Repositorys/UsersRepository.h"
#include "Repositorys/UserRolesRepository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BaseWindow; }
QT_END_NAMESPACE

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

    void login(shared_ptr<UserBL> user_bl);

private slots:
    void on_login_btn_clicked();

    void resetBaseWindow();

    void on_registrate_btn_clicked();

private:
    Ui::BaseWindow *ui;

    unique_ptr<TeamWindow> team_window;
    unique_ptr<StudioWindow> studio_window;
    unique_ptr<TournamentWindow> tournament_window;

    shared_ptr<UsersRepository> user_repository;
    shared_ptr<UserRolesRepository> user_roles_repository;
};
#endif // BASEWINDOW_H
