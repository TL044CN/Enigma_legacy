#pragma once

#include <string>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <thread>

namespace Enigma {

	struct ProfileResult {
		std::string Name;
		long long Start, End;
		uint32_t ThreadID;
	};

	struct ProfilerSession {
		std::string Name;
	};

	class Profiler {
	private:
		ProfilerSession* m_CurrentSession;
		std::ofstream m_OutputStream;
		int m_ProfileCount;

	public:
		Profiler() :m_CurrentSession(nullptr), m_ProfileCount(0) {}

		void BeginSession(const std::string& name, const std::string& path = "profile.json") {
			m_OutputStream.open(path);
			Header();
			m_CurrentSession = new ProfilerSession{ name };
		}

		void EndSession() {
			Footer();
			m_OutputStream.close();
			delete m_CurrentSession;
			m_CurrentSession = nullptr;
			m_ProfileCount = 0;
		}

		void WriteProfile(const ProfileResult& result) {
			if (m_ProfileCount++ > 0)
				m_OutputStream << ",";

			std::string name = result.Name;
			std::replace(name.begin(), name.end(), '"', '\'');

			m_OutputStream << "\n{";
			m_OutputStream << "\"category\":\"function\",";
			m_OutputStream << "\"duration\":" << (result.End - result.Start) << ',';
			m_OutputStream << "\"name\":\"" << name << "\",";
			m_OutputStream << "\"ph\":\"X\",";
			m_OutputStream << "\"PID\":0,";
			m_OutputStream << "\"TID\":" << result.ThreadID << ',';
			m_OutputStream << "\"TimeStamp\":" << result.Start;
			m_OutputStream << "}";

			m_OutputStream.flush();
		}

		void Header() {
			m_OutputStream << "{\"otherData\": {},\"traceEvents\":[";
			m_OutputStream.flush();
		}

		void Footer() {
			m_OutputStream << "\n]}";
			m_OutputStream.flush();
		}

		static Profiler& Get() {
			static Profiler instance;
			return instance;
		}
	};

	class ProfilerTimer {
	public:
		ProfilerTimer(const char* name) :m_Name(name), m_Stopped(false) {
			m_StartTimepoint = std::chrono::high_resolution_clock::now();
		}

		~ProfilerTimer() {
			if (!m_Stopped)
				Stop();
		}

		void Stop() {
			auto endTimepoint = std::chrono::high_resolution_clock::now();

			long long start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimepoint).time_since_epoch().count();
			long long end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimepoint).time_since_epoch().count();

			uint32_t threadID = std::hash<std::thread::id>{}(std::this_thread::get_id());
			Profiler::Get().WriteProfile({ m_Name, start, end, threadID });

			m_Stopped = true;
		}
	private:
		const char* m_Name;
		std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimepoint;
		bool m_Stopped;
	};
}

#define ENGM_PROFILE 0
#if ENGM_PROFILE
	#define ENGM_PROFILE_BEGIN_SESSION(name, path) ::Enigma::Profiler::Get().BeginSession(name, path)
	#define ENGM_PROFILE_END_SESSION() ::Enigma::Profiler::Get().EndSession()
	#define ENGM_PROFILE_SCOPE(name) ::Enigma::ProfilerTimer timer##__LINE__(name)
	#define ENGM_PROFILE_FUNCTION() ENGM_PROFILE_SCOPE(__FUNCSIG__)
#else
	#define ENGM_PROFILE_BEGIN_SESSION(name, path)
	#define ENGM_PROFILE_END_SESSION()
	#define ENGM_PROFILE_SCOPE(name)
	#define ENGM_PROFILE_FUNCTION()
#endif