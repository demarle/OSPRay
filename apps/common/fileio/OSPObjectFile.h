// ======================================================================== //
// Copyright 2009-2014 Intel Corporation                                    //
//                                                                          //
// Licensed under the Apache License, Version 2.0 (the "License");          //
// you may not use this file except in compliance with the License.         //
// You may obtain a copy of the License at                                  //
//                                                                          //
//     http://www.apache.org/licenses/LICENSE-2.0                           //
//                                                                          //
// Unless required by applicable law or agreed to in writing, software      //
// distributed under the License is distributed on an "AS IS" BASIS,        //
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. //
// See the License for the specific language governing permissions and      //
// limitations under the License.                                           //
// ======================================================================== //

#pragma once

#include "apps/common/fileio/TinyXML2.h"
#include "ospray/fileio/ObjectFile.h"

namespace ospray {

  //! \brief A concrete implementation of the CommonObjectFile class
  //!  for loading collections of OSPRay objects stored in XML format.
  //!
  //!  The loader creates and configures OSPRay object state according
  //!  to the XML specification.  Importantly this object state is not
  //!  committed, to allow an application to set additional parameters
  //!  through the returned ObjectCatalog type.
  //!
  class OSPObjectFile : public ObjectFile {
  public:

    //! Constructor.
    OSPObjectFile(const std::string &filename) : filename(filename) {}

    //! Destructor.
    virtual ~OSPObjectFile() {};

    //! Import a collection of objects.
    virtual OSPObjectCatalog importObjects();

    //! A string description of this class.
    virtual std::string toString() const { return("ospray::OSPObjectFile"); }

  private:

    //! Path to the file containing the object state.
    std::string filename;

    //! Import a scalar float.
    void importAttributeFloat(const tinyxml2::XMLNode *node, OSPObject parent);

    //! Import a 2-vector float.
    void importAttributeFloat2(const tinyxml2::XMLNode *node, OSPObject parent);

    //! Import a 3-vector float.
    void importAttributeFloat3(const tinyxml2::XMLNode *node, OSPObject parent);

    //! Import a signed scalar integer.
    void importAttributeInteger(const tinyxml2::XMLNode *node, OSPObject parent);

    //! Import a signed 3-vector integer.
    void importAttributeInteger3(const tinyxml2::XMLNode *node, OSPObject parent);

    //! Import a string.
    void importAttributeString(const tinyxml2::XMLNode *node, OSPObject parent);

    //! Import a light object.
    OSPObjectCatalog importLight(const tinyxml2::XMLNode *root);

    //! Import a light object attribute.
    void importLightAttribute(const tinyxml2::XMLNode *node, OSPLight light);

    //! Import a OSPLoadDataMode flag.
    OSPLoadDataMode importLoadDataMode(const tinyxml2::XMLNode *node);

    //! Import an object.
    OSPObjectCatalog importObject(const tinyxml2::XMLNode *node);

    //! To be implemented.
    inline OSPObjectCatalog importTriangleMesh(const tinyxml2::XMLNode *root) { return(NULL); }

    //! Import a volume object.
    OSPObjectCatalog importVolume(const tinyxml2::XMLNode *root);

    //! Import a volume object attribute.
    void importVolumeAttribute(const tinyxml2::XMLNode *node, OSPVolume volume);

    //! Optionally import the contents of a volume file based on an OSPLoadDataMode flag.
    void importVolumeFile(const tinyxml2::XMLNode *node, OSPVolume volume);

  };

} // ::ospray

