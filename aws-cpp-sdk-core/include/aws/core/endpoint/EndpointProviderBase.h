/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */


#pragma once

#include <aws/core/endpoint/AWSEndpoint.h>
#include <aws/core/client/AWSError.h>

namespace Aws
{
    namespace Utils
    {
        template< typename R, typename E> class Outcome;
    } // namespace Utils
    namespace Client
    {
        enum class CoreErrors;
    } // namespace CoreErrors

    namespace Endpoint
    {
        /**
          * EndpointProviderBase is an interface definition that resolves the provided
          *   EndpointParameters to either an Endpoint or an error.
          */
        template<typename EndpointParametersT>
        class AWS_CORE_API EndpointProviderBase
        {
        public:
            using ResolveEndpointOutcome = Aws::Utils::Outcome<AWSEndpoint, Aws::Client::AWSError<Aws::Client::CoreErrors> >;

            virtual ~EndpointProviderBase() = default;

            /**
             * The core of the endpoint provider interface.
             */
            virtual ResolveEndpointOutcome ResolveEndpoint(const EndpointParametersT& endpointParameters) const = 0;
        };
    } // namespace Endpoint
} // namespace Aws
