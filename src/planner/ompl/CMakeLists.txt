#==============================================================================
# Dependencies
#
find_package(OMPL QUIET)
if(OMPL_FOUND)
  if("${OMPL_VERSION}" VERSION_LESS "1.0.0")
    message(STATUS "Looking for OMPL - found version ${OMPL_VERSION}, but"
                   " version 1.0.0 or later is required, skipping planer_ompl"
                   " component")
    return()
  else()
    message(STATUS "Looking for OMPL - version ${OMPL_VERSION} found")
  endif()
else()
  message(STATUS
    "Looking for OMPL - NOT found, skipping planner_ompl component")
  return()
endif()


#==============================================================================
# Libraries
#
set(sources 
  CRRT.cpp
  CRRTConnect.cpp
  dart.cpp
  GeometricStateSpace.cpp
  GoalRegion.cpp
  MotionValidator.cpp
  Planner.cpp
  StateSampler.cpp
  StateValidityChecker.cpp
)

add_library("${PROJECT_NAME}_planner_ompl" SHARED ${sources})
target_include_directories("${PROJECT_NAME}_planner_ompl" SYSTEM
  PUBLIC ${OMPL_INCLUDE_DIRS}
)
target_link_libraries("${PROJECT_NAME}_planner_ompl"
  "${PROJECT_NAME}_constraint"
  "${PROJECT_NAME}_distance"
  "${PROJECT_NAME}_statespace"
  "${PROJECT_NAME}_trajectory"
  ${DART_LIBRARIES}
  ${OMPL_LIBRARIES}
)

add_component(${PROJECT_NAME} planner_ompl)
add_component_targets(${PROJECT_NAME} planner_ompl "${PROJECT_NAME}_planner_ompl")
add_component_dependencies(${PROJECT_NAME} planner_ompl
  constraint
  distance
  planner
  statespace
  trajectory
)

coveralls_add_sources(${sources})
