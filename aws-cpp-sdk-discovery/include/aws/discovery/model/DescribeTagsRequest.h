﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/discovery/ApplicationDiscoveryService_EXPORTS.h>
#include <aws/discovery/ApplicationDiscoveryServiceRequest.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/discovery/model/TagFilter.h>
#include <utility>

namespace Aws
{
namespace ApplicationDiscoveryService
{
namespace Model
{

  /**
   */
  class AWS_APPLICATIONDISCOVERYSERVICE_API DescribeTagsRequest : public ApplicationDiscoveryServiceRequest
  {
  public:
    DescribeTagsRequest();

    // Service request name is the Operation name which will send this request out,
    // each operation should has unique request name, so that we can get operation's name from this request.
    // Note: this is not true for response, multiple operations may have the same response name,
    // so we can not get operation's name from response.
    inline virtual const char* GetServiceRequestName() const override { return "DescribeTags"; }

    Aws::String SerializePayload() const override;

    Aws::Http::HeaderValueCollection GetRequestSpecificHeaders() const override;


    /**
     * <p>You can filter the list using a <i>key</i>-<i>value</i> format. You can
     * separate these items by using logical operators. Allowed filters include
     * <code>tagKey</code>, <code>tagValue</code>, and <code>configurationId</code>.
     * </p>
     */
    inline const Aws::Vector<TagFilter>& GetFilters() const{ return m_filters; }

    /**
     * <p>You can filter the list using a <i>key</i>-<i>value</i> format. You can
     * separate these items by using logical operators. Allowed filters include
     * <code>tagKey</code>, <code>tagValue</code>, and <code>configurationId</code>.
     * </p>
     */
    inline bool FiltersHasBeenSet() const { return m_filtersHasBeenSet; }

    /**
     * <p>You can filter the list using a <i>key</i>-<i>value</i> format. You can
     * separate these items by using logical operators. Allowed filters include
     * <code>tagKey</code>, <code>tagValue</code>, and <code>configurationId</code>.
     * </p>
     */
    inline void SetFilters(const Aws::Vector<TagFilter>& value) { m_filtersHasBeenSet = true; m_filters = value; }

    /**
     * <p>You can filter the list using a <i>key</i>-<i>value</i> format. You can
     * separate these items by using logical operators. Allowed filters include
     * <code>tagKey</code>, <code>tagValue</code>, and <code>configurationId</code>.
     * </p>
     */
    inline void SetFilters(Aws::Vector<TagFilter>&& value) { m_filtersHasBeenSet = true; m_filters = std::move(value); }

    /**
     * <p>You can filter the list using a <i>key</i>-<i>value</i> format. You can
     * separate these items by using logical operators. Allowed filters include
     * <code>tagKey</code>, <code>tagValue</code>, and <code>configurationId</code>.
     * </p>
     */
    inline DescribeTagsRequest& WithFilters(const Aws::Vector<TagFilter>& value) { SetFilters(value); return *this;}

    /**
     * <p>You can filter the list using a <i>key</i>-<i>value</i> format. You can
     * separate these items by using logical operators. Allowed filters include
     * <code>tagKey</code>, <code>tagValue</code>, and <code>configurationId</code>.
     * </p>
     */
    inline DescribeTagsRequest& WithFilters(Aws::Vector<TagFilter>&& value) { SetFilters(std::move(value)); return *this;}

    /**
     * <p>You can filter the list using a <i>key</i>-<i>value</i> format. You can
     * separate these items by using logical operators. Allowed filters include
     * <code>tagKey</code>, <code>tagValue</code>, and <code>configurationId</code>.
     * </p>
     */
    inline DescribeTagsRequest& AddFilters(const TagFilter& value) { m_filtersHasBeenSet = true; m_filters.push_back(value); return *this; }

    /**
     * <p>You can filter the list using a <i>key</i>-<i>value</i> format. You can
     * separate these items by using logical operators. Allowed filters include
     * <code>tagKey</code>, <code>tagValue</code>, and <code>configurationId</code>.
     * </p>
     */
    inline DescribeTagsRequest& AddFilters(TagFilter&& value) { m_filtersHasBeenSet = true; m_filters.push_back(std::move(value)); return *this; }


    /**
     * <p>The total number of items to return in a single page of output. The maximum
     * value is 100.</p>
     */
    inline int GetMaxResults() const{ return m_maxResults; }

    /**
     * <p>The total number of items to return in a single page of output. The maximum
     * value is 100.</p>
     */
    inline bool MaxResultsHasBeenSet() const { return m_maxResultsHasBeenSet; }

    /**
     * <p>The total number of items to return in a single page of output. The maximum
     * value is 100.</p>
     */
    inline void SetMaxResults(int value) { m_maxResultsHasBeenSet = true; m_maxResults = value; }

    /**
     * <p>The total number of items to return in a single page of output. The maximum
     * value is 100.</p>
     */
    inline DescribeTagsRequest& WithMaxResults(int value) { SetMaxResults(value); return *this;}


    /**
     * <p>A token to start the list. Use this token to get the next set of results.</p>
     */
    inline const Aws::String& GetNextToken() const{ return m_nextToken; }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.</p>
     */
    inline bool NextTokenHasBeenSet() const { return m_nextTokenHasBeenSet; }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.</p>
     */
    inline void SetNextToken(const Aws::String& value) { m_nextTokenHasBeenSet = true; m_nextToken = value; }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.</p>
     */
    inline void SetNextToken(Aws::String&& value) { m_nextTokenHasBeenSet = true; m_nextToken = std::move(value); }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.</p>
     */
    inline void SetNextToken(const char* value) { m_nextTokenHasBeenSet = true; m_nextToken.assign(value); }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.</p>
     */
    inline DescribeTagsRequest& WithNextToken(const Aws::String& value) { SetNextToken(value); return *this;}

    /**
     * <p>A token to start the list. Use this token to get the next set of results.</p>
     */
    inline DescribeTagsRequest& WithNextToken(Aws::String&& value) { SetNextToken(std::move(value)); return *this;}

    /**
     * <p>A token to start the list. Use this token to get the next set of results.</p>
     */
    inline DescribeTagsRequest& WithNextToken(const char* value) { SetNextToken(value); return *this;}

  private:

    Aws::Vector<TagFilter> m_filters;
    bool m_filtersHasBeenSet = false;

    int m_maxResults;
    bool m_maxResultsHasBeenSet = false;

    Aws::String m_nextToken;
    bool m_nextTokenHasBeenSet = false;
  };

} // namespace Model
} // namespace ApplicationDiscoveryService
} // namespace Aws
