#include "../../Header/Renderer/ThreadInfo.h"

ThreadInfo::ThreadInfo() = default;
ThreadInfo::ThreadInfo(int index, int threadCount) {
	Index = index;
	ThreadCount = threadCount;
}