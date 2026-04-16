#pragma once

#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <functional>

class RenderWorker
{
public:
    static RenderWorker& Instance()
    {
        static RenderWorker instance;
        return instance;
    }

    void Submit(std::function<void()> job)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_jobs.push(std::move(job));
        }
        m_cv.notify_one();
    }

private:
    RenderWorker()
    {
        m_thread = std::thread(&RenderWorker::Loop, this);
    }

    ~RenderWorker()
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_running = false;
        }

        m_cv.notify_one();
        m_thread.join();
    }

    void Loop()
    {
        while (true)
        {
            std::function<void()> job;

            {
                std::unique_lock<std::mutex> lock(m_mutex);

                m_cv.wait(lock, [this]
                    {
                        return !m_jobs.empty() || !m_running;
                    });

                if (!m_running && m_jobs.empty())
                    return;

                job = std::move(m_jobs.front());
                m_jobs.pop();
            }

            job();
        }
    }

private:
    std::thread m_thread;
    std::mutex m_mutex;
    std::condition_variable m_cv;
    std::queue<std::function<void()>> m_jobs;
    bool m_running = true;
};