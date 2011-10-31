/*
 * @file   imagesSet.hpp
 * @date   2011-09-27
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

#ifndef _imagesSet_hpp_
#define _imagesSet_hpp_
#include <vector>

#include <ec2-api/parse/type/stateReason.hpp>

namespace ec2 {
  namespace xml {
    namespace parse {
      namespace type {

        struct imagesSet_t {
        public:
          typedef std::vector<imagesSet_t>::iterator        Iterator;
          typedef std::vector<imagesSet_t>::const_iterator  ConstIterator;

        private:
          std::string _imageId;
          std::string _imageLocation;
          std::string _imageState;
          std::string _imageOwnerId;
          bool        _isPublic;
          //productCodes_t _productCodes;
          std::string _architecture;
          std::string _imageType;
          std::string _platform;
          stateReason_t _stateReason;
          std::string _name;
          std::string _description;
          std::string _kernelId;
          std::string _imageOwnerAlias;
          std::string _ramdiskId;
          std::string _rootDeviceType;
          std::string _rootDeviceName;
          std::string _blockDeviceMapping;
          std::string _virtualizationType;
          std::string _hypervisor;
          

        public:
          imagesSet_t (){}
          const std::string& imageId() const { return _imageId; }
          const std::string& imageLocation() const { return _imageLocation; }
          const std::string& imageState() const { return _imageState; }
          const std::string& imageOwnerId() const { return _imageOwnerId; }
          const bool        isPublic() const { return _isPublic; }
          const std::string& architecture() const { return _architecture; }
          const std::string& imageType() const { return _imageType; }
          const std::string& platform() const { return _platform; }
          const stateReason_t& stateReason() const { return _stateReason; }
          const std::string& name() const { return _name; }
          const std::string& description() const { return _description; }
          const std::string& kernelId() const { return _kernelId; }
          const std::string& imageOwnerAlias() const { return _imageOwnerAlias; }
          const std::string& ramdiskId() const { return _ramdiskId; }
          const std::string& rootDeviceType() const { return _rootDeviceType; }
          const std::string& rootDeviceName() const { return _rootDeviceName; }
          const std::string& blockDeviceMapping() const { return _blockDeviceMapping; }
          const std::string& virtualizationType() const { return _virtualizationType; }
          const std::string& hypervisor() const { return _hypervisor; }

          void imageId(const std::string& v) { _imageId = v; }
          void imageLocation(const std::string& v) { _imageLocation = v; }
          void imageState(const std::string& v) { _imageState = v; }
          void imageOwnerId(const std::string& v) { _imageOwnerId = v; }
          void isPublic(const bool& v)        { _isPublic = v; }
          void architecture(const std::string& v) { _architecture = v; }
          void imageType(const std::string& v) { _imageType = v; }
          void platform(const std::string& v) { _platform = v; }
          void stateReason(const stateReason_t& v) { _stateReason = v; }
          void name(const std::string& v) { _name = v; }
          void description(const std::string& v) { _description = v; }
          void kernelId(const std::string& v) { _kernelId = v; }
          void imageOwnerAlias(const std::string& v) { _imageOwnerAlias = v; }
          void ramdiskId(const std::string& v) { _ramdiskId = v; }
          void rootDeviceType(const std::string& v) { _rootDeviceType = v; }
          void rootDeviceName(const std::string& v) { _rootDeviceName = v; }
          void blockDeviceMapping(const std::string& v) { _blockDeviceMapping = v; }
          void virtualizationType(const std::string& v) { _virtualizationType = v; }
          void hypervisor(const std::string& v) { _hypervisor = v; }

        const std::string toString() const {
          std::ostringstream oss;
          oss
            << "    <imageId>" << imageId()  << "</imageId>" << std::endl
            << "    <imageLocation>" << imageLocation()  << "</imageLocation>" << std::endl
            << "    <imageState>" << imageState()  << "</imageState>" << std::endl
            << "    <imageOwnerId>" << imageOwnerId()  << "</imageOwnerId>" << std::endl
            << "    <isPublic>" << isPublic()  << "</isPublic>" << std::endl
            << "    <architecture>" << architecture()  << "</architecture>" << std::endl
            << "    <imageType>" << imageType()  << "</imageType>" << std::endl
            ;
          if(platform().size())
            oss << "    <platform>" << platform()  << "</platform>" << std::endl;
          if(stateReason().isSet())
            oss << "    <stateReason>"<< std::endl <<"    "<<stateReason() << "</stateReason>"<< std::endl;
          if(name().size())
            oss << "    <name>" << name()  << "</name>" << std::endl;
          if(description().size())
            oss << "    <description>" << description()  << "</description>" << std::endl;
          if(kernelId().size())
            oss << "    <kernelId>" << kernelId()  << "</kernelId>" << std::endl;
          if(imageOwnerAlias().size())
            oss << "    <imageOwnerAlias>" << imageOwnerAlias()  << "</imageOwnerAlias>" << std::endl;
          if( ramdiskId().size())
            oss<< "    <ramdiskId>" << ramdiskId()  << "</ramdiskId>" << std::endl;
          if( rootDeviceType().size())
            oss<< "    <rootDeviceType>" << rootDeviceType()  << "</rootDeviceType>" << std::endl;
          
          if( rootDeviceName().size())
            oss<< "    <rootDeviceName>" << rootDeviceName()  << "</rootDeviceName>" << std::endl;
          if( rootDeviceName().size())
            oss << "    <blockDeviceMapping>" << blockDeviceMapping() << "</blockDeviceMapping>" << std::endl;
          else oss << "    <blockDeviceMapping/>" << std::endl;
            oss
            << "    <virtualizationType>" << virtualizationType() << "</virtualizationType>" << std::endl
            << "    <hypervisor>" << hypervisor()  << "</hypervisor>" << std::endl
            ;
          return oss.str();
          }
        };

        // ******************************************************************* //
        inline
        std::ostream & operator << (std::ostream &s, const imagesSet_t &l) {
          s<< l.toString();
          return s;
        }


      } // namespace type
  } // namespace parse
  } // namespace xml
} // namespace ec2

/*
 * Local variables:
 *  tab-width: 2
 *  c-indent-level: 2
 *  c-basic-offset: 2
 * End:
 */
#endif /* _imagesSet_hpp_ */
