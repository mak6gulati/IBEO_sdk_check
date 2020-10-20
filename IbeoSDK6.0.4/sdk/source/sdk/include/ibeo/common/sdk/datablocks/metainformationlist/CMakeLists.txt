setupHeaders(
    HEADERS
        MetaInformationAppBaseConfig.hpp
        MetaInformationBase.hpp
        MetaInformationEcuId.hpp
        MetaInformationFactory.hpp
        MetaInformationKeywords.hpp
        MetaInformationList.hpp
        MetaInformationListExporter7110.hpp
        MetaInformationListImporter7110.hpp
        MetaInformationUnsupported.hpp
        MetaInformationVersionNumber.hpp
    GROUP datablocks\\metainformationlist
)

include(${CMAKE_CURRENT_LIST_DIR}/special/CMakeLists.txt)
