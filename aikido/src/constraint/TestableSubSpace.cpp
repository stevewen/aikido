#include <dart/common/StlHelpers.h>
#include <aikido/constraint/TestableSubSpace.hpp>

namespace aikido
{
namespace constraint
{
using dart::common::make_unique;

//=============================================================================
TestableSubSpace::TestableSubSpace(
    std::shared_ptr<statespace::CompoundStateSpace> _stateSpace,
    std::vector<std::shared_ptr<TestableConstraint>> _constraints)
    : mStateSpace(std::move(_stateSpace))
    , mConstraints(std::move(_constraints))
{
  if (mConstraints.size() != mStateSpace->getNumStates()) {
    std::stringstream msg;
    msg << "Mismatch between size of CompoundStateSpace and the number of"
        << " constraints: " << mStateSpace->getNumStates()
        << " != " << mConstraints.size() << ".";
    throw std::invalid_argument(msg.str());
  }

  for (size_t i = 0; i < mStateSpace->getNumStates(); ++i) {
    if (mConstraints[i]->getStateSpace() != mStateSpace->getSubSpace<>(i)) {
      std::stringstream msg;
      msg << "Constraint " << i << " is not defined over this StateSpace.";
      throw std::invalid_argument(msg.str());
    }
  }
}

//=============================================================================
statespace::StateSpacePtr TestableSubSpace::getStateSpace() const
{
  return mStateSpace;
}

//=============================================================================
bool TestableSubSpace::isSatisfied(
    const aikido::statespace::StateSpace::State* state) const
{
  for (size_t i = 0; i < mStateSpace->getNumStates(); ++i) {
    auto subState = mStateSpace->getSubState<>(state, i);
    if (!mConstraints[i]->isSatisfied(subState)) {
      return false;
    }
  }
  return true;
}

}  // namespace constraint
}  // namespace aikido