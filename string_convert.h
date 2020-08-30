#pragma once

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <climits>
#include <stdexcept>
#include <string>

#if !defined(STRING_CONVERT_MAX)
constexpr size_t STRING_CONVERT_MAX = INT_MAX;
#endif

inline std::wstring convert(const std::string & mbs)
{
	std::wstring wcs;

	if (size_t size = mbs.size(); size <= STRING_CONVERT_MAX)
	{
		if (int cch = ::MultiByteToWideChar(CP_THREAD_ACP, 0, mbs.data(), static_cast<int>(size), nullptr, 0); cch > 0)
		{
			wcs.resize(cch);

			::MultiByteToWideChar(CP_THREAD_ACP, 0, mbs.data(), static_cast<int>(size), wcs.data(), cch);
		}
	}
	else
	{
		throw std::length_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): string too long");
	}

	return wcs;
}

inline std::string convert(const std::wstring & wcs)
{
	std::string mbs;

	if (size_t size = wcs.size(); size <= STRING_CONVERT_MAX)
	{
		if (int cch = ::WideCharToMultiByte(CP_THREAD_ACP, 0, wcs.data(), static_cast<int>(size), nullptr, 0, nullptr, nullptr); cch > 0)
		{
			mbs.resize(cch);

			::WideCharToMultiByte(CP_THREAD_ACP, 0, wcs.data(), static_cast<int>(size), mbs.data(), cch, nullptr, nullptr);
		}
	}
	else
	{
		throw std::length_error(__FILE__ "(" _CRT_STRINGIZE(__LINE__) "): string too long");
	}

	return mbs;
}
