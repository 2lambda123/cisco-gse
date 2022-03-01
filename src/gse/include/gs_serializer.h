/*
 *  gs_serializer.h
 *
 *  Copyright (C) 2022
 *  Cisco Systems, Inc.
 *  All Rights Reserved
 *
 *  Description:
 *      The Game State Serializer is an object that will encode game state
 *      data into a given data buffer.
 *
 *      These functions will utilize the provided DataBuffer object in order
 *      to serialize various data types.  If an error occurs in writing to the
 *      data buffer, a DataBufferException may be thrown.  No attempt is
 *      made by the serializer to restore the buffer's data length to what
 *      it was before the error is thrown.  Doing so consumes CPU cycles and
 *      likely of no benefit to the caller.
 *
 *      Each of the serialization functions returns the number of octets written
 *      into the buffer.  No data is written if DataBuffer does not contain a
 *      valid pointer, but the number of octets that would have been written is
 *      returned.  This is useful for precomputing required space for variable-
 *      length objects.
 *
 *  Portability Issues:
 *      The C++ float and double types are assumed to be implemented following
 *      IEEE-754 specification.
 */

#ifndef GS_SERIALIZER_H
#define GS_SERIALIZER_H

#include <stdexcept>
#include "gs_types.h"
#include "data_buffer.h"

namespace gs
{

// SerializerException exception definition
class SerializerException : public std::runtime_error
{
    public:
        SerializerException(const std::string &what_arg) :
            std::runtime_error(what_arg)
        {
        }
};

// Game State Serializer object
class Serializer
{
    public:
        Serializer() = default;
        ~Serializer() = default;

        // Write unsigned integer types
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Uint8 value) const;
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Uint16 value) const;
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Uint32 value) const;
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Uint64 value) const;

        // Write signed integer types
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Int8 value) const;
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Int16 value) const;
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Int32 value) const;
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Int64 value) const;

        // Write variable-width integer types
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          const VarUint &value) const;
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          const VarInt &value) const;

        // Write floating point types
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          const Float16 &value) const;
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Float32 value) const;
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Float64 value) const;

        // Write the Boolean type
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          Boolean value) const;

        // Write strings
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          const String &value) const;

        // Write a blob object
        std::size_t Write(std::unique_ptr<DataBuffer<>> &data_buffer,
                          const Blob &value) const;
};

} // namespace gs

#endif // GS_SERIALIZER_H
