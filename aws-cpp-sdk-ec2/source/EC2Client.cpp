﻿/**
 * Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
 * SPDX-License-Identifier: Apache-2.0.
 */

#include <aws/core/utils/Outcome.h>
#include <aws/core/auth/AWSAuthSigner.h>
#include <aws/core/client/CoreErrors.h>
#include <aws/core/client/RetryStrategy.h>
#include <aws/core/http/HttpClient.h>
#include <aws/core/http/HttpResponse.h>
#include <aws/core/http/HttpClientFactory.h>
#include <aws/core/auth/AWSCredentialsProviderChain.h>
#include <aws/core/utils/xml/XmlSerializer.h>
#include <aws/core/utils/memory/stl/AWSStringStream.h>
#include <aws/core/utils/threading/Executor.h>
#include <aws/core/utils/DNS.h>
#include <aws/core/utils/logging/LogMacros.h>

#include <aws/ec2/EC2Client.h>
#include <aws/ec2/EC2Endpoint.h>
#include <aws/ec2/EC2ErrorMarshaller.h>
#include <aws/ec2/model/AcceptReservedInstancesExchangeQuoteRequest.h>
#include <aws/ec2/model/AcceptTransitGatewayMulticastDomainAssociationsRequest.h>
#include <aws/ec2/model/AcceptTransitGatewayPeeringAttachmentRequest.h>
#include <aws/ec2/model/AcceptTransitGatewayVpcAttachmentRequest.h>
#include <aws/ec2/model/AcceptVpcEndpointConnectionsRequest.h>
#include <aws/ec2/model/AcceptVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/AdvertiseByoipCidrRequest.h>
#include <aws/ec2/model/AllocateAddressRequest.h>
#include <aws/ec2/model/AllocateHostsRequest.h>
#include <aws/ec2/model/AllocateIpamPoolCidrRequest.h>
#include <aws/ec2/model/ApplySecurityGroupsToClientVpnTargetNetworkRequest.h>
#include <aws/ec2/model/AssignIpv6AddressesRequest.h>
#include <aws/ec2/model/AssignPrivateIpAddressesRequest.h>
#include <aws/ec2/model/AssociateAddressRequest.h>
#include <aws/ec2/model/AssociateClientVpnTargetNetworkRequest.h>
#include <aws/ec2/model/AssociateDhcpOptionsRequest.h>
#include <aws/ec2/model/AssociateEnclaveCertificateIamRoleRequest.h>
#include <aws/ec2/model/AssociateIamInstanceProfileRequest.h>
#include <aws/ec2/model/AssociateInstanceEventWindowRequest.h>
#include <aws/ec2/model/AssociateRouteTableRequest.h>
#include <aws/ec2/model/AssociateSubnetCidrBlockRequest.h>
#include <aws/ec2/model/AssociateTransitGatewayMulticastDomainRequest.h>
#include <aws/ec2/model/AssociateTransitGatewayPolicyTableRequest.h>
#include <aws/ec2/model/AssociateTransitGatewayRouteTableRequest.h>
#include <aws/ec2/model/AssociateTrunkInterfaceRequest.h>
#include <aws/ec2/model/AssociateVpcCidrBlockRequest.h>
#include <aws/ec2/model/AttachClassicLinkVpcRequest.h>
#include <aws/ec2/model/AttachInternetGatewayRequest.h>
#include <aws/ec2/model/AttachNetworkInterfaceRequest.h>
#include <aws/ec2/model/AttachVolumeRequest.h>
#include <aws/ec2/model/AttachVpnGatewayRequest.h>
#include <aws/ec2/model/AuthorizeClientVpnIngressRequest.h>
#include <aws/ec2/model/AuthorizeSecurityGroupEgressRequest.h>
#include <aws/ec2/model/AuthorizeSecurityGroupIngressRequest.h>
#include <aws/ec2/model/BundleInstanceRequest.h>
#include <aws/ec2/model/CancelBundleTaskRequest.h>
#include <aws/ec2/model/CancelCapacityReservationRequest.h>
#include <aws/ec2/model/CancelCapacityReservationFleetsRequest.h>
#include <aws/ec2/model/CancelConversionTaskRequest.h>
#include <aws/ec2/model/CancelExportTaskRequest.h>
#include <aws/ec2/model/CancelImportTaskRequest.h>
#include <aws/ec2/model/CancelReservedInstancesListingRequest.h>
#include <aws/ec2/model/CancelSpotFleetRequestsRequest.h>
#include <aws/ec2/model/CancelSpotInstanceRequestsRequest.h>
#include <aws/ec2/model/ConfirmProductInstanceRequest.h>
#include <aws/ec2/model/CopyFpgaImageRequest.h>
#include <aws/ec2/model/CopyImageRequest.h>
#include <aws/ec2/model/CopySnapshotRequest.h>
#include <aws/ec2/model/CreateCapacityReservationRequest.h>
#include <aws/ec2/model/CreateCapacityReservationFleetRequest.h>
#include <aws/ec2/model/CreateCarrierGatewayRequest.h>
#include <aws/ec2/model/CreateClientVpnEndpointRequest.h>
#include <aws/ec2/model/CreateClientVpnRouteRequest.h>
#include <aws/ec2/model/CreateCoipCidrRequest.h>
#include <aws/ec2/model/CreateCoipPoolRequest.h>
#include <aws/ec2/model/CreateCustomerGatewayRequest.h>
#include <aws/ec2/model/CreateDefaultSubnetRequest.h>
#include <aws/ec2/model/CreateDefaultVpcRequest.h>
#include <aws/ec2/model/CreateDhcpOptionsRequest.h>
#include <aws/ec2/model/CreateEgressOnlyInternetGatewayRequest.h>
#include <aws/ec2/model/CreateFleetRequest.h>
#include <aws/ec2/model/CreateFlowLogsRequest.h>
#include <aws/ec2/model/CreateFpgaImageRequest.h>
#include <aws/ec2/model/CreateImageRequest.h>
#include <aws/ec2/model/CreateInstanceEventWindowRequest.h>
#include <aws/ec2/model/CreateInstanceExportTaskRequest.h>
#include <aws/ec2/model/CreateInternetGatewayRequest.h>
#include <aws/ec2/model/CreateIpamRequest.h>
#include <aws/ec2/model/CreateIpamPoolRequest.h>
#include <aws/ec2/model/CreateIpamScopeRequest.h>
#include <aws/ec2/model/CreateKeyPairRequest.h>
#include <aws/ec2/model/CreateLaunchTemplateRequest.h>
#include <aws/ec2/model/CreateLaunchTemplateVersionRequest.h>
#include <aws/ec2/model/CreateLocalGatewayRouteRequest.h>
#include <aws/ec2/model/CreateLocalGatewayRouteTableRequest.h>
#include <aws/ec2/model/CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationRequest.h>
#include <aws/ec2/model/CreateLocalGatewayRouteTableVpcAssociationRequest.h>
#include <aws/ec2/model/CreateManagedPrefixListRequest.h>
#include <aws/ec2/model/CreateNatGatewayRequest.h>
#include <aws/ec2/model/CreateNetworkAclRequest.h>
#include <aws/ec2/model/CreateNetworkAclEntryRequest.h>
#include <aws/ec2/model/CreateNetworkInsightsAccessScopeRequest.h>
#include <aws/ec2/model/CreateNetworkInsightsPathRequest.h>
#include <aws/ec2/model/CreateNetworkInterfaceRequest.h>
#include <aws/ec2/model/CreateNetworkInterfacePermissionRequest.h>
#include <aws/ec2/model/CreatePlacementGroupRequest.h>
#include <aws/ec2/model/CreatePublicIpv4PoolRequest.h>
#include <aws/ec2/model/CreateReplaceRootVolumeTaskRequest.h>
#include <aws/ec2/model/CreateReservedInstancesListingRequest.h>
#include <aws/ec2/model/CreateRestoreImageTaskRequest.h>
#include <aws/ec2/model/CreateRouteRequest.h>
#include <aws/ec2/model/CreateRouteTableRequest.h>
#include <aws/ec2/model/CreateSecurityGroupRequest.h>
#include <aws/ec2/model/CreateSnapshotRequest.h>
#include <aws/ec2/model/CreateSnapshotsRequest.h>
#include <aws/ec2/model/CreateSpotDatafeedSubscriptionRequest.h>
#include <aws/ec2/model/CreateStoreImageTaskRequest.h>
#include <aws/ec2/model/CreateSubnetRequest.h>
#include <aws/ec2/model/CreateSubnetCidrReservationRequest.h>
#include <aws/ec2/model/CreateTagsRequest.h>
#include <aws/ec2/model/CreateTrafficMirrorFilterRequest.h>
#include <aws/ec2/model/CreateTrafficMirrorFilterRuleRequest.h>
#include <aws/ec2/model/CreateTrafficMirrorSessionRequest.h>
#include <aws/ec2/model/CreateTrafficMirrorTargetRequest.h>
#include <aws/ec2/model/CreateTransitGatewayRequest.h>
#include <aws/ec2/model/CreateTransitGatewayConnectRequest.h>
#include <aws/ec2/model/CreateTransitGatewayConnectPeerRequest.h>
#include <aws/ec2/model/CreateTransitGatewayMulticastDomainRequest.h>
#include <aws/ec2/model/CreateTransitGatewayPeeringAttachmentRequest.h>
#include <aws/ec2/model/CreateTransitGatewayPolicyTableRequest.h>
#include <aws/ec2/model/CreateTransitGatewayPrefixListReferenceRequest.h>
#include <aws/ec2/model/CreateTransitGatewayRouteRequest.h>
#include <aws/ec2/model/CreateTransitGatewayRouteTableRequest.h>
#include <aws/ec2/model/CreateTransitGatewayRouteTableAnnouncementRequest.h>
#include <aws/ec2/model/CreateTransitGatewayVpcAttachmentRequest.h>
#include <aws/ec2/model/CreateVolumeRequest.h>
#include <aws/ec2/model/CreateVpcRequest.h>
#include <aws/ec2/model/CreateVpcEndpointRequest.h>
#include <aws/ec2/model/CreateVpcEndpointConnectionNotificationRequest.h>
#include <aws/ec2/model/CreateVpcEndpointServiceConfigurationRequest.h>
#include <aws/ec2/model/CreateVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/CreateVpnConnectionRequest.h>
#include <aws/ec2/model/CreateVpnConnectionRouteRequest.h>
#include <aws/ec2/model/CreateVpnGatewayRequest.h>
#include <aws/ec2/model/DeleteCarrierGatewayRequest.h>
#include <aws/ec2/model/DeleteClientVpnEndpointRequest.h>
#include <aws/ec2/model/DeleteClientVpnRouteRequest.h>
#include <aws/ec2/model/DeleteCoipCidrRequest.h>
#include <aws/ec2/model/DeleteCoipPoolRequest.h>
#include <aws/ec2/model/DeleteCustomerGatewayRequest.h>
#include <aws/ec2/model/DeleteDhcpOptionsRequest.h>
#include <aws/ec2/model/DeleteEgressOnlyInternetGatewayRequest.h>
#include <aws/ec2/model/DeleteFleetsRequest.h>
#include <aws/ec2/model/DeleteFlowLogsRequest.h>
#include <aws/ec2/model/DeleteFpgaImageRequest.h>
#include <aws/ec2/model/DeleteInstanceEventWindowRequest.h>
#include <aws/ec2/model/DeleteInternetGatewayRequest.h>
#include <aws/ec2/model/DeleteIpamRequest.h>
#include <aws/ec2/model/DeleteIpamPoolRequest.h>
#include <aws/ec2/model/DeleteIpamScopeRequest.h>
#include <aws/ec2/model/DeleteKeyPairRequest.h>
#include <aws/ec2/model/DeleteLaunchTemplateRequest.h>
#include <aws/ec2/model/DeleteLaunchTemplateVersionsRequest.h>
#include <aws/ec2/model/DeleteLocalGatewayRouteRequest.h>
#include <aws/ec2/model/DeleteLocalGatewayRouteTableRequest.h>
#include <aws/ec2/model/DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationRequest.h>
#include <aws/ec2/model/DeleteLocalGatewayRouteTableVpcAssociationRequest.h>
#include <aws/ec2/model/DeleteManagedPrefixListRequest.h>
#include <aws/ec2/model/DeleteNatGatewayRequest.h>
#include <aws/ec2/model/DeleteNetworkAclRequest.h>
#include <aws/ec2/model/DeleteNetworkAclEntryRequest.h>
#include <aws/ec2/model/DeleteNetworkInsightsAccessScopeRequest.h>
#include <aws/ec2/model/DeleteNetworkInsightsAccessScopeAnalysisRequest.h>
#include <aws/ec2/model/DeleteNetworkInsightsAnalysisRequest.h>
#include <aws/ec2/model/DeleteNetworkInsightsPathRequest.h>
#include <aws/ec2/model/DeleteNetworkInterfaceRequest.h>
#include <aws/ec2/model/DeleteNetworkInterfacePermissionRequest.h>
#include <aws/ec2/model/DeletePlacementGroupRequest.h>
#include <aws/ec2/model/DeletePublicIpv4PoolRequest.h>
#include <aws/ec2/model/DeleteQueuedReservedInstancesRequest.h>
#include <aws/ec2/model/DeleteRouteRequest.h>
#include <aws/ec2/model/DeleteRouteTableRequest.h>
#include <aws/ec2/model/DeleteSecurityGroupRequest.h>
#include <aws/ec2/model/DeleteSnapshotRequest.h>
#include <aws/ec2/model/DeleteSpotDatafeedSubscriptionRequest.h>
#include <aws/ec2/model/DeleteSubnetRequest.h>
#include <aws/ec2/model/DeleteSubnetCidrReservationRequest.h>
#include <aws/ec2/model/DeleteTagsRequest.h>
#include <aws/ec2/model/DeleteTrafficMirrorFilterRequest.h>
#include <aws/ec2/model/DeleteTrafficMirrorFilterRuleRequest.h>
#include <aws/ec2/model/DeleteTrafficMirrorSessionRequest.h>
#include <aws/ec2/model/DeleteTrafficMirrorTargetRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayConnectRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayConnectPeerRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayMulticastDomainRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayPeeringAttachmentRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayPolicyTableRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayPrefixListReferenceRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayRouteRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayRouteTableRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayRouteTableAnnouncementRequest.h>
#include <aws/ec2/model/DeleteTransitGatewayVpcAttachmentRequest.h>
#include <aws/ec2/model/DeleteVolumeRequest.h>
#include <aws/ec2/model/DeleteVpcRequest.h>
#include <aws/ec2/model/DeleteVpcEndpointConnectionNotificationsRequest.h>
#include <aws/ec2/model/DeleteVpcEndpointServiceConfigurationsRequest.h>
#include <aws/ec2/model/DeleteVpcEndpointsRequest.h>
#include <aws/ec2/model/DeleteVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/DeleteVpnConnectionRequest.h>
#include <aws/ec2/model/DeleteVpnConnectionRouteRequest.h>
#include <aws/ec2/model/DeleteVpnGatewayRequest.h>
#include <aws/ec2/model/DeprovisionByoipCidrRequest.h>
#include <aws/ec2/model/DeprovisionIpamPoolCidrRequest.h>
#include <aws/ec2/model/DeprovisionPublicIpv4PoolCidrRequest.h>
#include <aws/ec2/model/DeregisterImageRequest.h>
#include <aws/ec2/model/DeregisterInstanceEventNotificationAttributesRequest.h>
#include <aws/ec2/model/DeregisterTransitGatewayMulticastGroupMembersRequest.h>
#include <aws/ec2/model/DeregisterTransitGatewayMulticastGroupSourcesRequest.h>
#include <aws/ec2/model/DescribeAccountAttributesRequest.h>
#include <aws/ec2/model/DescribeAddressesRequest.h>
#include <aws/ec2/model/DescribeAddressesAttributeRequest.h>
#include <aws/ec2/model/DescribeAggregateIdFormatRequest.h>
#include <aws/ec2/model/DescribeAvailabilityZonesRequest.h>
#include <aws/ec2/model/DescribeBundleTasksRequest.h>
#include <aws/ec2/model/DescribeByoipCidrsRequest.h>
#include <aws/ec2/model/DescribeCapacityReservationFleetsRequest.h>
#include <aws/ec2/model/DescribeCapacityReservationsRequest.h>
#include <aws/ec2/model/DescribeCarrierGatewaysRequest.h>
#include <aws/ec2/model/DescribeClassicLinkInstancesRequest.h>
#include <aws/ec2/model/DescribeClientVpnAuthorizationRulesRequest.h>
#include <aws/ec2/model/DescribeClientVpnConnectionsRequest.h>
#include <aws/ec2/model/DescribeClientVpnEndpointsRequest.h>
#include <aws/ec2/model/DescribeClientVpnRoutesRequest.h>
#include <aws/ec2/model/DescribeClientVpnTargetNetworksRequest.h>
#include <aws/ec2/model/DescribeCoipPoolsRequest.h>
#include <aws/ec2/model/DescribeConversionTasksRequest.h>
#include <aws/ec2/model/DescribeCustomerGatewaysRequest.h>
#include <aws/ec2/model/DescribeDhcpOptionsRequest.h>
#include <aws/ec2/model/DescribeEgressOnlyInternetGatewaysRequest.h>
#include <aws/ec2/model/DescribeElasticGpusRequest.h>
#include <aws/ec2/model/DescribeExportImageTasksRequest.h>
#include <aws/ec2/model/DescribeExportTasksRequest.h>
#include <aws/ec2/model/DescribeFastLaunchImagesRequest.h>
#include <aws/ec2/model/DescribeFastSnapshotRestoresRequest.h>
#include <aws/ec2/model/DescribeFleetHistoryRequest.h>
#include <aws/ec2/model/DescribeFleetInstancesRequest.h>
#include <aws/ec2/model/DescribeFleetsRequest.h>
#include <aws/ec2/model/DescribeFlowLogsRequest.h>
#include <aws/ec2/model/DescribeFpgaImageAttributeRequest.h>
#include <aws/ec2/model/DescribeFpgaImagesRequest.h>
#include <aws/ec2/model/DescribeHostReservationOfferingsRequest.h>
#include <aws/ec2/model/DescribeHostReservationsRequest.h>
#include <aws/ec2/model/DescribeHostsRequest.h>
#include <aws/ec2/model/DescribeIamInstanceProfileAssociationsRequest.h>
#include <aws/ec2/model/DescribeIdFormatRequest.h>
#include <aws/ec2/model/DescribeIdentityIdFormatRequest.h>
#include <aws/ec2/model/DescribeImageAttributeRequest.h>
#include <aws/ec2/model/DescribeImagesRequest.h>
#include <aws/ec2/model/DescribeImportImageTasksRequest.h>
#include <aws/ec2/model/DescribeImportSnapshotTasksRequest.h>
#include <aws/ec2/model/DescribeInstanceAttributeRequest.h>
#include <aws/ec2/model/DescribeInstanceCreditSpecificationsRequest.h>
#include <aws/ec2/model/DescribeInstanceEventNotificationAttributesRequest.h>
#include <aws/ec2/model/DescribeInstanceEventWindowsRequest.h>
#include <aws/ec2/model/DescribeInstanceStatusRequest.h>
#include <aws/ec2/model/DescribeInstanceTypeOfferingsRequest.h>
#include <aws/ec2/model/DescribeInstanceTypesRequest.h>
#include <aws/ec2/model/DescribeInstancesRequest.h>
#include <aws/ec2/model/DescribeInternetGatewaysRequest.h>
#include <aws/ec2/model/DescribeIpamPoolsRequest.h>
#include <aws/ec2/model/DescribeIpamScopesRequest.h>
#include <aws/ec2/model/DescribeIpamsRequest.h>
#include <aws/ec2/model/DescribeIpv6PoolsRequest.h>
#include <aws/ec2/model/DescribeKeyPairsRequest.h>
#include <aws/ec2/model/DescribeLaunchTemplateVersionsRequest.h>
#include <aws/ec2/model/DescribeLaunchTemplatesRequest.h>
#include <aws/ec2/model/DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsRequest.h>
#include <aws/ec2/model/DescribeLocalGatewayRouteTableVpcAssociationsRequest.h>
#include <aws/ec2/model/DescribeLocalGatewayRouteTablesRequest.h>
#include <aws/ec2/model/DescribeLocalGatewayVirtualInterfaceGroupsRequest.h>
#include <aws/ec2/model/DescribeLocalGatewayVirtualInterfacesRequest.h>
#include <aws/ec2/model/DescribeLocalGatewaysRequest.h>
#include <aws/ec2/model/DescribeManagedPrefixListsRequest.h>
#include <aws/ec2/model/DescribeMovingAddressesRequest.h>
#include <aws/ec2/model/DescribeNatGatewaysRequest.h>
#include <aws/ec2/model/DescribeNetworkAclsRequest.h>
#include <aws/ec2/model/DescribeNetworkInsightsAccessScopeAnalysesRequest.h>
#include <aws/ec2/model/DescribeNetworkInsightsAccessScopesRequest.h>
#include <aws/ec2/model/DescribeNetworkInsightsAnalysesRequest.h>
#include <aws/ec2/model/DescribeNetworkInsightsPathsRequest.h>
#include <aws/ec2/model/DescribeNetworkInterfaceAttributeRequest.h>
#include <aws/ec2/model/DescribeNetworkInterfacePermissionsRequest.h>
#include <aws/ec2/model/DescribeNetworkInterfacesRequest.h>
#include <aws/ec2/model/DescribePlacementGroupsRequest.h>
#include <aws/ec2/model/DescribePrefixListsRequest.h>
#include <aws/ec2/model/DescribePrincipalIdFormatRequest.h>
#include <aws/ec2/model/DescribePublicIpv4PoolsRequest.h>
#include <aws/ec2/model/DescribeRegionsRequest.h>
#include <aws/ec2/model/DescribeReplaceRootVolumeTasksRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesListingsRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesModificationsRequest.h>
#include <aws/ec2/model/DescribeReservedInstancesOfferingsRequest.h>
#include <aws/ec2/model/DescribeRouteTablesRequest.h>
#include <aws/ec2/model/DescribeScheduledInstanceAvailabilityRequest.h>
#include <aws/ec2/model/DescribeScheduledInstancesRequest.h>
#include <aws/ec2/model/DescribeSecurityGroupReferencesRequest.h>
#include <aws/ec2/model/DescribeSecurityGroupRulesRequest.h>
#include <aws/ec2/model/DescribeSecurityGroupsRequest.h>
#include <aws/ec2/model/DescribeSnapshotAttributeRequest.h>
#include <aws/ec2/model/DescribeSnapshotTierStatusRequest.h>
#include <aws/ec2/model/DescribeSnapshotsRequest.h>
#include <aws/ec2/model/DescribeSpotDatafeedSubscriptionRequest.h>
#include <aws/ec2/model/DescribeSpotFleetInstancesRequest.h>
#include <aws/ec2/model/DescribeSpotFleetRequestHistoryRequest.h>
#include <aws/ec2/model/DescribeSpotFleetRequestsRequest.h>
#include <aws/ec2/model/DescribeSpotInstanceRequestsRequest.h>
#include <aws/ec2/model/DescribeSpotPriceHistoryRequest.h>
#include <aws/ec2/model/DescribeStaleSecurityGroupsRequest.h>
#include <aws/ec2/model/DescribeStoreImageTasksRequest.h>
#include <aws/ec2/model/DescribeSubnetsRequest.h>
#include <aws/ec2/model/DescribeTagsRequest.h>
#include <aws/ec2/model/DescribeTrafficMirrorFiltersRequest.h>
#include <aws/ec2/model/DescribeTrafficMirrorSessionsRequest.h>
#include <aws/ec2/model/DescribeTrafficMirrorTargetsRequest.h>
#include <aws/ec2/model/DescribeTransitGatewayAttachmentsRequest.h>
#include <aws/ec2/model/DescribeTransitGatewayConnectPeersRequest.h>
#include <aws/ec2/model/DescribeTransitGatewayConnectsRequest.h>
#include <aws/ec2/model/DescribeTransitGatewayMulticastDomainsRequest.h>
#include <aws/ec2/model/DescribeTransitGatewayPeeringAttachmentsRequest.h>
#include <aws/ec2/model/DescribeTransitGatewayPolicyTablesRequest.h>
#include <aws/ec2/model/DescribeTransitGatewayRouteTableAnnouncementsRequest.h>
#include <aws/ec2/model/DescribeTransitGatewayRouteTablesRequest.h>
#include <aws/ec2/model/DescribeTransitGatewayVpcAttachmentsRequest.h>
#include <aws/ec2/model/DescribeTransitGatewaysRequest.h>
#include <aws/ec2/model/DescribeTrunkInterfaceAssociationsRequest.h>
#include <aws/ec2/model/DescribeVolumeAttributeRequest.h>
#include <aws/ec2/model/DescribeVolumeStatusRequest.h>
#include <aws/ec2/model/DescribeVolumesRequest.h>
#include <aws/ec2/model/DescribeVolumesModificationsRequest.h>
#include <aws/ec2/model/DescribeVpcAttributeRequest.h>
#include <aws/ec2/model/DescribeVpcClassicLinkRequest.h>
#include <aws/ec2/model/DescribeVpcClassicLinkDnsSupportRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointConnectionNotificationsRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointConnectionsRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointServiceConfigurationsRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointServicePermissionsRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointServicesRequest.h>
#include <aws/ec2/model/DescribeVpcEndpointsRequest.h>
#include <aws/ec2/model/DescribeVpcPeeringConnectionsRequest.h>
#include <aws/ec2/model/DescribeVpcsRequest.h>
#include <aws/ec2/model/DescribeVpnConnectionsRequest.h>
#include <aws/ec2/model/DescribeVpnGatewaysRequest.h>
#include <aws/ec2/model/DetachClassicLinkVpcRequest.h>
#include <aws/ec2/model/DetachInternetGatewayRequest.h>
#include <aws/ec2/model/DetachNetworkInterfaceRequest.h>
#include <aws/ec2/model/DetachVolumeRequest.h>
#include <aws/ec2/model/DetachVpnGatewayRequest.h>
#include <aws/ec2/model/DisableEbsEncryptionByDefaultRequest.h>
#include <aws/ec2/model/DisableFastLaunchRequest.h>
#include <aws/ec2/model/DisableFastSnapshotRestoresRequest.h>
#include <aws/ec2/model/DisableImageDeprecationRequest.h>
#include <aws/ec2/model/DisableIpamOrganizationAdminAccountRequest.h>
#include <aws/ec2/model/DisableSerialConsoleAccessRequest.h>
#include <aws/ec2/model/DisableTransitGatewayRouteTablePropagationRequest.h>
#include <aws/ec2/model/DisableVgwRoutePropagationRequest.h>
#include <aws/ec2/model/DisableVpcClassicLinkRequest.h>
#include <aws/ec2/model/DisableVpcClassicLinkDnsSupportRequest.h>
#include <aws/ec2/model/DisassociateAddressRequest.h>
#include <aws/ec2/model/DisassociateClientVpnTargetNetworkRequest.h>
#include <aws/ec2/model/DisassociateEnclaveCertificateIamRoleRequest.h>
#include <aws/ec2/model/DisassociateIamInstanceProfileRequest.h>
#include <aws/ec2/model/DisassociateInstanceEventWindowRequest.h>
#include <aws/ec2/model/DisassociateRouteTableRequest.h>
#include <aws/ec2/model/DisassociateSubnetCidrBlockRequest.h>
#include <aws/ec2/model/DisassociateTransitGatewayMulticastDomainRequest.h>
#include <aws/ec2/model/DisassociateTransitGatewayPolicyTableRequest.h>
#include <aws/ec2/model/DisassociateTransitGatewayRouteTableRequest.h>
#include <aws/ec2/model/DisassociateTrunkInterfaceRequest.h>
#include <aws/ec2/model/DisassociateVpcCidrBlockRequest.h>
#include <aws/ec2/model/EnableEbsEncryptionByDefaultRequest.h>
#include <aws/ec2/model/EnableFastLaunchRequest.h>
#include <aws/ec2/model/EnableFastSnapshotRestoresRequest.h>
#include <aws/ec2/model/EnableImageDeprecationRequest.h>
#include <aws/ec2/model/EnableIpamOrganizationAdminAccountRequest.h>
#include <aws/ec2/model/EnableSerialConsoleAccessRequest.h>
#include <aws/ec2/model/EnableTransitGatewayRouteTablePropagationRequest.h>
#include <aws/ec2/model/EnableVgwRoutePropagationRequest.h>
#include <aws/ec2/model/EnableVolumeIORequest.h>
#include <aws/ec2/model/EnableVpcClassicLinkRequest.h>
#include <aws/ec2/model/EnableVpcClassicLinkDnsSupportRequest.h>
#include <aws/ec2/model/ExportClientVpnClientCertificateRevocationListRequest.h>
#include <aws/ec2/model/ExportClientVpnClientConfigurationRequest.h>
#include <aws/ec2/model/ExportImageRequest.h>
#include <aws/ec2/model/ExportTransitGatewayRoutesRequest.h>
#include <aws/ec2/model/GetAssociatedEnclaveCertificateIamRolesRequest.h>
#include <aws/ec2/model/GetAssociatedIpv6PoolCidrsRequest.h>
#include <aws/ec2/model/GetCapacityReservationUsageRequest.h>
#include <aws/ec2/model/GetCoipPoolUsageRequest.h>
#include <aws/ec2/model/GetConsoleOutputRequest.h>
#include <aws/ec2/model/GetConsoleScreenshotRequest.h>
#include <aws/ec2/model/GetDefaultCreditSpecificationRequest.h>
#include <aws/ec2/model/GetEbsDefaultKmsKeyIdRequest.h>
#include <aws/ec2/model/GetEbsEncryptionByDefaultRequest.h>
#include <aws/ec2/model/GetFlowLogsIntegrationTemplateRequest.h>
#include <aws/ec2/model/GetGroupsForCapacityReservationRequest.h>
#include <aws/ec2/model/GetHostReservationPurchasePreviewRequest.h>
#include <aws/ec2/model/GetInstanceTypesFromInstanceRequirementsRequest.h>
#include <aws/ec2/model/GetInstanceUefiDataRequest.h>
#include <aws/ec2/model/GetIpamAddressHistoryRequest.h>
#include <aws/ec2/model/GetIpamPoolAllocationsRequest.h>
#include <aws/ec2/model/GetIpamPoolCidrsRequest.h>
#include <aws/ec2/model/GetIpamResourceCidrsRequest.h>
#include <aws/ec2/model/GetLaunchTemplateDataRequest.h>
#include <aws/ec2/model/GetManagedPrefixListAssociationsRequest.h>
#include <aws/ec2/model/GetManagedPrefixListEntriesRequest.h>
#include <aws/ec2/model/GetNetworkInsightsAccessScopeAnalysisFindingsRequest.h>
#include <aws/ec2/model/GetNetworkInsightsAccessScopeContentRequest.h>
#include <aws/ec2/model/GetPasswordDataRequest.h>
#include <aws/ec2/model/GetReservedInstancesExchangeQuoteRequest.h>
#include <aws/ec2/model/GetSerialConsoleAccessStatusRequest.h>
#include <aws/ec2/model/GetSpotPlacementScoresRequest.h>
#include <aws/ec2/model/GetSubnetCidrReservationsRequest.h>
#include <aws/ec2/model/GetTransitGatewayAttachmentPropagationsRequest.h>
#include <aws/ec2/model/GetTransitGatewayMulticastDomainAssociationsRequest.h>
#include <aws/ec2/model/GetTransitGatewayPolicyTableAssociationsRequest.h>
#include <aws/ec2/model/GetTransitGatewayPolicyTableEntriesRequest.h>
#include <aws/ec2/model/GetTransitGatewayPrefixListReferencesRequest.h>
#include <aws/ec2/model/GetTransitGatewayRouteTableAssociationsRequest.h>
#include <aws/ec2/model/GetTransitGatewayRouteTablePropagationsRequest.h>
#include <aws/ec2/model/GetVpnConnectionDeviceSampleConfigurationRequest.h>
#include <aws/ec2/model/GetVpnConnectionDeviceTypesRequest.h>
#include <aws/ec2/model/ImportClientVpnClientCertificateRevocationListRequest.h>
#include <aws/ec2/model/ImportImageRequest.h>
#include <aws/ec2/model/ImportInstanceRequest.h>
#include <aws/ec2/model/ImportKeyPairRequest.h>
#include <aws/ec2/model/ImportSnapshotRequest.h>
#include <aws/ec2/model/ImportVolumeRequest.h>
#include <aws/ec2/model/ListImagesInRecycleBinRequest.h>
#include <aws/ec2/model/ListSnapshotsInRecycleBinRequest.h>
#include <aws/ec2/model/ModifyAddressAttributeRequest.h>
#include <aws/ec2/model/ModifyAvailabilityZoneGroupRequest.h>
#include <aws/ec2/model/ModifyCapacityReservationRequest.h>
#include <aws/ec2/model/ModifyCapacityReservationFleetRequest.h>
#include <aws/ec2/model/ModifyClientVpnEndpointRequest.h>
#include <aws/ec2/model/ModifyDefaultCreditSpecificationRequest.h>
#include <aws/ec2/model/ModifyEbsDefaultKmsKeyIdRequest.h>
#include <aws/ec2/model/ModifyFleetRequest.h>
#include <aws/ec2/model/ModifyFpgaImageAttributeRequest.h>
#include <aws/ec2/model/ModifyHostsRequest.h>
#include <aws/ec2/model/ModifyIdFormatRequest.h>
#include <aws/ec2/model/ModifyIdentityIdFormatRequest.h>
#include <aws/ec2/model/ModifyImageAttributeRequest.h>
#include <aws/ec2/model/ModifyInstanceAttributeRequest.h>
#include <aws/ec2/model/ModifyInstanceCapacityReservationAttributesRequest.h>
#include <aws/ec2/model/ModifyInstanceCreditSpecificationRequest.h>
#include <aws/ec2/model/ModifyInstanceEventStartTimeRequest.h>
#include <aws/ec2/model/ModifyInstanceEventWindowRequest.h>
#include <aws/ec2/model/ModifyInstanceMaintenanceOptionsRequest.h>
#include <aws/ec2/model/ModifyInstanceMetadataOptionsRequest.h>
#include <aws/ec2/model/ModifyInstancePlacementRequest.h>
#include <aws/ec2/model/ModifyIpamRequest.h>
#include <aws/ec2/model/ModifyIpamPoolRequest.h>
#include <aws/ec2/model/ModifyIpamResourceCidrRequest.h>
#include <aws/ec2/model/ModifyIpamScopeRequest.h>
#include <aws/ec2/model/ModifyLaunchTemplateRequest.h>
#include <aws/ec2/model/ModifyLocalGatewayRouteRequest.h>
#include <aws/ec2/model/ModifyManagedPrefixListRequest.h>
#include <aws/ec2/model/ModifyNetworkInterfaceAttributeRequest.h>
#include <aws/ec2/model/ModifyPrivateDnsNameOptionsRequest.h>
#include <aws/ec2/model/ModifyReservedInstancesRequest.h>
#include <aws/ec2/model/ModifySecurityGroupRulesRequest.h>
#include <aws/ec2/model/ModifySnapshotAttributeRequest.h>
#include <aws/ec2/model/ModifySnapshotTierRequest.h>
#include <aws/ec2/model/ModifySpotFleetRequestRequest.h>
#include <aws/ec2/model/ModifySubnetAttributeRequest.h>
#include <aws/ec2/model/ModifyTrafficMirrorFilterNetworkServicesRequest.h>
#include <aws/ec2/model/ModifyTrafficMirrorFilterRuleRequest.h>
#include <aws/ec2/model/ModifyTrafficMirrorSessionRequest.h>
#include <aws/ec2/model/ModifyTransitGatewayRequest.h>
#include <aws/ec2/model/ModifyTransitGatewayPrefixListReferenceRequest.h>
#include <aws/ec2/model/ModifyTransitGatewayVpcAttachmentRequest.h>
#include <aws/ec2/model/ModifyVolumeRequest.h>
#include <aws/ec2/model/ModifyVolumeAttributeRequest.h>
#include <aws/ec2/model/ModifyVpcAttributeRequest.h>
#include <aws/ec2/model/ModifyVpcEndpointRequest.h>
#include <aws/ec2/model/ModifyVpcEndpointConnectionNotificationRequest.h>
#include <aws/ec2/model/ModifyVpcEndpointServiceConfigurationRequest.h>
#include <aws/ec2/model/ModifyVpcEndpointServicePayerResponsibilityRequest.h>
#include <aws/ec2/model/ModifyVpcEndpointServicePermissionsRequest.h>
#include <aws/ec2/model/ModifyVpcPeeringConnectionOptionsRequest.h>
#include <aws/ec2/model/ModifyVpcTenancyRequest.h>
#include <aws/ec2/model/ModifyVpnConnectionRequest.h>
#include <aws/ec2/model/ModifyVpnConnectionOptionsRequest.h>
#include <aws/ec2/model/ModifyVpnTunnelCertificateRequest.h>
#include <aws/ec2/model/ModifyVpnTunnelOptionsRequest.h>
#include <aws/ec2/model/MonitorInstancesRequest.h>
#include <aws/ec2/model/MoveAddressToVpcRequest.h>
#include <aws/ec2/model/MoveByoipCidrToIpamRequest.h>
#include <aws/ec2/model/ProvisionByoipCidrRequest.h>
#include <aws/ec2/model/ProvisionIpamPoolCidrRequest.h>
#include <aws/ec2/model/ProvisionPublicIpv4PoolCidrRequest.h>
#include <aws/ec2/model/PurchaseHostReservationRequest.h>
#include <aws/ec2/model/PurchaseReservedInstancesOfferingRequest.h>
#include <aws/ec2/model/PurchaseScheduledInstancesRequest.h>
#include <aws/ec2/model/RebootInstancesRequest.h>
#include <aws/ec2/model/RegisterImageRequest.h>
#include <aws/ec2/model/RegisterInstanceEventNotificationAttributesRequest.h>
#include <aws/ec2/model/RegisterTransitGatewayMulticastGroupMembersRequest.h>
#include <aws/ec2/model/RegisterTransitGatewayMulticastGroupSourcesRequest.h>
#include <aws/ec2/model/RejectTransitGatewayMulticastDomainAssociationsRequest.h>
#include <aws/ec2/model/RejectTransitGatewayPeeringAttachmentRequest.h>
#include <aws/ec2/model/RejectTransitGatewayVpcAttachmentRequest.h>
#include <aws/ec2/model/RejectVpcEndpointConnectionsRequest.h>
#include <aws/ec2/model/RejectVpcPeeringConnectionRequest.h>
#include <aws/ec2/model/ReleaseAddressRequest.h>
#include <aws/ec2/model/ReleaseHostsRequest.h>
#include <aws/ec2/model/ReleaseIpamPoolAllocationRequest.h>
#include <aws/ec2/model/ReplaceIamInstanceProfileAssociationRequest.h>
#include <aws/ec2/model/ReplaceNetworkAclAssociationRequest.h>
#include <aws/ec2/model/ReplaceNetworkAclEntryRequest.h>
#include <aws/ec2/model/ReplaceRouteRequest.h>
#include <aws/ec2/model/ReplaceRouteTableAssociationRequest.h>
#include <aws/ec2/model/ReplaceTransitGatewayRouteRequest.h>
#include <aws/ec2/model/ReportInstanceStatusRequest.h>
#include <aws/ec2/model/RequestSpotFleetRequest.h>
#include <aws/ec2/model/RequestSpotInstancesRequest.h>
#include <aws/ec2/model/ResetAddressAttributeRequest.h>
#include <aws/ec2/model/ResetEbsDefaultKmsKeyIdRequest.h>
#include <aws/ec2/model/ResetFpgaImageAttributeRequest.h>
#include <aws/ec2/model/ResetImageAttributeRequest.h>
#include <aws/ec2/model/ResetInstanceAttributeRequest.h>
#include <aws/ec2/model/ResetNetworkInterfaceAttributeRequest.h>
#include <aws/ec2/model/ResetSnapshotAttributeRequest.h>
#include <aws/ec2/model/RestoreAddressToClassicRequest.h>
#include <aws/ec2/model/RestoreImageFromRecycleBinRequest.h>
#include <aws/ec2/model/RestoreManagedPrefixListVersionRequest.h>
#include <aws/ec2/model/RestoreSnapshotFromRecycleBinRequest.h>
#include <aws/ec2/model/RestoreSnapshotTierRequest.h>
#include <aws/ec2/model/RevokeClientVpnIngressRequest.h>
#include <aws/ec2/model/RevokeSecurityGroupEgressRequest.h>
#include <aws/ec2/model/RevokeSecurityGroupIngressRequest.h>
#include <aws/ec2/model/RunInstancesRequest.h>
#include <aws/ec2/model/RunScheduledInstancesRequest.h>
#include <aws/ec2/model/SearchLocalGatewayRoutesRequest.h>
#include <aws/ec2/model/SearchTransitGatewayMulticastGroupsRequest.h>
#include <aws/ec2/model/SearchTransitGatewayRoutesRequest.h>
#include <aws/ec2/model/SendDiagnosticInterruptRequest.h>
#include <aws/ec2/model/StartInstancesRequest.h>
#include <aws/ec2/model/StartNetworkInsightsAccessScopeAnalysisRequest.h>
#include <aws/ec2/model/StartNetworkInsightsAnalysisRequest.h>
#include <aws/ec2/model/StartVpcEndpointServicePrivateDnsVerificationRequest.h>
#include <aws/ec2/model/StopInstancesRequest.h>
#include <aws/ec2/model/TerminateClientVpnConnectionsRequest.h>
#include <aws/ec2/model/TerminateInstancesRequest.h>
#include <aws/ec2/model/UnassignIpv6AddressesRequest.h>
#include <aws/ec2/model/UnassignPrivateIpAddressesRequest.h>
#include <aws/ec2/model/UnmonitorInstancesRequest.h>
#include <aws/ec2/model/UpdateSecurityGroupRuleDescriptionsEgressRequest.h>
#include <aws/ec2/model/UpdateSecurityGroupRuleDescriptionsIngressRequest.h>
#include <aws/ec2/model/WithdrawByoipCidrRequest.h>

using namespace Aws;
using namespace Aws::Auth;
using namespace Aws::Client;
using namespace Aws::EC2;
using namespace Aws::EC2::Model;
using namespace Aws::Http;
using namespace Aws::Utils::Xml;


static const char* SERVICE_NAME = "ec2";
static const char* ALLOCATION_TAG = "EC2Client";

EC2Client::EC2Client(const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(clientConfiguration,
            Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG,
                                             Aws::MakeShared<DefaultAWSCredentialsProviderChain>(ALLOCATION_TAG),
                                             SERVICE_NAME,
                                             Aws::Region::ComputeSignerRegion(clientConfiguration.region)),
            Aws::MakeShared<EC2ErrorMarshaller>(ALLOCATION_TAG)),
  m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

EC2Client::EC2Client(const AWSCredentials& credentials,
                     const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(clientConfiguration,
            Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG,
                                             Aws::MakeShared<SimpleAWSCredentialsProvider>(ALLOCATION_TAG, credentials),
                                             SERVICE_NAME,
                                             Aws::Region::ComputeSignerRegion(clientConfiguration.region)),
            Aws::MakeShared<EC2ErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

EC2Client::EC2Client(const std::shared_ptr<AWSCredentialsProvider>& credentialsProvider,
                     const Client::ClientConfiguration& clientConfiguration) :
  BASECLASS(clientConfiguration,
            Aws::MakeShared<AWSAuthV4Signer>(ALLOCATION_TAG,
                                             credentialsProvider,
                                             SERVICE_NAME,
                                             Aws::Region::ComputeSignerRegion(clientConfiguration.region)),
            Aws::MakeShared<EC2ErrorMarshaller>(ALLOCATION_TAG)),
    m_executor(clientConfiguration.executor)
{
  init(clientConfiguration);
}

EC2Client::~EC2Client()
{
}

void EC2Client::init(const Client::ClientConfiguration& config)
{
  AWSClient::SetServiceClientName("EC2");
  m_configScheme = SchemeMapper::ToString(config.scheme);
  if (config.endpointOverride.empty())
  {
      m_uri = m_configScheme + "://" + EC2Endpoint::ForRegion(config.region, config.useDualStack);
  }
  else
  {
      OverrideEndpoint(config.endpointOverride);
  }
}

void EC2Client::OverrideEndpoint(const Aws::String& endpoint)
{
  if (endpoint.compare(0, 7, "http://") == 0 || endpoint.compare(0, 8, "https://") == 0)
  {
      m_uri = endpoint;
  }
  else
  {
      m_uri = m_configScheme + "://" + endpoint;
  }
}

AcceptReservedInstancesExchangeQuoteOutcome EC2Client::AcceptReservedInstancesExchangeQuote(const AcceptReservedInstancesExchangeQuoteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AcceptReservedInstancesExchangeQuoteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AcceptReservedInstancesExchangeQuoteOutcomeCallable EC2Client::AcceptReservedInstancesExchangeQuoteCallable(const AcceptReservedInstancesExchangeQuoteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AcceptReservedInstancesExchangeQuoteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AcceptReservedInstancesExchangeQuote(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AcceptReservedInstancesExchangeQuoteAsync(const AcceptReservedInstancesExchangeQuoteRequest& request, const AcceptReservedInstancesExchangeQuoteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AcceptReservedInstancesExchangeQuote(request), context);
    } );
}

AcceptTransitGatewayMulticastDomainAssociationsOutcome EC2Client::AcceptTransitGatewayMulticastDomainAssociations(const AcceptTransitGatewayMulticastDomainAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AcceptTransitGatewayMulticastDomainAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AcceptTransitGatewayMulticastDomainAssociationsOutcomeCallable EC2Client::AcceptTransitGatewayMulticastDomainAssociationsCallable(const AcceptTransitGatewayMulticastDomainAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AcceptTransitGatewayMulticastDomainAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AcceptTransitGatewayMulticastDomainAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AcceptTransitGatewayMulticastDomainAssociationsAsync(const AcceptTransitGatewayMulticastDomainAssociationsRequest& request, const AcceptTransitGatewayMulticastDomainAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AcceptTransitGatewayMulticastDomainAssociations(request), context);
    } );
}

AcceptTransitGatewayPeeringAttachmentOutcome EC2Client::AcceptTransitGatewayPeeringAttachment(const AcceptTransitGatewayPeeringAttachmentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AcceptTransitGatewayPeeringAttachmentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AcceptTransitGatewayPeeringAttachmentOutcomeCallable EC2Client::AcceptTransitGatewayPeeringAttachmentCallable(const AcceptTransitGatewayPeeringAttachmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AcceptTransitGatewayPeeringAttachmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AcceptTransitGatewayPeeringAttachment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AcceptTransitGatewayPeeringAttachmentAsync(const AcceptTransitGatewayPeeringAttachmentRequest& request, const AcceptTransitGatewayPeeringAttachmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AcceptTransitGatewayPeeringAttachment(request), context);
    } );
}

AcceptTransitGatewayVpcAttachmentOutcome EC2Client::AcceptTransitGatewayVpcAttachment(const AcceptTransitGatewayVpcAttachmentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AcceptTransitGatewayVpcAttachmentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AcceptTransitGatewayVpcAttachmentOutcomeCallable EC2Client::AcceptTransitGatewayVpcAttachmentCallable(const AcceptTransitGatewayVpcAttachmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AcceptTransitGatewayVpcAttachmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AcceptTransitGatewayVpcAttachment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AcceptTransitGatewayVpcAttachmentAsync(const AcceptTransitGatewayVpcAttachmentRequest& request, const AcceptTransitGatewayVpcAttachmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AcceptTransitGatewayVpcAttachment(request), context);
    } );
}

AcceptVpcEndpointConnectionsOutcome EC2Client::AcceptVpcEndpointConnections(const AcceptVpcEndpointConnectionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AcceptVpcEndpointConnectionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AcceptVpcEndpointConnectionsOutcomeCallable EC2Client::AcceptVpcEndpointConnectionsCallable(const AcceptVpcEndpointConnectionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AcceptVpcEndpointConnectionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AcceptVpcEndpointConnections(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AcceptVpcEndpointConnectionsAsync(const AcceptVpcEndpointConnectionsRequest& request, const AcceptVpcEndpointConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AcceptVpcEndpointConnections(request), context);
    } );
}

AcceptVpcPeeringConnectionOutcome EC2Client::AcceptVpcPeeringConnection(const AcceptVpcPeeringConnectionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AcceptVpcPeeringConnectionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AcceptVpcPeeringConnectionOutcomeCallable EC2Client::AcceptVpcPeeringConnectionCallable(const AcceptVpcPeeringConnectionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AcceptVpcPeeringConnectionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AcceptVpcPeeringConnection(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AcceptVpcPeeringConnectionAsync(const AcceptVpcPeeringConnectionRequest& request, const AcceptVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AcceptVpcPeeringConnection(request), context);
    } );
}

AdvertiseByoipCidrOutcome EC2Client::AdvertiseByoipCidr(const AdvertiseByoipCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AdvertiseByoipCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AdvertiseByoipCidrOutcomeCallable EC2Client::AdvertiseByoipCidrCallable(const AdvertiseByoipCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AdvertiseByoipCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AdvertiseByoipCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AdvertiseByoipCidrAsync(const AdvertiseByoipCidrRequest& request, const AdvertiseByoipCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AdvertiseByoipCidr(request), context);
    } );
}

AllocateAddressOutcome EC2Client::AllocateAddress(const AllocateAddressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AllocateAddressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AllocateAddressOutcomeCallable EC2Client::AllocateAddressCallable(const AllocateAddressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AllocateAddressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AllocateAddress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AllocateAddressAsync(const AllocateAddressRequest& request, const AllocateAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AllocateAddress(request), context);
    } );
}

AllocateHostsOutcome EC2Client::AllocateHosts(const AllocateHostsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AllocateHostsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AllocateHostsOutcomeCallable EC2Client::AllocateHostsCallable(const AllocateHostsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AllocateHostsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AllocateHosts(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AllocateHostsAsync(const AllocateHostsRequest& request, const AllocateHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AllocateHosts(request), context);
    } );
}

AllocateIpamPoolCidrOutcome EC2Client::AllocateIpamPoolCidr(const AllocateIpamPoolCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AllocateIpamPoolCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AllocateIpamPoolCidrOutcomeCallable EC2Client::AllocateIpamPoolCidrCallable(const AllocateIpamPoolCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AllocateIpamPoolCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AllocateIpamPoolCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AllocateIpamPoolCidrAsync(const AllocateIpamPoolCidrRequest& request, const AllocateIpamPoolCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AllocateIpamPoolCidr(request), context);
    } );
}

ApplySecurityGroupsToClientVpnTargetNetworkOutcome EC2Client::ApplySecurityGroupsToClientVpnTargetNetwork(const ApplySecurityGroupsToClientVpnTargetNetworkRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ApplySecurityGroupsToClientVpnTargetNetworkOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ApplySecurityGroupsToClientVpnTargetNetworkOutcomeCallable EC2Client::ApplySecurityGroupsToClientVpnTargetNetworkCallable(const ApplySecurityGroupsToClientVpnTargetNetworkRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ApplySecurityGroupsToClientVpnTargetNetworkOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ApplySecurityGroupsToClientVpnTargetNetwork(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ApplySecurityGroupsToClientVpnTargetNetworkAsync(const ApplySecurityGroupsToClientVpnTargetNetworkRequest& request, const ApplySecurityGroupsToClientVpnTargetNetworkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ApplySecurityGroupsToClientVpnTargetNetwork(request), context);
    } );
}

AssignIpv6AddressesOutcome EC2Client::AssignIpv6Addresses(const AssignIpv6AddressesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssignIpv6AddressesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssignIpv6AddressesOutcomeCallable EC2Client::AssignIpv6AddressesCallable(const AssignIpv6AddressesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssignIpv6AddressesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssignIpv6Addresses(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssignIpv6AddressesAsync(const AssignIpv6AddressesRequest& request, const AssignIpv6AddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssignIpv6Addresses(request), context);
    } );
}

AssignPrivateIpAddressesOutcome EC2Client::AssignPrivateIpAddresses(const AssignPrivateIpAddressesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssignPrivateIpAddressesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssignPrivateIpAddressesOutcomeCallable EC2Client::AssignPrivateIpAddressesCallable(const AssignPrivateIpAddressesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssignPrivateIpAddressesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssignPrivateIpAddresses(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssignPrivateIpAddressesAsync(const AssignPrivateIpAddressesRequest& request, const AssignPrivateIpAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssignPrivateIpAddresses(request), context);
    } );
}

AssociateAddressOutcome EC2Client::AssociateAddress(const AssociateAddressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateAddressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateAddressOutcomeCallable EC2Client::AssociateAddressCallable(const AssociateAddressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateAddressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateAddress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateAddressAsync(const AssociateAddressRequest& request, const AssociateAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateAddress(request), context);
    } );
}

AssociateClientVpnTargetNetworkOutcome EC2Client::AssociateClientVpnTargetNetwork(const AssociateClientVpnTargetNetworkRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateClientVpnTargetNetworkOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateClientVpnTargetNetworkOutcomeCallable EC2Client::AssociateClientVpnTargetNetworkCallable(const AssociateClientVpnTargetNetworkRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateClientVpnTargetNetworkOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateClientVpnTargetNetwork(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateClientVpnTargetNetworkAsync(const AssociateClientVpnTargetNetworkRequest& request, const AssociateClientVpnTargetNetworkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateClientVpnTargetNetwork(request), context);
    } );
}

AssociateDhcpOptionsOutcome EC2Client::AssociateDhcpOptions(const AssociateDhcpOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateDhcpOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateDhcpOptionsOutcomeCallable EC2Client::AssociateDhcpOptionsCallable(const AssociateDhcpOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateDhcpOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateDhcpOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateDhcpOptionsAsync(const AssociateDhcpOptionsRequest& request, const AssociateDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateDhcpOptions(request), context);
    } );
}

AssociateEnclaveCertificateIamRoleOutcome EC2Client::AssociateEnclaveCertificateIamRole(const AssociateEnclaveCertificateIamRoleRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateEnclaveCertificateIamRoleOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateEnclaveCertificateIamRoleOutcomeCallable EC2Client::AssociateEnclaveCertificateIamRoleCallable(const AssociateEnclaveCertificateIamRoleRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateEnclaveCertificateIamRoleOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateEnclaveCertificateIamRole(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateEnclaveCertificateIamRoleAsync(const AssociateEnclaveCertificateIamRoleRequest& request, const AssociateEnclaveCertificateIamRoleResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateEnclaveCertificateIamRole(request), context);
    } );
}

AssociateIamInstanceProfileOutcome EC2Client::AssociateIamInstanceProfile(const AssociateIamInstanceProfileRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateIamInstanceProfileOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateIamInstanceProfileOutcomeCallable EC2Client::AssociateIamInstanceProfileCallable(const AssociateIamInstanceProfileRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateIamInstanceProfileOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateIamInstanceProfile(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateIamInstanceProfileAsync(const AssociateIamInstanceProfileRequest& request, const AssociateIamInstanceProfileResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateIamInstanceProfile(request), context);
    } );
}

AssociateInstanceEventWindowOutcome EC2Client::AssociateInstanceEventWindow(const AssociateInstanceEventWindowRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateInstanceEventWindowOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateInstanceEventWindowOutcomeCallable EC2Client::AssociateInstanceEventWindowCallable(const AssociateInstanceEventWindowRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateInstanceEventWindowOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateInstanceEventWindow(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateInstanceEventWindowAsync(const AssociateInstanceEventWindowRequest& request, const AssociateInstanceEventWindowResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateInstanceEventWindow(request), context);
    } );
}

AssociateRouteTableOutcome EC2Client::AssociateRouteTable(const AssociateRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateRouteTableOutcomeCallable EC2Client::AssociateRouteTableCallable(const AssociateRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateRouteTableAsync(const AssociateRouteTableRequest& request, const AssociateRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateRouteTable(request), context);
    } );
}

AssociateSubnetCidrBlockOutcome EC2Client::AssociateSubnetCidrBlock(const AssociateSubnetCidrBlockRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateSubnetCidrBlockOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateSubnetCidrBlockOutcomeCallable EC2Client::AssociateSubnetCidrBlockCallable(const AssociateSubnetCidrBlockRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateSubnetCidrBlockOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateSubnetCidrBlock(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateSubnetCidrBlockAsync(const AssociateSubnetCidrBlockRequest& request, const AssociateSubnetCidrBlockResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateSubnetCidrBlock(request), context);
    } );
}

AssociateTransitGatewayMulticastDomainOutcome EC2Client::AssociateTransitGatewayMulticastDomain(const AssociateTransitGatewayMulticastDomainRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateTransitGatewayMulticastDomainOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateTransitGatewayMulticastDomainOutcomeCallable EC2Client::AssociateTransitGatewayMulticastDomainCallable(const AssociateTransitGatewayMulticastDomainRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateTransitGatewayMulticastDomainOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateTransitGatewayMulticastDomain(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateTransitGatewayMulticastDomainAsync(const AssociateTransitGatewayMulticastDomainRequest& request, const AssociateTransitGatewayMulticastDomainResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateTransitGatewayMulticastDomain(request), context);
    } );
}

AssociateTransitGatewayPolicyTableOutcome EC2Client::AssociateTransitGatewayPolicyTable(const AssociateTransitGatewayPolicyTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateTransitGatewayPolicyTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateTransitGatewayPolicyTableOutcomeCallable EC2Client::AssociateTransitGatewayPolicyTableCallable(const AssociateTransitGatewayPolicyTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateTransitGatewayPolicyTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateTransitGatewayPolicyTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateTransitGatewayPolicyTableAsync(const AssociateTransitGatewayPolicyTableRequest& request, const AssociateTransitGatewayPolicyTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateTransitGatewayPolicyTable(request), context);
    } );
}

AssociateTransitGatewayRouteTableOutcome EC2Client::AssociateTransitGatewayRouteTable(const AssociateTransitGatewayRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateTransitGatewayRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateTransitGatewayRouteTableOutcomeCallable EC2Client::AssociateTransitGatewayRouteTableCallable(const AssociateTransitGatewayRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateTransitGatewayRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateTransitGatewayRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateTransitGatewayRouteTableAsync(const AssociateTransitGatewayRouteTableRequest& request, const AssociateTransitGatewayRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateTransitGatewayRouteTable(request), context);
    } );
}

AssociateTrunkInterfaceOutcome EC2Client::AssociateTrunkInterface(const AssociateTrunkInterfaceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateTrunkInterfaceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateTrunkInterfaceOutcomeCallable EC2Client::AssociateTrunkInterfaceCallable(const AssociateTrunkInterfaceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateTrunkInterfaceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateTrunkInterface(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateTrunkInterfaceAsync(const AssociateTrunkInterfaceRequest& request, const AssociateTrunkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateTrunkInterface(request), context);
    } );
}

AssociateVpcCidrBlockOutcome EC2Client::AssociateVpcCidrBlock(const AssociateVpcCidrBlockRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AssociateVpcCidrBlockOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AssociateVpcCidrBlockOutcomeCallable EC2Client::AssociateVpcCidrBlockCallable(const AssociateVpcCidrBlockRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AssociateVpcCidrBlockOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AssociateVpcCidrBlock(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AssociateVpcCidrBlockAsync(const AssociateVpcCidrBlockRequest& request, const AssociateVpcCidrBlockResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AssociateVpcCidrBlock(request), context);
    } );
}

AttachClassicLinkVpcOutcome EC2Client::AttachClassicLinkVpc(const AttachClassicLinkVpcRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AttachClassicLinkVpcOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AttachClassicLinkVpcOutcomeCallable EC2Client::AttachClassicLinkVpcCallable(const AttachClassicLinkVpcRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AttachClassicLinkVpcOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AttachClassicLinkVpc(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AttachClassicLinkVpcAsync(const AttachClassicLinkVpcRequest& request, const AttachClassicLinkVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AttachClassicLinkVpc(request), context);
    } );
}

AttachInternetGatewayOutcome EC2Client::AttachInternetGateway(const AttachInternetGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AttachInternetGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AttachInternetGatewayOutcomeCallable EC2Client::AttachInternetGatewayCallable(const AttachInternetGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AttachInternetGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AttachInternetGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AttachInternetGatewayAsync(const AttachInternetGatewayRequest& request, const AttachInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AttachInternetGateway(request), context);
    } );
}

AttachNetworkInterfaceOutcome EC2Client::AttachNetworkInterface(const AttachNetworkInterfaceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AttachNetworkInterfaceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AttachNetworkInterfaceOutcomeCallable EC2Client::AttachNetworkInterfaceCallable(const AttachNetworkInterfaceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AttachNetworkInterfaceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AttachNetworkInterface(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AttachNetworkInterfaceAsync(const AttachNetworkInterfaceRequest& request, const AttachNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AttachNetworkInterface(request), context);
    } );
}

AttachVolumeOutcome EC2Client::AttachVolume(const AttachVolumeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AttachVolumeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AttachVolumeOutcomeCallable EC2Client::AttachVolumeCallable(const AttachVolumeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AttachVolumeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AttachVolume(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AttachVolumeAsync(const AttachVolumeRequest& request, const AttachVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AttachVolume(request), context);
    } );
}

AttachVpnGatewayOutcome EC2Client::AttachVpnGateway(const AttachVpnGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AttachVpnGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AttachVpnGatewayOutcomeCallable EC2Client::AttachVpnGatewayCallable(const AttachVpnGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AttachVpnGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AttachVpnGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AttachVpnGatewayAsync(const AttachVpnGatewayRequest& request, const AttachVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AttachVpnGateway(request), context);
    } );
}

AuthorizeClientVpnIngressOutcome EC2Client::AuthorizeClientVpnIngress(const AuthorizeClientVpnIngressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AuthorizeClientVpnIngressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AuthorizeClientVpnIngressOutcomeCallable EC2Client::AuthorizeClientVpnIngressCallable(const AuthorizeClientVpnIngressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AuthorizeClientVpnIngressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AuthorizeClientVpnIngress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AuthorizeClientVpnIngressAsync(const AuthorizeClientVpnIngressRequest& request, const AuthorizeClientVpnIngressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AuthorizeClientVpnIngress(request), context);
    } );
}

AuthorizeSecurityGroupEgressOutcome EC2Client::AuthorizeSecurityGroupEgress(const AuthorizeSecurityGroupEgressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AuthorizeSecurityGroupEgressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AuthorizeSecurityGroupEgressOutcomeCallable EC2Client::AuthorizeSecurityGroupEgressCallable(const AuthorizeSecurityGroupEgressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AuthorizeSecurityGroupEgressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AuthorizeSecurityGroupEgress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AuthorizeSecurityGroupEgressAsync(const AuthorizeSecurityGroupEgressRequest& request, const AuthorizeSecurityGroupEgressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AuthorizeSecurityGroupEgress(request), context);
    } );
}

AuthorizeSecurityGroupIngressOutcome EC2Client::AuthorizeSecurityGroupIngress(const AuthorizeSecurityGroupIngressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return AuthorizeSecurityGroupIngressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

AuthorizeSecurityGroupIngressOutcomeCallable EC2Client::AuthorizeSecurityGroupIngressCallable(const AuthorizeSecurityGroupIngressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< AuthorizeSecurityGroupIngressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->AuthorizeSecurityGroupIngress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::AuthorizeSecurityGroupIngressAsync(const AuthorizeSecurityGroupIngressRequest& request, const AuthorizeSecurityGroupIngressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, AuthorizeSecurityGroupIngress(request), context);
    } );
}

BundleInstanceOutcome EC2Client::BundleInstance(const BundleInstanceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return BundleInstanceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

BundleInstanceOutcomeCallable EC2Client::BundleInstanceCallable(const BundleInstanceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< BundleInstanceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->BundleInstance(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::BundleInstanceAsync(const BundleInstanceRequest& request, const BundleInstanceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, BundleInstance(request), context);
    } );
}

CancelBundleTaskOutcome EC2Client::CancelBundleTask(const CancelBundleTaskRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CancelBundleTaskOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CancelBundleTaskOutcomeCallable EC2Client::CancelBundleTaskCallable(const CancelBundleTaskRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CancelBundleTaskOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CancelBundleTask(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CancelBundleTaskAsync(const CancelBundleTaskRequest& request, const CancelBundleTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CancelBundleTask(request), context);
    } );
}

CancelCapacityReservationOutcome EC2Client::CancelCapacityReservation(const CancelCapacityReservationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CancelCapacityReservationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CancelCapacityReservationOutcomeCallable EC2Client::CancelCapacityReservationCallable(const CancelCapacityReservationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CancelCapacityReservationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CancelCapacityReservation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CancelCapacityReservationAsync(const CancelCapacityReservationRequest& request, const CancelCapacityReservationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CancelCapacityReservation(request), context);
    } );
}

CancelCapacityReservationFleetsOutcome EC2Client::CancelCapacityReservationFleets(const CancelCapacityReservationFleetsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CancelCapacityReservationFleetsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CancelCapacityReservationFleetsOutcomeCallable EC2Client::CancelCapacityReservationFleetsCallable(const CancelCapacityReservationFleetsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CancelCapacityReservationFleetsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CancelCapacityReservationFleets(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CancelCapacityReservationFleetsAsync(const CancelCapacityReservationFleetsRequest& request, const CancelCapacityReservationFleetsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CancelCapacityReservationFleets(request), context);
    } );
}

CancelConversionTaskOutcome EC2Client::CancelConversionTask(const CancelConversionTaskRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CancelConversionTaskOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CancelConversionTaskOutcomeCallable EC2Client::CancelConversionTaskCallable(const CancelConversionTaskRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CancelConversionTaskOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CancelConversionTask(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CancelConversionTaskAsync(const CancelConversionTaskRequest& request, const CancelConversionTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CancelConversionTask(request), context);
    } );
}

CancelExportTaskOutcome EC2Client::CancelExportTask(const CancelExportTaskRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CancelExportTaskOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CancelExportTaskOutcomeCallable EC2Client::CancelExportTaskCallable(const CancelExportTaskRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CancelExportTaskOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CancelExportTask(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CancelExportTaskAsync(const CancelExportTaskRequest& request, const CancelExportTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CancelExportTask(request), context);
    } );
}

CancelImportTaskOutcome EC2Client::CancelImportTask(const CancelImportTaskRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CancelImportTaskOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CancelImportTaskOutcomeCallable EC2Client::CancelImportTaskCallable(const CancelImportTaskRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CancelImportTaskOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CancelImportTask(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CancelImportTaskAsync(const CancelImportTaskRequest& request, const CancelImportTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CancelImportTask(request), context);
    } );
}

CancelReservedInstancesListingOutcome EC2Client::CancelReservedInstancesListing(const CancelReservedInstancesListingRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CancelReservedInstancesListingOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CancelReservedInstancesListingOutcomeCallable EC2Client::CancelReservedInstancesListingCallable(const CancelReservedInstancesListingRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CancelReservedInstancesListingOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CancelReservedInstancesListing(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CancelReservedInstancesListingAsync(const CancelReservedInstancesListingRequest& request, const CancelReservedInstancesListingResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CancelReservedInstancesListing(request), context);
    } );
}

CancelSpotFleetRequestsOutcome EC2Client::CancelSpotFleetRequests(const CancelSpotFleetRequestsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CancelSpotFleetRequestsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CancelSpotFleetRequestsOutcomeCallable EC2Client::CancelSpotFleetRequestsCallable(const CancelSpotFleetRequestsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CancelSpotFleetRequestsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CancelSpotFleetRequests(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CancelSpotFleetRequestsAsync(const CancelSpotFleetRequestsRequest& request, const CancelSpotFleetRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CancelSpotFleetRequests(request), context);
    } );
}

CancelSpotInstanceRequestsOutcome EC2Client::CancelSpotInstanceRequests(const CancelSpotInstanceRequestsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CancelSpotInstanceRequestsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CancelSpotInstanceRequestsOutcomeCallable EC2Client::CancelSpotInstanceRequestsCallable(const CancelSpotInstanceRequestsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CancelSpotInstanceRequestsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CancelSpotInstanceRequests(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CancelSpotInstanceRequestsAsync(const CancelSpotInstanceRequestsRequest& request, const CancelSpotInstanceRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CancelSpotInstanceRequests(request), context);
    } );
}

ConfirmProductInstanceOutcome EC2Client::ConfirmProductInstance(const ConfirmProductInstanceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ConfirmProductInstanceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ConfirmProductInstanceOutcomeCallable EC2Client::ConfirmProductInstanceCallable(const ConfirmProductInstanceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ConfirmProductInstanceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ConfirmProductInstance(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ConfirmProductInstanceAsync(const ConfirmProductInstanceRequest& request, const ConfirmProductInstanceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ConfirmProductInstance(request), context);
    } );
}

CopyFpgaImageOutcome EC2Client::CopyFpgaImage(const CopyFpgaImageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CopyFpgaImageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CopyFpgaImageOutcomeCallable EC2Client::CopyFpgaImageCallable(const CopyFpgaImageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CopyFpgaImageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CopyFpgaImage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CopyFpgaImageAsync(const CopyFpgaImageRequest& request, const CopyFpgaImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CopyFpgaImage(request), context);
    } );
}

CopyImageOutcome EC2Client::CopyImage(const CopyImageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CopyImageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CopyImageOutcomeCallable EC2Client::CopyImageCallable(const CopyImageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CopyImageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CopyImage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CopyImageAsync(const CopyImageRequest& request, const CopyImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CopyImage(request), context);
    } );
}

CopySnapshotOutcome EC2Client::CopySnapshot(const CopySnapshotRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CopySnapshotOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CopySnapshotOutcomeCallable EC2Client::CopySnapshotCallable(const CopySnapshotRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CopySnapshotOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CopySnapshot(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CopySnapshotAsync(const CopySnapshotRequest& request, const CopySnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CopySnapshot(request), context);
    } );
}

CreateCapacityReservationOutcome EC2Client::CreateCapacityReservation(const CreateCapacityReservationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateCapacityReservationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateCapacityReservationOutcomeCallable EC2Client::CreateCapacityReservationCallable(const CreateCapacityReservationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateCapacityReservationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateCapacityReservation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateCapacityReservationAsync(const CreateCapacityReservationRequest& request, const CreateCapacityReservationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateCapacityReservation(request), context);
    } );
}

CreateCapacityReservationFleetOutcome EC2Client::CreateCapacityReservationFleet(const CreateCapacityReservationFleetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateCapacityReservationFleetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateCapacityReservationFleetOutcomeCallable EC2Client::CreateCapacityReservationFleetCallable(const CreateCapacityReservationFleetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateCapacityReservationFleetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateCapacityReservationFleet(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateCapacityReservationFleetAsync(const CreateCapacityReservationFleetRequest& request, const CreateCapacityReservationFleetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateCapacityReservationFleet(request), context);
    } );
}

CreateCarrierGatewayOutcome EC2Client::CreateCarrierGateway(const CreateCarrierGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateCarrierGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateCarrierGatewayOutcomeCallable EC2Client::CreateCarrierGatewayCallable(const CreateCarrierGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateCarrierGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateCarrierGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateCarrierGatewayAsync(const CreateCarrierGatewayRequest& request, const CreateCarrierGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateCarrierGateway(request), context);
    } );
}

CreateClientVpnEndpointOutcome EC2Client::CreateClientVpnEndpoint(const CreateClientVpnEndpointRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateClientVpnEndpointOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateClientVpnEndpointOutcomeCallable EC2Client::CreateClientVpnEndpointCallable(const CreateClientVpnEndpointRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateClientVpnEndpointOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateClientVpnEndpoint(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateClientVpnEndpointAsync(const CreateClientVpnEndpointRequest& request, const CreateClientVpnEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateClientVpnEndpoint(request), context);
    } );
}

CreateClientVpnRouteOutcome EC2Client::CreateClientVpnRoute(const CreateClientVpnRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateClientVpnRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateClientVpnRouteOutcomeCallable EC2Client::CreateClientVpnRouteCallable(const CreateClientVpnRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateClientVpnRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateClientVpnRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateClientVpnRouteAsync(const CreateClientVpnRouteRequest& request, const CreateClientVpnRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateClientVpnRoute(request), context);
    } );
}

CreateCoipCidrOutcome EC2Client::CreateCoipCidr(const CreateCoipCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateCoipCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateCoipCidrOutcomeCallable EC2Client::CreateCoipCidrCallable(const CreateCoipCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateCoipCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateCoipCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateCoipCidrAsync(const CreateCoipCidrRequest& request, const CreateCoipCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateCoipCidr(request), context);
    } );
}

CreateCoipPoolOutcome EC2Client::CreateCoipPool(const CreateCoipPoolRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateCoipPoolOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateCoipPoolOutcomeCallable EC2Client::CreateCoipPoolCallable(const CreateCoipPoolRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateCoipPoolOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateCoipPool(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateCoipPoolAsync(const CreateCoipPoolRequest& request, const CreateCoipPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateCoipPool(request), context);
    } );
}

CreateCustomerGatewayOutcome EC2Client::CreateCustomerGateway(const CreateCustomerGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateCustomerGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateCustomerGatewayOutcomeCallable EC2Client::CreateCustomerGatewayCallable(const CreateCustomerGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateCustomerGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateCustomerGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateCustomerGatewayAsync(const CreateCustomerGatewayRequest& request, const CreateCustomerGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateCustomerGateway(request), context);
    } );
}

CreateDefaultSubnetOutcome EC2Client::CreateDefaultSubnet(const CreateDefaultSubnetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateDefaultSubnetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateDefaultSubnetOutcomeCallable EC2Client::CreateDefaultSubnetCallable(const CreateDefaultSubnetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateDefaultSubnetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateDefaultSubnet(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateDefaultSubnetAsync(const CreateDefaultSubnetRequest& request, const CreateDefaultSubnetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateDefaultSubnet(request), context);
    } );
}

CreateDefaultVpcOutcome EC2Client::CreateDefaultVpc(const CreateDefaultVpcRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateDefaultVpcOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateDefaultVpcOutcomeCallable EC2Client::CreateDefaultVpcCallable(const CreateDefaultVpcRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateDefaultVpcOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateDefaultVpc(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateDefaultVpcAsync(const CreateDefaultVpcRequest& request, const CreateDefaultVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateDefaultVpc(request), context);
    } );
}

CreateDhcpOptionsOutcome EC2Client::CreateDhcpOptions(const CreateDhcpOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateDhcpOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateDhcpOptionsOutcomeCallable EC2Client::CreateDhcpOptionsCallable(const CreateDhcpOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateDhcpOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateDhcpOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateDhcpOptionsAsync(const CreateDhcpOptionsRequest& request, const CreateDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateDhcpOptions(request), context);
    } );
}

CreateEgressOnlyInternetGatewayOutcome EC2Client::CreateEgressOnlyInternetGateway(const CreateEgressOnlyInternetGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateEgressOnlyInternetGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateEgressOnlyInternetGatewayOutcomeCallable EC2Client::CreateEgressOnlyInternetGatewayCallable(const CreateEgressOnlyInternetGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateEgressOnlyInternetGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateEgressOnlyInternetGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateEgressOnlyInternetGatewayAsync(const CreateEgressOnlyInternetGatewayRequest& request, const CreateEgressOnlyInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateEgressOnlyInternetGateway(request), context);
    } );
}

CreateFleetOutcome EC2Client::CreateFleet(const CreateFleetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateFleetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateFleetOutcomeCallable EC2Client::CreateFleetCallable(const CreateFleetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateFleetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateFleet(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateFleetAsync(const CreateFleetRequest& request, const CreateFleetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateFleet(request), context);
    } );
}

CreateFlowLogsOutcome EC2Client::CreateFlowLogs(const CreateFlowLogsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateFlowLogsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateFlowLogsOutcomeCallable EC2Client::CreateFlowLogsCallable(const CreateFlowLogsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateFlowLogsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateFlowLogs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateFlowLogsAsync(const CreateFlowLogsRequest& request, const CreateFlowLogsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateFlowLogs(request), context);
    } );
}

CreateFpgaImageOutcome EC2Client::CreateFpgaImage(const CreateFpgaImageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateFpgaImageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateFpgaImageOutcomeCallable EC2Client::CreateFpgaImageCallable(const CreateFpgaImageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateFpgaImageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateFpgaImage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateFpgaImageAsync(const CreateFpgaImageRequest& request, const CreateFpgaImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateFpgaImage(request), context);
    } );
}

CreateImageOutcome EC2Client::CreateImage(const CreateImageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateImageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateImageOutcomeCallable EC2Client::CreateImageCallable(const CreateImageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateImageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateImage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateImageAsync(const CreateImageRequest& request, const CreateImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateImage(request), context);
    } );
}

CreateInstanceEventWindowOutcome EC2Client::CreateInstanceEventWindow(const CreateInstanceEventWindowRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateInstanceEventWindowOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateInstanceEventWindowOutcomeCallable EC2Client::CreateInstanceEventWindowCallable(const CreateInstanceEventWindowRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateInstanceEventWindowOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateInstanceEventWindow(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateInstanceEventWindowAsync(const CreateInstanceEventWindowRequest& request, const CreateInstanceEventWindowResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateInstanceEventWindow(request), context);
    } );
}

CreateInstanceExportTaskOutcome EC2Client::CreateInstanceExportTask(const CreateInstanceExportTaskRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateInstanceExportTaskOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateInstanceExportTaskOutcomeCallable EC2Client::CreateInstanceExportTaskCallable(const CreateInstanceExportTaskRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateInstanceExportTaskOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateInstanceExportTask(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateInstanceExportTaskAsync(const CreateInstanceExportTaskRequest& request, const CreateInstanceExportTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateInstanceExportTask(request), context);
    } );
}

CreateInternetGatewayOutcome EC2Client::CreateInternetGateway(const CreateInternetGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateInternetGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateInternetGatewayOutcomeCallable EC2Client::CreateInternetGatewayCallable(const CreateInternetGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateInternetGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateInternetGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateInternetGatewayAsync(const CreateInternetGatewayRequest& request, const CreateInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateInternetGateway(request), context);
    } );
}

CreateIpamOutcome EC2Client::CreateIpam(const CreateIpamRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateIpamOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateIpamOutcomeCallable EC2Client::CreateIpamCallable(const CreateIpamRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateIpamOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateIpam(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateIpamAsync(const CreateIpamRequest& request, const CreateIpamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateIpam(request), context);
    } );
}

CreateIpamPoolOutcome EC2Client::CreateIpamPool(const CreateIpamPoolRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateIpamPoolOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateIpamPoolOutcomeCallable EC2Client::CreateIpamPoolCallable(const CreateIpamPoolRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateIpamPoolOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateIpamPool(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateIpamPoolAsync(const CreateIpamPoolRequest& request, const CreateIpamPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateIpamPool(request), context);
    } );
}

CreateIpamScopeOutcome EC2Client::CreateIpamScope(const CreateIpamScopeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateIpamScopeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateIpamScopeOutcomeCallable EC2Client::CreateIpamScopeCallable(const CreateIpamScopeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateIpamScopeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateIpamScope(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateIpamScopeAsync(const CreateIpamScopeRequest& request, const CreateIpamScopeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateIpamScope(request), context);
    } );
}

CreateKeyPairOutcome EC2Client::CreateKeyPair(const CreateKeyPairRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateKeyPairOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateKeyPairOutcomeCallable EC2Client::CreateKeyPairCallable(const CreateKeyPairRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateKeyPairOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateKeyPair(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateKeyPairAsync(const CreateKeyPairRequest& request, const CreateKeyPairResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateKeyPair(request), context);
    } );
}

CreateLaunchTemplateOutcome EC2Client::CreateLaunchTemplate(const CreateLaunchTemplateRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateLaunchTemplateOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateLaunchTemplateOutcomeCallable EC2Client::CreateLaunchTemplateCallable(const CreateLaunchTemplateRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateLaunchTemplateOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateLaunchTemplate(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateLaunchTemplateAsync(const CreateLaunchTemplateRequest& request, const CreateLaunchTemplateResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateLaunchTemplate(request), context);
    } );
}

CreateLaunchTemplateVersionOutcome EC2Client::CreateLaunchTemplateVersion(const CreateLaunchTemplateVersionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateLaunchTemplateVersionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateLaunchTemplateVersionOutcomeCallable EC2Client::CreateLaunchTemplateVersionCallable(const CreateLaunchTemplateVersionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateLaunchTemplateVersionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateLaunchTemplateVersion(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateLaunchTemplateVersionAsync(const CreateLaunchTemplateVersionRequest& request, const CreateLaunchTemplateVersionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateLaunchTemplateVersion(request), context);
    } );
}

CreateLocalGatewayRouteOutcome EC2Client::CreateLocalGatewayRoute(const CreateLocalGatewayRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateLocalGatewayRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateLocalGatewayRouteOutcomeCallable EC2Client::CreateLocalGatewayRouteCallable(const CreateLocalGatewayRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateLocalGatewayRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateLocalGatewayRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateLocalGatewayRouteAsync(const CreateLocalGatewayRouteRequest& request, const CreateLocalGatewayRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateLocalGatewayRoute(request), context);
    } );
}

CreateLocalGatewayRouteTableOutcome EC2Client::CreateLocalGatewayRouteTable(const CreateLocalGatewayRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateLocalGatewayRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateLocalGatewayRouteTableOutcomeCallable EC2Client::CreateLocalGatewayRouteTableCallable(const CreateLocalGatewayRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateLocalGatewayRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateLocalGatewayRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateLocalGatewayRouteTableAsync(const CreateLocalGatewayRouteTableRequest& request, const CreateLocalGatewayRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateLocalGatewayRouteTable(request), context);
    } );
}

CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationOutcome EC2Client::CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociation(const CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationOutcomeCallable EC2Client::CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationCallable(const CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationAsync(const CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationRequest& request, const CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateLocalGatewayRouteTableVirtualInterfaceGroupAssociation(request), context);
    } );
}

CreateLocalGatewayRouteTableVpcAssociationOutcome EC2Client::CreateLocalGatewayRouteTableVpcAssociation(const CreateLocalGatewayRouteTableVpcAssociationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateLocalGatewayRouteTableVpcAssociationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateLocalGatewayRouteTableVpcAssociationOutcomeCallable EC2Client::CreateLocalGatewayRouteTableVpcAssociationCallable(const CreateLocalGatewayRouteTableVpcAssociationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateLocalGatewayRouteTableVpcAssociationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateLocalGatewayRouteTableVpcAssociation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateLocalGatewayRouteTableVpcAssociationAsync(const CreateLocalGatewayRouteTableVpcAssociationRequest& request, const CreateLocalGatewayRouteTableVpcAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateLocalGatewayRouteTableVpcAssociation(request), context);
    } );
}

CreateManagedPrefixListOutcome EC2Client::CreateManagedPrefixList(const CreateManagedPrefixListRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateManagedPrefixListOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateManagedPrefixListOutcomeCallable EC2Client::CreateManagedPrefixListCallable(const CreateManagedPrefixListRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateManagedPrefixListOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateManagedPrefixList(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateManagedPrefixListAsync(const CreateManagedPrefixListRequest& request, const CreateManagedPrefixListResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateManagedPrefixList(request), context);
    } );
}

CreateNatGatewayOutcome EC2Client::CreateNatGateway(const CreateNatGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateNatGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateNatGatewayOutcomeCallable EC2Client::CreateNatGatewayCallable(const CreateNatGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateNatGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateNatGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateNatGatewayAsync(const CreateNatGatewayRequest& request, const CreateNatGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateNatGateway(request), context);
    } );
}

CreateNetworkAclOutcome EC2Client::CreateNetworkAcl(const CreateNetworkAclRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateNetworkAclOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateNetworkAclOutcomeCallable EC2Client::CreateNetworkAclCallable(const CreateNetworkAclRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateNetworkAclOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateNetworkAcl(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateNetworkAclAsync(const CreateNetworkAclRequest& request, const CreateNetworkAclResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateNetworkAcl(request), context);
    } );
}

CreateNetworkAclEntryOutcome EC2Client::CreateNetworkAclEntry(const CreateNetworkAclEntryRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateNetworkAclEntryOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateNetworkAclEntryOutcomeCallable EC2Client::CreateNetworkAclEntryCallable(const CreateNetworkAclEntryRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateNetworkAclEntryOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateNetworkAclEntry(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateNetworkAclEntryAsync(const CreateNetworkAclEntryRequest& request, const CreateNetworkAclEntryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateNetworkAclEntry(request), context);
    } );
}

CreateNetworkInsightsAccessScopeOutcome EC2Client::CreateNetworkInsightsAccessScope(const CreateNetworkInsightsAccessScopeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateNetworkInsightsAccessScopeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateNetworkInsightsAccessScopeOutcomeCallable EC2Client::CreateNetworkInsightsAccessScopeCallable(const CreateNetworkInsightsAccessScopeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateNetworkInsightsAccessScopeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateNetworkInsightsAccessScope(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateNetworkInsightsAccessScopeAsync(const CreateNetworkInsightsAccessScopeRequest& request, const CreateNetworkInsightsAccessScopeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateNetworkInsightsAccessScope(request), context);
    } );
}

CreateNetworkInsightsPathOutcome EC2Client::CreateNetworkInsightsPath(const CreateNetworkInsightsPathRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateNetworkInsightsPathOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateNetworkInsightsPathOutcomeCallable EC2Client::CreateNetworkInsightsPathCallable(const CreateNetworkInsightsPathRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateNetworkInsightsPathOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateNetworkInsightsPath(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateNetworkInsightsPathAsync(const CreateNetworkInsightsPathRequest& request, const CreateNetworkInsightsPathResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateNetworkInsightsPath(request), context);
    } );
}

CreateNetworkInterfaceOutcome EC2Client::CreateNetworkInterface(const CreateNetworkInterfaceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateNetworkInterfaceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateNetworkInterfaceOutcomeCallable EC2Client::CreateNetworkInterfaceCallable(const CreateNetworkInterfaceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateNetworkInterfaceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateNetworkInterface(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateNetworkInterfaceAsync(const CreateNetworkInterfaceRequest& request, const CreateNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateNetworkInterface(request), context);
    } );
}

CreateNetworkInterfacePermissionOutcome EC2Client::CreateNetworkInterfacePermission(const CreateNetworkInterfacePermissionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateNetworkInterfacePermissionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateNetworkInterfacePermissionOutcomeCallable EC2Client::CreateNetworkInterfacePermissionCallable(const CreateNetworkInterfacePermissionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateNetworkInterfacePermissionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateNetworkInterfacePermission(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateNetworkInterfacePermissionAsync(const CreateNetworkInterfacePermissionRequest& request, const CreateNetworkInterfacePermissionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateNetworkInterfacePermission(request), context);
    } );
}

CreatePlacementGroupOutcome EC2Client::CreatePlacementGroup(const CreatePlacementGroupRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreatePlacementGroupOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreatePlacementGroupOutcomeCallable EC2Client::CreatePlacementGroupCallable(const CreatePlacementGroupRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreatePlacementGroupOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreatePlacementGroup(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreatePlacementGroupAsync(const CreatePlacementGroupRequest& request, const CreatePlacementGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreatePlacementGroup(request), context);
    } );
}

CreatePublicIpv4PoolOutcome EC2Client::CreatePublicIpv4Pool(const CreatePublicIpv4PoolRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreatePublicIpv4PoolOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreatePublicIpv4PoolOutcomeCallable EC2Client::CreatePublicIpv4PoolCallable(const CreatePublicIpv4PoolRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreatePublicIpv4PoolOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreatePublicIpv4Pool(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreatePublicIpv4PoolAsync(const CreatePublicIpv4PoolRequest& request, const CreatePublicIpv4PoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreatePublicIpv4Pool(request), context);
    } );
}

CreateReplaceRootVolumeTaskOutcome EC2Client::CreateReplaceRootVolumeTask(const CreateReplaceRootVolumeTaskRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateReplaceRootVolumeTaskOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateReplaceRootVolumeTaskOutcomeCallable EC2Client::CreateReplaceRootVolumeTaskCallable(const CreateReplaceRootVolumeTaskRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateReplaceRootVolumeTaskOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateReplaceRootVolumeTask(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateReplaceRootVolumeTaskAsync(const CreateReplaceRootVolumeTaskRequest& request, const CreateReplaceRootVolumeTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateReplaceRootVolumeTask(request), context);
    } );
}

CreateReservedInstancesListingOutcome EC2Client::CreateReservedInstancesListing(const CreateReservedInstancesListingRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateReservedInstancesListingOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateReservedInstancesListingOutcomeCallable EC2Client::CreateReservedInstancesListingCallable(const CreateReservedInstancesListingRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateReservedInstancesListingOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateReservedInstancesListing(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateReservedInstancesListingAsync(const CreateReservedInstancesListingRequest& request, const CreateReservedInstancesListingResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateReservedInstancesListing(request), context);
    } );
}

CreateRestoreImageTaskOutcome EC2Client::CreateRestoreImageTask(const CreateRestoreImageTaskRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateRestoreImageTaskOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateRestoreImageTaskOutcomeCallable EC2Client::CreateRestoreImageTaskCallable(const CreateRestoreImageTaskRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateRestoreImageTaskOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateRestoreImageTask(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateRestoreImageTaskAsync(const CreateRestoreImageTaskRequest& request, const CreateRestoreImageTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateRestoreImageTask(request), context);
    } );
}

CreateRouteOutcome EC2Client::CreateRoute(const CreateRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateRouteOutcomeCallable EC2Client::CreateRouteCallable(const CreateRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateRouteAsync(const CreateRouteRequest& request, const CreateRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateRoute(request), context);
    } );
}

CreateRouteTableOutcome EC2Client::CreateRouteTable(const CreateRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateRouteTableOutcomeCallable EC2Client::CreateRouteTableCallable(const CreateRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateRouteTableAsync(const CreateRouteTableRequest& request, const CreateRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateRouteTable(request), context);
    } );
}

CreateSecurityGroupOutcome EC2Client::CreateSecurityGroup(const CreateSecurityGroupRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateSecurityGroupOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateSecurityGroupOutcomeCallable EC2Client::CreateSecurityGroupCallable(const CreateSecurityGroupRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateSecurityGroupOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateSecurityGroup(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateSecurityGroupAsync(const CreateSecurityGroupRequest& request, const CreateSecurityGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateSecurityGroup(request), context);
    } );
}

CreateSnapshotOutcome EC2Client::CreateSnapshot(const CreateSnapshotRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateSnapshotOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateSnapshotOutcomeCallable EC2Client::CreateSnapshotCallable(const CreateSnapshotRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateSnapshotOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateSnapshot(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateSnapshotAsync(const CreateSnapshotRequest& request, const CreateSnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateSnapshot(request), context);
    } );
}

CreateSnapshotsOutcome EC2Client::CreateSnapshots(const CreateSnapshotsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateSnapshotsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateSnapshotsOutcomeCallable EC2Client::CreateSnapshotsCallable(const CreateSnapshotsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateSnapshotsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateSnapshots(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateSnapshotsAsync(const CreateSnapshotsRequest& request, const CreateSnapshotsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateSnapshots(request), context);
    } );
}

CreateSpotDatafeedSubscriptionOutcome EC2Client::CreateSpotDatafeedSubscription(const CreateSpotDatafeedSubscriptionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateSpotDatafeedSubscriptionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateSpotDatafeedSubscriptionOutcomeCallable EC2Client::CreateSpotDatafeedSubscriptionCallable(const CreateSpotDatafeedSubscriptionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateSpotDatafeedSubscriptionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateSpotDatafeedSubscription(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateSpotDatafeedSubscriptionAsync(const CreateSpotDatafeedSubscriptionRequest& request, const CreateSpotDatafeedSubscriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateSpotDatafeedSubscription(request), context);
    } );
}

CreateStoreImageTaskOutcome EC2Client::CreateStoreImageTask(const CreateStoreImageTaskRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateStoreImageTaskOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateStoreImageTaskOutcomeCallable EC2Client::CreateStoreImageTaskCallable(const CreateStoreImageTaskRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateStoreImageTaskOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateStoreImageTask(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateStoreImageTaskAsync(const CreateStoreImageTaskRequest& request, const CreateStoreImageTaskResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateStoreImageTask(request), context);
    } );
}

CreateSubnetOutcome EC2Client::CreateSubnet(const CreateSubnetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateSubnetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateSubnetOutcomeCallable EC2Client::CreateSubnetCallable(const CreateSubnetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateSubnetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateSubnet(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateSubnetAsync(const CreateSubnetRequest& request, const CreateSubnetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateSubnet(request), context);
    } );
}

CreateSubnetCidrReservationOutcome EC2Client::CreateSubnetCidrReservation(const CreateSubnetCidrReservationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateSubnetCidrReservationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateSubnetCidrReservationOutcomeCallable EC2Client::CreateSubnetCidrReservationCallable(const CreateSubnetCidrReservationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateSubnetCidrReservationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateSubnetCidrReservation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateSubnetCidrReservationAsync(const CreateSubnetCidrReservationRequest& request, const CreateSubnetCidrReservationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateSubnetCidrReservation(request), context);
    } );
}

CreateTagsOutcome EC2Client::CreateTags(const CreateTagsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTagsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTagsOutcomeCallable EC2Client::CreateTagsCallable(const CreateTagsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTagsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTags(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTagsAsync(const CreateTagsRequest& request, const CreateTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTags(request), context);
    } );
}

CreateTrafficMirrorFilterOutcome EC2Client::CreateTrafficMirrorFilter(const CreateTrafficMirrorFilterRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTrafficMirrorFilterOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTrafficMirrorFilterOutcomeCallable EC2Client::CreateTrafficMirrorFilterCallable(const CreateTrafficMirrorFilterRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTrafficMirrorFilterOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTrafficMirrorFilter(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTrafficMirrorFilterAsync(const CreateTrafficMirrorFilterRequest& request, const CreateTrafficMirrorFilterResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTrafficMirrorFilter(request), context);
    } );
}

CreateTrafficMirrorFilterRuleOutcome EC2Client::CreateTrafficMirrorFilterRule(const CreateTrafficMirrorFilterRuleRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTrafficMirrorFilterRuleOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTrafficMirrorFilterRuleOutcomeCallable EC2Client::CreateTrafficMirrorFilterRuleCallable(const CreateTrafficMirrorFilterRuleRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTrafficMirrorFilterRuleOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTrafficMirrorFilterRule(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTrafficMirrorFilterRuleAsync(const CreateTrafficMirrorFilterRuleRequest& request, const CreateTrafficMirrorFilterRuleResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTrafficMirrorFilterRule(request), context);
    } );
}

CreateTrafficMirrorSessionOutcome EC2Client::CreateTrafficMirrorSession(const CreateTrafficMirrorSessionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTrafficMirrorSessionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTrafficMirrorSessionOutcomeCallable EC2Client::CreateTrafficMirrorSessionCallable(const CreateTrafficMirrorSessionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTrafficMirrorSessionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTrafficMirrorSession(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTrafficMirrorSessionAsync(const CreateTrafficMirrorSessionRequest& request, const CreateTrafficMirrorSessionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTrafficMirrorSession(request), context);
    } );
}

CreateTrafficMirrorTargetOutcome EC2Client::CreateTrafficMirrorTarget(const CreateTrafficMirrorTargetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTrafficMirrorTargetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTrafficMirrorTargetOutcomeCallable EC2Client::CreateTrafficMirrorTargetCallable(const CreateTrafficMirrorTargetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTrafficMirrorTargetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTrafficMirrorTarget(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTrafficMirrorTargetAsync(const CreateTrafficMirrorTargetRequest& request, const CreateTrafficMirrorTargetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTrafficMirrorTarget(request), context);
    } );
}

CreateTransitGatewayOutcome EC2Client::CreateTransitGateway(const CreateTransitGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayOutcomeCallable EC2Client::CreateTransitGatewayCallable(const CreateTransitGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayAsync(const CreateTransitGatewayRequest& request, const CreateTransitGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGateway(request), context);
    } );
}

CreateTransitGatewayConnectOutcome EC2Client::CreateTransitGatewayConnect(const CreateTransitGatewayConnectRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayConnectOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayConnectOutcomeCallable EC2Client::CreateTransitGatewayConnectCallable(const CreateTransitGatewayConnectRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayConnectOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayConnect(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayConnectAsync(const CreateTransitGatewayConnectRequest& request, const CreateTransitGatewayConnectResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayConnect(request), context);
    } );
}

CreateTransitGatewayConnectPeerOutcome EC2Client::CreateTransitGatewayConnectPeer(const CreateTransitGatewayConnectPeerRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayConnectPeerOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayConnectPeerOutcomeCallable EC2Client::CreateTransitGatewayConnectPeerCallable(const CreateTransitGatewayConnectPeerRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayConnectPeerOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayConnectPeer(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayConnectPeerAsync(const CreateTransitGatewayConnectPeerRequest& request, const CreateTransitGatewayConnectPeerResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayConnectPeer(request), context);
    } );
}

CreateTransitGatewayMulticastDomainOutcome EC2Client::CreateTransitGatewayMulticastDomain(const CreateTransitGatewayMulticastDomainRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayMulticastDomainOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayMulticastDomainOutcomeCallable EC2Client::CreateTransitGatewayMulticastDomainCallable(const CreateTransitGatewayMulticastDomainRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayMulticastDomainOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayMulticastDomain(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayMulticastDomainAsync(const CreateTransitGatewayMulticastDomainRequest& request, const CreateTransitGatewayMulticastDomainResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayMulticastDomain(request), context);
    } );
}

CreateTransitGatewayPeeringAttachmentOutcome EC2Client::CreateTransitGatewayPeeringAttachment(const CreateTransitGatewayPeeringAttachmentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayPeeringAttachmentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayPeeringAttachmentOutcomeCallable EC2Client::CreateTransitGatewayPeeringAttachmentCallable(const CreateTransitGatewayPeeringAttachmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayPeeringAttachmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayPeeringAttachment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayPeeringAttachmentAsync(const CreateTransitGatewayPeeringAttachmentRequest& request, const CreateTransitGatewayPeeringAttachmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayPeeringAttachment(request), context);
    } );
}

CreateTransitGatewayPolicyTableOutcome EC2Client::CreateTransitGatewayPolicyTable(const CreateTransitGatewayPolicyTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayPolicyTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayPolicyTableOutcomeCallable EC2Client::CreateTransitGatewayPolicyTableCallable(const CreateTransitGatewayPolicyTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayPolicyTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayPolicyTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayPolicyTableAsync(const CreateTransitGatewayPolicyTableRequest& request, const CreateTransitGatewayPolicyTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayPolicyTable(request), context);
    } );
}

CreateTransitGatewayPrefixListReferenceOutcome EC2Client::CreateTransitGatewayPrefixListReference(const CreateTransitGatewayPrefixListReferenceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayPrefixListReferenceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayPrefixListReferenceOutcomeCallable EC2Client::CreateTransitGatewayPrefixListReferenceCallable(const CreateTransitGatewayPrefixListReferenceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayPrefixListReferenceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayPrefixListReference(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayPrefixListReferenceAsync(const CreateTransitGatewayPrefixListReferenceRequest& request, const CreateTransitGatewayPrefixListReferenceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayPrefixListReference(request), context);
    } );
}

CreateTransitGatewayRouteOutcome EC2Client::CreateTransitGatewayRoute(const CreateTransitGatewayRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayRouteOutcomeCallable EC2Client::CreateTransitGatewayRouteCallable(const CreateTransitGatewayRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayRouteAsync(const CreateTransitGatewayRouteRequest& request, const CreateTransitGatewayRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayRoute(request), context);
    } );
}

CreateTransitGatewayRouteTableOutcome EC2Client::CreateTransitGatewayRouteTable(const CreateTransitGatewayRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayRouteTableOutcomeCallable EC2Client::CreateTransitGatewayRouteTableCallable(const CreateTransitGatewayRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayRouteTableAsync(const CreateTransitGatewayRouteTableRequest& request, const CreateTransitGatewayRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayRouteTable(request), context);
    } );
}

CreateTransitGatewayRouteTableAnnouncementOutcome EC2Client::CreateTransitGatewayRouteTableAnnouncement(const CreateTransitGatewayRouteTableAnnouncementRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayRouteTableAnnouncementOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayRouteTableAnnouncementOutcomeCallable EC2Client::CreateTransitGatewayRouteTableAnnouncementCallable(const CreateTransitGatewayRouteTableAnnouncementRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayRouteTableAnnouncementOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayRouteTableAnnouncement(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayRouteTableAnnouncementAsync(const CreateTransitGatewayRouteTableAnnouncementRequest& request, const CreateTransitGatewayRouteTableAnnouncementResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayRouteTableAnnouncement(request), context);
    } );
}

CreateTransitGatewayVpcAttachmentOutcome EC2Client::CreateTransitGatewayVpcAttachment(const CreateTransitGatewayVpcAttachmentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateTransitGatewayVpcAttachmentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateTransitGatewayVpcAttachmentOutcomeCallable EC2Client::CreateTransitGatewayVpcAttachmentCallable(const CreateTransitGatewayVpcAttachmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateTransitGatewayVpcAttachmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateTransitGatewayVpcAttachment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateTransitGatewayVpcAttachmentAsync(const CreateTransitGatewayVpcAttachmentRequest& request, const CreateTransitGatewayVpcAttachmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateTransitGatewayVpcAttachment(request), context);
    } );
}

CreateVolumeOutcome EC2Client::CreateVolume(const CreateVolumeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateVolumeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateVolumeOutcomeCallable EC2Client::CreateVolumeCallable(const CreateVolumeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateVolumeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateVolume(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateVolumeAsync(const CreateVolumeRequest& request, const CreateVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateVolume(request), context);
    } );
}

CreateVpcOutcome EC2Client::CreateVpc(const CreateVpcRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateVpcOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateVpcOutcomeCallable EC2Client::CreateVpcCallable(const CreateVpcRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateVpcOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateVpc(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateVpcAsync(const CreateVpcRequest& request, const CreateVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateVpc(request), context);
    } );
}

CreateVpcEndpointOutcome EC2Client::CreateVpcEndpoint(const CreateVpcEndpointRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateVpcEndpointOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateVpcEndpointOutcomeCallable EC2Client::CreateVpcEndpointCallable(const CreateVpcEndpointRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateVpcEndpointOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateVpcEndpoint(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateVpcEndpointAsync(const CreateVpcEndpointRequest& request, const CreateVpcEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateVpcEndpoint(request), context);
    } );
}

CreateVpcEndpointConnectionNotificationOutcome EC2Client::CreateVpcEndpointConnectionNotification(const CreateVpcEndpointConnectionNotificationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateVpcEndpointConnectionNotificationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateVpcEndpointConnectionNotificationOutcomeCallable EC2Client::CreateVpcEndpointConnectionNotificationCallable(const CreateVpcEndpointConnectionNotificationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateVpcEndpointConnectionNotificationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateVpcEndpointConnectionNotification(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateVpcEndpointConnectionNotificationAsync(const CreateVpcEndpointConnectionNotificationRequest& request, const CreateVpcEndpointConnectionNotificationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateVpcEndpointConnectionNotification(request), context);
    } );
}

CreateVpcEndpointServiceConfigurationOutcome EC2Client::CreateVpcEndpointServiceConfiguration(const CreateVpcEndpointServiceConfigurationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateVpcEndpointServiceConfigurationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateVpcEndpointServiceConfigurationOutcomeCallable EC2Client::CreateVpcEndpointServiceConfigurationCallable(const CreateVpcEndpointServiceConfigurationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateVpcEndpointServiceConfigurationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateVpcEndpointServiceConfiguration(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateVpcEndpointServiceConfigurationAsync(const CreateVpcEndpointServiceConfigurationRequest& request, const CreateVpcEndpointServiceConfigurationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateVpcEndpointServiceConfiguration(request), context);
    } );
}

CreateVpcPeeringConnectionOutcome EC2Client::CreateVpcPeeringConnection(const CreateVpcPeeringConnectionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateVpcPeeringConnectionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateVpcPeeringConnectionOutcomeCallable EC2Client::CreateVpcPeeringConnectionCallable(const CreateVpcPeeringConnectionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateVpcPeeringConnectionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateVpcPeeringConnection(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateVpcPeeringConnectionAsync(const CreateVpcPeeringConnectionRequest& request, const CreateVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateVpcPeeringConnection(request), context);
    } );
}

CreateVpnConnectionOutcome EC2Client::CreateVpnConnection(const CreateVpnConnectionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateVpnConnectionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateVpnConnectionOutcomeCallable EC2Client::CreateVpnConnectionCallable(const CreateVpnConnectionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateVpnConnectionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateVpnConnection(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateVpnConnectionAsync(const CreateVpnConnectionRequest& request, const CreateVpnConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateVpnConnection(request), context);
    } );
}

CreateVpnConnectionRouteOutcome EC2Client::CreateVpnConnectionRoute(const CreateVpnConnectionRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateVpnConnectionRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateVpnConnectionRouteOutcomeCallable EC2Client::CreateVpnConnectionRouteCallable(const CreateVpnConnectionRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateVpnConnectionRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateVpnConnectionRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateVpnConnectionRouteAsync(const CreateVpnConnectionRouteRequest& request, const CreateVpnConnectionRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateVpnConnectionRoute(request), context);
    } );
}

CreateVpnGatewayOutcome EC2Client::CreateVpnGateway(const CreateVpnGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return CreateVpnGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

CreateVpnGatewayOutcomeCallable EC2Client::CreateVpnGatewayCallable(const CreateVpnGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< CreateVpnGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->CreateVpnGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::CreateVpnGatewayAsync(const CreateVpnGatewayRequest& request, const CreateVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, CreateVpnGateway(request), context);
    } );
}

DeleteCarrierGatewayOutcome EC2Client::DeleteCarrierGateway(const DeleteCarrierGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteCarrierGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteCarrierGatewayOutcomeCallable EC2Client::DeleteCarrierGatewayCallable(const DeleteCarrierGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteCarrierGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteCarrierGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteCarrierGatewayAsync(const DeleteCarrierGatewayRequest& request, const DeleteCarrierGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteCarrierGateway(request), context);
    } );
}

DeleteClientVpnEndpointOutcome EC2Client::DeleteClientVpnEndpoint(const DeleteClientVpnEndpointRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteClientVpnEndpointOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteClientVpnEndpointOutcomeCallable EC2Client::DeleteClientVpnEndpointCallable(const DeleteClientVpnEndpointRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteClientVpnEndpointOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteClientVpnEndpoint(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteClientVpnEndpointAsync(const DeleteClientVpnEndpointRequest& request, const DeleteClientVpnEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteClientVpnEndpoint(request), context);
    } );
}

DeleteClientVpnRouteOutcome EC2Client::DeleteClientVpnRoute(const DeleteClientVpnRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteClientVpnRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteClientVpnRouteOutcomeCallable EC2Client::DeleteClientVpnRouteCallable(const DeleteClientVpnRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteClientVpnRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteClientVpnRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteClientVpnRouteAsync(const DeleteClientVpnRouteRequest& request, const DeleteClientVpnRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteClientVpnRoute(request), context);
    } );
}

DeleteCoipCidrOutcome EC2Client::DeleteCoipCidr(const DeleteCoipCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteCoipCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteCoipCidrOutcomeCallable EC2Client::DeleteCoipCidrCallable(const DeleteCoipCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteCoipCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteCoipCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteCoipCidrAsync(const DeleteCoipCidrRequest& request, const DeleteCoipCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteCoipCidr(request), context);
    } );
}

DeleteCoipPoolOutcome EC2Client::DeleteCoipPool(const DeleteCoipPoolRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteCoipPoolOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteCoipPoolOutcomeCallable EC2Client::DeleteCoipPoolCallable(const DeleteCoipPoolRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteCoipPoolOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteCoipPool(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteCoipPoolAsync(const DeleteCoipPoolRequest& request, const DeleteCoipPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteCoipPool(request), context);
    } );
}

DeleteCustomerGatewayOutcome EC2Client::DeleteCustomerGateway(const DeleteCustomerGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteCustomerGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteCustomerGatewayOutcomeCallable EC2Client::DeleteCustomerGatewayCallable(const DeleteCustomerGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteCustomerGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteCustomerGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteCustomerGatewayAsync(const DeleteCustomerGatewayRequest& request, const DeleteCustomerGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteCustomerGateway(request), context);
    } );
}

DeleteDhcpOptionsOutcome EC2Client::DeleteDhcpOptions(const DeleteDhcpOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteDhcpOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteDhcpOptionsOutcomeCallable EC2Client::DeleteDhcpOptionsCallable(const DeleteDhcpOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteDhcpOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteDhcpOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteDhcpOptionsAsync(const DeleteDhcpOptionsRequest& request, const DeleteDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteDhcpOptions(request), context);
    } );
}

DeleteEgressOnlyInternetGatewayOutcome EC2Client::DeleteEgressOnlyInternetGateway(const DeleteEgressOnlyInternetGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteEgressOnlyInternetGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteEgressOnlyInternetGatewayOutcomeCallable EC2Client::DeleteEgressOnlyInternetGatewayCallable(const DeleteEgressOnlyInternetGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteEgressOnlyInternetGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteEgressOnlyInternetGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteEgressOnlyInternetGatewayAsync(const DeleteEgressOnlyInternetGatewayRequest& request, const DeleteEgressOnlyInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteEgressOnlyInternetGateway(request), context);
    } );
}

DeleteFleetsOutcome EC2Client::DeleteFleets(const DeleteFleetsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteFleetsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteFleetsOutcomeCallable EC2Client::DeleteFleetsCallable(const DeleteFleetsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteFleetsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteFleets(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteFleetsAsync(const DeleteFleetsRequest& request, const DeleteFleetsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteFleets(request), context);
    } );
}

DeleteFlowLogsOutcome EC2Client::DeleteFlowLogs(const DeleteFlowLogsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteFlowLogsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteFlowLogsOutcomeCallable EC2Client::DeleteFlowLogsCallable(const DeleteFlowLogsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteFlowLogsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteFlowLogs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteFlowLogsAsync(const DeleteFlowLogsRequest& request, const DeleteFlowLogsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteFlowLogs(request), context);
    } );
}

DeleteFpgaImageOutcome EC2Client::DeleteFpgaImage(const DeleteFpgaImageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteFpgaImageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteFpgaImageOutcomeCallable EC2Client::DeleteFpgaImageCallable(const DeleteFpgaImageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteFpgaImageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteFpgaImage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteFpgaImageAsync(const DeleteFpgaImageRequest& request, const DeleteFpgaImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteFpgaImage(request), context);
    } );
}

DeleteInstanceEventWindowOutcome EC2Client::DeleteInstanceEventWindow(const DeleteInstanceEventWindowRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteInstanceEventWindowOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteInstanceEventWindowOutcomeCallable EC2Client::DeleteInstanceEventWindowCallable(const DeleteInstanceEventWindowRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteInstanceEventWindowOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteInstanceEventWindow(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteInstanceEventWindowAsync(const DeleteInstanceEventWindowRequest& request, const DeleteInstanceEventWindowResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteInstanceEventWindow(request), context);
    } );
}

DeleteInternetGatewayOutcome EC2Client::DeleteInternetGateway(const DeleteInternetGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteInternetGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteInternetGatewayOutcomeCallable EC2Client::DeleteInternetGatewayCallable(const DeleteInternetGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteInternetGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteInternetGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteInternetGatewayAsync(const DeleteInternetGatewayRequest& request, const DeleteInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteInternetGateway(request), context);
    } );
}

DeleteIpamOutcome EC2Client::DeleteIpam(const DeleteIpamRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteIpamOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteIpamOutcomeCallable EC2Client::DeleteIpamCallable(const DeleteIpamRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteIpamOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteIpam(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteIpamAsync(const DeleteIpamRequest& request, const DeleteIpamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteIpam(request), context);
    } );
}

DeleteIpamPoolOutcome EC2Client::DeleteIpamPool(const DeleteIpamPoolRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteIpamPoolOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteIpamPoolOutcomeCallable EC2Client::DeleteIpamPoolCallable(const DeleteIpamPoolRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteIpamPoolOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteIpamPool(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteIpamPoolAsync(const DeleteIpamPoolRequest& request, const DeleteIpamPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteIpamPool(request), context);
    } );
}

DeleteIpamScopeOutcome EC2Client::DeleteIpamScope(const DeleteIpamScopeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteIpamScopeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteIpamScopeOutcomeCallable EC2Client::DeleteIpamScopeCallable(const DeleteIpamScopeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteIpamScopeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteIpamScope(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteIpamScopeAsync(const DeleteIpamScopeRequest& request, const DeleteIpamScopeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteIpamScope(request), context);
    } );
}

DeleteKeyPairOutcome EC2Client::DeleteKeyPair(const DeleteKeyPairRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteKeyPairOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteKeyPairOutcomeCallable EC2Client::DeleteKeyPairCallable(const DeleteKeyPairRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteKeyPairOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteKeyPair(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteKeyPairAsync(const DeleteKeyPairRequest& request, const DeleteKeyPairResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteKeyPair(request), context);
    } );
}

DeleteLaunchTemplateOutcome EC2Client::DeleteLaunchTemplate(const DeleteLaunchTemplateRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteLaunchTemplateOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteLaunchTemplateOutcomeCallable EC2Client::DeleteLaunchTemplateCallable(const DeleteLaunchTemplateRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteLaunchTemplateOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteLaunchTemplate(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteLaunchTemplateAsync(const DeleteLaunchTemplateRequest& request, const DeleteLaunchTemplateResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteLaunchTemplate(request), context);
    } );
}

DeleteLaunchTemplateVersionsOutcome EC2Client::DeleteLaunchTemplateVersions(const DeleteLaunchTemplateVersionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteLaunchTemplateVersionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteLaunchTemplateVersionsOutcomeCallable EC2Client::DeleteLaunchTemplateVersionsCallable(const DeleteLaunchTemplateVersionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteLaunchTemplateVersionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteLaunchTemplateVersions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteLaunchTemplateVersionsAsync(const DeleteLaunchTemplateVersionsRequest& request, const DeleteLaunchTemplateVersionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteLaunchTemplateVersions(request), context);
    } );
}

DeleteLocalGatewayRouteOutcome EC2Client::DeleteLocalGatewayRoute(const DeleteLocalGatewayRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteLocalGatewayRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteLocalGatewayRouteOutcomeCallable EC2Client::DeleteLocalGatewayRouteCallable(const DeleteLocalGatewayRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteLocalGatewayRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteLocalGatewayRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteLocalGatewayRouteAsync(const DeleteLocalGatewayRouteRequest& request, const DeleteLocalGatewayRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteLocalGatewayRoute(request), context);
    } );
}

DeleteLocalGatewayRouteTableOutcome EC2Client::DeleteLocalGatewayRouteTable(const DeleteLocalGatewayRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteLocalGatewayRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteLocalGatewayRouteTableOutcomeCallable EC2Client::DeleteLocalGatewayRouteTableCallable(const DeleteLocalGatewayRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteLocalGatewayRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteLocalGatewayRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteLocalGatewayRouteTableAsync(const DeleteLocalGatewayRouteTableRequest& request, const DeleteLocalGatewayRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteLocalGatewayRouteTable(request), context);
    } );
}

DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationOutcome EC2Client::DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociation(const DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationOutcomeCallable EC2Client::DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationCallable(const DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationAsync(const DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationRequest& request, const DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteLocalGatewayRouteTableVirtualInterfaceGroupAssociation(request), context);
    } );
}

DeleteLocalGatewayRouteTableVpcAssociationOutcome EC2Client::DeleteLocalGatewayRouteTableVpcAssociation(const DeleteLocalGatewayRouteTableVpcAssociationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteLocalGatewayRouteTableVpcAssociationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteLocalGatewayRouteTableVpcAssociationOutcomeCallable EC2Client::DeleteLocalGatewayRouteTableVpcAssociationCallable(const DeleteLocalGatewayRouteTableVpcAssociationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteLocalGatewayRouteTableVpcAssociationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteLocalGatewayRouteTableVpcAssociation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteLocalGatewayRouteTableVpcAssociationAsync(const DeleteLocalGatewayRouteTableVpcAssociationRequest& request, const DeleteLocalGatewayRouteTableVpcAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteLocalGatewayRouteTableVpcAssociation(request), context);
    } );
}

DeleteManagedPrefixListOutcome EC2Client::DeleteManagedPrefixList(const DeleteManagedPrefixListRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteManagedPrefixListOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteManagedPrefixListOutcomeCallable EC2Client::DeleteManagedPrefixListCallable(const DeleteManagedPrefixListRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteManagedPrefixListOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteManagedPrefixList(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteManagedPrefixListAsync(const DeleteManagedPrefixListRequest& request, const DeleteManagedPrefixListResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteManagedPrefixList(request), context);
    } );
}

DeleteNatGatewayOutcome EC2Client::DeleteNatGateway(const DeleteNatGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteNatGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteNatGatewayOutcomeCallable EC2Client::DeleteNatGatewayCallable(const DeleteNatGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteNatGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteNatGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteNatGatewayAsync(const DeleteNatGatewayRequest& request, const DeleteNatGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteNatGateway(request), context);
    } );
}

DeleteNetworkAclOutcome EC2Client::DeleteNetworkAcl(const DeleteNetworkAclRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteNetworkAclOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteNetworkAclOutcomeCallable EC2Client::DeleteNetworkAclCallable(const DeleteNetworkAclRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteNetworkAclOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteNetworkAcl(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteNetworkAclAsync(const DeleteNetworkAclRequest& request, const DeleteNetworkAclResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteNetworkAcl(request), context);
    } );
}

DeleteNetworkAclEntryOutcome EC2Client::DeleteNetworkAclEntry(const DeleteNetworkAclEntryRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteNetworkAclEntryOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteNetworkAclEntryOutcomeCallable EC2Client::DeleteNetworkAclEntryCallable(const DeleteNetworkAclEntryRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteNetworkAclEntryOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteNetworkAclEntry(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteNetworkAclEntryAsync(const DeleteNetworkAclEntryRequest& request, const DeleteNetworkAclEntryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteNetworkAclEntry(request), context);
    } );
}

DeleteNetworkInsightsAccessScopeOutcome EC2Client::DeleteNetworkInsightsAccessScope(const DeleteNetworkInsightsAccessScopeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteNetworkInsightsAccessScopeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteNetworkInsightsAccessScopeOutcomeCallable EC2Client::DeleteNetworkInsightsAccessScopeCallable(const DeleteNetworkInsightsAccessScopeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteNetworkInsightsAccessScopeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteNetworkInsightsAccessScope(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteNetworkInsightsAccessScopeAsync(const DeleteNetworkInsightsAccessScopeRequest& request, const DeleteNetworkInsightsAccessScopeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteNetworkInsightsAccessScope(request), context);
    } );
}

DeleteNetworkInsightsAccessScopeAnalysisOutcome EC2Client::DeleteNetworkInsightsAccessScopeAnalysis(const DeleteNetworkInsightsAccessScopeAnalysisRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteNetworkInsightsAccessScopeAnalysisOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteNetworkInsightsAccessScopeAnalysisOutcomeCallable EC2Client::DeleteNetworkInsightsAccessScopeAnalysisCallable(const DeleteNetworkInsightsAccessScopeAnalysisRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteNetworkInsightsAccessScopeAnalysisOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteNetworkInsightsAccessScopeAnalysis(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteNetworkInsightsAccessScopeAnalysisAsync(const DeleteNetworkInsightsAccessScopeAnalysisRequest& request, const DeleteNetworkInsightsAccessScopeAnalysisResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteNetworkInsightsAccessScopeAnalysis(request), context);
    } );
}

DeleteNetworkInsightsAnalysisOutcome EC2Client::DeleteNetworkInsightsAnalysis(const DeleteNetworkInsightsAnalysisRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteNetworkInsightsAnalysisOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteNetworkInsightsAnalysisOutcomeCallable EC2Client::DeleteNetworkInsightsAnalysisCallable(const DeleteNetworkInsightsAnalysisRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteNetworkInsightsAnalysisOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteNetworkInsightsAnalysis(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteNetworkInsightsAnalysisAsync(const DeleteNetworkInsightsAnalysisRequest& request, const DeleteNetworkInsightsAnalysisResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteNetworkInsightsAnalysis(request), context);
    } );
}

DeleteNetworkInsightsPathOutcome EC2Client::DeleteNetworkInsightsPath(const DeleteNetworkInsightsPathRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteNetworkInsightsPathOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteNetworkInsightsPathOutcomeCallable EC2Client::DeleteNetworkInsightsPathCallable(const DeleteNetworkInsightsPathRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteNetworkInsightsPathOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteNetworkInsightsPath(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteNetworkInsightsPathAsync(const DeleteNetworkInsightsPathRequest& request, const DeleteNetworkInsightsPathResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteNetworkInsightsPath(request), context);
    } );
}

DeleteNetworkInterfaceOutcome EC2Client::DeleteNetworkInterface(const DeleteNetworkInterfaceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteNetworkInterfaceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteNetworkInterfaceOutcomeCallable EC2Client::DeleteNetworkInterfaceCallable(const DeleteNetworkInterfaceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteNetworkInterfaceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteNetworkInterface(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteNetworkInterfaceAsync(const DeleteNetworkInterfaceRequest& request, const DeleteNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteNetworkInterface(request), context);
    } );
}

DeleteNetworkInterfacePermissionOutcome EC2Client::DeleteNetworkInterfacePermission(const DeleteNetworkInterfacePermissionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteNetworkInterfacePermissionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteNetworkInterfacePermissionOutcomeCallable EC2Client::DeleteNetworkInterfacePermissionCallable(const DeleteNetworkInterfacePermissionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteNetworkInterfacePermissionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteNetworkInterfacePermission(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteNetworkInterfacePermissionAsync(const DeleteNetworkInterfacePermissionRequest& request, const DeleteNetworkInterfacePermissionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteNetworkInterfacePermission(request), context);
    } );
}

DeletePlacementGroupOutcome EC2Client::DeletePlacementGroup(const DeletePlacementGroupRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeletePlacementGroupOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeletePlacementGroupOutcomeCallable EC2Client::DeletePlacementGroupCallable(const DeletePlacementGroupRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeletePlacementGroupOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeletePlacementGroup(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeletePlacementGroupAsync(const DeletePlacementGroupRequest& request, const DeletePlacementGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeletePlacementGroup(request), context);
    } );
}

DeletePublicIpv4PoolOutcome EC2Client::DeletePublicIpv4Pool(const DeletePublicIpv4PoolRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeletePublicIpv4PoolOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeletePublicIpv4PoolOutcomeCallable EC2Client::DeletePublicIpv4PoolCallable(const DeletePublicIpv4PoolRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeletePublicIpv4PoolOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeletePublicIpv4Pool(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeletePublicIpv4PoolAsync(const DeletePublicIpv4PoolRequest& request, const DeletePublicIpv4PoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeletePublicIpv4Pool(request), context);
    } );
}

DeleteQueuedReservedInstancesOutcome EC2Client::DeleteQueuedReservedInstances(const DeleteQueuedReservedInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteQueuedReservedInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteQueuedReservedInstancesOutcomeCallable EC2Client::DeleteQueuedReservedInstancesCallable(const DeleteQueuedReservedInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteQueuedReservedInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteQueuedReservedInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteQueuedReservedInstancesAsync(const DeleteQueuedReservedInstancesRequest& request, const DeleteQueuedReservedInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteQueuedReservedInstances(request), context);
    } );
}

DeleteRouteOutcome EC2Client::DeleteRoute(const DeleteRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteRouteOutcomeCallable EC2Client::DeleteRouteCallable(const DeleteRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteRouteAsync(const DeleteRouteRequest& request, const DeleteRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteRoute(request), context);
    } );
}

DeleteRouteTableOutcome EC2Client::DeleteRouteTable(const DeleteRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteRouteTableOutcomeCallable EC2Client::DeleteRouteTableCallable(const DeleteRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteRouteTableAsync(const DeleteRouteTableRequest& request, const DeleteRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteRouteTable(request), context);
    } );
}

DeleteSecurityGroupOutcome EC2Client::DeleteSecurityGroup(const DeleteSecurityGroupRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteSecurityGroupOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteSecurityGroupOutcomeCallable EC2Client::DeleteSecurityGroupCallable(const DeleteSecurityGroupRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteSecurityGroupOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteSecurityGroup(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteSecurityGroupAsync(const DeleteSecurityGroupRequest& request, const DeleteSecurityGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteSecurityGroup(request), context);
    } );
}

DeleteSnapshotOutcome EC2Client::DeleteSnapshot(const DeleteSnapshotRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteSnapshotOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteSnapshotOutcomeCallable EC2Client::DeleteSnapshotCallable(const DeleteSnapshotRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteSnapshotOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteSnapshot(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteSnapshotAsync(const DeleteSnapshotRequest& request, const DeleteSnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteSnapshot(request), context);
    } );
}

DeleteSpotDatafeedSubscriptionOutcome EC2Client::DeleteSpotDatafeedSubscription(const DeleteSpotDatafeedSubscriptionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteSpotDatafeedSubscriptionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteSpotDatafeedSubscriptionOutcomeCallable EC2Client::DeleteSpotDatafeedSubscriptionCallable(const DeleteSpotDatafeedSubscriptionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteSpotDatafeedSubscriptionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteSpotDatafeedSubscription(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteSpotDatafeedSubscriptionAsync(const DeleteSpotDatafeedSubscriptionRequest& request, const DeleteSpotDatafeedSubscriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteSpotDatafeedSubscription(request), context);
    } );
}

DeleteSubnetOutcome EC2Client::DeleteSubnet(const DeleteSubnetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteSubnetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteSubnetOutcomeCallable EC2Client::DeleteSubnetCallable(const DeleteSubnetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteSubnetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteSubnet(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteSubnetAsync(const DeleteSubnetRequest& request, const DeleteSubnetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteSubnet(request), context);
    } );
}

DeleteSubnetCidrReservationOutcome EC2Client::DeleteSubnetCidrReservation(const DeleteSubnetCidrReservationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteSubnetCidrReservationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteSubnetCidrReservationOutcomeCallable EC2Client::DeleteSubnetCidrReservationCallable(const DeleteSubnetCidrReservationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteSubnetCidrReservationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteSubnetCidrReservation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteSubnetCidrReservationAsync(const DeleteSubnetCidrReservationRequest& request, const DeleteSubnetCidrReservationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteSubnetCidrReservation(request), context);
    } );
}

DeleteTagsOutcome EC2Client::DeleteTags(const DeleteTagsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTagsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTagsOutcomeCallable EC2Client::DeleteTagsCallable(const DeleteTagsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTagsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTags(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTagsAsync(const DeleteTagsRequest& request, const DeleteTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTags(request), context);
    } );
}

DeleteTrafficMirrorFilterOutcome EC2Client::DeleteTrafficMirrorFilter(const DeleteTrafficMirrorFilterRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTrafficMirrorFilterOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTrafficMirrorFilterOutcomeCallable EC2Client::DeleteTrafficMirrorFilterCallable(const DeleteTrafficMirrorFilterRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTrafficMirrorFilterOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTrafficMirrorFilter(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTrafficMirrorFilterAsync(const DeleteTrafficMirrorFilterRequest& request, const DeleteTrafficMirrorFilterResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTrafficMirrorFilter(request), context);
    } );
}

DeleteTrafficMirrorFilterRuleOutcome EC2Client::DeleteTrafficMirrorFilterRule(const DeleteTrafficMirrorFilterRuleRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTrafficMirrorFilterRuleOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTrafficMirrorFilterRuleOutcomeCallable EC2Client::DeleteTrafficMirrorFilterRuleCallable(const DeleteTrafficMirrorFilterRuleRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTrafficMirrorFilterRuleOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTrafficMirrorFilterRule(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTrafficMirrorFilterRuleAsync(const DeleteTrafficMirrorFilterRuleRequest& request, const DeleteTrafficMirrorFilterRuleResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTrafficMirrorFilterRule(request), context);
    } );
}

DeleteTrafficMirrorSessionOutcome EC2Client::DeleteTrafficMirrorSession(const DeleteTrafficMirrorSessionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTrafficMirrorSessionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTrafficMirrorSessionOutcomeCallable EC2Client::DeleteTrafficMirrorSessionCallable(const DeleteTrafficMirrorSessionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTrafficMirrorSessionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTrafficMirrorSession(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTrafficMirrorSessionAsync(const DeleteTrafficMirrorSessionRequest& request, const DeleteTrafficMirrorSessionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTrafficMirrorSession(request), context);
    } );
}

DeleteTrafficMirrorTargetOutcome EC2Client::DeleteTrafficMirrorTarget(const DeleteTrafficMirrorTargetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTrafficMirrorTargetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTrafficMirrorTargetOutcomeCallable EC2Client::DeleteTrafficMirrorTargetCallable(const DeleteTrafficMirrorTargetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTrafficMirrorTargetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTrafficMirrorTarget(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTrafficMirrorTargetAsync(const DeleteTrafficMirrorTargetRequest& request, const DeleteTrafficMirrorTargetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTrafficMirrorTarget(request), context);
    } );
}

DeleteTransitGatewayOutcome EC2Client::DeleteTransitGateway(const DeleteTransitGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayOutcomeCallable EC2Client::DeleteTransitGatewayCallable(const DeleteTransitGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayAsync(const DeleteTransitGatewayRequest& request, const DeleteTransitGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGateway(request), context);
    } );
}

DeleteTransitGatewayConnectOutcome EC2Client::DeleteTransitGatewayConnect(const DeleteTransitGatewayConnectRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayConnectOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayConnectOutcomeCallable EC2Client::DeleteTransitGatewayConnectCallable(const DeleteTransitGatewayConnectRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayConnectOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayConnect(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayConnectAsync(const DeleteTransitGatewayConnectRequest& request, const DeleteTransitGatewayConnectResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayConnect(request), context);
    } );
}

DeleteTransitGatewayConnectPeerOutcome EC2Client::DeleteTransitGatewayConnectPeer(const DeleteTransitGatewayConnectPeerRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayConnectPeerOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayConnectPeerOutcomeCallable EC2Client::DeleteTransitGatewayConnectPeerCallable(const DeleteTransitGatewayConnectPeerRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayConnectPeerOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayConnectPeer(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayConnectPeerAsync(const DeleteTransitGatewayConnectPeerRequest& request, const DeleteTransitGatewayConnectPeerResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayConnectPeer(request), context);
    } );
}

DeleteTransitGatewayMulticastDomainOutcome EC2Client::DeleteTransitGatewayMulticastDomain(const DeleteTransitGatewayMulticastDomainRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayMulticastDomainOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayMulticastDomainOutcomeCallable EC2Client::DeleteTransitGatewayMulticastDomainCallable(const DeleteTransitGatewayMulticastDomainRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayMulticastDomainOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayMulticastDomain(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayMulticastDomainAsync(const DeleteTransitGatewayMulticastDomainRequest& request, const DeleteTransitGatewayMulticastDomainResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayMulticastDomain(request), context);
    } );
}

DeleteTransitGatewayPeeringAttachmentOutcome EC2Client::DeleteTransitGatewayPeeringAttachment(const DeleteTransitGatewayPeeringAttachmentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayPeeringAttachmentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayPeeringAttachmentOutcomeCallable EC2Client::DeleteTransitGatewayPeeringAttachmentCallable(const DeleteTransitGatewayPeeringAttachmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayPeeringAttachmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayPeeringAttachment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayPeeringAttachmentAsync(const DeleteTransitGatewayPeeringAttachmentRequest& request, const DeleteTransitGatewayPeeringAttachmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayPeeringAttachment(request), context);
    } );
}

DeleteTransitGatewayPolicyTableOutcome EC2Client::DeleteTransitGatewayPolicyTable(const DeleteTransitGatewayPolicyTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayPolicyTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayPolicyTableOutcomeCallable EC2Client::DeleteTransitGatewayPolicyTableCallable(const DeleteTransitGatewayPolicyTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayPolicyTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayPolicyTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayPolicyTableAsync(const DeleteTransitGatewayPolicyTableRequest& request, const DeleteTransitGatewayPolicyTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayPolicyTable(request), context);
    } );
}

DeleteTransitGatewayPrefixListReferenceOutcome EC2Client::DeleteTransitGatewayPrefixListReference(const DeleteTransitGatewayPrefixListReferenceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayPrefixListReferenceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayPrefixListReferenceOutcomeCallable EC2Client::DeleteTransitGatewayPrefixListReferenceCallable(const DeleteTransitGatewayPrefixListReferenceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayPrefixListReferenceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayPrefixListReference(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayPrefixListReferenceAsync(const DeleteTransitGatewayPrefixListReferenceRequest& request, const DeleteTransitGatewayPrefixListReferenceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayPrefixListReference(request), context);
    } );
}

DeleteTransitGatewayRouteOutcome EC2Client::DeleteTransitGatewayRoute(const DeleteTransitGatewayRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayRouteOutcomeCallable EC2Client::DeleteTransitGatewayRouteCallable(const DeleteTransitGatewayRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayRouteAsync(const DeleteTransitGatewayRouteRequest& request, const DeleteTransitGatewayRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayRoute(request), context);
    } );
}

DeleteTransitGatewayRouteTableOutcome EC2Client::DeleteTransitGatewayRouteTable(const DeleteTransitGatewayRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayRouteTableOutcomeCallable EC2Client::DeleteTransitGatewayRouteTableCallable(const DeleteTransitGatewayRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayRouteTableAsync(const DeleteTransitGatewayRouteTableRequest& request, const DeleteTransitGatewayRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayRouteTable(request), context);
    } );
}

DeleteTransitGatewayRouteTableAnnouncementOutcome EC2Client::DeleteTransitGatewayRouteTableAnnouncement(const DeleteTransitGatewayRouteTableAnnouncementRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayRouteTableAnnouncementOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayRouteTableAnnouncementOutcomeCallable EC2Client::DeleteTransitGatewayRouteTableAnnouncementCallable(const DeleteTransitGatewayRouteTableAnnouncementRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayRouteTableAnnouncementOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayRouteTableAnnouncement(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayRouteTableAnnouncementAsync(const DeleteTransitGatewayRouteTableAnnouncementRequest& request, const DeleteTransitGatewayRouteTableAnnouncementResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayRouteTableAnnouncement(request), context);
    } );
}

DeleteTransitGatewayVpcAttachmentOutcome EC2Client::DeleteTransitGatewayVpcAttachment(const DeleteTransitGatewayVpcAttachmentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteTransitGatewayVpcAttachmentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteTransitGatewayVpcAttachmentOutcomeCallable EC2Client::DeleteTransitGatewayVpcAttachmentCallable(const DeleteTransitGatewayVpcAttachmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteTransitGatewayVpcAttachmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteTransitGatewayVpcAttachment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteTransitGatewayVpcAttachmentAsync(const DeleteTransitGatewayVpcAttachmentRequest& request, const DeleteTransitGatewayVpcAttachmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteTransitGatewayVpcAttachment(request), context);
    } );
}

DeleteVolumeOutcome EC2Client::DeleteVolume(const DeleteVolumeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteVolumeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteVolumeOutcomeCallable EC2Client::DeleteVolumeCallable(const DeleteVolumeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteVolumeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteVolume(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteVolumeAsync(const DeleteVolumeRequest& request, const DeleteVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteVolume(request), context);
    } );
}

DeleteVpcOutcome EC2Client::DeleteVpc(const DeleteVpcRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteVpcOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteVpcOutcomeCallable EC2Client::DeleteVpcCallable(const DeleteVpcRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteVpcOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteVpc(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteVpcAsync(const DeleteVpcRequest& request, const DeleteVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteVpc(request), context);
    } );
}

DeleteVpcEndpointConnectionNotificationsOutcome EC2Client::DeleteVpcEndpointConnectionNotifications(const DeleteVpcEndpointConnectionNotificationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteVpcEndpointConnectionNotificationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteVpcEndpointConnectionNotificationsOutcomeCallable EC2Client::DeleteVpcEndpointConnectionNotificationsCallable(const DeleteVpcEndpointConnectionNotificationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteVpcEndpointConnectionNotificationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteVpcEndpointConnectionNotifications(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteVpcEndpointConnectionNotificationsAsync(const DeleteVpcEndpointConnectionNotificationsRequest& request, const DeleteVpcEndpointConnectionNotificationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteVpcEndpointConnectionNotifications(request), context);
    } );
}

DeleteVpcEndpointServiceConfigurationsOutcome EC2Client::DeleteVpcEndpointServiceConfigurations(const DeleteVpcEndpointServiceConfigurationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteVpcEndpointServiceConfigurationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteVpcEndpointServiceConfigurationsOutcomeCallable EC2Client::DeleteVpcEndpointServiceConfigurationsCallable(const DeleteVpcEndpointServiceConfigurationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteVpcEndpointServiceConfigurationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteVpcEndpointServiceConfigurations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteVpcEndpointServiceConfigurationsAsync(const DeleteVpcEndpointServiceConfigurationsRequest& request, const DeleteVpcEndpointServiceConfigurationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteVpcEndpointServiceConfigurations(request), context);
    } );
}

DeleteVpcEndpointsOutcome EC2Client::DeleteVpcEndpoints(const DeleteVpcEndpointsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteVpcEndpointsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteVpcEndpointsOutcomeCallable EC2Client::DeleteVpcEndpointsCallable(const DeleteVpcEndpointsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteVpcEndpointsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteVpcEndpoints(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteVpcEndpointsAsync(const DeleteVpcEndpointsRequest& request, const DeleteVpcEndpointsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteVpcEndpoints(request), context);
    } );
}

DeleteVpcPeeringConnectionOutcome EC2Client::DeleteVpcPeeringConnection(const DeleteVpcPeeringConnectionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteVpcPeeringConnectionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteVpcPeeringConnectionOutcomeCallable EC2Client::DeleteVpcPeeringConnectionCallable(const DeleteVpcPeeringConnectionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteVpcPeeringConnectionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteVpcPeeringConnection(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteVpcPeeringConnectionAsync(const DeleteVpcPeeringConnectionRequest& request, const DeleteVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteVpcPeeringConnection(request), context);
    } );
}

DeleteVpnConnectionOutcome EC2Client::DeleteVpnConnection(const DeleteVpnConnectionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteVpnConnectionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteVpnConnectionOutcomeCallable EC2Client::DeleteVpnConnectionCallable(const DeleteVpnConnectionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteVpnConnectionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteVpnConnection(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteVpnConnectionAsync(const DeleteVpnConnectionRequest& request, const DeleteVpnConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteVpnConnection(request), context);
    } );
}

DeleteVpnConnectionRouteOutcome EC2Client::DeleteVpnConnectionRoute(const DeleteVpnConnectionRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteVpnConnectionRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteVpnConnectionRouteOutcomeCallable EC2Client::DeleteVpnConnectionRouteCallable(const DeleteVpnConnectionRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteVpnConnectionRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteVpnConnectionRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteVpnConnectionRouteAsync(const DeleteVpnConnectionRouteRequest& request, const DeleteVpnConnectionRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteVpnConnectionRoute(request), context);
    } );
}

DeleteVpnGatewayOutcome EC2Client::DeleteVpnGateway(const DeleteVpnGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeleteVpnGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeleteVpnGatewayOutcomeCallable EC2Client::DeleteVpnGatewayCallable(const DeleteVpnGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeleteVpnGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeleteVpnGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeleteVpnGatewayAsync(const DeleteVpnGatewayRequest& request, const DeleteVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeleteVpnGateway(request), context);
    } );
}

DeprovisionByoipCidrOutcome EC2Client::DeprovisionByoipCidr(const DeprovisionByoipCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeprovisionByoipCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeprovisionByoipCidrOutcomeCallable EC2Client::DeprovisionByoipCidrCallable(const DeprovisionByoipCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeprovisionByoipCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeprovisionByoipCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeprovisionByoipCidrAsync(const DeprovisionByoipCidrRequest& request, const DeprovisionByoipCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeprovisionByoipCidr(request), context);
    } );
}

DeprovisionIpamPoolCidrOutcome EC2Client::DeprovisionIpamPoolCidr(const DeprovisionIpamPoolCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeprovisionIpamPoolCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeprovisionIpamPoolCidrOutcomeCallable EC2Client::DeprovisionIpamPoolCidrCallable(const DeprovisionIpamPoolCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeprovisionIpamPoolCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeprovisionIpamPoolCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeprovisionIpamPoolCidrAsync(const DeprovisionIpamPoolCidrRequest& request, const DeprovisionIpamPoolCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeprovisionIpamPoolCidr(request), context);
    } );
}

DeprovisionPublicIpv4PoolCidrOutcome EC2Client::DeprovisionPublicIpv4PoolCidr(const DeprovisionPublicIpv4PoolCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeprovisionPublicIpv4PoolCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeprovisionPublicIpv4PoolCidrOutcomeCallable EC2Client::DeprovisionPublicIpv4PoolCidrCallable(const DeprovisionPublicIpv4PoolCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeprovisionPublicIpv4PoolCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeprovisionPublicIpv4PoolCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeprovisionPublicIpv4PoolCidrAsync(const DeprovisionPublicIpv4PoolCidrRequest& request, const DeprovisionPublicIpv4PoolCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeprovisionPublicIpv4PoolCidr(request), context);
    } );
}

DeregisterImageOutcome EC2Client::DeregisterImage(const DeregisterImageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeregisterImageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeregisterImageOutcomeCallable EC2Client::DeregisterImageCallable(const DeregisterImageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeregisterImageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeregisterImage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeregisterImageAsync(const DeregisterImageRequest& request, const DeregisterImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeregisterImage(request), context);
    } );
}

DeregisterInstanceEventNotificationAttributesOutcome EC2Client::DeregisterInstanceEventNotificationAttributes(const DeregisterInstanceEventNotificationAttributesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeregisterInstanceEventNotificationAttributesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeregisterInstanceEventNotificationAttributesOutcomeCallable EC2Client::DeregisterInstanceEventNotificationAttributesCallable(const DeregisterInstanceEventNotificationAttributesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeregisterInstanceEventNotificationAttributesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeregisterInstanceEventNotificationAttributes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeregisterInstanceEventNotificationAttributesAsync(const DeregisterInstanceEventNotificationAttributesRequest& request, const DeregisterInstanceEventNotificationAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeregisterInstanceEventNotificationAttributes(request), context);
    } );
}

DeregisterTransitGatewayMulticastGroupMembersOutcome EC2Client::DeregisterTransitGatewayMulticastGroupMembers(const DeregisterTransitGatewayMulticastGroupMembersRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeregisterTransitGatewayMulticastGroupMembersOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeregisterTransitGatewayMulticastGroupMembersOutcomeCallable EC2Client::DeregisterTransitGatewayMulticastGroupMembersCallable(const DeregisterTransitGatewayMulticastGroupMembersRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeregisterTransitGatewayMulticastGroupMembersOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeregisterTransitGatewayMulticastGroupMembers(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeregisterTransitGatewayMulticastGroupMembersAsync(const DeregisterTransitGatewayMulticastGroupMembersRequest& request, const DeregisterTransitGatewayMulticastGroupMembersResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeregisterTransitGatewayMulticastGroupMembers(request), context);
    } );
}

DeregisterTransitGatewayMulticastGroupSourcesOutcome EC2Client::DeregisterTransitGatewayMulticastGroupSources(const DeregisterTransitGatewayMulticastGroupSourcesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DeregisterTransitGatewayMulticastGroupSourcesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DeregisterTransitGatewayMulticastGroupSourcesOutcomeCallable EC2Client::DeregisterTransitGatewayMulticastGroupSourcesCallable(const DeregisterTransitGatewayMulticastGroupSourcesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DeregisterTransitGatewayMulticastGroupSourcesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DeregisterTransitGatewayMulticastGroupSources(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DeregisterTransitGatewayMulticastGroupSourcesAsync(const DeregisterTransitGatewayMulticastGroupSourcesRequest& request, const DeregisterTransitGatewayMulticastGroupSourcesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DeregisterTransitGatewayMulticastGroupSources(request), context);
    } );
}

DescribeAccountAttributesOutcome EC2Client::DescribeAccountAttributes(const DescribeAccountAttributesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeAccountAttributesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeAccountAttributesOutcomeCallable EC2Client::DescribeAccountAttributesCallable(const DescribeAccountAttributesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeAccountAttributesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeAccountAttributes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeAccountAttributesAsync(const DescribeAccountAttributesRequest& request, const DescribeAccountAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeAccountAttributes(request), context);
    } );
}

DescribeAddressesOutcome EC2Client::DescribeAddresses(const DescribeAddressesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeAddressesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeAddressesOutcomeCallable EC2Client::DescribeAddressesCallable(const DescribeAddressesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeAddressesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeAddresses(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeAddressesAsync(const DescribeAddressesRequest& request, const DescribeAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeAddresses(request), context);
    } );
}

DescribeAddressesAttributeOutcome EC2Client::DescribeAddressesAttribute(const DescribeAddressesAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeAddressesAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeAddressesAttributeOutcomeCallable EC2Client::DescribeAddressesAttributeCallable(const DescribeAddressesAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeAddressesAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeAddressesAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeAddressesAttributeAsync(const DescribeAddressesAttributeRequest& request, const DescribeAddressesAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeAddressesAttribute(request), context);
    } );
}

DescribeAggregateIdFormatOutcome EC2Client::DescribeAggregateIdFormat(const DescribeAggregateIdFormatRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeAggregateIdFormatOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeAggregateIdFormatOutcomeCallable EC2Client::DescribeAggregateIdFormatCallable(const DescribeAggregateIdFormatRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeAggregateIdFormatOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeAggregateIdFormat(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeAggregateIdFormatAsync(const DescribeAggregateIdFormatRequest& request, const DescribeAggregateIdFormatResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeAggregateIdFormat(request), context);
    } );
}

DescribeAvailabilityZonesOutcome EC2Client::DescribeAvailabilityZones(const DescribeAvailabilityZonesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeAvailabilityZonesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeAvailabilityZonesOutcomeCallable EC2Client::DescribeAvailabilityZonesCallable(const DescribeAvailabilityZonesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeAvailabilityZonesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeAvailabilityZones(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeAvailabilityZonesAsync(const DescribeAvailabilityZonesRequest& request, const DescribeAvailabilityZonesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeAvailabilityZones(request), context);
    } );
}

DescribeBundleTasksOutcome EC2Client::DescribeBundleTasks(const DescribeBundleTasksRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeBundleTasksOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeBundleTasksOutcomeCallable EC2Client::DescribeBundleTasksCallable(const DescribeBundleTasksRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeBundleTasksOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeBundleTasks(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeBundleTasksAsync(const DescribeBundleTasksRequest& request, const DescribeBundleTasksResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeBundleTasks(request), context);
    } );
}

DescribeByoipCidrsOutcome EC2Client::DescribeByoipCidrs(const DescribeByoipCidrsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeByoipCidrsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeByoipCidrsOutcomeCallable EC2Client::DescribeByoipCidrsCallable(const DescribeByoipCidrsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeByoipCidrsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeByoipCidrs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeByoipCidrsAsync(const DescribeByoipCidrsRequest& request, const DescribeByoipCidrsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeByoipCidrs(request), context);
    } );
}

DescribeCapacityReservationFleetsOutcome EC2Client::DescribeCapacityReservationFleets(const DescribeCapacityReservationFleetsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeCapacityReservationFleetsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeCapacityReservationFleetsOutcomeCallable EC2Client::DescribeCapacityReservationFleetsCallable(const DescribeCapacityReservationFleetsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeCapacityReservationFleetsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeCapacityReservationFleets(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeCapacityReservationFleetsAsync(const DescribeCapacityReservationFleetsRequest& request, const DescribeCapacityReservationFleetsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeCapacityReservationFleets(request), context);
    } );
}

DescribeCapacityReservationsOutcome EC2Client::DescribeCapacityReservations(const DescribeCapacityReservationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeCapacityReservationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeCapacityReservationsOutcomeCallable EC2Client::DescribeCapacityReservationsCallable(const DescribeCapacityReservationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeCapacityReservationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeCapacityReservations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeCapacityReservationsAsync(const DescribeCapacityReservationsRequest& request, const DescribeCapacityReservationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeCapacityReservations(request), context);
    } );
}

DescribeCarrierGatewaysOutcome EC2Client::DescribeCarrierGateways(const DescribeCarrierGatewaysRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeCarrierGatewaysOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeCarrierGatewaysOutcomeCallable EC2Client::DescribeCarrierGatewaysCallable(const DescribeCarrierGatewaysRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeCarrierGatewaysOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeCarrierGateways(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeCarrierGatewaysAsync(const DescribeCarrierGatewaysRequest& request, const DescribeCarrierGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeCarrierGateways(request), context);
    } );
}

DescribeClassicLinkInstancesOutcome EC2Client::DescribeClassicLinkInstances(const DescribeClassicLinkInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeClassicLinkInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeClassicLinkInstancesOutcomeCallable EC2Client::DescribeClassicLinkInstancesCallable(const DescribeClassicLinkInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeClassicLinkInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeClassicLinkInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeClassicLinkInstancesAsync(const DescribeClassicLinkInstancesRequest& request, const DescribeClassicLinkInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeClassicLinkInstances(request), context);
    } );
}

DescribeClientVpnAuthorizationRulesOutcome EC2Client::DescribeClientVpnAuthorizationRules(const DescribeClientVpnAuthorizationRulesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeClientVpnAuthorizationRulesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeClientVpnAuthorizationRulesOutcomeCallable EC2Client::DescribeClientVpnAuthorizationRulesCallable(const DescribeClientVpnAuthorizationRulesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeClientVpnAuthorizationRulesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeClientVpnAuthorizationRules(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeClientVpnAuthorizationRulesAsync(const DescribeClientVpnAuthorizationRulesRequest& request, const DescribeClientVpnAuthorizationRulesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeClientVpnAuthorizationRules(request), context);
    } );
}

DescribeClientVpnConnectionsOutcome EC2Client::DescribeClientVpnConnections(const DescribeClientVpnConnectionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeClientVpnConnectionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeClientVpnConnectionsOutcomeCallable EC2Client::DescribeClientVpnConnectionsCallable(const DescribeClientVpnConnectionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeClientVpnConnectionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeClientVpnConnections(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeClientVpnConnectionsAsync(const DescribeClientVpnConnectionsRequest& request, const DescribeClientVpnConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeClientVpnConnections(request), context);
    } );
}

DescribeClientVpnEndpointsOutcome EC2Client::DescribeClientVpnEndpoints(const DescribeClientVpnEndpointsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeClientVpnEndpointsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeClientVpnEndpointsOutcomeCallable EC2Client::DescribeClientVpnEndpointsCallable(const DescribeClientVpnEndpointsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeClientVpnEndpointsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeClientVpnEndpoints(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeClientVpnEndpointsAsync(const DescribeClientVpnEndpointsRequest& request, const DescribeClientVpnEndpointsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeClientVpnEndpoints(request), context);
    } );
}

DescribeClientVpnRoutesOutcome EC2Client::DescribeClientVpnRoutes(const DescribeClientVpnRoutesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeClientVpnRoutesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeClientVpnRoutesOutcomeCallable EC2Client::DescribeClientVpnRoutesCallable(const DescribeClientVpnRoutesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeClientVpnRoutesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeClientVpnRoutes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeClientVpnRoutesAsync(const DescribeClientVpnRoutesRequest& request, const DescribeClientVpnRoutesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeClientVpnRoutes(request), context);
    } );
}

DescribeClientVpnTargetNetworksOutcome EC2Client::DescribeClientVpnTargetNetworks(const DescribeClientVpnTargetNetworksRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeClientVpnTargetNetworksOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeClientVpnTargetNetworksOutcomeCallable EC2Client::DescribeClientVpnTargetNetworksCallable(const DescribeClientVpnTargetNetworksRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeClientVpnTargetNetworksOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeClientVpnTargetNetworks(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeClientVpnTargetNetworksAsync(const DescribeClientVpnTargetNetworksRequest& request, const DescribeClientVpnTargetNetworksResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeClientVpnTargetNetworks(request), context);
    } );
}

DescribeCoipPoolsOutcome EC2Client::DescribeCoipPools(const DescribeCoipPoolsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeCoipPoolsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeCoipPoolsOutcomeCallable EC2Client::DescribeCoipPoolsCallable(const DescribeCoipPoolsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeCoipPoolsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeCoipPools(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeCoipPoolsAsync(const DescribeCoipPoolsRequest& request, const DescribeCoipPoolsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeCoipPools(request), context);
    } );
}

DescribeConversionTasksOutcome EC2Client::DescribeConversionTasks(const DescribeConversionTasksRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeConversionTasksOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeConversionTasksOutcomeCallable EC2Client::DescribeConversionTasksCallable(const DescribeConversionTasksRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeConversionTasksOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeConversionTasks(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeConversionTasksAsync(const DescribeConversionTasksRequest& request, const DescribeConversionTasksResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeConversionTasks(request), context);
    } );
}

DescribeCustomerGatewaysOutcome EC2Client::DescribeCustomerGateways(const DescribeCustomerGatewaysRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeCustomerGatewaysOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeCustomerGatewaysOutcomeCallable EC2Client::DescribeCustomerGatewaysCallable(const DescribeCustomerGatewaysRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeCustomerGatewaysOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeCustomerGateways(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeCustomerGatewaysAsync(const DescribeCustomerGatewaysRequest& request, const DescribeCustomerGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeCustomerGateways(request), context);
    } );
}

DescribeDhcpOptionsOutcome EC2Client::DescribeDhcpOptions(const DescribeDhcpOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeDhcpOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeDhcpOptionsOutcomeCallable EC2Client::DescribeDhcpOptionsCallable(const DescribeDhcpOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeDhcpOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeDhcpOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeDhcpOptionsAsync(const DescribeDhcpOptionsRequest& request, const DescribeDhcpOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeDhcpOptions(request), context);
    } );
}

DescribeEgressOnlyInternetGatewaysOutcome EC2Client::DescribeEgressOnlyInternetGateways(const DescribeEgressOnlyInternetGatewaysRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeEgressOnlyInternetGatewaysOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeEgressOnlyInternetGatewaysOutcomeCallable EC2Client::DescribeEgressOnlyInternetGatewaysCallable(const DescribeEgressOnlyInternetGatewaysRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeEgressOnlyInternetGatewaysOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeEgressOnlyInternetGateways(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeEgressOnlyInternetGatewaysAsync(const DescribeEgressOnlyInternetGatewaysRequest& request, const DescribeEgressOnlyInternetGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeEgressOnlyInternetGateways(request), context);
    } );
}

DescribeElasticGpusOutcome EC2Client::DescribeElasticGpus(const DescribeElasticGpusRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeElasticGpusOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeElasticGpusOutcomeCallable EC2Client::DescribeElasticGpusCallable(const DescribeElasticGpusRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeElasticGpusOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeElasticGpus(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeElasticGpusAsync(const DescribeElasticGpusRequest& request, const DescribeElasticGpusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeElasticGpus(request), context);
    } );
}

DescribeExportImageTasksOutcome EC2Client::DescribeExportImageTasks(const DescribeExportImageTasksRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeExportImageTasksOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeExportImageTasksOutcomeCallable EC2Client::DescribeExportImageTasksCallable(const DescribeExportImageTasksRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeExportImageTasksOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeExportImageTasks(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeExportImageTasksAsync(const DescribeExportImageTasksRequest& request, const DescribeExportImageTasksResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeExportImageTasks(request), context);
    } );
}

DescribeExportTasksOutcome EC2Client::DescribeExportTasks(const DescribeExportTasksRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeExportTasksOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeExportTasksOutcomeCallable EC2Client::DescribeExportTasksCallable(const DescribeExportTasksRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeExportTasksOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeExportTasks(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeExportTasksAsync(const DescribeExportTasksRequest& request, const DescribeExportTasksResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeExportTasks(request), context);
    } );
}

DescribeFastLaunchImagesOutcome EC2Client::DescribeFastLaunchImages(const DescribeFastLaunchImagesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeFastLaunchImagesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeFastLaunchImagesOutcomeCallable EC2Client::DescribeFastLaunchImagesCallable(const DescribeFastLaunchImagesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeFastLaunchImagesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeFastLaunchImages(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeFastLaunchImagesAsync(const DescribeFastLaunchImagesRequest& request, const DescribeFastLaunchImagesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeFastLaunchImages(request), context);
    } );
}

DescribeFastSnapshotRestoresOutcome EC2Client::DescribeFastSnapshotRestores(const DescribeFastSnapshotRestoresRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeFastSnapshotRestoresOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeFastSnapshotRestoresOutcomeCallable EC2Client::DescribeFastSnapshotRestoresCallable(const DescribeFastSnapshotRestoresRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeFastSnapshotRestoresOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeFastSnapshotRestores(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeFastSnapshotRestoresAsync(const DescribeFastSnapshotRestoresRequest& request, const DescribeFastSnapshotRestoresResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeFastSnapshotRestores(request), context);
    } );
}

DescribeFleetHistoryOutcome EC2Client::DescribeFleetHistory(const DescribeFleetHistoryRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeFleetHistoryOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeFleetHistoryOutcomeCallable EC2Client::DescribeFleetHistoryCallable(const DescribeFleetHistoryRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeFleetHistoryOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeFleetHistory(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeFleetHistoryAsync(const DescribeFleetHistoryRequest& request, const DescribeFleetHistoryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeFleetHistory(request), context);
    } );
}

DescribeFleetInstancesOutcome EC2Client::DescribeFleetInstances(const DescribeFleetInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeFleetInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeFleetInstancesOutcomeCallable EC2Client::DescribeFleetInstancesCallable(const DescribeFleetInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeFleetInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeFleetInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeFleetInstancesAsync(const DescribeFleetInstancesRequest& request, const DescribeFleetInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeFleetInstances(request), context);
    } );
}

DescribeFleetsOutcome EC2Client::DescribeFleets(const DescribeFleetsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeFleetsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeFleetsOutcomeCallable EC2Client::DescribeFleetsCallable(const DescribeFleetsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeFleetsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeFleets(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeFleetsAsync(const DescribeFleetsRequest& request, const DescribeFleetsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeFleets(request), context);
    } );
}

DescribeFlowLogsOutcome EC2Client::DescribeFlowLogs(const DescribeFlowLogsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeFlowLogsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeFlowLogsOutcomeCallable EC2Client::DescribeFlowLogsCallable(const DescribeFlowLogsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeFlowLogsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeFlowLogs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeFlowLogsAsync(const DescribeFlowLogsRequest& request, const DescribeFlowLogsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeFlowLogs(request), context);
    } );
}

DescribeFpgaImageAttributeOutcome EC2Client::DescribeFpgaImageAttribute(const DescribeFpgaImageAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeFpgaImageAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeFpgaImageAttributeOutcomeCallable EC2Client::DescribeFpgaImageAttributeCallable(const DescribeFpgaImageAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeFpgaImageAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeFpgaImageAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeFpgaImageAttributeAsync(const DescribeFpgaImageAttributeRequest& request, const DescribeFpgaImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeFpgaImageAttribute(request), context);
    } );
}

DescribeFpgaImagesOutcome EC2Client::DescribeFpgaImages(const DescribeFpgaImagesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeFpgaImagesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeFpgaImagesOutcomeCallable EC2Client::DescribeFpgaImagesCallable(const DescribeFpgaImagesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeFpgaImagesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeFpgaImages(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeFpgaImagesAsync(const DescribeFpgaImagesRequest& request, const DescribeFpgaImagesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeFpgaImages(request), context);
    } );
}

DescribeHostReservationOfferingsOutcome EC2Client::DescribeHostReservationOfferings(const DescribeHostReservationOfferingsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeHostReservationOfferingsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeHostReservationOfferingsOutcomeCallable EC2Client::DescribeHostReservationOfferingsCallable(const DescribeHostReservationOfferingsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeHostReservationOfferingsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeHostReservationOfferings(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeHostReservationOfferingsAsync(const DescribeHostReservationOfferingsRequest& request, const DescribeHostReservationOfferingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeHostReservationOfferings(request), context);
    } );
}

DescribeHostReservationsOutcome EC2Client::DescribeHostReservations(const DescribeHostReservationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeHostReservationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeHostReservationsOutcomeCallable EC2Client::DescribeHostReservationsCallable(const DescribeHostReservationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeHostReservationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeHostReservations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeHostReservationsAsync(const DescribeHostReservationsRequest& request, const DescribeHostReservationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeHostReservations(request), context);
    } );
}

DescribeHostsOutcome EC2Client::DescribeHosts(const DescribeHostsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeHostsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeHostsOutcomeCallable EC2Client::DescribeHostsCallable(const DescribeHostsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeHostsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeHosts(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeHostsAsync(const DescribeHostsRequest& request, const DescribeHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeHosts(request), context);
    } );
}

DescribeIamInstanceProfileAssociationsOutcome EC2Client::DescribeIamInstanceProfileAssociations(const DescribeIamInstanceProfileAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeIamInstanceProfileAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeIamInstanceProfileAssociationsOutcomeCallable EC2Client::DescribeIamInstanceProfileAssociationsCallable(const DescribeIamInstanceProfileAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeIamInstanceProfileAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeIamInstanceProfileAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeIamInstanceProfileAssociationsAsync(const DescribeIamInstanceProfileAssociationsRequest& request, const DescribeIamInstanceProfileAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeIamInstanceProfileAssociations(request), context);
    } );
}

DescribeIdFormatOutcome EC2Client::DescribeIdFormat(const DescribeIdFormatRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeIdFormatOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeIdFormatOutcomeCallable EC2Client::DescribeIdFormatCallable(const DescribeIdFormatRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeIdFormatOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeIdFormat(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeIdFormatAsync(const DescribeIdFormatRequest& request, const DescribeIdFormatResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeIdFormat(request), context);
    } );
}

DescribeIdentityIdFormatOutcome EC2Client::DescribeIdentityIdFormat(const DescribeIdentityIdFormatRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeIdentityIdFormatOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeIdentityIdFormatOutcomeCallable EC2Client::DescribeIdentityIdFormatCallable(const DescribeIdentityIdFormatRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeIdentityIdFormatOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeIdentityIdFormat(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeIdentityIdFormatAsync(const DescribeIdentityIdFormatRequest& request, const DescribeIdentityIdFormatResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeIdentityIdFormat(request), context);
    } );
}

DescribeImageAttributeOutcome EC2Client::DescribeImageAttribute(const DescribeImageAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeImageAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeImageAttributeOutcomeCallable EC2Client::DescribeImageAttributeCallable(const DescribeImageAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeImageAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeImageAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeImageAttributeAsync(const DescribeImageAttributeRequest& request, const DescribeImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeImageAttribute(request), context);
    } );
}

DescribeImagesOutcome EC2Client::DescribeImages(const DescribeImagesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeImagesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeImagesOutcomeCallable EC2Client::DescribeImagesCallable(const DescribeImagesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeImagesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeImages(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeImagesAsync(const DescribeImagesRequest& request, const DescribeImagesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeImages(request), context);
    } );
}

DescribeImportImageTasksOutcome EC2Client::DescribeImportImageTasks(const DescribeImportImageTasksRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeImportImageTasksOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeImportImageTasksOutcomeCallable EC2Client::DescribeImportImageTasksCallable(const DescribeImportImageTasksRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeImportImageTasksOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeImportImageTasks(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeImportImageTasksAsync(const DescribeImportImageTasksRequest& request, const DescribeImportImageTasksResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeImportImageTasks(request), context);
    } );
}

DescribeImportSnapshotTasksOutcome EC2Client::DescribeImportSnapshotTasks(const DescribeImportSnapshotTasksRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeImportSnapshotTasksOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeImportSnapshotTasksOutcomeCallable EC2Client::DescribeImportSnapshotTasksCallable(const DescribeImportSnapshotTasksRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeImportSnapshotTasksOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeImportSnapshotTasks(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeImportSnapshotTasksAsync(const DescribeImportSnapshotTasksRequest& request, const DescribeImportSnapshotTasksResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeImportSnapshotTasks(request), context);
    } );
}

DescribeInstanceAttributeOutcome EC2Client::DescribeInstanceAttribute(const DescribeInstanceAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeInstanceAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeInstanceAttributeOutcomeCallable EC2Client::DescribeInstanceAttributeCallable(const DescribeInstanceAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeInstanceAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeInstanceAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeInstanceAttributeAsync(const DescribeInstanceAttributeRequest& request, const DescribeInstanceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeInstanceAttribute(request), context);
    } );
}

DescribeInstanceCreditSpecificationsOutcome EC2Client::DescribeInstanceCreditSpecifications(const DescribeInstanceCreditSpecificationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeInstanceCreditSpecificationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeInstanceCreditSpecificationsOutcomeCallable EC2Client::DescribeInstanceCreditSpecificationsCallable(const DescribeInstanceCreditSpecificationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeInstanceCreditSpecificationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeInstanceCreditSpecifications(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeInstanceCreditSpecificationsAsync(const DescribeInstanceCreditSpecificationsRequest& request, const DescribeInstanceCreditSpecificationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeInstanceCreditSpecifications(request), context);
    } );
}

DescribeInstanceEventNotificationAttributesOutcome EC2Client::DescribeInstanceEventNotificationAttributes(const DescribeInstanceEventNotificationAttributesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeInstanceEventNotificationAttributesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeInstanceEventNotificationAttributesOutcomeCallable EC2Client::DescribeInstanceEventNotificationAttributesCallable(const DescribeInstanceEventNotificationAttributesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeInstanceEventNotificationAttributesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeInstanceEventNotificationAttributes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeInstanceEventNotificationAttributesAsync(const DescribeInstanceEventNotificationAttributesRequest& request, const DescribeInstanceEventNotificationAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeInstanceEventNotificationAttributes(request), context);
    } );
}

DescribeInstanceEventWindowsOutcome EC2Client::DescribeInstanceEventWindows(const DescribeInstanceEventWindowsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeInstanceEventWindowsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeInstanceEventWindowsOutcomeCallable EC2Client::DescribeInstanceEventWindowsCallable(const DescribeInstanceEventWindowsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeInstanceEventWindowsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeInstanceEventWindows(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeInstanceEventWindowsAsync(const DescribeInstanceEventWindowsRequest& request, const DescribeInstanceEventWindowsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeInstanceEventWindows(request), context);
    } );
}

DescribeInstanceStatusOutcome EC2Client::DescribeInstanceStatus(const DescribeInstanceStatusRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeInstanceStatusOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeInstanceStatusOutcomeCallable EC2Client::DescribeInstanceStatusCallable(const DescribeInstanceStatusRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeInstanceStatusOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeInstanceStatus(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeInstanceStatusAsync(const DescribeInstanceStatusRequest& request, const DescribeInstanceStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeInstanceStatus(request), context);
    } );
}

DescribeInstanceTypeOfferingsOutcome EC2Client::DescribeInstanceTypeOfferings(const DescribeInstanceTypeOfferingsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeInstanceTypeOfferingsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeInstanceTypeOfferingsOutcomeCallable EC2Client::DescribeInstanceTypeOfferingsCallable(const DescribeInstanceTypeOfferingsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeInstanceTypeOfferingsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeInstanceTypeOfferings(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeInstanceTypeOfferingsAsync(const DescribeInstanceTypeOfferingsRequest& request, const DescribeInstanceTypeOfferingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeInstanceTypeOfferings(request), context);
    } );
}

DescribeInstanceTypesOutcome EC2Client::DescribeInstanceTypes(const DescribeInstanceTypesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeInstanceTypesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeInstanceTypesOutcomeCallable EC2Client::DescribeInstanceTypesCallable(const DescribeInstanceTypesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeInstanceTypesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeInstanceTypes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeInstanceTypesAsync(const DescribeInstanceTypesRequest& request, const DescribeInstanceTypesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeInstanceTypes(request), context);
    } );
}

DescribeInstancesOutcome EC2Client::DescribeInstances(const DescribeInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeInstancesOutcomeCallable EC2Client::DescribeInstancesCallable(const DescribeInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeInstancesAsync(const DescribeInstancesRequest& request, const DescribeInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeInstances(request), context);
    } );
}

DescribeInternetGatewaysOutcome EC2Client::DescribeInternetGateways(const DescribeInternetGatewaysRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeInternetGatewaysOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeInternetGatewaysOutcomeCallable EC2Client::DescribeInternetGatewaysCallable(const DescribeInternetGatewaysRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeInternetGatewaysOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeInternetGateways(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeInternetGatewaysAsync(const DescribeInternetGatewaysRequest& request, const DescribeInternetGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeInternetGateways(request), context);
    } );
}

DescribeIpamPoolsOutcome EC2Client::DescribeIpamPools(const DescribeIpamPoolsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeIpamPoolsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeIpamPoolsOutcomeCallable EC2Client::DescribeIpamPoolsCallable(const DescribeIpamPoolsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeIpamPoolsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeIpamPools(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeIpamPoolsAsync(const DescribeIpamPoolsRequest& request, const DescribeIpamPoolsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeIpamPools(request), context);
    } );
}

DescribeIpamScopesOutcome EC2Client::DescribeIpamScopes(const DescribeIpamScopesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeIpamScopesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeIpamScopesOutcomeCallable EC2Client::DescribeIpamScopesCallable(const DescribeIpamScopesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeIpamScopesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeIpamScopes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeIpamScopesAsync(const DescribeIpamScopesRequest& request, const DescribeIpamScopesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeIpamScopes(request), context);
    } );
}

DescribeIpamsOutcome EC2Client::DescribeIpams(const DescribeIpamsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeIpamsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeIpamsOutcomeCallable EC2Client::DescribeIpamsCallable(const DescribeIpamsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeIpamsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeIpams(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeIpamsAsync(const DescribeIpamsRequest& request, const DescribeIpamsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeIpams(request), context);
    } );
}

DescribeIpv6PoolsOutcome EC2Client::DescribeIpv6Pools(const DescribeIpv6PoolsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeIpv6PoolsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeIpv6PoolsOutcomeCallable EC2Client::DescribeIpv6PoolsCallable(const DescribeIpv6PoolsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeIpv6PoolsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeIpv6Pools(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeIpv6PoolsAsync(const DescribeIpv6PoolsRequest& request, const DescribeIpv6PoolsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeIpv6Pools(request), context);
    } );
}

DescribeKeyPairsOutcome EC2Client::DescribeKeyPairs(const DescribeKeyPairsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeKeyPairsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeKeyPairsOutcomeCallable EC2Client::DescribeKeyPairsCallable(const DescribeKeyPairsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeKeyPairsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeKeyPairs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeKeyPairsAsync(const DescribeKeyPairsRequest& request, const DescribeKeyPairsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeKeyPairs(request), context);
    } );
}

DescribeLaunchTemplateVersionsOutcome EC2Client::DescribeLaunchTemplateVersions(const DescribeLaunchTemplateVersionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeLaunchTemplateVersionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeLaunchTemplateVersionsOutcomeCallable EC2Client::DescribeLaunchTemplateVersionsCallable(const DescribeLaunchTemplateVersionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeLaunchTemplateVersionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeLaunchTemplateVersions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeLaunchTemplateVersionsAsync(const DescribeLaunchTemplateVersionsRequest& request, const DescribeLaunchTemplateVersionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeLaunchTemplateVersions(request), context);
    } );
}

DescribeLaunchTemplatesOutcome EC2Client::DescribeLaunchTemplates(const DescribeLaunchTemplatesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeLaunchTemplatesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeLaunchTemplatesOutcomeCallable EC2Client::DescribeLaunchTemplatesCallable(const DescribeLaunchTemplatesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeLaunchTemplatesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeLaunchTemplates(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeLaunchTemplatesAsync(const DescribeLaunchTemplatesRequest& request, const DescribeLaunchTemplatesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeLaunchTemplates(request), context);
    } );
}

DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsOutcome EC2Client::DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociations(const DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsOutcomeCallable EC2Client::DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsCallable(const DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsAsync(const DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsRequest& request, const DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeLocalGatewayRouteTableVirtualInterfaceGroupAssociations(request), context);
    } );
}

DescribeLocalGatewayRouteTableVpcAssociationsOutcome EC2Client::DescribeLocalGatewayRouteTableVpcAssociations(const DescribeLocalGatewayRouteTableVpcAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeLocalGatewayRouteTableVpcAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeLocalGatewayRouteTableVpcAssociationsOutcomeCallable EC2Client::DescribeLocalGatewayRouteTableVpcAssociationsCallable(const DescribeLocalGatewayRouteTableVpcAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeLocalGatewayRouteTableVpcAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeLocalGatewayRouteTableVpcAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeLocalGatewayRouteTableVpcAssociationsAsync(const DescribeLocalGatewayRouteTableVpcAssociationsRequest& request, const DescribeLocalGatewayRouteTableVpcAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeLocalGatewayRouteTableVpcAssociations(request), context);
    } );
}

DescribeLocalGatewayRouteTablesOutcome EC2Client::DescribeLocalGatewayRouteTables(const DescribeLocalGatewayRouteTablesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeLocalGatewayRouteTablesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeLocalGatewayRouteTablesOutcomeCallable EC2Client::DescribeLocalGatewayRouteTablesCallable(const DescribeLocalGatewayRouteTablesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeLocalGatewayRouteTablesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeLocalGatewayRouteTables(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeLocalGatewayRouteTablesAsync(const DescribeLocalGatewayRouteTablesRequest& request, const DescribeLocalGatewayRouteTablesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeLocalGatewayRouteTables(request), context);
    } );
}

DescribeLocalGatewayVirtualInterfaceGroupsOutcome EC2Client::DescribeLocalGatewayVirtualInterfaceGroups(const DescribeLocalGatewayVirtualInterfaceGroupsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeLocalGatewayVirtualInterfaceGroupsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeLocalGatewayVirtualInterfaceGroupsOutcomeCallable EC2Client::DescribeLocalGatewayVirtualInterfaceGroupsCallable(const DescribeLocalGatewayVirtualInterfaceGroupsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeLocalGatewayVirtualInterfaceGroupsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeLocalGatewayVirtualInterfaceGroups(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeLocalGatewayVirtualInterfaceGroupsAsync(const DescribeLocalGatewayVirtualInterfaceGroupsRequest& request, const DescribeLocalGatewayVirtualInterfaceGroupsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeLocalGatewayVirtualInterfaceGroups(request), context);
    } );
}

DescribeLocalGatewayVirtualInterfacesOutcome EC2Client::DescribeLocalGatewayVirtualInterfaces(const DescribeLocalGatewayVirtualInterfacesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeLocalGatewayVirtualInterfacesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeLocalGatewayVirtualInterfacesOutcomeCallable EC2Client::DescribeLocalGatewayVirtualInterfacesCallable(const DescribeLocalGatewayVirtualInterfacesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeLocalGatewayVirtualInterfacesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeLocalGatewayVirtualInterfaces(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeLocalGatewayVirtualInterfacesAsync(const DescribeLocalGatewayVirtualInterfacesRequest& request, const DescribeLocalGatewayVirtualInterfacesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeLocalGatewayVirtualInterfaces(request), context);
    } );
}

DescribeLocalGatewaysOutcome EC2Client::DescribeLocalGateways(const DescribeLocalGatewaysRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeLocalGatewaysOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeLocalGatewaysOutcomeCallable EC2Client::DescribeLocalGatewaysCallable(const DescribeLocalGatewaysRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeLocalGatewaysOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeLocalGateways(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeLocalGatewaysAsync(const DescribeLocalGatewaysRequest& request, const DescribeLocalGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeLocalGateways(request), context);
    } );
}

DescribeManagedPrefixListsOutcome EC2Client::DescribeManagedPrefixLists(const DescribeManagedPrefixListsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeManagedPrefixListsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeManagedPrefixListsOutcomeCallable EC2Client::DescribeManagedPrefixListsCallable(const DescribeManagedPrefixListsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeManagedPrefixListsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeManagedPrefixLists(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeManagedPrefixListsAsync(const DescribeManagedPrefixListsRequest& request, const DescribeManagedPrefixListsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeManagedPrefixLists(request), context);
    } );
}

DescribeMovingAddressesOutcome EC2Client::DescribeMovingAddresses(const DescribeMovingAddressesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeMovingAddressesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeMovingAddressesOutcomeCallable EC2Client::DescribeMovingAddressesCallable(const DescribeMovingAddressesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeMovingAddressesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeMovingAddresses(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeMovingAddressesAsync(const DescribeMovingAddressesRequest& request, const DescribeMovingAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeMovingAddresses(request), context);
    } );
}

DescribeNatGatewaysOutcome EC2Client::DescribeNatGateways(const DescribeNatGatewaysRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeNatGatewaysOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeNatGatewaysOutcomeCallable EC2Client::DescribeNatGatewaysCallable(const DescribeNatGatewaysRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeNatGatewaysOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeNatGateways(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeNatGatewaysAsync(const DescribeNatGatewaysRequest& request, const DescribeNatGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeNatGateways(request), context);
    } );
}

DescribeNetworkAclsOutcome EC2Client::DescribeNetworkAcls(const DescribeNetworkAclsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeNetworkAclsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeNetworkAclsOutcomeCallable EC2Client::DescribeNetworkAclsCallable(const DescribeNetworkAclsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeNetworkAclsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeNetworkAcls(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeNetworkAclsAsync(const DescribeNetworkAclsRequest& request, const DescribeNetworkAclsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeNetworkAcls(request), context);
    } );
}

DescribeNetworkInsightsAccessScopeAnalysesOutcome EC2Client::DescribeNetworkInsightsAccessScopeAnalyses(const DescribeNetworkInsightsAccessScopeAnalysesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeNetworkInsightsAccessScopeAnalysesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeNetworkInsightsAccessScopeAnalysesOutcomeCallable EC2Client::DescribeNetworkInsightsAccessScopeAnalysesCallable(const DescribeNetworkInsightsAccessScopeAnalysesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeNetworkInsightsAccessScopeAnalysesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeNetworkInsightsAccessScopeAnalyses(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeNetworkInsightsAccessScopeAnalysesAsync(const DescribeNetworkInsightsAccessScopeAnalysesRequest& request, const DescribeNetworkInsightsAccessScopeAnalysesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeNetworkInsightsAccessScopeAnalyses(request), context);
    } );
}

DescribeNetworkInsightsAccessScopesOutcome EC2Client::DescribeNetworkInsightsAccessScopes(const DescribeNetworkInsightsAccessScopesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeNetworkInsightsAccessScopesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeNetworkInsightsAccessScopesOutcomeCallable EC2Client::DescribeNetworkInsightsAccessScopesCallable(const DescribeNetworkInsightsAccessScopesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeNetworkInsightsAccessScopesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeNetworkInsightsAccessScopes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeNetworkInsightsAccessScopesAsync(const DescribeNetworkInsightsAccessScopesRequest& request, const DescribeNetworkInsightsAccessScopesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeNetworkInsightsAccessScopes(request), context);
    } );
}

DescribeNetworkInsightsAnalysesOutcome EC2Client::DescribeNetworkInsightsAnalyses(const DescribeNetworkInsightsAnalysesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeNetworkInsightsAnalysesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeNetworkInsightsAnalysesOutcomeCallable EC2Client::DescribeNetworkInsightsAnalysesCallable(const DescribeNetworkInsightsAnalysesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeNetworkInsightsAnalysesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeNetworkInsightsAnalyses(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeNetworkInsightsAnalysesAsync(const DescribeNetworkInsightsAnalysesRequest& request, const DescribeNetworkInsightsAnalysesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeNetworkInsightsAnalyses(request), context);
    } );
}

DescribeNetworkInsightsPathsOutcome EC2Client::DescribeNetworkInsightsPaths(const DescribeNetworkInsightsPathsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeNetworkInsightsPathsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeNetworkInsightsPathsOutcomeCallable EC2Client::DescribeNetworkInsightsPathsCallable(const DescribeNetworkInsightsPathsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeNetworkInsightsPathsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeNetworkInsightsPaths(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeNetworkInsightsPathsAsync(const DescribeNetworkInsightsPathsRequest& request, const DescribeNetworkInsightsPathsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeNetworkInsightsPaths(request), context);
    } );
}

DescribeNetworkInterfaceAttributeOutcome EC2Client::DescribeNetworkInterfaceAttribute(const DescribeNetworkInterfaceAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeNetworkInterfaceAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeNetworkInterfaceAttributeOutcomeCallable EC2Client::DescribeNetworkInterfaceAttributeCallable(const DescribeNetworkInterfaceAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeNetworkInterfaceAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeNetworkInterfaceAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeNetworkInterfaceAttributeAsync(const DescribeNetworkInterfaceAttributeRequest& request, const DescribeNetworkInterfaceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeNetworkInterfaceAttribute(request), context);
    } );
}

DescribeNetworkInterfacePermissionsOutcome EC2Client::DescribeNetworkInterfacePermissions(const DescribeNetworkInterfacePermissionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeNetworkInterfacePermissionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeNetworkInterfacePermissionsOutcomeCallable EC2Client::DescribeNetworkInterfacePermissionsCallable(const DescribeNetworkInterfacePermissionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeNetworkInterfacePermissionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeNetworkInterfacePermissions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeNetworkInterfacePermissionsAsync(const DescribeNetworkInterfacePermissionsRequest& request, const DescribeNetworkInterfacePermissionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeNetworkInterfacePermissions(request), context);
    } );
}

DescribeNetworkInterfacesOutcome EC2Client::DescribeNetworkInterfaces(const DescribeNetworkInterfacesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeNetworkInterfacesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeNetworkInterfacesOutcomeCallable EC2Client::DescribeNetworkInterfacesCallable(const DescribeNetworkInterfacesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeNetworkInterfacesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeNetworkInterfaces(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeNetworkInterfacesAsync(const DescribeNetworkInterfacesRequest& request, const DescribeNetworkInterfacesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeNetworkInterfaces(request), context);
    } );
}

DescribePlacementGroupsOutcome EC2Client::DescribePlacementGroups(const DescribePlacementGroupsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribePlacementGroupsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribePlacementGroupsOutcomeCallable EC2Client::DescribePlacementGroupsCallable(const DescribePlacementGroupsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribePlacementGroupsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribePlacementGroups(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribePlacementGroupsAsync(const DescribePlacementGroupsRequest& request, const DescribePlacementGroupsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribePlacementGroups(request), context);
    } );
}

DescribePrefixListsOutcome EC2Client::DescribePrefixLists(const DescribePrefixListsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribePrefixListsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribePrefixListsOutcomeCallable EC2Client::DescribePrefixListsCallable(const DescribePrefixListsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribePrefixListsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribePrefixLists(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribePrefixListsAsync(const DescribePrefixListsRequest& request, const DescribePrefixListsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribePrefixLists(request), context);
    } );
}

DescribePrincipalIdFormatOutcome EC2Client::DescribePrincipalIdFormat(const DescribePrincipalIdFormatRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribePrincipalIdFormatOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribePrincipalIdFormatOutcomeCallable EC2Client::DescribePrincipalIdFormatCallable(const DescribePrincipalIdFormatRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribePrincipalIdFormatOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribePrincipalIdFormat(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribePrincipalIdFormatAsync(const DescribePrincipalIdFormatRequest& request, const DescribePrincipalIdFormatResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribePrincipalIdFormat(request), context);
    } );
}

DescribePublicIpv4PoolsOutcome EC2Client::DescribePublicIpv4Pools(const DescribePublicIpv4PoolsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribePublicIpv4PoolsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribePublicIpv4PoolsOutcomeCallable EC2Client::DescribePublicIpv4PoolsCallable(const DescribePublicIpv4PoolsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribePublicIpv4PoolsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribePublicIpv4Pools(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribePublicIpv4PoolsAsync(const DescribePublicIpv4PoolsRequest& request, const DescribePublicIpv4PoolsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribePublicIpv4Pools(request), context);
    } );
}

DescribeRegionsOutcome EC2Client::DescribeRegions(const DescribeRegionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeRegionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeRegionsOutcomeCallable EC2Client::DescribeRegionsCallable(const DescribeRegionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeRegionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeRegions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeRegionsAsync(const DescribeRegionsRequest& request, const DescribeRegionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeRegions(request), context);
    } );
}

DescribeReplaceRootVolumeTasksOutcome EC2Client::DescribeReplaceRootVolumeTasks(const DescribeReplaceRootVolumeTasksRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeReplaceRootVolumeTasksOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeReplaceRootVolumeTasksOutcomeCallable EC2Client::DescribeReplaceRootVolumeTasksCallable(const DescribeReplaceRootVolumeTasksRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeReplaceRootVolumeTasksOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeReplaceRootVolumeTasks(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeReplaceRootVolumeTasksAsync(const DescribeReplaceRootVolumeTasksRequest& request, const DescribeReplaceRootVolumeTasksResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeReplaceRootVolumeTasks(request), context);
    } );
}

DescribeReservedInstancesOutcome EC2Client::DescribeReservedInstances(const DescribeReservedInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeReservedInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeReservedInstancesOutcomeCallable EC2Client::DescribeReservedInstancesCallable(const DescribeReservedInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeReservedInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeReservedInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeReservedInstancesAsync(const DescribeReservedInstancesRequest& request, const DescribeReservedInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeReservedInstances(request), context);
    } );
}

DescribeReservedInstancesListingsOutcome EC2Client::DescribeReservedInstancesListings(const DescribeReservedInstancesListingsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeReservedInstancesListingsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeReservedInstancesListingsOutcomeCallable EC2Client::DescribeReservedInstancesListingsCallable(const DescribeReservedInstancesListingsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeReservedInstancesListingsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeReservedInstancesListings(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeReservedInstancesListingsAsync(const DescribeReservedInstancesListingsRequest& request, const DescribeReservedInstancesListingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeReservedInstancesListings(request), context);
    } );
}

DescribeReservedInstancesModificationsOutcome EC2Client::DescribeReservedInstancesModifications(const DescribeReservedInstancesModificationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeReservedInstancesModificationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeReservedInstancesModificationsOutcomeCallable EC2Client::DescribeReservedInstancesModificationsCallable(const DescribeReservedInstancesModificationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeReservedInstancesModificationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeReservedInstancesModifications(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeReservedInstancesModificationsAsync(const DescribeReservedInstancesModificationsRequest& request, const DescribeReservedInstancesModificationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeReservedInstancesModifications(request), context);
    } );
}

DescribeReservedInstancesOfferingsOutcome EC2Client::DescribeReservedInstancesOfferings(const DescribeReservedInstancesOfferingsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeReservedInstancesOfferingsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeReservedInstancesOfferingsOutcomeCallable EC2Client::DescribeReservedInstancesOfferingsCallable(const DescribeReservedInstancesOfferingsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeReservedInstancesOfferingsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeReservedInstancesOfferings(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeReservedInstancesOfferingsAsync(const DescribeReservedInstancesOfferingsRequest& request, const DescribeReservedInstancesOfferingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeReservedInstancesOfferings(request), context);
    } );
}

DescribeRouteTablesOutcome EC2Client::DescribeRouteTables(const DescribeRouteTablesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeRouteTablesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeRouteTablesOutcomeCallable EC2Client::DescribeRouteTablesCallable(const DescribeRouteTablesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeRouteTablesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeRouteTables(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeRouteTablesAsync(const DescribeRouteTablesRequest& request, const DescribeRouteTablesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeRouteTables(request), context);
    } );
}

DescribeScheduledInstanceAvailabilityOutcome EC2Client::DescribeScheduledInstanceAvailability(const DescribeScheduledInstanceAvailabilityRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeScheduledInstanceAvailabilityOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeScheduledInstanceAvailabilityOutcomeCallable EC2Client::DescribeScheduledInstanceAvailabilityCallable(const DescribeScheduledInstanceAvailabilityRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeScheduledInstanceAvailabilityOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeScheduledInstanceAvailability(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeScheduledInstanceAvailabilityAsync(const DescribeScheduledInstanceAvailabilityRequest& request, const DescribeScheduledInstanceAvailabilityResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeScheduledInstanceAvailability(request), context);
    } );
}

DescribeScheduledInstancesOutcome EC2Client::DescribeScheduledInstances(const DescribeScheduledInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeScheduledInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeScheduledInstancesOutcomeCallable EC2Client::DescribeScheduledInstancesCallable(const DescribeScheduledInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeScheduledInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeScheduledInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeScheduledInstancesAsync(const DescribeScheduledInstancesRequest& request, const DescribeScheduledInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeScheduledInstances(request), context);
    } );
}

DescribeSecurityGroupReferencesOutcome EC2Client::DescribeSecurityGroupReferences(const DescribeSecurityGroupReferencesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSecurityGroupReferencesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSecurityGroupReferencesOutcomeCallable EC2Client::DescribeSecurityGroupReferencesCallable(const DescribeSecurityGroupReferencesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSecurityGroupReferencesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSecurityGroupReferences(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSecurityGroupReferencesAsync(const DescribeSecurityGroupReferencesRequest& request, const DescribeSecurityGroupReferencesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSecurityGroupReferences(request), context);
    } );
}

DescribeSecurityGroupRulesOutcome EC2Client::DescribeSecurityGroupRules(const DescribeSecurityGroupRulesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSecurityGroupRulesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSecurityGroupRulesOutcomeCallable EC2Client::DescribeSecurityGroupRulesCallable(const DescribeSecurityGroupRulesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSecurityGroupRulesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSecurityGroupRules(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSecurityGroupRulesAsync(const DescribeSecurityGroupRulesRequest& request, const DescribeSecurityGroupRulesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSecurityGroupRules(request), context);
    } );
}

DescribeSecurityGroupsOutcome EC2Client::DescribeSecurityGroups(const DescribeSecurityGroupsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSecurityGroupsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSecurityGroupsOutcomeCallable EC2Client::DescribeSecurityGroupsCallable(const DescribeSecurityGroupsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSecurityGroupsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSecurityGroups(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSecurityGroupsAsync(const DescribeSecurityGroupsRequest& request, const DescribeSecurityGroupsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSecurityGroups(request), context);
    } );
}

DescribeSnapshotAttributeOutcome EC2Client::DescribeSnapshotAttribute(const DescribeSnapshotAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSnapshotAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSnapshotAttributeOutcomeCallable EC2Client::DescribeSnapshotAttributeCallable(const DescribeSnapshotAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSnapshotAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSnapshotAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSnapshotAttributeAsync(const DescribeSnapshotAttributeRequest& request, const DescribeSnapshotAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSnapshotAttribute(request), context);
    } );
}

DescribeSnapshotTierStatusOutcome EC2Client::DescribeSnapshotTierStatus(const DescribeSnapshotTierStatusRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSnapshotTierStatusOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSnapshotTierStatusOutcomeCallable EC2Client::DescribeSnapshotTierStatusCallable(const DescribeSnapshotTierStatusRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSnapshotTierStatusOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSnapshotTierStatus(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSnapshotTierStatusAsync(const DescribeSnapshotTierStatusRequest& request, const DescribeSnapshotTierStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSnapshotTierStatus(request), context);
    } );
}

DescribeSnapshotsOutcome EC2Client::DescribeSnapshots(const DescribeSnapshotsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSnapshotsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSnapshotsOutcomeCallable EC2Client::DescribeSnapshotsCallable(const DescribeSnapshotsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSnapshotsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSnapshots(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSnapshotsAsync(const DescribeSnapshotsRequest& request, const DescribeSnapshotsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSnapshots(request), context);
    } );
}

DescribeSpotDatafeedSubscriptionOutcome EC2Client::DescribeSpotDatafeedSubscription(const DescribeSpotDatafeedSubscriptionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSpotDatafeedSubscriptionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSpotDatafeedSubscriptionOutcomeCallable EC2Client::DescribeSpotDatafeedSubscriptionCallable(const DescribeSpotDatafeedSubscriptionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSpotDatafeedSubscriptionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSpotDatafeedSubscription(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSpotDatafeedSubscriptionAsync(const DescribeSpotDatafeedSubscriptionRequest& request, const DescribeSpotDatafeedSubscriptionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSpotDatafeedSubscription(request), context);
    } );
}

DescribeSpotFleetInstancesOutcome EC2Client::DescribeSpotFleetInstances(const DescribeSpotFleetInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSpotFleetInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSpotFleetInstancesOutcomeCallable EC2Client::DescribeSpotFleetInstancesCallable(const DescribeSpotFleetInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSpotFleetInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSpotFleetInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSpotFleetInstancesAsync(const DescribeSpotFleetInstancesRequest& request, const DescribeSpotFleetInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSpotFleetInstances(request), context);
    } );
}

DescribeSpotFleetRequestHistoryOutcome EC2Client::DescribeSpotFleetRequestHistory(const DescribeSpotFleetRequestHistoryRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSpotFleetRequestHistoryOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSpotFleetRequestHistoryOutcomeCallable EC2Client::DescribeSpotFleetRequestHistoryCallable(const DescribeSpotFleetRequestHistoryRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSpotFleetRequestHistoryOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSpotFleetRequestHistory(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSpotFleetRequestHistoryAsync(const DescribeSpotFleetRequestHistoryRequest& request, const DescribeSpotFleetRequestHistoryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSpotFleetRequestHistory(request), context);
    } );
}

DescribeSpotFleetRequestsOutcome EC2Client::DescribeSpotFleetRequests(const DescribeSpotFleetRequestsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSpotFleetRequestsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSpotFleetRequestsOutcomeCallable EC2Client::DescribeSpotFleetRequestsCallable(const DescribeSpotFleetRequestsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSpotFleetRequestsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSpotFleetRequests(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSpotFleetRequestsAsync(const DescribeSpotFleetRequestsRequest& request, const DescribeSpotFleetRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSpotFleetRequests(request), context);
    } );
}

DescribeSpotInstanceRequestsOutcome EC2Client::DescribeSpotInstanceRequests(const DescribeSpotInstanceRequestsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSpotInstanceRequestsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSpotInstanceRequestsOutcomeCallable EC2Client::DescribeSpotInstanceRequestsCallable(const DescribeSpotInstanceRequestsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSpotInstanceRequestsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSpotInstanceRequests(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSpotInstanceRequestsAsync(const DescribeSpotInstanceRequestsRequest& request, const DescribeSpotInstanceRequestsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSpotInstanceRequests(request), context);
    } );
}

DescribeSpotPriceHistoryOutcome EC2Client::DescribeSpotPriceHistory(const DescribeSpotPriceHistoryRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSpotPriceHistoryOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSpotPriceHistoryOutcomeCallable EC2Client::DescribeSpotPriceHistoryCallable(const DescribeSpotPriceHistoryRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSpotPriceHistoryOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSpotPriceHistory(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSpotPriceHistoryAsync(const DescribeSpotPriceHistoryRequest& request, const DescribeSpotPriceHistoryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSpotPriceHistory(request), context);
    } );
}

DescribeStaleSecurityGroupsOutcome EC2Client::DescribeStaleSecurityGroups(const DescribeStaleSecurityGroupsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeStaleSecurityGroupsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeStaleSecurityGroupsOutcomeCallable EC2Client::DescribeStaleSecurityGroupsCallable(const DescribeStaleSecurityGroupsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeStaleSecurityGroupsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeStaleSecurityGroups(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeStaleSecurityGroupsAsync(const DescribeStaleSecurityGroupsRequest& request, const DescribeStaleSecurityGroupsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeStaleSecurityGroups(request), context);
    } );
}

DescribeStoreImageTasksOutcome EC2Client::DescribeStoreImageTasks(const DescribeStoreImageTasksRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeStoreImageTasksOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeStoreImageTasksOutcomeCallable EC2Client::DescribeStoreImageTasksCallable(const DescribeStoreImageTasksRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeStoreImageTasksOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeStoreImageTasks(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeStoreImageTasksAsync(const DescribeStoreImageTasksRequest& request, const DescribeStoreImageTasksResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeStoreImageTasks(request), context);
    } );
}

DescribeSubnetsOutcome EC2Client::DescribeSubnets(const DescribeSubnetsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeSubnetsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeSubnetsOutcomeCallable EC2Client::DescribeSubnetsCallable(const DescribeSubnetsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeSubnetsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeSubnets(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeSubnetsAsync(const DescribeSubnetsRequest& request, const DescribeSubnetsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeSubnets(request), context);
    } );
}

DescribeTagsOutcome EC2Client::DescribeTags(const DescribeTagsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTagsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTagsOutcomeCallable EC2Client::DescribeTagsCallable(const DescribeTagsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTagsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTags(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTagsAsync(const DescribeTagsRequest& request, const DescribeTagsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTags(request), context);
    } );
}

DescribeTrafficMirrorFiltersOutcome EC2Client::DescribeTrafficMirrorFilters(const DescribeTrafficMirrorFiltersRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTrafficMirrorFiltersOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTrafficMirrorFiltersOutcomeCallable EC2Client::DescribeTrafficMirrorFiltersCallable(const DescribeTrafficMirrorFiltersRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTrafficMirrorFiltersOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTrafficMirrorFilters(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTrafficMirrorFiltersAsync(const DescribeTrafficMirrorFiltersRequest& request, const DescribeTrafficMirrorFiltersResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTrafficMirrorFilters(request), context);
    } );
}

DescribeTrafficMirrorSessionsOutcome EC2Client::DescribeTrafficMirrorSessions(const DescribeTrafficMirrorSessionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTrafficMirrorSessionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTrafficMirrorSessionsOutcomeCallable EC2Client::DescribeTrafficMirrorSessionsCallable(const DescribeTrafficMirrorSessionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTrafficMirrorSessionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTrafficMirrorSessions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTrafficMirrorSessionsAsync(const DescribeTrafficMirrorSessionsRequest& request, const DescribeTrafficMirrorSessionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTrafficMirrorSessions(request), context);
    } );
}

DescribeTrafficMirrorTargetsOutcome EC2Client::DescribeTrafficMirrorTargets(const DescribeTrafficMirrorTargetsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTrafficMirrorTargetsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTrafficMirrorTargetsOutcomeCallable EC2Client::DescribeTrafficMirrorTargetsCallable(const DescribeTrafficMirrorTargetsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTrafficMirrorTargetsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTrafficMirrorTargets(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTrafficMirrorTargetsAsync(const DescribeTrafficMirrorTargetsRequest& request, const DescribeTrafficMirrorTargetsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTrafficMirrorTargets(request), context);
    } );
}

DescribeTransitGatewayAttachmentsOutcome EC2Client::DescribeTransitGatewayAttachments(const DescribeTransitGatewayAttachmentsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewayAttachmentsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewayAttachmentsOutcomeCallable EC2Client::DescribeTransitGatewayAttachmentsCallable(const DescribeTransitGatewayAttachmentsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewayAttachmentsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGatewayAttachments(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewayAttachmentsAsync(const DescribeTransitGatewayAttachmentsRequest& request, const DescribeTransitGatewayAttachmentsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGatewayAttachments(request), context);
    } );
}

DescribeTransitGatewayConnectPeersOutcome EC2Client::DescribeTransitGatewayConnectPeers(const DescribeTransitGatewayConnectPeersRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewayConnectPeersOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewayConnectPeersOutcomeCallable EC2Client::DescribeTransitGatewayConnectPeersCallable(const DescribeTransitGatewayConnectPeersRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewayConnectPeersOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGatewayConnectPeers(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewayConnectPeersAsync(const DescribeTransitGatewayConnectPeersRequest& request, const DescribeTransitGatewayConnectPeersResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGatewayConnectPeers(request), context);
    } );
}

DescribeTransitGatewayConnectsOutcome EC2Client::DescribeTransitGatewayConnects(const DescribeTransitGatewayConnectsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewayConnectsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewayConnectsOutcomeCallable EC2Client::DescribeTransitGatewayConnectsCallable(const DescribeTransitGatewayConnectsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewayConnectsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGatewayConnects(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewayConnectsAsync(const DescribeTransitGatewayConnectsRequest& request, const DescribeTransitGatewayConnectsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGatewayConnects(request), context);
    } );
}

DescribeTransitGatewayMulticastDomainsOutcome EC2Client::DescribeTransitGatewayMulticastDomains(const DescribeTransitGatewayMulticastDomainsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewayMulticastDomainsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewayMulticastDomainsOutcomeCallable EC2Client::DescribeTransitGatewayMulticastDomainsCallable(const DescribeTransitGatewayMulticastDomainsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewayMulticastDomainsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGatewayMulticastDomains(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewayMulticastDomainsAsync(const DescribeTransitGatewayMulticastDomainsRequest& request, const DescribeTransitGatewayMulticastDomainsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGatewayMulticastDomains(request), context);
    } );
}

DescribeTransitGatewayPeeringAttachmentsOutcome EC2Client::DescribeTransitGatewayPeeringAttachments(const DescribeTransitGatewayPeeringAttachmentsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewayPeeringAttachmentsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewayPeeringAttachmentsOutcomeCallable EC2Client::DescribeTransitGatewayPeeringAttachmentsCallable(const DescribeTransitGatewayPeeringAttachmentsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewayPeeringAttachmentsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGatewayPeeringAttachments(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewayPeeringAttachmentsAsync(const DescribeTransitGatewayPeeringAttachmentsRequest& request, const DescribeTransitGatewayPeeringAttachmentsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGatewayPeeringAttachments(request), context);
    } );
}

DescribeTransitGatewayPolicyTablesOutcome EC2Client::DescribeTransitGatewayPolicyTables(const DescribeTransitGatewayPolicyTablesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewayPolicyTablesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewayPolicyTablesOutcomeCallable EC2Client::DescribeTransitGatewayPolicyTablesCallable(const DescribeTransitGatewayPolicyTablesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewayPolicyTablesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGatewayPolicyTables(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewayPolicyTablesAsync(const DescribeTransitGatewayPolicyTablesRequest& request, const DescribeTransitGatewayPolicyTablesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGatewayPolicyTables(request), context);
    } );
}

DescribeTransitGatewayRouteTableAnnouncementsOutcome EC2Client::DescribeTransitGatewayRouteTableAnnouncements(const DescribeTransitGatewayRouteTableAnnouncementsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewayRouteTableAnnouncementsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewayRouteTableAnnouncementsOutcomeCallable EC2Client::DescribeTransitGatewayRouteTableAnnouncementsCallable(const DescribeTransitGatewayRouteTableAnnouncementsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewayRouteTableAnnouncementsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGatewayRouteTableAnnouncements(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewayRouteTableAnnouncementsAsync(const DescribeTransitGatewayRouteTableAnnouncementsRequest& request, const DescribeTransitGatewayRouteTableAnnouncementsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGatewayRouteTableAnnouncements(request), context);
    } );
}

DescribeTransitGatewayRouteTablesOutcome EC2Client::DescribeTransitGatewayRouteTables(const DescribeTransitGatewayRouteTablesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewayRouteTablesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewayRouteTablesOutcomeCallable EC2Client::DescribeTransitGatewayRouteTablesCallable(const DescribeTransitGatewayRouteTablesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewayRouteTablesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGatewayRouteTables(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewayRouteTablesAsync(const DescribeTransitGatewayRouteTablesRequest& request, const DescribeTransitGatewayRouteTablesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGatewayRouteTables(request), context);
    } );
}

DescribeTransitGatewayVpcAttachmentsOutcome EC2Client::DescribeTransitGatewayVpcAttachments(const DescribeTransitGatewayVpcAttachmentsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewayVpcAttachmentsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewayVpcAttachmentsOutcomeCallable EC2Client::DescribeTransitGatewayVpcAttachmentsCallable(const DescribeTransitGatewayVpcAttachmentsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewayVpcAttachmentsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGatewayVpcAttachments(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewayVpcAttachmentsAsync(const DescribeTransitGatewayVpcAttachmentsRequest& request, const DescribeTransitGatewayVpcAttachmentsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGatewayVpcAttachments(request), context);
    } );
}

DescribeTransitGatewaysOutcome EC2Client::DescribeTransitGateways(const DescribeTransitGatewaysRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTransitGatewaysOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTransitGatewaysOutcomeCallable EC2Client::DescribeTransitGatewaysCallable(const DescribeTransitGatewaysRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTransitGatewaysOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTransitGateways(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTransitGatewaysAsync(const DescribeTransitGatewaysRequest& request, const DescribeTransitGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTransitGateways(request), context);
    } );
}

DescribeTrunkInterfaceAssociationsOutcome EC2Client::DescribeTrunkInterfaceAssociations(const DescribeTrunkInterfaceAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeTrunkInterfaceAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeTrunkInterfaceAssociationsOutcomeCallable EC2Client::DescribeTrunkInterfaceAssociationsCallable(const DescribeTrunkInterfaceAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeTrunkInterfaceAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeTrunkInterfaceAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeTrunkInterfaceAssociationsAsync(const DescribeTrunkInterfaceAssociationsRequest& request, const DescribeTrunkInterfaceAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeTrunkInterfaceAssociations(request), context);
    } );
}

DescribeVolumeAttributeOutcome EC2Client::DescribeVolumeAttribute(const DescribeVolumeAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVolumeAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVolumeAttributeOutcomeCallable EC2Client::DescribeVolumeAttributeCallable(const DescribeVolumeAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVolumeAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVolumeAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVolumeAttributeAsync(const DescribeVolumeAttributeRequest& request, const DescribeVolumeAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVolumeAttribute(request), context);
    } );
}

DescribeVolumeStatusOutcome EC2Client::DescribeVolumeStatus(const DescribeVolumeStatusRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVolumeStatusOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVolumeStatusOutcomeCallable EC2Client::DescribeVolumeStatusCallable(const DescribeVolumeStatusRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVolumeStatusOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVolumeStatus(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVolumeStatusAsync(const DescribeVolumeStatusRequest& request, const DescribeVolumeStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVolumeStatus(request), context);
    } );
}

DescribeVolumesOutcome EC2Client::DescribeVolumes(const DescribeVolumesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVolumesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVolumesOutcomeCallable EC2Client::DescribeVolumesCallable(const DescribeVolumesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVolumesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVolumes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVolumesAsync(const DescribeVolumesRequest& request, const DescribeVolumesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVolumes(request), context);
    } );
}

DescribeVolumesModificationsOutcome EC2Client::DescribeVolumesModifications(const DescribeVolumesModificationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVolumesModificationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVolumesModificationsOutcomeCallable EC2Client::DescribeVolumesModificationsCallable(const DescribeVolumesModificationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVolumesModificationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVolumesModifications(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVolumesModificationsAsync(const DescribeVolumesModificationsRequest& request, const DescribeVolumesModificationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVolumesModifications(request), context);
    } );
}

DescribeVpcAttributeOutcome EC2Client::DescribeVpcAttribute(const DescribeVpcAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcAttributeOutcomeCallable EC2Client::DescribeVpcAttributeCallable(const DescribeVpcAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcAttributeAsync(const DescribeVpcAttributeRequest& request, const DescribeVpcAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcAttribute(request), context);
    } );
}

DescribeVpcClassicLinkOutcome EC2Client::DescribeVpcClassicLink(const DescribeVpcClassicLinkRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcClassicLinkOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcClassicLinkOutcomeCallable EC2Client::DescribeVpcClassicLinkCallable(const DescribeVpcClassicLinkRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcClassicLinkOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcClassicLink(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcClassicLinkAsync(const DescribeVpcClassicLinkRequest& request, const DescribeVpcClassicLinkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcClassicLink(request), context);
    } );
}

DescribeVpcClassicLinkDnsSupportOutcome EC2Client::DescribeVpcClassicLinkDnsSupport(const DescribeVpcClassicLinkDnsSupportRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcClassicLinkDnsSupportOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcClassicLinkDnsSupportOutcomeCallable EC2Client::DescribeVpcClassicLinkDnsSupportCallable(const DescribeVpcClassicLinkDnsSupportRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcClassicLinkDnsSupportOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcClassicLinkDnsSupport(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcClassicLinkDnsSupportAsync(const DescribeVpcClassicLinkDnsSupportRequest& request, const DescribeVpcClassicLinkDnsSupportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcClassicLinkDnsSupport(request), context);
    } );
}

DescribeVpcEndpointConnectionNotificationsOutcome EC2Client::DescribeVpcEndpointConnectionNotifications(const DescribeVpcEndpointConnectionNotificationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcEndpointConnectionNotificationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcEndpointConnectionNotificationsOutcomeCallable EC2Client::DescribeVpcEndpointConnectionNotificationsCallable(const DescribeVpcEndpointConnectionNotificationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcEndpointConnectionNotificationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcEndpointConnectionNotifications(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcEndpointConnectionNotificationsAsync(const DescribeVpcEndpointConnectionNotificationsRequest& request, const DescribeVpcEndpointConnectionNotificationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcEndpointConnectionNotifications(request), context);
    } );
}

DescribeVpcEndpointConnectionsOutcome EC2Client::DescribeVpcEndpointConnections(const DescribeVpcEndpointConnectionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcEndpointConnectionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcEndpointConnectionsOutcomeCallable EC2Client::DescribeVpcEndpointConnectionsCallable(const DescribeVpcEndpointConnectionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcEndpointConnectionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcEndpointConnections(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcEndpointConnectionsAsync(const DescribeVpcEndpointConnectionsRequest& request, const DescribeVpcEndpointConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcEndpointConnections(request), context);
    } );
}

DescribeVpcEndpointServiceConfigurationsOutcome EC2Client::DescribeVpcEndpointServiceConfigurations(const DescribeVpcEndpointServiceConfigurationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcEndpointServiceConfigurationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcEndpointServiceConfigurationsOutcomeCallable EC2Client::DescribeVpcEndpointServiceConfigurationsCallable(const DescribeVpcEndpointServiceConfigurationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcEndpointServiceConfigurationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcEndpointServiceConfigurations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcEndpointServiceConfigurationsAsync(const DescribeVpcEndpointServiceConfigurationsRequest& request, const DescribeVpcEndpointServiceConfigurationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcEndpointServiceConfigurations(request), context);
    } );
}

DescribeVpcEndpointServicePermissionsOutcome EC2Client::DescribeVpcEndpointServicePermissions(const DescribeVpcEndpointServicePermissionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcEndpointServicePermissionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcEndpointServicePermissionsOutcomeCallable EC2Client::DescribeVpcEndpointServicePermissionsCallable(const DescribeVpcEndpointServicePermissionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcEndpointServicePermissionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcEndpointServicePermissions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcEndpointServicePermissionsAsync(const DescribeVpcEndpointServicePermissionsRequest& request, const DescribeVpcEndpointServicePermissionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcEndpointServicePermissions(request), context);
    } );
}

DescribeVpcEndpointServicesOutcome EC2Client::DescribeVpcEndpointServices(const DescribeVpcEndpointServicesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcEndpointServicesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcEndpointServicesOutcomeCallable EC2Client::DescribeVpcEndpointServicesCallable(const DescribeVpcEndpointServicesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcEndpointServicesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcEndpointServices(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcEndpointServicesAsync(const DescribeVpcEndpointServicesRequest& request, const DescribeVpcEndpointServicesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcEndpointServices(request), context);
    } );
}

DescribeVpcEndpointsOutcome EC2Client::DescribeVpcEndpoints(const DescribeVpcEndpointsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcEndpointsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcEndpointsOutcomeCallable EC2Client::DescribeVpcEndpointsCallable(const DescribeVpcEndpointsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcEndpointsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcEndpoints(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcEndpointsAsync(const DescribeVpcEndpointsRequest& request, const DescribeVpcEndpointsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcEndpoints(request), context);
    } );
}

DescribeVpcPeeringConnectionsOutcome EC2Client::DescribeVpcPeeringConnections(const DescribeVpcPeeringConnectionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcPeeringConnectionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcPeeringConnectionsOutcomeCallable EC2Client::DescribeVpcPeeringConnectionsCallable(const DescribeVpcPeeringConnectionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcPeeringConnectionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcPeeringConnections(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcPeeringConnectionsAsync(const DescribeVpcPeeringConnectionsRequest& request, const DescribeVpcPeeringConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcPeeringConnections(request), context);
    } );
}

DescribeVpcsOutcome EC2Client::DescribeVpcs(const DescribeVpcsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpcsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpcsOutcomeCallable EC2Client::DescribeVpcsCallable(const DescribeVpcsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpcsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpcs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpcsAsync(const DescribeVpcsRequest& request, const DescribeVpcsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpcs(request), context);
    } );
}

DescribeVpnConnectionsOutcome EC2Client::DescribeVpnConnections(const DescribeVpnConnectionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpnConnectionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpnConnectionsOutcomeCallable EC2Client::DescribeVpnConnectionsCallable(const DescribeVpnConnectionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpnConnectionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpnConnections(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpnConnectionsAsync(const DescribeVpnConnectionsRequest& request, const DescribeVpnConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpnConnections(request), context);
    } );
}

DescribeVpnGatewaysOutcome EC2Client::DescribeVpnGateways(const DescribeVpnGatewaysRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DescribeVpnGatewaysOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DescribeVpnGatewaysOutcomeCallable EC2Client::DescribeVpnGatewaysCallable(const DescribeVpnGatewaysRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DescribeVpnGatewaysOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DescribeVpnGateways(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DescribeVpnGatewaysAsync(const DescribeVpnGatewaysRequest& request, const DescribeVpnGatewaysResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DescribeVpnGateways(request), context);
    } );
}

DetachClassicLinkVpcOutcome EC2Client::DetachClassicLinkVpc(const DetachClassicLinkVpcRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DetachClassicLinkVpcOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DetachClassicLinkVpcOutcomeCallable EC2Client::DetachClassicLinkVpcCallable(const DetachClassicLinkVpcRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DetachClassicLinkVpcOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DetachClassicLinkVpc(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DetachClassicLinkVpcAsync(const DetachClassicLinkVpcRequest& request, const DetachClassicLinkVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DetachClassicLinkVpc(request), context);
    } );
}

DetachInternetGatewayOutcome EC2Client::DetachInternetGateway(const DetachInternetGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DetachInternetGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DetachInternetGatewayOutcomeCallable EC2Client::DetachInternetGatewayCallable(const DetachInternetGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DetachInternetGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DetachInternetGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DetachInternetGatewayAsync(const DetachInternetGatewayRequest& request, const DetachInternetGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DetachInternetGateway(request), context);
    } );
}

DetachNetworkInterfaceOutcome EC2Client::DetachNetworkInterface(const DetachNetworkInterfaceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DetachNetworkInterfaceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DetachNetworkInterfaceOutcomeCallable EC2Client::DetachNetworkInterfaceCallable(const DetachNetworkInterfaceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DetachNetworkInterfaceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DetachNetworkInterface(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DetachNetworkInterfaceAsync(const DetachNetworkInterfaceRequest& request, const DetachNetworkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DetachNetworkInterface(request), context);
    } );
}

DetachVolumeOutcome EC2Client::DetachVolume(const DetachVolumeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DetachVolumeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DetachVolumeOutcomeCallable EC2Client::DetachVolumeCallable(const DetachVolumeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DetachVolumeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DetachVolume(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DetachVolumeAsync(const DetachVolumeRequest& request, const DetachVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DetachVolume(request), context);
    } );
}

DetachVpnGatewayOutcome EC2Client::DetachVpnGateway(const DetachVpnGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DetachVpnGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DetachVpnGatewayOutcomeCallable EC2Client::DetachVpnGatewayCallable(const DetachVpnGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DetachVpnGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DetachVpnGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DetachVpnGatewayAsync(const DetachVpnGatewayRequest& request, const DetachVpnGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DetachVpnGateway(request), context);
    } );
}

DisableEbsEncryptionByDefaultOutcome EC2Client::DisableEbsEncryptionByDefault(const DisableEbsEncryptionByDefaultRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableEbsEncryptionByDefaultOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableEbsEncryptionByDefaultOutcomeCallable EC2Client::DisableEbsEncryptionByDefaultCallable(const DisableEbsEncryptionByDefaultRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableEbsEncryptionByDefaultOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableEbsEncryptionByDefault(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableEbsEncryptionByDefaultAsync(const DisableEbsEncryptionByDefaultRequest& request, const DisableEbsEncryptionByDefaultResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableEbsEncryptionByDefault(request), context);
    } );
}

DisableFastLaunchOutcome EC2Client::DisableFastLaunch(const DisableFastLaunchRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableFastLaunchOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableFastLaunchOutcomeCallable EC2Client::DisableFastLaunchCallable(const DisableFastLaunchRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableFastLaunchOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableFastLaunch(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableFastLaunchAsync(const DisableFastLaunchRequest& request, const DisableFastLaunchResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableFastLaunch(request), context);
    } );
}

DisableFastSnapshotRestoresOutcome EC2Client::DisableFastSnapshotRestores(const DisableFastSnapshotRestoresRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableFastSnapshotRestoresOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableFastSnapshotRestoresOutcomeCallable EC2Client::DisableFastSnapshotRestoresCallable(const DisableFastSnapshotRestoresRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableFastSnapshotRestoresOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableFastSnapshotRestores(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableFastSnapshotRestoresAsync(const DisableFastSnapshotRestoresRequest& request, const DisableFastSnapshotRestoresResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableFastSnapshotRestores(request), context);
    } );
}

DisableImageDeprecationOutcome EC2Client::DisableImageDeprecation(const DisableImageDeprecationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableImageDeprecationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableImageDeprecationOutcomeCallable EC2Client::DisableImageDeprecationCallable(const DisableImageDeprecationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableImageDeprecationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableImageDeprecation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableImageDeprecationAsync(const DisableImageDeprecationRequest& request, const DisableImageDeprecationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableImageDeprecation(request), context);
    } );
}

DisableIpamOrganizationAdminAccountOutcome EC2Client::DisableIpamOrganizationAdminAccount(const DisableIpamOrganizationAdminAccountRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableIpamOrganizationAdminAccountOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableIpamOrganizationAdminAccountOutcomeCallable EC2Client::DisableIpamOrganizationAdminAccountCallable(const DisableIpamOrganizationAdminAccountRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableIpamOrganizationAdminAccountOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableIpamOrganizationAdminAccount(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableIpamOrganizationAdminAccountAsync(const DisableIpamOrganizationAdminAccountRequest& request, const DisableIpamOrganizationAdminAccountResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableIpamOrganizationAdminAccount(request), context);
    } );
}

DisableSerialConsoleAccessOutcome EC2Client::DisableSerialConsoleAccess(const DisableSerialConsoleAccessRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableSerialConsoleAccessOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableSerialConsoleAccessOutcomeCallable EC2Client::DisableSerialConsoleAccessCallable(const DisableSerialConsoleAccessRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableSerialConsoleAccessOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableSerialConsoleAccess(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableSerialConsoleAccessAsync(const DisableSerialConsoleAccessRequest& request, const DisableSerialConsoleAccessResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableSerialConsoleAccess(request), context);
    } );
}

DisableTransitGatewayRouteTablePropagationOutcome EC2Client::DisableTransitGatewayRouteTablePropagation(const DisableTransitGatewayRouteTablePropagationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableTransitGatewayRouteTablePropagationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableTransitGatewayRouteTablePropagationOutcomeCallable EC2Client::DisableTransitGatewayRouteTablePropagationCallable(const DisableTransitGatewayRouteTablePropagationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableTransitGatewayRouteTablePropagationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableTransitGatewayRouteTablePropagation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableTransitGatewayRouteTablePropagationAsync(const DisableTransitGatewayRouteTablePropagationRequest& request, const DisableTransitGatewayRouteTablePropagationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableTransitGatewayRouteTablePropagation(request), context);
    } );
}

DisableVgwRoutePropagationOutcome EC2Client::DisableVgwRoutePropagation(const DisableVgwRoutePropagationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableVgwRoutePropagationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableVgwRoutePropagationOutcomeCallable EC2Client::DisableVgwRoutePropagationCallable(const DisableVgwRoutePropagationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableVgwRoutePropagationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableVgwRoutePropagation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableVgwRoutePropagationAsync(const DisableVgwRoutePropagationRequest& request, const DisableVgwRoutePropagationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableVgwRoutePropagation(request), context);
    } );
}

DisableVpcClassicLinkOutcome EC2Client::DisableVpcClassicLink(const DisableVpcClassicLinkRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableVpcClassicLinkOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableVpcClassicLinkOutcomeCallable EC2Client::DisableVpcClassicLinkCallable(const DisableVpcClassicLinkRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableVpcClassicLinkOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableVpcClassicLink(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableVpcClassicLinkAsync(const DisableVpcClassicLinkRequest& request, const DisableVpcClassicLinkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableVpcClassicLink(request), context);
    } );
}

DisableVpcClassicLinkDnsSupportOutcome EC2Client::DisableVpcClassicLinkDnsSupport(const DisableVpcClassicLinkDnsSupportRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisableVpcClassicLinkDnsSupportOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisableVpcClassicLinkDnsSupportOutcomeCallable EC2Client::DisableVpcClassicLinkDnsSupportCallable(const DisableVpcClassicLinkDnsSupportRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisableVpcClassicLinkDnsSupportOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisableVpcClassicLinkDnsSupport(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisableVpcClassicLinkDnsSupportAsync(const DisableVpcClassicLinkDnsSupportRequest& request, const DisableVpcClassicLinkDnsSupportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisableVpcClassicLinkDnsSupport(request), context);
    } );
}

DisassociateAddressOutcome EC2Client::DisassociateAddress(const DisassociateAddressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateAddressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateAddressOutcomeCallable EC2Client::DisassociateAddressCallable(const DisassociateAddressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateAddressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateAddress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateAddressAsync(const DisassociateAddressRequest& request, const DisassociateAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateAddress(request), context);
    } );
}

DisassociateClientVpnTargetNetworkOutcome EC2Client::DisassociateClientVpnTargetNetwork(const DisassociateClientVpnTargetNetworkRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateClientVpnTargetNetworkOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateClientVpnTargetNetworkOutcomeCallable EC2Client::DisassociateClientVpnTargetNetworkCallable(const DisassociateClientVpnTargetNetworkRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateClientVpnTargetNetworkOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateClientVpnTargetNetwork(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateClientVpnTargetNetworkAsync(const DisassociateClientVpnTargetNetworkRequest& request, const DisassociateClientVpnTargetNetworkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateClientVpnTargetNetwork(request), context);
    } );
}

DisassociateEnclaveCertificateIamRoleOutcome EC2Client::DisassociateEnclaveCertificateIamRole(const DisassociateEnclaveCertificateIamRoleRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateEnclaveCertificateIamRoleOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateEnclaveCertificateIamRoleOutcomeCallable EC2Client::DisassociateEnclaveCertificateIamRoleCallable(const DisassociateEnclaveCertificateIamRoleRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateEnclaveCertificateIamRoleOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateEnclaveCertificateIamRole(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateEnclaveCertificateIamRoleAsync(const DisassociateEnclaveCertificateIamRoleRequest& request, const DisassociateEnclaveCertificateIamRoleResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateEnclaveCertificateIamRole(request), context);
    } );
}

DisassociateIamInstanceProfileOutcome EC2Client::DisassociateIamInstanceProfile(const DisassociateIamInstanceProfileRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateIamInstanceProfileOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateIamInstanceProfileOutcomeCallable EC2Client::DisassociateIamInstanceProfileCallable(const DisassociateIamInstanceProfileRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateIamInstanceProfileOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateIamInstanceProfile(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateIamInstanceProfileAsync(const DisassociateIamInstanceProfileRequest& request, const DisassociateIamInstanceProfileResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateIamInstanceProfile(request), context);
    } );
}

DisassociateInstanceEventWindowOutcome EC2Client::DisassociateInstanceEventWindow(const DisassociateInstanceEventWindowRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateInstanceEventWindowOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateInstanceEventWindowOutcomeCallable EC2Client::DisassociateInstanceEventWindowCallable(const DisassociateInstanceEventWindowRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateInstanceEventWindowOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateInstanceEventWindow(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateInstanceEventWindowAsync(const DisassociateInstanceEventWindowRequest& request, const DisassociateInstanceEventWindowResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateInstanceEventWindow(request), context);
    } );
}

DisassociateRouteTableOutcome EC2Client::DisassociateRouteTable(const DisassociateRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateRouteTableOutcomeCallable EC2Client::DisassociateRouteTableCallable(const DisassociateRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateRouteTableAsync(const DisassociateRouteTableRequest& request, const DisassociateRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateRouteTable(request), context);
    } );
}

DisassociateSubnetCidrBlockOutcome EC2Client::DisassociateSubnetCidrBlock(const DisassociateSubnetCidrBlockRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateSubnetCidrBlockOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateSubnetCidrBlockOutcomeCallable EC2Client::DisassociateSubnetCidrBlockCallable(const DisassociateSubnetCidrBlockRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateSubnetCidrBlockOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateSubnetCidrBlock(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateSubnetCidrBlockAsync(const DisassociateSubnetCidrBlockRequest& request, const DisassociateSubnetCidrBlockResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateSubnetCidrBlock(request), context);
    } );
}

DisassociateTransitGatewayMulticastDomainOutcome EC2Client::DisassociateTransitGatewayMulticastDomain(const DisassociateTransitGatewayMulticastDomainRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateTransitGatewayMulticastDomainOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateTransitGatewayMulticastDomainOutcomeCallable EC2Client::DisassociateTransitGatewayMulticastDomainCallable(const DisassociateTransitGatewayMulticastDomainRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateTransitGatewayMulticastDomainOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateTransitGatewayMulticastDomain(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateTransitGatewayMulticastDomainAsync(const DisassociateTransitGatewayMulticastDomainRequest& request, const DisassociateTransitGatewayMulticastDomainResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateTransitGatewayMulticastDomain(request), context);
    } );
}

DisassociateTransitGatewayPolicyTableOutcome EC2Client::DisassociateTransitGatewayPolicyTable(const DisassociateTransitGatewayPolicyTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateTransitGatewayPolicyTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateTransitGatewayPolicyTableOutcomeCallable EC2Client::DisassociateTransitGatewayPolicyTableCallable(const DisassociateTransitGatewayPolicyTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateTransitGatewayPolicyTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateTransitGatewayPolicyTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateTransitGatewayPolicyTableAsync(const DisassociateTransitGatewayPolicyTableRequest& request, const DisassociateTransitGatewayPolicyTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateTransitGatewayPolicyTable(request), context);
    } );
}

DisassociateTransitGatewayRouteTableOutcome EC2Client::DisassociateTransitGatewayRouteTable(const DisassociateTransitGatewayRouteTableRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateTransitGatewayRouteTableOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateTransitGatewayRouteTableOutcomeCallable EC2Client::DisassociateTransitGatewayRouteTableCallable(const DisassociateTransitGatewayRouteTableRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateTransitGatewayRouteTableOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateTransitGatewayRouteTable(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateTransitGatewayRouteTableAsync(const DisassociateTransitGatewayRouteTableRequest& request, const DisassociateTransitGatewayRouteTableResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateTransitGatewayRouteTable(request), context);
    } );
}

DisassociateTrunkInterfaceOutcome EC2Client::DisassociateTrunkInterface(const DisassociateTrunkInterfaceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateTrunkInterfaceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateTrunkInterfaceOutcomeCallable EC2Client::DisassociateTrunkInterfaceCallable(const DisassociateTrunkInterfaceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateTrunkInterfaceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateTrunkInterface(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateTrunkInterfaceAsync(const DisassociateTrunkInterfaceRequest& request, const DisassociateTrunkInterfaceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateTrunkInterface(request), context);
    } );
}

DisassociateVpcCidrBlockOutcome EC2Client::DisassociateVpcCidrBlock(const DisassociateVpcCidrBlockRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return DisassociateVpcCidrBlockOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

DisassociateVpcCidrBlockOutcomeCallable EC2Client::DisassociateVpcCidrBlockCallable(const DisassociateVpcCidrBlockRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< DisassociateVpcCidrBlockOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->DisassociateVpcCidrBlock(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::DisassociateVpcCidrBlockAsync(const DisassociateVpcCidrBlockRequest& request, const DisassociateVpcCidrBlockResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, DisassociateVpcCidrBlock(request), context);
    } );
}

EnableEbsEncryptionByDefaultOutcome EC2Client::EnableEbsEncryptionByDefault(const EnableEbsEncryptionByDefaultRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableEbsEncryptionByDefaultOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableEbsEncryptionByDefaultOutcomeCallable EC2Client::EnableEbsEncryptionByDefaultCallable(const EnableEbsEncryptionByDefaultRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableEbsEncryptionByDefaultOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableEbsEncryptionByDefault(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableEbsEncryptionByDefaultAsync(const EnableEbsEncryptionByDefaultRequest& request, const EnableEbsEncryptionByDefaultResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableEbsEncryptionByDefault(request), context);
    } );
}

EnableFastLaunchOutcome EC2Client::EnableFastLaunch(const EnableFastLaunchRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableFastLaunchOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableFastLaunchOutcomeCallable EC2Client::EnableFastLaunchCallable(const EnableFastLaunchRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableFastLaunchOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableFastLaunch(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableFastLaunchAsync(const EnableFastLaunchRequest& request, const EnableFastLaunchResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableFastLaunch(request), context);
    } );
}

EnableFastSnapshotRestoresOutcome EC2Client::EnableFastSnapshotRestores(const EnableFastSnapshotRestoresRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableFastSnapshotRestoresOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableFastSnapshotRestoresOutcomeCallable EC2Client::EnableFastSnapshotRestoresCallable(const EnableFastSnapshotRestoresRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableFastSnapshotRestoresOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableFastSnapshotRestores(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableFastSnapshotRestoresAsync(const EnableFastSnapshotRestoresRequest& request, const EnableFastSnapshotRestoresResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableFastSnapshotRestores(request), context);
    } );
}

EnableImageDeprecationOutcome EC2Client::EnableImageDeprecation(const EnableImageDeprecationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableImageDeprecationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableImageDeprecationOutcomeCallable EC2Client::EnableImageDeprecationCallable(const EnableImageDeprecationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableImageDeprecationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableImageDeprecation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableImageDeprecationAsync(const EnableImageDeprecationRequest& request, const EnableImageDeprecationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableImageDeprecation(request), context);
    } );
}

EnableIpamOrganizationAdminAccountOutcome EC2Client::EnableIpamOrganizationAdminAccount(const EnableIpamOrganizationAdminAccountRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableIpamOrganizationAdminAccountOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableIpamOrganizationAdminAccountOutcomeCallable EC2Client::EnableIpamOrganizationAdminAccountCallable(const EnableIpamOrganizationAdminAccountRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableIpamOrganizationAdminAccountOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableIpamOrganizationAdminAccount(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableIpamOrganizationAdminAccountAsync(const EnableIpamOrganizationAdminAccountRequest& request, const EnableIpamOrganizationAdminAccountResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableIpamOrganizationAdminAccount(request), context);
    } );
}

EnableSerialConsoleAccessOutcome EC2Client::EnableSerialConsoleAccess(const EnableSerialConsoleAccessRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableSerialConsoleAccessOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableSerialConsoleAccessOutcomeCallable EC2Client::EnableSerialConsoleAccessCallable(const EnableSerialConsoleAccessRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableSerialConsoleAccessOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableSerialConsoleAccess(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableSerialConsoleAccessAsync(const EnableSerialConsoleAccessRequest& request, const EnableSerialConsoleAccessResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableSerialConsoleAccess(request), context);
    } );
}

EnableTransitGatewayRouteTablePropagationOutcome EC2Client::EnableTransitGatewayRouteTablePropagation(const EnableTransitGatewayRouteTablePropagationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableTransitGatewayRouteTablePropagationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableTransitGatewayRouteTablePropagationOutcomeCallable EC2Client::EnableTransitGatewayRouteTablePropagationCallable(const EnableTransitGatewayRouteTablePropagationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableTransitGatewayRouteTablePropagationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableTransitGatewayRouteTablePropagation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableTransitGatewayRouteTablePropagationAsync(const EnableTransitGatewayRouteTablePropagationRequest& request, const EnableTransitGatewayRouteTablePropagationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableTransitGatewayRouteTablePropagation(request), context);
    } );
}

EnableVgwRoutePropagationOutcome EC2Client::EnableVgwRoutePropagation(const EnableVgwRoutePropagationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableVgwRoutePropagationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableVgwRoutePropagationOutcomeCallable EC2Client::EnableVgwRoutePropagationCallable(const EnableVgwRoutePropagationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableVgwRoutePropagationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableVgwRoutePropagation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableVgwRoutePropagationAsync(const EnableVgwRoutePropagationRequest& request, const EnableVgwRoutePropagationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableVgwRoutePropagation(request), context);
    } );
}

EnableVolumeIOOutcome EC2Client::EnableVolumeIO(const EnableVolumeIORequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableVolumeIOOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableVolumeIOOutcomeCallable EC2Client::EnableVolumeIOCallable(const EnableVolumeIORequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableVolumeIOOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableVolumeIO(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableVolumeIOAsync(const EnableVolumeIORequest& request, const EnableVolumeIOResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableVolumeIO(request), context);
    } );
}

EnableVpcClassicLinkOutcome EC2Client::EnableVpcClassicLink(const EnableVpcClassicLinkRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableVpcClassicLinkOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableVpcClassicLinkOutcomeCallable EC2Client::EnableVpcClassicLinkCallable(const EnableVpcClassicLinkRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableVpcClassicLinkOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableVpcClassicLink(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableVpcClassicLinkAsync(const EnableVpcClassicLinkRequest& request, const EnableVpcClassicLinkResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableVpcClassicLink(request), context);
    } );
}

EnableVpcClassicLinkDnsSupportOutcome EC2Client::EnableVpcClassicLinkDnsSupport(const EnableVpcClassicLinkDnsSupportRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return EnableVpcClassicLinkDnsSupportOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

EnableVpcClassicLinkDnsSupportOutcomeCallable EC2Client::EnableVpcClassicLinkDnsSupportCallable(const EnableVpcClassicLinkDnsSupportRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< EnableVpcClassicLinkDnsSupportOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->EnableVpcClassicLinkDnsSupport(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::EnableVpcClassicLinkDnsSupportAsync(const EnableVpcClassicLinkDnsSupportRequest& request, const EnableVpcClassicLinkDnsSupportResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, EnableVpcClassicLinkDnsSupport(request), context);
    } );
}

ExportClientVpnClientCertificateRevocationListOutcome EC2Client::ExportClientVpnClientCertificateRevocationList(const ExportClientVpnClientCertificateRevocationListRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ExportClientVpnClientCertificateRevocationListOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ExportClientVpnClientCertificateRevocationListOutcomeCallable EC2Client::ExportClientVpnClientCertificateRevocationListCallable(const ExportClientVpnClientCertificateRevocationListRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ExportClientVpnClientCertificateRevocationListOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ExportClientVpnClientCertificateRevocationList(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ExportClientVpnClientCertificateRevocationListAsync(const ExportClientVpnClientCertificateRevocationListRequest& request, const ExportClientVpnClientCertificateRevocationListResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ExportClientVpnClientCertificateRevocationList(request), context);
    } );
}

ExportClientVpnClientConfigurationOutcome EC2Client::ExportClientVpnClientConfiguration(const ExportClientVpnClientConfigurationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ExportClientVpnClientConfigurationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ExportClientVpnClientConfigurationOutcomeCallable EC2Client::ExportClientVpnClientConfigurationCallable(const ExportClientVpnClientConfigurationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ExportClientVpnClientConfigurationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ExportClientVpnClientConfiguration(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ExportClientVpnClientConfigurationAsync(const ExportClientVpnClientConfigurationRequest& request, const ExportClientVpnClientConfigurationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ExportClientVpnClientConfiguration(request), context);
    } );
}

ExportImageOutcome EC2Client::ExportImage(const ExportImageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ExportImageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ExportImageOutcomeCallable EC2Client::ExportImageCallable(const ExportImageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ExportImageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ExportImage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ExportImageAsync(const ExportImageRequest& request, const ExportImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ExportImage(request), context);
    } );
}

ExportTransitGatewayRoutesOutcome EC2Client::ExportTransitGatewayRoutes(const ExportTransitGatewayRoutesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ExportTransitGatewayRoutesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ExportTransitGatewayRoutesOutcomeCallable EC2Client::ExportTransitGatewayRoutesCallable(const ExportTransitGatewayRoutesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ExportTransitGatewayRoutesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ExportTransitGatewayRoutes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ExportTransitGatewayRoutesAsync(const ExportTransitGatewayRoutesRequest& request, const ExportTransitGatewayRoutesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ExportTransitGatewayRoutes(request), context);
    } );
}

GetAssociatedEnclaveCertificateIamRolesOutcome EC2Client::GetAssociatedEnclaveCertificateIamRoles(const GetAssociatedEnclaveCertificateIamRolesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetAssociatedEnclaveCertificateIamRolesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetAssociatedEnclaveCertificateIamRolesOutcomeCallable EC2Client::GetAssociatedEnclaveCertificateIamRolesCallable(const GetAssociatedEnclaveCertificateIamRolesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetAssociatedEnclaveCertificateIamRolesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetAssociatedEnclaveCertificateIamRoles(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetAssociatedEnclaveCertificateIamRolesAsync(const GetAssociatedEnclaveCertificateIamRolesRequest& request, const GetAssociatedEnclaveCertificateIamRolesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetAssociatedEnclaveCertificateIamRoles(request), context);
    } );
}

GetAssociatedIpv6PoolCidrsOutcome EC2Client::GetAssociatedIpv6PoolCidrs(const GetAssociatedIpv6PoolCidrsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetAssociatedIpv6PoolCidrsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetAssociatedIpv6PoolCidrsOutcomeCallable EC2Client::GetAssociatedIpv6PoolCidrsCallable(const GetAssociatedIpv6PoolCidrsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetAssociatedIpv6PoolCidrsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetAssociatedIpv6PoolCidrs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetAssociatedIpv6PoolCidrsAsync(const GetAssociatedIpv6PoolCidrsRequest& request, const GetAssociatedIpv6PoolCidrsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetAssociatedIpv6PoolCidrs(request), context);
    } );
}

GetCapacityReservationUsageOutcome EC2Client::GetCapacityReservationUsage(const GetCapacityReservationUsageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetCapacityReservationUsageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetCapacityReservationUsageOutcomeCallable EC2Client::GetCapacityReservationUsageCallable(const GetCapacityReservationUsageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetCapacityReservationUsageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetCapacityReservationUsage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetCapacityReservationUsageAsync(const GetCapacityReservationUsageRequest& request, const GetCapacityReservationUsageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetCapacityReservationUsage(request), context);
    } );
}

GetCoipPoolUsageOutcome EC2Client::GetCoipPoolUsage(const GetCoipPoolUsageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetCoipPoolUsageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetCoipPoolUsageOutcomeCallable EC2Client::GetCoipPoolUsageCallable(const GetCoipPoolUsageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetCoipPoolUsageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetCoipPoolUsage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetCoipPoolUsageAsync(const GetCoipPoolUsageRequest& request, const GetCoipPoolUsageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetCoipPoolUsage(request), context);
    } );
}

GetConsoleOutputOutcome EC2Client::GetConsoleOutput(const GetConsoleOutputRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetConsoleOutputOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetConsoleOutputOutcomeCallable EC2Client::GetConsoleOutputCallable(const GetConsoleOutputRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetConsoleOutputOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetConsoleOutput(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetConsoleOutputAsync(const GetConsoleOutputRequest& request, const GetConsoleOutputResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetConsoleOutput(request), context);
    } );
}

GetConsoleScreenshotOutcome EC2Client::GetConsoleScreenshot(const GetConsoleScreenshotRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetConsoleScreenshotOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetConsoleScreenshotOutcomeCallable EC2Client::GetConsoleScreenshotCallable(const GetConsoleScreenshotRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetConsoleScreenshotOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetConsoleScreenshot(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetConsoleScreenshotAsync(const GetConsoleScreenshotRequest& request, const GetConsoleScreenshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetConsoleScreenshot(request), context);
    } );
}

GetDefaultCreditSpecificationOutcome EC2Client::GetDefaultCreditSpecification(const GetDefaultCreditSpecificationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetDefaultCreditSpecificationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetDefaultCreditSpecificationOutcomeCallable EC2Client::GetDefaultCreditSpecificationCallable(const GetDefaultCreditSpecificationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetDefaultCreditSpecificationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetDefaultCreditSpecification(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetDefaultCreditSpecificationAsync(const GetDefaultCreditSpecificationRequest& request, const GetDefaultCreditSpecificationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetDefaultCreditSpecification(request), context);
    } );
}

GetEbsDefaultKmsKeyIdOutcome EC2Client::GetEbsDefaultKmsKeyId(const GetEbsDefaultKmsKeyIdRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetEbsDefaultKmsKeyIdOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetEbsDefaultKmsKeyIdOutcomeCallable EC2Client::GetEbsDefaultKmsKeyIdCallable(const GetEbsDefaultKmsKeyIdRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetEbsDefaultKmsKeyIdOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetEbsDefaultKmsKeyId(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetEbsDefaultKmsKeyIdAsync(const GetEbsDefaultKmsKeyIdRequest& request, const GetEbsDefaultKmsKeyIdResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetEbsDefaultKmsKeyId(request), context);
    } );
}

GetEbsEncryptionByDefaultOutcome EC2Client::GetEbsEncryptionByDefault(const GetEbsEncryptionByDefaultRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetEbsEncryptionByDefaultOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetEbsEncryptionByDefaultOutcomeCallable EC2Client::GetEbsEncryptionByDefaultCallable(const GetEbsEncryptionByDefaultRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetEbsEncryptionByDefaultOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetEbsEncryptionByDefault(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetEbsEncryptionByDefaultAsync(const GetEbsEncryptionByDefaultRequest& request, const GetEbsEncryptionByDefaultResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetEbsEncryptionByDefault(request), context);
    } );
}

GetFlowLogsIntegrationTemplateOutcome EC2Client::GetFlowLogsIntegrationTemplate(const GetFlowLogsIntegrationTemplateRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetFlowLogsIntegrationTemplateOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetFlowLogsIntegrationTemplateOutcomeCallable EC2Client::GetFlowLogsIntegrationTemplateCallable(const GetFlowLogsIntegrationTemplateRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetFlowLogsIntegrationTemplateOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetFlowLogsIntegrationTemplate(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetFlowLogsIntegrationTemplateAsync(const GetFlowLogsIntegrationTemplateRequest& request, const GetFlowLogsIntegrationTemplateResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetFlowLogsIntegrationTemplate(request), context);
    } );
}

GetGroupsForCapacityReservationOutcome EC2Client::GetGroupsForCapacityReservation(const GetGroupsForCapacityReservationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetGroupsForCapacityReservationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetGroupsForCapacityReservationOutcomeCallable EC2Client::GetGroupsForCapacityReservationCallable(const GetGroupsForCapacityReservationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetGroupsForCapacityReservationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetGroupsForCapacityReservation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetGroupsForCapacityReservationAsync(const GetGroupsForCapacityReservationRequest& request, const GetGroupsForCapacityReservationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetGroupsForCapacityReservation(request), context);
    } );
}

GetHostReservationPurchasePreviewOutcome EC2Client::GetHostReservationPurchasePreview(const GetHostReservationPurchasePreviewRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetHostReservationPurchasePreviewOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetHostReservationPurchasePreviewOutcomeCallable EC2Client::GetHostReservationPurchasePreviewCallable(const GetHostReservationPurchasePreviewRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetHostReservationPurchasePreviewOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetHostReservationPurchasePreview(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetHostReservationPurchasePreviewAsync(const GetHostReservationPurchasePreviewRequest& request, const GetHostReservationPurchasePreviewResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetHostReservationPurchasePreview(request), context);
    } );
}

GetInstanceTypesFromInstanceRequirementsOutcome EC2Client::GetInstanceTypesFromInstanceRequirements(const GetInstanceTypesFromInstanceRequirementsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetInstanceTypesFromInstanceRequirementsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetInstanceTypesFromInstanceRequirementsOutcomeCallable EC2Client::GetInstanceTypesFromInstanceRequirementsCallable(const GetInstanceTypesFromInstanceRequirementsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetInstanceTypesFromInstanceRequirementsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetInstanceTypesFromInstanceRequirements(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetInstanceTypesFromInstanceRequirementsAsync(const GetInstanceTypesFromInstanceRequirementsRequest& request, const GetInstanceTypesFromInstanceRequirementsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetInstanceTypesFromInstanceRequirements(request), context);
    } );
}

GetInstanceUefiDataOutcome EC2Client::GetInstanceUefiData(const GetInstanceUefiDataRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetInstanceUefiDataOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetInstanceUefiDataOutcomeCallable EC2Client::GetInstanceUefiDataCallable(const GetInstanceUefiDataRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetInstanceUefiDataOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetInstanceUefiData(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetInstanceUefiDataAsync(const GetInstanceUefiDataRequest& request, const GetInstanceUefiDataResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetInstanceUefiData(request), context);
    } );
}

GetIpamAddressHistoryOutcome EC2Client::GetIpamAddressHistory(const GetIpamAddressHistoryRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetIpamAddressHistoryOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetIpamAddressHistoryOutcomeCallable EC2Client::GetIpamAddressHistoryCallable(const GetIpamAddressHistoryRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetIpamAddressHistoryOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetIpamAddressHistory(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetIpamAddressHistoryAsync(const GetIpamAddressHistoryRequest& request, const GetIpamAddressHistoryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetIpamAddressHistory(request), context);
    } );
}

GetIpamPoolAllocationsOutcome EC2Client::GetIpamPoolAllocations(const GetIpamPoolAllocationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetIpamPoolAllocationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetIpamPoolAllocationsOutcomeCallable EC2Client::GetIpamPoolAllocationsCallable(const GetIpamPoolAllocationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetIpamPoolAllocationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetIpamPoolAllocations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetIpamPoolAllocationsAsync(const GetIpamPoolAllocationsRequest& request, const GetIpamPoolAllocationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetIpamPoolAllocations(request), context);
    } );
}

GetIpamPoolCidrsOutcome EC2Client::GetIpamPoolCidrs(const GetIpamPoolCidrsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetIpamPoolCidrsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetIpamPoolCidrsOutcomeCallable EC2Client::GetIpamPoolCidrsCallable(const GetIpamPoolCidrsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetIpamPoolCidrsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetIpamPoolCidrs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetIpamPoolCidrsAsync(const GetIpamPoolCidrsRequest& request, const GetIpamPoolCidrsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetIpamPoolCidrs(request), context);
    } );
}

GetIpamResourceCidrsOutcome EC2Client::GetIpamResourceCidrs(const GetIpamResourceCidrsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetIpamResourceCidrsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetIpamResourceCidrsOutcomeCallable EC2Client::GetIpamResourceCidrsCallable(const GetIpamResourceCidrsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetIpamResourceCidrsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetIpamResourceCidrs(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetIpamResourceCidrsAsync(const GetIpamResourceCidrsRequest& request, const GetIpamResourceCidrsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetIpamResourceCidrs(request), context);
    } );
}

GetLaunchTemplateDataOutcome EC2Client::GetLaunchTemplateData(const GetLaunchTemplateDataRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetLaunchTemplateDataOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetLaunchTemplateDataOutcomeCallable EC2Client::GetLaunchTemplateDataCallable(const GetLaunchTemplateDataRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetLaunchTemplateDataOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetLaunchTemplateData(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetLaunchTemplateDataAsync(const GetLaunchTemplateDataRequest& request, const GetLaunchTemplateDataResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetLaunchTemplateData(request), context);
    } );
}

GetManagedPrefixListAssociationsOutcome EC2Client::GetManagedPrefixListAssociations(const GetManagedPrefixListAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetManagedPrefixListAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetManagedPrefixListAssociationsOutcomeCallable EC2Client::GetManagedPrefixListAssociationsCallable(const GetManagedPrefixListAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetManagedPrefixListAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetManagedPrefixListAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetManagedPrefixListAssociationsAsync(const GetManagedPrefixListAssociationsRequest& request, const GetManagedPrefixListAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetManagedPrefixListAssociations(request), context);
    } );
}

GetManagedPrefixListEntriesOutcome EC2Client::GetManagedPrefixListEntries(const GetManagedPrefixListEntriesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetManagedPrefixListEntriesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetManagedPrefixListEntriesOutcomeCallable EC2Client::GetManagedPrefixListEntriesCallable(const GetManagedPrefixListEntriesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetManagedPrefixListEntriesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetManagedPrefixListEntries(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetManagedPrefixListEntriesAsync(const GetManagedPrefixListEntriesRequest& request, const GetManagedPrefixListEntriesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetManagedPrefixListEntries(request), context);
    } );
}

GetNetworkInsightsAccessScopeAnalysisFindingsOutcome EC2Client::GetNetworkInsightsAccessScopeAnalysisFindings(const GetNetworkInsightsAccessScopeAnalysisFindingsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetNetworkInsightsAccessScopeAnalysisFindingsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetNetworkInsightsAccessScopeAnalysisFindingsOutcomeCallable EC2Client::GetNetworkInsightsAccessScopeAnalysisFindingsCallable(const GetNetworkInsightsAccessScopeAnalysisFindingsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetNetworkInsightsAccessScopeAnalysisFindingsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetNetworkInsightsAccessScopeAnalysisFindings(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetNetworkInsightsAccessScopeAnalysisFindingsAsync(const GetNetworkInsightsAccessScopeAnalysisFindingsRequest& request, const GetNetworkInsightsAccessScopeAnalysisFindingsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetNetworkInsightsAccessScopeAnalysisFindings(request), context);
    } );
}

GetNetworkInsightsAccessScopeContentOutcome EC2Client::GetNetworkInsightsAccessScopeContent(const GetNetworkInsightsAccessScopeContentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetNetworkInsightsAccessScopeContentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetNetworkInsightsAccessScopeContentOutcomeCallable EC2Client::GetNetworkInsightsAccessScopeContentCallable(const GetNetworkInsightsAccessScopeContentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetNetworkInsightsAccessScopeContentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetNetworkInsightsAccessScopeContent(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetNetworkInsightsAccessScopeContentAsync(const GetNetworkInsightsAccessScopeContentRequest& request, const GetNetworkInsightsAccessScopeContentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetNetworkInsightsAccessScopeContent(request), context);
    } );
}

GetPasswordDataOutcome EC2Client::GetPasswordData(const GetPasswordDataRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetPasswordDataOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetPasswordDataOutcomeCallable EC2Client::GetPasswordDataCallable(const GetPasswordDataRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetPasswordDataOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetPasswordData(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetPasswordDataAsync(const GetPasswordDataRequest& request, const GetPasswordDataResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetPasswordData(request), context);
    } );
}

GetReservedInstancesExchangeQuoteOutcome EC2Client::GetReservedInstancesExchangeQuote(const GetReservedInstancesExchangeQuoteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetReservedInstancesExchangeQuoteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetReservedInstancesExchangeQuoteOutcomeCallable EC2Client::GetReservedInstancesExchangeQuoteCallable(const GetReservedInstancesExchangeQuoteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetReservedInstancesExchangeQuoteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetReservedInstancesExchangeQuote(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetReservedInstancesExchangeQuoteAsync(const GetReservedInstancesExchangeQuoteRequest& request, const GetReservedInstancesExchangeQuoteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetReservedInstancesExchangeQuote(request), context);
    } );
}

GetSerialConsoleAccessStatusOutcome EC2Client::GetSerialConsoleAccessStatus(const GetSerialConsoleAccessStatusRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetSerialConsoleAccessStatusOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetSerialConsoleAccessStatusOutcomeCallable EC2Client::GetSerialConsoleAccessStatusCallable(const GetSerialConsoleAccessStatusRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetSerialConsoleAccessStatusOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetSerialConsoleAccessStatus(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetSerialConsoleAccessStatusAsync(const GetSerialConsoleAccessStatusRequest& request, const GetSerialConsoleAccessStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetSerialConsoleAccessStatus(request), context);
    } );
}

GetSpotPlacementScoresOutcome EC2Client::GetSpotPlacementScores(const GetSpotPlacementScoresRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetSpotPlacementScoresOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetSpotPlacementScoresOutcomeCallable EC2Client::GetSpotPlacementScoresCallable(const GetSpotPlacementScoresRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetSpotPlacementScoresOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetSpotPlacementScores(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetSpotPlacementScoresAsync(const GetSpotPlacementScoresRequest& request, const GetSpotPlacementScoresResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetSpotPlacementScores(request), context);
    } );
}

GetSubnetCidrReservationsOutcome EC2Client::GetSubnetCidrReservations(const GetSubnetCidrReservationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetSubnetCidrReservationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetSubnetCidrReservationsOutcomeCallable EC2Client::GetSubnetCidrReservationsCallable(const GetSubnetCidrReservationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetSubnetCidrReservationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetSubnetCidrReservations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetSubnetCidrReservationsAsync(const GetSubnetCidrReservationsRequest& request, const GetSubnetCidrReservationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetSubnetCidrReservations(request), context);
    } );
}

GetTransitGatewayAttachmentPropagationsOutcome EC2Client::GetTransitGatewayAttachmentPropagations(const GetTransitGatewayAttachmentPropagationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetTransitGatewayAttachmentPropagationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetTransitGatewayAttachmentPropagationsOutcomeCallable EC2Client::GetTransitGatewayAttachmentPropagationsCallable(const GetTransitGatewayAttachmentPropagationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetTransitGatewayAttachmentPropagationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetTransitGatewayAttachmentPropagations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetTransitGatewayAttachmentPropagationsAsync(const GetTransitGatewayAttachmentPropagationsRequest& request, const GetTransitGatewayAttachmentPropagationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetTransitGatewayAttachmentPropagations(request), context);
    } );
}

GetTransitGatewayMulticastDomainAssociationsOutcome EC2Client::GetTransitGatewayMulticastDomainAssociations(const GetTransitGatewayMulticastDomainAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetTransitGatewayMulticastDomainAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetTransitGatewayMulticastDomainAssociationsOutcomeCallable EC2Client::GetTransitGatewayMulticastDomainAssociationsCallable(const GetTransitGatewayMulticastDomainAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetTransitGatewayMulticastDomainAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetTransitGatewayMulticastDomainAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetTransitGatewayMulticastDomainAssociationsAsync(const GetTransitGatewayMulticastDomainAssociationsRequest& request, const GetTransitGatewayMulticastDomainAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetTransitGatewayMulticastDomainAssociations(request), context);
    } );
}

GetTransitGatewayPolicyTableAssociationsOutcome EC2Client::GetTransitGatewayPolicyTableAssociations(const GetTransitGatewayPolicyTableAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetTransitGatewayPolicyTableAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetTransitGatewayPolicyTableAssociationsOutcomeCallable EC2Client::GetTransitGatewayPolicyTableAssociationsCallable(const GetTransitGatewayPolicyTableAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetTransitGatewayPolicyTableAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetTransitGatewayPolicyTableAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetTransitGatewayPolicyTableAssociationsAsync(const GetTransitGatewayPolicyTableAssociationsRequest& request, const GetTransitGatewayPolicyTableAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetTransitGatewayPolicyTableAssociations(request), context);
    } );
}

GetTransitGatewayPolicyTableEntriesOutcome EC2Client::GetTransitGatewayPolicyTableEntries(const GetTransitGatewayPolicyTableEntriesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetTransitGatewayPolicyTableEntriesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetTransitGatewayPolicyTableEntriesOutcomeCallable EC2Client::GetTransitGatewayPolicyTableEntriesCallable(const GetTransitGatewayPolicyTableEntriesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetTransitGatewayPolicyTableEntriesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetTransitGatewayPolicyTableEntries(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetTransitGatewayPolicyTableEntriesAsync(const GetTransitGatewayPolicyTableEntriesRequest& request, const GetTransitGatewayPolicyTableEntriesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetTransitGatewayPolicyTableEntries(request), context);
    } );
}

GetTransitGatewayPrefixListReferencesOutcome EC2Client::GetTransitGatewayPrefixListReferences(const GetTransitGatewayPrefixListReferencesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetTransitGatewayPrefixListReferencesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetTransitGatewayPrefixListReferencesOutcomeCallable EC2Client::GetTransitGatewayPrefixListReferencesCallable(const GetTransitGatewayPrefixListReferencesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetTransitGatewayPrefixListReferencesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetTransitGatewayPrefixListReferences(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetTransitGatewayPrefixListReferencesAsync(const GetTransitGatewayPrefixListReferencesRequest& request, const GetTransitGatewayPrefixListReferencesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetTransitGatewayPrefixListReferences(request), context);
    } );
}

GetTransitGatewayRouteTableAssociationsOutcome EC2Client::GetTransitGatewayRouteTableAssociations(const GetTransitGatewayRouteTableAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetTransitGatewayRouteTableAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetTransitGatewayRouteTableAssociationsOutcomeCallable EC2Client::GetTransitGatewayRouteTableAssociationsCallable(const GetTransitGatewayRouteTableAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetTransitGatewayRouteTableAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetTransitGatewayRouteTableAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetTransitGatewayRouteTableAssociationsAsync(const GetTransitGatewayRouteTableAssociationsRequest& request, const GetTransitGatewayRouteTableAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetTransitGatewayRouteTableAssociations(request), context);
    } );
}

GetTransitGatewayRouteTablePropagationsOutcome EC2Client::GetTransitGatewayRouteTablePropagations(const GetTransitGatewayRouteTablePropagationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetTransitGatewayRouteTablePropagationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetTransitGatewayRouteTablePropagationsOutcomeCallable EC2Client::GetTransitGatewayRouteTablePropagationsCallable(const GetTransitGatewayRouteTablePropagationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetTransitGatewayRouteTablePropagationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetTransitGatewayRouteTablePropagations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetTransitGatewayRouteTablePropagationsAsync(const GetTransitGatewayRouteTablePropagationsRequest& request, const GetTransitGatewayRouteTablePropagationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetTransitGatewayRouteTablePropagations(request), context);
    } );
}

GetVpnConnectionDeviceSampleConfigurationOutcome EC2Client::GetVpnConnectionDeviceSampleConfiguration(const GetVpnConnectionDeviceSampleConfigurationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetVpnConnectionDeviceSampleConfigurationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetVpnConnectionDeviceSampleConfigurationOutcomeCallable EC2Client::GetVpnConnectionDeviceSampleConfigurationCallable(const GetVpnConnectionDeviceSampleConfigurationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetVpnConnectionDeviceSampleConfigurationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetVpnConnectionDeviceSampleConfiguration(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetVpnConnectionDeviceSampleConfigurationAsync(const GetVpnConnectionDeviceSampleConfigurationRequest& request, const GetVpnConnectionDeviceSampleConfigurationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetVpnConnectionDeviceSampleConfiguration(request), context);
    } );
}

GetVpnConnectionDeviceTypesOutcome EC2Client::GetVpnConnectionDeviceTypes(const GetVpnConnectionDeviceTypesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return GetVpnConnectionDeviceTypesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

GetVpnConnectionDeviceTypesOutcomeCallable EC2Client::GetVpnConnectionDeviceTypesCallable(const GetVpnConnectionDeviceTypesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< GetVpnConnectionDeviceTypesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->GetVpnConnectionDeviceTypes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::GetVpnConnectionDeviceTypesAsync(const GetVpnConnectionDeviceTypesRequest& request, const GetVpnConnectionDeviceTypesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, GetVpnConnectionDeviceTypes(request), context);
    } );
}

ImportClientVpnClientCertificateRevocationListOutcome EC2Client::ImportClientVpnClientCertificateRevocationList(const ImportClientVpnClientCertificateRevocationListRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ImportClientVpnClientCertificateRevocationListOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ImportClientVpnClientCertificateRevocationListOutcomeCallable EC2Client::ImportClientVpnClientCertificateRevocationListCallable(const ImportClientVpnClientCertificateRevocationListRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ImportClientVpnClientCertificateRevocationListOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ImportClientVpnClientCertificateRevocationList(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ImportClientVpnClientCertificateRevocationListAsync(const ImportClientVpnClientCertificateRevocationListRequest& request, const ImportClientVpnClientCertificateRevocationListResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ImportClientVpnClientCertificateRevocationList(request), context);
    } );
}

ImportImageOutcome EC2Client::ImportImage(const ImportImageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ImportImageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ImportImageOutcomeCallable EC2Client::ImportImageCallable(const ImportImageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ImportImageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ImportImage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ImportImageAsync(const ImportImageRequest& request, const ImportImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ImportImage(request), context);
    } );
}

ImportInstanceOutcome EC2Client::ImportInstance(const ImportInstanceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ImportInstanceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ImportInstanceOutcomeCallable EC2Client::ImportInstanceCallable(const ImportInstanceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ImportInstanceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ImportInstance(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ImportInstanceAsync(const ImportInstanceRequest& request, const ImportInstanceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ImportInstance(request), context);
    } );
}

ImportKeyPairOutcome EC2Client::ImportKeyPair(const ImportKeyPairRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ImportKeyPairOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ImportKeyPairOutcomeCallable EC2Client::ImportKeyPairCallable(const ImportKeyPairRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ImportKeyPairOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ImportKeyPair(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ImportKeyPairAsync(const ImportKeyPairRequest& request, const ImportKeyPairResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ImportKeyPair(request), context);
    } );
}

ImportSnapshotOutcome EC2Client::ImportSnapshot(const ImportSnapshotRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ImportSnapshotOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ImportSnapshotOutcomeCallable EC2Client::ImportSnapshotCallable(const ImportSnapshotRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ImportSnapshotOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ImportSnapshot(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ImportSnapshotAsync(const ImportSnapshotRequest& request, const ImportSnapshotResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ImportSnapshot(request), context);
    } );
}

ImportVolumeOutcome EC2Client::ImportVolume(const ImportVolumeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ImportVolumeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ImportVolumeOutcomeCallable EC2Client::ImportVolumeCallable(const ImportVolumeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ImportVolumeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ImportVolume(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ImportVolumeAsync(const ImportVolumeRequest& request, const ImportVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ImportVolume(request), context);
    } );
}

ListImagesInRecycleBinOutcome EC2Client::ListImagesInRecycleBin(const ListImagesInRecycleBinRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ListImagesInRecycleBinOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ListImagesInRecycleBinOutcomeCallable EC2Client::ListImagesInRecycleBinCallable(const ListImagesInRecycleBinRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ListImagesInRecycleBinOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ListImagesInRecycleBin(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ListImagesInRecycleBinAsync(const ListImagesInRecycleBinRequest& request, const ListImagesInRecycleBinResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ListImagesInRecycleBin(request), context);
    } );
}

ListSnapshotsInRecycleBinOutcome EC2Client::ListSnapshotsInRecycleBin(const ListSnapshotsInRecycleBinRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ListSnapshotsInRecycleBinOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ListSnapshotsInRecycleBinOutcomeCallable EC2Client::ListSnapshotsInRecycleBinCallable(const ListSnapshotsInRecycleBinRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ListSnapshotsInRecycleBinOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ListSnapshotsInRecycleBin(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ListSnapshotsInRecycleBinAsync(const ListSnapshotsInRecycleBinRequest& request, const ListSnapshotsInRecycleBinResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ListSnapshotsInRecycleBin(request), context);
    } );
}

ModifyAddressAttributeOutcome EC2Client::ModifyAddressAttribute(const ModifyAddressAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyAddressAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyAddressAttributeOutcomeCallable EC2Client::ModifyAddressAttributeCallable(const ModifyAddressAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyAddressAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyAddressAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyAddressAttributeAsync(const ModifyAddressAttributeRequest& request, const ModifyAddressAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyAddressAttribute(request), context);
    } );
}

ModifyAvailabilityZoneGroupOutcome EC2Client::ModifyAvailabilityZoneGroup(const ModifyAvailabilityZoneGroupRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyAvailabilityZoneGroupOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyAvailabilityZoneGroupOutcomeCallable EC2Client::ModifyAvailabilityZoneGroupCallable(const ModifyAvailabilityZoneGroupRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyAvailabilityZoneGroupOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyAvailabilityZoneGroup(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyAvailabilityZoneGroupAsync(const ModifyAvailabilityZoneGroupRequest& request, const ModifyAvailabilityZoneGroupResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyAvailabilityZoneGroup(request), context);
    } );
}

ModifyCapacityReservationOutcome EC2Client::ModifyCapacityReservation(const ModifyCapacityReservationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyCapacityReservationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyCapacityReservationOutcomeCallable EC2Client::ModifyCapacityReservationCallable(const ModifyCapacityReservationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyCapacityReservationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyCapacityReservation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyCapacityReservationAsync(const ModifyCapacityReservationRequest& request, const ModifyCapacityReservationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyCapacityReservation(request), context);
    } );
}

ModifyCapacityReservationFleetOutcome EC2Client::ModifyCapacityReservationFleet(const ModifyCapacityReservationFleetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyCapacityReservationFleetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyCapacityReservationFleetOutcomeCallable EC2Client::ModifyCapacityReservationFleetCallable(const ModifyCapacityReservationFleetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyCapacityReservationFleetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyCapacityReservationFleet(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyCapacityReservationFleetAsync(const ModifyCapacityReservationFleetRequest& request, const ModifyCapacityReservationFleetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyCapacityReservationFleet(request), context);
    } );
}

ModifyClientVpnEndpointOutcome EC2Client::ModifyClientVpnEndpoint(const ModifyClientVpnEndpointRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyClientVpnEndpointOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyClientVpnEndpointOutcomeCallable EC2Client::ModifyClientVpnEndpointCallable(const ModifyClientVpnEndpointRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyClientVpnEndpointOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyClientVpnEndpoint(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyClientVpnEndpointAsync(const ModifyClientVpnEndpointRequest& request, const ModifyClientVpnEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyClientVpnEndpoint(request), context);
    } );
}

ModifyDefaultCreditSpecificationOutcome EC2Client::ModifyDefaultCreditSpecification(const ModifyDefaultCreditSpecificationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyDefaultCreditSpecificationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyDefaultCreditSpecificationOutcomeCallable EC2Client::ModifyDefaultCreditSpecificationCallable(const ModifyDefaultCreditSpecificationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyDefaultCreditSpecificationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyDefaultCreditSpecification(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyDefaultCreditSpecificationAsync(const ModifyDefaultCreditSpecificationRequest& request, const ModifyDefaultCreditSpecificationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyDefaultCreditSpecification(request), context);
    } );
}

ModifyEbsDefaultKmsKeyIdOutcome EC2Client::ModifyEbsDefaultKmsKeyId(const ModifyEbsDefaultKmsKeyIdRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyEbsDefaultKmsKeyIdOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyEbsDefaultKmsKeyIdOutcomeCallable EC2Client::ModifyEbsDefaultKmsKeyIdCallable(const ModifyEbsDefaultKmsKeyIdRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyEbsDefaultKmsKeyIdOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyEbsDefaultKmsKeyId(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyEbsDefaultKmsKeyIdAsync(const ModifyEbsDefaultKmsKeyIdRequest& request, const ModifyEbsDefaultKmsKeyIdResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyEbsDefaultKmsKeyId(request), context);
    } );
}

ModifyFleetOutcome EC2Client::ModifyFleet(const ModifyFleetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyFleetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyFleetOutcomeCallable EC2Client::ModifyFleetCallable(const ModifyFleetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyFleetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyFleet(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyFleetAsync(const ModifyFleetRequest& request, const ModifyFleetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyFleet(request), context);
    } );
}

ModifyFpgaImageAttributeOutcome EC2Client::ModifyFpgaImageAttribute(const ModifyFpgaImageAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyFpgaImageAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyFpgaImageAttributeOutcomeCallable EC2Client::ModifyFpgaImageAttributeCallable(const ModifyFpgaImageAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyFpgaImageAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyFpgaImageAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyFpgaImageAttributeAsync(const ModifyFpgaImageAttributeRequest& request, const ModifyFpgaImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyFpgaImageAttribute(request), context);
    } );
}

ModifyHostsOutcome EC2Client::ModifyHosts(const ModifyHostsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyHostsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyHostsOutcomeCallable EC2Client::ModifyHostsCallable(const ModifyHostsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyHostsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyHosts(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyHostsAsync(const ModifyHostsRequest& request, const ModifyHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyHosts(request), context);
    } );
}

ModifyIdFormatOutcome EC2Client::ModifyIdFormat(const ModifyIdFormatRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyIdFormatOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyIdFormatOutcomeCallable EC2Client::ModifyIdFormatCallable(const ModifyIdFormatRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyIdFormatOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyIdFormat(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyIdFormatAsync(const ModifyIdFormatRequest& request, const ModifyIdFormatResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyIdFormat(request), context);
    } );
}

ModifyIdentityIdFormatOutcome EC2Client::ModifyIdentityIdFormat(const ModifyIdentityIdFormatRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyIdentityIdFormatOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyIdentityIdFormatOutcomeCallable EC2Client::ModifyIdentityIdFormatCallable(const ModifyIdentityIdFormatRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyIdentityIdFormatOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyIdentityIdFormat(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyIdentityIdFormatAsync(const ModifyIdentityIdFormatRequest& request, const ModifyIdentityIdFormatResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyIdentityIdFormat(request), context);
    } );
}

ModifyImageAttributeOutcome EC2Client::ModifyImageAttribute(const ModifyImageAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyImageAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyImageAttributeOutcomeCallable EC2Client::ModifyImageAttributeCallable(const ModifyImageAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyImageAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyImageAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyImageAttributeAsync(const ModifyImageAttributeRequest& request, const ModifyImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyImageAttribute(request), context);
    } );
}

ModifyInstanceAttributeOutcome EC2Client::ModifyInstanceAttribute(const ModifyInstanceAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyInstanceAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyInstanceAttributeOutcomeCallable EC2Client::ModifyInstanceAttributeCallable(const ModifyInstanceAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyInstanceAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyInstanceAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyInstanceAttributeAsync(const ModifyInstanceAttributeRequest& request, const ModifyInstanceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyInstanceAttribute(request), context);
    } );
}

ModifyInstanceCapacityReservationAttributesOutcome EC2Client::ModifyInstanceCapacityReservationAttributes(const ModifyInstanceCapacityReservationAttributesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyInstanceCapacityReservationAttributesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyInstanceCapacityReservationAttributesOutcomeCallable EC2Client::ModifyInstanceCapacityReservationAttributesCallable(const ModifyInstanceCapacityReservationAttributesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyInstanceCapacityReservationAttributesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyInstanceCapacityReservationAttributes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyInstanceCapacityReservationAttributesAsync(const ModifyInstanceCapacityReservationAttributesRequest& request, const ModifyInstanceCapacityReservationAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyInstanceCapacityReservationAttributes(request), context);
    } );
}

ModifyInstanceCreditSpecificationOutcome EC2Client::ModifyInstanceCreditSpecification(const ModifyInstanceCreditSpecificationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyInstanceCreditSpecificationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyInstanceCreditSpecificationOutcomeCallable EC2Client::ModifyInstanceCreditSpecificationCallable(const ModifyInstanceCreditSpecificationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyInstanceCreditSpecificationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyInstanceCreditSpecification(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyInstanceCreditSpecificationAsync(const ModifyInstanceCreditSpecificationRequest& request, const ModifyInstanceCreditSpecificationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyInstanceCreditSpecification(request), context);
    } );
}

ModifyInstanceEventStartTimeOutcome EC2Client::ModifyInstanceEventStartTime(const ModifyInstanceEventStartTimeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyInstanceEventStartTimeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyInstanceEventStartTimeOutcomeCallable EC2Client::ModifyInstanceEventStartTimeCallable(const ModifyInstanceEventStartTimeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyInstanceEventStartTimeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyInstanceEventStartTime(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyInstanceEventStartTimeAsync(const ModifyInstanceEventStartTimeRequest& request, const ModifyInstanceEventStartTimeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyInstanceEventStartTime(request), context);
    } );
}

ModifyInstanceEventWindowOutcome EC2Client::ModifyInstanceEventWindow(const ModifyInstanceEventWindowRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyInstanceEventWindowOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyInstanceEventWindowOutcomeCallable EC2Client::ModifyInstanceEventWindowCallable(const ModifyInstanceEventWindowRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyInstanceEventWindowOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyInstanceEventWindow(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyInstanceEventWindowAsync(const ModifyInstanceEventWindowRequest& request, const ModifyInstanceEventWindowResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyInstanceEventWindow(request), context);
    } );
}

ModifyInstanceMaintenanceOptionsOutcome EC2Client::ModifyInstanceMaintenanceOptions(const ModifyInstanceMaintenanceOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyInstanceMaintenanceOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyInstanceMaintenanceOptionsOutcomeCallable EC2Client::ModifyInstanceMaintenanceOptionsCallable(const ModifyInstanceMaintenanceOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyInstanceMaintenanceOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyInstanceMaintenanceOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyInstanceMaintenanceOptionsAsync(const ModifyInstanceMaintenanceOptionsRequest& request, const ModifyInstanceMaintenanceOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyInstanceMaintenanceOptions(request), context);
    } );
}

ModifyInstanceMetadataOptionsOutcome EC2Client::ModifyInstanceMetadataOptions(const ModifyInstanceMetadataOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyInstanceMetadataOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyInstanceMetadataOptionsOutcomeCallable EC2Client::ModifyInstanceMetadataOptionsCallable(const ModifyInstanceMetadataOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyInstanceMetadataOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyInstanceMetadataOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyInstanceMetadataOptionsAsync(const ModifyInstanceMetadataOptionsRequest& request, const ModifyInstanceMetadataOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyInstanceMetadataOptions(request), context);
    } );
}

ModifyInstancePlacementOutcome EC2Client::ModifyInstancePlacement(const ModifyInstancePlacementRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyInstancePlacementOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyInstancePlacementOutcomeCallable EC2Client::ModifyInstancePlacementCallable(const ModifyInstancePlacementRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyInstancePlacementOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyInstancePlacement(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyInstancePlacementAsync(const ModifyInstancePlacementRequest& request, const ModifyInstancePlacementResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyInstancePlacement(request), context);
    } );
}

ModifyIpamOutcome EC2Client::ModifyIpam(const ModifyIpamRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyIpamOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyIpamOutcomeCallable EC2Client::ModifyIpamCallable(const ModifyIpamRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyIpamOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyIpam(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyIpamAsync(const ModifyIpamRequest& request, const ModifyIpamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyIpam(request), context);
    } );
}

ModifyIpamPoolOutcome EC2Client::ModifyIpamPool(const ModifyIpamPoolRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyIpamPoolOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyIpamPoolOutcomeCallable EC2Client::ModifyIpamPoolCallable(const ModifyIpamPoolRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyIpamPoolOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyIpamPool(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyIpamPoolAsync(const ModifyIpamPoolRequest& request, const ModifyIpamPoolResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyIpamPool(request), context);
    } );
}

ModifyIpamResourceCidrOutcome EC2Client::ModifyIpamResourceCidr(const ModifyIpamResourceCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyIpamResourceCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyIpamResourceCidrOutcomeCallable EC2Client::ModifyIpamResourceCidrCallable(const ModifyIpamResourceCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyIpamResourceCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyIpamResourceCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyIpamResourceCidrAsync(const ModifyIpamResourceCidrRequest& request, const ModifyIpamResourceCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyIpamResourceCidr(request), context);
    } );
}

ModifyIpamScopeOutcome EC2Client::ModifyIpamScope(const ModifyIpamScopeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyIpamScopeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyIpamScopeOutcomeCallable EC2Client::ModifyIpamScopeCallable(const ModifyIpamScopeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyIpamScopeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyIpamScope(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyIpamScopeAsync(const ModifyIpamScopeRequest& request, const ModifyIpamScopeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyIpamScope(request), context);
    } );
}

ModifyLaunchTemplateOutcome EC2Client::ModifyLaunchTemplate(const ModifyLaunchTemplateRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyLaunchTemplateOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyLaunchTemplateOutcomeCallable EC2Client::ModifyLaunchTemplateCallable(const ModifyLaunchTemplateRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyLaunchTemplateOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyLaunchTemplate(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyLaunchTemplateAsync(const ModifyLaunchTemplateRequest& request, const ModifyLaunchTemplateResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyLaunchTemplate(request), context);
    } );
}

ModifyLocalGatewayRouteOutcome EC2Client::ModifyLocalGatewayRoute(const ModifyLocalGatewayRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyLocalGatewayRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyLocalGatewayRouteOutcomeCallable EC2Client::ModifyLocalGatewayRouteCallable(const ModifyLocalGatewayRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyLocalGatewayRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyLocalGatewayRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyLocalGatewayRouteAsync(const ModifyLocalGatewayRouteRequest& request, const ModifyLocalGatewayRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyLocalGatewayRoute(request), context);
    } );
}

ModifyManagedPrefixListOutcome EC2Client::ModifyManagedPrefixList(const ModifyManagedPrefixListRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyManagedPrefixListOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyManagedPrefixListOutcomeCallable EC2Client::ModifyManagedPrefixListCallable(const ModifyManagedPrefixListRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyManagedPrefixListOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyManagedPrefixList(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyManagedPrefixListAsync(const ModifyManagedPrefixListRequest& request, const ModifyManagedPrefixListResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyManagedPrefixList(request), context);
    } );
}

ModifyNetworkInterfaceAttributeOutcome EC2Client::ModifyNetworkInterfaceAttribute(const ModifyNetworkInterfaceAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyNetworkInterfaceAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyNetworkInterfaceAttributeOutcomeCallable EC2Client::ModifyNetworkInterfaceAttributeCallable(const ModifyNetworkInterfaceAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyNetworkInterfaceAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyNetworkInterfaceAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyNetworkInterfaceAttributeAsync(const ModifyNetworkInterfaceAttributeRequest& request, const ModifyNetworkInterfaceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyNetworkInterfaceAttribute(request), context);
    } );
}

ModifyPrivateDnsNameOptionsOutcome EC2Client::ModifyPrivateDnsNameOptions(const ModifyPrivateDnsNameOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyPrivateDnsNameOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyPrivateDnsNameOptionsOutcomeCallable EC2Client::ModifyPrivateDnsNameOptionsCallable(const ModifyPrivateDnsNameOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyPrivateDnsNameOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyPrivateDnsNameOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyPrivateDnsNameOptionsAsync(const ModifyPrivateDnsNameOptionsRequest& request, const ModifyPrivateDnsNameOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyPrivateDnsNameOptions(request), context);
    } );
}

ModifyReservedInstancesOutcome EC2Client::ModifyReservedInstances(const ModifyReservedInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyReservedInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyReservedInstancesOutcomeCallable EC2Client::ModifyReservedInstancesCallable(const ModifyReservedInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyReservedInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyReservedInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyReservedInstancesAsync(const ModifyReservedInstancesRequest& request, const ModifyReservedInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyReservedInstances(request), context);
    } );
}

ModifySecurityGroupRulesOutcome EC2Client::ModifySecurityGroupRules(const ModifySecurityGroupRulesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifySecurityGroupRulesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifySecurityGroupRulesOutcomeCallable EC2Client::ModifySecurityGroupRulesCallable(const ModifySecurityGroupRulesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifySecurityGroupRulesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifySecurityGroupRules(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifySecurityGroupRulesAsync(const ModifySecurityGroupRulesRequest& request, const ModifySecurityGroupRulesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifySecurityGroupRules(request), context);
    } );
}

ModifySnapshotAttributeOutcome EC2Client::ModifySnapshotAttribute(const ModifySnapshotAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifySnapshotAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifySnapshotAttributeOutcomeCallable EC2Client::ModifySnapshotAttributeCallable(const ModifySnapshotAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifySnapshotAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifySnapshotAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifySnapshotAttributeAsync(const ModifySnapshotAttributeRequest& request, const ModifySnapshotAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifySnapshotAttribute(request), context);
    } );
}

ModifySnapshotTierOutcome EC2Client::ModifySnapshotTier(const ModifySnapshotTierRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifySnapshotTierOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifySnapshotTierOutcomeCallable EC2Client::ModifySnapshotTierCallable(const ModifySnapshotTierRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifySnapshotTierOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifySnapshotTier(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifySnapshotTierAsync(const ModifySnapshotTierRequest& request, const ModifySnapshotTierResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifySnapshotTier(request), context);
    } );
}

ModifySpotFleetRequestOutcome EC2Client::ModifySpotFleetRequest(const ModifySpotFleetRequestRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifySpotFleetRequestOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifySpotFleetRequestOutcomeCallable EC2Client::ModifySpotFleetRequestCallable(const ModifySpotFleetRequestRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifySpotFleetRequestOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifySpotFleetRequest(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifySpotFleetRequestAsync(const ModifySpotFleetRequestRequest& request, const ModifySpotFleetRequestResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifySpotFleetRequest(request), context);
    } );
}

ModifySubnetAttributeOutcome EC2Client::ModifySubnetAttribute(const ModifySubnetAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifySubnetAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifySubnetAttributeOutcomeCallable EC2Client::ModifySubnetAttributeCallable(const ModifySubnetAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifySubnetAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifySubnetAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifySubnetAttributeAsync(const ModifySubnetAttributeRequest& request, const ModifySubnetAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifySubnetAttribute(request), context);
    } );
}

ModifyTrafficMirrorFilterNetworkServicesOutcome EC2Client::ModifyTrafficMirrorFilterNetworkServices(const ModifyTrafficMirrorFilterNetworkServicesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyTrafficMirrorFilterNetworkServicesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyTrafficMirrorFilterNetworkServicesOutcomeCallable EC2Client::ModifyTrafficMirrorFilterNetworkServicesCallable(const ModifyTrafficMirrorFilterNetworkServicesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyTrafficMirrorFilterNetworkServicesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyTrafficMirrorFilterNetworkServices(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyTrafficMirrorFilterNetworkServicesAsync(const ModifyTrafficMirrorFilterNetworkServicesRequest& request, const ModifyTrafficMirrorFilterNetworkServicesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyTrafficMirrorFilterNetworkServices(request), context);
    } );
}

ModifyTrafficMirrorFilterRuleOutcome EC2Client::ModifyTrafficMirrorFilterRule(const ModifyTrafficMirrorFilterRuleRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyTrafficMirrorFilterRuleOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyTrafficMirrorFilterRuleOutcomeCallable EC2Client::ModifyTrafficMirrorFilterRuleCallable(const ModifyTrafficMirrorFilterRuleRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyTrafficMirrorFilterRuleOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyTrafficMirrorFilterRule(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyTrafficMirrorFilterRuleAsync(const ModifyTrafficMirrorFilterRuleRequest& request, const ModifyTrafficMirrorFilterRuleResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyTrafficMirrorFilterRule(request), context);
    } );
}

ModifyTrafficMirrorSessionOutcome EC2Client::ModifyTrafficMirrorSession(const ModifyTrafficMirrorSessionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyTrafficMirrorSessionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyTrafficMirrorSessionOutcomeCallable EC2Client::ModifyTrafficMirrorSessionCallable(const ModifyTrafficMirrorSessionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyTrafficMirrorSessionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyTrafficMirrorSession(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyTrafficMirrorSessionAsync(const ModifyTrafficMirrorSessionRequest& request, const ModifyTrafficMirrorSessionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyTrafficMirrorSession(request), context);
    } );
}

ModifyTransitGatewayOutcome EC2Client::ModifyTransitGateway(const ModifyTransitGatewayRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyTransitGatewayOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyTransitGatewayOutcomeCallable EC2Client::ModifyTransitGatewayCallable(const ModifyTransitGatewayRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyTransitGatewayOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyTransitGateway(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyTransitGatewayAsync(const ModifyTransitGatewayRequest& request, const ModifyTransitGatewayResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyTransitGateway(request), context);
    } );
}

ModifyTransitGatewayPrefixListReferenceOutcome EC2Client::ModifyTransitGatewayPrefixListReference(const ModifyTransitGatewayPrefixListReferenceRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyTransitGatewayPrefixListReferenceOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyTransitGatewayPrefixListReferenceOutcomeCallable EC2Client::ModifyTransitGatewayPrefixListReferenceCallable(const ModifyTransitGatewayPrefixListReferenceRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyTransitGatewayPrefixListReferenceOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyTransitGatewayPrefixListReference(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyTransitGatewayPrefixListReferenceAsync(const ModifyTransitGatewayPrefixListReferenceRequest& request, const ModifyTransitGatewayPrefixListReferenceResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyTransitGatewayPrefixListReference(request), context);
    } );
}

ModifyTransitGatewayVpcAttachmentOutcome EC2Client::ModifyTransitGatewayVpcAttachment(const ModifyTransitGatewayVpcAttachmentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyTransitGatewayVpcAttachmentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyTransitGatewayVpcAttachmentOutcomeCallable EC2Client::ModifyTransitGatewayVpcAttachmentCallable(const ModifyTransitGatewayVpcAttachmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyTransitGatewayVpcAttachmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyTransitGatewayVpcAttachment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyTransitGatewayVpcAttachmentAsync(const ModifyTransitGatewayVpcAttachmentRequest& request, const ModifyTransitGatewayVpcAttachmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyTransitGatewayVpcAttachment(request), context);
    } );
}

ModifyVolumeOutcome EC2Client::ModifyVolume(const ModifyVolumeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVolumeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVolumeOutcomeCallable EC2Client::ModifyVolumeCallable(const ModifyVolumeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVolumeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVolume(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVolumeAsync(const ModifyVolumeRequest& request, const ModifyVolumeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVolume(request), context);
    } );
}

ModifyVolumeAttributeOutcome EC2Client::ModifyVolumeAttribute(const ModifyVolumeAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVolumeAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVolumeAttributeOutcomeCallable EC2Client::ModifyVolumeAttributeCallable(const ModifyVolumeAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVolumeAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVolumeAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVolumeAttributeAsync(const ModifyVolumeAttributeRequest& request, const ModifyVolumeAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVolumeAttribute(request), context);
    } );
}

ModifyVpcAttributeOutcome EC2Client::ModifyVpcAttribute(const ModifyVpcAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpcAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpcAttributeOutcomeCallable EC2Client::ModifyVpcAttributeCallable(const ModifyVpcAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpcAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpcAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpcAttributeAsync(const ModifyVpcAttributeRequest& request, const ModifyVpcAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpcAttribute(request), context);
    } );
}

ModifyVpcEndpointOutcome EC2Client::ModifyVpcEndpoint(const ModifyVpcEndpointRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpcEndpointOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpcEndpointOutcomeCallable EC2Client::ModifyVpcEndpointCallable(const ModifyVpcEndpointRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpcEndpointOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpcEndpoint(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpcEndpointAsync(const ModifyVpcEndpointRequest& request, const ModifyVpcEndpointResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpcEndpoint(request), context);
    } );
}

ModifyVpcEndpointConnectionNotificationOutcome EC2Client::ModifyVpcEndpointConnectionNotification(const ModifyVpcEndpointConnectionNotificationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpcEndpointConnectionNotificationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpcEndpointConnectionNotificationOutcomeCallable EC2Client::ModifyVpcEndpointConnectionNotificationCallable(const ModifyVpcEndpointConnectionNotificationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpcEndpointConnectionNotificationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpcEndpointConnectionNotification(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpcEndpointConnectionNotificationAsync(const ModifyVpcEndpointConnectionNotificationRequest& request, const ModifyVpcEndpointConnectionNotificationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpcEndpointConnectionNotification(request), context);
    } );
}

ModifyVpcEndpointServiceConfigurationOutcome EC2Client::ModifyVpcEndpointServiceConfiguration(const ModifyVpcEndpointServiceConfigurationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpcEndpointServiceConfigurationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpcEndpointServiceConfigurationOutcomeCallable EC2Client::ModifyVpcEndpointServiceConfigurationCallable(const ModifyVpcEndpointServiceConfigurationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpcEndpointServiceConfigurationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpcEndpointServiceConfiguration(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpcEndpointServiceConfigurationAsync(const ModifyVpcEndpointServiceConfigurationRequest& request, const ModifyVpcEndpointServiceConfigurationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpcEndpointServiceConfiguration(request), context);
    } );
}

ModifyVpcEndpointServicePayerResponsibilityOutcome EC2Client::ModifyVpcEndpointServicePayerResponsibility(const ModifyVpcEndpointServicePayerResponsibilityRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpcEndpointServicePayerResponsibilityOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpcEndpointServicePayerResponsibilityOutcomeCallable EC2Client::ModifyVpcEndpointServicePayerResponsibilityCallable(const ModifyVpcEndpointServicePayerResponsibilityRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpcEndpointServicePayerResponsibilityOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpcEndpointServicePayerResponsibility(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpcEndpointServicePayerResponsibilityAsync(const ModifyVpcEndpointServicePayerResponsibilityRequest& request, const ModifyVpcEndpointServicePayerResponsibilityResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpcEndpointServicePayerResponsibility(request), context);
    } );
}

ModifyVpcEndpointServicePermissionsOutcome EC2Client::ModifyVpcEndpointServicePermissions(const ModifyVpcEndpointServicePermissionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpcEndpointServicePermissionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpcEndpointServicePermissionsOutcomeCallable EC2Client::ModifyVpcEndpointServicePermissionsCallable(const ModifyVpcEndpointServicePermissionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpcEndpointServicePermissionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpcEndpointServicePermissions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpcEndpointServicePermissionsAsync(const ModifyVpcEndpointServicePermissionsRequest& request, const ModifyVpcEndpointServicePermissionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpcEndpointServicePermissions(request), context);
    } );
}

ModifyVpcPeeringConnectionOptionsOutcome EC2Client::ModifyVpcPeeringConnectionOptions(const ModifyVpcPeeringConnectionOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpcPeeringConnectionOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpcPeeringConnectionOptionsOutcomeCallable EC2Client::ModifyVpcPeeringConnectionOptionsCallable(const ModifyVpcPeeringConnectionOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpcPeeringConnectionOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpcPeeringConnectionOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpcPeeringConnectionOptionsAsync(const ModifyVpcPeeringConnectionOptionsRequest& request, const ModifyVpcPeeringConnectionOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpcPeeringConnectionOptions(request), context);
    } );
}

ModifyVpcTenancyOutcome EC2Client::ModifyVpcTenancy(const ModifyVpcTenancyRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpcTenancyOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpcTenancyOutcomeCallable EC2Client::ModifyVpcTenancyCallable(const ModifyVpcTenancyRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpcTenancyOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpcTenancy(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpcTenancyAsync(const ModifyVpcTenancyRequest& request, const ModifyVpcTenancyResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpcTenancy(request), context);
    } );
}

ModifyVpnConnectionOutcome EC2Client::ModifyVpnConnection(const ModifyVpnConnectionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpnConnectionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpnConnectionOutcomeCallable EC2Client::ModifyVpnConnectionCallable(const ModifyVpnConnectionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpnConnectionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpnConnection(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpnConnectionAsync(const ModifyVpnConnectionRequest& request, const ModifyVpnConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpnConnection(request), context);
    } );
}

ModifyVpnConnectionOptionsOutcome EC2Client::ModifyVpnConnectionOptions(const ModifyVpnConnectionOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpnConnectionOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpnConnectionOptionsOutcomeCallable EC2Client::ModifyVpnConnectionOptionsCallable(const ModifyVpnConnectionOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpnConnectionOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpnConnectionOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpnConnectionOptionsAsync(const ModifyVpnConnectionOptionsRequest& request, const ModifyVpnConnectionOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpnConnectionOptions(request), context);
    } );
}

ModifyVpnTunnelCertificateOutcome EC2Client::ModifyVpnTunnelCertificate(const ModifyVpnTunnelCertificateRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpnTunnelCertificateOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpnTunnelCertificateOutcomeCallable EC2Client::ModifyVpnTunnelCertificateCallable(const ModifyVpnTunnelCertificateRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpnTunnelCertificateOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpnTunnelCertificate(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpnTunnelCertificateAsync(const ModifyVpnTunnelCertificateRequest& request, const ModifyVpnTunnelCertificateResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpnTunnelCertificate(request), context);
    } );
}

ModifyVpnTunnelOptionsOutcome EC2Client::ModifyVpnTunnelOptions(const ModifyVpnTunnelOptionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ModifyVpnTunnelOptionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ModifyVpnTunnelOptionsOutcomeCallable EC2Client::ModifyVpnTunnelOptionsCallable(const ModifyVpnTunnelOptionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ModifyVpnTunnelOptionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ModifyVpnTunnelOptions(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ModifyVpnTunnelOptionsAsync(const ModifyVpnTunnelOptionsRequest& request, const ModifyVpnTunnelOptionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ModifyVpnTunnelOptions(request), context);
    } );
}

MonitorInstancesOutcome EC2Client::MonitorInstances(const MonitorInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return MonitorInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

MonitorInstancesOutcomeCallable EC2Client::MonitorInstancesCallable(const MonitorInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< MonitorInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->MonitorInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::MonitorInstancesAsync(const MonitorInstancesRequest& request, const MonitorInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, MonitorInstances(request), context);
    } );
}

MoveAddressToVpcOutcome EC2Client::MoveAddressToVpc(const MoveAddressToVpcRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return MoveAddressToVpcOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

MoveAddressToVpcOutcomeCallable EC2Client::MoveAddressToVpcCallable(const MoveAddressToVpcRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< MoveAddressToVpcOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->MoveAddressToVpc(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::MoveAddressToVpcAsync(const MoveAddressToVpcRequest& request, const MoveAddressToVpcResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, MoveAddressToVpc(request), context);
    } );
}

MoveByoipCidrToIpamOutcome EC2Client::MoveByoipCidrToIpam(const MoveByoipCidrToIpamRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return MoveByoipCidrToIpamOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

MoveByoipCidrToIpamOutcomeCallable EC2Client::MoveByoipCidrToIpamCallable(const MoveByoipCidrToIpamRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< MoveByoipCidrToIpamOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->MoveByoipCidrToIpam(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::MoveByoipCidrToIpamAsync(const MoveByoipCidrToIpamRequest& request, const MoveByoipCidrToIpamResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, MoveByoipCidrToIpam(request), context);
    } );
}

ProvisionByoipCidrOutcome EC2Client::ProvisionByoipCidr(const ProvisionByoipCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ProvisionByoipCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ProvisionByoipCidrOutcomeCallable EC2Client::ProvisionByoipCidrCallable(const ProvisionByoipCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ProvisionByoipCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ProvisionByoipCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ProvisionByoipCidrAsync(const ProvisionByoipCidrRequest& request, const ProvisionByoipCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ProvisionByoipCidr(request), context);
    } );
}

ProvisionIpamPoolCidrOutcome EC2Client::ProvisionIpamPoolCidr(const ProvisionIpamPoolCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ProvisionIpamPoolCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ProvisionIpamPoolCidrOutcomeCallable EC2Client::ProvisionIpamPoolCidrCallable(const ProvisionIpamPoolCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ProvisionIpamPoolCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ProvisionIpamPoolCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ProvisionIpamPoolCidrAsync(const ProvisionIpamPoolCidrRequest& request, const ProvisionIpamPoolCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ProvisionIpamPoolCidr(request), context);
    } );
}

ProvisionPublicIpv4PoolCidrOutcome EC2Client::ProvisionPublicIpv4PoolCidr(const ProvisionPublicIpv4PoolCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ProvisionPublicIpv4PoolCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ProvisionPublicIpv4PoolCidrOutcomeCallable EC2Client::ProvisionPublicIpv4PoolCidrCallable(const ProvisionPublicIpv4PoolCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ProvisionPublicIpv4PoolCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ProvisionPublicIpv4PoolCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ProvisionPublicIpv4PoolCidrAsync(const ProvisionPublicIpv4PoolCidrRequest& request, const ProvisionPublicIpv4PoolCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ProvisionPublicIpv4PoolCidr(request), context);
    } );
}

PurchaseHostReservationOutcome EC2Client::PurchaseHostReservation(const PurchaseHostReservationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return PurchaseHostReservationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

PurchaseHostReservationOutcomeCallable EC2Client::PurchaseHostReservationCallable(const PurchaseHostReservationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< PurchaseHostReservationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->PurchaseHostReservation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::PurchaseHostReservationAsync(const PurchaseHostReservationRequest& request, const PurchaseHostReservationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, PurchaseHostReservation(request), context);
    } );
}

PurchaseReservedInstancesOfferingOutcome EC2Client::PurchaseReservedInstancesOffering(const PurchaseReservedInstancesOfferingRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return PurchaseReservedInstancesOfferingOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

PurchaseReservedInstancesOfferingOutcomeCallable EC2Client::PurchaseReservedInstancesOfferingCallable(const PurchaseReservedInstancesOfferingRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< PurchaseReservedInstancesOfferingOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->PurchaseReservedInstancesOffering(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::PurchaseReservedInstancesOfferingAsync(const PurchaseReservedInstancesOfferingRequest& request, const PurchaseReservedInstancesOfferingResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, PurchaseReservedInstancesOffering(request), context);
    } );
}

PurchaseScheduledInstancesOutcome EC2Client::PurchaseScheduledInstances(const PurchaseScheduledInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return PurchaseScheduledInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

PurchaseScheduledInstancesOutcomeCallable EC2Client::PurchaseScheduledInstancesCallable(const PurchaseScheduledInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< PurchaseScheduledInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->PurchaseScheduledInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::PurchaseScheduledInstancesAsync(const PurchaseScheduledInstancesRequest& request, const PurchaseScheduledInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, PurchaseScheduledInstances(request), context);
    } );
}

RebootInstancesOutcome EC2Client::RebootInstances(const RebootInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RebootInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RebootInstancesOutcomeCallable EC2Client::RebootInstancesCallable(const RebootInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RebootInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RebootInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RebootInstancesAsync(const RebootInstancesRequest& request, const RebootInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RebootInstances(request), context);
    } );
}

RegisterImageOutcome EC2Client::RegisterImage(const RegisterImageRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RegisterImageOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RegisterImageOutcomeCallable EC2Client::RegisterImageCallable(const RegisterImageRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RegisterImageOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RegisterImage(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RegisterImageAsync(const RegisterImageRequest& request, const RegisterImageResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RegisterImage(request), context);
    } );
}

RegisterInstanceEventNotificationAttributesOutcome EC2Client::RegisterInstanceEventNotificationAttributes(const RegisterInstanceEventNotificationAttributesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RegisterInstanceEventNotificationAttributesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RegisterInstanceEventNotificationAttributesOutcomeCallable EC2Client::RegisterInstanceEventNotificationAttributesCallable(const RegisterInstanceEventNotificationAttributesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RegisterInstanceEventNotificationAttributesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RegisterInstanceEventNotificationAttributes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RegisterInstanceEventNotificationAttributesAsync(const RegisterInstanceEventNotificationAttributesRequest& request, const RegisterInstanceEventNotificationAttributesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RegisterInstanceEventNotificationAttributes(request), context);
    } );
}

RegisterTransitGatewayMulticastGroupMembersOutcome EC2Client::RegisterTransitGatewayMulticastGroupMembers(const RegisterTransitGatewayMulticastGroupMembersRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RegisterTransitGatewayMulticastGroupMembersOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RegisterTransitGatewayMulticastGroupMembersOutcomeCallable EC2Client::RegisterTransitGatewayMulticastGroupMembersCallable(const RegisterTransitGatewayMulticastGroupMembersRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RegisterTransitGatewayMulticastGroupMembersOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RegisterTransitGatewayMulticastGroupMembers(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RegisterTransitGatewayMulticastGroupMembersAsync(const RegisterTransitGatewayMulticastGroupMembersRequest& request, const RegisterTransitGatewayMulticastGroupMembersResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RegisterTransitGatewayMulticastGroupMembers(request), context);
    } );
}

RegisterTransitGatewayMulticastGroupSourcesOutcome EC2Client::RegisterTransitGatewayMulticastGroupSources(const RegisterTransitGatewayMulticastGroupSourcesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RegisterTransitGatewayMulticastGroupSourcesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RegisterTransitGatewayMulticastGroupSourcesOutcomeCallable EC2Client::RegisterTransitGatewayMulticastGroupSourcesCallable(const RegisterTransitGatewayMulticastGroupSourcesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RegisterTransitGatewayMulticastGroupSourcesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RegisterTransitGatewayMulticastGroupSources(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RegisterTransitGatewayMulticastGroupSourcesAsync(const RegisterTransitGatewayMulticastGroupSourcesRequest& request, const RegisterTransitGatewayMulticastGroupSourcesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RegisterTransitGatewayMulticastGroupSources(request), context);
    } );
}

RejectTransitGatewayMulticastDomainAssociationsOutcome EC2Client::RejectTransitGatewayMulticastDomainAssociations(const RejectTransitGatewayMulticastDomainAssociationsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RejectTransitGatewayMulticastDomainAssociationsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RejectTransitGatewayMulticastDomainAssociationsOutcomeCallable EC2Client::RejectTransitGatewayMulticastDomainAssociationsCallable(const RejectTransitGatewayMulticastDomainAssociationsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RejectTransitGatewayMulticastDomainAssociationsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RejectTransitGatewayMulticastDomainAssociations(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RejectTransitGatewayMulticastDomainAssociationsAsync(const RejectTransitGatewayMulticastDomainAssociationsRequest& request, const RejectTransitGatewayMulticastDomainAssociationsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RejectTransitGatewayMulticastDomainAssociations(request), context);
    } );
}

RejectTransitGatewayPeeringAttachmentOutcome EC2Client::RejectTransitGatewayPeeringAttachment(const RejectTransitGatewayPeeringAttachmentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RejectTransitGatewayPeeringAttachmentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RejectTransitGatewayPeeringAttachmentOutcomeCallable EC2Client::RejectTransitGatewayPeeringAttachmentCallable(const RejectTransitGatewayPeeringAttachmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RejectTransitGatewayPeeringAttachmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RejectTransitGatewayPeeringAttachment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RejectTransitGatewayPeeringAttachmentAsync(const RejectTransitGatewayPeeringAttachmentRequest& request, const RejectTransitGatewayPeeringAttachmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RejectTransitGatewayPeeringAttachment(request), context);
    } );
}

RejectTransitGatewayVpcAttachmentOutcome EC2Client::RejectTransitGatewayVpcAttachment(const RejectTransitGatewayVpcAttachmentRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RejectTransitGatewayVpcAttachmentOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RejectTransitGatewayVpcAttachmentOutcomeCallable EC2Client::RejectTransitGatewayVpcAttachmentCallable(const RejectTransitGatewayVpcAttachmentRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RejectTransitGatewayVpcAttachmentOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RejectTransitGatewayVpcAttachment(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RejectTransitGatewayVpcAttachmentAsync(const RejectTransitGatewayVpcAttachmentRequest& request, const RejectTransitGatewayVpcAttachmentResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RejectTransitGatewayVpcAttachment(request), context);
    } );
}

RejectVpcEndpointConnectionsOutcome EC2Client::RejectVpcEndpointConnections(const RejectVpcEndpointConnectionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RejectVpcEndpointConnectionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RejectVpcEndpointConnectionsOutcomeCallable EC2Client::RejectVpcEndpointConnectionsCallable(const RejectVpcEndpointConnectionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RejectVpcEndpointConnectionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RejectVpcEndpointConnections(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RejectVpcEndpointConnectionsAsync(const RejectVpcEndpointConnectionsRequest& request, const RejectVpcEndpointConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RejectVpcEndpointConnections(request), context);
    } );
}

RejectVpcPeeringConnectionOutcome EC2Client::RejectVpcPeeringConnection(const RejectVpcPeeringConnectionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RejectVpcPeeringConnectionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RejectVpcPeeringConnectionOutcomeCallable EC2Client::RejectVpcPeeringConnectionCallable(const RejectVpcPeeringConnectionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RejectVpcPeeringConnectionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RejectVpcPeeringConnection(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RejectVpcPeeringConnectionAsync(const RejectVpcPeeringConnectionRequest& request, const RejectVpcPeeringConnectionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RejectVpcPeeringConnection(request), context);
    } );
}

ReleaseAddressOutcome EC2Client::ReleaseAddress(const ReleaseAddressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReleaseAddressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReleaseAddressOutcomeCallable EC2Client::ReleaseAddressCallable(const ReleaseAddressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReleaseAddressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReleaseAddress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReleaseAddressAsync(const ReleaseAddressRequest& request, const ReleaseAddressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReleaseAddress(request), context);
    } );
}

ReleaseHostsOutcome EC2Client::ReleaseHosts(const ReleaseHostsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReleaseHostsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReleaseHostsOutcomeCallable EC2Client::ReleaseHostsCallable(const ReleaseHostsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReleaseHostsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReleaseHosts(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReleaseHostsAsync(const ReleaseHostsRequest& request, const ReleaseHostsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReleaseHosts(request), context);
    } );
}

ReleaseIpamPoolAllocationOutcome EC2Client::ReleaseIpamPoolAllocation(const ReleaseIpamPoolAllocationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReleaseIpamPoolAllocationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReleaseIpamPoolAllocationOutcomeCallable EC2Client::ReleaseIpamPoolAllocationCallable(const ReleaseIpamPoolAllocationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReleaseIpamPoolAllocationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReleaseIpamPoolAllocation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReleaseIpamPoolAllocationAsync(const ReleaseIpamPoolAllocationRequest& request, const ReleaseIpamPoolAllocationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReleaseIpamPoolAllocation(request), context);
    } );
}

ReplaceIamInstanceProfileAssociationOutcome EC2Client::ReplaceIamInstanceProfileAssociation(const ReplaceIamInstanceProfileAssociationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReplaceIamInstanceProfileAssociationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReplaceIamInstanceProfileAssociationOutcomeCallable EC2Client::ReplaceIamInstanceProfileAssociationCallable(const ReplaceIamInstanceProfileAssociationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReplaceIamInstanceProfileAssociationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReplaceIamInstanceProfileAssociation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReplaceIamInstanceProfileAssociationAsync(const ReplaceIamInstanceProfileAssociationRequest& request, const ReplaceIamInstanceProfileAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReplaceIamInstanceProfileAssociation(request), context);
    } );
}

ReplaceNetworkAclAssociationOutcome EC2Client::ReplaceNetworkAclAssociation(const ReplaceNetworkAclAssociationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReplaceNetworkAclAssociationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReplaceNetworkAclAssociationOutcomeCallable EC2Client::ReplaceNetworkAclAssociationCallable(const ReplaceNetworkAclAssociationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReplaceNetworkAclAssociationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReplaceNetworkAclAssociation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReplaceNetworkAclAssociationAsync(const ReplaceNetworkAclAssociationRequest& request, const ReplaceNetworkAclAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReplaceNetworkAclAssociation(request), context);
    } );
}

ReplaceNetworkAclEntryOutcome EC2Client::ReplaceNetworkAclEntry(const ReplaceNetworkAclEntryRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReplaceNetworkAclEntryOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReplaceNetworkAclEntryOutcomeCallable EC2Client::ReplaceNetworkAclEntryCallable(const ReplaceNetworkAclEntryRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReplaceNetworkAclEntryOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReplaceNetworkAclEntry(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReplaceNetworkAclEntryAsync(const ReplaceNetworkAclEntryRequest& request, const ReplaceNetworkAclEntryResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReplaceNetworkAclEntry(request), context);
    } );
}

ReplaceRouteOutcome EC2Client::ReplaceRoute(const ReplaceRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReplaceRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReplaceRouteOutcomeCallable EC2Client::ReplaceRouteCallable(const ReplaceRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReplaceRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReplaceRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReplaceRouteAsync(const ReplaceRouteRequest& request, const ReplaceRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReplaceRoute(request), context);
    } );
}

ReplaceRouteTableAssociationOutcome EC2Client::ReplaceRouteTableAssociation(const ReplaceRouteTableAssociationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReplaceRouteTableAssociationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReplaceRouteTableAssociationOutcomeCallable EC2Client::ReplaceRouteTableAssociationCallable(const ReplaceRouteTableAssociationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReplaceRouteTableAssociationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReplaceRouteTableAssociation(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReplaceRouteTableAssociationAsync(const ReplaceRouteTableAssociationRequest& request, const ReplaceRouteTableAssociationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReplaceRouteTableAssociation(request), context);
    } );
}

ReplaceTransitGatewayRouteOutcome EC2Client::ReplaceTransitGatewayRoute(const ReplaceTransitGatewayRouteRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReplaceTransitGatewayRouteOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReplaceTransitGatewayRouteOutcomeCallable EC2Client::ReplaceTransitGatewayRouteCallable(const ReplaceTransitGatewayRouteRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReplaceTransitGatewayRouteOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReplaceTransitGatewayRoute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReplaceTransitGatewayRouteAsync(const ReplaceTransitGatewayRouteRequest& request, const ReplaceTransitGatewayRouteResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReplaceTransitGatewayRoute(request), context);
    } );
}

ReportInstanceStatusOutcome EC2Client::ReportInstanceStatus(const ReportInstanceStatusRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ReportInstanceStatusOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ReportInstanceStatusOutcomeCallable EC2Client::ReportInstanceStatusCallable(const ReportInstanceStatusRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ReportInstanceStatusOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ReportInstanceStatus(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ReportInstanceStatusAsync(const ReportInstanceStatusRequest& request, const ReportInstanceStatusResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ReportInstanceStatus(request), context);
    } );
}

RequestSpotFleetOutcome EC2Client::RequestSpotFleet(const RequestSpotFleetRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RequestSpotFleetOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RequestSpotFleetOutcomeCallable EC2Client::RequestSpotFleetCallable(const RequestSpotFleetRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RequestSpotFleetOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RequestSpotFleet(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RequestSpotFleetAsync(const RequestSpotFleetRequest& request, const RequestSpotFleetResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RequestSpotFleet(request), context);
    } );
}

RequestSpotInstancesOutcome EC2Client::RequestSpotInstances(const RequestSpotInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RequestSpotInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RequestSpotInstancesOutcomeCallable EC2Client::RequestSpotInstancesCallable(const RequestSpotInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RequestSpotInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RequestSpotInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RequestSpotInstancesAsync(const RequestSpotInstancesRequest& request, const RequestSpotInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RequestSpotInstances(request), context);
    } );
}

ResetAddressAttributeOutcome EC2Client::ResetAddressAttribute(const ResetAddressAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ResetAddressAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ResetAddressAttributeOutcomeCallable EC2Client::ResetAddressAttributeCallable(const ResetAddressAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ResetAddressAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ResetAddressAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ResetAddressAttributeAsync(const ResetAddressAttributeRequest& request, const ResetAddressAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ResetAddressAttribute(request), context);
    } );
}

ResetEbsDefaultKmsKeyIdOutcome EC2Client::ResetEbsDefaultKmsKeyId(const ResetEbsDefaultKmsKeyIdRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ResetEbsDefaultKmsKeyIdOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ResetEbsDefaultKmsKeyIdOutcomeCallable EC2Client::ResetEbsDefaultKmsKeyIdCallable(const ResetEbsDefaultKmsKeyIdRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ResetEbsDefaultKmsKeyIdOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ResetEbsDefaultKmsKeyId(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ResetEbsDefaultKmsKeyIdAsync(const ResetEbsDefaultKmsKeyIdRequest& request, const ResetEbsDefaultKmsKeyIdResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ResetEbsDefaultKmsKeyId(request), context);
    } );
}

ResetFpgaImageAttributeOutcome EC2Client::ResetFpgaImageAttribute(const ResetFpgaImageAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ResetFpgaImageAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ResetFpgaImageAttributeOutcomeCallable EC2Client::ResetFpgaImageAttributeCallable(const ResetFpgaImageAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ResetFpgaImageAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ResetFpgaImageAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ResetFpgaImageAttributeAsync(const ResetFpgaImageAttributeRequest& request, const ResetFpgaImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ResetFpgaImageAttribute(request), context);
    } );
}

ResetImageAttributeOutcome EC2Client::ResetImageAttribute(const ResetImageAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ResetImageAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ResetImageAttributeOutcomeCallable EC2Client::ResetImageAttributeCallable(const ResetImageAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ResetImageAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ResetImageAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ResetImageAttributeAsync(const ResetImageAttributeRequest& request, const ResetImageAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ResetImageAttribute(request), context);
    } );
}

ResetInstanceAttributeOutcome EC2Client::ResetInstanceAttribute(const ResetInstanceAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ResetInstanceAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ResetInstanceAttributeOutcomeCallable EC2Client::ResetInstanceAttributeCallable(const ResetInstanceAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ResetInstanceAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ResetInstanceAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ResetInstanceAttributeAsync(const ResetInstanceAttributeRequest& request, const ResetInstanceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ResetInstanceAttribute(request), context);
    } );
}

ResetNetworkInterfaceAttributeOutcome EC2Client::ResetNetworkInterfaceAttribute(const ResetNetworkInterfaceAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ResetNetworkInterfaceAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ResetNetworkInterfaceAttributeOutcomeCallable EC2Client::ResetNetworkInterfaceAttributeCallable(const ResetNetworkInterfaceAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ResetNetworkInterfaceAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ResetNetworkInterfaceAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ResetNetworkInterfaceAttributeAsync(const ResetNetworkInterfaceAttributeRequest& request, const ResetNetworkInterfaceAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ResetNetworkInterfaceAttribute(request), context);
    } );
}

ResetSnapshotAttributeOutcome EC2Client::ResetSnapshotAttribute(const ResetSnapshotAttributeRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return ResetSnapshotAttributeOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

ResetSnapshotAttributeOutcomeCallable EC2Client::ResetSnapshotAttributeCallable(const ResetSnapshotAttributeRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< ResetSnapshotAttributeOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->ResetSnapshotAttribute(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::ResetSnapshotAttributeAsync(const ResetSnapshotAttributeRequest& request, const ResetSnapshotAttributeResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, ResetSnapshotAttribute(request), context);
    } );
}

RestoreAddressToClassicOutcome EC2Client::RestoreAddressToClassic(const RestoreAddressToClassicRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RestoreAddressToClassicOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RestoreAddressToClassicOutcomeCallable EC2Client::RestoreAddressToClassicCallable(const RestoreAddressToClassicRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RestoreAddressToClassicOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RestoreAddressToClassic(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RestoreAddressToClassicAsync(const RestoreAddressToClassicRequest& request, const RestoreAddressToClassicResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RestoreAddressToClassic(request), context);
    } );
}

RestoreImageFromRecycleBinOutcome EC2Client::RestoreImageFromRecycleBin(const RestoreImageFromRecycleBinRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RestoreImageFromRecycleBinOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RestoreImageFromRecycleBinOutcomeCallable EC2Client::RestoreImageFromRecycleBinCallable(const RestoreImageFromRecycleBinRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RestoreImageFromRecycleBinOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RestoreImageFromRecycleBin(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RestoreImageFromRecycleBinAsync(const RestoreImageFromRecycleBinRequest& request, const RestoreImageFromRecycleBinResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RestoreImageFromRecycleBin(request), context);
    } );
}

RestoreManagedPrefixListVersionOutcome EC2Client::RestoreManagedPrefixListVersion(const RestoreManagedPrefixListVersionRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RestoreManagedPrefixListVersionOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RestoreManagedPrefixListVersionOutcomeCallable EC2Client::RestoreManagedPrefixListVersionCallable(const RestoreManagedPrefixListVersionRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RestoreManagedPrefixListVersionOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RestoreManagedPrefixListVersion(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RestoreManagedPrefixListVersionAsync(const RestoreManagedPrefixListVersionRequest& request, const RestoreManagedPrefixListVersionResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RestoreManagedPrefixListVersion(request), context);
    } );
}

RestoreSnapshotFromRecycleBinOutcome EC2Client::RestoreSnapshotFromRecycleBin(const RestoreSnapshotFromRecycleBinRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RestoreSnapshotFromRecycleBinOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RestoreSnapshotFromRecycleBinOutcomeCallable EC2Client::RestoreSnapshotFromRecycleBinCallable(const RestoreSnapshotFromRecycleBinRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RestoreSnapshotFromRecycleBinOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RestoreSnapshotFromRecycleBin(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RestoreSnapshotFromRecycleBinAsync(const RestoreSnapshotFromRecycleBinRequest& request, const RestoreSnapshotFromRecycleBinResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RestoreSnapshotFromRecycleBin(request), context);
    } );
}

RestoreSnapshotTierOutcome EC2Client::RestoreSnapshotTier(const RestoreSnapshotTierRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RestoreSnapshotTierOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RestoreSnapshotTierOutcomeCallable EC2Client::RestoreSnapshotTierCallable(const RestoreSnapshotTierRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RestoreSnapshotTierOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RestoreSnapshotTier(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RestoreSnapshotTierAsync(const RestoreSnapshotTierRequest& request, const RestoreSnapshotTierResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RestoreSnapshotTier(request), context);
    } );
}

RevokeClientVpnIngressOutcome EC2Client::RevokeClientVpnIngress(const RevokeClientVpnIngressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RevokeClientVpnIngressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RevokeClientVpnIngressOutcomeCallable EC2Client::RevokeClientVpnIngressCallable(const RevokeClientVpnIngressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RevokeClientVpnIngressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RevokeClientVpnIngress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RevokeClientVpnIngressAsync(const RevokeClientVpnIngressRequest& request, const RevokeClientVpnIngressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RevokeClientVpnIngress(request), context);
    } );
}

RevokeSecurityGroupEgressOutcome EC2Client::RevokeSecurityGroupEgress(const RevokeSecurityGroupEgressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RevokeSecurityGroupEgressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RevokeSecurityGroupEgressOutcomeCallable EC2Client::RevokeSecurityGroupEgressCallable(const RevokeSecurityGroupEgressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RevokeSecurityGroupEgressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RevokeSecurityGroupEgress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RevokeSecurityGroupEgressAsync(const RevokeSecurityGroupEgressRequest& request, const RevokeSecurityGroupEgressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RevokeSecurityGroupEgress(request), context);
    } );
}

RevokeSecurityGroupIngressOutcome EC2Client::RevokeSecurityGroupIngress(const RevokeSecurityGroupIngressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RevokeSecurityGroupIngressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RevokeSecurityGroupIngressOutcomeCallable EC2Client::RevokeSecurityGroupIngressCallable(const RevokeSecurityGroupIngressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RevokeSecurityGroupIngressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RevokeSecurityGroupIngress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RevokeSecurityGroupIngressAsync(const RevokeSecurityGroupIngressRequest& request, const RevokeSecurityGroupIngressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RevokeSecurityGroupIngress(request), context);
    } );
}

RunInstancesOutcome EC2Client::RunInstances(const RunInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RunInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RunInstancesOutcomeCallable EC2Client::RunInstancesCallable(const RunInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RunInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RunInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RunInstancesAsync(const RunInstancesRequest& request, const RunInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RunInstances(request), context);
    } );
}

RunScheduledInstancesOutcome EC2Client::RunScheduledInstances(const RunScheduledInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return RunScheduledInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

RunScheduledInstancesOutcomeCallable EC2Client::RunScheduledInstancesCallable(const RunScheduledInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< RunScheduledInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->RunScheduledInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::RunScheduledInstancesAsync(const RunScheduledInstancesRequest& request, const RunScheduledInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, RunScheduledInstances(request), context);
    } );
}

SearchLocalGatewayRoutesOutcome EC2Client::SearchLocalGatewayRoutes(const SearchLocalGatewayRoutesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return SearchLocalGatewayRoutesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

SearchLocalGatewayRoutesOutcomeCallable EC2Client::SearchLocalGatewayRoutesCallable(const SearchLocalGatewayRoutesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< SearchLocalGatewayRoutesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->SearchLocalGatewayRoutes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::SearchLocalGatewayRoutesAsync(const SearchLocalGatewayRoutesRequest& request, const SearchLocalGatewayRoutesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, SearchLocalGatewayRoutes(request), context);
    } );
}

SearchTransitGatewayMulticastGroupsOutcome EC2Client::SearchTransitGatewayMulticastGroups(const SearchTransitGatewayMulticastGroupsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return SearchTransitGatewayMulticastGroupsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

SearchTransitGatewayMulticastGroupsOutcomeCallable EC2Client::SearchTransitGatewayMulticastGroupsCallable(const SearchTransitGatewayMulticastGroupsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< SearchTransitGatewayMulticastGroupsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->SearchTransitGatewayMulticastGroups(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::SearchTransitGatewayMulticastGroupsAsync(const SearchTransitGatewayMulticastGroupsRequest& request, const SearchTransitGatewayMulticastGroupsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, SearchTransitGatewayMulticastGroups(request), context);
    } );
}

SearchTransitGatewayRoutesOutcome EC2Client::SearchTransitGatewayRoutes(const SearchTransitGatewayRoutesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return SearchTransitGatewayRoutesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

SearchTransitGatewayRoutesOutcomeCallable EC2Client::SearchTransitGatewayRoutesCallable(const SearchTransitGatewayRoutesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< SearchTransitGatewayRoutesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->SearchTransitGatewayRoutes(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::SearchTransitGatewayRoutesAsync(const SearchTransitGatewayRoutesRequest& request, const SearchTransitGatewayRoutesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, SearchTransitGatewayRoutes(request), context);
    } );
}

SendDiagnosticInterruptOutcome EC2Client::SendDiagnosticInterrupt(const SendDiagnosticInterruptRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return SendDiagnosticInterruptOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

SendDiagnosticInterruptOutcomeCallable EC2Client::SendDiagnosticInterruptCallable(const SendDiagnosticInterruptRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< SendDiagnosticInterruptOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->SendDiagnosticInterrupt(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::SendDiagnosticInterruptAsync(const SendDiagnosticInterruptRequest& request, const SendDiagnosticInterruptResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, SendDiagnosticInterrupt(request), context);
    } );
}

StartInstancesOutcome EC2Client::StartInstances(const StartInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return StartInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

StartInstancesOutcomeCallable EC2Client::StartInstancesCallable(const StartInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< StartInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->StartInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::StartInstancesAsync(const StartInstancesRequest& request, const StartInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, StartInstances(request), context);
    } );
}

StartNetworkInsightsAccessScopeAnalysisOutcome EC2Client::StartNetworkInsightsAccessScopeAnalysis(const StartNetworkInsightsAccessScopeAnalysisRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return StartNetworkInsightsAccessScopeAnalysisOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

StartNetworkInsightsAccessScopeAnalysisOutcomeCallable EC2Client::StartNetworkInsightsAccessScopeAnalysisCallable(const StartNetworkInsightsAccessScopeAnalysisRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< StartNetworkInsightsAccessScopeAnalysisOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->StartNetworkInsightsAccessScopeAnalysis(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::StartNetworkInsightsAccessScopeAnalysisAsync(const StartNetworkInsightsAccessScopeAnalysisRequest& request, const StartNetworkInsightsAccessScopeAnalysisResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, StartNetworkInsightsAccessScopeAnalysis(request), context);
    } );
}

StartNetworkInsightsAnalysisOutcome EC2Client::StartNetworkInsightsAnalysis(const StartNetworkInsightsAnalysisRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return StartNetworkInsightsAnalysisOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

StartNetworkInsightsAnalysisOutcomeCallable EC2Client::StartNetworkInsightsAnalysisCallable(const StartNetworkInsightsAnalysisRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< StartNetworkInsightsAnalysisOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->StartNetworkInsightsAnalysis(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::StartNetworkInsightsAnalysisAsync(const StartNetworkInsightsAnalysisRequest& request, const StartNetworkInsightsAnalysisResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, StartNetworkInsightsAnalysis(request), context);
    } );
}

StartVpcEndpointServicePrivateDnsVerificationOutcome EC2Client::StartVpcEndpointServicePrivateDnsVerification(const StartVpcEndpointServicePrivateDnsVerificationRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return StartVpcEndpointServicePrivateDnsVerificationOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

StartVpcEndpointServicePrivateDnsVerificationOutcomeCallable EC2Client::StartVpcEndpointServicePrivateDnsVerificationCallable(const StartVpcEndpointServicePrivateDnsVerificationRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< StartVpcEndpointServicePrivateDnsVerificationOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->StartVpcEndpointServicePrivateDnsVerification(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::StartVpcEndpointServicePrivateDnsVerificationAsync(const StartVpcEndpointServicePrivateDnsVerificationRequest& request, const StartVpcEndpointServicePrivateDnsVerificationResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, StartVpcEndpointServicePrivateDnsVerification(request), context);
    } );
}

StopInstancesOutcome EC2Client::StopInstances(const StopInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return StopInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

StopInstancesOutcomeCallable EC2Client::StopInstancesCallable(const StopInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< StopInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->StopInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::StopInstancesAsync(const StopInstancesRequest& request, const StopInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, StopInstances(request), context);
    } );
}

TerminateClientVpnConnectionsOutcome EC2Client::TerminateClientVpnConnections(const TerminateClientVpnConnectionsRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return TerminateClientVpnConnectionsOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

TerminateClientVpnConnectionsOutcomeCallable EC2Client::TerminateClientVpnConnectionsCallable(const TerminateClientVpnConnectionsRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< TerminateClientVpnConnectionsOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->TerminateClientVpnConnections(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::TerminateClientVpnConnectionsAsync(const TerminateClientVpnConnectionsRequest& request, const TerminateClientVpnConnectionsResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, TerminateClientVpnConnections(request), context);
    } );
}

TerminateInstancesOutcome EC2Client::TerminateInstances(const TerminateInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return TerminateInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

TerminateInstancesOutcomeCallable EC2Client::TerminateInstancesCallable(const TerminateInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< TerminateInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->TerminateInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::TerminateInstancesAsync(const TerminateInstancesRequest& request, const TerminateInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, TerminateInstances(request), context);
    } );
}

UnassignIpv6AddressesOutcome EC2Client::UnassignIpv6Addresses(const UnassignIpv6AddressesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return UnassignIpv6AddressesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

UnassignIpv6AddressesOutcomeCallable EC2Client::UnassignIpv6AddressesCallable(const UnassignIpv6AddressesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UnassignIpv6AddressesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UnassignIpv6Addresses(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::UnassignIpv6AddressesAsync(const UnassignIpv6AddressesRequest& request, const UnassignIpv6AddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, UnassignIpv6Addresses(request), context);
    } );
}

UnassignPrivateIpAddressesOutcome EC2Client::UnassignPrivateIpAddresses(const UnassignPrivateIpAddressesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return UnassignPrivateIpAddressesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

UnassignPrivateIpAddressesOutcomeCallable EC2Client::UnassignPrivateIpAddressesCallable(const UnassignPrivateIpAddressesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UnassignPrivateIpAddressesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UnassignPrivateIpAddresses(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::UnassignPrivateIpAddressesAsync(const UnassignPrivateIpAddressesRequest& request, const UnassignPrivateIpAddressesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, UnassignPrivateIpAddresses(request), context);
    } );
}

UnmonitorInstancesOutcome EC2Client::UnmonitorInstances(const UnmonitorInstancesRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return UnmonitorInstancesOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

UnmonitorInstancesOutcomeCallable EC2Client::UnmonitorInstancesCallable(const UnmonitorInstancesRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UnmonitorInstancesOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UnmonitorInstances(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::UnmonitorInstancesAsync(const UnmonitorInstancesRequest& request, const UnmonitorInstancesResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, UnmonitorInstances(request), context);
    } );
}

UpdateSecurityGroupRuleDescriptionsEgressOutcome EC2Client::UpdateSecurityGroupRuleDescriptionsEgress(const UpdateSecurityGroupRuleDescriptionsEgressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return UpdateSecurityGroupRuleDescriptionsEgressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

UpdateSecurityGroupRuleDescriptionsEgressOutcomeCallable EC2Client::UpdateSecurityGroupRuleDescriptionsEgressCallable(const UpdateSecurityGroupRuleDescriptionsEgressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateSecurityGroupRuleDescriptionsEgressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateSecurityGroupRuleDescriptionsEgress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::UpdateSecurityGroupRuleDescriptionsEgressAsync(const UpdateSecurityGroupRuleDescriptionsEgressRequest& request, const UpdateSecurityGroupRuleDescriptionsEgressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, UpdateSecurityGroupRuleDescriptionsEgress(request), context);
    } );
}

UpdateSecurityGroupRuleDescriptionsIngressOutcome EC2Client::UpdateSecurityGroupRuleDescriptionsIngress(const UpdateSecurityGroupRuleDescriptionsIngressRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return UpdateSecurityGroupRuleDescriptionsIngressOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

UpdateSecurityGroupRuleDescriptionsIngressOutcomeCallable EC2Client::UpdateSecurityGroupRuleDescriptionsIngressCallable(const UpdateSecurityGroupRuleDescriptionsIngressRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< UpdateSecurityGroupRuleDescriptionsIngressOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->UpdateSecurityGroupRuleDescriptionsIngress(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::UpdateSecurityGroupRuleDescriptionsIngressAsync(const UpdateSecurityGroupRuleDescriptionsIngressRequest& request, const UpdateSecurityGroupRuleDescriptionsIngressResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, UpdateSecurityGroupRuleDescriptionsIngress(request), context);
    } );
}

WithdrawByoipCidrOutcome EC2Client::WithdrawByoipCidr(const WithdrawByoipCidrRequest& request) const
{
  Aws::Http::URI uri = m_uri;
  return WithdrawByoipCidrOutcome(MakeRequest(uri, request, Aws::Http::HttpMethod::HTTP_POST));
}

WithdrawByoipCidrOutcomeCallable EC2Client::WithdrawByoipCidrCallable(const WithdrawByoipCidrRequest& request) const
{
  auto task = Aws::MakeShared< std::packaged_task< WithdrawByoipCidrOutcome() > >(ALLOCATION_TAG, [this, request](){ return this->WithdrawByoipCidr(request); } );
  auto packagedFunction = [task]() { (*task)(); };
  m_executor->Submit(packagedFunction);
  return task->get_future();
}

void EC2Client::WithdrawByoipCidrAsync(const WithdrawByoipCidrRequest& request, const WithdrawByoipCidrResponseReceivedHandler& handler, const std::shared_ptr<const Aws::Client::AsyncCallerContext>& context) const
{
  m_executor->Submit( [this, request, handler, context]()
    {
      handler(this, request, WithdrawByoipCidr(request), context);
    } );
}

