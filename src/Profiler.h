#pragma once
#include "Core.h"
#include "Timestep.h"

class Profiler
{
public:
    Profiler();
    void DrawCall();
    void Update(float time, Timestep ts);

    struct Stats
    {
        int fps = 0;
        float frameTime = 0;
        int drawCalls;
        std::string renderer;
        std::string version;
    };

    void SetRenderer(std::string renderer);
    void SetVersion(std::string version);
    Profiler::Stats GetStats();

private:
    template <std::size_t Length>
    float average(uint32_t const (&arr)[Length]);
    float m_Time;
    Stats m_Stats;
    float m_LastFpsTime;
    float m_NumFrames;
    uint32_t m_DrawCalls[60];
    uint32_t m_DrawCallIndex = 0;
};