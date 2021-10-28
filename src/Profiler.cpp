#include "Profiler.h"

Profiler::Profiler() {
    for(int i = 0; i < 60; i ++) {
        m_DrawCalls[i] = 0;
    }
}

void Profiler::Update(float time, Timestep ts) {

    // Calculate FPS 
    m_NumFrames++;
    double fpsDelta = time - m_LastFpsTime;
    m_Stats.frameTime = ts;
    
    if(fpsDelta >= 1.0) {
        double fps = double(m_NumFrames)/ fpsDelta;
        m_Stats.fps = (int)(fps);
        m_NumFrames = 0;
        m_LastFpsTime = time;
    }

    // Calculate Draw Calls
    m_Time += ts;
    if(m_Time >= 1.0f) {
        m_Stats.drawCalls = int(average<60>(m_DrawCalls));
        m_Time = 0;
    }
    m_DrawCallIndex = (m_DrawCallIndex + 1) % 60; 
    m_DrawCalls[m_DrawCallIndex] = 0;
}

void Profiler::DrawCall() {
    m_DrawCalls[m_DrawCallIndex]++;
}

Profiler::Stats Profiler::GetStats() {
    return m_Stats;
}

void Profiler::SetRenderer(std::string renderer) {
    m_Stats.renderer = renderer;
}

template< std::size_t Length >
float Profiler::average(uint32_t const (&arr)[Length]) {
    int sum = 0;
    int count = 0;
    for(int i = 0; i < Length; i ++) {
        sum += arr[i];
        if(arr[i] != 0)
            count++;
    }
    if(count == 0) return 0;
    return sum/count;

}
