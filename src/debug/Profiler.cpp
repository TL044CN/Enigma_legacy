#include "Profiler.h"

namespace Enigma {

    void Profiler::header() {
        mOutStream << "[\n";
        mOutStream.flush();
    }

    void Profiler::footer() {
        mOutStream << "]";
        mOutStream.flush();
    }

    void Profiler::beginSession(
        const std::string &name, const std::string &path
    ) {
        mOutStream.open(path);
        header();
        mCurrentSession = new ProfilerSession{name};
    }

    void Profiler::endSession() {
        footer();
        mOutStream.close();
        delete mCurrentSession;
        mCurrentSession = nullptr;
        mProfileCount = 0;
    }

    void Profiler::writeProfile(const ProfileResult &result) {
        if(mProfileCount++ > 0) mOutStream << ',';
        std::string name = result.name;
        mOutStream << std::format(
            "{"
            "   \"Category\":{},\n"
            "   \"Duration\":{},\n"
            "   \"Name\":\"{}\",\n"
            "   \"TID\":{},\n"
            "   \"Timestamp\":{}"
            "}",
            "\"Function\"", (result.end-result.start),
            name, result.tid, result.start
        );
        mOutStream.flush();
    }

    Profiler& Profiler::get(){
        static Profiler instance;
        return instance;
    }


    ProfilerTimer::ProfilerTimer(const char* name)
    : mName(name), mStopped(false){
        mStartTimepoint = clock::now();
    }

    ProfilerTimer::~ProfilerTimer(){
        if(!mStopped) stop();
    }

    void ProfilerTimer::stop(){
        timepoint endTP = clock::now();
        long long start = std::chrono::time_point_cast<micros>(mStartTimepoint)
            .time_since_epoch().count();
        long long end = std::chrono::time_point_cast<micros>(endTP)
            .time_since_epoch().count();

        uint32_t tid = std::hash<std::thread::id>{}(std::this_thread::get_id());
        Profiler::get().writeProfile({mName, start, end, tid});
        mStopped = true;
    }

}