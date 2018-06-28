#include <cstring>
#include <exception>

// for basename
#include <libgen.h>

#include "properties.h"

class argumentexception: public std::exception
{
    virtual const char* what() const throw()
    {
        return "Invalid argument";
    }
};

batup::properties::properties() :
    decompress(false),
    writeStdout(true)
{
  
}

batup::properties::properties(const bool decompress,
                              const bool writeStdout,
                              const std::string &datafile) :
    decompress(decompress),
    writeStdout(writeStdout),
    datafile(datafile)
{
}

bool batup::properties::is_decompress() const {
    return decompress;
}

bool batup::properties::use_stdout() const {
    return writeStdout;
}

const std::string &batup::properties::getDatafile() const {
    return datafile;
}

batup::properties batup::parse_command_line(const int argc, const char* argv[]) {
    bool isDecompress = false;
    bool isStdout     = true;
    std::string outfile;

    if(::strcmp(basename(const_cast<char*>(argv[0])), "batdown") == 0) {
        isDecompress = true;
    }

    for(int i=1; i<argc; i++) {
        if(argv[i][0] == '-') {
            switch(argv[i][1]) {
            case 'c':
                isStdout = true;
                break;
            case 'd':
                isDecompress = true;
                break;
            default:
                throw argumentexception();
            }
        } else {
            isStdout = false;
            outfile = argv[i];
        }
    }

    return properties(isDecompress, isStdout, outfile);
}
