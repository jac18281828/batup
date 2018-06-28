#include <cstdlib>
#include <cstring>
#include <iostream>

#include <libgen.h>

#include "properties.h"
#include "wordordercomp.h"
#include "wordorderdecomp.h"
#include "decompapp.h"
#include "compapp.h"

using namespace batup;

/**
 * print out some helpful usage info
 */
void usage(const char* name, const char *message);

// main entry point
int main(const int argc, const char* argv[]) {

    try {
        const properties props = parse_command_line(argc, argv);

        if(props.is_decompress()) {
            wordorderdecomp decomp;
            decompapp app(props, &decomp);
            app.run();
        } else {
            wordordercomp comp;
            compapp app(props, &comp);
            app.run();
        }

    } catch(const std::exception &error) {
        usage(argv[0], error.what());
        return EXIT_FAILURE;
    }
  
  
    return EXIT_SUCCESS;
}

void usage(const char* name, const char* message) {


    std::cerr << "stopped: " << message << std::endl;
    
    if(strcmp(basename(const_cast<char*>(name)), "batup") == 0) {
        std::cerr << name << ": [parameters] file" << std::endl;
    } else {
        std::cerr << name << ": [parameters] file.batz" << std::endl;
    }

    std::cerr << "\tcompress or decompress the given file" << std::endl;
    std::cerr << "-c: use stdin/stdout" << std::endl;
    std::cerr << "-d: decompress" << std::endl;
    
}
