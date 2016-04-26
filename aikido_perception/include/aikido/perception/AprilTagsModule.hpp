/** 
 * @file AprilTagsModule.hpp
 * @author Shushman Choudhury
 * @date Apr 14, 2016
 * @brief The header for the April Tags detector. The function detectObjects
 * waits for the next ROS message on the specified topic.
 */

#ifndef AIKIDO_PERCEPTION_APRILTAGSMODULE_H
#define AIKIDO_PERCEPTION_APRILTAGSMODULE_H

#include <string>
#include <ros/ros.h>
#include <ros/forwards.h>
#include <ros/single_subscriber_publisher.h>
#include <aikido/perception/ConfigDataLoader.hpp>
#include <tf/transform_listener.h>
#include "yaml-cpp/yaml.h"

#include <dart/dart.h>
#include <aikido/util/CatkinResourceRetriever.hpp>

#include "PerceptionModule.hpp"


namespace aikido{
namespace perception{


class AprilTagsModule : public virtual PerceptionModule
{
public:
	//! The constructor for the April Tags detector
	/*!
		\param node the node handle to be passed to the detector
		\markerTopic the name of the topic on which april tags information is being published
		\configData the pointer to some configuration data loader
		\resourceRetriever a DART retriever for resources related to config files and models and so on
		\destinationFrame the desired TF for the detections
		\referenceLink a link on HERB with respect to which the pose is transformed
	*/
	AprilTagsModule(ros::NodeHandle node, std::string markerTopic, std::shared_ptr<ConfigDataLoader> configData,
					const dart::common::ResourceRetrieverPtr resourceRetriever,
					std::string destinationFrame, dart::dynamics::Frame* referenceLink);

	//!The virtual destructor
	virtual ~AprilTagsModule() = default;

	//! Implementation of the virtual method of PerceptionModule
	void detectObjects(std::vector<dart::dynamics::SkeletonPtr>& skeleton_list,double _timeout=10.0, ros::Time timestamp=ros::Time(0.0)) override; 


private:
	///The name of the ROS topic to read marker info from
	std::string mMarkerTopic;	

	///The desired reference frame for the object pose	
	std::string mReferenceFrameId;

	///To retrieve resources from disk and from packages
	dart::common::ResourceRetrieverPtr mResourceRetriever;
	
	///The reference frame of HERB to transform with respect to
	dart::dynamics::Frame* mReferenceLink;

	///The pointer to the loader of configuration data
	std::shared_ptr<ConfigDataLoader> mConfigData;

	///For the ROS node that will work with the April Tags module
	ros::NodeHandle mNode;

};

} //namespace perception
} //namespace aikido

#endif //AIKIDO_PERCEPTION_APRILTAGSMODULE_H