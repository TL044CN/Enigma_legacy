#ifndef TTPROFILER_H
#define TTPROFILER_H

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>
#include <format>

namespace Enigma {

    /**
     * @brief represents a Profiler Result
     */
    struct ProfileResult {
        std::string name;
        long long start, end;
        uint32_t tid;
    };

    /**
     * @brief represents a Profiler Session
     */
    struct ProfilerSession {
        std::string name;
    };

    /**
     * @brief Represents the Working Profiler
     */
    class Profiler {
    private:    /// private members
        ProfilerSession* mCurrentSession;
        std::ofstream mOutStream;
        uint32_t mProfileCount;

    public:     /// Constructors and Destructors
        /**
         * @brief Default Constructor 
         */
        Profiler() : mCurrentSession(nullptr), mProfileCount(0) {}

    private:    /// internal functionality
        void header();
        void footer();

    public:     /// exposed functionality
        void beginSession(
            const std::string& name,
            const std::string& path = "profile.plg"
        );
        void endSession();
        void writeProfile(const ProfileResult& result);

        static Profiler& get();
    };

    class ProfilerTimer {
    private:    /// internal aliases and datatypes
        using micros = std::chrono::microseconds;
        using clock = std::chrono::high_resolution_clock;
        using timepoint = std::chrono::time_point<clock>;

    private:    /// internal members
        const char* mName;
        timepoint mStartTimepoint;
        bool mStopped;

    public:     /// constructors and destructors
        ProfilerTimer(const char* name);
        ~ProfilerTimer();

    public:     /// exposed functionality
        void stop();

    };

}

#if ENGM_PROFILE
    #define ENGM_PROFILE_BEGIN_SESSION(name, path)\
        ::Enigma::Profiler::get().beginSession(name, path)
    #define ENGM_PROFILE_END_SESSION()\
        ::Enigma::Profiler::get().endSession()
    #define ENGM_PROFILE_SCOPE(name)\
        ::Enigma::ProfileTimer timer##__LINE__(name)
    #define ENGM_PROFILE_FUNCTION() ENGM_PROFILE_SCOPE(__FUNCSIG__)
#else
    #define ENGM_PROFILE_BEGIN_SESSION(name, path)
    #define ENGM_PROFILE_END_SESSION()
    #define ENGM_PROFILE_SCOPE(name)
    #define ENGM_PROFILE_FUNCTION()
#endif

#endif