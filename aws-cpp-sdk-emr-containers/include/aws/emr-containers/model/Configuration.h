﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/emr-containers/EMRContainers_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/core/utils/memory/stl/AWSMap.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <utility>

namespace Aws
{
namespace Utils
{
namespace Json
{
  class JsonValue;
  class JsonView;
} // namespace Json
} // namespace Utils
namespace EMRContainers
{
namespace Model
{

  /**
   * <p>A configuration specification to be used when provisioning virtual clusters,
   * which can include configurations for applications and software bundled with
   * Amazon EMR on EKS. A configuration consists of a classification, properties, and
   * optional nested configurations. A classification refers to an
   * application-specific configuration file. Properties are the settings you want to
   * change in that file.</p><p><h3>See Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/emr-containers-2020-10-01/Configuration">AWS
   * API Reference</a></p>
   */
  class AWS_EMRCONTAINERS_API Configuration
  {
  public:
    Configuration();
    Configuration(Aws::Utils::Json::JsonView jsonValue);
    Configuration& operator=(Aws::Utils::Json::JsonView jsonValue);
    Aws::Utils::Json::JsonValue Jsonize() const;


    /**
     * <p>The classification within a configuration.</p>
     */
    inline const Aws::String& GetClassification() const{ return m_classification; }

    /**
     * <p>The classification within a configuration.</p>
     */
    inline bool ClassificationHasBeenSet() const { return m_classificationHasBeenSet; }

    /**
     * <p>The classification within a configuration.</p>
     */
    inline void SetClassification(const Aws::String& value) { m_classificationHasBeenSet = true; m_classification = value; }

    /**
     * <p>The classification within a configuration.</p>
     */
    inline void SetClassification(Aws::String&& value) { m_classificationHasBeenSet = true; m_classification = std::move(value); }

    /**
     * <p>The classification within a configuration.</p>
     */
    inline void SetClassification(const char* value) { m_classificationHasBeenSet = true; m_classification.assign(value); }

    /**
     * <p>The classification within a configuration.</p>
     */
    inline Configuration& WithClassification(const Aws::String& value) { SetClassification(value); return *this;}

    /**
     * <p>The classification within a configuration.</p>
     */
    inline Configuration& WithClassification(Aws::String&& value) { SetClassification(std::move(value)); return *this;}

    /**
     * <p>The classification within a configuration.</p>
     */
    inline Configuration& WithClassification(const char* value) { SetClassification(value); return *this;}


    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline const Aws::Map<Aws::String, Aws::String>& GetProperties() const{ return m_properties; }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline bool PropertiesHasBeenSet() const { return m_propertiesHasBeenSet; }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline void SetProperties(const Aws::Map<Aws::String, Aws::String>& value) { m_propertiesHasBeenSet = true; m_properties = value; }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline void SetProperties(Aws::Map<Aws::String, Aws::String>&& value) { m_propertiesHasBeenSet = true; m_properties = std::move(value); }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline Configuration& WithProperties(const Aws::Map<Aws::String, Aws::String>& value) { SetProperties(value); return *this;}

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline Configuration& WithProperties(Aws::Map<Aws::String, Aws::String>&& value) { SetProperties(std::move(value)); return *this;}

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline Configuration& AddProperties(const Aws::String& key, const Aws::String& value) { m_propertiesHasBeenSet = true; m_properties.emplace(key, value); return *this; }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline Configuration& AddProperties(Aws::String&& key, const Aws::String& value) { m_propertiesHasBeenSet = true; m_properties.emplace(std::move(key), value); return *this; }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline Configuration& AddProperties(const Aws::String& key, Aws::String&& value) { m_propertiesHasBeenSet = true; m_properties.emplace(key, std::move(value)); return *this; }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline Configuration& AddProperties(Aws::String&& key, Aws::String&& value) { m_propertiesHasBeenSet = true; m_properties.emplace(std::move(key), std::move(value)); return *this; }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline Configuration& AddProperties(const char* key, Aws::String&& value) { m_propertiesHasBeenSet = true; m_properties.emplace(key, std::move(value)); return *this; }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline Configuration& AddProperties(Aws::String&& key, const char* value) { m_propertiesHasBeenSet = true; m_properties.emplace(std::move(key), value); return *this; }

    /**
     * <p>A set of properties specified within a configuration classification.</p>
     */
    inline Configuration& AddProperties(const char* key, const char* value) { m_propertiesHasBeenSet = true; m_properties.emplace(key, value); return *this; }


    /**
     * <p>A list of additional configurations to apply within a configuration
     * object.</p>
     */
    inline const Aws::Vector<Configuration>& GetConfigurations() const{ return m_configurations; }

    /**
     * <p>A list of additional configurations to apply within a configuration
     * object.</p>
     */
    inline bool ConfigurationsHasBeenSet() const { return m_configurationsHasBeenSet; }

    /**
     * <p>A list of additional configurations to apply within a configuration
     * object.</p>
     */
    inline void SetConfigurations(const Aws::Vector<Configuration>& value) { m_configurationsHasBeenSet = true; m_configurations = value; }

    /**
     * <p>A list of additional configurations to apply within a configuration
     * object.</p>
     */
    inline void SetConfigurations(Aws::Vector<Configuration>&& value) { m_configurationsHasBeenSet = true; m_configurations = std::move(value); }

    /**
     * <p>A list of additional configurations to apply within a configuration
     * object.</p>
     */
    inline Configuration& WithConfigurations(const Aws::Vector<Configuration>& value) { SetConfigurations(value); return *this;}

    /**
     * <p>A list of additional configurations to apply within a configuration
     * object.</p>
     */
    inline Configuration& WithConfigurations(Aws::Vector<Configuration>&& value) { SetConfigurations(std::move(value)); return *this;}

    /**
     * <p>A list of additional configurations to apply within a configuration
     * object.</p>
     */
    inline Configuration& AddConfigurations(const Configuration& value) { m_configurationsHasBeenSet = true; m_configurations.push_back(value); return *this; }

    /**
     * <p>A list of additional configurations to apply within a configuration
     * object.</p>
     */
    inline Configuration& AddConfigurations(Configuration&& value) { m_configurationsHasBeenSet = true; m_configurations.push_back(std::move(value)); return *this; }

  private:

    Aws::String m_classification;
    bool m_classificationHasBeenSet = false;

    Aws::Map<Aws::String, Aws::String> m_properties;
    bool m_propertiesHasBeenSet = false;

    Aws::Vector<Configuration> m_configurations;
    bool m_configurationsHasBeenSet = false;
  };

} // namespace Model
} // namespace EMRContainers
} // namespace Aws
