/*
 * @file   sample.cpp
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

#include <string>
#include <sstream>
#include <iostream>
#include <fstream>

#include <ec2-api/parse/parse.hpp>

const std::string RunInstancesResponse("<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<RunInstancesResponse xmlns=\"http://ec2.amazonaws.com/doc/2011-07-15/\">"
"    <requestId>4152f9f3-4f17-4de2-989a-5a12f659bf0a</requestId>"
"    <reservationId>r-2b71e744</reservationId>"
"    <ownerId>564113121057</ownerId>"
"    <groupSet>"
"        <item>"
"            <groupId>sg-5e97d437</groupId>"
"            <groupName>s4cloud</groupName>"
"        </item>"
"    </groupSet>"
"    <instancesSet>"
"        <item>"
"            <instanceId>i-07552866</instanceId>"
"            <imageId>ami-00857e69</imageId>"
"            <instanceState>"
"                <code>0</code>"
"                <name>pending</name>"
"            </instanceState>"
"            <privateDnsName/>"
"            <dnsName/>"
"            <reason/>"
"            <amiLaunchIndex>0</amiLaunchIndex>"
"            <productCodes/>"
"            <instanceType>m1.large</instanceType>"
"            <launchTime>2011-08-10T09:00:38.000Z</launchTime>"
"            <placement>"
"                <availabilityZone>us-east-1d</availabilityZone>"
"                <groupName/>"
"                <tenancy>default</tenancy>"
"            </placement>"
"            <kernelId>aki-fd15f694</kernelId>"
"            <ramdiskId>ari-7b739e12</ramdiskId>"
"            <monitoring>"
"                <state>disabled</state>"
"            </monitoring>"
"            <groupSet>"
"                <item>"
"                    <groupId>sg-5e97d437</groupId>"
"                    <groupName>s4cloud</groupName>"
"                </item>"
"            </groupSet>"
"            <stateReason>"
"                <code>pending</code>"
"                <message>pending</message>"
"            </stateReason>"
"            <rootDeviceType>instance-store</rootDeviceType>"
"            <blockDeviceMapping/>"
"            <clientToken/>"
"            <hypervisor>xen</hypervisor>"
"        </item>"
"    </instancesSet>"
"</RunInstancesResponse>"
);

const std::string DescribeInstancesResponse(
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
"<DescribeInstancesResponse xmlns=\"http://ec2.amazonaws.com/doc/2011-07-15/\">"
"    <requestId>68846c3a-251c-4085-883e-b1e3d5c331e1</requestId>"
"    <reservationSet>"
"        <item>"
"            <reservationId>r-9770e6f8</reservationId>"
"            <ownerId>564113121057</ownerId>"
"            <groupSet>"
"                <item>"
"                    <groupId>sg-5e97d437</groupId>"
"                    <groupName>s4cloud</groupName>"
"                </item>"
"            </groupSet>"
"            <instancesSet>"
"                <item>"
"                    <instanceId>i-a55a27c4</instanceId>"
"                    <imageId>ami-00857e69</imageId>"
"                    <instanceState>"
"                        <code>16</code>"
"                        <name>running</name>"
"                    </instanceState>"
"                    <privateDnsName>ip-10-101-30-90.ec2.internal</privateDnsName>"
"                    <dnsName>ec2-184-73-135-151.compute-1.amazonaws.com</dnsName>"
"                    <reason/>"
"                    <amiLaunchIndex>0</amiLaunchIndex>"
"                    <productCodes/>"
"                    <instanceType>m1.large</instanceType>"
"                    <launchTime>2011-08-10T09:00:18.000Z</launchTime>"
"                    <placement>"
"                        <availabilityZone>us-east-1a</availabilityZone>"
"                        <groupName/>"
"                        <tenancy>default</tenancy>"
"                    </placement>"
"                    <kernelId>aki-fd15f694</kernelId>"
"                    <ramdiskId>ari-7b739e12</ramdiskId>"
"                    <monitoring>"
"                        <state>disabled</state>"
"                    </monitoring>"
"                    <privateIpAddress>10.101.30.90</privateIpAddress>"
"                    <ipAddress>184.73.135.151</ipAddress>"
"                    <groupSet>"
"                        <item>"
"                            <groupId>sg-5e97d437</groupId>"
"                            <groupName>s4cloud</groupName>"
"                        </item>"
"                    </groupSet>"
"                    <architecture>x86_64</architecture>"
"                    <rootDeviceType>instance-store</rootDeviceType>"
"                    <blockDeviceMapping/>"
"                    <virtualizationType>paravirtual</virtualizationType>"
"                    <clientToken/>"
"                    <hypervisor>xen</hypervisor>"
"                </item>"
"            </instancesSet>"
"        </item>"
"        <item>"
"            <reservationId>r-2b71e744</reservationId>"
"            <ownerId>564113121057</ownerId>"
"            <groupSet>"
"                <item>"
"                    <groupId>sg-5e97d437</groupId>"
"                    <groupName>s4cloud</groupName>"
"                </item>"
"            </groupSet>"
"            <instancesSet>"
"                <item>"
"                    <instanceId>i-07552866</instanceId>"
"                    <imageId>ami-00857e69</imageId>"
"                    <instanceState>"
"                        <code>16</code>"
"                        <name>running</name>"
"                    </instanceState>"
"                    <privateDnsName>ip-10-46-86-218.ec2.internal</privateDnsName>"
"                    <dnsName>ec2-50-19-189-75.compute-1.amazonaws.com</dnsName>"
"                    <reason/>"
"                    <amiLaunchIndex>0</amiLaunchIndex>"
"                    <productCodes/>"
"                    <instanceType>m1.large</instanceType>"
"                    <launchTime>2011-08-10T09:00:38.000Z</launchTime>"
"                    <placement>"
"                        <availabilityZone>us-east-1d</availabilityZone>"
"                        <groupName/>"
"                        <tenancy>default</tenancy>"
"                    </placement>"
"                    <kernelId>aki-fd15f694</kernelId>"
"                    <ramdiskId>ari-7b739e12</ramdiskId>"
"                    <monitoring>"
"                        <state>disabled</state>"
"                    </monitoring>"
"                    <privateIpAddress>10.46.86.218</privateIpAddress>"
"                    <ipAddress>50.19.189.75</ipAddress>"
"                    <groupSet>"
"                        <item>"
"                            <groupId>sg-5e97d437</groupId>"
"                            <groupName>s4cloud</groupName>"
"                        </item>"
"                    </groupSet>"
"                    <architecture>x86_64</architecture>"
"                    <rootDeviceType>instance-store</rootDeviceType>"
"                    <blockDeviceMapping/>"
"                    <virtualizationType>paravirtual</virtualizationType>"
"                    <clientToken/>"
"                    <hypervisor>xen</hypervisor>"
"                </item>"
"            </instancesSet>"
"        </item>"
"    </reservationSet>"
"</DescribeInstancesResponse>"
);
using namespace ec2::xml;

int main(
  int argc,
  char *argv[]
  )
{
  std::stringstream iss;
  iss << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\" ?>" << std::endl;
  //iss << "<!DOCTYPE boost_serialization>" << std::endl;
  //iss << "<boost_serialization signature=\"serialization::archive\" version=\"5\">" << std::endl;
  //iss << "<TerminateInstancesResponse class_id=\"0\" tracking_level=\"0\" version=\"0\">" << std::endl;
  
  iss << "<TerminateInstancesResponse xmlns=\"http://ec2.amazonaws.com/doc/2011-07-15/\">" << std::endl;
  iss << "    <requestId>26489101-63eb-44ad-a800-6783070305fc</requestId>" << std::endl;
  iss << "    <instancesSet>" << std::endl;
iss << "        <item>" << std::endl;
iss << "            <instanceId>i-07552866</instanceId>" << std::endl;
iss << "            <currentState>" << std::endl;
iss << "                <code>32</code>" << std::endl;
iss << "                <name>shutting-down</name>" << std::endl;
iss << "            </currentState>" << std::endl;
iss << "            <previousState>" << std::endl;
iss << "                <code>16</code>" << std::endl;
iss << "                <name>running</name>" << std::endl;
iss << "            </previousState>" << std::endl;
iss << "        </item>" << std::endl;
iss << "    </instancesSet>" << std::endl;
iss << "</TerminateInstancesResponse>" << std::endl;
  
//TerminateInstances_t TerminateInstancesResponse;

std::cout << "'" << iss.str() << "'" << std::endl;
  //std::ifstream ifs("test1.xml");
  //boost::archive::xml_iarchive ia(ifs);


//  boost::archive::xml_iarchive ia(iss);
//ia >> BOOST_SERIALIZATION_NVP(TerminateInstancesResponse);

ec2::xml::parse::state::type state;
ec2::xml::parse::type::EC2Response_t p;

// iss << RunInstancesResponse;
//p = ec2::xml::parse_TerminateInstancesResponse (iss, state);
p = ec2::xml::parse::parse_EC2Response (iss, state);

std::cout<< "============== TerminateInstancesResponse ===\n";
std::cout<< p;
std::cout<< "\n==========================================\n";

iss.clear();
iss << DescribeInstancesResponse;
ec2::xml::parse::type::EC2Response_t p2;
p2 = ec2::xml::parse::parse_EC2Response (iss, state);
std::cout<< "============ DescribeInstancesResponse =====\n";
std::cout<< p2;
std::cout<< "\n==========================================\n";


iss.clear();
iss << RunInstancesResponse;
ec2::xml::parse::type::EC2Response_t p3;
p3 = ec2::xml::parse::parse_EC2Response (iss, state);
std::cout<< "============ RunInstancesResponse =====\n";
std::cout<< p3;
std::cout<< "\n==========================================\n";
  return 0;
}
