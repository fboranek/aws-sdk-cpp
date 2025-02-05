﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/iot/IoT_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/core/utils/DateTime.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/iot/model/AwsJobExecutionsRolloutConfig.h>
#include <aws/iot/model/AwsJobPresignedUrlConfig.h>
#include <aws/iot/model/TargetSelection.h>
#include <aws/iot/model/OTAUpdateStatus.h>
#include <aws/iot/model/ErrorInfo.h>
#include <aws/core/utils/memory/stl/AWSMap.h>
#include <aws/iot/model/Protocol.h>
#include <aws/iot/model/OTAUpdateFile.h>
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
namespace IoT
{
namespace Model
{

  /**
   * <p>Information about an OTA update.</p><p><h3>See Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/iot-2015-05-28/OTAUpdateInfo">AWS
   * API Reference</a></p>
   */
  class AWS_IOT_API OTAUpdateInfo
  {
  public:
    OTAUpdateInfo();
    OTAUpdateInfo(Aws::Utils::Json::JsonView jsonValue);
    OTAUpdateInfo& operator=(Aws::Utils::Json::JsonView jsonValue);
    Aws::Utils::Json::JsonValue Jsonize() const;


    /**
     * <p>The OTA update ID.</p>
     */
    inline const Aws::String& GetOtaUpdateId() const{ return m_otaUpdateId; }

    /**
     * <p>The OTA update ID.</p>
     */
    inline bool OtaUpdateIdHasBeenSet() const { return m_otaUpdateIdHasBeenSet; }

    /**
     * <p>The OTA update ID.</p>
     */
    inline void SetOtaUpdateId(const Aws::String& value) { m_otaUpdateIdHasBeenSet = true; m_otaUpdateId = value; }

    /**
     * <p>The OTA update ID.</p>
     */
    inline void SetOtaUpdateId(Aws::String&& value) { m_otaUpdateIdHasBeenSet = true; m_otaUpdateId = std::move(value); }

    /**
     * <p>The OTA update ID.</p>
     */
    inline void SetOtaUpdateId(const char* value) { m_otaUpdateIdHasBeenSet = true; m_otaUpdateId.assign(value); }

    /**
     * <p>The OTA update ID.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateId(const Aws::String& value) { SetOtaUpdateId(value); return *this;}

    /**
     * <p>The OTA update ID.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateId(Aws::String&& value) { SetOtaUpdateId(std::move(value)); return *this;}

    /**
     * <p>The OTA update ID.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateId(const char* value) { SetOtaUpdateId(value); return *this;}


    /**
     * <p>The OTA update ARN.</p>
     */
    inline const Aws::String& GetOtaUpdateArn() const{ return m_otaUpdateArn; }

    /**
     * <p>The OTA update ARN.</p>
     */
    inline bool OtaUpdateArnHasBeenSet() const { return m_otaUpdateArnHasBeenSet; }

    /**
     * <p>The OTA update ARN.</p>
     */
    inline void SetOtaUpdateArn(const Aws::String& value) { m_otaUpdateArnHasBeenSet = true; m_otaUpdateArn = value; }

    /**
     * <p>The OTA update ARN.</p>
     */
    inline void SetOtaUpdateArn(Aws::String&& value) { m_otaUpdateArnHasBeenSet = true; m_otaUpdateArn = std::move(value); }

    /**
     * <p>The OTA update ARN.</p>
     */
    inline void SetOtaUpdateArn(const char* value) { m_otaUpdateArnHasBeenSet = true; m_otaUpdateArn.assign(value); }

    /**
     * <p>The OTA update ARN.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateArn(const Aws::String& value) { SetOtaUpdateArn(value); return *this;}

    /**
     * <p>The OTA update ARN.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateArn(Aws::String&& value) { SetOtaUpdateArn(std::move(value)); return *this;}

    /**
     * <p>The OTA update ARN.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateArn(const char* value) { SetOtaUpdateArn(value); return *this;}


    /**
     * <p>The date when the OTA update was created.</p>
     */
    inline const Aws::Utils::DateTime& GetCreationDate() const{ return m_creationDate; }

    /**
     * <p>The date when the OTA update was created.</p>
     */
    inline bool CreationDateHasBeenSet() const { return m_creationDateHasBeenSet; }

    /**
     * <p>The date when the OTA update was created.</p>
     */
    inline void SetCreationDate(const Aws::Utils::DateTime& value) { m_creationDateHasBeenSet = true; m_creationDate = value; }

    /**
     * <p>The date when the OTA update was created.</p>
     */
    inline void SetCreationDate(Aws::Utils::DateTime&& value) { m_creationDateHasBeenSet = true; m_creationDate = std::move(value); }

    /**
     * <p>The date when the OTA update was created.</p>
     */
    inline OTAUpdateInfo& WithCreationDate(const Aws::Utils::DateTime& value) { SetCreationDate(value); return *this;}

    /**
     * <p>The date when the OTA update was created.</p>
     */
    inline OTAUpdateInfo& WithCreationDate(Aws::Utils::DateTime&& value) { SetCreationDate(std::move(value)); return *this;}


    /**
     * <p>The date when the OTA update was last updated.</p>
     */
    inline const Aws::Utils::DateTime& GetLastModifiedDate() const{ return m_lastModifiedDate; }

    /**
     * <p>The date when the OTA update was last updated.</p>
     */
    inline bool LastModifiedDateHasBeenSet() const { return m_lastModifiedDateHasBeenSet; }

    /**
     * <p>The date when the OTA update was last updated.</p>
     */
    inline void SetLastModifiedDate(const Aws::Utils::DateTime& value) { m_lastModifiedDateHasBeenSet = true; m_lastModifiedDate = value; }

    /**
     * <p>The date when the OTA update was last updated.</p>
     */
    inline void SetLastModifiedDate(Aws::Utils::DateTime&& value) { m_lastModifiedDateHasBeenSet = true; m_lastModifiedDate = std::move(value); }

    /**
     * <p>The date when the OTA update was last updated.</p>
     */
    inline OTAUpdateInfo& WithLastModifiedDate(const Aws::Utils::DateTime& value) { SetLastModifiedDate(value); return *this;}

    /**
     * <p>The date when the OTA update was last updated.</p>
     */
    inline OTAUpdateInfo& WithLastModifiedDate(Aws::Utils::DateTime&& value) { SetLastModifiedDate(std::move(value)); return *this;}


    /**
     * <p>A description of the OTA update.</p>
     */
    inline const Aws::String& GetDescription() const{ return m_description; }

    /**
     * <p>A description of the OTA update.</p>
     */
    inline bool DescriptionHasBeenSet() const { return m_descriptionHasBeenSet; }

    /**
     * <p>A description of the OTA update.</p>
     */
    inline void SetDescription(const Aws::String& value) { m_descriptionHasBeenSet = true; m_description = value; }

    /**
     * <p>A description of the OTA update.</p>
     */
    inline void SetDescription(Aws::String&& value) { m_descriptionHasBeenSet = true; m_description = std::move(value); }

    /**
     * <p>A description of the OTA update.</p>
     */
    inline void SetDescription(const char* value) { m_descriptionHasBeenSet = true; m_description.assign(value); }

    /**
     * <p>A description of the OTA update.</p>
     */
    inline OTAUpdateInfo& WithDescription(const Aws::String& value) { SetDescription(value); return *this;}

    /**
     * <p>A description of the OTA update.</p>
     */
    inline OTAUpdateInfo& WithDescription(Aws::String&& value) { SetDescription(std::move(value)); return *this;}

    /**
     * <p>A description of the OTA update.</p>
     */
    inline OTAUpdateInfo& WithDescription(const char* value) { SetDescription(value); return *this;}


    /**
     * <p>The targets of the OTA update.</p>
     */
    inline const Aws::Vector<Aws::String>& GetTargets() const{ return m_targets; }

    /**
     * <p>The targets of the OTA update.</p>
     */
    inline bool TargetsHasBeenSet() const { return m_targetsHasBeenSet; }

    /**
     * <p>The targets of the OTA update.</p>
     */
    inline void SetTargets(const Aws::Vector<Aws::String>& value) { m_targetsHasBeenSet = true; m_targets = value; }

    /**
     * <p>The targets of the OTA update.</p>
     */
    inline void SetTargets(Aws::Vector<Aws::String>&& value) { m_targetsHasBeenSet = true; m_targets = std::move(value); }

    /**
     * <p>The targets of the OTA update.</p>
     */
    inline OTAUpdateInfo& WithTargets(const Aws::Vector<Aws::String>& value) { SetTargets(value); return *this;}

    /**
     * <p>The targets of the OTA update.</p>
     */
    inline OTAUpdateInfo& WithTargets(Aws::Vector<Aws::String>&& value) { SetTargets(std::move(value)); return *this;}

    /**
     * <p>The targets of the OTA update.</p>
     */
    inline OTAUpdateInfo& AddTargets(const Aws::String& value) { m_targetsHasBeenSet = true; m_targets.push_back(value); return *this; }

    /**
     * <p>The targets of the OTA update.</p>
     */
    inline OTAUpdateInfo& AddTargets(Aws::String&& value) { m_targetsHasBeenSet = true; m_targets.push_back(std::move(value)); return *this; }

    /**
     * <p>The targets of the OTA update.</p>
     */
    inline OTAUpdateInfo& AddTargets(const char* value) { m_targetsHasBeenSet = true; m_targets.push_back(value); return *this; }


    /**
     * <p>The protocol used to transfer the OTA update image. Valid values are [HTTP],
     * [MQTT], [HTTP, MQTT]. When both HTTP and MQTT are specified, the target device
     * can choose the protocol.</p>
     */
    inline const Aws::Vector<Protocol>& GetProtocols() const{ return m_protocols; }

    /**
     * <p>The protocol used to transfer the OTA update image. Valid values are [HTTP],
     * [MQTT], [HTTP, MQTT]. When both HTTP and MQTT are specified, the target device
     * can choose the protocol.</p>
     */
    inline bool ProtocolsHasBeenSet() const { return m_protocolsHasBeenSet; }

    /**
     * <p>The protocol used to transfer the OTA update image. Valid values are [HTTP],
     * [MQTT], [HTTP, MQTT]. When both HTTP and MQTT are specified, the target device
     * can choose the protocol.</p>
     */
    inline void SetProtocols(const Aws::Vector<Protocol>& value) { m_protocolsHasBeenSet = true; m_protocols = value; }

    /**
     * <p>The protocol used to transfer the OTA update image. Valid values are [HTTP],
     * [MQTT], [HTTP, MQTT]. When both HTTP and MQTT are specified, the target device
     * can choose the protocol.</p>
     */
    inline void SetProtocols(Aws::Vector<Protocol>&& value) { m_protocolsHasBeenSet = true; m_protocols = std::move(value); }

    /**
     * <p>The protocol used to transfer the OTA update image. Valid values are [HTTP],
     * [MQTT], [HTTP, MQTT]. When both HTTP and MQTT are specified, the target device
     * can choose the protocol.</p>
     */
    inline OTAUpdateInfo& WithProtocols(const Aws::Vector<Protocol>& value) { SetProtocols(value); return *this;}

    /**
     * <p>The protocol used to transfer the OTA update image. Valid values are [HTTP],
     * [MQTT], [HTTP, MQTT]. When both HTTP and MQTT are specified, the target device
     * can choose the protocol.</p>
     */
    inline OTAUpdateInfo& WithProtocols(Aws::Vector<Protocol>&& value) { SetProtocols(std::move(value)); return *this;}

    /**
     * <p>The protocol used to transfer the OTA update image. Valid values are [HTTP],
     * [MQTT], [HTTP, MQTT]. When both HTTP and MQTT are specified, the target device
     * can choose the protocol.</p>
     */
    inline OTAUpdateInfo& AddProtocols(const Protocol& value) { m_protocolsHasBeenSet = true; m_protocols.push_back(value); return *this; }

    /**
     * <p>The protocol used to transfer the OTA update image. Valid values are [HTTP],
     * [MQTT], [HTTP, MQTT]. When both HTTP and MQTT are specified, the target device
     * can choose the protocol.</p>
     */
    inline OTAUpdateInfo& AddProtocols(Protocol&& value) { m_protocolsHasBeenSet = true; m_protocols.push_back(std::move(value)); return *this; }


    /**
     * <p>Configuration for the rollout of OTA updates.</p>
     */
    inline const AwsJobExecutionsRolloutConfig& GetAwsJobExecutionsRolloutConfig() const{ return m_awsJobExecutionsRolloutConfig; }

    /**
     * <p>Configuration for the rollout of OTA updates.</p>
     */
    inline bool AwsJobExecutionsRolloutConfigHasBeenSet() const { return m_awsJobExecutionsRolloutConfigHasBeenSet; }

    /**
     * <p>Configuration for the rollout of OTA updates.</p>
     */
    inline void SetAwsJobExecutionsRolloutConfig(const AwsJobExecutionsRolloutConfig& value) { m_awsJobExecutionsRolloutConfigHasBeenSet = true; m_awsJobExecutionsRolloutConfig = value; }

    /**
     * <p>Configuration for the rollout of OTA updates.</p>
     */
    inline void SetAwsJobExecutionsRolloutConfig(AwsJobExecutionsRolloutConfig&& value) { m_awsJobExecutionsRolloutConfigHasBeenSet = true; m_awsJobExecutionsRolloutConfig = std::move(value); }

    /**
     * <p>Configuration for the rollout of OTA updates.</p>
     */
    inline OTAUpdateInfo& WithAwsJobExecutionsRolloutConfig(const AwsJobExecutionsRolloutConfig& value) { SetAwsJobExecutionsRolloutConfig(value); return *this;}

    /**
     * <p>Configuration for the rollout of OTA updates.</p>
     */
    inline OTAUpdateInfo& WithAwsJobExecutionsRolloutConfig(AwsJobExecutionsRolloutConfig&& value) { SetAwsJobExecutionsRolloutConfig(std::move(value)); return *this;}


    /**
     * <p>Configuration information for pre-signed URLs. Valid when
     * <code>protocols</code> contains HTTP.</p>
     */
    inline const AwsJobPresignedUrlConfig& GetAwsJobPresignedUrlConfig() const{ return m_awsJobPresignedUrlConfig; }

    /**
     * <p>Configuration information for pre-signed URLs. Valid when
     * <code>protocols</code> contains HTTP.</p>
     */
    inline bool AwsJobPresignedUrlConfigHasBeenSet() const { return m_awsJobPresignedUrlConfigHasBeenSet; }

    /**
     * <p>Configuration information for pre-signed URLs. Valid when
     * <code>protocols</code> contains HTTP.</p>
     */
    inline void SetAwsJobPresignedUrlConfig(const AwsJobPresignedUrlConfig& value) { m_awsJobPresignedUrlConfigHasBeenSet = true; m_awsJobPresignedUrlConfig = value; }

    /**
     * <p>Configuration information for pre-signed URLs. Valid when
     * <code>protocols</code> contains HTTP.</p>
     */
    inline void SetAwsJobPresignedUrlConfig(AwsJobPresignedUrlConfig&& value) { m_awsJobPresignedUrlConfigHasBeenSet = true; m_awsJobPresignedUrlConfig = std::move(value); }

    /**
     * <p>Configuration information for pre-signed URLs. Valid when
     * <code>protocols</code> contains HTTP.</p>
     */
    inline OTAUpdateInfo& WithAwsJobPresignedUrlConfig(const AwsJobPresignedUrlConfig& value) { SetAwsJobPresignedUrlConfig(value); return *this;}

    /**
     * <p>Configuration information for pre-signed URLs. Valid when
     * <code>protocols</code> contains HTTP.</p>
     */
    inline OTAUpdateInfo& WithAwsJobPresignedUrlConfig(AwsJobPresignedUrlConfig&& value) { SetAwsJobPresignedUrlConfig(std::move(value)); return *this;}


    /**
     * <p>Specifies whether the OTA update will continue to run (CONTINUOUS), or will
     * be complete after all those things specified as targets have completed the OTA
     * update (SNAPSHOT). If continuous, the OTA update may also be run on a thing when
     * a change is detected in a target. For example, an OTA update will run on a thing
     * when the thing is added to a target group, even after the OTA update was
     * completed by all things originally in the group. </p>
     */
    inline const TargetSelection& GetTargetSelection() const{ return m_targetSelection; }

    /**
     * <p>Specifies whether the OTA update will continue to run (CONTINUOUS), or will
     * be complete after all those things specified as targets have completed the OTA
     * update (SNAPSHOT). If continuous, the OTA update may also be run on a thing when
     * a change is detected in a target. For example, an OTA update will run on a thing
     * when the thing is added to a target group, even after the OTA update was
     * completed by all things originally in the group. </p>
     */
    inline bool TargetSelectionHasBeenSet() const { return m_targetSelectionHasBeenSet; }

    /**
     * <p>Specifies whether the OTA update will continue to run (CONTINUOUS), or will
     * be complete after all those things specified as targets have completed the OTA
     * update (SNAPSHOT). If continuous, the OTA update may also be run on a thing when
     * a change is detected in a target. For example, an OTA update will run on a thing
     * when the thing is added to a target group, even after the OTA update was
     * completed by all things originally in the group. </p>
     */
    inline void SetTargetSelection(const TargetSelection& value) { m_targetSelectionHasBeenSet = true; m_targetSelection = value; }

    /**
     * <p>Specifies whether the OTA update will continue to run (CONTINUOUS), or will
     * be complete after all those things specified as targets have completed the OTA
     * update (SNAPSHOT). If continuous, the OTA update may also be run on a thing when
     * a change is detected in a target. For example, an OTA update will run on a thing
     * when the thing is added to a target group, even after the OTA update was
     * completed by all things originally in the group. </p>
     */
    inline void SetTargetSelection(TargetSelection&& value) { m_targetSelectionHasBeenSet = true; m_targetSelection = std::move(value); }

    /**
     * <p>Specifies whether the OTA update will continue to run (CONTINUOUS), or will
     * be complete after all those things specified as targets have completed the OTA
     * update (SNAPSHOT). If continuous, the OTA update may also be run on a thing when
     * a change is detected in a target. For example, an OTA update will run on a thing
     * when the thing is added to a target group, even after the OTA update was
     * completed by all things originally in the group. </p>
     */
    inline OTAUpdateInfo& WithTargetSelection(const TargetSelection& value) { SetTargetSelection(value); return *this;}

    /**
     * <p>Specifies whether the OTA update will continue to run (CONTINUOUS), or will
     * be complete after all those things specified as targets have completed the OTA
     * update (SNAPSHOT). If continuous, the OTA update may also be run on a thing when
     * a change is detected in a target. For example, an OTA update will run on a thing
     * when the thing is added to a target group, even after the OTA update was
     * completed by all things originally in the group. </p>
     */
    inline OTAUpdateInfo& WithTargetSelection(TargetSelection&& value) { SetTargetSelection(std::move(value)); return *this;}


    /**
     * <p>A list of files associated with the OTA update.</p>
     */
    inline const Aws::Vector<OTAUpdateFile>& GetOtaUpdateFiles() const{ return m_otaUpdateFiles; }

    /**
     * <p>A list of files associated with the OTA update.</p>
     */
    inline bool OtaUpdateFilesHasBeenSet() const { return m_otaUpdateFilesHasBeenSet; }

    /**
     * <p>A list of files associated with the OTA update.</p>
     */
    inline void SetOtaUpdateFiles(const Aws::Vector<OTAUpdateFile>& value) { m_otaUpdateFilesHasBeenSet = true; m_otaUpdateFiles = value; }

    /**
     * <p>A list of files associated with the OTA update.</p>
     */
    inline void SetOtaUpdateFiles(Aws::Vector<OTAUpdateFile>&& value) { m_otaUpdateFilesHasBeenSet = true; m_otaUpdateFiles = std::move(value); }

    /**
     * <p>A list of files associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateFiles(const Aws::Vector<OTAUpdateFile>& value) { SetOtaUpdateFiles(value); return *this;}

    /**
     * <p>A list of files associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateFiles(Aws::Vector<OTAUpdateFile>&& value) { SetOtaUpdateFiles(std::move(value)); return *this;}

    /**
     * <p>A list of files associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& AddOtaUpdateFiles(const OTAUpdateFile& value) { m_otaUpdateFilesHasBeenSet = true; m_otaUpdateFiles.push_back(value); return *this; }

    /**
     * <p>A list of files associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& AddOtaUpdateFiles(OTAUpdateFile&& value) { m_otaUpdateFilesHasBeenSet = true; m_otaUpdateFiles.push_back(std::move(value)); return *this; }


    /**
     * <p>The status of the OTA update.</p>
     */
    inline const OTAUpdateStatus& GetOtaUpdateStatus() const{ return m_otaUpdateStatus; }

    /**
     * <p>The status of the OTA update.</p>
     */
    inline bool OtaUpdateStatusHasBeenSet() const { return m_otaUpdateStatusHasBeenSet; }

    /**
     * <p>The status of the OTA update.</p>
     */
    inline void SetOtaUpdateStatus(const OTAUpdateStatus& value) { m_otaUpdateStatusHasBeenSet = true; m_otaUpdateStatus = value; }

    /**
     * <p>The status of the OTA update.</p>
     */
    inline void SetOtaUpdateStatus(OTAUpdateStatus&& value) { m_otaUpdateStatusHasBeenSet = true; m_otaUpdateStatus = std::move(value); }

    /**
     * <p>The status of the OTA update.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateStatus(const OTAUpdateStatus& value) { SetOtaUpdateStatus(value); return *this;}

    /**
     * <p>The status of the OTA update.</p>
     */
    inline OTAUpdateInfo& WithOtaUpdateStatus(OTAUpdateStatus&& value) { SetOtaUpdateStatus(std::move(value)); return *this;}


    /**
     * <p>The IoT job ID associated with the OTA update.</p>
     */
    inline const Aws::String& GetAwsIotJobId() const{ return m_awsIotJobId; }

    /**
     * <p>The IoT job ID associated with the OTA update.</p>
     */
    inline bool AwsIotJobIdHasBeenSet() const { return m_awsIotJobIdHasBeenSet; }

    /**
     * <p>The IoT job ID associated with the OTA update.</p>
     */
    inline void SetAwsIotJobId(const Aws::String& value) { m_awsIotJobIdHasBeenSet = true; m_awsIotJobId = value; }

    /**
     * <p>The IoT job ID associated with the OTA update.</p>
     */
    inline void SetAwsIotJobId(Aws::String&& value) { m_awsIotJobIdHasBeenSet = true; m_awsIotJobId = std::move(value); }

    /**
     * <p>The IoT job ID associated with the OTA update.</p>
     */
    inline void SetAwsIotJobId(const char* value) { m_awsIotJobIdHasBeenSet = true; m_awsIotJobId.assign(value); }

    /**
     * <p>The IoT job ID associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithAwsIotJobId(const Aws::String& value) { SetAwsIotJobId(value); return *this;}

    /**
     * <p>The IoT job ID associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithAwsIotJobId(Aws::String&& value) { SetAwsIotJobId(std::move(value)); return *this;}

    /**
     * <p>The IoT job ID associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithAwsIotJobId(const char* value) { SetAwsIotJobId(value); return *this;}


    /**
     * <p>The IoT job ARN associated with the OTA update.</p>
     */
    inline const Aws::String& GetAwsIotJobArn() const{ return m_awsIotJobArn; }

    /**
     * <p>The IoT job ARN associated with the OTA update.</p>
     */
    inline bool AwsIotJobArnHasBeenSet() const { return m_awsIotJobArnHasBeenSet; }

    /**
     * <p>The IoT job ARN associated with the OTA update.</p>
     */
    inline void SetAwsIotJobArn(const Aws::String& value) { m_awsIotJobArnHasBeenSet = true; m_awsIotJobArn = value; }

    /**
     * <p>The IoT job ARN associated with the OTA update.</p>
     */
    inline void SetAwsIotJobArn(Aws::String&& value) { m_awsIotJobArnHasBeenSet = true; m_awsIotJobArn = std::move(value); }

    /**
     * <p>The IoT job ARN associated with the OTA update.</p>
     */
    inline void SetAwsIotJobArn(const char* value) { m_awsIotJobArnHasBeenSet = true; m_awsIotJobArn.assign(value); }

    /**
     * <p>The IoT job ARN associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithAwsIotJobArn(const Aws::String& value) { SetAwsIotJobArn(value); return *this;}

    /**
     * <p>The IoT job ARN associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithAwsIotJobArn(Aws::String&& value) { SetAwsIotJobArn(std::move(value)); return *this;}

    /**
     * <p>The IoT job ARN associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithAwsIotJobArn(const char* value) { SetAwsIotJobArn(value); return *this;}


    /**
     * <p>Error information associated with the OTA update.</p>
     */
    inline const ErrorInfo& GetErrorInfo() const{ return m_errorInfo; }

    /**
     * <p>Error information associated with the OTA update.</p>
     */
    inline bool ErrorInfoHasBeenSet() const { return m_errorInfoHasBeenSet; }

    /**
     * <p>Error information associated with the OTA update.</p>
     */
    inline void SetErrorInfo(const ErrorInfo& value) { m_errorInfoHasBeenSet = true; m_errorInfo = value; }

    /**
     * <p>Error information associated with the OTA update.</p>
     */
    inline void SetErrorInfo(ErrorInfo&& value) { m_errorInfoHasBeenSet = true; m_errorInfo = std::move(value); }

    /**
     * <p>Error information associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithErrorInfo(const ErrorInfo& value) { SetErrorInfo(value); return *this;}

    /**
     * <p>Error information associated with the OTA update.</p>
     */
    inline OTAUpdateInfo& WithErrorInfo(ErrorInfo&& value) { SetErrorInfo(std::move(value)); return *this;}


    /**
     * <p>A collection of name/value pairs</p>
     */
    inline const Aws::Map<Aws::String, Aws::String>& GetAdditionalParameters() const{ return m_additionalParameters; }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline bool AdditionalParametersHasBeenSet() const { return m_additionalParametersHasBeenSet; }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline void SetAdditionalParameters(const Aws::Map<Aws::String, Aws::String>& value) { m_additionalParametersHasBeenSet = true; m_additionalParameters = value; }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline void SetAdditionalParameters(Aws::Map<Aws::String, Aws::String>&& value) { m_additionalParametersHasBeenSet = true; m_additionalParameters = std::move(value); }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline OTAUpdateInfo& WithAdditionalParameters(const Aws::Map<Aws::String, Aws::String>& value) { SetAdditionalParameters(value); return *this;}

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline OTAUpdateInfo& WithAdditionalParameters(Aws::Map<Aws::String, Aws::String>&& value) { SetAdditionalParameters(std::move(value)); return *this;}

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline OTAUpdateInfo& AddAdditionalParameters(const Aws::String& key, const Aws::String& value) { m_additionalParametersHasBeenSet = true; m_additionalParameters.emplace(key, value); return *this; }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline OTAUpdateInfo& AddAdditionalParameters(Aws::String&& key, const Aws::String& value) { m_additionalParametersHasBeenSet = true; m_additionalParameters.emplace(std::move(key), value); return *this; }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline OTAUpdateInfo& AddAdditionalParameters(const Aws::String& key, Aws::String&& value) { m_additionalParametersHasBeenSet = true; m_additionalParameters.emplace(key, std::move(value)); return *this; }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline OTAUpdateInfo& AddAdditionalParameters(Aws::String&& key, Aws::String&& value) { m_additionalParametersHasBeenSet = true; m_additionalParameters.emplace(std::move(key), std::move(value)); return *this; }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline OTAUpdateInfo& AddAdditionalParameters(const char* key, Aws::String&& value) { m_additionalParametersHasBeenSet = true; m_additionalParameters.emplace(key, std::move(value)); return *this; }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline OTAUpdateInfo& AddAdditionalParameters(Aws::String&& key, const char* value) { m_additionalParametersHasBeenSet = true; m_additionalParameters.emplace(std::move(key), value); return *this; }

    /**
     * <p>A collection of name/value pairs</p>
     */
    inline OTAUpdateInfo& AddAdditionalParameters(const char* key, const char* value) { m_additionalParametersHasBeenSet = true; m_additionalParameters.emplace(key, value); return *this; }

  private:

    Aws::String m_otaUpdateId;
    bool m_otaUpdateIdHasBeenSet = false;

    Aws::String m_otaUpdateArn;
    bool m_otaUpdateArnHasBeenSet = false;

    Aws::Utils::DateTime m_creationDate;
    bool m_creationDateHasBeenSet = false;

    Aws::Utils::DateTime m_lastModifiedDate;
    bool m_lastModifiedDateHasBeenSet = false;

    Aws::String m_description;
    bool m_descriptionHasBeenSet = false;

    Aws::Vector<Aws::String> m_targets;
    bool m_targetsHasBeenSet = false;

    Aws::Vector<Protocol> m_protocols;
    bool m_protocolsHasBeenSet = false;

    AwsJobExecutionsRolloutConfig m_awsJobExecutionsRolloutConfig;
    bool m_awsJobExecutionsRolloutConfigHasBeenSet = false;

    AwsJobPresignedUrlConfig m_awsJobPresignedUrlConfig;
    bool m_awsJobPresignedUrlConfigHasBeenSet = false;

    TargetSelection m_targetSelection;
    bool m_targetSelectionHasBeenSet = false;

    Aws::Vector<OTAUpdateFile> m_otaUpdateFiles;
    bool m_otaUpdateFilesHasBeenSet = false;

    OTAUpdateStatus m_otaUpdateStatus;
    bool m_otaUpdateStatusHasBeenSet = false;

    Aws::String m_awsIotJobId;
    bool m_awsIotJobIdHasBeenSet = false;

    Aws::String m_awsIotJobArn;
    bool m_awsIotJobArnHasBeenSet = false;

    ErrorInfo m_errorInfo;
    bool m_errorInfoHasBeenSet = false;

    Aws::Map<Aws::String, Aws::String> m_additionalParameters;
    bool m_additionalParametersHasBeenSet = false;
  };

} // namespace Model
} // namespace IoT
} // namespace Aws
