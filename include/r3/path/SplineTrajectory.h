#ifndef SPLINETRAJECTORY_H_
#define SPLINETRAJECTORY_H_
#include <Eigen/Dense>
#include <dart/dynamics/dynamics.h>
#include <r3/path/Trajectory.h>

namespace r3 {
namespace path {

class SplineTrajectory : public Trajectory {
public:
  struct Knot {
    double t;
    Eigen::MatrixXd values;
  };

  SplineTrajectory(
    std::vector<dart::dynamics::DegreeOfFreedomPtr> const &dofs,
    std::vector<Knot> const &knots, size_t order);

  virtual ~SplineTrajectory();

  virtual size_t order() const;
  virtual double start_time() const;
  virtual double end_time() const;
  virtual double duration() const;

  virtual std::string const &type() const;
  static std::string const &static_type();

  virtual double sample(double t, size_t order) const;

private:
  size_t order_;
  std::vector<dart::dynamics::DegreeOfFreedomPtr> dofs_;
  std::vector<Knot> knots_;
};

}
}

#endif
