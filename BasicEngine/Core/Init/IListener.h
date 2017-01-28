#pragma once
namespace BasicEngine {
	namespace Core {
		class IListener
		{
		public:
			virtual ~IListener() = 0;

			virtual void NotifyBeginFrame() = 0;
			virtual void NotifyDisplayFrame() = 0;
			virtual void NotifyEndFrame() = 0;
			virtual void NotifyReshape(int widhth, int height, int previousWidth, int previousHeight) = 0;
		};

		inline IListener::~IListener() {
			//Implementation of pure virtual destructor

		}
	}
}