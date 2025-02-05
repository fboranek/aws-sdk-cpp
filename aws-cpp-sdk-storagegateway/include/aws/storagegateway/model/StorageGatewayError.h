﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/storagegateway/StorageGateway_EXPORTS.h>
#include <aws/storagegateway/model/ErrorCode.h>
#include <aws/core/utils/memory/stl/AWSMap.h>
#include <aws/core/utils/memory/stl/AWSString.h>
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
namespace StorageGateway
{
namespace Model
{

  /**
   * <p>Provides additional information about an error that was returned by the
   * service. See the <code>errorCode</code> and <code>errorDetails</code> members
   * for more information about the error.</p><p><h3>See Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/storagegateway-2013-06-30/StorageGatewayError">AWS
   * API Reference</a></p>
   */
  class AWS_STORAGEGATEWAY_API StorageGatewayError
  {
  public:
    StorageGatewayError();
    StorageGatewayError(Aws::Utils::Json::JsonView jsonValue);
    StorageGatewayError& operator=(Aws::Utils::Json::JsonView jsonValue);
    Aws::Utils::Json::JsonValue Jsonize() const;


    /**
     * <p>Additional information about the error.</p>
     */
    inline const ErrorCode& GetErrorCode() const{ return m_errorCode; }

    /**
     * <p>Additional information about the error.</p>
     */
    inline bool ErrorCodeHasBeenSet() const { return m_errorCodeHasBeenSet; }

    /**
     * <p>Additional information about the error.</p>
     */
    inline void SetErrorCode(const ErrorCode& value) { m_errorCodeHasBeenSet = true; m_errorCode = value; }

    /**
     * <p>Additional information about the error.</p>
     */
    inline void SetErrorCode(ErrorCode&& value) { m_errorCodeHasBeenSet = true; m_errorCode = std::move(value); }

    /**
     * <p>Additional information about the error.</p>
     */
    inline StorageGatewayError& WithErrorCode(const ErrorCode& value) { SetErrorCode(value); return *this;}

    /**
     * <p>Additional information about the error.</p>
     */
    inline StorageGatewayError& WithErrorCode(ErrorCode&& value) { SetErrorCode(std::move(value)); return *this;}


    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline const Aws::Map<Aws::String, Aws::String>& GetErrorDetails() const{ return m_errorDetails; }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline bool ErrorDetailsHasBeenSet() const { return m_errorDetailsHasBeenSet; }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline void SetErrorDetails(const Aws::Map<Aws::String, Aws::String>& value) { m_errorDetailsHasBeenSet = true; m_errorDetails = value; }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline void SetErrorDetails(Aws::Map<Aws::String, Aws::String>&& value) { m_errorDetailsHasBeenSet = true; m_errorDetails = std::move(value); }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline StorageGatewayError& WithErrorDetails(const Aws::Map<Aws::String, Aws::String>& value) { SetErrorDetails(value); return *this;}

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline StorageGatewayError& WithErrorDetails(Aws::Map<Aws::String, Aws::String>&& value) { SetErrorDetails(std::move(value)); return *this;}

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline StorageGatewayError& AddErrorDetails(const Aws::String& key, const Aws::String& value) { m_errorDetailsHasBeenSet = true; m_errorDetails.emplace(key, value); return *this; }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline StorageGatewayError& AddErrorDetails(Aws::String&& key, const Aws::String& value) { m_errorDetailsHasBeenSet = true; m_errorDetails.emplace(std::move(key), value); return *this; }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline StorageGatewayError& AddErrorDetails(const Aws::String& key, Aws::String&& value) { m_errorDetailsHasBeenSet = true; m_errorDetails.emplace(key, std::move(value)); return *this; }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline StorageGatewayError& AddErrorDetails(Aws::String&& key, Aws::String&& value) { m_errorDetailsHasBeenSet = true; m_errorDetails.emplace(std::move(key), std::move(value)); return *this; }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline StorageGatewayError& AddErrorDetails(const char* key, Aws::String&& value) { m_errorDetailsHasBeenSet = true; m_errorDetails.emplace(key, std::move(value)); return *this; }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline StorageGatewayError& AddErrorDetails(Aws::String&& key, const char* value) { m_errorDetailsHasBeenSet = true; m_errorDetails.emplace(std::move(key), value); return *this; }

    /**
     * <p>Human-readable text that provides detail about the error that occurred.</p>
     */
    inline StorageGatewayError& AddErrorDetails(const char* key, const char* value) { m_errorDetailsHasBeenSet = true; m_errorDetails.emplace(key, value); return *this; }

  private:

    ErrorCode m_errorCode;
    bool m_errorCodeHasBeenSet = false;

    Aws::Map<Aws::String, Aws::String> m_errorDetails;
    bool m_errorDetailsHasBeenSet = false;
  };

} // namespace Model
} // namespace StorageGateway
} // namespace Aws
