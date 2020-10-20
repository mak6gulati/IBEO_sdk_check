//==============================================================================
//! \file
//!
//! $$IBEO_LICENSE_BEGIN$$
//! Copyright (c) Ibeo Automotive Systems GmbH 2010-2019
//! All Rights Reserved.
//!
//! For more details, please refer to the accompanying file
//! IbeoLicense.txt.
//! $$IBEO_LICENSE_END$$
//!
//! \date Feb 11, 2018
//------------------------------------------------------------------------------

#include <ibeo/common/sdk/datablocks/commands/Command2010Importer2010.hpp>
#include <ibeo/common/sdk/ContainerBufferAndImporterProvider.hpp>

#include <boost/iostreams/stream.hpp>
#include <boost/iostreams/device/array.hpp>
#include <boost/range/algorithm.hpp>

#if defined(__GNUC__) || defined(__clang__)
#    pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif // gcc or clang
//==============================================================================
namespace {
//==============================================================================
using C  = ibeo::common::sdk::Command2010;
using R  = ibeo::common::sdk::RegisteredImporter<C, ibeo::common::sdk::DataTypeId::DataType_Command2010>;
using Id = ibeo::common::sdk::ImporterBase::ImporterRegisterId;
//==============================================================================
} // namespace
//==============================================================================

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================
// Specializations for RegisteredImporter
//==============================================================================

//generate link between data-type-id/importer and importer create function <dtid, ImpHash> ==> Imp::create

template<>
const Id R::registeredImporterInitial
    = Id(std::make_pair(R::getDataTypeStatic(), C::getClassIdHashStatic()), R::create);

//registering ... (create map)
//add all device that can receive any datatype that can be imported to GeneralDataTypeContainer
class IbeoEcu;
class IdcFile;
class IbeoLux;
class IbeoTrackingBox;
class IbeoScala;

//register listener types
template<>
const Id R::registeredImporter = ContainerBufferAndImporterProviderGlobal<IbeoEcu>::getInstance().registerImporter(
    ContainerBufferAndImporterProviderGlobal<IdcFile>::getInstance().registerImporter(
        ContainerBufferAndImporterProviderGlobal<IbeoLux>::getInstance().registerImporter(
            ContainerBufferAndImporterProviderGlobal<IbeoTrackingBox>::getInstance().registerImporter(
                ContainerBufferAndImporterProviderGlobal<IbeoScala>::getInstance().registerImporter(
                    registeredImporterInitial)))));

//==============================================================================

ibeo::common::logging::LoggerSPtr Importer<C, DataTypeId::DataType_Command2010>::logger{
    ibeo::common::logging::LogManager::getInstance().createLogger(loggerId)};

//==============================================================================

Importer<C, DataTypeId::DataType_Command2010>::Importer()
  : RegisteredImporter(), m_baip(BufferAndImporterProviderGlobal<CommandCBase>::getInstance())
{}

//==============================================================================

std::streamsize Importer<C, DataTypeId::DataType_Command2010>::getSerializedSize(const DataContainerBase& c) const
{
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    const auto& spm = container->getSpecialCommand();
    if (!spm.empty())
    {
        const CommandCBase* cb = container->getSpecialCommand().begin()->second;
        if (cb)
        {
            //		LOGINFO(logger, "Special type is known for " << container->m_commandId);

            auto key = std::make_pair(CommandId::Id(uint16_t(cb->getCommandId())), cb->getClassIdHash());

            SpecialImporterBase<CommandCBase>* si = m_baip.getImporter(key);
            if (si)
            {
                return si->getSerializedSize(*cb);
            }
            else
            {
                return 0;
            }
        }
    }

    //LOGINFO(logger, "Special type is unknown for " << container->m_commandId);
    return static_cast<std::streamsize>(container->m_rawContent.size());
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Command2010>::deserialize(std::istream& is,
                                                                DataContainerBase& c,
                                                                const IbeoDataHeader& dh) const
{
    C* container{nullptr};
    try
    {
        container = &dynamic_cast<C&>(c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    container->setDataHeader(dh);
    container->m_specialCommandMap.clear();

    const int64_t startPos = streamposToInt64(is.tellg());

    container->m_rawContent.resize(static_cast<uint32_t>(dh.getMessageSize()));
    char* const buffer{container->m_rawContent.data()};
    const uint32_t bufferSize{static_cast<uint32_t>(container->m_rawContent.size())};
    is.read(buffer, bufferSize);
    //	LOGTRACE(logger, "  msgSize:" << dh.getMessageSize() << "  bufferSize: " << bufferSize);

    //	LOGINFO(logger, "Serialized size. " << this->getSerializedSize(c)
    //			<< (container->m_specialCommand ? "(ST)" : "(Raw)")
    //			<< "  Expected: " << dh.getMessageSize());

    const bool ok = deserializeSpecial(container, dh);

    return ok && !is.fail() && ((streamposToInt64(is.tellg()) - startPos) == this->getSerializedSize(c))
           && this->getSerializedSize(c) == dh.getMessageSize();
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Command2010>::deserializeSpecial(C* container, const IbeoDataHeader& dh) const
{
    char* const buffer{container->m_rawContent.data()};
    const uint32_t bufferSize{static_cast<uint32_t>(container->m_rawContent.size())};

    container->m_commandId = readCommandId(buffer);
    CommandId::Id id       = CommandId::Id(uint16_t(container->m_commandId));

    //	LOGWARNING(logger, "Looking for *** " << std::hex << container->m_commandId << std::dec <<" ***");

    const auto& providerMap = m_baip.getMap(); // BufferAndImporterProvider::ProviderMap

    bool ok = true;
    for (const auto& p : providerMap)
    {
        const SpecialImporterBase<CommandCBase>::ImporterRegisterId::Key key = p.first;

        if (key.first != id)
        {
            continue;
        }

        SpecialImporterBase<CommandCBase>* const si = m_baip.getImporter(key);

        if (si)
        {
            //		LOGINFO(logger, "#############" << "Importer loaded for " << container->m_commandId << "(" << command << ")");
            CommandCBase* const cb = m_baip.getBuffer(key);

            //		LOGERROR(logger, "§§§§§§§§§§§§§§§§§§§ Container Ptr: " << (void*)cb);

            boost::iostreams::stream<boost::iostreams::array_source> strm(buffer, bufferSize);
            std::istream& s = (std::istream&)strm;
            ok              = si->deserialize(s, *cb, dh);

            if (ok)
            {
                //			LOGTRACE(logger, "Deserilization ok");
                container->m_specialCommandMap[key.second] = cb;
            }
            else
            {
                container->m_specialCommandMap[key.second] = nullptr;
            }
        }
    }

    return ok;
}

//==============================================================================

bool Importer<C, DataTypeId::DataType_Command2010>::callListener(DataContainerListenerBase* l,
                                                                 const DataContainerBase* const c) const
{
    const bool gok = RegisteredImporter<C, DataTypeId::DataType_Command2010>::callListener(l, c);

    //LOGTRACE(logger, "=============================================================");
    const C* container{nullptr};
    try
    {
        container = &dynamic_cast<const C&>(*c);
    }
    catch (const std::bad_cast&)
    {
        throw ContainerMismatch();
    }

    //LOGTRACE(logger, "=============================================================");

    const CommandId::Id cmdId = CommandId::Id(uint16_t(container->getCommandId()));

    auto spListener = dynamic_cast<SpecialListenerBase<C, CommandId::Id>*>(l);
    if (spListener)
    {
        using SpLstBaseKeyMap      = SpecialListenerBase<CommandCBase, CommandId::Id>::KeyMap;
        using SpLstBaseKeyVector   = SpecialListenerBase<CommandCBase, CommandId::Id>::KeyVector;
        const SpLstBaseKeyMap& rst = spListener->getRegisteredSubTypes();
        const SpLstBaseKeyMap::const_iterator rstvIter
            = rst.find(cmdId); // has any registered sub/special types for cmdId
        if (rstvIter != rst.end())
        {
            const SpLstBaseKeyVector& rstv = rstvIter->second;

            bool allOk = true;
            for (auto& key : rstv)
            {
                SpecialImporterBase<CommandCBase>* const si = m_baip.getImporter(key);
                const auto& scIter                          = container->getSpecialCommand().find(key.second);
                if (scIter != container->getSpecialCommand().end())
                {
                    const bool ok = si->callListener(l, *(scIter->second));
                    allOk         = allOk || ok;
                }
            }

            return allOk && gok;
        }
        else
        {
            LOGTRACE(logger, "Command Id: " << cmdId << " not registered");
        }
        LOGTRACE(logger, "Listener not registered for " << container->m_commandId);
    }

    return gok;
}

//==============================================================================

CommandId Importer<C, DataTypeId::DataType_Command2010>::readCommandId(const char* const buffer) const
{
    CommandId commandId(CommandId::Id::CmdManagerSetFilter);
    boost::iostreams::stream<boost::iostreams::array_source> strm(buffer, 2);
    std::istream& s = (std::istream&)strm;
    commandId.readBE(s);

    const CommandId::Id cmdId = CommandId::Id(uint16_t(commandId));
    const auto& providerMap   = m_baip.getMap(); // BufferAndImporterProvider::ProviderMap

    bool found = false;
    for (const auto& p : providerMap)
    {
        if (p.first.first == cmdId)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        char buf[sizeof(uint16_t)];
        char* bufPtr{&buf[0]};
        commandId.writeBE(bufPtr);

        const char* readBufPtr{&buf[0]};
        commandId.readLE(readBufPtr);
    }

    return commandId;
}

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
