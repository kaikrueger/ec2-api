/*
 * @file   options_ec2-describe-images.hpp
 * @date   2011-10-17
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
#ifndef _options_ec2_describe_images_hpp_
#define _options_ec2_describe_images_hpp_

#include "options.hpp"

namespace ec2 {
  namespace options {
    class ec2_describe_images  : public ec2::options::optionCommand {
    public:
      typedef ec2::shared_ptr<ec2_describe_images> Ptr;

      ec2_describe_images() : optionCommand("DescribeImages", "DescribeInstancesResponse") {
        complete(specific());
      }
      virtual ~ec2_describe_images() {}
      
      void setOptions(const po::variables_map &vm, const std::vector<std::string> rest, ec2::Map_Type &opt) {
        for (unsigned int i = 0; i < rest.size(); ++i) {
          std::stringstream key;
          key << "ImageId."<< (i+1);
          opt[key.str()] = rest[i];
        }
        if ( !vm.count("all")) {
          opt["Owner.1"]   = "self";
        }
      }

      void help() {
        std::cout<< "SYNOPSIS"<< std::endl;
        std::cout<< "  ec2-describe-images [GENERAL OPTIONS] [AMI [...]] [-a] [-o OWNER [...]] [-x USER [...]]"<< std::endl;
        std::cout<< "DESCRIPTION"<< std::endl;
        std::cout<< "  List and describe registered AMIs and AMIs you have launch permissions for."<< std::endl;
        std::cout<< "  The AMI parameters, if specified, are the AMIs to describe."<< std::endl;
        std::cout<< "  The result set of AMIs described are the intersection of the AMIs specified,"<< std::endl;
        std::cout<< "  AMIs owned by the owners specified and AMIs with launch permissions as specified"<< std::endl;
        std::cout<< "  by the executable by options."<< std::endl;
        std::cout << cmdline_options() << std::endl;
      }
      
      const po::options_description &specific() {
        static po::options_description specific("SPECIFIC OPTIONS");
        specific.add_options()
          ("all,a", "Describe all AMIs, public, private or owned, that the user has access to.")
          ("owner,o", po::value< std::string >(), "OWNER Only AMIs owned by the users specified are described. OWNER may either be a"
           "user's account id for images owned by that user, 'self' for images owned by"
           "you, or 'amazon' for images owned by Amazon.")
          ("executable-by,x",po::value< std::string >(), " USER"
           "Only AMIs with launch permissions as specified are described. USER may either"
           "be a user's account id for AMIs owned by you for which the user has explicit"
           "launch permissions, 'self' for AMIs you have explicit launch permissions for,"
           "or 'all' for AMIs with public launch permissions.")
          ;
        return specific;
      };

      void printResponse(const ec2::xml::parse::type::EC2Response_t &response) {
        std::cout << response;
      };
      //po::options_description operator &() { };
    };
    
      
  } //namespace options
} // namespace ec2
#endif /* _options_ec2-describe-images_hpp_ */
