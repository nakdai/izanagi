#include "izSystem.h"

namespace izanagi
{
    // ファイルオープン
    void CFileStream::OnOpen(FILE_HANDLE* file, const char* path, const char* mode)
    {
        fopen_s(file, path, mode);
    }

    void CFileStream::OnClose(FILE_HANDLE file)
    {
        if (file != IZ_NULL) {
            fclose(file);
        }
    }

    IZ_INT CFileStream::OnSeek(FILE_HANDLE file, IZ_INT offset, IZ_INT origin)
    {
        return fseek(file, offset, origin);
    }

    IZ_LONG CFileStream::GetLength(FILE_HANDLE file)
    {
        // ファイルサイズ取得
        fseek(file, 0, SEEK_END);
        IZ_LONG ret = ftell(file);
        fseek(file, 0, SEEK_SET);
        return ret;
    }

    IZ_INT CFileStream::OnRead(void* buf, IZ_UINT size, IZ_UINT count, FILE_HANDLE file)
    {
        return fread(buf, size, count, file);
    }

    IZ_UINT CFileStream::Tell(FILE_HANDLE file)
    {
        return (IZ_UINT)ftell(file);
    }

    IZ_UINT CFileStream::OnWrite(const void* src, size_t size, size_t count, FILE_HANDLE file)
    {
        return fwrite(src, size, count, file);
    }

    IZ_INT CFileStream::Print(FILE_HANDLE file, const char* str)
    {
        return IZ_FPRINTF(file, "%s", str);
    }
}
