#pragma once

#include <functional>
#include <future>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

class ThreadPool {
public:
	explicit ThreadPool(size_t size);
	~ThreadPool();

	template <typename Func, typename... Args>
	auto exec(Func func, Args... args) -> std::future<decltype(func(args...))>
	{
		std::packaged_task<decltype(func(args...))()> task(std::bind(func, std::forward<Args>(args)...));
		auto res = task.get_future();
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			m_tasks.emplace(std::move(task));
		}
		m_tasksPrepared.notify_one();
		return res;
	}

private:
	size_t m_size;
	std::queue<std::packaged_task<void()>> m_tasks;
	std::mutex m_mutex;
	std::vector<std::thread> m_threads;
	std::condition_variable m_tasksPrepared;
	bool m_tasksFinished = false;

	void tasks();
};
