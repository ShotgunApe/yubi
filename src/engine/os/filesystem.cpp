#include "filesystem.h"

namespace os_junk {

    float* load_file_to_ptr(const std::string file_to_open) {
        struct stat tmp_buf;
        if (stat(file_to_open.c_str(), &tmp_buf) != 0) {
            SDL_Log("File does not exist, exiting...");
            return nullptr;
        }

        if (S_ISDIR(tmp_buf.st_mode)) {
            SDL_Log("Is a folder, exiting...");
            return nullptr;
        }

        SDL_IOStream *file_io = SDL_IOFromFile(file_to_open.c_str(), "rb");
        size_t file_len = SDL_GetIOSize(file_io);

        if (file_io == nullptr) {
            SDL_Log("SDL_IOFromFile failed, exiting...");
            return nullptr;
        }

        float *to_return = new float[file_len];
        size_t bytes_read = SDL_ReadIO(file_io, to_return, file_len);

        if (bytes_read != file_len) {
            SDL_Log("SDL_ReadIO did not read entire file, exiting...");
            return nullptr;
        }

        SDL_CloseIO(file_io);
        return to_return;
    }

}
