#if !defined(_IZANAGI_NETWORK_NETWORK_UDP_LIBUV_H__)
#define _IZANAGI_NETWORK_NETWORK_UDP_LIBUV_H__

#include <atomic>
#include "izDefs.h"
#include "izSystem.h"
#include "network/NetworkDefs.h"
#include "network/NetworkPacket.h"
#include "network/CallbackRegister.h"

namespace izanagi {
namespace net {
    /**
     */
    class Udp {
    public:
        Udp();
        virtual ~Udp();

        NO_COPIABLE(Udp);

    public:
        /** 起動.
         */
        IZ_BOOL start(
            IMemoryAllocator* allocator,
            const IPv4Endpoint& hostEp);

        /** 起動.
         */
        IZ_BOOL start(IMemoryAllocator* allocator);

        /** 接続.
         */
        IZ_BOOL connectTo(const IPv4Endpoint& remoteEp);

        /** 停止.
         */
        void stop();

        /** 受信したデータを取得.
         */
        IZ_INT recieve(
            void* buf,
            IZ_UINT size);

        IZ_INT recieveFrom(
            void* buf,
            IZ_UINT size,
            IPv4Endpoint& remoteEp);

        /** データを送信.
         */
        IZ_BOOL sendData(const void* data, IZ_UINT size);

        /** 指定した接続先にデータを送信.
         */
        IZ_BOOL sendTo(
            const void* data,
            IZ_UINT size,
            const IPv4Endpoint& remoteEp);

        inline IZ_BOOL IsStarted() const
        {
            return m_isStarted;
        }

    private:
        void startRecieve();

        void OnAlloc(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf);
        void OnRecieved(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags);

    protected:
        IMemoryAllocator* m_allocator{ nullptr };

        uv_udp_t m_udp;

        uv_udp_send_t m_reqSend;

        IZ_BOOL m_isBindAddr{ IZ_FALSE };
        IPv4Endpoint m_host;

        IZ_BOOL m_specifiedRemote{ IZ_FALSE };
        IPv4Endpoint m_remote;

        using CallbackOnAlloc = std::function < void(uv_handle_t* handle, size_t suggested_size, uv_buf_t* buf) >;
        Callback<CallbackOnAlloc> m_cbAllocated;

        using CallbackOnRecieved = std::function < void(uv_udp_t* handle, ssize_t nread, const uv_buf_t* buf, const struct sockaddr* addr, unsigned flags) > ;
        Callback<CallbackOnRecieved> m_cbRecieved;

        std::atomic<IZ_BOOL> m_isStarted{ IZ_FALSE };
        std::atomic<IZ_BOOL> m_isRecieving{ IZ_FALSE };

        struct RecvData {
            CStdList<RecvData>::Item listItem;
            uv_buf_t* buf;

            IZ_INT length{ -1 };

            IPv4Endpoint remote;

            RecvData()
            {
                listItem.Init(this);
            }
            ~RecvData() {}

            IZ_DECL_PLACEMENT_NEW();
        };

        std::mutex m_listRecvDataLocker;
        CStdList<RecvData> m_listRecvData;
    };
}    // namespace net
}    // namespace izanagi

#endif    // #if !defined(_IZANAGI_NETWORK_NETWORK_UDP_LIBUV_H__)
