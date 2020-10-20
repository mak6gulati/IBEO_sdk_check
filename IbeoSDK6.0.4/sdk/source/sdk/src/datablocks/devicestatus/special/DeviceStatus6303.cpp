//==============================================================================
//!\file
//!
//!$$IBEO_LICENSE_BEGIN$$
//!Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//!All Rights Reserved.
//!
//!For more details, please refer to the accompanying file
//!IbeoLicense.txt.
//!$$IBEO_LICENSE_END$$
//!
//!\date Jan 22, 2018
//------------------------------------------------------------------------------

//==============================================================================

#include <ibeo/common/sdk/datablocks/devicestatus/special/DeviceStatus6303.hpp>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

DeviceStatus6303::UserDefinedStructBase::UserDefinedStructBase(const ContentId contentId) : m_contentId(contentId) {}

//==============================================================================

DeviceStatus6303::UserDefinedStructBase::~UserDefinedStructBase() {}

//==============================================================================

bool DeviceStatus6303::addContent(const ContentDescr& cd)
{
    return addContent(cd.getContentId(),
                      cd.getElementType(),
                      cd.getNbOfBytes(),
                      cd.getNeededBufferAlignment(),
                      cd.getContentBuffer());
}

//==============================================================================

bool DeviceStatus6303::addContent(const ContentId cId,
                                  const ElementType et,
                                  const uint8_t nbOfBytes,
                                  const uint32_t alignment,
                                  const void* cData)
{
    if (m_contentEntries.size() == maxNbOfContentEntries)
    {
        return false;
    }

    if (findContent(cId) >= 0)
    {
        // no duplicate content types are allowed
        return false;
    }

    if (nbOfBytes <= 0)
    {
        return false;
    }

    char* targetBuffer     = m_contentData + m_usedBytesInContentData;
    const uint32_t padding = uint32_t((alignment - (uint64_t(targetBuffer) % alignment)) % alignment);

    if (m_usedBytesInContentData + nbOfBytes + padding >= contentBufferSize)
    {
        return false;
    }

    targetBuffer += padding;
    m_usedBytesInContentData += nbOfBytes + padding;

    //#ifdef DEBUG_DEVICESTATUS
    //	std::cout << "Adding Content: " << cId << "  et: " << et << " #Bytes: " << std::setw(3) << int(nbOfBytes)
    //			<< "  BufPosition: " << std::setw(4) << int64_t(targetBuffer)-int64_t(m_contentData)
    //			<< "  Alignment: " << alignment << " ==> Padding: " << padding << std::endl;
    //#endif //  DEBUG_DEVICESTATUS

    ContentDescr contentDescr(cId, et, nbOfBytes);
    contentDescr.setContentBuffer(targetBuffer);
    //	std::cerr << "     " << __func__ << "  " << cData << " --> " << (void*)targetBuffer << std::endl;
    memcpy(targetBuffer, cData, nbOfBytes);
    m_contentEntries.push_back(contentDescr);
    return true;
}

//==============================================================================

bool DeviceStatus6303::addContent(const UserDefinedStructBase& uds)
{
    if (m_contentEntries.size() == maxNbOfContentEntries)
        return false;

    if (findContent(uds.getContentId()) >= 0)
    {
        // no duplicate content types are allowed
        return false;
    }

    const uint8_t nbOfBytes = uds.getSerializedSize();
    if (nbOfBytes <= 0)
        return false;

    //	std::cerr << "   m_usedBytesInContentData: " << m_usedBytesInContentData
    //			<< "   nbOfBytes: " << int(nbOfBytes)
    //			<< "   m_usedBytesInContentData+nbOfBytes: " << (m_usedBytesInContentData+nbOfBytes)
    //			<< "   contentBufferSize: " << contentBufferSize
    //			<< "      " << (m_usedBytesInContentData+nbOfBytes >= contentBufferSize)
    //			<< std::endl;

    char* targetBuffer = m_contentData + m_usedBytesInContentData;
    if (m_usedBytesInContentData + nbOfBytes >= contentBufferSize)
        return false;

    m_usedBytesInContentData += nbOfBytes;

    //#ifdef DEBUG_DEVICESTATUS
    //	std::cout.clear();
    //	std::cout << "Adding Content: " << uds.getContentId() << "  et: " << ElementType::STRUCT << " #Bytes: " << std::setw(3) << int(nbOfBytes)
    //			<< "  BufPosition: " << std::setw(4)  << int64_t(targetBuffer)-int64_t(m_contentData)<< std::endl;
    //#endif //  DEBUG_DEVICESTATUS

    ContentDescr contentDescr(uds.getContentId(), ElementType::STRUCT, nbOfBytes);
    contentDescr.setContentBuffer(targetBuffer);
    uds.serialize(targetBuffer);
    m_contentEntries.push_back(contentDescr);
    return true;
}

//==============================================================================

int DeviceStatus6303::findContent(const ContentId cId)
{
    for (unsigned int i = 0; i < m_contentEntries.size(); ++i)
    {
        if (m_contentEntries.at(i).getContentId() == cId)
        {
            return int(i);
        }
    }

    return -1;
}

//==============================================================================

bool DeviceStatus6303::getContent(const ContentId cId, UserDefinedStructBase& uds)
{
    const int idx = findContent(cId);
    if (idx == -1)
    {
        return false;
    }

    const ContentDescr& c = m_contentEntries.at(uint32_t(idx));
    if (c.getElementType() != ElementType::STRUCT)
    {
        return false;
    }

    return uds.deserialize(c);
}

//==============================================================================

uint8_t DeviceStatus6303::getNbOfElements(const ElementType et, const uint8_t nbOfBytes)
{
    switch (et)
    {
    case ElementType::UINT8:
        return nbOfBytes;
    case ElementType::INT8:
        return nbOfBytes;
    case ElementType::UINT16:
        return nbOfBytes / uint8_t(sizeof(uint16_t));
    case ElementType::INT16:
        return nbOfBytes / uint8_t(sizeof(int16_t));
    case ElementType::UINT32:
        return nbOfBytes / uint8_t(sizeof(uint32_t));
    case ElementType::INT32:
        return nbOfBytes / uint8_t(sizeof(int32_t));
    case ElementType::FLOAT32:
        return nbOfBytes / uint8_t(sizeof(float));
    case ElementType::STRUCT:
        return 1;
    default:
        return 0;
    }
}

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

template<>
inline void writeBE(std::ostream& os, const DeviceStatus6303::ContentId& value)
{
    writeBE(os, uint16_t(value));
}

//==============================================================================

template<>
inline void writeBE(std::ostream& os, const DeviceStatus6303::ElementType& value)
{
    writeBE(os, uint8_t(value));
}

//==============================================================================

std::streamsize DeviceStatus6303::ContentDescr::getSerializedSize() const
{
    return 2 * std::streamsize(sizeof(uint8_t)) + std::streamsize(sizeof(uint16_t)) + m_nbOfBytes;
}

//==============================================================================

bool DeviceStatus6303::ContentDescr::serialize(std::ostream& os) const
{
    const int64_t startPos = streamposToInt64(os.tellp());

#ifdef DEBUG_DEVICESTATUS
    cout.clear();
    cout << "  Write: " << m_contentId << " " << m_elementType;
#endif // DEBUG_DEVICESTATUS

    writeBE(os, m_contentId);
    writeBE(os, m_elementType);
    writeBE(os, m_nbOfBytes);

    switch (m_elementType)
    {
    case ElementType::UINT8:
        writeVcElements(os, m_nbOfBytes, reinterpret_cast<const uint8_t*>(m_contentBuffer));
        break;
    case ElementType::INT8:
        writeVcElements(os, m_nbOfBytes, reinterpret_cast<const int8_t*>(m_contentBuffer));
        break;
    case ElementType::UINT16:
        writeVcElements(os, m_nbOfBytes, reinterpret_cast<const uint16_t*>(m_contentBuffer));
        break;
    case ElementType::INT16:
        writeVcElements(os, m_nbOfBytes, reinterpret_cast<const int16_t*>(m_contentBuffer));
        break;
    case ElementType::UINT32:
        writeVcElements(os, m_nbOfBytes, reinterpret_cast<const uint32_t*>(m_contentBuffer));
        break;
    case ElementType::INT32:
        writeVcElements(os, m_nbOfBytes, reinterpret_cast<const int32_t*>(m_contentBuffer));
        break;
    case ElementType::FLOAT32:
        writeVcElements(os, m_nbOfBytes, reinterpret_cast<const float*>(m_contentBuffer));
        break;
    case ElementType::STRUCT:
        // structs are already serialized inside the buffer.
        writeVcElements(os, m_nbOfBytes, reinterpret_cast<const char*>(m_contentBuffer));
        break;
    default:
        break; // ignore;
    } // witch element type

    return !os.fail() && ((streamposToInt64(os.tellp()) - startPos) == getSerializedSize());
}

//==============================================================================

template<typename T>
void DeviceStatus6303::ContentDescr::writeVcElements(std::ostream& os,
                                                     const uint32_t nbOfBytes,
                                                     const T* const elements)
{
    const uint32_t nbOfElements = uint32_t(nbOfBytes / sizeof(T));
#ifdef DEBUG_DEVICESTATUS
    cout << " #e:" << setw(3) << nbOfElements << " Content:  ";
#endif // DEBUG_DEVICESTATUS

    for (uint32_t i = 0; i < nbOfElements; ++i)
    {
        writeBE(os, elements[i]);
    }
#ifdef DEBUG_DEVICESTATUS
    cout << getHex(elements[0]) << "...";
    cout << getHex(elements[nbOfElements - 1]);
    cout << endl;
#endif // DEBUG_DEVICESTATUS
}

//==============================================================================

uint8_t DeviceStatus6303::ContentDescr::getNeededBufferAlignment() const
{
    switch (m_elementType)
    {
    case ElementType::UINT16:
    case ElementType::INT16:
        return 2;
    case ElementType::UINT32:
    case ElementType::INT32:
    case ElementType::FLOAT32:
        return 4;
    case ElementType::Illegal:
    case ElementType::UINT8:
    case ElementType::INT8:
    case ElementType::STRUCT:
    default:
        return 1;
    }
}

//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

//static
char DeviceStatus6303::ContentDescrDeserializer::deserializeBuffer[maxSizeOfContent + 1];

//==============================================================================

bool DeviceStatus6303::ContentDescrDeserializer::deserialize(std::istream& is)
{
    const int64_t startPos = streamposToInt64(is.tellg());

    m_contentId   = this->readContentId(is);
    m_elementType = this->readElementType(is);
    readBE(is, m_nbOfBytes);

    const uint8_t nbOfElements = getNbOfElements(m_elementType, m_nbOfBytes);
#ifdef DEBUG_DEVICESTATUS
    cout.clear();
    cout << "  Read: " << this->m_contentId << " #e:" << setw(3) << nbOfElements << " Content:  ";
#endif // DEBUG_DEVICESTATUS

    switch (m_elementType)
    {
    case ElementType::UINT8:
        readVcElements(is, nbOfElements, reinterpret_cast<uint8_t*>(m_contentBuffer));
        break;
    case ElementType::INT8:
        readVcElements(is, nbOfElements, reinterpret_cast<int8_t*>(m_contentBuffer));
        break;
    case ElementType::UINT16:
        readVcElements(is, nbOfElements, reinterpret_cast<uint16_t*>(m_contentBuffer));
        break;
    case ElementType::INT16:
        readVcElements(is, nbOfElements, reinterpret_cast<int16_t*>(m_contentBuffer));
        break;
    case ElementType::UINT32:
        readVcElements(is, nbOfElements, reinterpret_cast<uint32_t*>(m_contentBuffer));
        break;
    case ElementType::INT32:
        readVcElements(is, nbOfElements, reinterpret_cast<int32_t*>(m_contentBuffer));
        break;
    case ElementType::FLOAT32:
        readVcElements(is, nbOfElements, reinterpret_cast<float*>(m_contentBuffer));
        break;
    case ElementType::STRUCT:
        // structs are stored serialized inside the buffer.
        // so no need to change the byte order.
        readVcElements(is, m_nbOfBytes, reinterpret_cast<uint8_t*>(m_contentBuffer)); // nbOfElements==1
        break;
    default:
        is.ignore(this->m_nbOfBytes);
        this->m_nbOfBytes = 0;
        break; // ignore;
    } // switch element type

    return !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == getSerializedSize());
}

//==============================================================================

template<typename T>
void DeviceStatus6303::ContentDescrDeserializer ::readVcElements(std::istream& is,
                                                                 const int nbOfElementsToRead,
                                                                 T* const elements)
{
    for (int i = 0; i < nbOfElementsToRead; ++i)
    {
        readBE(is, elements[i]);
    }
#ifdef DEBUG_DEVICESTATUS
    cout << getHex(elements[0]) << "...";
    cout << getHex(elements[nbOfElementsToRead - 1]);
    cout << endl;
#endif //  DEBUG_DEVICESTATUS
}

//==============================================================================

DeviceStatus6303::ContentId DeviceStatus6303::ContentDescrDeserializer::readContentId(std::istream& is)
{
    uint16_t tmp;
    readBE(is, tmp);
    return ContentId(tmp);
}

//==============================================================================

DeviceStatus6303::ElementType DeviceStatus6303::ContentDescrDeserializer::readElementType(std::istream& is)
{
    uint8_t tmp;
    readBE(is, tmp);
    return ElementType(tmp);
}
//==============================================================================

//==============================================================================
//==============================================================================
//==============================================================================

//==============================================================================

bool operator==(const DeviceStatus6303& lhs, const DeviceStatus6303& rhs)
{
    // Temperatures might have been converted between degrees Celsius and Kelvin. They are not float-equal but
    // fuzzy-float-equal up to 3 decimal digits.

    using C = DeviceStatus6303;
    if ((lhs.getSerialNumberOfScanner() != rhs.getSerialNumberOfScanner())
        || (lhs.getScannerType() != rhs.getScannerType()) || (lhs.getDeviceId() != rhs.getDeviceId())
        || (lhs.getFpgaVersion() != rhs.getFpgaVersion()) || (lhs.getHostVersion() != rhs.getHostVersion())
        || (lhs.getFpgaStatusRegister() != rhs.getFpgaStatusRegister())
        || (lhs.getFpgaOperationRegister() != rhs.getFpgaOperationRegister())
        || (lhs.getScanPeriod() != rhs.getScanPeriod())
        || (!fuzzyFloatEqualT<3>(lhs.getSensorTemperatureApd0(), rhs.getSensorTemperatureApd0()))
        || (!fuzzyFloatEqualT<3>(lhs.getSensorTemperatureApd1(), rhs.getSensorTemperatureApd1()))
        || (!floatEqual(lhs.getMinApdVoltageOffset(), rhs.getMinApdVoltageOffset()))
        || (!floatEqual(lhs.getMaxApdVoltageOffset(), rhs.getMaxApdVoltageOffset()))
        || (lhs.getNoiseMeasurementThreshold() != rhs.getNoiseMeasurementThreshold())
        || (lhs.getReferenceNoise() != rhs.getReferenceNoise()))
    {
        return false;
    }

    // contents can be in different order
    for (unsigned int i = 0; i < lhs.getContentDescrs().size(); ++i)
    {
        const C::ContentDescr& cr = lhs.getContentDescrs().at(i);
        bool foundCIdMatch        = false;
        for (unsigned int j = 0; j < rhs.getContentDescrs().size(); ++j)
        {
            const C::ContentDescr& cl = rhs.getContentDescrs().at(j);
            if (cr.getContentId() == cl.getContentId())
            {
                foundCIdMatch = true;
                if (cr.getElementType() != cl.getElementType() || cr.getNbOfBytes() != cl.getNbOfBytes())
                {
                    return false;
                }

                if (memcmp(cr.getContentBuffer(), cl.getContentBuffer(), cr.getNbOfBytes()))
                {
                    return false;
                }
                // perfect match
                break;
            } // if cr::cId = cl::cId
            if (foundCIdMatch)
                continue;
        } // for j
        if (!foundCIdMatch)
            return false;
    } // for i
    return true;
}

//==============================================================================

std::ostream& operator<<(std::ostream& os, const DeviceStatus6303::ContentId cId)
{
    switch (cId)
    {
    case DeviceStatus6303::ContentId::Illegal:
        os << "Illegal";
        break;
    case DeviceStatus6303::ContentId::ApdVoltageTable:
        os << "ApdVoltageTable";
        break;
    case DeviceStatus6303::ContentId::NoiseTable:
        os << "NoiseTable";
        break;
    case DeviceStatus6303::ContentId::ScalaARMVersion:
        os << "ScalaARMVersion";
        break;
    case DeviceStatus6303::ContentId::ErrorScalaFPGA:
        os << "ErrorScalaFPGA";
        break;
    case DeviceStatus6303::ContentId::YawOffsetConf:
        os << "YawOffsetConf";
        break;
    case DeviceStatus6303::ContentId::YawOffsetCalc:
        os << "YawOffsetCalc";
        break;
    case DeviceStatus6303::ContentId::VelFactorConf:
        os << "VelFactorConf";
        break;
    case DeviceStatus6303::ContentId::VelFactorCalc:
        os << "VelFactorCalc";
        break;
    case DeviceStatus6303::ContentId::Dummy1:
        os << "Dummy1";
        break;
    case DeviceStatus6303::ContentId::Dummy2:
        os << "Dummy2";
        break;
    case DeviceStatus6303::ContentId::Dummy3:
        os << "Dummy3";
        break;
    case DeviceStatus6303::ContentId::Dummy4:
        os << "Dummy4";
        break;
    default:
        os << "ContentId{" << int(cId) << "}";
        break;
    }
    return os;
}

//==============================================================================

std::ostream& operator<<(std::ostream& os, const DeviceStatus6303::ElementType et)
{
    switch (et)
    {
    case DeviceStatus6303::ElementType::Illegal:
        os << "Illegal";
        break;
    case DeviceStatus6303::ElementType::UINT8:
        os << "UINT8";
        break;
    case DeviceStatus6303::ElementType::INT8:
        os << "INT8";
        break;
    case DeviceStatus6303::ElementType::UINT16:
        os << "UINT16";
        break;
    case DeviceStatus6303::ElementType::INT16:
        os << "INT16";
        break;
    case DeviceStatus6303::ElementType::UINT32:
        os << "UINT32";
        break;
    case DeviceStatus6303::ElementType::INT32:
        os << "INT32";
        break;
    case DeviceStatus6303::ElementType::FLOAT32:
        os << "FLOAT32";
        break;
    case DeviceStatus6303::ElementType::STRUCT:
        os << "STRUCT";
        break;
    default:
        os << "{ElementType " << int(et) << "is unsupported}";
        break;
    }
    return os;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
