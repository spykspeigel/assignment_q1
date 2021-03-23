#include "MyFirstController.h"


MyFirstController::MyFirstController(mc_rbdyn::RobotModulePtr rm, double dt, const mc_rtc::Configuration & config)
: mc_control::MCController(rm, dt)
{
  jointIndex = robot().jointIndexByName(jointName);

  config_.load(config);
  solver().addConstraintSet(contactConstraint);
  solver().addConstraintSet(dynamicsConstraint);
  solver().addConstraintSet(selfCollisionConstraint);
  solver().addConstraintSet(*compoundJointConstraint);
  solver().addTask(postureTask);

    auto tasks_t = config("tasks");
//    auto tasks= mc_tasks::MetaTaskLoader::load<mc_tasks::EndEffectorTask>(solver(),"/home/robo/Documents/robotics/my_first_controller/etc/task.yaml");
//    solver().addTask(tasks);
   for (auto& t: tasks_t.keys()){
    
      tasks_.emplace_back(mc_tasks::MetaTaskLoader::load(solver(),tasks_t(t)));
      solver().addTask(tasks_.back());
   }

  postureTask->weight(1.0);
  postureTask->stiffness(1);
  //solver().setContacts({{}});
  solver().setContacts({
  	{robots(), 0, 1, "LeftFoot", "AllGround"},
  	{robots(), 0, 1, "RightFoot", "AllGround"}
  });
  mc_rtc::log::success("MyFirstController init done");
}

bool MyFirstController::run()
{

  return mc_control::MCController::run();
}

void MyFirstController::reset(const mc_control::ControllerResetData & reset_data)
{
  mc_control::MCController::reset(reset_data);

}


//namespace mc_control

CONTROLLER_CONSTRUCTOR("MyFirstController", MyFirstController)