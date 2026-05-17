#include "filesystem.h"

namespace os_junk {
    //https://stackoverflow.com/questions/28137559/can-someone-explain-wavwave-file-headers
    struct wav_header {
        char RIFF[4];
        char chunk_size[4];
        char format[4];

        char subchunk1_id[4];
        char subchunk1_size[4];
        char audio_format[2];
        char num_channels[2];
        char sample_rate[4];
        char byte_rate[4];
        char block_align[2];
        char bits_per_sample[2];

        char subchunk2_id[4];
        int subchunk2_size[4];
    };

    char* load_file_to_ptr(const std::string file_to_open) {
        struct stat tmp_buf;
        if (stat(file_to_open.c_str(), &tmp_buf) != 0) {
            SDL_Log("File does not exist");
            return nullptr;
        }

        if (S_ISDIR(tmp_buf.st_mode)) {
            SDL_Log("Is a folder");
            return nullptr;
        }

        SDL_IOStream *file_io = SDL_IOFromFile(file_to_open.c_str(), "rb");
        size_t file_len = SDL_GetIOSize(file_io);

        if (file_io == nullptr) {
            SDL_Log("SDL_IOFromFile failed");
            return nullptr;
        }

        char *to_return = new char[file_len];
        size_t bytes_read = SDL_ReadIO(file_io, to_return, file_len);

        if (bytes_read != file_len) {
            SDL_Log("SDL_ReadIO did not read entire file");
            return nullptr;
        }

        SDL_CloseIO(file_io);
        return to_return;
    }

    // TODO: return struct for parsing header of file once loaded (rb)
    wav_header* parse_file_header(const char* file_ptr) {
        wav_header *to_return = new wav_header;

        return to_return;
    }

}
