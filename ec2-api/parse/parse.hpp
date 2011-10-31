/*
 * @file   parse.hpp
 * @date   2011-08-10
 *
 * Created by Kai Krueger <kai.krueger@itwm.fraunhofer.de>
 *
 * Copyright (c) 2011 Fraunhofer ITWM
 * All rights reserved.
 * 
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  XML parser for the ec2 responses.
 *
 */
#ifndef _parse_hpp_
#define _parse_hpp_

#include <string.h>

#include <ec2-api/parse/rapidxml/1.13/rapidxml.hpp>
#include <ec2-api/parse/rapidxml/1.13/rapidxml_utils.hpp>

#include <ec2-api/parse/util.hpp>

#include <ec2-api/parse/error.hpp>
#include <ec2-api/parse/warning.hpp>
#include <ec2-api/parse/types.hpp>
#include <ec2-api/parse/state.hpp>

#ifdef XMLPARSER_ANLONE
void print_node_tree(const rapidxml::xml_node<> *node);
#endif

namespace ec2 {
  namespace xml {
    namespace parse {
      static type::EC2Response_t EC2Response_t (const xml_node_type *
                                                , state::type &
                                                );

      static type::Response_t Response_t (const xml_node_type * , state::type &);

      static type::AuthorizeSecurityGroupIngressResponse_t AuthorizeSecurityGroupIngressResponse_t (const xml_node_type *
                                                                                                    , state::type &
                                                                                                    );

      static type::CreateSecurityGroupResponse_t CreateSecurityGroupResponse_t (const xml_node_type *
                                                                                , state::type &
                                                                                );

      static type::DescribeSecurityGroupsResponse_t DescribeSecurityGroupsResponse_t (const xml_node_type *
                                                                                      , state::type &
                                                                                      );

      static type::DescribeImagesResponse_t DescribeImagesResponse_t (const xml_node_type *
                                                                      , state::type &
                                                                      );
      static type::DescribeInstancesResponse_t DescribeInstancesResponse_t (const xml_node_type *
                                                                            , state::type &
                                                                            );
      static type::RunInstancesResponse_t RunInstancesResponse_t (const xml_node_type *
                                                                  , state::type &
                                                                  );
      static type::TerminateInstancesResponse_t TerminateInstancesResponse_t (const xml_node_type *
                                                                              , state::type &
                                                                              );

      static type::Error_t    Error_t (const xml_node_type *node, state::type &state);
      static type::groupSet_t groupSet_t (const xml_node_type *, state::type &);
      static type::stateReason_t stateReason_t (const xml_node_type *
                                                , state::type &
                                                );
      static type::imagesSet_t imagesSet_t (const xml_node_type *, state::type &);
      static type::instancesSet_t instancesSet_t (const xml_node_type *
                                                  , state::type &
                                                  );
      static type::instancesState_t instancesState_t (const xml_node_type *
                                                      , state::type &
                                                      );
      static type::reservationSet_t reservationSet_t (const xml_node_type *
                                                      , state::type &
                                                      );
      static type::ipPermissions_t ipPermissions_t (const xml_node_type *node
                                                    , state::type &state
                                                    );
      static type::securityGroupInfo_t securityGroupInfo_t (const xml_node_type *
                                                            , state::type &
                                                            );

      // ********************************************************************* //
      template<typename T>
      static T
      generic_parse ( T (*parse)(const xml_node_type *
                                 , state::type &
                                 )
                      , std::stringstream & f
                      , state::type & state
                      , const std::string & name_wanted
                      , const std::string & pre
                      )
      {
        xml_document_type doc;

        input_type inp (f);

        doc.parse < rapidxml::parse_full
          | rapidxml::parse_trim_whitespace
          | rapidxml::parse_normalize_whitespace
          > (inp.data())
          ;

        xml_node_type * node (doc.first_node());

        if (!node) {
          throw error::no_elements_given (pre);
        }

        skip (node, rapidxml::node_declaration);

        const std::string name (name_element (node));

        if (!node) {
          throw error::no_elements_given (pre);
        }

        if (name != name_wanted && name != "Response") {
          state.warn (warning::unexpected_element (name, pre));
        }

        if (node->next_sibling()) {
          throw error::more_than_one_definition (pre);
        }

        return parse (node, state);
      }

      // ********************************************************************* //
      static type::EC2Response_t EC2Response_t (const xml_node_type * node
                                                , state::type & state
                                                ) {
        type::EC2Response_t f;

        //const std::string node_name (name_element (node));
        const std::string node_name (node->name());
        //std::cout << "EC2Response: '"<< node_name << "'"<< std::endl;
        
        if (node_name == "Response")      f.Response(Response_t(node, state));
        else if( node_name == "AuthorizeSecurityGroupIngressResponse" ) 
          f.AuthorizeSecurityGroupIngressResponse(AuthorizeSecurityGroupIngressResponse_t(node, state));
        else if( node_name == "CreateSecurityGroupResponse" ) 
          f.CreateSecurityGroupResponse(CreateSecurityGroupResponse_t(node, state));
        else if (node_name == "DescribeImagesResponse")
          f.DescribeImagesResponse(DescribeImagesResponse_t(node, state));
        else if( node_name == "DescribeInstancesResponse" ) 
          f.DescribeInstancesResponse(DescribeInstancesResponse_t(node, state));
        else if( node_name == "DescribeSecurityGroupsResponse" ) 
          f.DescribeSecurityGroupsResponse(DescribeSecurityGroupsResponse_t(node, state));
        else if( node_name == "RunInstancesResponse" ) 
          f.RunInstancesResponse(RunInstancesResponse_t(node, state));
        else if( node_name == "TerminateInstancesResponse" ) 
          f.TerminateInstancesResponse(TerminateInstancesResponse_t(node, state));
        else {
          throw error::unexpected_element (node_name, "EC2Response_t");
        }

        return f;
      }

      // ********************************************************************* //
      static type::Response_t Response_t (const xml_node_type * node
                                          , state::type & state
                                          ) {
        type::Response_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "Errors") {
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "Error" )  f.error(Error_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "Response_t/Errors");
                }
              }
            } else if (child_name == "RequestID") f.requestId(child->value());
            else {
              throw error::unexpected_element (child_name, "Response_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::AuthorizeSecurityGroupIngressResponse_t AuthorizeSecurityGroupIngressResponse_t (
        const xml_node_type *node, state::type &state) {
        type::AuthorizeSecurityGroupIngressResponse_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "requestId") f.requestId(child->value());
            else if (child_name == "return") f.returnVal(fromString<bool>(child->value()));
            else {
              throw error::unexpected_element (child_name, "AuthorizeSecurityGroupIngressResponse_t");
            }
          }
        }

        return f;
      }


      // ********************************************************************* //
      static type::CreateSecurityGroupResponse_t CreateSecurityGroupResponse_t (const xml_node_type *node
                                                                                , state::type &state
                                                                                ) {
        type::CreateSecurityGroupResponse_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "requestId") f.requestId(child->value());
            else if (child_name == "return") f.returnVal(fromString<bool>(child->value()));
            else if (child_name == "groupId") f.groupId(child->value());
            else {
              throw error::unexpected_element (child_name, "CreateSecurityGroupResponse_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::DescribeImagesResponse_t DescribeImagesResponse_t (const xml_node_type * node
                                                                      , state::type & state
                                                                      ) {
        type::DescribeImagesResponse_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "requestId") f.requestId(child->value());
            else if (child_name == "imagesSet") {
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "item" ) f.imagesSet(imagesSet_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "DescribeImagesResponse_t/imagesSet");
                }
              }
            } else {
              throw error::unexpected_element (child_name, "DescribeImagesResponse_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::DescribeInstancesResponse_t DescribeInstancesResponse_t (const xml_node_type * node
                                                                            , state::type & state
                                                                            ) {
        type::DescribeInstancesResponse_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "requestId") f.requestId(child->value());
            else if (child_name == "reservationSet") {
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "item" ) f.reservationSet(reservationSet_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "DescribeInstancesResponse_t/reservationSet");
                }
              }
            } else {
              throw error::unexpected_element (child_name, "DescribeInstancesResponse_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::DescribeSecurityGroupsResponse_t DescribeSecurityGroupsResponse_t (const xml_node_type * node
                                                                                      , state::type & state
                                                                                      ) {
        type::DescribeSecurityGroupsResponse_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "requestId") f.requestId(child->value());
            else if (child_name == "securityGroupInfo") {
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "item" ) f.securityGroupInfo(securityGroupInfo_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "DescribeSecurityGroupsResponse_t/securityGroupInfo");
                }
              }
            } else {
              throw error::unexpected_element (child_name, "DescribeSecurityGroupsResponse_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::RunInstancesResponse_t RunInstancesResponse_t (const xml_node_type * node
                                                                  , state::type & state
                                                                  ) {
        type::RunInstancesResponse_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));
          //std::cout<<"  RunInstancesResponse: "<< child_name<<"\n";
        
          if (child)
          {
            if (child_name == "requestId") f.requestId(child->value());
            else if (child_name == "reservationId") f.reservationId(child->value());
            else if (child_name == "ownerId") f.ownerId(child->value());
            else if (child_name == "groupSet") {
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "item" ) f.groupSet(groupSet_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "RunInstancesResponse_t/groupSet");
                }
              }
            } else if (child_name == "instancesSet") {
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "item" ) f.instancesSet(instancesSet_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "RunInstancesResponse_t/instancesSet");
                }
              }
            } else {
              throw error::unexpected_element (child_name, "RunInstancesResponse_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::TerminateInstancesResponse_t TerminateInstancesResponse_t (const xml_node_type * node
                                                                              , state::type & state
                                                                              ) {
        type::TerminateInstancesResponse_t f;
        //parse_TerminateInstancesResponse_attributes(node, state);

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "requestId") f.requestId(child->value());
            else if (child_name == "instancesSet") {
              //xml_node_type * item = child->value();
              f.instancesSet(instancesSet_t(child->first_node(), state));
            } else
            {
              throw error::unexpected_element (child_name, "TerminateInstancesResponse_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::Error_t Error_t (const xml_node_type *node
                                    , state::type &state
                                    ) {
        type::Error_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "Code")    f.code(child->value());
            else if (child_name == "Message")  f.message(child->value());
            else {
              throw error::unexpected_element (child_name, "Error_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::groupSet_t groupSet_t (const xml_node_type *node
                                          , state::type &state
                                          ) {
        type::groupSet_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "groupId")    f.groupId(child->value());
            else if (child_name == "groupName")  f.groupName(child->value());
            else {
              throw error::unexpected_element (child_name, "groupSet_type");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::stateReason_t stateReason_t (const xml_node_type *node
                                                , state::type &state
                                                ) {
        type::stateReason_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "code")    f.code(child->value());
            else if (child_name == "message")  f.message(child->value());
            else {
              throw error::unexpected_element (child_name, "stateReason_type");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::imagesSet_t imagesSet_t (const xml_node_type *node
                                            , state::type &state
                                            ) {
        type::imagesSet_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));
          //std::cout<< "   => "<< child_name<< "\n";
        
          if (child)
          {
            if (child_name == "imageId")    f.imageId(child->value());
            else if (child_name == "imageLocation")  f.imageLocation(child->value());
            else if (child_name == "imageState") f.imageState(child->value());
            else if (child_name == "imageOwnerId") f.imageOwnerId(child->value());
            else if (child_name == "isPublic") f.isPublic(fromString<bool>(child->value()));
            else if (child_name == "productCodes") {}//f.productCodes(productCodes_t(child, state));
            else if (child_name == "architecture") f.architecture(child->value());
            else if (child_name == "imageType") f.imageType(child->value());
            else if (child_name == "platform")  f.platform(child->value());
            else if (child_name == "stateReason") f.stateReason(stateReason_t(child, state));
            else if (child_name == "name")      f.name(child->value());
            else if (child_name == "description")  f.description(child->value());
            else if (child_name == "kernelId")  f.kernelId(child->value());
            else if (child_name == "imageOwnerAlias") f.imageOwnerAlias(child->value());
            else if (child_name == "ramdiskId")  f.ramdiskId(child->value());
            else if (child_name == "rootDeviceType")  f.rootDeviceType(child->value());
            else if (child_name == "rootDeviceName")  f.rootDeviceName(child->value());
            else if (child_name == "blockDeviceMapping")  f.blockDeviceMapping(child->value());
            else if (child_name == "virtualizationType")  f.virtualizationType(child->value());
            else if (child_name == "hypervisor")  f.hypervisor(child->value());
            else
            {
              throw error::unexpected_element (child_name, "imagesSet_type");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::instancesSet_t instancesSet_t (const xml_node_type *node
                                                  , state::type &state
                                                  ) {
        type::instancesSet_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));
          //std::cout<< "   => "<< child_name<< "\n";
        
          if (child)
          {
            if (child_name == "instanceId")    f.instanceId(child->value());
            else if (child_name == "imageId")  f.imageId(child->value());
            else if (child_name == "instanceState") f.instanceState(instancesState_t(child, state));
            else if (child_name == "currentState") f.currentState(instancesState_t(child, state));
            else if (child_name == "previousState") f.previousState(instancesState_t(child, state));
            else if (child_name == "privateDnsName") f.privateDnsName(child->value());
            else if (child_name == "dnsName") f.dnsName(child->value());
            else if (child_name == "reason")  f.reason(child->value());
            else if (child_name == "keyName")  { /*f.reason(child->value());*/ 
            }
            else if (child_name == "amiLaunchIndex") f.amiLaunchIndex(fromString<int>(child->value()));
            else if (child_name == "productCodes") f.productCodes(child->value());
            else if (child_name == "instanceType") f.instanceType(child->value());
            else if (child_name == "launchTime") f.launchTime(child->value());
            else if (child_name == "placement") {
              //std::cout<< "placement\n"; 
            } else if (child_name == "kernelId") f.kernelId(child->value());
            else if (child_name == "ramdiskId") f.ramdiskId(child->value());
            else if (child_name == "monitoring") {
              //f.(child->value());
              //std::cout<< "monitoring\n"; 
            } else if (child_name == "privateIpAddress") f.privateIpAddress(child->value());
            else if (child_name == "ipAddress") f.ipAddress(child->value());
            else if (child_name == "groupSet") {
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "item" ) f.groupSet(groupSet_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "instancesSet_t/groupSet");
                }
              }
            } else if (child_name == "stateReason") f.stateReason(stateReason_t(child, state));
            else if (child_name == "architecture")  f.architecture(child->value());
            else if (child_name == "rootDeviceType") f.rootDeviceType(child->value());
            else if (child_name == "blockDeviceMapping") f.blockDeviceMapping(child->value());
            else if (child_name == "virtualizationType") f.virtualizationType(child->value());
            else if (child_name == "clientToken") f.clientToken(child->value());
            else if (child_name == "hypervisor") f.hypervisor(child->value());
            //} else if (child_name == "") {
            //std::cout<< "\n"; 
            //} else if (child_name == "") {
            //std::cout<< "\n"; 
            //} else if (child_name == "") {
            //std::cout<< "\n"; 
            else
            {
              throw error::unexpected_element (child_name, "instancesSet_type");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::instancesState_t instancesState_t (const xml_node_type *node
                                                      , state::type &state
                                                      ) {
        type::instancesState_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "code")    f.code(fromString<int>(child->value()));
            else if (child_name == "name")  f.name(child->value());
            else {
              throw error::unexpected_element (child_name, "instancesSet_type");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::reservationSet_t reservationSet_t (const xml_node_type *node
                                                      , state::type &state
                                                      ) {
        type::reservationSet_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "reservationId")    f.reservationId(child->value());
            else if (child_name == "ownerId")  f.ownerId(child->value());
            else if (child_name == "instancesSet") {
              //std::cout<< "====> instancesSet\n";
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "item" ) f.instancesSet(instancesSet_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "DescribeInstancesResponse_t/reservationSet");
                }
              }
            } else if (child_name == "groupSet") {
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "item" ) f.groupSet(groupSet_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "RunInstancesResponse_t/groupSet");
                }
              }
              //std::cout<< "  reservationSet/groupSet\n"; 
            } else
            {
              throw error::unexpected_element (child_name, "reservationSet_type");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::ipPermissions_t ipPermissions_t (const xml_node_type *node
                                                    , state::type &state
                                                    ) {
        type::ipPermissions_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "ipProtocol")    f.ipProtocol(child->value());
            else if (child_name == "fromPort")  f.fromPort(child->value());
            else if (child_name == "toPort")  f.toPort(child->value());
            else if (child_name == "groups")  f.groups(child->value());
            else if (child_name == "ipRanges") {
            } else
            {
              throw error::unexpected_element (child_name, "ipPermissions_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      static type::securityGroupInfo_t securityGroupInfo_t (const xml_node_type *node
                                                            , state::type &state
                                                            ) {
        type::securityGroupInfo_t f;

        for ( xml_node_type * child (node->first_node())
                ; child
                ; child = child ? child->next_sibling() : child
              )
        {
          const std::string child_name (name_element (child));

          if (child)
          {
            if (child_name == "ownerId")    f.ownerId(child->value());
            else if (child_name == "groupId")  f.groupId(child->value());
            else if (child_name == "groupName")  f.groupName(child->value());
            else if (child_name == "groupDescription")  f.groupDescription(child->value());
            else if (child_name == "ipPermissions") {
              //std::cout<< "====> instancesSet\n";
              for ( xml_node_type * item (child->first_node())
                      ; item
                      ; item = item ? item->next_sibling() : item
                    ) {
                const std::string item_name (name_element (item));
                if( item_name == "item" ) f.ipPermissions(ipPermissions_t(item, state));
                else {
                  throw error::unexpected_element (item_name, "securityGroupInfo_t/ipPermissions");
                }
              }
            } else if (child_name == "ipPermissionsEgress") {
            } else
            {
              throw error::unexpected_element (child_name, "securityGroupInfo_t");
            }
          }
        }

        return f;
      }

      // ********************************************************************* //
      /*---------------------------------------------------------------------*/
      /** parse_EC2Response
       * @brief parses XML response from EC2 call.

       @param[in] f       XML stream
       @param[in] state   state
       @param[in] expect  expected tag
       @return type::EC2Response_t parsed response data
      **/
      /*---------------------------------------------------------------------*/
      static type::EC2Response_t
      parse_EC2Response (std::stringstream & f, state::type & state, const std::string &expect="EC2Response") {
        return generic_parse (EC2Response_t, f, state,
                              expect, "parse_EC2Response");
      }


    } // namespace parse
  } // namespace xml
} // namespace pg

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 * End:
 */
#endif /* _parse_hpp_ */
