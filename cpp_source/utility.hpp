#pragma once
#include <chrono>
#include <stdint.h>
#include <string>

#if defined(_WINDOWS)
#include <Winsock2.h> 
#else
#include <sys/types.h>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#endif

#ifdef ENGINE_DEBUGON
#include <fstream>
#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#endif

namespace Utility
{
	static uint64_t getTimeStamp()
	{
		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::system_clock::now().time_since_epoch()
			);

		return ms.count();
	}

	static uint64_t getTimeStampSeconds()
	{
		std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::system_clock::now().time_since_epoch()
			);

		return s.count();
	}

	static uint64_t getSteadyTimeStamp()
	{
		std::chrono::milliseconds ms = std::chrono::duration_cast<std::chrono::milliseconds>(
			std::chrono::steady_clock::now().time_since_epoch()
			);

		return ms.count();
	}

	static uint64_t getSteadyTimeStampSeconds()
	{
		std::chrono::seconds s = std::chrono::duration_cast<std::chrono::seconds>(
			std::chrono::steady_clock::now().time_since_epoch()
			);

		return s.count();
	}

	template<class _X>
	struct AutoDeleterArry
	{
		AutoDeleterArry(_X *deletedObj) : obj_(deletedObj) {}

		AutoDeleterArry()
		{
			if (obj_)
				delete[]obj_;
			obj_ = 0;
		}

		_X* obj_;
	};

#if defined(_WINDOWS)
	static std::string getLocalIpAddress()
	{
		WORD wVersionRequested = MAKEWORD(2, 2);

		WSADATA wsaData;
		if (WSAStartup(wVersionRequested, &wsaData) != 0)
			return "";

		char local[255] = { 0 };
		gethostname(local, sizeof(local));
		hostent* ph = gethostbyname(local);
		if (ph == NULL)
			return "";

		in_addr addr;
		memcpy(&addr, ph->h_addr_list[0], sizeof(in_addr)); // get the first ip address

		std::string localIP;
		localIP.assign(inet_ntoa(addr));

		WSACleanup();
		return localIP;
	}
#else
	static std::string getLocalIpAddress()
	{
		struct ifaddrs *ifAddrStruct = NULL;
		struct ifaddrs *ifa = NULL;
		void *tmpAddrPtr = NULL;
		std::size_t found = -1;
		std::string ret;
		getifaddrs(&ifAddrStruct);

		for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next)
		{
			if (!ifa->ifa_addr)
			{
				continue;
			}
			if (ifa->ifa_addr->sa_family == AF_INET)
			{ // check it is IP4
				// is a valid IP4 Address
				tmpAddrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
				char addressBuffer[INET_ADDRSTRLEN];
				inet_ntop(AF_INET, tmpAddrPtr, addressBuffer, INET_ADDRSTRLEN);

				std::string ifa_name(ifa->ifa_name);

				found = ifa_name.find("vmnet");
				if (found != std::string::npos && found == 0)
					continue;

				found = ifa_name.find("docker");
				if (found != std::string::npos && found == 0)
					continue;

				std::string addr(addressBuffer);

				found = addr.find(".0.1");
				if (found != std::string::npos)
				{
					if (found + 4 == addr.length())
						continue;
				}
				ret = addr;
			}
		}
		if (ifAddrStruct != NULL)
			freeifaddrs(ifAddrStruct);
		return ret;
	}
#endif

// for debug, if remove macro "ENGINE_DEBUGON", the daemon will compile fail on Linux because the opencv
#if ENGINE_DEBUGON
	static bool writeString2File(const std::string& str, const std::string& filepath)
	{
		boost::filesystem::path path(boost::filesystem::current_path().string() + "/" + filepath);

		if (!boost::filesystem::exists(path.parent_path()))
			boost::filesystem::create_directories(path.parent_path());  //目录不存在，创建 

		std::ofstream fout;
		fout.open(path.string());
		if (!fout.is_open())
		{
			return false;
		}
		fout << str;
		fout.close();
		return true;
	}

	static bool writeImage2File(const cv::Mat& img, const std::string& filepath)
	{
		boost::filesystem::path path(boost::filesystem::current_path().string() + "/" + filepath);

		if (!boost::filesystem::exists(path))
			boost::filesystem::create_directories(path.parent_path());  //目录不存在，创建 
		cv::imwrite(path.string(), img);

		return true;
	}

#endif

	static void setThreadName(char* name)
	{
		#ifdef __linux__
		pthread_setname_np(pthread_self(), name);
		#endif
	}
}
