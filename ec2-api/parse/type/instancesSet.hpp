/*
 * @file   instancesSet.hpp
 * @date   2011-08-11
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

#ifndef _instancesSet_hpp_
#define _instancesSet_hpp_
#include <vector>

#include <ec2-api/parse/types.hpp>

#include <ec2-api/parse/type/instancesState.hpp>
#include <ec2-api/parse/type/placement.hpp>
#include <ec2-api/parse/type/monitoring.hpp>
#include <ec2-api/parse/type/groupSet.hpp>
#include <ec2-api/parse/type/stateReason.hpp>

namespace ec2 {
  namespace xml {
  namespace parse {
    namespace type {

      struct instancesSet_t {
      public:
        typedef std::vector<instancesSet_t>::iterator        Iterator;
        typedef std::vector<instancesSet_t>::const_iterator  ConstIterator;

        private:
        std::string _instanceId; 
        std::string _imageId; 
        instancesState_t _instanceState; 
        instancesState_t _currentState; 
        instancesState_t _previousState; 
        std::string _privateDnsName; 
        std::string _dnsName; 
        std::string _reason; 
        int         _amiLaunchIndex; 
        std::string _productCodes; 
        std::string _instanceType; 
        std::string _launchTime; 
        placement_t _placement; 
        std::string _kernelId; 
        std::string _ramdiskId; 
        monitoring_t _monitoring; 
        std::string _privateIpAddress; 
        std::string _ipAddress; 
        std::vector<groupSet_t>  _groupSet; 
        stateReason_t _stateReason; 
        std::string _architecture; 
        std::string _rootDeviceType; 
        std::string _blockDeviceMapping; 
        std::string _virtualizationType; 
        std::string _clientToken; 
        std::string _hypervisor; 
        
      public:
        instancesSet_t (){}
        const std::string&     instanceId() const { return _instanceId; }
        const std::string&     imageId() const { return _imageId; }
        const instancesState_t& instanceState() const { return _instanceState; }
        const instancesState_t& currentState() const { return _currentState; }
        const instancesState_t& previousState() const { return _previousState; }
        const std::string&     privateDnsName() const { return _privateDnsName; }
        const std::string&     dnsName() const { return _dnsName; }
        const std::string&     reason() const { return _reason; }
        const int &amiLaunchIndex() const { return _amiLaunchIndex; }
        const std::string& productCodes() const { return _productCodes; }
        const std::string& instanceType() const { return _instanceType; }
        const std::string& launchTime() const { return _launchTime; }
        const placement_t& placement() const { return _placement; }
        const std::string &kernelId() const { return _kernelId; }
        const std::string &ramdiskId() const { return _ramdiskId; }
        const monitoring_t &monitoring() const { return _monitoring; }
        const std::string &privateIpAddress() const { return _privateIpAddress; }
        const std::string &ipAddress() const { return _ipAddress; }
        const std::vector<groupSet_t> &groupSet() const { return _groupSet; }
        const stateReason_t &stateReason() const { return _stateReason; }
        const std::string &architecture() const { return _architecture; }
        const std::string &rootDeviceType() const { return _rootDeviceType; }
        const std::string &blockDeviceMapping() const { return _blockDeviceMapping; }
        const std::string &virtualizationType() const { return _virtualizationType; }
        const std::string &clientToken() const { return _clientToken; }
        const std::string &hypervisor() const { return _hypervisor; }

        void instanceId(const std::string&v) { _instanceId = v; }
        void imageId(const std::string&v) { _imageId = v; }
        void instanceState(const instancesState_t& v) { _instanceState = v; }
        void currentState(const instancesState_t&v) { _currentState = v; }
        void previousState(const instancesState_t&v) { _previousState = v; }
        void privateDnsName(const std::string&v) { _privateDnsName = v; }
        void dnsName(const std::string&v) { _dnsName = v; }
        void reason(const std::string&v) { _reason = v; }
        void amiLaunchIndex(const int &v) { _amiLaunchIndex = v; }
        void productCodes(const std::string&v) { _productCodes = v; }
        void instanceType(const std::string&v) { _instanceType = v; }
        void launchTime(const std::string&v) { _launchTime = v; }
        void placement(const placement_t&v) { _placement = v; }
        void kernelId(const std::string&v) { _kernelId = v; }
        void ramdiskId(const std::string &v) { _ramdiskId = v; }
        void monitoring(const monitoring_t&v) { _monitoring = v; }
        void privateIpAddress(const std::string &v) { _privateIpAddress = v; }
        void ipAddress(const std::string &v) { _ipAddress = v; }
        void groupSet(const groupSet_t &v) { _groupSet.push_back(v); }
        void stateReason(const stateReason_t &v) { _stateReason = v; }
        void architecture(const std::string &v) { _architecture = v; }
        void rootDeviceType(const std::string &v) { _rootDeviceType = v; }
        void blockDeviceMapping(const std::string &v) { _blockDeviceMapping = v; }
        void virtualizationType(const std::string &v) { _virtualizationType = v; }
        void clientToken(const std::string &v) { _clientToken = v; }
        void hypervisor(const std::string &v) { _hypervisor = v; }
        
        const std::string toString() const {
          std::ostringstream oss;
          oss << "    <instanceId>" << instanceId() << "  </instanceId>\n"
              << "    <imageId>" << imageId() << "  </imageId>\n"
              << "    <instanceState>\n" << instanceState() << "    </instanceState>\n"
              << "    <currentState>\n" << currentState() << "    </currentState>\n"
              << "    <previousState>\n" << previousState() << "    </previousState>\n"
              << "    <privateDnsName>" << privateDnsName() << "  </privateDnsName>\n"
              << "    <dnsName>" << dnsName() << "  </dnsName>\n"
              << "    <reason>" << reason() << "  </reason>\n"
              << "    <amiLaunchIndex>" << amiLaunchIndex() << "  </amiLaunchIndex>\n"
              << "    <productCodes>" << productCodes() << "  </productCodes>\n"
              << "    <instanceType>" << instanceType() << "  </instanceType>\n"
              << "    <launchTime>" << launchTime() << "  </launchTime>\n"
              << placement()
              << "    <kernelId>" << kernelId() << "  </kernelId>\n"
              << "    <ramdiskId>" << ramdiskId() << "  </ramdiskId>\n"
              << monitoring()
              << "    <privateIpAddress>" << privateIpAddress() << "  </privateIpAddress>\n"
              << "    <ipAddress>" << ipAddress() << "  </ipAddress>\n"
            //<< groupSet()
              << "    <stateReason>" << stateReason() << "  </stateReason>\n"
              << "    <architecture>" << architecture() << "  </architecture>\n"
              << "    <rootDeviceType>" << rootDeviceType() << "  </rootDeviceType>\n"
              << "    <blockDeviceMapping>" << blockDeviceMapping() << "  </blockDeviceMapping>\n"
              << "    <virtualizationType>" << virtualizationType() << "  </virtualizationType>\n"
              << "    <clientToken>" << clientToken() << "  </clientToken>\n"
              << "    <hypervisor>" << hypervisor() << "  </hypervisor>\n"
            //<< "    <>" << () << "  </>\n"
            // << "    <>" << () << "  </>\n"
            //<< "    <>" << () << "  </>\n"
            ;
          return oss.str();
          }
        };

        // ******************************************************************* //
        inline
        std::ostream & operator << (std::ostream &s, const instancesSet_t &l) {
          s<< l.toString();
          return s;
        }


      } // namespace type
  } // namespace parse
  } // namespace xml
} // namespace ec2


/*---------------------------------------------------------------------*/
/**
 *      M A I N
 *
 **/
/*---------------------------------------------------------------------*/

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 *  project-name: ec2-api
 * End:
 */
#endif /* _instancesSet_hpp_ */
