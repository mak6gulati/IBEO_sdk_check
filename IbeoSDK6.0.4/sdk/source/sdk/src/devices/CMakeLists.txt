setupSources(SOURCES
        IbeoDeviceBase.cpp
        IbeoEcu.cpp
        IbeoEthDevice.cpp
        IbeoLux.cpp
        IbeoLuxHr.cpp
        IbeoMiniLux.cpp
        IbeoScala.cpp
        IbeoTcpIpAcceptorBase.cpp
        IbeoTcpIpAcceptorEcu.cpp
        IbeoTcpIpAcceptorScala.cpp
        IbeoTrackingBox.cpp
        IdcFile.cpp
        IdcFileController.cpp
        IdcIStream.cpp
        IdcOStream.cpp
        TcpReceiveThreadEnsemble.cpp
        ThreadEnsemble.cpp
        UdpDemultiplexer.cpp
        UdpReceiveThreadEnsemble.cpp
        GROUP devices)

include(${CMAKE_CURRENT_LIST_DIR}/sutp/CMakeLists.txt)
