#ifndef AIKIDO_PLANNER_OMPL_UTIL_STATE_WRAPPER_HPP_
#define AIKIDO_PLANNER_OMPL_UTIL_STATE_WRAPPER_HPP_

#include <ompl/base/StateSpace.h>

namespace aikido {
namespace planner {
namespace ompl {

struct StateWrapper
{
  StateWrapper() {}
  StateWrapper(::ompl::base::StateSpacePtr space):
      space(space), state(space->allocState()) {}
  ~StateWrapper() { space->freeState(this->state); }

  const ::ompl::base::StateSpacePtr space;
  ::ompl::base::State *state;
};
typedef boost::shared_ptr<StateWrapper> StateWrapperPtr;

} // namespace ompl
} // namespace planner
} // namespace aikido

#endif // AIKIDO_PLANNER_OMPL_UTIL_STATE_WRAPPER_H_
