/*
 * @file   options_ec2-run-instances.hpp
 * @date   2011-10-18
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

#ifndef _options_ec2_run_instances_hpp_
#define _options_ec2_run_instances_hpp_

#include "options.hpp"

namespace ec2 {
  namespace options {
    class  ec2_run_instances : public ec2::options::optionCommand {
    public:
      typedef ec2::shared_ptr<ec2_run_instances> Ptr;

      ec2_run_instances() : optionCommand("RunInstances", "RunInstancesResponse") {
        complete(specific());
      }
      virtual ~ec2_run_instances() {}
      
      void setOptions(const po::variables_map &vm, const std::vector<std::string> rest, ec2::Map_Type &opt) {
        for (unsigned int i = 0; i < rest.size(); ++i) {
          std::stringstream key;
          key << "ImageId."<< (i+1);
          opt[key.str()] = rest[i];
        }
    
        if (vm.count("instance-count")) {
          std::string ic = vm["instance-count"].as<std::string>();
          size_t pos = ic.find("-");    // position of "live" in str
          if(pos != std::string::npos) {
            if(pos>0) opt["MinCount"]        = ic.substr(0, pos);
            else opt["MinCount"]        = "1";
            opt["MaxCount"]        = ic.substr(pos+1);
          }
          else {
            opt["MinCount"]        = "1";
            opt["MaxCount"]        = ic;
          }
          
        } else {
          opt["MinCount"]        = "1";
          opt["MaxCount"]        = "1";
        }
        
      }

      void help() {
        std::cout<< "SYNOPSIS"<< std::endl;
        std::cout<< "  ec2-run-instances [GENERAL OPTIONS] AMI [SPECIFIC OPTIONS]"<< std::endl;
        std::cout<< "DESCRIPTION"<< std::endl;
        std::cout<< "  Launch a number of instances of a specified AMI."<< std::endl;
        std::cout<< "  The AMI parameter is the AMI ID of the AMI to launch."<< std::endl;
        std::cout << cmdline_options() << std::endl;
      }

      const po::options_description &specific() {
        static po::options_description specific("SPECIFIC OPTIONS");
        specific.add_options()
          ("group,g", po::value< std::string >(), 
           "Specifies the security group (or groups if specified multiple times)"
          "within which the instance(s) should be run. Determines the ingress"
          "firewall rules that will be applied to the launched instances."
          "Defaults to the user's default group if not supplied.")
          ("instance-count,n", po::value< std::string >(),
           "The number of instances to attempt to launch. May be specified as a"
          "single integer or as a range (min-max). This specifies the minumum"
          "and maximum number of instances to attempt to launch. If a single"
          "integer is specified min and max are both set to that value.")
          ("instance-type,t", po::value< std::string >(),
           "Specifies the type of instance to be launched. Refer to the latest"
           "Developer's Guide for valid values.")
          ("kernel", po::value< std::string >(), 
           "Specifies the ID of the kernel to launch the instance(s) with.")
          ("ramdisk", po::value< std::string >(), 
           "Specifies the ID of the ramdisk to launch the instance(s) with.")
          //("", ,po::value< std::string >(), "")
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
#endif /* _options_ec2_run_instances_hpp_ */
