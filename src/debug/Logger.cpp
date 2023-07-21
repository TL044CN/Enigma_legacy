#include "Logger.h"
#include <vector>
#include <format>
#include <sstream>
#include <chrono>
#include <iostream>

namespace Enigma {

    constexpr const char* colorReset = "\x1b[0m";

    Logger::RGBColor::RGBColor(uint8_t r, uint8_t g, uint8_t b)
    : R(r), G(g), B(b) {}

    Logger::RGBColor::RGBColor(const std::string& stringRep){
        R = static_cast<uint8_t>(std::stoul("0x"+stringRep.substr(0,2), nullptr, 16));
        G = static_cast<uint8_t>(std::stoul("0x"+stringRep.substr(2,2), nullptr, 16));
        B = static_cast<uint8_t>(std::stoul("0x"+stringRep.substr(4,2), nullptr, 16));
    }

    std::string_view Logger::RGBColor::toConsoleCode() const {
        std::stringstream ss;
        ss << "\x1b[38;2" << R << ';' << G << ';' << B;
        return ss.str();
    }

    Logger::Logger(std::ostream& stream, const std::string& loggerName)
    : mStream(std::make_shared<std::ostream>(stream)), mName(loggerName){}


    void Logger::log(const RGBColor& baseColor, const std::string& message){
        std::stringstream ss;
        ss << baseColor.toConsoleCode()
        << std::format(
            "[{}][{:%T}]",
            mName,
            std::chrono::floor<std::chrono::seconds>
            (std::chrono::high_resolution_clock::now())
        ) << message << colorReset;
        *mStream.get() << ss.str();
    }

    void Logger::trace(const std::string& message) {
        if(mLoglevel > Loglevel::Trace) return;
        log(RGBColor(200,200,200), message);
    }

    void Logger::info(const std::string& message) {
        if(mLoglevel > Loglevel::Info) return;
        log(RGBColor(10,255,40), message);
    }

    void Logger::warn(const std::string& message) {
        if(mLoglevel > Loglevel::Trace) return;
        log(RGBColor(255,255,0), message);
    }

    void Logger::error(const std::string& message) {
        if(mLoglevel > Loglevel::Trace) return;
        log(RGBColor(255,50,50), message);
    }

    void Logger::fatal(const std::string& message) {
        if(mLoglevel > Loglevel::Trace) return;
        log(RGBColor(255,0,0), message);
    }

}