﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/ssm/SSM_EXPORTS.h>
#include <aws/ssm/SSMRequest.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/ssm/model/ComplianceStringFilter.h>
#include <utility>

namespace Aws
{
namespace SSM
{
namespace Model
{

  /**
   */
  class AWS_SSM_API ListComplianceSummariesRequest : public SSMRequest
  {
  public:
    ListComplianceSummariesRequest();

    // Service request name is the Operation name which will send this request out,
    // each operation should has unique request name, so that we can get operation's name from this request.
    // Note: this is not true for response, multiple operations may have the same response name,
    // so we can not get operation's name from response.
    inline virtual const char* GetServiceRequestName() const override { return "ListComplianceSummaries"; }

    Aws::String SerializePayload() const override;

    Aws::Http::HeaderValueCollection GetRequestSpecificHeaders() const override;


    /**
     * <p>One or more compliance or inventory filters. Use a filter to return a more
     * specific list of results.</p>
     */
    inline const Aws::Vector<ComplianceStringFilter>& GetFilters() const{ return m_filters; }

    /**
     * <p>One or more compliance or inventory filters. Use a filter to return a more
     * specific list of results.</p>
     */
    inline bool FiltersHasBeenSet() const { return m_filtersHasBeenSet; }

    /**
     * <p>One or more compliance or inventory filters. Use a filter to return a more
     * specific list of results.</p>
     */
    inline void SetFilters(const Aws::Vector<ComplianceStringFilter>& value) { m_filtersHasBeenSet = true; m_filters = value; }

    /**
     * <p>One or more compliance or inventory filters. Use a filter to return a more
     * specific list of results.</p>
     */
    inline void SetFilters(Aws::Vector<ComplianceStringFilter>&& value) { m_filtersHasBeenSet = true; m_filters = std::move(value); }

    /**
     * <p>One or more compliance or inventory filters. Use a filter to return a more
     * specific list of results.</p>
     */
    inline ListComplianceSummariesRequest& WithFilters(const Aws::Vector<ComplianceStringFilter>& value) { SetFilters(value); return *this;}

    /**
     * <p>One or more compliance or inventory filters. Use a filter to return a more
     * specific list of results.</p>
     */
    inline ListComplianceSummariesRequest& WithFilters(Aws::Vector<ComplianceStringFilter>&& value) { SetFilters(std::move(value)); return *this;}

    /**
     * <p>One or more compliance or inventory filters. Use a filter to return a more
     * specific list of results.</p>
     */
    inline ListComplianceSummariesRequest& AddFilters(const ComplianceStringFilter& value) { m_filtersHasBeenSet = true; m_filters.push_back(value); return *this; }

    /**
     * <p>One or more compliance or inventory filters. Use a filter to return a more
     * specific list of results.</p>
     */
    inline ListComplianceSummariesRequest& AddFilters(ComplianceStringFilter&& value) { m_filtersHasBeenSet = true; m_filters.push_back(std::move(value)); return *this; }


    /**
     * <p>A token to start the list. Use this token to get the next set of results.
     * </p>
     */
    inline const Aws::String& GetNextToken() const{ return m_nextToken; }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.
     * </p>
     */
    inline bool NextTokenHasBeenSet() const { return m_nextTokenHasBeenSet; }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.
     * </p>
     */
    inline void SetNextToken(const Aws::String& value) { m_nextTokenHasBeenSet = true; m_nextToken = value; }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.
     * </p>
     */
    inline void SetNextToken(Aws::String&& value) { m_nextTokenHasBeenSet = true; m_nextToken = std::move(value); }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.
     * </p>
     */
    inline void SetNextToken(const char* value) { m_nextTokenHasBeenSet = true; m_nextToken.assign(value); }

    /**
     * <p>A token to start the list. Use this token to get the next set of results.
     * </p>
     */
    inline ListComplianceSummariesRequest& WithNextToken(const Aws::String& value) { SetNextToken(value); return *this;}

    /**
     * <p>A token to start the list. Use this token to get the next set of results.
     * </p>
     */
    inline ListComplianceSummariesRequest& WithNextToken(Aws::String&& value) { SetNextToken(std::move(value)); return *this;}

    /**
     * <p>A token to start the list. Use this token to get the next set of results.
     * </p>
     */
    inline ListComplianceSummariesRequest& WithNextToken(const char* value) { SetNextToken(value); return *this;}


    /**
     * <p>The maximum number of items to return for this call. Currently, you can
     * specify null or 50. The call also returns a token that you can specify in a
     * subsequent call to get the next set of results.</p>
     */
    inline int GetMaxResults() const{ return m_maxResults; }

    /**
     * <p>The maximum number of items to return for this call. Currently, you can
     * specify null or 50. The call also returns a token that you can specify in a
     * subsequent call to get the next set of results.</p>
     */
    inline bool MaxResultsHasBeenSet() const { return m_maxResultsHasBeenSet; }

    /**
     * <p>The maximum number of items to return for this call. Currently, you can
     * specify null or 50. The call also returns a token that you can specify in a
     * subsequent call to get the next set of results.</p>
     */
    inline void SetMaxResults(int value) { m_maxResultsHasBeenSet = true; m_maxResults = value; }

    /**
     * <p>The maximum number of items to return for this call. Currently, you can
     * specify null or 50. The call also returns a token that you can specify in a
     * subsequent call to get the next set of results.</p>
     */
    inline ListComplianceSummariesRequest& WithMaxResults(int value) { SetMaxResults(value); return *this;}

  private:

    Aws::Vector<ComplianceStringFilter> m_filters;
    bool m_filtersHasBeenSet = false;

    Aws::String m_nextToken;
    bool m_nextTokenHasBeenSet = false;

    int m_maxResults;
    bool m_maxResultsHasBeenSet = false;
  };

} // namespace Model
} // namespace SSM
} // namespace Aws
