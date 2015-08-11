#include "network/NetworkRemote.h"

namespace izanagi {
namespace net {
    Remote* Remote::create(IMemoryAllocator* allocator)
    {
        void* buf = ALLOC(allocator, sizeof(Remote));
        Remote* client = new(buf) Remote;
        return client;
    }

    void Remote::deteteRemote(
        IMemoryAllocator* allocator,
        Remote* client)
    {
        FREE(allocator, client);
    }

    Remote::Remote()
    {
        m_socket = IZ_INVALID_SOCKET;
        
        m_allocator = nullptr;
        m_sendPacket.size = 0;
        m_sendPacket.data = nullptr;

        m_isRegistered = IZ_FALSE;
    }

    Remote::~Remote()
    {}

    // クライアントと接続しているソケットを割り当てる.
    void Remote::setSocket(IZ_SOCKET socket)
    {
        m_socket = socket;
    }

    // クライアントと接続しているソケットを取得.
    IZ_SOCKET Remote::getSocekt()
    {
        return m_socket;
    }

    // ソケットが有効かどうかを取得.
    IZ_BOOL Remote::isActive() const
    {
        return (m_socket != IZ_INVALID_SOCKET);
    }

    // データを送信.
    IZ_INT Remote::sendData(const void* data, IZ_UINT size)
    {
        VRETURN_VAL(isValidSocket(m_socket), 0);
        IZ_INT ret = send(m_socket, (const char*)data, size, 0);
        return ret;
    }

    // 登録されているデータを送信.
    IZ_INT Remote::sendData()
    {
        if (m_sendPacket.data == nullptr
            || !m_isRegistered)
        {
            return 0;
        }

        VRETURN_VAL(isValidSocket(m_socket), 0);

        IZ_INT ret = sendData(m_sendPacket.data, m_sendPacket.size);

        if (ret > 0) {
            m_isRegistered = IZ_FALSE;
        }

        return ret;
    }

    // データを受信.
    IZ_INT Remote::recieveData(void* data, IZ_UINT size)
    {
        VRETURN_VAL(isValidSocket(m_socket), 0);
        IZ_INT ret = recv(m_socket, (char*)data, size, 0);
        return ret;
    }

    // 送信データを登録.
    IZ_BOOL Remote::registerData(
        IMemoryAllocator* allocator,
        IZ_UINT num,
        const void** data, IZ_UINT* size)
    {
        IZ_ASSERT(allocator != IZ_NULL);

        IZ_UINT total = 0;
        for (IZ_UINT i = 0; i < num; i++) {
            total += size[i];
        }

        if (m_sendPacket.data == nullptr) {
            // メモリが確保されていない場合
            m_sendPacket.data = (IZ_CHAR*)ALLOC(allocator, total);
            VRETURN(m_sendPacket.data);

            m_sendPacket.size = total;

            m_allocator = allocator;
        }
        else if (m_sendPacket.size < total) {
            // サイズが小さい場合
            VRETURN(m_allocator == allocator);

            m_sendPacket.data = (IZ_CHAR*)REALLOC(allocator, m_sendPacket.data, total);
            VRETURN(m_sendPacket.data);

            m_sendPacket.size = total;
        }

        auto dst = m_sendPacket.data;

        for (IZ_UINT i = 0; i < num; i++) {
            auto s = size[i];

            memcpy(dst, data[i], s);
            dst += s;
        }

        m_isRegistered = IZ_TRUE;

        return IZ_TRUE;
    }

    void Remote::close()
    {
        if (isValidSocket(m_socket)) {
            closesocket(m_socket);
            m_socket = IZ_INVALID_SOCKET;
        }

        if (m_allocator != nullptr) {
            FREE(m_allocator, m_sendPacket.data);

            m_sendPacket.size = 0;
            m_sendPacket.data = nullptr;

            m_allocator = nullptr;
        }
    }

    void Remote::reset()
    {
        if (isValidSocket(m_socket)) {
            closesocket(m_socket);
            m_socket = IZ_INVALID_SOCKET;
        }

        m_isRegistered = IZ_FALSE;
    }
}    // namespace net
}    // namespace izanagi
