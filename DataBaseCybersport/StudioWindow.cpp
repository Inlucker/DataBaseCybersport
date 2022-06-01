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

    coms_table_model = make_shared<CommentatorsTableModel>();

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
    updateLists();
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
    shared_ptr<vector<CommentatorDTO>> coms_dto = commentator_repository->getCommentatorsDTOByStudioId(0);
    coms_table_model = make_shared<CommentatorsTableModel>(coms_dto);
    ui->free_tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->free_tableView->setModel(coms_table_model.get());
    for (int i = 0; i < coms_table_model->columnCount(); i++)
        ui->free_tableView->horizontalHeader()->setSectionResizeMode(i, QHeaderView::ResizeToContents);
}

void StudioWindow::updateLists()
{
    updateFreeCommentatorsList();
}

