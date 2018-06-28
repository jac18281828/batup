#include <cstdlib>
#include <iostream>
#include <fstream>
#include "app.h"

using namespace batup;

app::app(const batup::properties &props) :
    props(props)
{
    
}

const properties &app::getProperties() const {
    return props;
}

void app::error(const std::string &message) const {

    std::cerr << "Error: " << message << std::endl;
}

void app::run() {
    
    if(props.getDatafile().empty()) {
        process(std::cin, std::cout);
    } else {
        std::ifstream input;

        input.open(props.getDatafile(), std::ios_base::in);

        if(props.use_stdout()) {
            process(input, std::cout);
        } else {

            std::ofstream output;

            std::string outfile = props.getDatafile();
            if(!props.is_decompress()) {

                outfile += ".batz";
            } else {
                size_t lastDot = outfile.find_last_of('.');
                if(lastDot != std::string::npos) {
                    outfile.erase(lastDot, std::string::npos);
                    std::ifstream testfile(outfile);
                    if(testfile.good()) {
                        std::string response;
                        
                        std::cout << "Overwrite " << outfile << "? (y/N) ";
                        std::cin >> response;

                        if(response != "y") {
                            exit(EXIT_FAILURE);
                        }
                    }
                    
                }
            }

            output.open(outfile, std::ios_base::out);
            
            process(input, output);
            
            output.close();
            
        }

        input.close();
            
    }
}


