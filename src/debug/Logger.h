#ifndef TTLOGGER_H
#define TTLOGGER_H

#include <string_view>
#include <ostream>
#include <memory>

namespace Enigma {
    enum class Loglevel {
        Trace, Info, Warn, Error, Fatal
    };

    class Logger {
    private:
        struct RGBColor {
            uint8_t R, G, B;
            RGBColor(uint8_t r, uint8_t g, uint8_t b);
            RGBColor(const std::string& stringRep);
            std::string_view toConsoleCode() const;
        };

    private:
        Loglevel mLoglevel = Loglevel::Trace;
        std::shared_ptr<std::ostream> mStream;
        std::string mName;

    public:
        Logger(std::ostream& stream, const std::string& loggerName);

    private:
        void log(const RGBColor& baseColor, const std::string& message);

    public:
        void setLevel(Loglevel level);

        void info(const std::string& message);
        void warn(const std::string& message);
        void error(const std::string& message);
        void fatal(const std::string& message);
        void trace(const std::string& message);
    };
}

#endif