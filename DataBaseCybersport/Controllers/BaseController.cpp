#include "BaseController.h"

BaseController::BaseController()
{
    user = make_shared<UserBL>();
}

BaseController::BaseController(shared_ptr<UserBL> u)
{
    user = u;
}


void BaseController::login(shared_ptr<UserBL> u)
{
    user = u;
}

void BaseController::logout() noexcept
{
    user.reset();
}

shared_ptr<UserBL> BaseController::getUser() noexcept
{
    return user;
}
