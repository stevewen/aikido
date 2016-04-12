#include <aikido/distance/WeightedDistanceMetric.hpp>

namespace aikido
{
namespace distance
{
WeightedDistanceMetric::WeightedDistanceMetric(
    std::shared_ptr<statespace::CompoundStateSpace> _space,
    std::vector<DistanceMetricPtr> _metrics)
    : mStateSpace(std::move(_space))
    , mMetrics(std::move(_metrics))
    , mWeights(_metrics.size(), 1.0)
{
  if (mStateSpace->getNumStates() != mMetrics.size()) {
    throw std::invalid_argument(
        "Must provide a metric for every subspace in the CompoundStateSpace.");
  }
}

WeightedDistanceMetric::WeightedDistanceMetric(
    std::shared_ptr<statespace::CompoundStateSpace> _space,
    std::vector<DistanceMetricPtr> _metrics, std::vector<double> _weights)
    : mStateSpace(_space)
    , mMetrics(std::move(_metrics))
    , mWeights(std::move(_weights))
{
  if (mStateSpace->getNumStates() != mMetrics.size()) {
    throw std::invalid_argument(
        "Must provide a metric for every subspace in the CompoundStateSpace.");
  }

  if (mWeights.size() != mMetrics.size()) {
    throw std::invalid_argument("Must provide a weight for every metric.");
  }
}

double WeightedDistanceMetric::distance(
    const aikido::statespace::StateSpace::State* _state1,
    const aikido::statespace::StateSpace::State* _state2) const
{
  auto state1 =
      static_cast<const statespace::CompoundStateSpace::State*>(_state1);
  auto state2 =
      static_cast<const statespace::CompoundStateSpace::State*>(_state2);

  double dist = 0.0;
  for (size_t i = 0; i < mMetrics.size(); ++i) {
    dist += mWeights[i]
            * mMetrics[i]->distance(mStateSpace->getSubState<>(state1, i),
                                    mStateSpace->getSubState<>(state2, i));
  }
  return dist;
}

/// Computes the state that lies at time t in [0, 1] on the segment
/// that connects from state to to state. The memory location of state
/// is not required to be different from the memory of either from or to.
void WeightedDistanceMetric::interpolate(
    const aikido::statespace::StateSpace::State* _from,
    const aikido::statespace::StateSpace::State* _to, const double _t,
    aikido::statespace::StateSpace::State* _state) const
{
  auto from = static_cast<const statespace::CompoundStateSpace::State*>(_from);
  auto to = static_cast<const statespace::CompoundStateSpace::State*>(_to);
  auto state = static_cast<statespace::CompoundStateSpace::State*>(_state);

  for (size_t i = 0; i < mMetrics.size(); ++i) {
    mMetrics[i]->interpolate(mStateSpace->getSubState<>(from, i),
                             mStateSpace->getSubState<>(to, i), _t,
                             mStateSpace->getSubState<>(state, i));
  }
}
}
}