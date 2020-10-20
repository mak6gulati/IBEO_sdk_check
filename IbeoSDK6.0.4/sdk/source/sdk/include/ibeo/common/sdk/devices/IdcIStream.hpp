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
//!\date Aug 22, 2018
//------------------------------------------------------------------------------

#pragma once

//==============================================================================

#include <ibeo/common/sdk/misc/WinCompatibility.hpp>

#include <ibeo/common/sdk/datablocks/IbeoDataHeader.hpp>
#include <ibeo/common/logging/logging.hpp>

#include <fstream>
#include <memory>

//==============================================================================
namespace ibeo {
namespace common {
namespace sdk {
//==============================================================================

//==============================================================================
//!\brief An IDC input stream.
//------------------------------------------------------------------------------
class IdcIStream
{
private:
    //========================================
    //!\brief A wrapper class providing a std::istream.
    //!
    //! The origin of the stored istream (reference)
    //! can be an istream passed in the constructor
    //! call or an internally hold fstream.
    //----------------------------------------
    class IStreamWrapper
    {
    public:
        //========================================
        //!\brief Constructor. Wraps the given istream.
        //!\param[in] is  istream to be wrapped.
        //----------------------------------------
        IStreamWrapper(std::istream& is);

        //========================================
        //!\brief Constructor. Wraps an internally held
        //!       fstream.
        //!
        //! The file will be opened in binary read mode.
        //!
        //!\param[in] filename  Name of the file the
        //!                     fstream will be associated
        //!                     with.
        //----------------------------------------
        IStreamWrapper(const std::string& filename);

        //========================================
        //!\brief Destructor.
        //!
        //! Closes an open fstream in case it has been
        //! opened.
        //----------------------------------------
        ~IStreamWrapper() = default;

    public:
        //========================================
        //!\brief Return the istream.
        //!\return A reference to the wrapped istream.
        //----------------------------------------
        std::istream& operator()() { return m_is; }

    public:
        //========================================
        //!\brief Checks whether the fstream is still open
        //!       if it is a file.
        //!\return \c true if this instance is not wrapping
        //!        a fstream or if the fstream is associated
        //!        to a file.
        //!        \c false if the instance is holding an
        //!        fstream which is not associated with a file.
        //----------------------------------------
        bool isOpen() const { return !m_isFile || m_fs.is_open(); }

        //========================================
        //!\brief Returns whether this instance is wrapping
        //!       an istream referring with the internal
        //!       fstream.
        //!\return \c true if this instance is wrapping
        //!        actually the internal fstream.
        //!        \c false if this instance was constructed
        //!        with an external istream.
        //----------------------------------------
        bool isFile() const { return m_isFile; }

    private:
        //========================================
        //!\brief Internal fstream. Valid only if
        //!       \a m_isFile is \c true.
        //!
        //----------------------------------------
        std::fstream m_fs{};

        //========================================
        //!\brief The reference to the wrapped istream.
        //----------------------------------------
        std::istream& m_is;

        //========================================
        //!\brief \c true if \a m_is is referring to
        //!       \m_fs.
        //----------------------------------------
        bool m_isFile;
    }; // IStreamWrapper

public:
    //========================================
    //!\brief Creates an IdcIStream from an external stream.
    //!\param[in] is  The external istream to be wrapped.
    //----------------------------------------
    explicit IdcIStream(std::istream& is);

    //========================================
    //!\brief Creates an IdcIStream which is associated
    //!       with the file given by \a filename.
    //!\param[in] filename  The name of the file to be
    //!                     wrapped as istream.
    //----------------------------------------
    explicit IdcIStream(const std::string& filename);

    //========================================
    //!\brief Destructor.
    //----------------------------------------
    ~IdcIStream() = default;

public:
    //========================================
    //!\brief Check whether the stream is currently
    //!       associated with a file if it was
    //!       constructed with a filename.
    //!
    //!\return \c true if the IdcIStream was initialized with
    //!        an istream object or if it was initialized
    //!        with a filename and it is currently
    //!        associated with a file.
    //!        \c false otherwise.
    //----------------------------------------
    bool isOpen() { return m_strw.isOpen(); }

    //========================================
    //!\brief Check whether the eofbit is set.
    //!\return \c true if the eofbit is set.
    //!        \c false otherwise.
    //----------------------------------------
    bool isEof() { return m_strw().eof(); }

    //========================================
    //!\brief Check whether no error bit is set.
    //! \return \c true if the not error bit is set.
    //!         \c false otherwise.
    //----------------------------------------
    bool isGood() { return m_strw().good(); }

    //========================================
    //!\brief Check whether the stream is associated
    //!       with a file.
    //! \return \c true if the stream is associated
    //!         with a file.
    //!         \c false otherwise.
    //----------------------------------------
    bool isFile() { return m_strw.isFile(); }

public:
    //========================================
    //!\brief Returns the filename of the stream.
    //!\return The filename, if the IdcIStream was
    //!        created with a filename. An empty
    //!        string otherwise.
    //----------------------------------------
    const std::string& getFilename() const { return m_filename; }

public:
    //========================================
    //!\brief Read the next DataBlock from the file.
    //!
    //! Only the header will be deserialized while the
    //! body will be read in file order.
    //!
    //! The buffer to hold the data will be allocated.
    //! A copy of the data from the file stream will be
    //! performed.
    //!\param[out] dh  IbeoDataHeader of the received
    //!                message.
    //!
    //!\return The contents of the datablock in raw
    //!        file order.
    //----------------------------------------
    std::shared_ptr<char> getNextDataBlockRaw(IbeoDataHeader& dh);

protected:
    static constexpr const char* loggerId = "ibeo::common::sdk::IdcIStream";
    static ibeo::common::logging::LoggerSPtr logger;

protected:
    //========================================
    //!\brief Internal stream, the IDC file.
    //----------------------------------------
    IStreamWrapper m_strw;

    //========================================
    //!\brief The name of an open file.
    //----------------------------------------
    std::string m_filename{}; //idc filename (only valid for opened file)
}; // IdcIStream

//==============================================================================
} // namespace sdk
} // namespace common
} // namespace ibeo
//==============================================================================
