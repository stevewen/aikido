/** 
 * @file YamlFileLoader.hpp
 * @author Shushman Choudhury
 * @date Apr 20, 2016
 * @brief The header for the instance of the configuration data loader 
 * for marker-based perception which reads a YAML file.
 */

#ifndef AIKIDO_PERCEPTION_YAML_FILE_LOADER_H
#define AIKIDO_PERCEPTION_YAML_FILE_LOADER_H

#include "yaml-cpp/yaml.h"
#include <aikido/perception/eigen_yaml.hpp>
#include <aikido/util/CatkinResourceRetriever.hpp>
#include <dart/common/LocalResourceRetriever.h>
#include <dart/dart.h>
#include <Eigen/Geometry>
#include "ConfigDataLoader.hpp"
#include <stdexcept>

namespace aikido{
namespace perception{

class YamlFileLoader : public virtual ConfigDataLoader
{
public:

    //! The constructor for YAML Loader
    /*!
        \param resourceRetriever the pointer to obtain the config. file
        \param configDataURI the URI for the configuration information file
    */
    YamlFileLoader(const dart::common::ResourceRetrieverPtr& resourceRetriever,
                   dart::common::Uri configDataURI);

    //! The virtual destructor
    virtual ~YamlFileLoader() = default;

    //! The implementation of the virtual method from ConfigDataLoader
    bool getTagNameOffset(const std::string& _tagName, std::string& body_name, dart::common::Uri& body_resource, Eigen::Isometry3d& body_offset) override;

private:

    ///The map of tag IDs to object name, resource for model and offset
    YAML::Node mTagData;
};


} //namespace perception

} //namespace aikido

#endif //AIKIDO_PERCEPTION_YAML_FILE_LOADER_H