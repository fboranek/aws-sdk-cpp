﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#pragma once
#include <aws/inspector/Inspector_EXPORTS.h>
#include <aws/core/utils/memory/stl/AWSString.h>
#include <aws/core/utils/memory/stl/AWSVector.h>
#include <aws/inspector/model/Scope.h>
#include <aws/inspector/model/Attribute.h>
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
namespace Inspector
{
namespace Model
{

  /**
   * <p>Contains information about what was excluded from an assessment
   * run.</p><p><h3>See Also:</h3>   <a
   * href="http://docs.aws.amazon.com/goto/WebAPI/inspector-2016-02-16/Exclusion">AWS
   * API Reference</a></p>
   */
  class AWS_INSPECTOR_API Exclusion
  {
  public:
    Exclusion();
    Exclusion(Aws::Utils::Json::JsonView jsonValue);
    Exclusion& operator=(Aws::Utils::Json::JsonView jsonValue);
    Aws::Utils::Json::JsonValue Jsonize() const;


    /**
     * <p>The ARN that specifies the exclusion.</p>
     */
    inline const Aws::String& GetArn() const{ return m_arn; }

    /**
     * <p>The ARN that specifies the exclusion.</p>
     */
    inline bool ArnHasBeenSet() const { return m_arnHasBeenSet; }

    /**
     * <p>The ARN that specifies the exclusion.</p>
     */
    inline void SetArn(const Aws::String& value) { m_arnHasBeenSet = true; m_arn = value; }

    /**
     * <p>The ARN that specifies the exclusion.</p>
     */
    inline void SetArn(Aws::String&& value) { m_arnHasBeenSet = true; m_arn = std::move(value); }

    /**
     * <p>The ARN that specifies the exclusion.</p>
     */
    inline void SetArn(const char* value) { m_arnHasBeenSet = true; m_arn.assign(value); }

    /**
     * <p>The ARN that specifies the exclusion.</p>
     */
    inline Exclusion& WithArn(const Aws::String& value) { SetArn(value); return *this;}

    /**
     * <p>The ARN that specifies the exclusion.</p>
     */
    inline Exclusion& WithArn(Aws::String&& value) { SetArn(std::move(value)); return *this;}

    /**
     * <p>The ARN that specifies the exclusion.</p>
     */
    inline Exclusion& WithArn(const char* value) { SetArn(value); return *this;}


    /**
     * <p>The name of the exclusion.</p>
     */
    inline const Aws::String& GetTitle() const{ return m_title; }

    /**
     * <p>The name of the exclusion.</p>
     */
    inline bool TitleHasBeenSet() const { return m_titleHasBeenSet; }

    /**
     * <p>The name of the exclusion.</p>
     */
    inline void SetTitle(const Aws::String& value) { m_titleHasBeenSet = true; m_title = value; }

    /**
     * <p>The name of the exclusion.</p>
     */
    inline void SetTitle(Aws::String&& value) { m_titleHasBeenSet = true; m_title = std::move(value); }

    /**
     * <p>The name of the exclusion.</p>
     */
    inline void SetTitle(const char* value) { m_titleHasBeenSet = true; m_title.assign(value); }

    /**
     * <p>The name of the exclusion.</p>
     */
    inline Exclusion& WithTitle(const Aws::String& value) { SetTitle(value); return *this;}

    /**
     * <p>The name of the exclusion.</p>
     */
    inline Exclusion& WithTitle(Aws::String&& value) { SetTitle(std::move(value)); return *this;}

    /**
     * <p>The name of the exclusion.</p>
     */
    inline Exclusion& WithTitle(const char* value) { SetTitle(value); return *this;}


    /**
     * <p>The description of the exclusion.</p>
     */
    inline const Aws::String& GetDescription() const{ return m_description; }

    /**
     * <p>The description of the exclusion.</p>
     */
    inline bool DescriptionHasBeenSet() const { return m_descriptionHasBeenSet; }

    /**
     * <p>The description of the exclusion.</p>
     */
    inline void SetDescription(const Aws::String& value) { m_descriptionHasBeenSet = true; m_description = value; }

    /**
     * <p>The description of the exclusion.</p>
     */
    inline void SetDescription(Aws::String&& value) { m_descriptionHasBeenSet = true; m_description = std::move(value); }

    /**
     * <p>The description of the exclusion.</p>
     */
    inline void SetDescription(const char* value) { m_descriptionHasBeenSet = true; m_description.assign(value); }

    /**
     * <p>The description of the exclusion.</p>
     */
    inline Exclusion& WithDescription(const Aws::String& value) { SetDescription(value); return *this;}

    /**
     * <p>The description of the exclusion.</p>
     */
    inline Exclusion& WithDescription(Aws::String&& value) { SetDescription(std::move(value)); return *this;}

    /**
     * <p>The description of the exclusion.</p>
     */
    inline Exclusion& WithDescription(const char* value) { SetDescription(value); return *this;}


    /**
     * <p>The recommendation for the exclusion.</p>
     */
    inline const Aws::String& GetRecommendation() const{ return m_recommendation; }

    /**
     * <p>The recommendation for the exclusion.</p>
     */
    inline bool RecommendationHasBeenSet() const { return m_recommendationHasBeenSet; }

    /**
     * <p>The recommendation for the exclusion.</p>
     */
    inline void SetRecommendation(const Aws::String& value) { m_recommendationHasBeenSet = true; m_recommendation = value; }

    /**
     * <p>The recommendation for the exclusion.</p>
     */
    inline void SetRecommendation(Aws::String&& value) { m_recommendationHasBeenSet = true; m_recommendation = std::move(value); }

    /**
     * <p>The recommendation for the exclusion.</p>
     */
    inline void SetRecommendation(const char* value) { m_recommendationHasBeenSet = true; m_recommendation.assign(value); }

    /**
     * <p>The recommendation for the exclusion.</p>
     */
    inline Exclusion& WithRecommendation(const Aws::String& value) { SetRecommendation(value); return *this;}

    /**
     * <p>The recommendation for the exclusion.</p>
     */
    inline Exclusion& WithRecommendation(Aws::String&& value) { SetRecommendation(std::move(value)); return *this;}

    /**
     * <p>The recommendation for the exclusion.</p>
     */
    inline Exclusion& WithRecommendation(const char* value) { SetRecommendation(value); return *this;}


    /**
     * <p>The AWS resources for which the exclusion pertains.</p>
     */
    inline const Aws::Vector<Scope>& GetScopes() const{ return m_scopes; }

    /**
     * <p>The AWS resources for which the exclusion pertains.</p>
     */
    inline bool ScopesHasBeenSet() const { return m_scopesHasBeenSet; }

    /**
     * <p>The AWS resources for which the exclusion pertains.</p>
     */
    inline void SetScopes(const Aws::Vector<Scope>& value) { m_scopesHasBeenSet = true; m_scopes = value; }

    /**
     * <p>The AWS resources for which the exclusion pertains.</p>
     */
    inline void SetScopes(Aws::Vector<Scope>&& value) { m_scopesHasBeenSet = true; m_scopes = std::move(value); }

    /**
     * <p>The AWS resources for which the exclusion pertains.</p>
     */
    inline Exclusion& WithScopes(const Aws::Vector<Scope>& value) { SetScopes(value); return *this;}

    /**
     * <p>The AWS resources for which the exclusion pertains.</p>
     */
    inline Exclusion& WithScopes(Aws::Vector<Scope>&& value) { SetScopes(std::move(value)); return *this;}

    /**
     * <p>The AWS resources for which the exclusion pertains.</p>
     */
    inline Exclusion& AddScopes(const Scope& value) { m_scopesHasBeenSet = true; m_scopes.push_back(value); return *this; }

    /**
     * <p>The AWS resources for which the exclusion pertains.</p>
     */
    inline Exclusion& AddScopes(Scope&& value) { m_scopesHasBeenSet = true; m_scopes.push_back(std::move(value)); return *this; }


    /**
     * <p>The system-defined attributes for the exclusion.</p>
     */
    inline const Aws::Vector<Attribute>& GetAttributes() const{ return m_attributes; }

    /**
     * <p>The system-defined attributes for the exclusion.</p>
     */
    inline bool AttributesHasBeenSet() const { return m_attributesHasBeenSet; }

    /**
     * <p>The system-defined attributes for the exclusion.</p>
     */
    inline void SetAttributes(const Aws::Vector<Attribute>& value) { m_attributesHasBeenSet = true; m_attributes = value; }

    /**
     * <p>The system-defined attributes for the exclusion.</p>
     */
    inline void SetAttributes(Aws::Vector<Attribute>&& value) { m_attributesHasBeenSet = true; m_attributes = std::move(value); }

    /**
     * <p>The system-defined attributes for the exclusion.</p>
     */
    inline Exclusion& WithAttributes(const Aws::Vector<Attribute>& value) { SetAttributes(value); return *this;}

    /**
     * <p>The system-defined attributes for the exclusion.</p>
     */
    inline Exclusion& WithAttributes(Aws::Vector<Attribute>&& value) { SetAttributes(std::move(value)); return *this;}

    /**
     * <p>The system-defined attributes for the exclusion.</p>
     */
    inline Exclusion& AddAttributes(const Attribute& value) { m_attributesHasBeenSet = true; m_attributes.push_back(value); return *this; }

    /**
     * <p>The system-defined attributes for the exclusion.</p>
     */
    inline Exclusion& AddAttributes(Attribute&& value) { m_attributesHasBeenSet = true; m_attributes.push_back(std::move(value)); return *this; }

  private:

    Aws::String m_arn;
    bool m_arnHasBeenSet = false;

    Aws::String m_title;
    bool m_titleHasBeenSet = false;

    Aws::String m_description;
    bool m_descriptionHasBeenSet = false;

    Aws::String m_recommendation;
    bool m_recommendationHasBeenSet = false;

    Aws::Vector<Scope> m_scopes;
    bool m_scopesHasBeenSet = false;

    Aws::Vector<Attribute> m_attributes;
    bool m_attributesHasBeenSet = false;
  };

} // namespace Model
} // namespace Inspector
} // namespace Aws
