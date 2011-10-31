/*
 * @file   parsertest.cpp
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


#include <tests/parsertest.hpp>
#include <tests/testconfig.hpp>

#include <boost/throw_exception.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/regex.hpp>

#include <ec2-api/EC2Exception.hpp>
#include <ec2-api/parse/parse.hpp>

using namespace ec2::tests;

CPPUNIT_TEST_SUITE_REGISTRATION( ec2::tests::ParserTest );

ParserTest::ParserTest() {
}

ParserTest::~ParserTest() {
}

void ParserTest::setUp() {
}

void ParserTest::tearDown() {
}

const std::string ParserTest::_convert(const std::string &in) {
  std::string out;
  out = boost::regex_replace(boost::regex_replace(in, boost::regex("\n"), ""),
                             boost::regex(" [ ]+"), "");
  return out;
}

const std::string ParserTest::_loadFile(
  const fs::path &file
  )
{

  fs::ifstream ifs;
  ifs.open(fs::path(DATADIR) / file);
  std::string p;
  std::stringstream iss;

  while( std::getline( ifs, p ) ) {
    iss << p << std::endl;
  }
  ifs.close();

  return iss.str();
}

void ParserTest::AuthorizeSecurityGroupIngressTest() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  const std::string expected_response("AuthorizeSecurityGroupIngressResponse");
  
  std::stringstream iss;
  iss << _loadFile(expected_response+".1.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
  
}

void ParserTest::CreateSecurityGroupResponseTest() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("CreateSecurityGroupResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".1.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::DescribeImagesResponseTest() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("DescribeImagesResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".1.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::DescribeInstancesResponse1Test() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("DescribeInstancesResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".1.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::DescribeInstancesResponse2Test() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("DescribeInstancesResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".2.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::DescribeInstancesResponse3Test() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("DescribeInstancesResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".3.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::DescribeInstancesResponse4Test() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("DescribeInstancesResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".4.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::DescribeSecurityGroupsResponseTest() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("DescribeSecurityGroupsResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".1.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::RunInstancesResponse1Test() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("RunInstancesResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".1.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::RunInstancesResponse2Test() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("RunInstancesResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".2.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::TerminateInstancesResponseTest() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("TerminateInstancesResponse");

  std::stringstream iss;
  iss << _loadFile(expected_response+".1.xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::ResponseAuthFailureTest() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("Response.AuthFailure");
  
  std::stringstream iss;
  iss << _loadFile(expected_response+".xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::ResponseInvalidGroupDuplicateTest() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("Response.InvalidGroup.Duplicate");

  std::stringstream iss;
  iss << _loadFile(expected_response+".xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::ResponseInvalidGroupNotFoundTest() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("Response.InvalidGroup.NotFound");

  std::stringstream iss;
  iss << _loadFile(expected_response+".xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

void ParserTest::ResponseUnknownParameterTest() {
  ec2::xml::parse::type::EC2Response_t ret;
  ec2::xml::parse::state::type state;
  std::string expected_response("Response.UnknownParameter");

  std::stringstream iss;
  iss << _loadFile(expected_response+".xml");
  CPPUNIT_ASSERT_NO_THROW(ret = ec2::xml::parse::parse_EC2Response (iss, state, expected_response));
  CPPUNIT_ASSERT(strcmp(_convert(iss.str()).c_str(), _convert(ret.toString()).c_str()));
}

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
