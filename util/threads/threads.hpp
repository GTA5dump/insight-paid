#include "common.hpp"

namespace insight
{
	struct thread_context 
	{
		const char* m_name{"Re"};
		HANDLE m_handle = 0;
		bool m_running = true;
		void* m_argument = nullptr;
		std::function<void(void*)> m_callback = {};
	};

	class threads 
	{
	public:
		static void add_job(std::function<void(void*)> callback, void* argument = nullptr);
		static void add_thread(const char* name, std::function<void(void*)> callback, void* argument = nullptr);
		static void remove_thread(const char* name);
	public:
		static void destroy();
	private:
		static threads* get()
		{
			static threads i{};

			return &i;
		}
	public:
		static void initialize() {
			get();
		}
	private:
		std::vector<thread_context*> m_threads;
	};

}