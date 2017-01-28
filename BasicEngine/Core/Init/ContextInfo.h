#pragma once
namespace BasicEngine {
	namespace Core {
		struct ContextInfo
		{
			int majorVersion, minorVersion;
			bool core;

			ContextInfo(int _majorVersion = 3, int _minorVersion = 3, bool _core = true) :
				majorVersion(_majorVersion),
				minorVersion(_minorVersion),
				core(_core) {};

			ContextInfo(ContextInfo& copied) {
				majorVersion = copied.majorVersion;
				minorVersion = copied.minorVersion;
				core = copied.core;
			}

			void operator=(ContextInfo copied) {
				majorVersion = copied.majorVersion;
				minorVersion = copied.minorVersion;
				core = copied.core;
			}
		};
	}
}