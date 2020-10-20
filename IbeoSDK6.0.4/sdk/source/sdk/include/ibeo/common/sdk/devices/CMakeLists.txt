setupHeaders(HEADERS
        IbeoDevice.hpp
        IbeoDevice.tpp
        IbeoDeviceBase.hpp
        IbeoEcu.hpp
        IbeoEthDevice.hpp
        IbeoEthType.hpp
        IbeoLux.hpp
        IbeoLuxHr.hpp
        IbeoMiniLux.hpp
        IbeoScala.hpp
        IbeoTcpDevice.hpp
        IbeoTcpIpAcceptorBase.hpp
        IbeoTcpIpAcceptorEcu.hpp
        IbeoTcpIpAcceptorScala.hpp
        IbeoTrackingBox.hpp
        IdcFile.hpp
        IdcFileController.hpp
        IdcIStream.hpp
        IdcOStream.hpp
        TcpReceiveThreadEnsemble.hpp
        ThreadEnsemble.hpp
        UdpDemultiplexer.hpp
        UdpReceiveThreadEnsemble.hpp
        GROUP devices)

include(${CMAKE_CURRENT_LIST_DIR}/sutp/CMakeLists.txt)
