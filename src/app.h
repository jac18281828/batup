#pragma once

#include <string>

#include "properties.h"

namespace batup {

    /**
     * A simple application container
     */
    class app {
    private:
        const properties &props;
        
    protected:
        virtual void process(std::istream &in, std::ostream &out) = 0;

        const properties &getProperties() const;

        void error(const std::string &msg) const;
        
    public:
        app(const properties &props);
        
        virtual void run();
    };
}
