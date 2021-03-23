#pragma once

#include <mc_control/mc_controller.h>
#include <mc_tasks/CoMTask.h>

#include <mc_tasks/EndEffectorTask.h>
#include <mc_rtc/logging.h>
#include <mc_rtc/Configuration.h>
#include <mc_tasks/MetaTaskLoader.h>
#include "api.h"


struct MyFirstController_DLLAPI MyFirstController : public mc_control::MCController
{
    MyFirstController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config);

    bool run() override;

    void reset(const mc_control::ControllerResetData & reset_data) override;

    void switch_target();

    void switch_com_target();
private:
    mc_rtc::Configuration config_;
    int jointIndex = 0;
    bool goingLeft = true;
//    std::shared_ptr<mc_tasks::CoMTask> comTask;
    std::shared_ptr<mc_tasks::EndEffectorTask> efTask;
    std::vector<mc_tasks::MetaTaskPtr> tasks_;
    std::string jointName = "NECK_Y";
    Eigen::Vector3d comZero;
    bool comDown = true;
};
