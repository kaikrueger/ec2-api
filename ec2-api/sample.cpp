/*
 * @file   sample.cpp
 * @date   2011-08-09
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

#include <iostream>

#include <ec2-api/ec2.hpp>
#include <ec2-api/SimpleRequestObserver.hpp>

const std::string EC2_ACCESS_KEY("");
const std::string EC2_SECRET_KEY("");
const std::string EC2_USER("");


int main(
  int argc,
  char *argv[]
  )
{
  ec2::Map_Type opt;
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::RequestObserver::Ptr Observer(ec2::RequestObserver::Ptr(new ec2::SimpleRequestObserver()));
  

  ec2::CFRuntime sdk(Observer, EC2_ACCESS_KEY, EC2_SECRET_KEY, EC2_USER);
  sdk.setDebug();
  
  //sdk.authenticate("DescribeKeyPairs");

  // Describe instances
  try {
    //opt["Owner.1"]   = "self";
    opt["ImageId.1"] = "ami-00857e69";
    ret =  sdk.DescribeImages(opt);
    std::cout << "============= DescribeImages ==============\n";
    std::cout << ret << std::endl;
    std::cout << "===========================================\n";
  } catch( std::exception &e ) {
    std::cout<<"==>> Call failed due to: "<< e.what() << std::endl;
  }
  
  try {
    ret =  sdk.DescribeInstances();
    std::cout << ret << std::endl;
    std::cout << "===========================================\n";
  } catch( std::exception &e ) {
    std::cout<<"==>> Call failed due to: "<< e.what() << std::endl;
  }

  try {
    ret =  sdk.DescribeInstances();
    std::cout << ret << std::endl;
  } catch( std::exception &e ) {
    std::cout<<"==>> Call failed due to: "<< e.what() <<  std::endl;
  }

  // DescribeSecurityGroups
  try {
    opt.clear();
    //opt["Owner.1"]   = "self";
    //opt["ImageId.1"] = "ami-00857e69";
    opt["GroupName.1"] = "blahh";
    ret =  sdk.DescribeSecurityGroups(opt);
    std::cout << ret << std::endl;
    std::cout << "===========================================\n";
  } catch( std::exception &e ) {
    std::cout<<"==>> Call failed due to: "<< e.what() << std::endl;
  }

  // DescribeSecurityGroups
  try {
    opt.clear();
    //opt["Owner.1"]   = "self";
    //opt["ImageId.1"] = "ami-00857e69";
    opt["GroupName.1"] = "s4cloud";
    ret =  sdk.DescribeSecurityGroups(opt);
    std::cout << ret << std::endl;
    std::cout << "===========================================\n";
  } catch( std::exception &e ) {
    std::cout<<"==>> Call failed due to: "<< e.what() << std::endl;
  }
#if 1
 try {
    opt.clear();
    opt["Owner.1"]   = "self";
    //opt["ImageId.1"] = "ami-00857e69";
    ret = sdk.DescribeImages(opt);
    std::cout << ret << std::endl;
    std::cout << "===========================================\n";
 } catch( std::exception &e ) {
    std::cout<<"==>> Call failed due to: "<< e.what() << std::endl;
 }
#endif

#if 0
  // run instance
  opt.clear();
  opt["ImageId"]         = "ami-00857e69";
  opt["MinCount"]        = "1";
  opt["MaxCount"]        = "1";
  opt["SecurityGroup.1"] = "s4cloud";
  opt["InstanceType"]    = "m1.large";
  ret = RunInstances(opt);
  std::cout << ret << std::endl;
#endif

#if 0
  // terminate instance
  std::cout<<"Clear options\n";
  opt.clear();
  opt["InstanceId.1"] = "i-07552866";
  ret = sdk.TerminateInstances(opt);
  std::cout << ret << std::endl;
#endif

  return 0;
}
