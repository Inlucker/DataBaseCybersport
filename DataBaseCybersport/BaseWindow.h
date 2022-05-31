#ifndef BASEWINDOW_H
#define BASEWINDOW_H

#include <QMainWindow>
#include <memory>

using namespace std;

#include "TeamWindow.h"
#include "Repositorys/UsersRepository.h"

QT_BEGIN_NAMESPACE
namespace Ui { class BaseWindow; }
QT_END_NAMESPACE

class BaseWindow : public QMainWindow
{
    Q_OBJECT

public:
    BaseWindow(QWidget *parent = nullptr);
    ~BaseWindow();

private slots:
    void on_login_btn_clicked();

    void resetBaseWindow();

private:
    Ui::BaseWindow *ui;

    unique_ptr<TeamWindow> team_window;
    shared_ptr<UsersRepository> user_repository;
};
#endif // BASEWINDOW_H
