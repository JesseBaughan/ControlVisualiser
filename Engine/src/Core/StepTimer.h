/**
 * @brief This time class is based off of the DirectX StepTimer sample.
 * Original code can be found here:
 * https://github.com/microsoft/DirectX-Graphics-Samples/blob/master/Samples/UWP/D3D12Bundles/src/StepTimer.h
*/

#pragma once

#include <stdint.h>
#include <math.h>
#include <chrono>
#include <ctime>

using namespace std::chrono;

class StepTimer
{
public:
    StepTimer()
        :  m_targetElapsedTime_us(1000)
    {
        m_lastTime = maxres_nonsleeping_clock::now();

        // Initialize max delta to 1/10 of a second.
        m_maxDelta = 10000;
    }

    // Get elapsed time since the previous Update call.
    uint64_t GetElapsedTimeUs()                                  const { return m_elapsedTime_us; }
    double GetElapsedSeconds()                                  const { return static_cast<double>(m_elapsedTime_us * 1e-6); }

    // Get total time since the start of the program.
    uint64_t GetTotalTime_us()                                    const { return m_totalTime_us; }
    double GetTotalSeconds()                                    const { return static_cast<double>(m_totalTime_us * 1e-6); }

    // Get total number of updates since start of the program.
    uint32_t GetFrameCount()                                    const { return m_frameCount; }

    // Get the current framerate.
    uint32_t GetFramesPerSecond()                               const { return m_framesPerSecond; }

    // Set whether to use fixed or variable timestep mode.
    void SetFixedTimeStep(bool isFixedTimestep)                 { m_isFixedTimeStep = isFixedTimestep; }

    // Set how often to call Update when in fixed timestep mode.
    void SetTargetElapsedTimeUs(uint64_t targetElapsed)          { m_targetElapsedTime_us = targetElapsed; }
    void SetTargetElapsedSeconds(double targetElapsed)          { m_targetElapsedTime_us = targetElapsed * 1e6; }

    using maxres_sys_or_steady =
        std::conditional<system_clock::period::den <= steady_clock::period::den,
                         system_clock, steady_clock>::type;

    using maxres_nonsleeping_clock =
        std::conditional<high_resolution_clock::is_steady,
                         high_resolution_clock, maxres_sys_or_steady>::type;

    // Integer format represents time using 10,000,000 ticks per second.
    static constexpr uint64_t TicksPerSecond = 10000000;

    void ResetElapsedTime()
    {
        m_leftOverTime_us = 0;
    }

    using LPUPDATEFUNC = void();

    // Update timer state, calling the specified Update function the appropriate number of times.
    void Tick(LPUPDATEFUNC update = nullptr)
    {
        // Query the current time.
        auto currentTime = maxres_nonsleeping_clock::now();

        uint64_t timeDelta = duration_cast<microseconds>(currentTime - m_lastTime).count();

        m_lastTime = currentTime;

        // Clamp excessively large time deltas (e.g. after paused in the debugger).
        if (timeDelta > m_maxDelta)
        {
            timeDelta = m_maxDelta;
        }

        if (m_isFixedTimeStep)
        {
            // Fixed timestep update logic

            // If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
            // the clock to exactly match the target value. This prevents tiny and irrelevant errors
            // from accumulating over time. Without this clamping, a game that requested a 60 fps
            // fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
            // accumulate enough tiny errors that it would drop a frame. It is better to just round
            // small deviations down to zero to leave things running smoothly.
            static constexpr uint64_t max_deviation_us = 250;   //1/4 of a millisecond
            if (abs(static_cast<int>(timeDelta - m_targetElapsedTime_us)) < max_deviation_us)
            {
                timeDelta = m_targetElapsedTime_us;
            }

            m_leftOverTime_us += timeDelta;

            while (m_leftOverTime_us >= m_targetElapsedTime_us)
            {
                m_elapsedTime_us = m_targetElapsedTime_us;
                m_totalTime_us += m_targetElapsedTime_us;
                m_leftOverTime_us -= m_targetElapsedTime_us;
                m_frameCount++;

                if (update)
                {
                    update();
                }
            }
        }
        else
        {
            // Variable timestep update logic.
            m_elapsedTime_us = timeDelta;
            m_totalTime_us += timeDelta;
            m_leftOverTime_us = 0;
            m_frameCount++;

            if (update)
            {
                update();
            }
        }
    }

private:
    // Source timing data uses QPC units.
    long int m_qpcFrequency;
    system_clock::time_point m_lastTime;
    uint64_t m_maxDelta;

    // Derived timing data uses a canonical tick format.
    uint64_t m_elapsedTime_us{0};
    uint64_t m_totalTime_us{0};
    uint64_t m_leftOverTime_us{0};

    // Members for tracking the framerate.
    uint64_t m_frameCount{0};
    uint64_t m_framesPerSecond{0};
    uint64_t m_framesThisSecond{0};

    // Members for configuring fixed timestep mode.
    bool m_isFixedTimeStep{false};
    uint64_t m_targetElapsedTime_us{0};
};