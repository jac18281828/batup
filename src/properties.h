#pragma once

#include <string>

namespace batup {


    /**
     * properties object for tracking command arguments
     */
    class properties {
    private:
        bool decompress;
        bool writeStdout;
        std::string datafile;

    public:
        properties();

        properties(const bool decompress,
                   const bool writeStdout,
                   const std::string &datafile);

        bool is_decompress() const;

        bool use_stdout() const;

        const std::string &getDatafile() const;

    };

    properties parse_command_line(const int argc, const char* argv[]);
};
