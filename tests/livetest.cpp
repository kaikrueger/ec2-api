/*
 * @file   livetest.cpp
 *  @date   2011-09-28
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


#include <tests/livetest.hpp>
#include <tests/testconfig.hpp>

#include <ec2-api/ec2.hpp>
#include <ec2-api/SimpleRequestObserver.hpp>

#include <botan/exceptn.h>

using namespace ec2::tests;

CPPUNIT_TEST_SUITE_REGISTRATION( ec2::tests::LiveTest );

LiveTest::LiveTest() {
}

LiveTest::~LiveTest() {
}

void LiveTest::AuthNoKey() {
  
  ec2::Map_Type opt;
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::RequestObserver::Ptr Observer(ec2::RequestObserver::Ptr(new ec2::SimpleRequestObserver()));
  ec2::CFRuntime sdk(Observer, "", "", "");
  //sdk.setDebug();

  CPPUNIT_ASSERT_THROW(ret =  sdk.DescribeImages(opt), Botan::Invalid_Key_Length);
}

void LiveTest::AuthBadAccessKey() {
  
  ec2::Map_Type opt;
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::RequestObserver::Ptr Observer(ec2::RequestObserver::Ptr(new ec2::SimpleRequestObserver()));
  ec2::CFRuntime sdk(Observer, "", std::string(EC2_SECRET_KEY), "");
  //sdk.setDebug();

  CPPUNIT_ASSERT_NO_THROW(ret =  sdk.DescribeImages(opt));
  CPPUNIT_ASSERT_EQUAL(true, ret.IsErrorResponse());
  //std::cout << "AuthBadAccessKey" << ret;

  ec2::xml::parse::type::Response_t resp;
  CPPUNIT_ASSERT_NO_THROW(resp = ret.Response());
  CPPUNIT_ASSERT_EQUAL(resp.error().code(), std::string("AuthFailure"));
  
}

void LiveTest::AuthBadSignature() {
  
  ec2::Map_Type opt;
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::RequestObserver::Ptr Observer(ec2::RequestObserver::Ptr(new ec2::SimpleRequestObserver()));
  ec2::CFRuntime sdk(Observer, std::string(EC2_ACCESS_KEY), "blah", "");
  //sdk.setDebug();

  CPPUNIT_ASSERT_NO_THROW(ret =  sdk.DescribeImages(opt));
  CPPUNIT_ASSERT_EQUAL(true, ret.IsErrorResponse());
  //std::cout << "AuthBadSignature" << ret;

  ec2::xml::parse::type::Response_t resp;
  CPPUNIT_ASSERT_NO_THROW(resp = ret.Response());
  CPPUNIT_ASSERT_EQUAL(resp.error().code(), std::string("SignatureDoesNotMatch"));
  
}

void LiveTest::DescribeImagesAll() {
  ec2::Map_Type opt;
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::RequestObserver::Ptr Observer(ec2::RequestObserver::Ptr(new ec2::SimpleRequestObserver()));
  ec2::CFRuntime sdk(Observer, std::string(EC2_ACCESS_KEY), std::string(EC2_SECRET_KEY), "");
  //sdk.setDebug();

  //opt["ImageId.1"]="ami-00000000";
  CPPUNIT_ASSERT_NO_THROW(ret =  sdk.DescribeImages(opt));
  CPPUNIT_ASSERT_EQUAL(false, ret.IsErrorResponse());

  ec2::xml::parse::type::Response_t resp;
  CPPUNIT_ASSERT_THROW(resp = ret.Response(), boost::bad_get);

//std::cout << ret;
}

void LiveTest::DescribeInstances() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::RequestObserver::Ptr Observer(ec2::RequestObserver::Ptr(new ec2::SimpleRequestObserver()));
  ec2::CFRuntime sdk(Observer, std::string(EC2_ACCESS_KEY), std::string(EC2_SECRET_KEY), "");
  //sdk.setDebug();

  CPPUNIT_ASSERT_NO_THROW(ret = sdk.DescribeInstances());
  ec2::xml::parse::type::DescribeInstancesResponse_t resp;
  CPPUNIT_ASSERT_NO_THROW(resp = ret.DescribeInstancesResponse());
  CPPUNIT_ASSERT_EQUAL(0, (int)resp.instances());
  //std::cout <<"DescribeInstances: " << ret;
}

void LiveTest::TerminateInstancesNotExisting() {
  ec2::Map_Type opt;
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::RequestObserver::Ptr Observer(ec2::RequestObserver::Ptr(new ec2::SimpleRequestObserver()));
  ec2::CFRuntime sdk(Observer, std::string(EC2_ACCESS_KEY), std::string(EC2_SECRET_KEY), "");
  opt["InstanceId.1"] = "i-00000000";
  CPPUNIT_ASSERT_NO_THROW(ret = sdk.TerminateInstances(opt));
  CPPUNIT_ASSERT_EQUAL(true, ret.IsErrorResponse());
  //std::cout << ret << std::endl;
}
