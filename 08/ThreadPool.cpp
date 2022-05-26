#include "ThreadPool.hpp"

ThreadPool::ThreadPool(size_t size)
    : m_size(size)
{
	for (size_t i = 0; i < m_size; i++)
		m_threads.push_back(std::thread([this]() { tasks(); }));
}

ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(m_mutex);
		m_tasksFinished = true;
	}

	m_tasksPrepared.notify_all();
	for (auto& th : m_threads)
		th.join();
}

void ThreadPool::tasks()
{
	while (true) {
		std::packaged_task<void()> task;
		{
			std::unique_lock<std::mutex> lock(m_mutex);
			while (m_tasks.empty() && !m_tasksFinished)
				m_tasksPrepared.wait(lock);

			if (m_tasks.empty() && m_tasksFinished)
				return;

			task = std::move(m_tasks.front());
			m_tasks.pop();
		}
		task();
	}
}