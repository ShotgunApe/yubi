#ifndef FILESYSTEM_H
#define FILESYSTEM_H

/*      /os/filesystem.h
 *
 *      This is where any filesystem handling is done.
 *
 */

#include <string>
#include <sys/stat.h>

#include <SDL3/SDL_log.h>
#include <SDL3/SDL_iostream.h>

// TODO: create function that generates filesystem on first boot - use posix functions to quickly get lists of songs
namespace os_junk {
    struct wav_header;
    char* load_file_to_ptr(const std::string file_to_open);
    wav_header* parse_file_header(const char* file_ptr);
}

#endif
